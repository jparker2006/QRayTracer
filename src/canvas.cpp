#include "include/canvas.h"

Canvas::Canvas(int nWidth, int nHeight) {
    this->nWidth = nWidth;
    this->nHeight = nHeight;
    for (int i=0; i<nWidth; i++) {
        QVector<Vector*> curr_vec = {};
        for (int j=0; j<nHeight; j++) {
            curr_vec.push_back(new Vector(0.0, 0.0, 0.0, 0.0));
        }
        this->aPixels.push_back(curr_vec);
    }
}

void Canvas::write_pixel(int x, int y, Vector *color) {
    this->aPixels[x][y] = color;
}

Vector* Canvas::get_pixel(int x, int y) {
    return this->aPixels[x][y];
}

void Canvas::write_ppm() {
    QString sFile = "";
    sFile += "P3\n" + QString::number(this->nWidth) + " " + QString::number(this->nHeight) + "\n255\n"; // heading
    for (int i=0; i<this->nHeight; i++) {
        for (int j=0; j<this->nWidth; j++) {
            sFile += QString::number(qRound(this->aPixels[j][i]->fx * 255.0)) + " ";
            sFile += QString::number(qRound(this->aPixels[j][i]->fy * 255.0)) + " ";
            sFile += QString::number(qRound(this->aPixels[j][i]->fz * 255.0)) + " ";
        }
        sFile += "\n";
    }
    std::ofstream f_ppm;
    f_ppm.open("image.ppm");
    f_ppm << sFile.toStdString();
    f_ppm.close();
}
