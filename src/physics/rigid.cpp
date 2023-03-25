#include "rigid.h"

const float gravity = 50.0f;
const float threshold = 1.0f;

bool inBounding(sf::FloatRect boundingA, sf::FloatRect boundingB) {
    if (((boundingA.left > boundingB.left && boundingA.left < boundingB.left + boundingB.width) ||
             (boundingA.left + boundingA.width > boundingB.left && boundingA.left + boundingA.width < boundingB.left + boundingB.width)) &&
            ((boundingA.top > boundingB.top && boundingA.top < boundingB.top + boundingB.height) || 
             (boundingA.top + boundingA.height > boundingB.top && boundingA.top + boundingA.height < boundingB.top + boundingB.height))
    ) return true;
    return false;
}

RigidBody::RigidBody(Shape& shape): StaticBody(shape) {};

void RigidBody::update(Window& window, std::vector<StaticBody*>& objects) {
    this->velocity += (this->acceleration + sf::Vector2f(0.0f, gravity)) * window.deltaTime;

    // Shape
    sf::FloatRect bounding = this->mShape.getBoundingBox();
    sf::VertexArray& vertices = this->mShape.vertices;

    // Normals
    std::vector<sf::Vector2f> normals(vertices.getVertexCount());

    for (unsigned int i = 0; i < vertices.getVertexCount(); i++) {
        sf::Vector2f current = vertices[i].position;
        sf::Vector2f next = vertices[(i + 1) % vertices.getVertexCount()].position;

        sf::Vector2f direction = next - current;
        sf::Vector2f normal(direction.y, -direction.x);

        normals[i] = VectorNormalize(normal);
    }

    this->colliding = false;
    for (StaticBody* body : objects) {
        if (body == this) continue;

        sf::FloatRect mBounding = body->getBoundingBox();

        // Check in bounding box
        if (inBounding(bounding, mBounding)) {
            this->colliding = true;

            // Shape
            sf::VertexArray& mVertices = body->getVertices();

            // Projections
            std::vector<sf::Vector2f> mNormals(mVertices.getVertexCount());

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
                    this->colliding = false;
                    break;
                }
            }

            // Handle collision
            if (this->colliding) {
                this->acceleration = sf::Vector2f(0.0f, 0.0f);
                this->velocity = sf::Vector2f(0.0f, 0.0f);
            }
        }
    }

    this->position += this->velocity * window.deltaTime;
    StaticBody::update(window, objects);
}
