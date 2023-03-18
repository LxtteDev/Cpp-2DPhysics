#include <iostream>
#include "shapes/square.h"

int main(int, char**) {
    Window window(sf::VideoMode(1280, 720), "2D Physics engine");

    Square shape(sf::Vector2f(10.0f, 10.0f), sf::Vector2f(100.0f, 50.0f), 0);

    while(window.open) {
        window.events();
        window.clear();

        shape.update(window);

        window.render();
    }

    window.close();
}
