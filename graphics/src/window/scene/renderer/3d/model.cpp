#include "model.h"

#include "extensions/file.h"
#include "extensions/char_extension.h"
#include "extensions/console.h"

#include <vector>

using namespace ftl::graphics;

const ftl::graphics::material& model::material() const {
    return _material;
}
const ftl::graphics::mesh& model::mesh() const {
    return _mesh;
}

void model::material(const ftl::graphics::material& material) {
    _material = material;
}
void model::mesh(const ftl::graphics::mesh& mesh) {
    _mesh = mesh;
}
