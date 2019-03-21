#ifndef IMATH_H
#define IMATH_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER


#include <Utils/Standard.h>

class IMath {
public:
    static int32_t Cos[256];
    static int32_t Sin[256];
    static int32_t Atan[258];
    static char Str[258];

    static void Init();
    static float pythag(int a, int b);
    static float pydistance(int a, int b, int a2, int b2);
    static int32_t cosHex(int n);
    static int32_t sinHex(int n);
    static int32_t atanHex(int x, int y);
    static int abs(int n);
    static int max(int a, int b);
    static int min(int a, int b);
    static int clamp(int v, int a, int b);
    static double clampDouble(double v, double a, double b);
    static double clampDoubleDown(double v, double a, double b);
    static float sign(float a);
    static int sign(int a);
    static int floor(double a);
    static int floor(float a);
    static int ceil(double a);
    static int ceil(float a);
    static int wrapDeg(int d);
    static int randRange(int min, int max);
    static char* toString(int a);
};

#endif /* IMATH_H */
