#include <QCoreApplication>
#include <QDebug>

#include "include/vector.h"
#include "include/canvas.h"
#include "include/color.h"
#include "include/matrix.h"

Matrix *create_4x4() {
    Matrix *m = new Matrix(4, 4);
    m->matrice = {{3, -9, 7, 3}, {3, -8, 2, -9}, {-4, 4, 4, 1}, {-6, 5, -1, 1}};
    return m;
}

Matrix *create_3x3() {
    Matrix *m = new Matrix(3, 3);
    m->matrice = {{1, 2, 6}, {-5, 8, -4}, {2, 6, 4}};
    return m;
}

Matrix *create_2x2() {
    Matrix *m = new Matrix(2, 2);
    m->matrice = {{-2, -8}, {3, 5}};
    return m;
}

int main(int argc, char *argv[]) {
    QCoreApplication application(argc, argv);
    return application.exec();
}

