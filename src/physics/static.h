#include <SFML/Graphics.hpp>
#include "../window/window.h"
#include "../shapes/shape.h"

#ifndef STATIC_H_
#define STATIC_H_

class StaticBody {
    public:
        StaticBody(Shape& shape);

        virtual void update(Window& window, std::vector<StaticBody*>& objects);
        sf::VertexArray& getVertices();
        sf::FloatRect getBoundingBox();

        sf::Vector2f position; // The first point

    protected:
        sf::Vector2f lastPosition;
        Shape& mShape;
};

#endif
