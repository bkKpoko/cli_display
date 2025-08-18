#include "model.h"

model::model(Nvector<vertex3d> v, Nvector<triangle> tr)
    : vertices(v), trises(tr), pos(), rotation(), scale(1.) {}

model::~model() {}
