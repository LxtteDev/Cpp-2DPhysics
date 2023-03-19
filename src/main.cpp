#include <iostream>
#include "shapes/square.h"
#include "physics/collision.h"

int main(int, char**) {
    Window window(sf::VideoMode(1280, 720), "2D Physics engine");

    // Create floor
    sf::VertexArray floorVerts(sf::TriangleStrip, 8);
    floorVerts[1] = sf::Vector2f(0.0f, 570.0f);
    floorVerts[0] = sf::Vector2f(320.0f, 570.0f);
    floorVerts[2] = sf::Vector2f(320.0f, 620.0f);
    floorVerts[4] = sf::Vector2f(640.0f, 620.0f);
    floorVerts[6] = sf::Vector2f(960.0f, 670.0f);
    floorVerts[7] = sf::Vector2f(1280.0f, 670.0f);
    floorVerts[5] = sf::Vector2f(1280.0f, 720.0f);
    floorVerts[3] = sf::Vector2f(0.0f, 720.0f);

    Shape floor(floorVerts);

    // Boxes
    Square flatHigh(sf::Vector2f(160.0f, 150.0f), sf::Vector2f(100.0f, 100.0f), sf::Color::Red);
    Square flatMedium(sf::Vector2f(480.0f, 150.0f), sf::Vector2f(100.0f, 100.0f), sf::Color::Green);
    Square slant(sf::Vector2f(800.0f, 150.0f), sf::Vector2f(100.0f, 100.0f), sf::Color::Blue);
    Square flatLow(sf::Vector2f(1120.0f, 150.0f), sf::Vector2f(100.0f, 100.0f), sf::Color::Magenta);

    // Physics
    StaticBody pFloor(floor);
    StaticBody pFlatHigh(flatHigh);
    StaticBody pFlatMedium(flatMedium);
    StaticBody pSlant(slant);
    StaticBody pFlatLow(flatLow);

    // Collision groups
    Collision group;
    group.addObject(pFloor);
    group.addObject(pFlatHigh);
    group.addObject(pFlatMedium);
    group.addObject(pSlant);
    group.addObject(pFlatLow);

    while(window.open) {
        window.events();
        window.clear();

        pFlatHigh.position += sf::Vector2f(5.0f, 5.0f) * window.deltaTime;

        group.update(window);

        window.render();
    }

    window.close();
}
