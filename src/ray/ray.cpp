#include "include/ray/ray.h"

Ray::Ray(Vector *origin, Vector *direction) {
    this->origin = origin;
    this->direction = direction;
}

Vector* Ray::position(float ft) {
    Vector *mvDirection = this->direction->scalar_multiply(ft);
    Vector *vPosition = mvDirection->ew_add(this->origin);
    delete mvDirection;
    return vPosition;
}

Ray* Ray::transform(Matrix *matrix) {
    return new Ray(matrix->vector_multiply(this->origin), matrix->vector_multiply(this->direction));
}

void Ray::free_ray() {
    delete this->origin;
    delete this->direction;
    delete this;
}
