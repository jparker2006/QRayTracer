#ifndef RAY_H
#define RAY_H

#include "include/vector.h"
#include "include/matrix.h"

class Ray {
public:
    Ray(Vector *origin, Vector *direction);
    Vector *position(float ft);
    Vector *origin, *direction;
    Ray *transform(Matrix *matrix);
};

#endif // RAY_H