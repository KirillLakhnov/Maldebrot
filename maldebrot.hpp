#ifndef MALDEBROT
#define MALDEBROT

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <SFML/Graphics.hpp>

const int NMax = 1000;
const int VECT_SIZE_SSE    = 4;
const int VECT_SIZE_AVX2   = 8;
const int VECT_SIZE_AVX512 = 16;

class FPS
{
    private:
        sf::Clock clock_; 
        unsigned int frame_;
        float fps_;

    public:
        FPS() : frame_(0), fps_(0) {}
       ~FPS() {frame_ = 0; fps_ = 0;}

        float getFPS() const {return fps_;}

        void update()
        {
            if (clock_.getElapsedTime().asSeconds() >= 1.f)
            {
                fps_   = frame_ / clock_.getElapsedTime().asSeconds();
                frame_ = 0;

                clock_.restart();                
            }

            ++frame_;
        }
};

void maldebrot (void (*set_maldebrot) (sf::Uint8*, float, int, int, int));

void set_pixel (sf::Uint8* pixels, int dx, int dy, int index);

#endif // MALDEBROT