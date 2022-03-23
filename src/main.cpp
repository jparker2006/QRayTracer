#include <QCoreApplication>
#include <QDebug>
#include <QDateTime>

#include "include/vector.h"
#include "include/canvas.h"
#include "include/color.h"
#include "include/matrix.h"
#include "include/ray.h"
#include "include/sphere.h"
#include "include/intersection.h"
#include "include/light.h"
#include "include/material.h"

float fEPSILON = 0.0001;

bool fuzzy_eq(float x, float y) {
    return qAbs(x - y) < fEPSILON;
}

int main(int argc, char *argv[]) {
    QCoreApplication application(argc, argv);
    long lStartTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    int nCanvasDimension = 350;
    Canvas *canvas = new Canvas(nCanvasDimension, nCanvasDimension);
    Material *mat = new Material(new Vector(0.2, 0.7, 0.5, 0), 0.1, 0.9, 0.9, 200);
    Light *light = new Light(white, new Vector(-10, 10, -10, 1));
    Sphere *sphere = new Sphere(mat);
    float world_y, world_x, wall_z = 10, wall_size = 7.0, px_size = wall_size / nCanvasDimension, half = wall_size / 2;
    Vector *ray_origin = new Vector(0, 0, -5, 1);
    for (int y=0; y<nCanvasDimension; y++) {
        world_y = half - y * px_size;
        for (int x=0; x<nCanvasDimension; x++) {
            world_x = -half + x * px_size;
            Vector *position = new Vector(world_x, world_y, wall_z, 1.0);
            Ray *ray = new Ray(ray_origin, position->ew_subtract(ray_origin)->normalize());
            QVector<Intersection*> xs = sphere->intersection(ray);
            if (Intersection::hit(xs)) {
                Vector *point = ray->position(Intersection::hit(xs)->ft);
                Vector *normal = sphere->normal(point);
                Vector *eye = ray->direction->negate();
                Vector *color = mat->lighting(light, point, eye, normal);
                canvas->write_pixel(x, y, color);
            }
        }
    }
    canvas->write_ppm();
    long lElapsed = QDateTime::currentDateTime().toMSecsSinceEpoch() - lStartTime;
    qDebug() << "rendering finished in" << lElapsed << "milliseconds";
    application.exit();
    return 0;
}
