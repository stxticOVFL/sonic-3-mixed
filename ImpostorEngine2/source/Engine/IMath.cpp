#if INTERFACE
#include <Utils/Standard.h>

class IMath {
public:
    static int32_t Cos[256];
    static int32_t Sin[256];
    static int32_t Atan[258];

    static char Str[258];
};
#endif

#include <Engine/IMath.h>

int32_t IMath::Cos[256];
int32_t IMath::Sin[256];
int32_t IMath::Atan[258];
char IMath::Str[258];

PUBLIC STATIC void IMath::Init() {
    for (int i = 0; i < 256; i++) {
        Cos[i] = (int32_t)(cos(i * M_PI / 128.0) * 0xFFFF);
        Sin[i] = (int32_t)(-sin(i * M_PI / 128.0) * 0xFFFF);
        Atan[i] = (int32_t)(atan2(i * 1.0, 256.0) * 0x80 / M_PI + 0x100) & 0xFF;
    }
    for (int i = 256; i < 258; i++) {
        Atan[i] = (int32_t)(atan2(i * 1.0, 256.0) * 0x80 / M_PI + 0x100) & 0xFF;
    }
}

PUBLIC STATIC float IMath::pythag(int a, int b) {
	return sqrt(pow(a, 2) + pow(b, 2));
}

PUBLIC STATIC float IMath::pydistance(int a, int b, int a2, int b2) {
	return abs(sqrt(pow(a, 2) + pow(b, 2)) - sqrt(pow(a2, 2) + pow(b2, 2)));
}

PUBLIC STATIC int32_t IMath::cosHex(int n) {
    return Cos[n & 0xFF];
}
PUBLIC STATIC int32_t IMath::sinHex(int n) {
    return Sin[n & 0xFF];
}
PUBLIC STATIC int32_t IMath::atanHex(int x, int y) {
    if (x == 0 && y == 0) return 0x0;

    y = -y;

    int val;
    int ax = abs(x);
    int ay = abs(y);

    if (ay < ax) {
        ay = (ay << 8) / ax;
        val = Atan[ay & 0xFF];
    }
    else if (ay > ax) {
        ax = (ax << 8) / ay;
        val = 0x40 - Atan[ax & 0xFF];
    }
    else {
        val = 0x20;
    }

    if (x < 0)
        val = -val + 0x80;
    if (y < 0)
        val = -val + 0x100;

    return val & 0xFF;
}

PUBLIC STATIC int IMath::abs(int n) {
    if (n < 0)
        return -n;
    return n;
}

PUBLIC STATIC int IMath::max(int a, int b) {
    return a > b ? a : b;
}

PUBLIC STATIC int IMath::min(int a, int b) {
    return a < b ? a : b;
}

PUBLIC STATIC int IMath::clamp(int v, int a, int b) {
    return IMath::max(a, IMath::min(v, b));
}

PUBLIC STATIC double IMath::clampDouble(double v, double a, double b) {
    return fmax(a, fmin(v, b));
}

PUBLIC STATIC double IMath::clampDoubleDown(double v, double a, double b) {
    return fmax(a, fmin(v, b)) - a;
}

PUBLIC STATIC float IMath::sign(float a) {
    if (a < 0)
        return -1.0;
    if (a > 0)
        return 1.0;
    return 0.0;
}

PUBLIC STATIC int IMath::sign(int a) {
    if (a < 0)
        return -1;
    if (a > 0)
        return 1;
    return 0;
}

PUBLIC STATIC int IMath::floor(double a) {
    return std::floor(a);
}

PUBLIC STATIC int IMath::floor(float a) {
    return std::floor(a);
}

PUBLIC STATIC int IMath::ceil(double a) {
    return std::ceil(a);
}

PUBLIC STATIC int IMath::ceil(float a) {
    return std::ceil(a);
}

PUBLIC STATIC int IMath::wrapDeg(int d) {
    while (d < 0)
        d += 360;
    while (d >= 360)
        d -= 360;
    return d;
}

PUBLIC STATIC int IMath::randRange(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

PUBLIC STATIC char* IMath::toString(int a) {
    sprintf(IMath::Str, "%d", a);
    return IMath::Str;
}