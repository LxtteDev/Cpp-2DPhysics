#include "square.h"

Square::Square(sf::Vector2f position, sf::Vector2f size, float rotation): Shape(sf::VertexArray(sf::Quads, 4)), position(position), size(size), rotation(rotation) {};

void Square::update(Window& window) {
    sf::Vector2f previousPosition = this->mVertices[0].position;
    sf::Vector2f previousSize = this->mVertices[2].position - previousPosition;

    if (previousPosition != this->position || previousSize != this->size) {
        this->mVertices[0] = sf::Vector2f(this->position.x, this->position.y);
        this->mVertices[1] = sf::Vector2f(this->position.x + this->size.x, this->position.y);
        this->mVertices[2] = sf::Vector2f(this->position.x + this->size.x, this->position.y + this->size.y);
        this->mVertices[3] = sf::Vector2f(this->position.x, this->position.y + this->size.y);
    }

    Shape::update(window);
}