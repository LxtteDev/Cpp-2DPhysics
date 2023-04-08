#include "concave.h"

float getAngle(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) {
    sf::Vector2f ab = b - a;
    sf::Vector2f bc = c - b;

    float crossProduct = ab.x * bc.y - ab.y * bc.x;
    float dotProduct = ab.x * bc.x + ab.y * bc.y;

    float angle = std::atan2(crossProduct, dotProduct) * ( 180.0f / 3.14159f );

    if (angle < 0.0f) return 360.0f + angle;
    return angle;
}

sf::FloatRect triangleBounding(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) {
    sf::Vector2f A(std::min(a.x, std::min(b.x, c.x)), std::min(a.y, std::min(b.y, c.y)));
    sf::Vector2f B(std::max(a.x, std::max(b.x, c.x)), std::max(a.y, std::max(b.y, c.y)));

    return sf::FloatRect(A, B - A);
}

Concave::Concave(sf::VertexArray vertices): Shape(vertices) {
    std::vector<sf::Vector2f> mVerts(vertices.getVertexCount());

    for (unsigned int i = 0; i < vertices.getVertexCount(); i++)
        mVerts[i] = vertices[i].position;

    std::vector<Triangle> triangles;
    bool looping = true;
    unsigned int i = 0;

    while(looping) {
        sf::Vector2f A = mVerts[i];
        sf::Vector2f B = mVerts[(i + 1) % mVerts.size()];
        sf::Vector2f C = mVerts[(i + 2) % mVerts.size()];

        float angle = getAngle(A, B, C);

        if (angle < 180.0f) {
            triangles.push_back({ A, B, C });
            mVerts.erase(mVerts.begin() + ((i + 1) % mVerts.size()));
            i = 0;
        } else {
            i++;
        }

        if (i + 1 >= mVerts.size() || mVerts.size() < 3)
            looping = false;
    }

    this->vertices = sf::VertexArray(sf::Triangles);

    for (unsigned int i = 0; i < triangles.size(); i++) {
        Triangle triangle = triangles[i];

        this->vertices.append(triangle.a);
        this->vertices.append(triangle.b);
        this->vertices.append(triangle.c);
    }
}

sf::Vector2f Concave::intersects(Shape* shape) {
    // Shape
    sf::FloatRect mBounding = shape->getBoundingBox();

    for (unsigned int i = 0; i < this->vertices.getVertexCount(); i += 3) {
        sf::Vector2f A = this->vertices[i].position;
        sf::Vector2f B = this->vertices[(i + 1) % this->vertices.getVertexCount()].position;
        sf::Vector2f C = this->vertices[(i + 2) % this->vertices.getVertexCount()].position;

        sf::FloatRect bounding = triangleBounding(A, B, C);

        if (inBounding(mBounding, bounding)) { // Inside triangle bounding box
            sf::VertexArray triangleVerts(sf::Points, 3);
            triangleVerts[0] = A;
            triangleVerts[1] = B;
            triangleVerts[2] = C;

            // return doesIntersect(this->vertices, triangleVerts);
            sf::Vector2f offset = gilbertIntersection(triangleVerts, shape->vertices);
            return offset;
        }
    }

    return sf::Vector2f();
}
