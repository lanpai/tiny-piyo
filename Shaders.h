#ifndef _TINY_PIYO_GEOMETRY_H
#define _TINY_PIYO_GEOMETRY_H

#include "IGLSLShader.h"
#include "IRenderable.h"
#include "Types.h"

#include <vector>

ShaderProgramSource ParseShader(const std::string& filepath);
unsigned int CompileShader(unsigned int type, const std::string& source);
unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

class BasicGeoShader : public IGLSLShader
{
    public:
        void Init();
        void End();

        void Render();

        void DrawTri(GeoVertex3D a, GeoVertex3D b, GeoVertex3D c);

    private:
        unsigned int _vaoID;
        unsigned int _vboID; 
        unsigned int _iboID;

        int _numIndices;
        std::vector<GeoVertex3D> _vertices;
        std::vector<unsigned int> _indices;
};

#endif