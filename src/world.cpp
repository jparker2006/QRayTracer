#include "include/world.h"
#include <QDebug>

World::World() {
    this->objects = {};
}

QVector<Intersection *> World::intersect_world(Ray *ray) {
    QVector<Intersection *> intersections = {};
    for (int i=0; i<this->objects.size(); i++) {
        QVector<Intersection *> curr_intersections = this->objects[i]->intersection(ray);
        for (int j=0; j<curr_intersections.length(); j++)
            intersections.push_back(curr_intersections[j]);
    }
    return intersections;
}

Vector* World::shade_hit(Computation *comp) {
    bool shadowed = check_shadowed(comp->over_point);
    return comp->object->material->lighting(this->light, comp->over_point, comp->eye, comp->normal, shadowed, comp->object->transformation);
}

Vector* World::color_at(Ray *ray) {
    QVector<Intersection *> intersections = this->intersect_world(ray);
    Intersection* intersection = Intersection::hit(intersections);
    if (!intersection)
        return new Vector(0, 0, 0, 0);
    Computation *comp = Computation::prepare_computations(ray, this->objects[intersection->index], intersection);
    delete intersection;
    delete ray;
    return shade_hit(comp);
}

bool World::check_shadowed(Vector *point) {
    Vector *v = this->light->position->ew_subtract(point);
    float fDistance = v->magnitude();
    Vector *direction = v->normalize();
    delete v;
    Ray *ray = new Ray(point, direction);
    QVector<Intersection *> intersections = this->intersect_world(ray);
    delete ray;
    for (int i=0; i<intersections.length(); i++) {
        if (intersections[i]->ft > 0.0 && intersections[i]->ft < fDistance)
            return true;
    }
    return false;
}
