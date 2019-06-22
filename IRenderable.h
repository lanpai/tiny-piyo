#ifndef _I_RENDERABLE_H
#define _I_RENDERABLE_H

class GLSLProgram;

class IRenderable
{
    public:
        virtual void Draw(GLSLProgram program) = 0;
}

#endif
