#include "bounding.h"

BoundingBox::BoundingBox(sf::FloatRect rect, sf::Color colour): Shape(sf::VertexArray(sf::PrimitiveType::LineStrip, 5)) {
    this->vertices[0] = sf::Vector2f(rect.left, rect.top);
    this->vertices[1] = sf::Vector2f(rect.left + rect.width, rect.top);
    this->vertices[2] = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
    this->vertices[3] = sf::Vector2f(rect.left, rect.top + rect.height);
    this->vertices[4] = sf::Vector2f(rect.left, rect.top);

    this->vertices[0].color = colour;
    this->vertices[1].color = colour;
    this->vertices[2].color = colour;
    this->vertices[3].color = colour;
    this->vertices[4].color = colour;
}

void BoundingBox::update(Window& window) {
    Shape::update(window);
}