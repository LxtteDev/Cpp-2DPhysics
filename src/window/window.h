#include <SFML/Graphics.hpp>

#ifndef WINDOW_H_
#define WINDOW_H_

class Window {
    public:
        Window(sf::VideoMode videoMode, const char* name);

        void close();
        void clear();
        void render();
        void events();
        void draw(sf::Drawable& object);

        bool open = true;
        float deltaTime = 0.0f;

    private:
        sf::RenderWindow window;
        sf::Clock clock;
};

#endif
