#include "include/computation.h"
#include <QDebug>

Computation::Computation() {}

Computation* Computation::prepare_computations(Ray *ray, Body* body, Intersection *intersection, QVector<Intersection*> xs, QVector<Body*> world) {
    Computation *computations = new Computation();
    computations->object = body;
    computations->ft = intersection->ft;
    computations->point = ray->position(intersection->ft);
    computations->normal = body->normal(computations->point);
    computations->eye = ray->direction->negate();
    if (computations->normal->dot_product(computations->eye) < 0) {
        computations->bInside = true;
        computations->normal = computations->normal->negate();
    }
    else
        computations->bInside = false;
    float fEPSILON = 0.0001;
    Vector *nvEPSILON = computations->normal->scalar_multiply(fEPSILON);
    computations->over_point = computations->point->ew_add(nvEPSILON);
    computations->under_point = computations->point->ew_subtract(nvEPSILON);
    delete nvEPSILON;
    computations->reflect = ray->direction->reflect(computations->normal);
    QVector<Body*> container = {};
    for (int i=0; i<xs.length(); i++) {
        if (intersection->index == xs[i]->index && xs[i]->ft == intersection->ft) {
            if (container.isEmpty())
               computations->n1 = 1.0;
            else
                computations->n1 = container.last()->material->fRefractive_Index;
        }
        bool bIncluding = false;
        for (int x=0; x<container.size(); x++) {
            if (container[x]->index == intersection->index) {
                container.removeAt(x);
                bIncluding = true;
                break;
            }
        }
        if (!bIncluding)
            container.push_back(world[intersection->index]);
        if (intersection->index == xs[i]->index && xs[i]->ft == intersection->ft) {
            if (container.isEmpty())
                computations->n2 = 1.0;
            else
                computations->n2 = container.last()->material->fRefractive_Index;
            break;
        }
    }
    return computations;
}


