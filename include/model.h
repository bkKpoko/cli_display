#ifndef _MODEL_H_
#define _MODEL_H_

#include "game.h"
#include "lin_alg.h"
#include "rot_mat.h"

class model {
public:
  Nvector<vertex3d> vertices;
  Nvector<triangle> trises;

  vec3<double> pos;
  rot_mat rotation;
  vec3<double> scale;

  model(Nvector<vertex3d> v, Nvector<triangle> tr);

  ~model();
};
#endif // !_MODEL_H_
