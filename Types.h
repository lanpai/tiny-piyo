#ifndef _TINY_PIYO_MATH_H
#define _TINY_PIYO_MATH_H

struct float3
{
    float3() :
        x(0), y(0), z(0) {}
    float3(float X, float Y, float Z) :
        x(X), y(Y), z(Z) {}

    float x;
    float y;
    float z;
};

struct float2
{
    float2() :
        x(0), y(0) {}
    float2(float X, float Y) :
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

struct Vertex3D
{
    Vertex3D() :
        position(float3()), color(ColorRGBA8()) {}
    Vertex3D(const float3& Position, const ColorRGBA8& Color) :
        position(Position), color(Color) {}

    float3 position;
    ColorRGBA8 color;
};

struct SampVertex3D
{
    SampVertex3D() :
        position(float3()), color(ColorRGBA8()), uv(float2()) {}
    SampVertex3D(const float3& Position, const ColorRGBA8& Color, const float2& UV) :
        position(Position), color(Color), uv(UV) {}

    float3 position;
    ColorRGBA8 color;
    float2 uv;
};

#endif