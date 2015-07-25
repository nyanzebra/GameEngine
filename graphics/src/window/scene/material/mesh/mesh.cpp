#include "mesh.h"
#include "../../renderer/vertex_data.h"

#include <extensions/file.h>
#include <extensions/console.h>

#include <map>

using namespace ftl::graphics;


const std::vector<unsigned int>& mesh::indices() const {
    return _indices;
}

const std::vector<glm::vec3>& mesh::normals() const {
    return _normals;
}

const std::vector<glm::vec3>& mesh::vertices() const {
    return _vertices;
}

const std::vector<glm::vec2>& mesh::coordinates() const {
    return _coordinates;
}

void mesh::normals(const std::vector<glm::vec3>& normals) {
    _normals = normals;
}

void mesh::vertices(const std::vector<glm::vec3>& vertices) {
    _vertices = vertices;
}

void mesh::coordinates(const std::vector<glm::vec2>& coordinates) {
    _coordinates = coordinates;
}

const std::string mesh::extract_line(const std::string& file_data, unsigned& counter) const {
    std::string temp = "";

    while (file_data[counter] != '\n' && file_data[counter] != ' ') {
        temp += file_data[counter++];
    }

    return temp;
}

const std::vector<glm::vec3> mesh::extract(const std::string& file_data, unsigned& counter, const std::string& T) const {
    std::vector<glm::vec3> resultant;

    for (; counter < file_data.size(); ++counter) {
        std::string data_T = "";
        data_T += file_data[counter++];
        data_T += file_data[counter++];

        if (data_T == T) {
            if (file_data[counter] == ' ') {
                counter++;
            }

            float a = std::stof(extract_line(file_data, counter));
            counter++;

            float b = std::stof(extract_line(file_data, counter));
            counter++;

            float c = 0.0f;
            if (T != "vt") {
                c = std::stof(extract_line(file_data, counter));
            } else {
                counter--;
            }

            resultant.push_back(glm::vec3(a, b, c));
        } else {
            counter -= 2;
            break;
        }
    }
    return resultant;
}

const std::vector<unsigned> mesh::extract_faces(const std::string& file_data, unsigned& counter) const {
    std::vector<unsigned> values;
    for (; counter < file_data.size(); ++counter) {
        if (file_data[counter++] == 'f') {
            std::string temp = "";
            while (counter <= file_data.size() && file_data[counter] != '\n') {
                if (file_data[counter] != '/' && file_data[counter] != ' ') {
                    temp += file_data[counter];
                }
                counter++;
                if (file_data[counter] == '/' || file_data[counter] == ' ' || file_data[counter] == '\n') {
                    values.push_back(std::stoi(temp));
                    temp = "";
                }
            }
        } else {
            break;
        }
    }

    return values;
}

bool load_OBJ(const char * path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> & out_uvs, std::vector<glm::vec3> & out_normals) {
    printf("Loading OBJ file %s...\n", path);

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;


    FILE * file = fopen(path, "r");
    if (file == NULL) {
        printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
        getchar();
        return false;
    }

    while (1) {

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        // else : parse lineHeader

        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        } else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            temp_uvs.push_back(uv);
        } else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        } else if (strcmp(lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9) {
                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        } else {
            // Probably a comment, eat up the rest of the line
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }

    }

    // For each vertex of each triangle
    for (unsigned int i = 0; i < vertexIndices.size(); i++) {

        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        glm::vec3 vertex = temp_vertices[vertexIndex - 1];
        glm::vec2 uv = temp_uvs[uvIndex - 1];
        glm::vec3 normal = temp_normals[normalIndex - 1];

        // Put the attributes in buffers
        out_vertices.push_back(vertex);
        out_uvs.push_back(uv);
        out_normals.push_back(normal);

    }

    return true;
}

bool getSimilarVertexIndex_fast(vertex_data& packed, std::map<vertex_data, unsigned short>& VertexToOutIndex, unsigned short& result) {
    std::map<vertex_data, unsigned short>::iterator it = VertexToOutIndex.find(packed);
    if (it == VertexToOutIndex.end()) {
        return false;
    } else {
        result = it->second;
        return true;
    }
}

void indexVBO(std::vector<glm::vec3>& in_vertices, std::vector<glm::vec2>& in_uvs, std::vector<glm::vec3>& in_normals, std::vector<unsigned int>& out_indices, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals) {
    std::map<vertex_data, unsigned short> VertexToOutIndex;

    // For each input vertex
    for (unsigned int i = 0; i < in_vertices.size(); i++) {

        vertex_data packed = { in_vertices[i], in_normals[i], in_uvs[i] };


        // Try to find a similar vertex in out_XXXX
        unsigned short index;
        bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);

        if (found) { // A similar vertex is already in the VBO, use it instead !
            out_indices.push_back(index);
        } else { // If not, it needs to be added in the output data.
            out_vertices.push_back(in_vertices[i]);
            out_uvs.push_back(in_uvs[i]);
            out_normals.push_back(in_normals[i]);
            unsigned short newindex = (unsigned short)out_vertices.size() - 1;
            out_indices.push_back(newindex);
            VertexToOutIndex[packed] = newindex;
        }
    }
}

//http://www.opengl-tutorial.org/download/
void mesh::load(const std::string& resource_name) {
    load_OBJ(resource_name.c_str(), _vertices, _coordinates, _normals);
    indexer();   
}

//http://www.opengl-tutorial.org/download/
void mesh::indexer() {

    std::vector<glm::vec3> temp_normals;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_coordinates;

    indexVBO(_vertices, _coordinates, _normals, _indices, temp_vertices, temp_coordinates, temp_normals);

    _vertices = temp_vertices;
    _normals = temp_normals;
    _coordinates = temp_coordinates;
}
