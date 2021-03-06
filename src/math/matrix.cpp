#include "include/math/matrix.h"
#include <QDebug>

Matrix::Matrix(int nRows, int nColumns) {
    this->nRows = nRows;
    this->nColumns = nColumns;
    for (int i=0; i<nRows; i++) {
        QVector<float> curr_row = {};
        for (int j=0; j<nColumns; j++) {
            curr_row.push_back(0.0);
        }
        this->matrice.push_back(curr_row);
    }
}

// optimize this class with this
Matrix::Matrix(int nRows, int nColumns, QVector<QVector<float>> matrice_data) {
    this->nRows = nRows;
    this->nColumns = nColumns;
    this->matrice = matrice_data;
}

Matrix* Matrix::scalar_add(float s) {
    QVector<QVector<float>> matrix = {};
    for (int i=0; i<this->nRows; i++) {
        QVector<float> curr_row = {};
        for (int j=0; j<this->nColumns; j++) {
            curr_row.push_back(this->matrice[i][j] + s);
        }
        this->matrice.push_back(curr_row);
    }
    return new Matrix(this->nRows, this->nColumns, matrix);
}

Matrix* Matrix::scalar_subtract(float s) {
    QVector<QVector<float>> matrix = {};
    for (int i=0; i<this->nRows; i++) {
        QVector<float> curr_row = {};
        for (int j=0; j<this->nColumns; j++) {
            curr_row.push_back(this->matrice[i][j] - s);
        }
        this->matrice.push_back(curr_row);
    }
    return new Matrix(this->nRows, this->nColumns, matrix);
}

Matrix* Matrix::scalar_multiply(float s) {
    QVector<QVector<float>> matrix = {};
    for (int i=0; i<this->nRows; i++) {
        QVector<float> curr_row = {};
        for (int j=0; j<this->nColumns; j++) {
            curr_row.push_back(this->matrice[i][j] * s);
        }
        this->matrice.push_back(curr_row);
    }
    return new Matrix(this->nRows, this->nColumns, matrix);
}

Matrix* Matrix::scalar_divide(float s) {
    QVector<QVector<float>> matrix = {};
    for (int i=0; i<this->nRows; i++) {
        QVector<float> curr_row = {};
        for (int j=0; j<this->nColumns; j++) {
            curr_row.push_back(this->matrice[i][j] / s);
        }
        this->matrice.push_back(curr_row);
    }
    return new Matrix(this->nRows, this->nColumns, matrix);
}

Matrix* Matrix::ew_add(Matrix *matrix) {
    if (matrix->nRows != this->nRows || matrix->nColumns != this->nColumns) {
        qDebug() << "cannot do element wise operation";
        return nullptr;
    }
    QVector<QVector<float>> matrice = {};
    for (int i=0; i<this->nRows; i++) {
        QVector<float> curr_row = {};
        for (int j=0; j<this->nColumns; j++) {
            curr_row.push_back(this->matrice[i][j] + matrix->matrice[i][j]);
        }
        this->matrice.push_back(curr_row);
    }
    return new Matrix(this->nRows, this->nColumns, matrice);
}

Matrix* Matrix::ew_subtract(Matrix *matrix) {
    if (matrix->nRows != this->nRows || matrix->nColumns != this->nColumns) {
        qDebug() << "cannot do element wise operation";
        return nullptr;
    }
    QVector<QVector<float>> matrice = {};
    for (int i=0; i<this->nRows; i++) {
        QVector<float> curr_row = {};
        for (int j=0; j<this->nColumns; j++) {
            curr_row.push_back(this->matrice[i][j] - matrix->matrice[i][j]);
        }
        this->matrice.push_back(curr_row);
    }
    return new Matrix(this->nRows, this->nColumns, matrice);
}

Matrix* Matrix::ew_multiply(Matrix *matrix) {
    if (matrix->nRows != this->nRows || matrix->nColumns != this->nColumns) {
        qDebug() << "cannot do element wise operation";
        return nullptr;
    }
    QVector<QVector<float>> matrice = {};
    for (int i=0; i<this->nRows; i++) {
        QVector<float> curr_row = {};
        for (int j=0; j<this->nColumns; j++) {
            curr_row.push_back(this->matrice[i][j] * matrix->matrice[i][j]);
        }
        this->matrice.push_back(curr_row);
    }
    return new Matrix(this->nRows, this->nColumns, matrice);
}

Matrix* Matrix::ew_divide(Matrix *matrix) {
    QVector<QVector<float>> matrice = {};
    for (int i=0; i<this->nRows; i++) {
        QVector<float> curr_row = {};
        for (int j=0; j<this->nColumns; j++) {
            curr_row.push_back(this->matrice[i][j] / matrix->matrice[i][j]);
        }
        this->matrice.push_back(curr_row);
    }
    return new Matrix(this->nRows, this->nColumns, matrice);
}

bool Matrix::compare(Matrix *matrix) {
    if (matrix->nRows != this->nRows || matrix->nColumns != this->nColumns)
        return false;
    for (int i=0; i<this->nRows; i++) {
        for (int j=0; j<this->nColumns; j++) {
            if (qAbs(this->matrice[i][j] - matrix->matrice[i][j]) > fEPSILON)
                return false;
        }
    }
    return true;
}

Matrix* Matrix::dot_product(Matrix *matrix) {
    if (this->nColumns != matrix->nRows) {
        qDebug() << "dot product impossible";
        return nullptr;
    }
    Matrix *mResult = new Matrix(this->nRows, matrix->nColumns);
    for (int i=0; i<this->nRows; i++) {
        for (int j=0; j<matrix->nColumns; j++) {
            float sum = 0.0;
            for (int k=0; k<this->nColumns; k++) {
                sum += this->matrice[i][k] * matrix->matrice[k][j];
            }
            mResult->matrice[i][j] = sum;
        }
    }
    return mResult;
}

Matrix* Matrix::identity_multiply() {
    Matrix *identity_matrix = Matrix::identity_matrix();
    Matrix* mResult = this->dot_product(identity_matrix);
    delete identity_matrix;
    return mResult;
}

Matrix* Matrix::identity_matrix() {
    Matrix *identity_matrix = new Matrix(4, 4);
    identity_matrix->matrice[0][0] = 1.0;
    identity_matrix->matrice[1][1] = 1.0;
    identity_matrix->matrice[2][2] = 1.0;
    identity_matrix->matrice[3][3] = 1.0;
    return identity_matrix;
}

Vector* Matrix::vector_multiply(Vector *vector) { // look at optimizing this
    Matrix *vector_as_matrix = Matrix::from_vector(vector);
    Matrix *dotted = this->dot_product(vector_as_matrix);
    Vector *vector_final = dotted->to_vector();
    delete vector_as_matrix;
    delete dotted;
    return vector_final;
}

Vector* Matrix::to_vector() {
    return new Vector(this->matrice[0][0], this->matrice[1][0], this->matrice[2][0], this->matrice[3][0]);
}

Matrix* Matrix::from_vector(Vector *vector) {
    Matrix *matrix = new Matrix(4, 1);
    matrix->matrice[0][0] = vector->fx;
    matrix->matrice[1][0] = vector->fy;
    matrix->matrice[2][0] = vector->fz;
    matrix->matrice[3][0] = vector->fw;
    return matrix;
}

Matrix* Matrix::transpose() {
    Matrix *transposed = new Matrix(this->nColumns, this->nRows);
    for (int i=0; i<this->nColumns; i++) {
        for (int j=0; j<this->nRows; j++) {
            transposed->matrice[i][j] = this->matrice[j][i];
        }
    }
    return transposed;
}

float Matrix::determinant() {
    if (2 == this->nColumns && 2 == this->nRows)
        return this->matrice[0][0] * this->matrice[1][1] - this->matrice[0][1] * this->matrice[1][0];
    float fDeterminant = 0.0;
    for (int i=0; i<this->nColumns; i++) {
        fDeterminant += this->matrice[0][i] * this->cofactor(0, i);
    }
    return fDeterminant;
}

Matrix* Matrix::submatrix(int nRow, int nCol) {
    QVector<QVector<float>> matrice = this->matrice;
    matrice.removeAt(nRow);
    for (int i=0; i<this->nRows - 1; i++) {
        matrice[i].removeAt(nCol);
    }
    return new Matrix(this->nRows - 1, this->nColumns - 1, matrice);
}

float Matrix::minor(int nRow, int nCol) {
    Matrix *submatrix = this->submatrix(nRow, nCol);
    float fminor = submatrix->determinant();
    delete submatrix;
    return fminor;
}

float Matrix::cofactor(int nRow, int nCol) {
    float fMinor = this->minor(nRow, nCol);
    if (0 == (nRow + nCol) % 2)
        return fMinor;
    return -fMinor;
}

Matrix* Matrix::inverse() { // look at refactoring
    float fDeterminant = this->determinant();
    if (0 == fDeterminant) {
        qDebug() << "cant be inverted";
        return nullptr;
    }
    Matrix *matrix = new Matrix(this->nRows, this->nColumns);
    for (int i=0; i<this->nRows; i++) {
        for (int j=0; j<this->nColumns; j++) {
            float fCofactor = this->cofactor(i, j);
            matrix->matrice[j][i] = fCofactor / fDeterminant;
        }
    }
    return matrix;
}

Matrix* Matrix::translation(float fx, float fy, float fz) {
    Matrix *matrix = new Matrix(4, 4);
    matrix->matrice = {
        {1.0, 0.0, 0.0, fx},
        {0.0, 1.0, 0.0, fy},
        {0.0, 0.0, 1.0, fz},
        {0.0, 0.0, 0.0, 1.0}
    };
    return matrix;
}

Matrix* Matrix::scaling(float fx, float fy, float fz) {
    Matrix *matrix = new Matrix(4, 4);
    matrix->matrice = {
        {fx, 0.0, 0.0, 0.0},
        {0.0, fy, 0.0, 0.0},
        {0.0, 0.0, fz, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
    return matrix;
}

Matrix* Matrix::rotate_x(float r) {
    Matrix *matrix = new Matrix(4, 4);
    matrix->matrice = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, qCos(r), -qSin(r), 0.0},
        {0.0, qSin(r), qCos(r), 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
    return matrix;
}

Matrix* Matrix::rotate_y(float r) {
    Matrix *matrix = new Matrix(4, 4);
    matrix->matrice = {
        {qCos(r), 0.0, qSin(r), 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {-qSin(r), 0.0, qCos(r), 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
    return matrix;
}


Matrix* Matrix::rotate_z(float r) {
    Matrix *matrix = new Matrix(4, 4);
    matrix->matrice = {
        {qCos(r), -qSin(r), 0.0, 0.0},
        {qSin(r), qCos(r), 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
    return matrix;
}

Matrix* Matrix::shearing(float fxy, float fxz, float fyx, float fyz, float fzx, float fzy) {
    Matrix *matrix = new Matrix(4, 4);
    matrix->matrice = {
        {1.0, fxy, fxz, 0.0},
        {fyx, 1.0, fyz, 0.0},
        {fzx, fzy, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
    return matrix;
}

Matrix* Matrix::view_transformation(Vector *from, Vector *to, Vector *up) {
    Vector *abfoward = to->ew_subtract(from);
    Vector *foward = abfoward->normalize();
    delete abfoward;
    up = up->normalize();
    Vector *left = foward->cross_product(up);
    Vector *true_up = left->cross_product(foward);
    Matrix *orientation = new Matrix(4, 4);
    orientation->matrice = {
        {left->fx, left->fy, left->fz, 0.0},
        {true_up->fx, true_up->fy, true_up->fz, 0.0},
        {-foward->fx, -foward->fy, -foward->fz, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
    delete foward;
    delete left;
    delete true_up;
    return orientation->dot_product(Matrix::translation(-from->fx, -from->fy, -from->fz));
}

Matrix* Matrix::clone() {
    Matrix *matrix = new Matrix(this->nRows, this->nColumns);
    matrix->matrice = this->matrice;
    return matrix;
}

QString Matrix::stringify() {
    QString sMatrix = "";
    for (int i=0; i<nRows; i++) {
        sMatrix += "[";
        for (int j=0; j<nColumns; j++) {
            sMatrix += QString::number(this->matrice[i][j]) + " ";
        }
        sMatrix = sMatrix.trimmed();
        sMatrix += "]\n";
    }
    return sMatrix;
}
