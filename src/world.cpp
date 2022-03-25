#include "include/world.h"
#include <QDebug>

World::World() {

}

QVector<Intersection *> World::intersect_world(Ray *ray) {
    QVector<Intersection *> intersections = {};
    for (int i=0; i<this->objects.size(); i++) {
        QVector<Intersection *> curr_intersections = this->objects[i]->intersection(ray);
        for (int j=0; j<curr_intersections.length(); j++) {
            intersections.push_back(curr_intersections[j]);
        }
    }
    return intersections;
}

Vector* World::shade_hit(Computation *comp) {
    return comp->object->material->lighting(this->light, comp->point, comp->eye, comp->normal);
}

Vector* World::color_at(Ray *ray) {
    QVector<Intersection *> intersections = this->intersect_world(ray);
    if (0 == intersections.length())
        return new Vector(0, 0, 0, 0); // ray misses (change?)
    Computation *comp = Computation::prepare_computations(ray, this->objects[0], Intersection::hit(intersections));
    return shade_hit(comp);
}
