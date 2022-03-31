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
#include "include/triangle.h"

float fEPSILON = 0.0001;

bool fuzzy_eq(float x, float y) {
    return qAbs(x - y) < fEPSILON;
}

void render(Camera *camera, World *world) {
    Canvas *image = new Canvas(camera->fhsize, camera->fvsize);
    for (int y=0; y<camera->fvsize; y++) {
        for (int x=0; x<camera->fhsize; x++) {
            Ray *ray = camera->ray_for_pixel(x, y);
            Vector *color = world->color_at(ray, 10);
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

    Camera *cam = new Camera(200, 100, M_PI / 3.0, Matrix::identity_matrix());
    Vector *from = new Vector(0, 3.6, -5, 1);
    Vector *to = new Vector(0, 1, 0, 1);
    Vector *up = new Vector(0, 1, 0, 0);
    cam->transformation = Matrix::view_transformation(from, to, up);

    World *world = new World();
    world->light = new Light(white, new Vector(-10, 10, -10, 1));

    Pattern *checker = new Pattern(black, white, Pattern::PatternType::CHECKERBOARD);
    checker->transform(Matrix::scaling(new Vector(0.75, 0.75, 0.75, 0)));

    Pattern *striped = new Pattern(Vector::from_rgb(247, 229, 148), Vector::from_rgb(221, 160, 221), Pattern::PatternType::STRIPED);
    striped->transform(Matrix::scaling(new Vector(0.17, 0.17, 0.17, 0)));

    Pattern *ring = new Pattern(Vector::from_rgb(250, 128, 114), Vector::from_rgb(135, 206, 235), Pattern::PatternType::RING);
    ring->transform(Matrix::scaling(new Vector(0.18, 0.18, 0.18, 0)));
    ring->transform(Matrix::rotate_x(M_PI / 2.0));

    Material *floor_material = new Material(black, 0.1, 0.9, 0.0, 200);
    floor_material->pattern = checker;

    Material *middle_material = new Material(Vector::from_rgb(27.8, 27.8, 27.8), 0.1, 0.9, 0.9, 200);
    middle_material->fTransparency = 1.0;
    middle_material->fRefractive_Index = 1.5;

    Material *right_material = new Material(white, 0.1, 0.9, 0.9, 200);
    right_material->pattern = ring;

    Material *left_material = new Material(white, 0.1, 0.9, 0.9, 200);
    left_material->pattern = striped;

    Sphere *middle = new Sphere(middle_material);
    middle->transform(Matrix::translation(new Vector(-0.5, 1.0, 0.5, 0.0)));

    Sphere *right = new Sphere(right_material);
    right->transform(Matrix::translation(new Vector(1.7, 0.5, -0.5, 0.0)));
    right->transform(Matrix::rotate_y(M_PI / 5));
    right->transform(Matrix::rotate_x(M_PI / 6));
    right->transform(Matrix::scaling(new Vector(0.7, 0.7, 0.7, 0.0)));

    Cone *left = new Cone(left_material);
    left->fMax = 1.0;
    left->bClosed = true;

    Plane *floor = new Plane(floor_material);

    world->push(middle);
    world->push(right);
    world->push(left);
    world->push(floor);

    render(cam, world);

    long lElapsedTime = QDateTime::currentDateTime().toMSecsSinceEpoch() - lStartTime;
    qDebug() << "rendering finished in" << lElapsedTime << "milliseconds";

    return 0;
}
