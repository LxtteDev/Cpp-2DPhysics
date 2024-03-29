#include "rigid.h"

const float gravity = 50.0f;
const float threshold = 1.0f;

RigidBody::RigidBody(Shape* shape): StaticBody(shape) {};

void RigidBody::update(Window& window, std::vector<StaticBody*>& objects) {
    this->velocity += (this->acceleration + sf::Vector2f(0.0f, gravity)) * window.deltaTime;
    this->position += this->velocity * window.deltaTime;
    StaticBody::update(window, objects);

    sf::FloatRect bounding = this->mShape->getBoundingBox();

    this->colliding = false;
    for (StaticBody* body : objects) {
        if (body == this) continue;

        sf::FloatRect mBounding = body->getBoundingBox();

        // Check in bounding box
        if (inBounding(bounding, mBounding)) {
            // this->colliding = body->checkCollides(this);
            /* this->colliding = body->intersects(this->mShape);

            // Handle collision
            if (this->colliding) {
                std::vector<sf::Vector2f> positions = edgeClip(body->getVertices(), this->mShape->vertices);

                for (unsigned int i = 0; i < positions.size(); i++)
                    std::cout << i << ": " << positions[i].x << ", " << positions[i].y << std::endl;

                this->acceleration = sf::Vector2f(0.0f, 0.0f);
                this->velocity = sf::Vector2f(0.0f, 0.0f);
            } */

            sf::Vector2f offset = body->intersects(this->mShape);
            if (offset.x != 0 || offset.y != 0) {
                this->colliding = true;

                // offset += sf::Vector2f(std::sign(offset.x), std::sign(offset.y));
                this->position += offset;

                if (offset.x > 0)
                    this->velocity.x = std::max(0.0f, this->velocity.x);
                else if (offset.x < 0)
                    this->velocity.x = std::min(0.0f, this->velocity.x);

                if (offset.y > 0)
                    this->velocity.y = std::max(0.0f, this->velocity.y);
                else if (offset.y < 0)
                    this->velocity.y = std::min(0.0f, this->velocity.y);

                break;
            }
        }
    }
}
