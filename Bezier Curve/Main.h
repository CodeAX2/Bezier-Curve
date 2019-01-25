#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>


extern sf::RenderWindow* window;

void start();
void draw();
void end();
sf::Vector2f linearlyInterpolate(float amount, sf::Vector2f pointA, sf::Vector2f pointB);
void calculateCurve();
float distance(sf::Vector2f a, sf::Vector2f b);


/*
 *	Below functions all require to
 *	be added into "Source.cpp"
 *	so that they can be called.
 *	This is only required if they
 *	have an implimentation.
*/

void mousePressed();
void mouseReleased();
void keyPressed(sf::Keyboard::Key keyCode);
void keyReleased(sf::Keyboard::Key keyCode);

