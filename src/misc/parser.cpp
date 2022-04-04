#include "include/misc/parser.h"
#include "include/textile/material.h"
#include <QDebug>

Parser::Parser() { }

QVector<Body*> Parser::parse_file(QString sFilePath, Material *mat) {
    this->mat = mat;
    QString sFile = Parser::LoadFile(sFilePath.toStdString().c_str());
    QList<QString> lines = sFile.split("\n");
    lines.removeAt(lines.length() - 1);
    int nRemoved = 0;
    for (int i=lines.length() - 1; i>=0; i--) {
        if (lines[i].left(2) != "v " && lines[i].left(2) != "f " && lines[i].left(3) != "vn ") {
            lines.removeAt(i);
            nRemoved++;
        }
    }
//    qDebug() << nRemoved << "lines truncated by parser";
    QVector<Vector*> vertices = { nullptr }; // null makes it 1 based
    for (int i=0; i<lines.length(); i++) {
        if (lines[i].left(2) == "v ") {
            QList<QString> coords = lines[i].split(" ");
            vertices.push_back(new Vector(coords[1].toFloat(), coords[2].toFloat(), coords[3].toFloat(), 1.0));
        }
    }
    QVector<Vector*> normals = { nullptr };
    for (int i=0; i<lines.length(); i++) {
        if (lines[i].left(3) == "vn ") {
            QList<QString> coords = lines[i].split(" ");
            normals.push_back(new Vector(coords[1].toFloat(), coords[2].toFloat(), coords[3].toFloat(), 1.0));
        }
    }
    QVector<Body*> group;
    for (int i=0; i<lines.length(); i++) {
        if (lines[i].left(2) == "f ") {
            if (!lines[i].contains("/")) {
                QList<QString> indices = lines[i].split(" ");
                if (indices.size() != 4) { // polygon
                    QVector<Triangle *> triangles = this->fan_triangulation(vertices, indices);
                    for (int x=0; x<triangles.length(); x++) {
                        group.push_back(triangles[x]);
                    }
                }
                else {
                    Triangle *triangle = new Triangle(mat, vertices[indices[1].toInt()], vertices[indices[2].toInt()], vertices[indices[3].toInt()]);
                    group.push_back(triangle);
                }
            }
            else {
                QList<QString> split_line = lines[i].split(" ");
                QList<QString> v_indices = {};
                QList<QString> n_indices = {};
                if ('/' == split_line[1][2]) { // "x//x" case
                    for (int j=1; j<split_line.length(); j++) {
                        QList<QString> pair = split_line[j].split("//");
                        v_indices.push_back(pair[0]);
                        n_indices.push_back(pair[1]);
                    }
                }
                else { // "x/x/x" case
                    for (int j=1; j<split_line.length(); j++) {
                        QList<QString> pair = split_line[j].split("/");
                        v_indices.push_back(pair[0]);
                        n_indices.push_back(pair[2]);
                    }
                }
                SmoothTriangle *triangle = new SmoothTriangle(
                    mat,
                    vertices[v_indices[0].toInt()], vertices[v_indices[1].toInt()], vertices[v_indices[2].toInt()],
                    normals[n_indices[0].toInt()], normals[n_indices[1].toInt()], normals[n_indices[2].toInt()]
                );
                group.push_back(triangle);
            }
        }
    }
    return group;
}

QVector<Triangle *> Parser::fan_triangulation(QVector<Vector*> vertices, QList<QString> indices) {
    QVector<Triangle *> triangles = {};
    for (int i=2; i<vertices.length() - 1; i++) {
        Triangle *t = new Triangle(this->mat, vertices[indices[1].toInt()], vertices[indices[i].toInt()], vertices[indices[i + 1].toInt()]);
        triangles.push_back(t);
    }
    return triangles;
}

QVector<SmoothTriangle *> Parser::fan_smooth_triangulation(QVector<Vector *> vertices, QVector<Vector *> normals, QList<QString> v_indices, QList<QString> n_indices) { // dont think ill need this
    QVector<SmoothTriangle *> triangles = {};
    for (int i=2; i<vertices.length() - 1; i++) {
        SmoothTriangle *t = new SmoothTriangle(
                this->mat,
                vertices[v_indices[1].toInt()], vertices[v_indices[i].toInt()], vertices[v_indices[i + 1].toInt()],
                normals[n_indices[1].toInt()], normals[n_indices[i].toInt()], normals[n_indices[i + 1].toInt()]
        );
        triangles.push_back(t);
    }
    return triangles;
}

char* Parser::LoadFile(const char *source) {
    char* buffer = 0;
    long length = 0;
    FILE* s = fopen(source, "r");
    if (s) {
        fseek (s, 0, SEEK_END);
        length = ftell(s);
        fseek (s, 0, SEEK_SET);
        buffer = (char*) malloc(length);
        buffer[length-1] = '\0';
        if (buffer)
            fread (buffer, 1, length, s);
        fclose (s);
    }
    return buffer;
}
