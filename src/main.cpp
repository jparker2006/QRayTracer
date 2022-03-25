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

float fEPSILON = 0.0001;

bool fuzzy_eq(float x, float y) {
    return qAbs(x - y) < fEPSILON;
}

void render(Camera *camera, World *world) {
    Canvas *image = new Canvas(camera->fhsize, camera->fvsize);
    for (int y=0; y<camera->fhsize; y++) {
        for (int x=0; x<camera->fhsize; x++) {
            Ray *ray = camera->ray_for_pixel(x, y);
            Vector *color = world->color_at(ray);
            image->write_pixel(x, y, color);
        }
        qDebug() << (y / camera->fhsize) * 100.0 << "%";
    }
    image->write_ppm();
}

int main(int argc, char *argv[]) {
    QCoreApplication application(argc, argv);
    Camera *cam = new Camera(300, 300, M_PI / 3.0, Matrix::identity_matrix());
    World *world = new World();
    world->light = new Light(white, new Vector(-10, 10, -10, 1));
    Material *mat = new Material(new Vector(0.8, 1.0, 0.6, 0), 0.1, 0.7, 0.2, 200);
    world->objects.push_back(new Sphere(mat));
    render(cam, world);
    return 0;
}
