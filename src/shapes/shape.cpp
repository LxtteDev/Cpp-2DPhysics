#include "shape.h"

Shape::Shape(sf::VertexArray vertices): vertices(vertices) {};

void Shape::updateVerts() {
    if (this->rotation != this->lastRotation) {
        sf::FloatRect bounding = this->getBoundingBox(true);

        sf::Transform rotate;
        rotate.rotate(this->rotation - this->lastRotation, sf::Vector2f(bounding.left, bounding.top) + sf::Vector2f(bounding.width / 2, bounding.height / 2));

        for (unsigned int i = 0; i < this->vertices.getVertexCount(); i++) {
            this->vertices[i].position = rotate.transformPoint(this->vertices[i].position);
        }

        this->lastRotation = this->rotation;
    }
}

void Shape::update(Window& window) {
    Shape::updateVerts();

    window.draw(this->vertices);
}

sf::Vector2f Shape::intersects(Shape* shape) { // m -> body
    // return doesIntersect(this->vertices, shape->vertices);
    return gilbertIntersection(this->vertices, shape->vertices);
}

void Shape::setColour(sf::Color colour) {
    for (unsigned int i = 0; i < this->vertices.getVertexCount(); i++)
        this->vertices[i].color = colour;
}

sf::FloatRect Shape::getBoundingBox(bool selfCalled) {
    if (!selfCalled) Shape::updateVerts();

    sf::Vector2f a = this->vertices[0].position;
    sf::Vector2f b = this->vertices[0].position;

    for (unsigned int i = 0; i < this->vertices.getVertexCount(); i++) {
        sf::Vector2f position = this->vertices[i].position;

        a = sf::Vector2f(std::min(a.x, position.x), std::min(a.y, position.y));
        b = sf::Vector2f(std::max(b.x, position.x), std::max(b.y, position.y));
    }

    return sf::FloatRect(a, b - a);
}

