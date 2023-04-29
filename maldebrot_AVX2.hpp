#ifndef MALDEBROT_AVX2
#define MALDEBROT_AVX2

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <immintrin.h>

#include <SFML/Graphics.hpp>

#include "maldebrot.hpp"

void set_maldebrot_avx2 (sf::Uint8* pixels, float scale, int cx, int cy, int rMax);

#endif //MALDEBROT_AVX2