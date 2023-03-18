#include <iostream>
#include "shape.h"
#include "../math/vector.h"

#ifndef SQUARE_H_
#define SQUARE_H_

class Square : public Shape {
    public:
        Square(sf::Vector2f position, sf::Vector2f size, float rotation);

        void update(Window& window) override;
        void setOrigin(sf::Vector2f origin);
        void setColour(sf::Color colour);

        sf::Vector2f position;
        sf::Vector2f size;
        float rotation;

    private:
        sf::Vector2f offset;
};

#endif
