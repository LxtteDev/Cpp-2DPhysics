#include <SFML/Graphics.hpp>
#include "../window/window.h"
#include "../shapes/shape.h"

#ifndef STATIC_H_
#define STATIC_H_

class StaticBody {
    public:
        StaticBody(Shape& shape);

        void update(Window& window);

    private:
        Shape& mShape;
};

#endif
