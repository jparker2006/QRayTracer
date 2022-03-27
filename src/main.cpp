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
    for (int y=0; y<camera->fvsize; y++) {
        for (int x=0; x<camera->fhsize; x++) {
            Ray *ray = camera->ray_for_pixel(x, y);
            Vector *color = world->color_at(ray);
            image->write_pixel(x, y, color);
        }
        qDebug() << (y / camera->fvsize) * 100.0 << "%";
    }
    image->write_ppm();
}

int main(int argc, char *argv[]) {
    QCoreApplication application(argc, argv);

    Camera *cam = new Camera(200, 100, M_PI / 3.0, Matrix::identity_matrix());
    Vector *from = new Vector(0, 1.5, -5, 1);
    Vector *to = new Vector(0, 1, 0, 1);
    Vector *up = new Vector(0, 1, 0, 0);
    cam->transformation = Matrix::view_transformation(from, to, up);

    World *world = new World();
    world->light = new Light(white, new Vector(-4, 10, -10, 1));
    Material *border_material = new Material(new Vector(1, 0.9, 0.9, 0), 0.1, 0.9, 0.0, 200);
    Material *middle_material = new Material(new Vector(0.1, 1.0, 0.5, 0.0), 0.2, 0.9, 0.7, 250);
    Material *right_material = new Material(new Vector(0.5, 1, 0.1, 0.0), 0.2, 0.9, 0.7, 150);
    Material *left_material = new Material(new Vector(1, 0.8, 0.1, 0.0), 0.2, 0.9, 0.7, 200);

    Sphere *middle = new Sphere(middle_material, 0);
    middle->transformation = middle->transformation->dot_product(Matrix::translation(new Vector(-0.5, 1.0, 0.5, 0.0)));

    Sphere *right = new Sphere(right_material, 1);
    right->transformation = right->transformation->dot_product(Matrix::translation(new Vector(1.5, 0.5, -0.5, 0.0)));
    right->transformation = right->transformation->dot_product(Matrix::scaling(new Vector(0.5, 0.5, 0.5, 0.0)));

    Sphere *left = new Sphere(left_material, 2);
    left->transformation = left->transformation->dot_product(Matrix::translation(new Vector(-1.5, 0.33, -0.75, 0.0)));
    left->transformation = left->transformation->dot_product(Matrix::scaling(new Vector(0.33, 0.33, 0.33, 0.0)));

    Sphere *floor = new Sphere(border_material, 3);
    floor->transformation = floor->transformation->dot_product(Matrix::scaling(new Vector(10.0, 0.01, 10.0, 0)));

    world->objects.push_back(middle);
    world->objects.push_back(right);
    world->objects.push_back(left);
    world->objects.push_back(floor);

    render(cam, world);

    return 0;
}







