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

bool Shape::intersects(Shape* shape) { // m -> body
    // Shape
    sf::VertexArray& vertices = this->vertices;
    sf::VertexArray& mVertices = shape->vertices;

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

