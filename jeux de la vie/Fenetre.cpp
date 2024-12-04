#include "Fenetre.h"
#include "slider.h" 
#include <iostream>
#include "Grille.h" 

Slider& Fenetre::getSlider2() {
    return slider2;
}

Slider& Fenetre::getSlider1() {
    return slider1;
}

Fenetre::Fenetre(int largeur, int hauteur, const std::string& titre) :
    pause(true),
    avancer("Avancer"),
    reculer("Reculer"),
    activerClicBouton("Activer Modification"), clicsGrilleActifs(false),

    slider1(largeur - 20, hauteur - 200, 150, 1.0f, 0.001f),        // premier slider pour vitess
    slider2(largeur - 40 - 20, hauteur - 200, 150, 1, 100)          // deuxi?me slider pour zoom 
{
    window.create(sf::VideoMode(largeur, hauteur), titre);

    boutonPause.setSize(sf::Vector2f(100, 40));                     //taille du rectangle du bouton 
    boutonPause.setFillColor(sf::Color(200, 200, 200));             //couleur du fond 


    activerClicBouton.setPosition(largeur - 250, 10);
    activerClicBouton.setBackgroundColor(sf::Color(150, 150, 150));

    avancer.setPosition(static_cast<float>(150), static_cast<float>(hauteur - 45));
    reculer.setPosition(static_cast<float>(280), static_cast<float>(hauteur - 45));
    boutonPause.setPosition(static_cast<float>(10), static_cast<float>(hauteur - 45));
    textePause.setPosition(static_cast<float>(15), static_cast<float>(hauteur - 40));

    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police." << std::endl;
        exit(-1);
    }

    textePause.setFont(font);
    textePause.setCharacterSize(20);
    textePause.setFillColor(sf::Color::Black);
    textePause.setPosition(15, hauteur - 40);
    textePause.setString("START");                                  // le bouton pause -> start au lancement 
}

sf::RenderWindow& Fenetre::getWindow() {                            //affichege de la fenentre 
    return window;
}

bool Fenetre::estPause() {
    return pause;
}

bool Fenetre::sontClicsGrilleActifs() const {
    return clicsGrilleActifs;
}



void Fenetre::gererEvenements(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

        if (reculer.estClique(mousePos)) {
            std::cout << "Reculer d'une it?ration." << std::endl;
            return;
        }

        if (avancer.estClique(mousePos)) {
            std::cout << "Avancer d'une it?ration." << std::endl;
            return;
        }

        if (boutonPause.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            pause = !pause;
            textePause.setString(pause ? sf::String("Play") : sf::String("Pause"));
            return;
        }

        if (pause && activerClicBouton.estClique(mousePos)) {
            clicsGrilleActifs = !clicsGrilleActifs; // Active/d?sactive les clics
            activerClicBouton.setString(clicsGrilleActifs ? sf::String("D?sactiver Modification") : sf::String("Activer Modification"));
        }
    }

    slider1.handleEvent(event, window);
    slider2.handleEvent(event, window);
}



void Fenetre::afficherPause() {
    slider2.draw(window); // Slider2 en permanence
    slider1.draw(window); // Slider1 en permanence

    if (pause) {
        avancer.afficher(window); // Bouton avancer en pause
        reculer.afficher(window); // Bouton reculer en pause
        activerClicBouton.afficher(window); // Bouton d'activation des clics
    }

    window.draw(boutonPause); // Bouton pause
    window.draw(textePause);  // Texte pause
}