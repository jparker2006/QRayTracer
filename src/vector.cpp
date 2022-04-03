// vector has a w = 0.0
// point has a w = 1.0
// color x = r, y = g, z = b

#include "include/vector.h"
#include "include/matrix.h"

Vector::Vector(float fx, float fy, float fz, float fw) {
    this->fx = fx;
    this->fy = fy;
    this->fz = fz;
    this->fw = fw;
}

Vector* Vector::scalar_add(float s) {
    return new Vector(this->fx + s, this->fy + s, this->fz + s, this->fw + s);
}

Vector* Vector::scalar_subtract(float s) {
    return new Vector(this->fx - s, this->fy - s, this->fz - s, this->fw - s);
}

Vector* Vector::scalar_multiply(float s) {
    return new Vector(this->fx * s, this->fy * s, this->fz * s, this->fw * s);
}

Vector* Vector::scalar_divide(float s) {
    return new Vector(this->fx / s, this->fy / s, this->fz / s, this->fw / s);
}

Vector* Vector::ew_add(Vector *vec) {
    return new Vector(this->fx + vec->fx, this->fy + vec->fy, this->fz + vec->fz, this->fw + vec->fw);
}

Vector* Vector::ew_subtract(Vector *vec) {
    return new Vector(this->fx - vec->fx, this->fy - vec->fy, this->fz - vec->fz, this->fw - vec->fw);
}

Vector* Vector::ew_multiply(Vector *vec) {
    return new Vector(this->fx * vec->fx, this->fy * vec->fy, this->fz * vec->fz, this->fw * vec->fw);
}

Vector* Vector::ew_divide(Vector *vec) {
    return new Vector(this->fx / vec->fx, this->fy / vec->fy, this->fz / vec->fz, this->fw / vec->fw);
}

Vector* Vector::negate() {
    return new Vector(this->fx * -1.0, this->fy * -1.0, this->fz * -1.0, this->fw * -1.0);
}

float Vector::magnitude() {
    return qSqrt(qPow(this->fx, 2) + qPow(this->fy, 2) + qPow(this->fz, 2) + qPow(this->fw, 2));
}

Vector* Vector::normalize() {
    float fMag = this->magnitude();
    return new Vector(this->fx / fMag, this->fy / fMag, this->fz / fMag, this->fw / fMag);
}

float Vector::dot_product(Vector *vec) {
    return this->fx * vec->fx + this->fy * vec->fy + this->fz * vec->fz + this->fw * vec->fw;
}

Vector* Vector::cross_product(Vector *vec) {
    return new Vector(
        this->fy * vec->fz - this->fz * vec->fy,
        this->fz * vec->fx - this->fx * vec->fz,
        this->fx * vec->fy - this->fy * vec->fx,
        0.0
    );
}

Vector* Vector::identity_multiply() {
    Matrix *identity_matrix = Matrix::identity_matrix();
    Vector *identitied_vector = identity_matrix->vector_multiply(this);
    delete identity_matrix;
    return identitied_vector;
}

Vector* Vector::reflect(Vector *normal) {
    float in_dot_normal = this->dot_product(normal);
    Vector *multed = normal->scalar_multiply(2 * in_dot_normal);
    Vector *final = this->ew_subtract(multed);
    delete multed;
    return final;
}

Vector* Vector::from_rgb(float r, float g, float b) {
    return new Vector(r / 255.0, g / 255.0, b / 255.0, 0);
}

QString Vector::stringify() {
    QString sVec = "";
    sVec += "{ x: " + QString::number(this->fx);
    sVec += " y: " + QString::number(this->fy);
    sVec += " z: " + QString::number(this->fz);
    sVec += " w: " + QString::number(this->fw) + " }";
    return sVec;
}
