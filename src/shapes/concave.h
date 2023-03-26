#include <iostream>
#include <vector>
#include "shape.h"
#include "../math/vector.h"

#ifndef CONCAVE_H_
#define CONCAVE_H_

class Concave : public Shape {
    public:
        Concave(sf::VertexArray vertices);
};

#endif
