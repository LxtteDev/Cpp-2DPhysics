#include "rigid.h"

const float gravity = 10.0f;
const float threshold = 1.0f;

/*

    Line intercept (https://www.desmos.com/calculator/dlx46f79fe by Me)

    X = [ s1(x) + o1 = s2(x) + o2 ] (s -> slope, o -> y-intercept)
    X = [ ( o2 - o1 ) / ( s1 - s2 ) ]

    Y = [ (y - o1) / s1 = (y - o2) / s2 ] (s -> slope, o -> y-intercept)
    Y = [ ( o1s2 - s1o2 ) / ( s2 - s1 ) ]

*/

RigidBody::RigidBody(Shape& shape): StaticBody(shape) {};

void RigidBody::update(Window& window, std::vector<StaticBody*>& objects) {
    this->velocity += (this->acceleration + sf::Vector2f(0.0f, gravity)) * window.deltaTime;

    sf::FloatRect bounding = this->mShape.getBoundingBox();

    for (StaticBody* body : objects) {
        if (body == this) continue; // Ignore self
        sf::FloatRect mBounding = body->getBoundingBox();

        if (((bounding.left >= mBounding.left && bounding.left <= mBounding.left + mBounding.width) ||
             (bounding.left + bounding.width >= mBounding.left && bounding.left + bounding.width <= mBounding.left + mBounding.width)) &&
            ((bounding.top >= mBounding.top && bounding.top <= mBounding.top + mBounding.height) || 
             (bounding.top + bounding.height >= mBounding.top && bounding.top + bounding.height <= mBounding.top + mBounding.height))
        ) {
            // Inside bounding box
            // std::cout << "Inside bounding box" << std::endl;
            this->acceleration = sf::Vector2f(0.0f, 0.0f);
            this->velocity = sf::Vector2f(0.0f, 0.0f);
        }
    }

    this->position += this->velocity * window.deltaTime;
    StaticBody::update(window, objects);
}
