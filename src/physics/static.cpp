#include "static.h"

StaticBody::StaticBody(Shape& shape): mShape(shape) {
    this->position = this->mShape.vertices[0].position;
    this->lastPosition = this->position;
};

void StaticBody::update(Window& window, std::vector<StaticBody*>& objects) {
    if (this->lastPosition != this->position) {
        sf::Vector2f offset = this->position - this->lastPosition;

        for (unsigned int i = 0; i < this->mShape.vertices.getVertexCount(); i++)
            this->mShape.vertices[i].position += offset;

        this->lastPosition = this->position;
    }

    this->mShape.update(window);
}
