#include "shape.h"

Shape::Shape(sf::VertexArray vertices): vertices(vertices) {};

void Shape::update(Window& window) {
    window.draw(this->vertices);
}

