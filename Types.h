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

struct ColorHSVA8
{
    ColorHSVA8() :
        h(0), s(0), v(0), a(0) {}
    ColorHSVA8(int H, float S, float V, float A) :
        h(H), s(S), v(V), a(A) {}

    int h;
    float s;
    float v;
    float a;
};

struct ColorRGBA8
{
    ColorRGBA8() :
        r(0), g(0), b(0), a(0) {}
    ColorRGBA8(unsigned char R, unsigned char G, unsigned char B, unsigned char A) :
        r(R), g(G), b(B), a(A) {}

    const ColorHSVA8 ConvertToHSVA8()
    {
        float Rprime = (float)r / 255;
        float Gprime = (float)g / 255;
        float Bprime = (float)b / 255;

        float A = (float)a / 255;

        float Cmax = std::fmax(std::fmax(Rprime, Gprime), Bprime);
        float Cmin = std::fmin(std::fmin(Rprime, Gprime), Bprime);

        float delta = Cmax - Cmin;

        int H;
        if (delta == 0)
            H = 0;
        else if (Cmax == Rprime)
            H = 60 * std::fmod(((Gprime - Bprime) / delta), 6);
        else if (Cmax == Gprime)
            H = 60 * (((Bprime - Rprime) / delta) + 2);
        else if (Cmax == Bprime)
            H = 60 * (((Rprime - Gprime) / delta) + 4);
        if (H < 0)
            H = 360 + H;

        float S;
        if (Cmax == 0)
            S = 0;
        else
            S = delta / Cmax;

        float V = Cmax;

        return ColorHSVA8(H, S, V, A);
    }

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