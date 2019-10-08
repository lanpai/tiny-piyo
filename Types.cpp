#include "Types.h"

const ColorRGBA8 ColorHSVA8::ConvertToRGBA8()
{
    unsigned char A = a * 255;

    float C = v * s;
    float X = C * (1.0 - std::abs(std::fmod((h / 60.0), 2.0) - 1.0));
    float m = v - C;

    if (0 <= h && h < 60) {
        return ColorRGBA8(
                (C + m) * 255,
                (X + m) * 255,
                m * 255,
                A);
    }
    else if (60 <= h && h < 120) {
        return ColorRGBA8(
                (X + m) * 255,
                (C + m) * 255,
                m * 255,
                A);
    }
    else if (120 <= h && h < 180) {
        return ColorRGBA8(
                m * 255,
                (C + m) * 255,
                (X + m) * 255,
                A);
    }
    else if (180 <= h && h < 240) {
        return ColorRGBA8(
                m * 255,
                (X + m) * 255,
                (C + m) * 255,
                A);
    }
    else if (240 <= h && h < 300) {
        return ColorRGBA8(
                (X + m) * 255,
                m * 255,
                (C + m) * 255,
                A);
    }
    else {
        return ColorRGBA8(
                (C + m) * 255,
                m * 255,
                (X + m) * 255,
                A);
    }

}

const ColorHSVA8 ColorRGBA8::ConvertToHSVA8()
{
    float Rprime = (float)r / 255;
    float Gprime = (float)g / 255;
    float Bprime = (float)b / 255;

    float A = (float)a / 255;

    float Cmax = std::fmax(std::fmax(Rprime, Gprime), Bprime);
    float Cmin = std::fmin(std::fmin(Rprime, Gprime), Bprime);

    float delta = Cmax - Cmin;

    int H = 0;
    if (delta != 0) {
        if (Cmax == Rprime)
            H = 60 * std::fmod(((Gprime - Bprime) / delta), 6);
        else if (Cmax == Gprime)
            H = 60 * (((Bprime - Rprime) / delta) + 2);
        else if (Cmax == Bprime)
            H = 60 * (((Rprime - Gprime) / delta) + 4);
    }
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
