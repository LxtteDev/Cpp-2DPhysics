#include "shape.h"

Shape::Shape(sf::VertexArray vertices): mVertices(vertices) {};

void Shape::update(Window& window) {
    window.draw(this->mVertices);
}

