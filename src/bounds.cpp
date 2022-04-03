#include "include/bounds.h"

Bounds::Bounds(Vector *min, Vector *max) {
    this->min = min;
    this->max = max;
}

Bounds* Bounds::get_bounds(Body *body) {
    Q_UNUSED(body);
    return nullptr;
}
