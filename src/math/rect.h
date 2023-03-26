#include <SFML/Graphics.hpp>

#ifndef RECT_H_
#define RECT_H_

template <typename T>
bool inBounding(sf::Rect<T> a, sf::Rect<T> b) {
    if (((a.left > b.left && a.left < b.left + b.width) ||
         (a.left + a.width > b.left && a.left + a.width < b.left + b.width)) &&
        ((a.top > b.top && a.top < b.top + b.height) || 
         (a.top + a.height > b.top && a.top + a.height < b.top + b.height)) ||
        ((b.left > b.left && b.left < a.left + a.width) ||
         (b.left + b.width > a.left && b.left + b.width < a.left + a.width)) &&
        ((b.top > a.top && b.top < a.top + a.height) || 
         (b.top + b.height > a.top && b.top + b.height < a.top + a.height))
    ) return true;
    return false;
}

#endif
