#include <vector>
#include "../math/vector.h"
#include "../math/rect.h"

#ifndef INTERSECT_H_
#define INTERSECT_H_

// Functions
inline sf::Vector2f projectOnAxis(sf::VertexArray& a, sf::Vector2f& axis) { // Min, max
    float proj = VectorDot(a[0].position, axis);
    sf::Vector2f projection(proj, proj); // Min, max

    for (unsigned int i = 1; i < a.getVertexCount(); i++) {
        float proj = VectorDot(a[i].position, axis);

        projection.x = std::min(proj, projection.x);
        projection.y = std::max(proj, projection.y);
    }

    return projection; // Min, max
}

template <typename T>
float projectionOverlap(sf::Vector2<T> a, sf::Vector2<T> b) {
    if (a.y < b.x || b.y < a.x) {
        return 0;
    }

    return std::min(a.y, b.y) - std::max(a.x, b.x);
}

// Collisions
inline bool separatingAxis(sf::VertexArray& a, sf::VertexArray& b) { // Cheaper but less accurate
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

inline std::vector<sf::Vector2f> edgeClip(sf::VertexArray& a, sf::VertexArray& b) { // More expensive but gives position
    std::vector<sf::Vector2f> output;

    for (unsigned int i = 0; i < a.getVertexCount() - 1; i++) {
        sf::Vector2f aA = a[i].position;
        sf::Vector2f aB = a[i + 1].position;

        if (aA.x == aB.x && aA.y == aB.y) continue;

        float a1 = (aB.y - aA.y);
        float a2 = (aA.x - aB.x);
        float aLine = a1 * aA.x + a2 * aA.y;

        for (unsigned int j = 0; j < b.getVertexCount() - 1; j++) {
            sf::Vector2f bA = b[j].position;
            sf::Vector2f bB = b[j + 1].position;

            if (bA.x == bB.x && bA.y == bB.y) continue;

            float b1 = (bB.y - bA.y);
            float b2 = (bA.x - bB.x);
            float bLine = b1 * bA.x + b2 * bA.y;

            float determinant = a1 * b2 - b1 * a2;

            if (determinant != 0) {
                float x = (b2 * aLine - a2 * bLine) / determinant;
                float y = (a1 * bLine - b1 * aLine) / determinant;

                output.push_back(sf::Vector2f(x, y));
            }
        }
    }

    return output;
};

inline sf::Vector2f gilbertIntersection(sf::VertexArray& a, sf::VertexArray& b) {
    float minOverlap = std::numeric_limits<float>::infinity();
    sf::Vector2f smallestOverlapAxis;

    for (unsigned int i = 0; i < a.getVertexCount(); i++) {
        sf::Vector2f normal = VectorNormal(a[i].position, a[(i + 1) % a.getVertexCount()].position);

        sf::Vector2f projectionA = projectOnAxis(a, normal);
        sf::Vector2f projectionB = projectOnAxis(b, normal);

        float overlap = projectionOverlap(projectionA, projectionB);

        if (overlap == 0)
            return sf::Vector2f();
        else if (overlap < minOverlap) {
            minOverlap = overlap;
            smallestOverlapAxis = normal;
        }
    }

    for (unsigned int i = 0; i < b.getVertexCount(); i++) {
        sf::Vector2f normal = VectorNormal(b[i].position, b[(i + 1) % b.getVertexCount()].position);

        sf::Vector2f projectionA = projectOnAxis(a, normal);
        sf::Vector2f projectionB = projectOnAxis(b, normal);

        float overlap = projectionOverlap(projectionA, projectionB);

        if (overlap == 0)
            return sf::Vector2f();
        else if (overlap < minOverlap) {
            minOverlap = overlap;
            smallestOverlapAxis = normal;
        }
    }

    return smallestOverlapAxis * minOverlap;
}   

#pragma once

#endif
