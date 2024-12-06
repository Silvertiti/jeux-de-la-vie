#ifndef SLIDER_H
#define SLIDER_H

#include <SFML/Graphics.hpp>

class Slider {
private:
    sf::RectangleShape bar;   // Piste verticale
    sf::CircleShape curseur;  // Bouton du slider
    float minValue, maxValue, currentValue;

public:

    Slider(float x, float y, float height, float minValue, float maxValue);
    void afficher(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    float getCurrentValue() const;
    sf::FloatRect getBarBounds() const {
        return bar.getGlobalBounds();
    }
};

#endif // SLIDER_H