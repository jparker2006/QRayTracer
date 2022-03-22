#include <QCoreApplication>
#include <QDebug>

#include "include/vector.h"
#include "include/canvas.h"
#include "include/color.h"
#include "include/matrix.h"
#include "include/ray.h"
#include "include/sphere.h"
#include "include/intersection.h"

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

    Canvas *canvas = new Canvas(100, 100);
    Sphere *sphere = new Sphere();
    float world_y, world_x, wall_z = 10, wall_size = 7.0, px_size = wall_size / 100, half = wall_size / 2;
    Vector *ray_origin = new Vector(0, 0, -5, 1);
    for (int y=0; y<100; y++) {
        world_y = half - y * px_size;
        for (int x=0; x<100; x++) {
            world_x = -half + x * px_size;
            Vector *position = new Vector(world_x, world_y, wall_z, 1.0);
            Ray *ray = new Ray(ray_origin, position->ew_subtract(ray_origin)->normalize());
            QVector<Intersection*> xs = sphere->intersection(ray, false);
            if (Intersection::hit(xs))
                canvas->write_pixel(x, y, blue);
        }
    }
    canvas->write_ppm();

    return application.exec();
}

