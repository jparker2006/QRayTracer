#include "include/parser.h"
#include "include/material.h"
#include <QDebug>

Parser::Parser() { }

Group* Parser::parse_file(QString sFilePath) {
    QString sFile = Parser::LoadFile(sFilePath.toStdString().c_str());
    QList<QString> lines = sFile.split("\n");
    lines.removeAt(lines.length() - 1);
    int nRemoved = 0;
    for (int i=lines.length() - 1; i>=0; i--) {
        if (lines[i].left(2) != "v " && lines[i].left(2) != "f ") {
            lines.removeAt(i);
            nRemoved++;
        }
    }
    qDebug() << nRemoved << "lines truncated by parser";
    QVector<Vector*> vertices = { nullptr }; // null makes it 1 based
    for (int i=0; i<lines.length(); i++) {
        if (lines[i].left(2) == "v ") {
            QList<QString> coords = lines[i].split(" ");
            vertices.push_back(new Vector(coords[1].toFloat(), coords[2].toFloat(), coords[3].toFloat(), 1.0));
        }
    }
    Material *mat = new Material(new Vector(1, 0, 0, 0), 1, 1, 1, 1);
    Group *group = new Group(mat);
    for (int i=0; i<lines.length(); i++) {
        if (lines[i].left(2) == "f ") {
            QList<QString> indices = lines[i].split(" ");
            if (indices.size() != 4) { // polygon
                QVector<Triangle *> triangles = this->fan_triangulation(vertices, indices);
                for (int x=0; x<triangles.length(); x++) {
                    group->push(triangles[x]);
                }
            }
            else {
                Triangle *triangle = new Triangle(mat, vertices[indices[1].toInt()], vertices[indices[2].toInt()], vertices[indices[3].toInt()]);
                group->push(triangle);
            }
        }
    }
    qDebug() << "file loaded";
    return group;
}

QVector<Triangle *> Parser::fan_triangulation(QVector<Vector*> vertices, QList<QString> indices) {
    QVector<Triangle *> triangles = {};
    Material *mat = new Material(new Vector(1, 0, 0, 0), 1, 1, 1, 1);
    for (int i=2; i<vertices.length() - 1; i++) {
        Triangle *t = new Triangle(mat, vertices[indices[1].toInt()], vertices[indices[i].toInt()], vertices[indices[i + 1].toInt()]);
        triangles.push_back(t);
    }
    return triangles;
}

char* Parser::LoadFile(const char *source) {
    char* buffer = 0;
    long length = 0;
    FILE* s = fopen (source, "r");
    if (s) {
        fseek (s, 0, SEEK_END);
        length = ftell (s);
        fseek (s, 0, SEEK_SET);
        buffer = (char*) malloc (length);
        buffer[length-1] = '\0';
        if (buffer) {
            fread (buffer, 1, length, s);
        }
        fclose (s);
    }
    return buffer;
}
