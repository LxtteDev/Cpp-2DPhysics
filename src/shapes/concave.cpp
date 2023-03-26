#include "concave.h"

struct Triangle {
    sf::Vector2f a, b, c;
};

float getAngle(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) {
    sf::Vector2f ab = b - a;
    sf::Vector2f bc = c - b;

    float crossProduct = ab.x * bc.y - ab.y * bc.x;
    float dotProduct = ab.x * bc.x + ab.y * bc.y;

    float angle = std::atan2(crossProduct, dotProduct) * ( 180.0f / 3.14159f );

    if (angle < 0.0f) return 360.0f + angle;
    return angle;
}

Concave::Concave(sf::VertexArray vertices): Shape(vertices) {
    std::vector<Triangle> triangles;

    for (unsigned int i = 0; i < vertices.getVertexCount(); i++) {
        sf::Vector2f A = vertices[i].position;
        sf::Vector2f B = vertices[(i + 1) % vertices.getVertexCount()].position;
        sf::Vector2f C = vertices[(i + 2) % vertices.getVertexCount()].position;

        float angle = getAngle(A, B, C);

        if (angle < 180.0f) {
            triangles.push_back({ A, B, C });
        }

        // std::cout << i << " (" << current.x << ", " << current.y << ")" << std::endl;
        // std::cout << i << ", " << angle << " (" << (i + vertices.getVertexCount() - 1) % vertices.getVertexCount() << ", " << i << ", " << (i + 1) % vertices.getVertexCount() << ")" << std::endl;
        // std::cout << "(" << previous.x << ", " << previous.y << ") (" << current.x << ", " << current.y << ") (" << next.x << ", " << next.y << ")" << std::endl;
    }

    this->vertices = sf::VertexArray(sf::Triangles);

    for (unsigned int i = 0; i < triangles.size(); i++) {
        Triangle triangle = triangles[i];

        sf::Color colour(i * 10 + 10, i * 15 + 10, i * 20 + 10);

        this->vertices.append(triangle.a);
        this->vertices.append(triangle.b);
        this->vertices.append(triangle.c);

        this->vertices[i * 3].color = colour;
        this->vertices[i * 3 + 1].color = colour;
        this->vertices[i * 3 + 2].color = colour;
    }
}