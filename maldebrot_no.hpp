#ifndef MALDEBROT_NO
#define MALDEBROT_NO

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SFML/Graphics.hpp>

#include "maldebrot.hpp"

void set_maldebrot_no_o (sf::Uint8* pixels, float scale, int cx, int cy, int rMax);

void set_maldebrot_array (sf::Uint8* pixels, float scale, int cx, int cy, int rMax);

#endif //MALDEBROT_NO