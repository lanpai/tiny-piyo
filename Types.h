#ifndef _TINY_PIYO_MATH_H
#define _TINY_PIYO_MATH_H

struct Vertex3D
{
    Vertex3D() :
        x(0), y(0), z(0) {}
    Vertex3D(float X, float Y, float Z) :
        x(X), y(Y), z(Z) {}
    float x;
    float y;
    float z;
};

struct Vertex2D
{
    Vertex2D() :
        x(0), y(0) {}
    Vertex2D(float X, float Y) :
        x(X), y(Y) {}

    float x;
    float y;
};

struct ColorRGBA8
{
    ColorRGBA8() :
        r(0), g(0), b(0), a(0) {}
    ColorRGBA8(unsigned char R, unsigned char G, unsigned char B, unsigned char A) :
        r(R), g(G), b(B), a(A) {}

    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

struct GeoVertex3D
{
    GeoVertex3D() :
        position(Vertex3D()), color(ColorRGBA8()) {}
    GeoVertex3D(const Vertex3D& Position, const ColorRGBA8& Color) :
        position(Position), color(Color) {}

    Vertex3D position;
    ColorRGBA8 color;
};

struct SampVertex3D
{
    SampVertex3D() :
        position(Vertex3D()), color(ColorRGBA8()), uv(Vertex2D()) {}
    SampVertex3D(const Vertex3D& Position, const ColorRGBA8& Color, const Vertex2D& UV) :
        position(Position), color(Color), uv(UV) {}

    Vertex3D position;
    ColorRGBA8 color;
    Vertex2D uv;
};

#endif