#include <SFML/Graphics.hpp>
#include <iostream>

class Slider {
private:
    sf::RectangleShape track;  // Piste verticale
    sf::CircleShape knob;      // Bouton du slider
    float minValue, maxValue, currentValue;

public:
    Slider(float x, float y, float height, float minValue, float maxValue)
        : minValue(minValue), maxValue(maxValue), currentValue(minValue) {
        // Piste
        track.setSize({ 5, height });
        track.setPosition(x, y);
        track.setFillColor(sf::Color::White);

        // Bouton
        knob.setRadius(10);
        knob.setOrigin(10, 10);  // Centre du bouton
        knob.setPosition(x + 2.5f, y);  // Début de la piste
        knob.setFillColor(sf::Color::Green);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(track);
        window.draw(knob);
    }

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            // Vérifier si la souris est dans la zone de la piste
            if (mousePos.x >= track.getPosition().x &&
                mousePos.x <= track.getPosition().x + track.getSize().x) {

                // Limiter la position Y du bouton à la piste
                float y = mousePos.y;
                if (y < track.getPosition().y) y = track.getPosition().y;
                if (y > track.getPosition().y + track.getSize().y) y = track.getPosition().y + track.getSize().y;

                // Déplacer le bouton
                knob.setPosition(track.getPosition().x + 2.5f, y);

                // Calculer la valeur actuelle du slider (en fonction de sa position verticale)
                float percent = (y - track.getPosition().y) / track.getSize().y;
                currentValue = minValue + percent * (maxValue - minValue);

                // Afficher la valeur actuelle et la position
                std::cout << "Valeur actuelle : " << currentValue
                    << " | Position Y : " << y << std::endl;
            }
        }
    }
    void createSlider() {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Slider Vertical Corrigé");

        Slider slider(400, 100, 400, 0, 100);  // Slider vertical de 0 à 100

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                slider.handleEvent(event, window);
            }

            window.clear();
            slider.draw(window);
            window.display();
        }
    }
};


