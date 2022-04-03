/*
 TODO:
 bounding-boxes
 csg
 triangles
 obj parser
 anti aliasing
 soft shadows
 blur
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

float fEPSILON = 0.0001;

bool fuzzy_eq(float x, float y) {
    return qAbs(x - y) < fEPSILON;
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

int main(int argc, char *argv[]) {
    QCoreApplication application(argc, argv);
    long lStartTime = QDateTime::currentDateTime().toMSecsSinceEpoch();

    Camera *cam = new Camera(700, 700, M_PI / 3.0, Matrix::identity_matrix());
    Vector *from = new Vector(0, 3, -3, 1);
    Vector *to = new Vector(0, 1, 0, 1);
    Vector *up = new Vector(0, 1, 0, 0);
    cam->transformation = Matrix::view_transformation(from, to, up);

    World *world = new World();
    world->light = new Light(white, new Vector(-10, 10, -10, 1));

    render(cam, world);

    long lElapsedTime = QDateTime::currentDateTime().toMSecsSinceEpoch() - lStartTime;
    qDebug() << "rendering finished in" << lElapsedTime << "milliseconds";
    return 0;
}
