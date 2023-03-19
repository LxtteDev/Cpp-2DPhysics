#include "../window/window.h"

#ifndef SHAPE_H_
#define SHAPE_H_

class Shape {
    public:
        Shape(sf::VertexArray vertices);

        virtual void update(Window& window);

        sf::VertexArray vertices;
};

#endif
