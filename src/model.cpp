#include "model.h"
#include "rot_mat.h"
#include <cstdio>
#include <fstream>

model::model() : vertices(), trises() {}

model::model(Nvector<vertex3d> v, Nvector<triangle> tr)
    : vertices(v), trises(tr), pos(), rotation(), scale(1.) {}

void model::import_stl(const char *name) {
  std::ifstream file(name, std::ios::binary);

  unsigned int num_triangles;
  float tmp;

  // skip header 80 bytes
  file.seekg(80, std::ios::beg);
  file.read(reinterpret_cast<char *>(&num_triangles), sizeof(num_triangles));

  trises.resize(num_triangles);
  vertices.resize(num_triangles * 3);

  for (size_t i = 0; i < num_triangles; ++i) {
    // skip normals
    file.seekg(12, std::ios::cur);
    for (size_t j = 0; j < 3; j++) {
      trises[i].v[j] = i * 3 + j;
      for (size_t k = 0; k < 3; k++) {
        file.read(reinterpret_cast<char *>(&tmp), sizeof(float));
        vertices[i * 3 + j][k] = (double)tmp;
      }
    }
    // skip attributes
    file.seekg(2, std::ios::cur);
  }
  file.close();

  pos = 0.;
  rotation = rot_mat();
  scale = 1;
}

model::~model() {}
