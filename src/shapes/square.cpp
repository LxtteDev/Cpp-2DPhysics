#include "square.h"

Square::Square(sf::Vector2f position, sf::Vector2f size, sf::Color colour): Shape(sf::VertexArray(sf::Quads, 4)) {
    this->vertices[0] = position;
    this->vertices[1] = position + sf::Vector2f(size.x, 0.0f);
    this->vertices[2] = position + size;
    this->vertices[3] = position + sf::Vector2f(0.0f, size.y);

    this->vertices[0].color = colour;
    this->vertices[1].color = colour;
    this->vertices[2].color = colour;
    this->vertices[3].color = colour;
};

void Square::update(Window& window) {
    Shape::update(window);
}