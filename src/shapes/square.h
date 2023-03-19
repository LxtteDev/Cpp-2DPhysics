#include <iostream>
#include "shape.h"
#include "../math/vector.h"

#ifndef SQUARE_H_
#define SQUARE_H_

class Square : public Shape {
    public:
        Square(sf::Vector2f position, sf::Vector2f size, sf::Color colour = sf::Color::White);

        void update(Window& window) override;
};

#endif
