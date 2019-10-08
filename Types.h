#ifndef _TINY_PIYO_MATH_H
#define _TINY_PIYO_MATH_H

#include <cmath>

struct float3
{
    float3() :
        x(0), y(0), z(0) {}
    float3(float X, float Y, float Z) :
        x(X), y(Y), z(Z) {}

    inline float3 operator + (const float3 &b) const
        { return float3(x + b.x, y + b.y, z + b.z); }

    inline float3 operator - (const float3 &b) const
        { return float3(x - b.x, y - b.y, z - b.z); }

    inline float3 operator * (const float3 &b) const
        { return float3(x * b.x, y * b.y, z * b.z); }

    inline float3 operator / (const float3 &b) const
        { return float3(x / b.x, y / b.y, z / b.z); }

    inline float3 operator + (const float &b) const
        { return float3(x + b, y + b, z + b); }

    inline float3 operator - (const float &b) const
        { return float3(x - b, y - b, z - b); }

    inline float3 operator * (const float &b) const
        { return float3(x * b, y * b, z * b); }

    inline float3 operator / (const float &b) const
        { return float3(x / b, y / b, z / b); }

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

    inline float2 operator + (const float2 &b) const
        { return float2(x + b.x, y + b.y); }

    inline float2 operator - (const float2 &b) const
        { return float2(x - b.x, y - b.y); }

    inline float2 operator * (const float2 &b) const
        { return float2(x * b.x, y * b.y); }

    inline float2 operator / (const float2 &b) const
        { return float2(x / b.x, y / b.y); }

    inline float2 operator + (const float &b) const
        { return float2(x + b, y + b); }

    inline float2 operator - (const float &b) const
        { return float2(x - b, y - b); }

    inline float2 operator * (const float &b) const
        { return float2(x * b, y * b); }

    inline float2 operator / (const float &b) const
        { return float2(x / b, y / b); }

    float x;
    float y;
};

struct ColorRGBA8;
struct ColorHSVA8
{
    ColorHSVA8() :
        h(0), s(0), v(0), a(0) {}
    ColorHSVA8(int H, float S, float V, float A) :
        h(H), s(S), v(V), a(A) {}

    const ColorRGBA8 ConvertToRGBA8();

    int h;
    float s;
    float v;
    float a;
};

#define ColorRGBA8_WHITE    ColorRGBA8(255, 255, 255, 255)
#define ColorRGBA8_BLACK    ColorRGBA8(  0,   0,   0, 255)
#define ColorRGBA8_RED      ColorRGBA8(255,   0,   0, 255)
#define ColorRGBA8_GREEN    ColorRGBA8(  0, 255,   0, 255)
#define ColorRGBA8_BLUE     ColorRGBA8(  0,   0, 255, 255)

struct ColorRGBA8
{
    ColorRGBA8() :
        r(0), g(0), b(0), a(0) {}
    ColorRGBA8(unsigned char R, unsigned char G, unsigned char B, unsigned char A) :
        r(R), g(G), b(B), a(A) {}

    const ColorHSVA8 ConvertToHSVA8();

    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

struct Vertex3D
{
    Vertex3D(
        const float3& Position = float3(),
        const ColorRGBA8& Color = ColorRGBA8(),
        const float3& Normal = float3(),
        const float2& UV = float2()
    ) :
        position(Position), color(Color), normal(Normal), uv(UV) {}
    Vertex3D(
        const float3& Position = float3(),
        const float3& Normal = float3(),
        const float2& UV = float2(),
        const ColorRGBA8& Color = ColorRGBA8()
    ) :
        position(Position), color(Color), normal(Normal), uv(UV) {}

    float3 position;
    ColorRGBA8 color;
    float3 normal;
    float2 uv;
};

#endif
