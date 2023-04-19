#include <iostream>
#include "shapes/square.h"
#include "shapes/bounding.h"
#include "shapes/concave.h"
#include "physics/collision.h"

// void changeColour(sf::VertexArray& array, sf::Color colour) {
//     for (unsigned int i = 0; i < array.getVertexCount(); i++) {
//         array[i].color = colour;
//     }
// }

int main(int, char**) {
    Window window(sf::VideoMode(1280, 720), "2D Physics engine");

    // Create floor
    sf::VertexArray floorVerts(sf::Points, 8);
    floorVerts[0] = sf::Vector2f(0.0f, 570.0f);     // 0 1
    floorVerts[1] = sf::Vector2f(320.0f, 570.0f);   // 1 0
    floorVerts[2] = sf::Vector2f(320.0f, 620.0f);   // 2 2
    floorVerts[3] = sf::Vector2f(640.0f, 620.0f);   // 3 4
    floorVerts[4] = sf::Vector2f(960.0f, 670.0f);   // 4 6
    floorVerts[5] = sf::Vector2f(1280.0f, 670.0f);  // 5 7
    floorVerts[6] = sf::Vector2f(1280.0f, 720.0f);  // 6 5
    floorVerts[7] = sf::Vector2f(0.0f, 720.0f);     // 7 3

    // Shape floor(floorVerts);
    Concave floor(floorVerts);

    // Boxes
    Square red(sf::Vector2f(470.0f, 100.0f), sf::Vector2f(100.0f, 100.0f), sf::Color::Red);
    Square green(sf::Vector2f(120.0f, 100.0f), sf::Vector2f(100.0f, 100.0f), sf::Color::Green);
    Square blue(sf::Vector2f(800.0f, 100.0f), sf::Vector2f(100.0f, 100.0f), sf::Color::Blue);
    Square magenta(sf::Vector2f(1120.0f, 100.0f), sf::Vector2f(100.0f, 100.0f), sf::Color::Magenta);

    // Physics
    StaticBody pFloor(&floor);
    RigidBody pRed(&red);
    RigidBody pGreen(&green);
    RigidBody pBlue(&blue);
    RigidBody pMagenta(&magenta);

    // Collision groups  
    Collision group;
    group.addObject(pFloor);
    group.addObject(pRed);
    group.addObject(pGreen);
    group.addObject(pBlue);
    group.addObject(pMagenta);



    while(window.open) {
        // bool unpress = false;
        // while (!unpress)
        //     if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        //         unpress = true;
        
        window.events();
        window.clear();

        group.update(window);

        window.render();

        // bool press = false;
        // while (!press)
        //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        //         press = true;
    }

    window.close();
}
