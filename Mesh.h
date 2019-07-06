#ifndef _TINY_PIYO_MODEL_H
#define _TINY_PIYO_MODEL_H

#include "Types.h"

#include <string>
#include <vector>

struct Mesh
{
    Mesh() {}
    Mesh(const std::vector<Vertex3D>& Vertices, const std::vector<unsigned int>& Indices) :
        vertices(Vertices), indices(Indices) {}

    std::vector<Vertex3D> vertices;
    std::vector<unsigned int> indices;
};

Mesh ParseOBJ(const std::string& filepath);

#endif