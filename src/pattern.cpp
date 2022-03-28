#include "include/pattern.h"

Pattern::Pattern(Vector *colorA, Vector *colorB, PatternType type) {
    this->colorA = colorA;
    this->colorB = colorB;
    this->transformation = Matrix::identity_matrix();
    this->type = type;
}

Vector *Pattern::pattern_at(Vector *point, Matrix *transformation) {
    // maybe calc point in pattern space up here
    switch (this->type) {
        case STRIPED:
            return stripe_at(point, transformation);
        case GRADIENT:
            return gradient_at(point, transformation);
        case RING:
            return ring_at(point, transformation);
        case CHECKERBOARD:
            return checker_at(point, transformation);
    }
    return new Vector(0, 0, 0, 0);
}

Vector *Pattern::stripe_at(Vector *point, Matrix *transformation) {
    Vector *pattern_point = calc_pattern_point(point, transformation);
    return 0 == qFloor(pattern_point->fx) % 2 ? colorA : colorB;
}

Vector *Pattern::gradient_at(Vector *point, Matrix *transformation) {
    Vector *pattern_point = calc_pattern_point(point, transformation);
    Vector *distance_from_colors = this->colorB->ew_subtract(this->colorA);
    float fFraction = pattern_point->fx - qFloor(pattern_point->fx);
    return this->colorA->scalar_add(distance_from_colors->fx * fFraction);
}

Vector *Pattern::ring_at(Vector *point, Matrix *transformation) {
    Vector *pattern_point = calc_pattern_point(point, transformation);
    float fx = pattern_point->fx;
    float fz = pattern_point->fz;
    float fdistance_from_center = qSqrt(qPow(fx, 2) + qPow(fz, 2));
    return 0 == qFloor(fdistance_from_center) % 2 ? this->colorA : this->colorB;
}

Vector *Pattern::checker_at(Vector *point, Matrix *transformation) {
    Vector *pattern_point = calc_pattern_point(point, transformation);
    float fsum = qAbs(pattern_point->fx) + qAbs(pattern_point->fy) + qAbs(pattern_point->fz);
    return 0 == qFloor(fsum) % 2 ? this->colorA : this->colorB;
}

Vector *Pattern::calc_pattern_point(Vector *point, Matrix *transformation) {
    Vector *object_point = transformation->inverse()->vector_multiply(point);
    Vector *pattern_point = this->transformation->inverse()->vector_multiply(object_point);
    return pattern_point;
}

