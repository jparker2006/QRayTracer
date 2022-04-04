#ifndef CAMERA_H
#define CAMERA_H

#include "include/math/matrix.h"
#include "include/ray/ray.h"

class Camera {
public:
    Camera(float fhsize, float fvsize, float fov, Matrix *transformation);
    float pixel_size();
    Ray *ray_for_pixel(float fx, float fy);
    float fhsize, fvsize, fov, half_width, half_height, fpixel_size;
    Matrix *transformation;
};

#endif // CAMERA_H
