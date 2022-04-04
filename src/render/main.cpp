﻿/*
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

void render(Camera *camera, World *world) {
    Canvas *image = new Canvas(camera->fhsize, camera->fvsize);
    for (int y=0; y<camera->fvsize; y++) {
        for (int x=0; x<camera->fhsize; x++) {
            Ray *ray = camera->ray_for_pixel(x, y);
            Vector *color = world->color_at(ray, 2);
            image->write_pixel(x, y, color);
            delete ray;
        }
        qDebug() << (y / camera->fvsize) * 100.0 << "%";
    }
    image->write_ppm();
}

int main(int argc, char *argv[]) {
    QCoreApplication application(argc, argv);
    long lStartTime = QDateTime::currentDateTime().toMSecsSinceEpoch();

    float fMULT = 1;
    float fWIDTH = 125 * fMULT;
    float fHEIGHT = 125 * fMULT;
    Camera *cam = new Camera(fWIDTH, fHEIGHT, M_PI / 2.5, Matrix::identity_matrix());
    Vector *from = new Vector(0.0, 2.5, -5.0, 1);
    Vector *to = new Vector(0, 1, 0, 1);
    Vector *up = new Vector(0, 1, 0, 0);
    cam->transformation = Matrix::view_transformation(from, to, up);

    World *world = new World();
    world->light = new Light(white, new Vector(-10, 10, -10, 1));

    Parser *parser = new Parser();
    QString sFile = "/home/jparker/Desktop/teapot.obj";
    Material *mat = new Material(white, 0.1, 0.9, 0.9, 200);
    QVector<Body*> g = parser->parse_file(sFile, mat);
    for (int i=0; i<g.size(); i++) {
        world->push(g[i]);
    }

    qDebug() << world->objects.size();

    Plane *plane = new Plane(new Material(new Vector(0.35, 0.35, 0.35, 0), 0.1, 0.9, 0.9, 200));
    world->push(plane);

    render(cam, world);

    long lElapsedTime = QDateTime::currentDateTime().toMSecsSinceEpoch() - lStartTime;
    qDebug() << "rendering finished in" << lElapsedTime << "milliseconds";
    qDebug() << (fWIDTH * fHEIGHT) << "pixels rendered";
    qDebug() << ((float)(fWIDTH * fHEIGHT) / (float)(lElapsedTime)) << "px / ms";
    return 0;
}



