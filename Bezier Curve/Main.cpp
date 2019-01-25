#include "Main.h"


sf::Vector2f p0, p1, p2;

const float T_STEP = 0.01f;

std::vector<sf::Vector2f> curve;

int selectedPoint = -1;

void start() {
	p0 = sf::Vector2f(100, 300);
	p1 = sf::Vector2f(600, 100);
	p2 = sf::Vector2f(400, 300);


	calculateCurve();

}

void draw() {

	if (selectedPoint != -1) {

		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));

		switch (selectedPoint) {
		case 0:
			p0 = mousePos;
			break;
		case 1:
			p1 = mousePos;
			break;
		case 2:
			p2 = mousePos;
			break;
		}

		calculateCurve();

	}




	sf::Vertex mainLine[2];

	mainLine[0].position = p0;
	mainLine[0].color = sf::Color(125, 125, 125);
	mainLine[1].position = p1;
	mainLine[1].color = sf::Color(125, 125, 125);

	window->draw(mainLine, 2, sf::Lines);

	mainLine[0].position = p1;
	mainLine[1].position = p2;

	window->draw(mainLine, 2, sf::Lines);


	sf::CircleShape curvePoint(10);



	curvePoint.setPosition(p0 - sf::Vector2f(10, 10));
	curvePoint.setFillColor(sf::Color::Green);

	if (selectedPoint == 0) curvePoint.setFillColor(sf::Color::Red);

	window->draw(curvePoint);


	curvePoint.setPosition(p1 - sf::Vector2f(10, 10));
	curvePoint.setFillColor(sf::Color::Green);

	if (selectedPoint == 1) curvePoint.setFillColor(sf::Color::Red);

	window->draw(curvePoint);

	curvePoint.setPosition(p2 - sf::Vector2f(10, 10));
	curvePoint.setFillColor(sf::Color::Green);

	if (selectedPoint == 2) curvePoint.setFillColor(sf::Color::Red);

	window->draw(curvePoint);


	for (int i = 0; i < curve.size() - 1; i++) {

		sf::Vertex curCurve[2];

		curCurve[0].position = curve[i];
		curCurve[0].color = sf::Color::Cyan;
		curCurve[1].position = curve[i + 1];
		curCurve[1].color = sf::Color::Cyan;

		window->draw(curCurve, 2, sf::Lines);

	}


}

void end() {

}

void mousePressed() {
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

	if (distance(sf::Vector2f(mousePos), p0) <= 11.f) {
		selectedPoint = 0;
	} else if (distance(sf::Vector2f(mousePos), p1) <= 11.f) {
		selectedPoint = 1;
	} else if (distance(sf::Vector2f(mousePos), p2) <= 11.f) {
		selectedPoint = 2;
	} else {
		selectedPoint = -1;
	}

}

void mouseReleased() {
	selectedPoint = -1;
}


sf::Vector2f linearlyInterpolate(float amount, sf::Vector2f pointA, sf::Vector2f pointB) {


	if (amount < 0) amount = 0;
	if (amount > 1) amount = 1;

	sf::Vector2f line = pointB - pointA;
	line *= amount;
	line += pointA;

	return line;

}

void calculateCurve() {

	curve.clear();

	for (float curT = 0; curT <= 1.f; curT += T_STEP) {
		sf::Vector2f q0 = linearlyInterpolate(curT, p0, p1);
		sf::Vector2f q1 = linearlyInterpolate(curT, p1, p2);
		sf::Vector2f b = linearlyInterpolate(curT, q0, q1);
		curve.push_back(b);
	}

}


float distance(sf::Vector2f a, sf::Vector2f b) {

	float dx = a.x - b.x;
	float dy = a.y - b.y;

	return sqrt(dx*dx + dy * dy);
}