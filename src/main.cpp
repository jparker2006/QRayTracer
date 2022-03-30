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

float fEPSILON = 0.0001;

bool fuzzy_eq(float x, float y) {
    return qAbs(x - y) < fEPSILON;
}

void render(Camera *camera, World *world) {
    Canvas *image = new Canvas(camera->fhsize, camera->fvsize);
    for (int y=0; y<camera->fvsize; y++) {
        for (int x=0; x<camera->fhsize; x++) {
            Ray *ray = camera->ray_for_pixel(x, y);
            Vector *color = world->color_at(ray, 5);
            image->write_pixel(x, y, color);
        }
        qDebug() << (y / camera->fvsize) * 100.0 << "%";
    }
    image->write_ppm();
}

int main(int argc, char *argv[]) {
    QCoreApplication application(argc, argv);
    long lStartTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    Camera *cam = new Camera(200, 100, M_PI / 3.0, Matrix::identity_matrix());
    Vector *from = new Vector(0, 2.5, -5, 1);
    Vector *to = new Vector(0, 1, 0, 1);
    Vector *up = new Vector(0, 1, 0, 0);
    cam->transformation = Matrix::view_transformation(from, to, up);
    World *world = new World();
    world->light = new Light(white, new Vector(-10, 10, -10, 1));
    Pattern *pattern = new Pattern(Vector::from_rgb(100, 200, 60), Vector::from_rgb(200, 199, 50), Pattern::PatternType::STRIPED);
    Material *floor_material = new Material(new Vector(0.9, 0.9, 0.9, 0), 0.1, 0.9, 0.0, 200);
    Material *middle_material = new Material(new Vector(0.1, 1.0, 0.5, 0.0), 1, 0.9, 0.9, 200);
    middle_material->fTransparency = 1.0;
    middle_material->fReflective = 1.0;
    middle_material->fRefractive_Index = 1.5;
    Sphere *middle = new Sphere(middle_material, 0);
    middle->transformation = middle->transformation->dot_product(Matrix::translation(new Vector(-0.5, 1.0, 0.5, 0.0)));
    Plane *floor = new Plane(floor_material, 1);
    floor->material->pattern = pattern;
    world->objects.push_back(middle); // steal ID AUTO INCREMENT from sql
    world->objects.push_back(floor);
    render(cam, world);
    long lElapsedTime = QDateTime::currentDateTime().toMSecsSinceEpoch() - lStartTime;
    qDebug() << "rendering finished in" << lElapsedTime << "milliseconds";
    return 0;
}



