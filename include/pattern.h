#ifndef PATTERN_H
#define PATTERN_H

#include "include/vector.h"
#include "include/matrix.h"

class Pattern {
public:
    enum PatternType {
        STRIPED,
        GRADIENT,
        RING,
        CHECKERBOARD
    };
    Pattern(Vector *colorA, Vector *colorB, PatternType type);
    Vector *pattern_at(Vector *point, Matrix *transformation);
    Vector *stripe_at(Vector *point);
    Vector *gradient_at(Vector *point);
    Vector *ring_at(Vector *point);
    Vector *checker_at(Vector *point);
    Vector *calc_pattern_point(Vector *point, Matrix *transformation);
    Vector *colorA, *colorB;
    Matrix *transformation;
    PatternType type;
    void transform(Matrix *matrix);
};

#endif // PATTERN_H
