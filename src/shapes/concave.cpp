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

bool Concave::intersects(Shape* shape) {
    // Shape
    sf::VertexArray& vertices = this->vertices;
    // sf::VertexArray& mVertices = shape->vertices;
    sf::FloatRect mBounding = shape->getBoundingBox();
    // std::cout << "(" << mBounding.left << ", " << mBounding.top << "), (" << mBounding.width << ", " << mBounding.height << ")" << std::endl;

    for (unsigned int i = 0; i < vertices.getVertexCount(); i += 3) {
        sf::Vector2f A = vertices[i].position;
        sf::Vector2f B = vertices[(i + 1) % vertices.getVertexCount()].position;
        sf::Vector2f C = vertices[(i + 2) % vertices.getVertexCount()].position;

        sf::FloatRect bounding = triangleBounding(A, B, C);
        // std::cout << "(" << bounding.left << ", " << bounding.top << "), (" << bounding.width << ", " << bounding.height << ")" << std::endl;

        if (inBounding(bounding, mBounding)) {
            std::cout << "true" << std::endl;
            return true;
        }
    }

    return false;

    /* // Projections
    std::vector<sf::Vector2f> normals(triangles.size());
    std::vector<sf::Vector2f> mNormals(mVertices.getVertexCount());

    for (unsigned int i = 0; i < triangles.size(); i++) {
        sf::Vector2f current = vertices[i].position;
        sf::Vector2f next = vertices[(i + 1) % vertices.getVertexCount()].position;

        sf::Vector2f direction = next - current;
        sf::Vector2f normal(direction.y, -direction.x);

        normals[i] = VectorNormalize(normal);
    }

    for (unsigned int i = 0; i < mVertices.getVertexCount(); i++) {
        sf::Vector2f current = mVertices[i].position;
        sf::Vector2f next = mVertices[(i + 1) % mVertices.getVertexCount()].position;

        sf::Vector2f direction = next - current;
        sf::Vector2f normal(direction.y, -direction.x);

        mNormals[i] = VectorNormalize(normal);
    }

    // Check collisions
    for (unsigned int i = 0; i < normals.size() + mNormals.size(); i++) {
        sf::Vector2f normal = (i >= normals.size() ? mNormals : normals)[i % normals.size()];

        float aMin = FLT_MAX, aMax = FLT_MIN, bMin = FLT_MAX, bMax = FLT_MIN;

        for (unsigned int j = 0; j < vertices.getVertexCount(); j++) {
            float projection = VectorDot(vertices[j].position, normal);

            aMin = std::min(aMin, projection);
            aMax = std::max(aMax, projection);
        }

        for (unsigned int j = 0; j < mVertices.getVertexCount(); j++) {
            float projection = VectorDot(mVertices[j].position, normal);

            bMin = std::min(bMin, projection);
            bMax = std::max(bMax, projection);
        }

        if(aMax < bMin || bMax < aMin) {
            return false;
        }
    }

    return true; */
}
