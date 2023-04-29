#include "maldebrot.hpp"

void maldebrot (void (*set_maldebrot) (sf::Uint8*, float, int, int, int))
{
    FPS fps;
    char fps_buffer[10];

    sf::Texture screen;
    screen.create (1280, 720);

    sf::Sprite sprite (screen);
    sf::Uint8* pixels = (sf::Uint8*) calloc (1280*720*4, sizeof (sf::Uint8));

    float scale = 0.004;
    int x = 760;
    int y = 360;

#ifndef NO_DRAW_MODE
    sf::RenderWindow window (sf::VideoMode(1280, 720), "Maldebrot");

    sf::Font font;
    font.loadFromFile ("sfml_files/SrbijaSans.otf");

    sf::Text text_fps;
    text_fps.setFont (font);
    text_fps.setPosition (25, 25);
    text_fps.setCharacterSize (40);
    text_fps.setColor (sf::Color (20, 250, 20));
    text_fps.setStyle (sf::Text::Bold);

    while (window.isOpen())
    {
        sf::Event event = {};

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    break;
                }
                case (sf::Event::KeyPressed):
                {
                    switch (event.key.code)
                    {
                        case (sf::Keyboard::Z):
                        {
                            scale *= 0.75;
                            break;
                        }
                        case (sf::Keyboard::X):
                        {
                            scale *= 1.25;
                            break;
                        }
                        case (sf::Keyboard::Up):
                        {
                            y += 100;
                            break;
                        }
                        case (sf::Keyboard::Down):
                        {
                            y -= 100;
                            break;
                        }
                        case (sf::Keyboard::Right):
                        {
                            x += 100;
                            break;
                        }
                        case (sf::Keyboard::Left):
                        {
                            x -= 100;
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                }
            }
        }
#endif

#ifdef NO_DRAW_MODE
        float fps_average = 0;

        for (int i = 0; i < 100; i++)
        {
            fps.update ();
            set_maldebrot (pixels, scale, x, y, 100);

            fps_average += fps.getFPS();
        }

        fps_average = fps_average/100.;

        printf ("%.2f", fps_average);
#endif

#ifndef NO_DRAW_MODE
        fps.update ();
        set_maldebrot (pixels, scale, x, y, 100);

        sprintf(fps_buffer, "%.2f", fps.getFPS());
        sf::String str(fps_buffer);
        text_fps.setString(str);

        screen.update (pixels);

        window.clear ();
        window.draw(sprite);
        window.draw(text_fps);
        window.display ();
    }
#endif
}

void set_pixel (sf::Uint8* pixels, int dx, int dy, int index)
{
    assert (pixels);

    pixels[(1280 * dy + dx) * 4 + 0] = 5 * tanh (index);
    pixels[(1280 * dy + dx) * 4 + 1] = sinh (index);
    pixels[(1280 * dy + dx) * 4 + 2] = 255 - sin (index) * 12 * cosh(index);
    pixels[(1280 * dy + dx) * 4 + 3] = 255 - exp (-(float)index / 255);
}
