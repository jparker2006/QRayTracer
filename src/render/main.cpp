/*
 TODO:
 bounding-boxes
 csg
 soft shadows
 blur
 multithreading
*/
#include <QCoreApplication>
#include <QDebug>
#include <QDateTime>
#include <random>

#include "include/math/vector.h"
#include "include/render/canvas.h"
#include "include/textile/color.h"
#include "include/math/matrix.h"
#include "include/ray/ray.h"
#include "include/bodies/sphere.h"
#include "include/ray/intersection.h"
#include "include/render/light.h"
#include "include/textile/material.h"
#include "include/render/world.h"
#include "include/misc/computation.h"
#include "include/render/camera.h"
#include "include/bodies/plane.h"
#include "include/textile/pattern.h"
#include "include/bodies/cube.h"
#include "include/bodies/cylinder.h"
#include "include/bodies/cone.h"
#include "include/bodies/group.h"
#include "include/bodies/triangle.h"
#include "include/bodies/smoothtriangle.h"
#include "include/misc/parser.h"
#include "include/misc/thread.h"


//int main(int argc, char *argv[]) {
//    QCoreApplication application(argc, argv);
//    QMutex *mutex = new QMutex();
//    Vector *data = new Vector(0, 0, 0, 0);
//    Thread *t1 = new Thread(0, 0, mutex, data); // x
//    Thread *t2 = new Thread(0, 1, mutex, data); // y
//    Thread *t3 = new Thread(0, 2, mutex, data); // z
//    t1->start();
//    t2->start();
//    t3->start();
//    qDebug() << data->stringify();
//    return application.exec();
//}


inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

int nSamplesPerPixel = 10;
int nRayBounces = 1;
void render(Camera *camera, World *world) {
    Canvas *image = new Canvas(camera->fhsize, camera->fvsize);
    for (int y=0; y<camera->fvsize; y++) {
        for (int x=0; x<camera->fhsize; x++) {
            Vector *color = new Vector(0, 0, 0, 0);
            for (int z=0; z<nSamplesPerPixel; z++) {
                auto u = x + random_double();
                auto v = y + random_double();
                Ray *ray = camera->ray_for_pixel(u, v);
                color = color->ew_add(world->color_at(ray, nRayBounces));
            }
            image->write_pixel(x, y, color, nSamplesPerPixel);
        }
        qDebug() << (y / camera->fvsize) * 100.0 << "%";
    }
    image->write_ppm();
}

int main(int argc, char *argv[]) {
    QCoreApplication application(argc, argv);
    long lStartTime = QDateTime::currentDateTime().toMSecsSinceEpoch();

    int nWIDTH = 1920 / 4;
    int nHEIGHT = 1080 / 4;
    Camera *cam = new Camera(nWIDTH, nHEIGHT, M_PI / 4.0, Matrix::identity_matrix());
    Vector *from = new Vector(-3, 1, 2.5, 1);
    Vector *to = new Vector(0, 0.5, 0, 1);
    Vector *up = new Vector(0, 1, 0, 0);
    cam->transformation = Matrix::view_transformation(from, to, up);

    World *world = new World();
    world->light = new Light(new Vector(1.55, 1.55, 1.55, 0), new Vector(-1, 2, 4, 1));

    Material *plane_mat = new Material(white, 0.025, 0.67, 0, 0);
    Plane *plane = new Plane(plane_mat);
    Material *sp_mat_r = new Material(red, 0.1, 0.6, 0, 0);
    Material *sp_mat_b = new Material(new Vector(0.5, 0.5, 1.0, 0), 0.1, 0.6, 0, 0);

    Sphere *red_sphere = new Sphere(sp_mat_r);
    red_sphere->transform(Matrix::translation(0.5, 0.5, 0));
    red_sphere->transform(Matrix::scaling(0.5, 0.5, 0.5));

    Sphere *blue_sphere = new Sphere(sp_mat_b);
    blue_sphere->transform(Matrix::translation(-0.25, 0.33, 0));
    blue_sphere->transform(Matrix::scaling(0.33, 0.33, 0.33));

    world->push(red_sphere);
    world->push(blue_sphere);
    world->push(plane);

    render(cam, world);

    long lElapsedTime = QDateTime::currentDateTime().toMSecsSinceEpoch() - lStartTime;
    qDebug() << "rendering finished in" << lElapsedTime << "milliseconds";
    qDebug() << (nWIDTH * nHEIGHT) << "pixels rendered";
    qDebug() << ((float)(nWIDTH * nHEIGHT) / (float)(lElapsedTime)) << "px / ms";
    return 0;
}
