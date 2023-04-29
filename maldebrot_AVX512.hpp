#ifndef MALDEBROT_AVX512
#define MALDEBROT_AVX512

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <immintrin.h>

#include <SFML/Graphics.hpp>

#include "maldebrot.hpp"

void set_maldebrot_avx512 (sf::Uint8* pixels, float scale, int cx, int cy, int rMax);

#endif //MALDEBROT_AVX512