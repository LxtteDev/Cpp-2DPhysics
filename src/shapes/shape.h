#include "../collisions/intersect.h"
#include "../window/window.h"

#ifndef SHAPE_H_
#define SHAPE_H_

class Shape {
    public:
        Shape(sf::VertexArray vertices);

        virtual void update(Window& window);
        virtual sf::Vector2f intersects(Shape* shape);
        virtual void setColour(sf::Color colour);
        sf::FloatRect getBoundingBox(bool selfCalled = false);

        sf::VertexArray vertices;
        float rotation = 0.0f;

    private:
        void updateVerts();

        float lastRotation = 0.0f;
};

#endif
