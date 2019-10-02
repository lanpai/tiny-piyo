#include "Mesh.h"

#include <fstream>
#include <sstream>
#include <cstdio>
#include <algorithm>

Mesh ParseOBJ(const std::string& filepath)
{
    // Defining temporary vectors
    std::vector<float3> vertices;
    std::vector<float2> uvs;
    std::vector<float3> normals;
    std::vector<unsigned int> indices;

    // Defining output vectors
    std::vector<Vertex3D> meshVertices;
    std::vector<unsigned int> meshIndices;

    // Initializing input file stream
    std::ifstream stream(filepath.c_str());
    if (!stream)
        std::printf("Failed to open OBJ file \"%s\"\n", filepath.c_str());

    // Parsing each line from file stream
    std::string line;
    while (getline(stream, line))
    {
        // Replacing / with whitespace to parse f
        std::replace(line.begin(), line.end(), '/', ' ');

        // Using a string stream to read between whitespace
        std::stringstream ss(line);
        std::string head;
        ss >> head;

        if (head == "v")
        {
            // Parsing if line is a vertex definition
            float a = 0.0f;
            float b = 0.0f;
            float c = 0.0f;
            if (!(ss >> a) || !(ss >> b) || !(ss >> c))
                std::printf("Failed to parse line in OBJ file:\n  %s\n", line.c_str());
            vertices.push_back(float3(a, b, c));
        }
        else if (head == "vt")
        {
            // Parsing if line is a UV definition
            float a = 0.0f;
            float b = 0.0f;
            if (!(ss >> a) || !(ss >> b))
                std::printf("Failed to parse line in OBJ file:\n  %s\n", line.c_str());
            uvs.push_back(float2(a, b));
        }
        else if (head == "vn")
        {
            // Parsing if line is a normal definition
            float a = 0.0f;
            float b = 0.0f;
            float c = 0.0f;
            if (!(ss >> a) || !(ss >> b) || !(ss >> c))
                std::printf("Failed to parse line in OBJ file:\n  %s\n", line.c_str());
            normals.push_back(float3(a, b, c));
        }
        else if (head == "f")
        {
            // Parsing if line is a face definition
            for (int i = 0; i < 3; i++)
            {
                int v = 0;
                int vt = 0;
                int vn = 0;
                if (!(ss >> v) || !(ss >> vt) || !(ss >> vn))
                    std::printf("Failed to parse line in OBJ file:\n  %s\n", line.c_str());
                meshVertices.push_back(
                    Vertex3D(
                        vertices[v - 1],
                        normals[vn - 1],
                        uvs[vn - 1],
                        ColorRGBA8(255, 255, 255, 255)
                    )
                );
                meshIndices.push_back(meshVertices.size() - 1);
            }
        }
    }

    return Mesh(meshVertices, meshIndices);
}
