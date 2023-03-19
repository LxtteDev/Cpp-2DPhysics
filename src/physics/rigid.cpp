#include "rigid.h"

/*

    Line intercept (https://www.desmos.com/calculator/dlx46f79fe by Me)

    X = [ s1(x) + o1 = s2(x) + o2 ] (s -> slope, o -> y-intercept)
    X = [ ( o2 - o1 ) / ( s1 - s2 ) ]

    Y = [ (y - o1) / s1 = (y - o2) / s2 ] (s -> slope, o -> y-intercept)
    Y = [ ( o1s2 - s1o2 ) / ( s2 - s1 ) ]

*/

RigidBody::RigidBody(Shape& shape): StaticBody(shape) {};

void RigidBody::update(Window& window, std::vector<StaticBody*>& objects) {
    // Update position
    this->velocity += (this->acceleration + sf::Vector2f(0.0f, 10.0f)) * window.deltaTime;
    this->position += this->velocity * window.deltaTime;

    StaticBody::update(window, objects);
}
