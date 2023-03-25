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

    sf::FloatRect bounding = this->mShape.getBoundingBox();

    this->colliding = false;
    for (StaticBody* body : objects) {
        if (body == this) continue;

        sf::FloatRect mBounding = body->getBoundingBox();

        // Check in bounding box
        if (inBounding(bounding, mBounding)) {
            this->colliding = body->checkCollides(this);

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
