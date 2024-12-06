#include "Slider.h"
#include <iostream>

Slider::Slider(float x, float y, float height, float minValue, float maxValue) : minValue(minValue), maxValue(maxValue), currentValue(minValue) {

    //Spec de la bar 
    bar.setSize({ 5, height });
    bar.setPosition(x - bar.getSize().x, y+10);
    bar.setFillColor(sf::Color::Black);
    bar.setRotation(-90);
    //Spec du curseur 
    curseur.setRadius(10);
    curseur.setOrigin(10, 10);
    curseur.setPosition(x - bar.getSize().x * 2, y + 8);
	std::cout << "x : " << x << " y : " << y << std::endl;
    curseur.setFillColor(sf::Color(200, 200, 200));
    curseur.setRotation(-90);
}

void Slider::afficher(sf::RenderWindow& window) {  //affichage 
    window.draw(bar);
    window.draw(curseur);
}
void Slider::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        // Vérifier si la souris est dans la zone de la piste
        if (mousePos.y >= bar.getPosition().y - 10 && mousePos.y <= bar.getPosition().y + bar.getSize().x + 10) { // Notez qu'on vérifie sur l'axe X en réalité

            // Limiter la position X du bouton à la barre (considérant la rotation)
            float x = mousePos.x;
            float barStart = bar.getPosition().x; // Position X de la barre
            float barEnd = barStart + bar.getSize().y; // Longueur de la barre

            if (x < barStart) x = barStart;
            if (x > barEnd) x = barEnd;

            // Déplacer le curseur
            curseur.setPosition(x, bar.getPosition().y -0.8f); // Centré sur la barre

            // Calculer la valeur actuelle en fonction de la position X
            float percent = (x - barStart) / bar.getSize().y;
            currentValue = minValue + percent * (maxValue - minValue);

            // Debugging output
            // std::cout << "Valeur actuelle : " << currentValue
            //           << " | Position X : " << x << std::endl;
        }
    }
}



float Slider::getCurrentValue() const { //utiliser pour donner une valeur def ds le constructeur 
    return currentValue;
}
    



/*void createSlider(); {
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
    }*/


    //OUVRE TROP D'ONGLET OR ON VEUT QUE CELA S'AFFICHE SUR LA FENTRE DU JEU 



