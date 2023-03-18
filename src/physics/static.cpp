#include "static.h"

StaticBody::StaticBody(Shape& shape): mShape(shape) {};

void StaticBody::update(Window& window) {
    this->mShape.update(window);
}
