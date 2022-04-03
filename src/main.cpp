/*
 TODO:
 bounding-boxes
 csg
 obj parser
 anti aliasing
 soft shadows
 blur
 multithreading
*/
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
#include "include/world.h"
#include "include/computation.h"
#include "include/camera.h"
#include "include/plane.h"
#include "include/pattern.h"
#include "include/cube.h"
#include "include/cylinder.h"
#include "include/cone.h"
#include "include/group.h"
#include "include/triangle.h"
#include "include/parser.h"
#include "include/thread.h"

int main(int argc, char *argv[]) {
    QCoreApplication application(argc, argv);
    QMutex *mutex = new QMutex();
    Vector *data = new Vector(0, 0, 0, 0);
    Thread *t1 = new Thread(0, 0, mutex, data); // x
    Thread *t2 = new Thread(0, 1, mutex, data); // y
    Thread *t3 = new Thread(0, 2, mutex, data); // z
    t1->start();
    t2->start();
    t3->start();
    qDebug() << data->stringify();
    return application.exec();
}

void render(Camera *camera, World *world) {
    Canvas *image = new Canvas(camera->fhsize, camera->fvsize);
    for (int y=0; y<camera->fvsize; y++) {
        for (int x=0; x<camera->fhsize; x++) {
            Ray *ray = camera->ray_for_pixel(x, y);
            Vector *color = world->color_at(ray, 4);
            image->write_pixel(x, y, color);
            delete ray;
        }
        qDebug() << (y / camera->fvsize) * 100.0 << "%";
    }
    image->write_ppm();
}

//int main(int argc, char *argv[]) {
//    QCoreApplication application(argc, argv);
//    long lStartTime = QDateTime::currentDateTime().toMSecsSinceEpoch();

//    Camera *cam = new Camera(30, 30, M_PI / 3.0, Matrix::identity_matrix());
//    Vector *from = new Vector(0.0, 1.5, -5.0, 1);
//    Vector *to = new Vector(0, 1, 0, 1);
//    Vector *up = new Vector(0, 1, 0, 0);
//    cam->transformation = Matrix::view_transformation(from, to, up);

//    World *world = new World();
//    world->light = new Light(white, new Vector(-10, 10, -10, 1));

//    Parser *parser = new Parser();
//    QString sFile = "/home/jparker/Desktop/teapot.obj";
//    Group *g = parser->parse_file(sFile);

//    world->push(g);

//    render(cam, world);

//    long lElapsedTime = QDateTime::currentDateTime().toMSecsSinceEpoch() - lStartTime;
//    qDebug() << "rendering finished in" << lElapsedTime << "milliseconds";
//    return 0;
//}
