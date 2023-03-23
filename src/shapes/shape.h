#include "../window/window.h"

#ifndef SHAPE_H_
#define SHAPE_H_

class Shape {
    public:
        Shape(sf::VertexArray vertices);

        virtual void update(Window& window);
        sf::FloatRect getBoundingBox();

        sf::VertexArray vertices;
        float rotation = 0.0f;

    private:
        float lastRotation = 0.0f;
};

#endif
