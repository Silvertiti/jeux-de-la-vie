#include "Fenetre.h"
#include <iostream>

Fenetre::Fenetre(int largeur, int hauteur, const std::string& titre) : pause(false) {
    window.create(sf::VideoMode(largeur, hauteur), titre);

    boutonPause.setSize(sf::Vector2f(100, 40));
    boutonPause.setFillColor(sf::Color(200, 200, 200));
    boutonPause.setPosition(10, hauteur - 45);



    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police." << std::endl;
        exit(-1);
    }

    textePause.setFont(font);
    textePause.setCharacterSize(20);
    textePause.setFillColor(sf::Color::Black);
    textePause.setPosition(15, hauteur - 40);
    textePause.setString("Pause");

}

sf::RenderWindow& Fenetre::getWindow() {
    return window;
}

bool Fenetre::estPause() const {
    return pause;
}

void Fenetre::gererEvenements() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (boutonPause.getGlobalBounds().contains(mousePos)) {
                pause = !pause;
                textePause.setString(pause ? "Play" : "Pause");
            }
        }
    }
}

void Fenetre::afficherPause() {
    window.draw(boutonPause);
    window.draw(textePause);
}
