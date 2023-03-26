#include <iostream>
#include <vector>
#include "shape.h"
#include "../math/vector.h"
#include "../math/rect.h"

#ifndef CONCAVE_H_
#define CONCAVE_H_

struct Triangle {
    sf::Vector2f a, b, c;
};

class Concave : public Shape {
    public:
        Concave(sf::VertexArray vertices);

        bool intersects(Shape* shape) override;
};

#endif
