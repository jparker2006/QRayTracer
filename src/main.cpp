#include <QCoreApplication>
#include "include/vector.h"
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication application(argc, argv);

    Vector *a = new Vector(1.0, 2.0, 3.0, 0.0);
    Vector *b = new Vector(2.0, 3.0, 4.0, 0.0);
    Vector *c = new Vector(0.0, 1.0, 0.0, 0.0);
    qDebug() << a->normalize()->stringify();

    return application.exec();
}
