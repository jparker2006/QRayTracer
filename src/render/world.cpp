#include "include/render/world.h"
#include <QDebug>

World::World() {
    this->objects = {};
}

QVector<Intersection *> World::intersect_world(Ray *ray) {
    QVector<Intersection *> intersections = {};
    for (int i=0; i<this->objects.size(); i++) {
        Ray *rTransformed;
        if (this->objects[i]->bTransformed)
            rTransformed = ray->transform(this->objects[i]->mInverse);
        else
            rTransformed = new Ray(ray->origin->clone(), ray->direction->clone());
        QVector<Intersection *> curr_intersections = this->objects[i]->intersection(rTransformed);
        for (int j=0; j<curr_intersections.length(); j++) {
            intersections.push_back(curr_intersections[j]);
        }
        rTransformed->free_ray();
    }
    return intersections;
}

Vector* World::shade_hit(Computation *comp, int nRemaining) {
    bool shadowed = check_shadowed(comp->over_point);
    Vector *vSurface = comp->object->material->lighting(this->light, comp->over_point, comp->eye, comp->normal, shadowed, comp->object->transformation);
    Vector *vReflected = this->reflected_color(comp, nRemaining);
    Vector *vRefracted = this->refracted_color(comp, nRemaining);
    if (comp->object->material->fReflective > 0.0 && comp->object->material->fTransparency > 0.0) {
        float reflectance = schlick_approximation(comp);
        vReflected = vReflected->scalar_multiply(reflectance);
        vRefracted = vRefracted->scalar_multiply(1.0 - reflectance);
    }
    comp->free_computation(); // giving reflection stuff error (deleted then recurse)
    Vector *color = vSurface->ew_add(vReflected->ew_add(vRefracted));
    delete vSurface;
    delete vReflected;
    delete vRefracted;
    return color;
}

Vector* World::color_at(Ray *ray, int nRemaining) {
    QVector<Intersection *> intersections = this->intersect_world(ray);
    Intersection* intersection = Intersection::hit(intersections);
    if (!intersection)
        return new Vector(0, 0, 0, 0);
    Computation *comp = Computation::prepare_computations(ray, this->objects[intersection->index], intersection, intersections, this->objects);
    delete intersection;
    ray->free_ray();
    return shade_hit(comp, nRemaining);
}

Vector* World::reflected_color(Computation *comp, int nRemaining) {
    if (0 == comp->object->material->fReflective || nRemaining <= 0)
        return new Vector(0, 0, 0, 0);
    Ray *reflected_ray = new Ray(comp->over_point, comp->reflect);
    Vector *color = this->color_at(reflected_ray, nRemaining - 1);
    return color->scalar_multiply(comp->object->material->fReflective);
}

Vector* World::refracted_color(Computation *comp, int nRemaining) {
    if (0 == comp->object->material->fTransparency || nRemaining <= 0) {
        return new Vector(0, 0, 0, 0);
    }
    float fn_ratio = comp->n1 / comp->n2;
    float fcos_i = comp->eye->dot_product(comp->normal);
    float fsin2_t = qPow(fn_ratio, 2) * (1 - fcos_i);
    float fcos_t = qSqrt(1.0 - fsin2_t);
    Vector *vDir0 = comp->normal->scalar_multiply(fn_ratio * fcos_i - fcos_t);
    Vector *vDir1 = comp->eye->scalar_multiply(fn_ratio);
    Vector *vDirection = vDir0->ew_subtract(vDir1);
    delete vDir0;
    delete vDir1;
    Ray *refracted_ray = new Ray(comp->under_point, vDirection);
    Vector *ut_color = this->color_at(refracted_ray, nRemaining - 1);
    Vector *color = ut_color->scalar_multiply(comp->object->material->fTransparency);
    delete ut_color;
    return color;
}

bool World::check_shadowed(Vector *point) {
    Vector *v = this->light->position->ew_subtract(point);
    float fDistance = v->magnitude();
    Vector *direction = v->normalize();
    delete v;
    Ray *ray = new Ray(point, direction);
    QVector<Intersection *> intersections = this->intersect_world(ray);
    for (int i=0; i<intersections.length(); i++) {
        if (intersections[i]->ft > 0.0 && intersections[i]->ft < fDistance)
            return true;
    }
    return false;
}

float World::schlick_approximation(Computation *comp) {
    float fcos = comp->eye->dot_product(comp->normal);
    if (comp->n1 > comp->n2) {
        float fn = comp->n1 / comp->n2;
        float fsin2_t = qPow(fn, 2) * (1 - qPow(fcos, 2));
        if (fsin2_t > 1.0)
            return 1.0;
        fcos = qSqrt(1.0 - fsin2_t);
    }
    float fr0 = qPow((comp->n1 - comp->n2) / (comp->n1 + comp->n2), 2);
    return fr0 + (1.0 - fr0) * qPow(1.0 - fcos, 5);
}

void World::push(Body *body) {
    body->index = this->objects.size();
    this->objects.push_back(body);
}
