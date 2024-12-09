#include <SFML/Graphics.hpp>

class Slider {
private:
    sf::RectangleShape bar;   // Piste verticale
    sf::CircleShape curseur;  // Bouton du slider
    float minValeur, maxValeur, currentValeur;

public:

    Slider(float x, float y, float taille, float minValeur, float maxValeur);
    void afficher(sf::RenderWindow& window);


    void handleEvent(sf::Event& event, sf::RenderWindow& window);


    float getCurrentValue() const;

};

