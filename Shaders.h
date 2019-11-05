#ifndef _TINY_PIYO_GEOMETRY_H
#define _TINY_PIYO_GEOMETRY_H

#include "IGLSLShader.h"
#include "Types.h"
#include "Mesh.h"

#include <vector>

class BasicGeoShader : public IGLSLShader
{
    public:
        void Init();
        void Destroy();
        
        void End();

        void Render();

        void DrawTri(Vertex3D a, Vertex3D b, Vertex3D c);
        void DrawQuad(Vertex3D a, Vertex3D b, Vertex3D c, Vertex3D d);
        void DrawMesh(const Mesh& mesh);

    private:
        unsigned int _vaoID;
        unsigned int _vboID; 
        unsigned int _iboID;

        int _numIndices;
        std::vector<Vertex3D> _vertices;
        std::vector<unsigned int> _indices;
};

#endif
