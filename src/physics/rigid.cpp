#include "rigid.h"

const float gravity = 50.0f;
const float threshold = 1.0f;

RigidBody::RigidBody(Shape& shape): StaticBody(shape) {};

void RigidBody::update(Window& window, std::vector<StaticBody*>& objects) {
    this->velocity += (this->acceleration + sf::Vector2f(0.0f, gravity)) * window.deltaTime;

    sf::FloatRect bounding = this->mShape.getBoundingBox();
    sf::VertexArray points = this->mShape.vertices;

    this->colliding = false;
    for (StaticBody* body : objects) {
        if (body == this) continue; // Ignore self
        sf::FloatRect mBounding = body->getBoundingBox();

        if (((bounding.left > mBounding.left && bounding.left < mBounding.left + mBounding.width) ||
             (bounding.left + bounding.width > mBounding.left && bounding.left + bounding.width < mBounding.left + mBounding.width)) &&
            ((bounding.top > mBounding.top && bounding.top < mBounding.top + mBounding.height) || 
             (bounding.top + bounding.height > mBounding.top && bounding.top + bounding.height < mBounding.top + mBounding.height))
        ) { // Inside bounding box
            sf::VertexArray mPoints = body->getVertices();

            for (unsigned int i = 0; i < mPoints.getVertexCount(); i++) {
                sf::Vector2f mPosA = mPoints[i].position;
                sf::Vector2f mPosB = mPoints[i + 1 >= mPoints.getVertexCount() ? 0 : i + 1].position;

                if (std::abs(mPosA.y - mPosB.y) <= threshold) { // Inside Y range (Same Y)
                    for (unsigned int j = 0; j < points.getVertexCount(); j++) {
                        sf::Vector2f posA = points[j].position;
                        sf::Vector2f posB = points[j + 1 >= points.getVertexCount() ? 0 : j + 1].position;

                        if (std::abs(posA.y - posB.y) <= threshold) { // Inside Y range (Same Y)
                            if (((posA.x > mPosA.x && posA.x < mPosB.x) || (posB.x > mPosA.x && posB.x < mPosB.x) ||
                                 (mPosA.x > posA.x && mPosA.x < posB.x) || (mPosB.x > posA.x && mPosB.x < posB.x)) &&
                                ((posA.y < mPosA.y + threshold && posA.y > mPosA.y - threshold)  ||
                                 (posA.y + threshold > mPosA.y && posA.y - threshold < mPosA.y))
                            ) { // Intersection
                                this->acceleration = sf::Vector2f(this->acceleration.x, std::min(this->acceleration.y, 0.0f));
                                this->velocity = sf::Vector2f(this->velocity.x, std::min(this->velocity.y, 0.0f));
                                this->position = sf::Vector2f(this->position.x, mPosA.y - ( posA.y - points[0].position.y ));

                                this->colliding = true;
                            }
                        }

                        if (this->colliding) break;
                    }
                }

                if (this->colliding) break;
            }
        }

        if (this->colliding) break;
    }

    this->position += this->velocity * window.deltaTime;
    StaticBody::update(window, objects);
}
