#include "maldebrot_AVX2.hpp"

void set_maldebrot_avx2 (sf::Uint8* pixels, float scale, int cx, int cy, int rMax)
{
    assert (pixels);
    
    const __m256  RMAX = _mm256_set1_ps (float(rMax*rMax));
    const __m256i NMAX = _mm256_set1_epi32 (NMax);

    for (int dy = 0; dy < 720; dy++)
    {
        float y0 = (dy - cy) * scale;
        float x0 = (   - cx) * scale;

        for (int dx = 0; dx < 1280; dx += VECT_SIZE_AVX2, x0 += VECT_SIZE_AVX2 * scale)
        {
            __m256 X0 = _mm256_set_ps (x0 + 7 * scale, x0 + 6 * scale, x0 + 5 * scale, x0 + 4 * scale, x0 + 3 * scale, x0 + 2 * scale, x0 + scale, x0);
            __m256 Y0 = _mm256_set1_ps (y0);

            __m256 X = X0;
            __m256 Y = Y0;

            __m256i  N = _mm256_setzero_si256 ();
            __m256 cmp = _mm256_setzero_ps ();
            __m256  X2 = _mm256_setzero_ps ();
            __m256  Y2 = _mm256_setzero_ps ();
            __m256  XY = _mm256_setzero_ps ();
            __m256   R = _mm256_setzero_ps ();

            int mask = 1;

            while (mask > 0)
            {
                mask = 0;

                X2 = _mm256_mul_ps (X, X);
                Y2 = _mm256_mul_ps (Y, Y);
                XY = _mm256_mul_ps (X, Y);
                R  = _mm256_add_ps (X2, Y2);

                X = _mm256_add_ps (_mm256_sub_ps (X2, Y2), X0);
                Y = _mm256_add_ps (_mm256_add_ps (XY, XY), Y0);

                cmp = _mm256_cmp_ps (RMAX, R, _CMP_GT_OQ);
                cmp = _mm256_and_ps (cmp, _mm256_castsi256_ps (_mm256_cmpgt_epi32 (NMAX, N)));

                N = _mm256_sub_epi32 (N, _mm256_castps_si256(cmp));
                mask = _mm256_movemask_ps (cmp);
            } 

#ifdef NO_DRAW_MODE
                volatile __m256i NR = N; 
#endif

#ifndef NO_DRAW_MODE
            for (int i = 0; i < VECT_SIZE_AVX2; i++)
            {
                int* N_int = (int*)(&N);
                set_pixel(pixels, dx + i, dy, N_int[i]);
            }
#endif
        }
    }
}