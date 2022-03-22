#include "include/ray.h"

Ray::Ray(Vector *origin, Vector *direction) {
    this->origin = origin;
    this->direction = direction;
}

Vector* Ray::position(float ft) {
    return this->direction->scalar_multiply(ft)->ew_add(this->origin);
}

Ray* Ray::transform(Matrix *matrix) {
    return new Ray(matrix->vector_multiply(this->origin), matrix->vector_multiply(this->direction));
}
