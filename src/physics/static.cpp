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

bool StaticBody::checkCollides(StaticBody* body) { // m -> body
    // Shape
    sf::VertexArray& vertices = this->mShape.vertices;
    sf::VertexArray& mVertices = body->getVertices();

    // Projections
    std::vector<sf::Vector2f> normals(vertices.getVertexCount());
    std::vector<sf::Vector2f> mNormals(mVertices.getVertexCount());

    for (unsigned int i = 0; i < vertices.getVertexCount(); i++) {
        sf::Vector2f current = vertices[i].position;
        sf::Vector2f next = vertices[(i + 1) % vertices.getVertexCount()].position;

        sf::Vector2f direction = next - current;
        sf::Vector2f normal(direction.y, -direction.x);

        normals[i] = VectorNormalize(normal);
    }

    for (unsigned int i = 0; i < mVertices.getVertexCount(); i++) {
        sf::Vector2f current = mVertices[i].position;
        sf::Vector2f next = mVertices[(i + 1) % mVertices.getVertexCount()].position;

        sf::Vector2f direction = next - current;
        sf::Vector2f normal(direction.y, -direction.x);

        mNormals[i] = VectorNormalize(normal);
    }

    // Check collisions
    for (unsigned int i = 0; i < normals.size() + mNormals.size(); i++) {
        sf::Vector2f normal = (i >= normals.size() ? mNormals : normals)[i % normals.size()];

        float aMin = FLT_MAX, aMax = FLT_MIN, bMin = FLT_MAX, bMax = FLT_MIN;

        for (unsigned int j = 0; j < vertices.getVertexCount(); j++) {
            float projection = VectorDot(vertices[j].position, normal);

            aMin = std::min(aMin, projection);
            aMax = std::max(aMax, projection);
        }

        for (unsigned int j = 0; j < mVertices.getVertexCount(); j++) {
            float projection = VectorDot(mVertices[j].position, normal);

            bMin = std::min(bMin, projection);
            bMax = std::max(bMax, projection);
        }

        if(aMax < bMin || bMax < aMin) {
            return false;
        }
    }

    return true;
}

sf::VertexArray& StaticBody::getVertices() {
    return this->mShape.vertices;
}

sf::FloatRect StaticBody::getBoundingBox() {
    return this->mShape.getBoundingBox();
}

float StaticBody::getRotation() {
    return this->mShape.rotation;
}
