#ifndef MALDEBROT_SSE
#define MALDEBROT_SSE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <emmintrin.h>

#include <SFML/Graphics.hpp>

#include "maldebrot.hpp"

void set_maldebrot_sse (sf::Uint8* pixels, float scale, int cx, int cy, int rMax);

#endif //MALDEBROT_SSE