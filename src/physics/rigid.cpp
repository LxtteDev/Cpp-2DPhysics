#include "rigid.h"

const float gravity = 50.0f;
const float threshold = 1.0f;

RigidBody::RigidBody(Shape* shape): StaticBody(shape) {};

void RigidBody::update(Window& window, std::vector<StaticBody*>& objects) {
    this->velocity += (this->acceleration + sf::Vector2f(0.0f, gravity)) * window.deltaTime;

    sf::FloatRect bounding = this->mShape->getBoundingBox();

    this->colliding = false;
    for (StaticBody* body : objects) {
        if (body == this) continue;

        sf::FloatRect mBounding = body->getBoundingBox();

        // Check in bounding box
        if (inBounding(bounding, mBounding)) {
            // this->colliding = body->checkCollides(this);
            this->colliding = body->intersects(this->mShape);

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
