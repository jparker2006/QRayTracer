#ifndef MATRIX_H
#define MATRIX_H

#include <QVector>

#include "include/math/vector.h"

class Matrix {
public:
    Matrix(int nRows, int nColumns);
    Matrix(int nRows, int nColumns, QVector<QVector<float> > matrice_data);
    Matrix *scalar_add(float s);
    Matrix *scalar_subtract(float s);
    Matrix *scalar_multiply(float s);
    Matrix *scalar_divide(float s);
    Matrix *ew_add(Matrix *matrix);
    Matrix *ew_subtract(Matrix *matrix);
    Matrix *ew_multiply(Matrix *matrix);
    Matrix *ew_divide(Matrix *matrix);
    bool compare(Matrix *matrix);
    Matrix *dot_product(Matrix *matrix);
    Matrix *identity_multiply();
    static Matrix* identity_matrix();
    Vector *vector_multiply(Vector *vector);
    Vector *to_vector();
    static Matrix *from_vector(Vector *vector);
    Matrix *transpose();
    float determinant();
    Matrix *submatrix(int nRow, int nCol);
    float minor(int nRow, int nCol);
    float cofactor(int nRow, int nCol);
    Matrix *inverse();
    static Matrix *translation(float fx, float fy, float fz);
    static Matrix *scaling(float fx, float fy, float fz);
    static Matrix *rotate_x(float r);
    static Matrix *rotate_y(float r);
    static Matrix *rotate_z(float r);
    static Matrix *shearing(float fxy, float fxz, float fyx, float fyz, float fzx, float fzy);
    static Matrix *view_transformation(Vector *from, Vector *to, Vector *up);
    QString stringify();
    Matrix *clone();

    int nRows, nColumns;
    QVector<QVector<float>> matrice = {};
    float fEPSILON = 0.0001;
};

#endif // MATRIX_H
