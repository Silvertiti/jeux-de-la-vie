#include "Slider.h"
#include <iostream>

Slider::Slider(float x, float y, float height, float minValue, float maxValue) : minValue(minValue), maxValue(maxValue), currentValue(minValue) {

	bar.setSize({ 5, height });
	bar.setPosition(x - bar.getSize().x, y);
	bar.setFillColor(sf::Color::Black);


	curseur.setRadius(10);
	curseur.setOrigin(10, 10);
	curseur.setPosition(x - bar.getSize().x / 2, y);
	curseur.setFillColor(sf::Color::Green);
}

void Slider::draw(sf::RenderWindow& window) {
	window.draw(bar);
	window.draw(curseur);
}

void Slider::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		// V�rifier si la souris est dans la zone de la piste
		if (mousePos.x >= bar.getPosition().x - 10 &&
			mousePos.x <= bar.getPosition().x + 10 + bar.getSize().x) {

			// Limiter la position Y du bouton � la piste
			float y = mousePos.y;
			if (y < bar.getPosition().y) y = bar.getPosition().y;
			if (y > bar.getPosition().y + bar.getSize().y) y = bar.getPosition().y + bar.getSize().y;

			// D�placer le bouton
			curseur.setPosition(bar.getPosition().x + 2.5f, y);

			// Calculer la valeur actuelle du slider (en fonction de sa position verticale)
			float percent = (y - bar.getPosition().y) / bar.getSize().y;
			currentValue = minValue + percent * (maxValue - minValue);

			// Afficher la valeur actuelle et la position
			std::cout << "Valeur actuelle : " << currentValue
				<< " | Position Y : " << y << std::endl;
		}
	}

};


