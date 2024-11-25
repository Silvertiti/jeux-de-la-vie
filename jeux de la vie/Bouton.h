#ifndef BOUTON_H
#define BOUTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Bouton {

private:
	sf::RenderWindow window;
	sf::RectangleShape fond;
	sf::Text text;
	sf::Font font;


public:
	Bouton(const std::string& String);
	~Bouton();

	void setPosition(int x, int y);
	void setBackgroundColor(sf::Color c);

	void afficher(sf::RenderWindow& window);


};


#endif
