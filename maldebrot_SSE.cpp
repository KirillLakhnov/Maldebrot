#include "maldebrot_SSE.hpp"

void set_maldebrot_sse (sf::Uint8* pixels, float scale, int cx, int cy, int rMax)
{
    assert (pixels);

    const __m128  RMAX = _mm_set1_ps (float(rMax*rMax));
    const __m128i NMAX = _mm_set1_epi32 (NMax);

    for (int dy = 0; dy < 720; dy++)
    {
        float y0 = (dy - cy) * scale;
        float x0 = (   - cx) * scale;

        for (int dx = 0; dx < 1280; dx += VECT_SIZE_SSE, x0 += VECT_SIZE_SSE * scale)
        {
            __m128 X0 = _mm_set_ps (x0 + 3 * scale, x0 + 2 * scale, x0 + scale, x0);
            __m128 Y0 = _mm_set1_ps (y0);

            __m128 X = X0;
            __m128 Y = Y0;

            __m128i     N = _mm_setzero_si128 ();
            __m128    cmp = _mm_setzero_ps ();
            __m128     X2 = _mm_setzero_ps ();
            __m128     Y2 = _mm_setzero_ps ();
            __m128     XY = _mm_setzero_ps ();
            __m128      R = _mm_setzero_ps ();

            int mask = 1;

            while (mask > 0)
            {
                mask = 0;

                X2 = _mm_mul_ps (X, X);
                Y2 = _mm_mul_ps (Y, Y);
                XY = _mm_mul_ps (X, Y);
                R  = _mm_add_ps (X2, Y2);

                X = _mm_add_ps (_mm_sub_ps (X2, Y2), X0);
                Y = _mm_add_ps (_mm_add_ps (XY, XY), Y0);

                cmp = _mm_cmpge_ps (RMAX, R);
                cmp = _mm_and_ps (cmp, _mm_castsi128_ps (_mm_cmpgt_epi32 (NMAX, N)));

                N = _mm_sub_epi32 (N, _mm_castps_si128(cmp));
                mask = _mm_movemask_ps(cmp);
            }

            for (int i = 0; i < VECT_SIZE_SSE; i++)
            {
                int* N_int = (int*)(&N);
                set_pixel(pixels, dx + i, dy, N_int[i]);
            }
        }
    }
}