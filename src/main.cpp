#include <iostream>
#include "shapes/square.h"
#include "physics/collision.h"

int main(int, char**) {
    Window window(sf::VideoMode(1280, 720), "2D Physics engine");

    // Create floor
    sf::VertexArray floorVerts(sf::LineStrip, 8);
    floorVerts[0] = sf::Vector2f(0.0f, 570.0f);     // 1
    floorVerts[1] = sf::Vector2f(320.0f, 570.0f);   // 0
    floorVerts[2] = sf::Vector2f(320.0f, 620.0f);   // 2
    floorVerts[3] = sf::Vector2f(640.0f, 620.0f);   // 4
    floorVerts[4] = sf::Vector2f(960.0f, 670.0f);   // 6
    floorVerts[5] = sf::Vector2f(1280.0f, 670.0f);  // 7
    floorVerts[6] = sf::Vector2f(1280.0f, 720.0f);  // 5
    floorVerts[7] = sf::Vector2f(0.0f, 720.0f);     // 3

    Shape floor(floorVerts);

    // Boxes
    Square flatHigh(sf::Vector2f(160.0f, 150.0f), sf::Vector2f(100.0f, 100.0f), sf::Color::Red);
    Square flatMedium(sf::Vector2f(480.0f, 150.0f), sf::Vector2f(100.0f, 100.0f), sf::Color::Green);
    Square slant(sf::Vector2f(800.0f, 150.0f), sf::Vector2f(100.0f, 100.0f), sf::Color::Blue);
    Square flatLow(sf::Vector2f(1120.0f, 150.0f), sf::Vector2f(100.0f, 100.0f), sf::Color::Magenta);

    // Physics
    StaticBody pFloor(floor);
    RigidBody pFlatHigh(flatHigh);
    RigidBody pFlatMedium(flatMedium);
    RigidBody pSlant(slant);
    RigidBody pFlatLow(flatLow);

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

        group.update(window);

        window.render();
    }

    window.close();
}
