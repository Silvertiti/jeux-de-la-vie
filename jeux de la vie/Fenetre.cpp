#include "Fenetre.h"
#include "slider.h" 
#include <iostream>
#include "Grille.h" 

const Slider& Fenetre::getSlider2() const {
    return slider2;
}

const Slider& Fenetre::getSlider1() const {
    return slider1;
}

Fenetre::Fenetre(int largeur, int hauteur, const std::string& titre)
    : pause(false),
    avancer("Avancer"),
    avancerRapide("Avancer rapide"),
    slider1(largeur - 20, hauteur - 200, 150, 5.0f, 0.001f), // premier slider pour vitess
    slider2(largeur - 40 - 20, hauteur - 200, 150, 1, 100) // deuxième slider pour zoom 
{
    window.create(sf::VideoMode(largeur, hauteur), titre);

    avancer.setPosition(150, hauteur - 45);
    avancer.setBackgroundColor(sf::Color::Green);

    avancerRapide.setPosition(250, hauteur - 45);
    avancerRapide.setBackgroundColor(sf::Color::Red);

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

        slider1.handleEvent(event, window); //slider1
        slider2.handleEvent(event, window);  // tjrs voir slider2


        if (pause) {


            
        }
    }
}

void Fenetre::afficherPause() {
    // Afficher slider2 en permanence
    slider2.draw(window);   
    slider1.draw(window);
    
    // Afficher les éléments liés à la pause uniquement si en pause
    if (pause) {
        avancer.afficher(window);        // Bouton avancer
        avancerRapide.afficher(window); // bouton avancer rapide
         // slider1 uniquement en pause
    }

    window.draw(boutonPause); // pause
    window.draw(textePause); // txt de pause


}

    
    