#include <vector>
#include "../window/window.h"
#include "../shapes/shape.h"

#ifndef STATIC_H_
#define STATIC_H_

class StaticBody {
    public:
        StaticBody(Shape& shape);

        void update(Window& window);

        sf::Vector2f position; // The first point

    private:
        sf::Vector2f lastPosition;
        Shape& mShape;
};

#endif
