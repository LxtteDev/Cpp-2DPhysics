#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "static.h"
#include "../math/rect.h"

#ifndef RIGID_H_
#define RIGID_H_

class RigidBody : public StaticBody {
    public:
        RigidBody(Shape* shape);

        void update(Window& window, std::vector<StaticBody*>& objects) override;

        sf::Vector2f velocity;
        sf::Vector2f acceleration;
        bool colliding = false;
};

#endif
