#include "window.h"

Window::Window(sf::VideoMode videoMode, const char* name): window(videoMode, name) {};

void Window::close() {
    this->window.close();
}

void Window::clear() {
    this->window.clear();
}

void Window::render() {
    if (!open) return;

    sf::Time time = clock.restart();
    this->deltaTime = time.asSeconds();

    this->window.display();
}

void Window::events() {
    sf::Event event;

    while(this->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            open = false;
    }
}

void Window::draw(sf::Drawable& object) {
    this->window.draw(object);
}


