#include "renderer3d.h"

using namespace cppe::graphics;
using namespace cppe::io;

void Renderer3d::init() {
    glGenVertexArrays(1, &vertex_array);
    glGenBuffers(1, &object_buffer);

    glBindVertexArray(vertex_array);
    glBindBuffer(GL_ARRAY_BUFFER, object_buffer);
    glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(VERTEX_INDEX);
    glEnableVertexAttribArray(TEXTURE_COORIDINATES_INDEX);
    glEnableVertexAttribArray(TEXTURE_INDEX);
    glEnableVertexAttribArray(COLOR_INDEX);
    glEnableVertexAttribArray(NORMALS_INDEX);

    glVertexAttribPointer(VERTEX_INDEX,
        3,
        GL_FLOAT,
        GL_FALSE,
        VERTEX_SIZE,
        (const GLvoid*)0);
    glVertexAttribPointer(TEXTURE_COORIDINATES_INDEX,
        2,
        GL_FLOAT,
        GL_FALSE,
        VERTEX_SIZE,
        (const GLvoid*)(offsetof(MeshData, MeshData::texture_cooridinates)));
    glVertexAttribPointer(TEXTURE_INDEX,
        1,
        GL_FLOAT,
        GL_FALSE,
        VERTEX_SIZE,
        (const GLvoid*)(offsetof(MeshData, MeshData::texture_id)));
    glVertexAttribPointer(COLOR_INDEX,
        4,
        GL_UNSIGNED_BYTE,
        GL_TRUE,
        VERTEX_SIZE,
        (const GLvoid*)(offsetof(MeshData, MeshData::color)));
    glVertexAttribPointer(NORMALS_INDEX,
        3,
        GL_FLOAT,
        GL_FALSE,
        VERTEX_SIZE,
        (const GLvoid*)(offsetof(MeshData, MeshData::normal)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint* indices = new GLuint[INDICES_SIZE];

    for (unsigned int i = 0, j = 0; i < INDICES_SIZE; i += 6, j += 4) {
        indices[i + 0] = j + 0;
        indices[i + 1] = j + 1;
        indices[i + 2] = j + 2;
        indices[i + 3] = j + 2;
        indices[i + 4] = j + 3;
        indices[i + 5] = j + 0;
    }

    std::unique_ptr<IndexBuffer> ib(new IndexBuffer(indices, INDICES_SIZE));
    index_buffer = std::move(ib);

    if (!index_buffer) {
        console::output_line("ERROR:\tfailed to init index buffer");
    }

    //index_count = 0;

    glBindVertexArray(0);

    //atlas = unique_atlas(std::move(texture_atlas_new(512, 512, 1)));
    //font = unique_font(std::move(texture_font_new_from_file(atlas.get(), 20, "")));

}
