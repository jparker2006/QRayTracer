#ifndef VECTOR_H
#define VECTOR_H

#include <QtMath>
#include <QString>

class Vector {
public:
    Vector(float fx, float fy, float fz, float fw);
    float fx, fy, fz, fw;
    Vector *ew_add(Vector *vec);
    Vector *ew_subtract(Vector *vec);
    Vector *ew_multiply(Vector *vec);
    Vector *ew_divide(Vector *vec);
    Vector *negate();
    Vector *scalar_add(float s);
    Vector *scalar_subtract(float s);
    Vector *scalar_multiply(float s);
    Vector *scalar_divide(float s);
    float magnitude();
    Vector *normalize();
    float dot_product(Vector *vec);
    Vector *cross_product(Vector *vec);
    Vector *identity_multiply();
    Vector *reflect(Vector *normal);
    QString stringify();
};

#endif // VECTOR_H
