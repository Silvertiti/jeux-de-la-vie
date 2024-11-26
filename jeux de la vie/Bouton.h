#ifndef BOUTON_H
#define BOUTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Bouton {
public:
    Bouton(const std::string& texte);
    ~Bouton();

    void setPosition(int x, int y);
    void setBackgroundColor(sf::Color c);
    void afficher(sf::RenderWindow& window);

private:
    sf::RectangleShape fond;
    sf::Text text;
    sf::Font font;
};

#endif // BOUTON_H
