#ifndef CANVAS_H
#define CANVAS_H

#include <QVector>
#include <iostream>
#include <fstream>

#include "include/math/vector.h"

class Canvas {
public:
    Canvas(int nWidth, int nHeight);
    Vector *get_pixel(int x, int y);
    void write_ppm();
    int nWidth, nHeight;
    QVector<QVector<Vector*>> aPixels = {};
    void write_pixel(int x, int y, Vector *color, float nSamples);
};

#endif // CANVAS_H
