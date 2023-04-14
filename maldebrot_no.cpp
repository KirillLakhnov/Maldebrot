#include "maldebrot_no.hpp"

inline void add_ps (float a[8], float b[8], float c[8]) {for (int i = 0; i < 8; i++) {a[i] = b[i] + c[i];}}
inline void sub_ps (float a[8], float b[8], float c[8]) {for (int i = 0; i < 8; i++) {a[i] = b[i] - c[i];}}
inline void mul_ps (float a[8], float b[8], float c[8]) {for (int i = 0; i < 8; i++) {a[i] = b[i] * c[i];}}

inline void set1_ps (float arr[8], float num) {for (int i = 0; i < 8; i++) {arr[i] = num;}}
inline void set_ps (float arr[8], float num0, float num1, float num2, float num3,
                                  float num4, float num5, float num6, float num7) {arr[0] = num0; arr[1] = num1; arr[2] = num2; arr[3] = num3;
                                                                                   arr[4] = num4; arr[5] = num5; arr[6] = num6; arr[7] = num7;}

void set_maldebrot_no_o (sf::Uint8* pixels, float scale, int cx, int cy, int rMax)
{
    const float RMAX = float(rMax*rMax);

    for (int dy = 0; dy < 720; dy++)
    {
        float y0 = (dy - cy)*scale;
        float x0 =    (- cx)*scale;

        for (int dx = 0; dx < 1280; dx++, x0 += scale)
        {
            int index = 0;

            float x = x0;
            float y = y0;

            while (index < NMax)
            {
                float x2 = x*x;
                float y2 = y*y;
                float xy = x*y;

                float r = x2 + y2;

                if (r > (RMAX)) 
                {
                    break;
                }

                x = x2 - y2 + x0;
                y = 2*xy + y0;

                index++;
            }
            set_pixel (pixels, dx, dy, index);
        }
    }
}

void set_maldebrot_array (sf::Uint8* pixels, float scale, int cx, int cy, int rMax)
{
    const float RMAX = float(rMax*rMax);

    for (int dy = 0; dy < 720; dy++)
    {
        float y0 = (dy - cy) * scale;
        float x0 = (   - cx) * scale;

        for (int dx = 0; dx < 1280; dx += 8, x0 += 8 * scale)
        {
            float X0[8] = {x0, x0 + scale, x0 + 2 * scale, x0 + 3 * scale, x0 + 4 * scale, x0 + 5 * scale, x0 + 6 * scale, x0 + 7 * scale};
            float Y0[8] = {y0, y0, y0, y0, y0, y0, y0, y0};

            int   N[8] = {0, 0, 0, 0, 0, 0, 0, 0};
            int cmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};

            float X[8] = {X0[0], X0[1], X0[2], X0[3], X0[4], X0[5], X0[6], X0[7]};
            float Y[8] = {Y0[0], Y0[1], Y0[2], Y0[3], Y0[4], Y0[5], Y0[6], Y0[7]};

            float X2[8] = {};
            float Y2[8] = {};
            float XY[8] = {};
            float  R[8] = {};

            int mask = 1;

            while (mask > 0)
            {
                mask = 0;

                mul_ps (X2, X, X);
                mul_ps (Y2, Y, Y);
                mul_ps (XY, X, Y);
                add_ps (R, X2, Y2);

                sub_ps (X, X2, Y2); 
                add_ps (X, X, X0);

                add_ps (Y, XY, XY);
                add_ps (Y, Y, Y0);

                for (int i = 0; i < 8; i++) {cmp[i] = (((R[i] <= RMAX) && (N[i] <= NMax)) ? 1 : 0);}

                for (int i = 0; i < 8; i++) N[i] += cmp[i];
                for (int i = 0; i < 8; i++) mask += cmp[i];
            }

            for (int i = 0; i < 8; ++i)
            {
                set_pixel(pixels, dx + i, dy, N[i]);
            }
        }
    }
}
