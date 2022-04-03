#include "include/pattern.h"
#include <QDebug>

Pattern::Pattern(Vector *colorA, Vector *colorB, PatternType type) {
    this->colorA = colorA;
    this->colorB = colorB;
    this->transformation = Matrix::identity_matrix();
    this->type = type;
}

Vector *Pattern::pattern_at(Vector *point, Matrix *transformation) {
    Vector *point_pattern_space = calc_pattern_point(point, transformation);
    switch (this->type) {
        case STRIPED:
            return stripe_at(point_pattern_space);
        case GRADIENT:
            return gradient_at(point_pattern_space);
        case RING:
            return ring_at(point_pattern_space);
        case CHECKERBOARD:
            return checker_at(point_pattern_space);
    }
    return new Vector(0, 0, 0, 0);
}

Vector *Pattern::stripe_at(Vector *point) {
    return 0 == qFloor(point->fx) % 2 ? colorA : colorB;
}

Vector *Pattern::gradient_at(Vector *point) { // wrong i think (only does greyscale)
    Vector *distance_from_colors = this->colorB->ew_subtract(this->colorA);
    float fFraction = point->fx - qFloor(point->fx);
    float x = distance_from_colors->fx;
    delete distance_from_colors;
    return this->colorA->scalar_add(x * fFraction);
}

Vector *Pattern::ring_at(Vector *point) {
    float fx = point->fx;
    float fz = point->fz;
    float fdistance_from_center = qSqrt(qPow(fx, 2) + qPow(fz, 2));
    return 0 == qFloor(fdistance_from_center) % 2 ? this->colorA : this->colorB;
}

Vector *Pattern::checker_at(Vector *point) {
    float fsum = qFloor(point->fx) + qFloor(point->fy) + qFloor(point->fz);
    return 0 == qFloor(fsum) % 2 ? this->colorA : this->colorB;
}

Vector *Pattern::calc_pattern_point(Vector *point, Matrix *transformation) {
    Matrix *mObject_Transformation = transformation->inverse();
    Matrix *mPattern_Transformation = this->transformation->inverse();
    Vector *object_point = mObject_Transformation->vector_multiply(point);
    Vector *pattern_point = mPattern_Transformation->vector_multiply(object_point);
    delete object_point;
    delete mObject_Transformation;
    delete mPattern_Transformation;
    return pattern_point;
}

void Pattern::transform(Matrix *matrix) {
    this->transformation = this->transformation->dot_product(matrix);
}





