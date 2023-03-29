#include <vector>
#include "../math/vector.h"
#include "../math/rect.h"

#ifndef INTERSECT_H_
#define INTERSECT_H_

inline bool doesIntersect(sf::VertexArray& a, sf::VertexArray& b) {
    // Projections
    std::vector<sf::Vector2f> aNormals(a.getVertexCount());
    std::vector<sf::Vector2f> bNormals(b.getVertexCount());

    for (unsigned int i = 0; i < a.getVertexCount(); i++) {
        sf::Vector2f current = a[i].position;
        sf::Vector2f next = a[(i + 1) % a.getVertexCount()].position;

        sf::Vector2f direction = next - current;
        sf::Vector2f normal(direction.y, -direction.x);

        aNormals[i] = VectorNormalize(normal);
    }

    for (unsigned int i = 0; i < b.getVertexCount(); i++) {
        sf::Vector2f current = b[i].position;
        sf::Vector2f next = b[(i + 1) % b.getVertexCount()].position;

        sf::Vector2f direction = next - current;
        sf::Vector2f normal(direction.y, -direction.x);

        bNormals[i] = VectorNormalize(normal);
    }

    // Check collisions
    for (unsigned int i = 0; i < aNormals.size() + bNormals.size(); i++) {
        sf::Vector2f normal = (i >= aNormals.size() ? bNormals : aNormals)[i % aNormals.size()];

        float aMin = FLT_MAX, aMax = FLT_MIN, bMin = FLT_MAX, bMax = FLT_MIN;

        for (unsigned int j = 0; j < a.getVertexCount(); j++) {
            float projection = VectorDot(a[j].position, normal);

            aMin = std::min(aMin, projection);
            aMax = std::max(aMax, projection);
        }

        for (unsigned int j = 0; j < b.getVertexCount(); j++) {
            float projection = VectorDot(b[j].position, normal);

            bMin = std::min(bMin, projection);
            bMax = std::max(bMax, projection);
        }

        if(aMax < bMin || bMax < aMin) {
            return false;
        }
    }

    return true;
};

template <typename T>
std::vector<sf::Vector2<T>> edgeClip(sf::VertexArray& a, sf::VertexArray& b) {
    
};

#pragma once

#endif
