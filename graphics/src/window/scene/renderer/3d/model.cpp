#include "model.h"

#include "extensions/file.h"
#include "extensions/char_extension.h"
#include "extensions/console.h"

#include <vector>

using namespace cppe::graphics;
using namespace cppe::character;
using namespace cppe::io;

void Model::bindVertices(const vector3f vertices[], const unsigned& number_of_vertices) {
    for (unsigned int i = 0; i < number_of_vertices; ++i) {
        Model_vertices.push_back(vertices[i]);
    }
}

const std::string Model::extract_line(const std::string& file_data, unsigned& counter) const {
    std::string temp = "";

    while (file_data[counter] != '\n' && file_data[counter] != ' ') {
        temp += file_data[counter++];
    }

    return temp;
}

const std::vector<vector3f> Model::extract(const std::string& file_data, unsigned& counter, const std::string& T) const {
    std::vector<vector3f> resultant;

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

            resultant.push_back(vector3f(a, b, c));
        } else {
            counter -= 2;
            break;
        }
    }

    return resultant;
}

const std::vector<unsigned> Model::extract_faces(const std::string& file_data, unsigned& counter) const {
    std::vector<unsigned> values;
    for (; counter < file_data.size(); ++counter) {
        if (file_data[counter++] == 'f') {
            std::string temp = "";
            while (file_data[counter] != '\n') {
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

void Model::load(const std::string& resource_name) {
    std::vector<unsigned> vertex_indices, texture_coordinate_indices, normal_indices;
    std::vector<vector3f> temp_vertices, temp_normals, temp_coordinates;
    std::vector<vector3f> ordered_vertices, ordered_normals, ordered_coordinates;
    std::vector<unsigned> faces;

    file file(resource_name);

    file.read();

    std::string data = file.data();

    std::string temp = "";

    unsigned counter = 0;

    while (temp == "") {
        if (data[counter + 1] == 'v') {
            counter++;
            break;
        }
        counter++;
    }

    temp_vertices = extract(data, counter, "v ");
    temp_normals = extract(data, counter, "vn");
    temp_coordinates = extract(data, counter, "vt");
    faces = extract_faces(data, counter);

    for (int i = 0; i < faces.size(); i += 3) {
        ordered_vertices.push_back(temp_vertices[faces[i]]);
        ordered_normals.push_back(temp_vertices[faces[i + 1]]);
        ordered_coordinates.push_back(temp_vertices[faces[i + 2]]);
    }

    

    //send data to open gl...
}

void Model::bindMaterial(const Material& material, const vector3f vertices[], const unsigned& number_of_vertices) {
    for (unsigned int i = 0; i < number_of_vertices; ++i) {
        texture_vertices.push_back(vertices[i]);
    }
    this->material = material;
}

const std::list<vector3f> Model::getModelVertices() const {
    return Model_vertices;
}

const std::list<vector3f> Model::getTextureVertices() const {
    return texture_vertices;
}

void Model::addModelVertex(const vector3f& vertex) {
    Model_vertices.push_back(vertex);
}

void Model::addTextureVertex(const vector3f& vertex) {
    texture_vertices.push_back(vertex);
}

const Material& Model::getMaterial() const {
    return material;
}
