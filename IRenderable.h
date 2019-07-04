#ifndef _TINY_PIYO_I_RENDERABLE_H
#define _TINY_PIYO_I_RENDERABLE_H

class GLSLProgram;

class IRenderable
{
    public:
        virtual void Draw() = 0;
};

#endif
