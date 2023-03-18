#include "square.h"

Square::Square(sf::Vector2f position, sf::Vector2f size, float rotation): Shape(sf::VertexArray(sf::Quads, 4)), position(position), size(size), rotation(rotation) {};

void Square::update(Window& window) {
    sf::Vector2f previousPosition = this->mVertices[0].position + ( this->size * this->offset );
    sf::Vector2f previousSize = this->mVertices[2].position + ( this->size * this->offset ) - previousPosition;

    if (previousPosition != this->position || previousSize != this->size) {
        sf::Vector2f position = this->position - ( this->size * this->offset );

        this->mVertices[0] = sf::Vector2f(position.x, position.y);
        this->mVertices[1] = sf::Vector2f(position.x + this->size.x, position.y);
        this->mVertices[2] = sf::Vector2f(position.x + this->size.x, position.y + this->size.y);
        this->mVertices[3] = sf::Vector2f(position.x, position.y + this->size.y);
    }

    Shape::update(window);
}

void Square::setOrigin(sf::Vector2f origin) {
    this->offset = origin;
    sf::Vector2f position = this->position - ( this->size * origin );

    this->mVertices[0] = sf::Vector2f(position.x, position.y);
    this->mVertices[1] = sf::Vector2f(position.x + this->size.x, position.y);
    this->mVertices[2] = sf::Vector2f(position.x + this->size.x, position.y + this->size.y);
    this->mVertices[3] = sf::Vector2f(position.x, position.y + this->size.y);
}

void Square::setColour(sf::Color colour) {
    this->mVertices[0].color = colour;
    this->mVertices[1].color = colour;
    this->mVertices[2].color = colour;
    this->mVertices[3].color = colour;
}