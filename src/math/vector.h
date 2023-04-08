#include <SFML/Graphics.hpp>

#ifndef VECTOR_H_
#define VECTOR_H_

template <typename T>
sf::Vector2<T> operator /(const sf::Vector2<T>& left, const sf::Vector2<T>& right)
{
    T X = left.x / right.x;
    T Y = left.y / right.y;
    return sf::Vector2<T>(X,Y);
}

template <typename T>
sf::Vector2<T> operator *(const sf::Vector2<T>& left, const sf::Vector2<T>& right)
{
    T X = left.x * right.x;
    T Y = left.y * right.y;
    return sf::Vector2<T>(X,Y);
}

template <typename T>
float VectorDot(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    return a.x * b.x + a.y * b.y;
}

template <typename T>
sf::Vector2<T> VectorNormalize(const sf::Vector2<T>& a) {
    return a / std::sqrt(a.x * a.x + a.y * a.y);
}

template <typename T>
sf::Vector2<T> VectorAbs(const sf::Vector2<T>& a) {
    return sf::Vector<T>(std::abs(a.x), std::abs(a.y));
}

template <typename T>
sf::Vector2<T> VectorNormal(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    sf::Vector2f direction = b - a;
    sf::Vector2f normal(direction.y, -direction.x);

    return VectorNormalize(normal);
}

#endif
