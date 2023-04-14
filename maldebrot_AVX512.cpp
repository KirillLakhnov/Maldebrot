#include "maldebrot_AVX2.hpp"

void set_maldebrot_avx512 (sf::Uint8* pixels, float scale, int cx, int cy, int rMax)
{
    const __m512  RMAX = _mm512_set1_ps (float(rMax*rMax));
    const __m512i NMAX = _mm512_set1_epi32 (NMax);

    for (int dy = 0; dy < 720; dy++)
    {
        float y0 = (dy - cy) * scale;
        float x0 = (   - cx) * scale;

        for (int dx = 0; dx < 1280; dx += VECT_SIZE_AVX512, x0 += VECT_SIZE_AVX512 * scale)
        {
            __m512 X0 = _mm512_set_ps (x0,  x0 + scale, x0 +  2 * scale, x0 +  3 * scale, 
                                       x0 +  4 * scale, x0 +  5 * scale, x0 +  6 * scale, 
                                       x0 +  7 * scale, x0 +  8 * scale, x0 +  9 * scale,
                                       x0 + 10 * scale, x0 + 11 * scale, x0 + 12 * scale,
                                       x0 + 13 * scale, x0 + 14 * scale, x0 + 15 * scale);
            __m512 Y0 = _mm512_set1_ps (y0);

            __m512 X = X0;
            __m512 Y = Y0;

            __m512i  N = _mm512_setzero_si512 ();
            __m512  X2 = _mm512_setzero_ps ();
            __m512  Y2 = _mm512_setzero_ps ();
            __m512  XY = _mm512_setzero_ps ();
            __m512   R = _mm512_setzero_ps ();

            __mmask16 cmp = 1;

            int index = 0;

            while ((cmp > 0) && (index <= NMax))
            {
                X2 = _mm512_mul_ps (X, X);
                Y2 = _mm512_mul_ps (Y, Y);
                XY = _mm512_mul_ps (X, Y);
                R  = _mm512_add_ps (X2, Y2);

                X = _mm512_add_ps (_mm512_sub_ps (X2, Y2), X0);
                Y = _mm512_add_ps (_mm512_add_ps (XY, XY), Y0);

                cmp = _mm512_cmp_ps_mask (RMAX, R, _CMP_GT_OQ);
                N = _mm512_add_epi32 (N, _mm512_mask_blend_epi32(cmp, _mm512_setzero_epi32(), _mm512_set1_epi32(1)));
                
                index++;
            }

            for (int i = 0; i < VECT_SIZE_AVX512; i++)
            {
                int* N_int = (int*)(&N);
                set_pixel(pixels, dx + i, dy, N_int[i]);
            }
        }
    }
}