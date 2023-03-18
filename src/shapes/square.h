#include "shape.h"

#ifndef SQUARE_H_
#define SQUARE_H_

class Square : public Shape {
    public:
        Square(sf::Vector2f position, sf::Vector2f size, float rotation);

        void update(Window& window) override;

        sf::Vector2f position;
        sf::Vector2f size;
        float rotation;
};

#endif
