#include "collision.h"

Collision::Collision() {
}

void Collision::update(Window& window) {
    for (StaticBody* object : this->objects) {
        object->update(window);
    }
}

void Collision::addObject(StaticBody& object) {
    this->objects.push_back( &object );
}