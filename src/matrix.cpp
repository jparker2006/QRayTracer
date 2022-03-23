#include "include/matrix.h"

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

Matrix* Matrix::scalar_add(float s) {
    Matrix *matrix = new Matrix(this->nRows, this->nColumns);
    for (int i=0; i<this->matrice.length(); i++) {
        for (int j=0; j<matrice[i].length(); j++) {
            matrix->matrice[i][j] = this->matrice[i][j] + s;
        }
    }
    return matrix;
}

Matrix* Matrix::scalar_subtract(float s) {
    Matrix *matrix = new Matrix(this->nRows, this->nColumns);
    for (int i=0; i<this->matrice.length(); i++) {
        for (int j=0; j<matrice[i].length(); j++) {
            matrix->matrice[i][j] = this->matrice[i][j] - s;
        }
    }
    return matrix;
}

Matrix* Matrix::scalar_multiply(float s) {
    Matrix *matrix = new Matrix(this->nRows, this->nColumns);
    for (int i=0; i<this->matrice.length(); i++) {
        for (int j=0; j<matrice[i].length(); j++) {
            matrix->matrice[i][j] = this->matrice[i][j] * s;
        }
    }
    return matrix;
}

Matrix* Matrix::scalar_divide(float s) {
    Matrix *matrix = new Matrix(this->nRows, this->nColumns);
    for (int i=0; i<this->matrice.length(); i++) {
        for (int j=0; j<matrice[i].length(); j++) {
            matrix->matrice[i][j] = this->matrice[i][j] / s;
        }
    }
    return matrix;
}

Matrix* Matrix::ew_add(Matrix *matrix) {
    if (matrix->nRows != this->nRows || matrix->nColumns != this->nColumns)
        return nullptr;
    Matrix *new_matrix = new Matrix(this->nRows, this->nColumns);
    for (int i=0; i<this->nRows; i++) {
        for (int j=0; j<this->nColumns; j++) {
            new_matrix->matrice[i][j] = this->matrice[i][j] + matrix->matrice[i][j];
        }
    }
    return new_matrix;
}

Matrix* Matrix::ew_subtract(Matrix *matrix) {
    if (matrix->nRows != this->nRows || matrix->nColumns != this->nColumns)
        return nullptr;
    Matrix *new_matrix = new Matrix(this->nRows, this->nColumns);
    for (int i=0; i<this->nRows; i++) {
        for (int j=0; j<this->nColumns; j++) {
            new_matrix->matrice[i][j] = this->matrice[i][j] - matrix->matrice[i][j];
        }
    }
    return new_matrix;
}

Matrix* Matrix::ew_multiply(Matrix *matrix) {
    if (matrix->nRows != this->nRows || matrix->nColumns != this->nColumns)
        return nullptr;
    Matrix *new_matrix = new Matrix(this->nRows, this->nColumns);
    for (int i=0; i<this->nRows; i++) {
        for (int j=0; j<this->nColumns; j++) {
            new_matrix->matrice[i][j] = this->matrice[i][j] * matrix->matrice[i][j];
        }
    }
    return new_matrix;
}

Matrix* Matrix::ew_divide(Matrix *matrix) {
    if (matrix->nRows != this->nRows || matrix->nColumns != this->nColumns)
        return nullptr;
    Matrix *new_matrix = new Matrix(this->nRows, this->nColumns);
    for (int i=0; i<this->nRows; i++) {
        for (int j=0; j<this->nColumns; j++) {
            new_matrix->matrice[i][j] = this->matrice[i][j] / matrix->matrice[i][j];
        }
    }
    return new_matrix;
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
    if (this->nColumns != matrix->nRows)
        return nullptr;
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
    Matrix *identity_matrix = new Matrix(4, 4);
    identity_matrix->matrice[0][0] = 1;
    identity_matrix->matrice[1][1] = 1;
    identity_matrix->matrice[2][2] = 1;
    identity_matrix->matrice[3][3] = 1;
    return this->dot_product(identity_matrix);
}

Vector* Matrix::vector_multiply(Vector *vector) {
    Matrix *matrix = Matrix::from_vector(vector);
    return this->dot_product(matrix)->to_vector();
}

Vector* Matrix::to_vector() {
    return new Vector(this->matrice[0][0], this->matrice[1][0], this->matrice[2][0], this->matrice[3][0]);
}

Matrix* Matrix::from_vector(Vector *vector) { static
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
    Matrix *matrix = new Matrix(this->nRows - 1, this->nColumns - 1);
    QVector<QVector<float>> matrice = this->matrice;
    matrice.removeAt(nRow);
    for (int i=0; i<this->nRows - 1; i++) {
        matrice[i].removeAt(nCol);
    }
    matrix->matrice = matrice;
    return matrix;
}

float Matrix::minor(int nRow, int nCol) {
    return this->submatrix(nRow, nCol)->determinant();
}

float Matrix::cofactor(int nRow, int nCol) {
    float fMinor = this->minor(nRow, nCol);
    if (0 == (nRow + nCol) % 2)
        return fMinor;
    return -fMinor;
}

Matrix* Matrix::inverse() {
    float fDeterminant = this->determinant();
    if (0 == fDeterminant)
        return nullptr;
    Matrix *matrix = new Matrix(this->nRows, this->nColumns);
    for (int i=0; i<this->nRows; i++) {
        for (int j=0; j<this->nColumns; j++) {
            float fCofactor = this->cofactor(i, j);
            matrix->matrice[j][i] = fCofactor / fDeterminant;
        }
    }
    return matrix;
}

Matrix* Matrix::translation(Vector *vec) { static
    Matrix *matrix = new Matrix(4, 4);
    matrix->matrice = {
        {1.0, 0.0, 0.0, vec->fx},
        {0.0, 1.0, 0.0, vec->fy},
        {0.0, 0.0, 1.0, vec->fz},
        {0.0, 0.0, 0.0, 1.0}
    };
    return matrix;
}

Matrix* Matrix::scaling(Vector *vec) { static
    Matrix *matrix = new Matrix(4, 4);
    matrix->matrice = {
        {vec->fx, 0.0, 0.0, 0.0},
        {0.0, vec->fy, 0.0, 0.0},
        {0.0, 0.0, vec->fz, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
    return matrix;
}

Matrix* Matrix::rotate_x(float r) { static
    Matrix *matrix = new Matrix(4, 4);
    matrix->matrice = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, qCos(r), -qSin(r), 0.0},
        {0.0, qSin(r), qCos(r), 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
    return matrix;
}

Matrix* Matrix::rotate_y(float r) { static
    Matrix *matrix = new Matrix(4, 4);
    matrix->matrice = {
        {qCos(r), 0.0, qSin(r), 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {-qSin(r), 0.0, qCos(r), 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
    return matrix;
}


Matrix* Matrix::rotate_z(float r) { static
    Matrix *matrix = new Matrix(4, 4);
    matrix->matrice = {
        {qCos(r), -qSin(r), 0.0, 0.0},
        {qSin(r), qCos(r), 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
    return matrix;
}

Matrix* Matrix::shearing(float fxy, float fxz, float fyx, float fyz, float fzx, float fzy) { static
    Matrix *matrix = new Matrix(4, 4);
    matrix->matrice = {
        {1.0, fxy, fxz, 0.0},
        {fyx, 1.0, fyz, 0.0},
        {fzx, fzy, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
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
