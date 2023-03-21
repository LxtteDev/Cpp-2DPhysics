#include "shape.h"

#ifndef BOUNDING_H_
#define BOUNDING_H_

class BoundingBox : public Shape {
    public:
        BoundingBox(sf::FloatRect rect, sf::Color colour = sf::Color::White);

        void update(Window& window) override;
};

#endif
