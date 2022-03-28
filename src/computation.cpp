#include "include/computation.h"
#include <QDebug>

Computation::Computation() {

}

Computation* Computation::prepare_computations(Ray *ray, Body* body, Intersection *intersection) { static
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
    computations->over_point = computations->point->ew_add(computations->normal->scalar_multiply(fEPSILON));
    return computations;
}
