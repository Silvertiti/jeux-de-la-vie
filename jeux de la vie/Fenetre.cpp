#include "Fenetre.h"
#include <iostream>

Fenetre::Fenetre(int largeur, int hauteur, const std::string& titre)
    : pause(true),
    avancer("Avancer"),
    reculer("Reculer"),
    activerClicBouton("Activer Modification"),
    clicsGrilleActifs(false),
    slider1(largeur - 20, hauteur - 200, 150, 1.0f, 0.001f),        // premier slider pour vitess
    grilleOffset(0.0f, 0.0f),
    isDragging(false) {

    window.create(sf::VideoMode(largeur, hauteur), titre);

    // Bouton "Pause/Start"
    boutonPause.setSize(sf::Vector2f(100, 40));
    boutonPause.setFillColor(sf::Color(200, 200, 200));
    boutonPause.setPosition(10, hauteur - 60); // Ajustez la position selon vos besoins

    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police." << std::endl;
        exit(-1);
    }

    textePause.setFont(font);
    textePause.setCharacterSize(20);
    textePause.setFillColor(sf::Color::Black);
    textePause.setPosition(boutonPause.getPosition().x + 10, boutonPause.getPosition().y + 5);
    textePause.setString("START");

    // Bouton "Avancer"
    avancer.setPosition(10, hauteur - 120); // Ajustez cette position
    avancer.setBackgroundColor(sf::Color(100, 100, 255));

    // Bouton "Reculer"
    reculer.setPosition(150, hauteur - 120); // Ajustez cette position
    reculer.setBackgroundColor(sf::Color(255, 100, 100));

    // Bouton "Activer Modification"
    activerClicBouton.setPosition(10, hauteur - 180); // Ajustez cette position
    activerClicBouton.setBackgroundColor(sf::Color(100, 255, 100));
}


sf::RenderWindow& Fenetre::getWindow() {
    return window;
}

bool Fenetre::estPause() const {
    return pause;
}

bool Fenetre::sontClicsGrilleActifs() const {
    return clicsGrilleActifs;
}

Slider& Fenetre::getSlider1() {
    return slider1;
}

Slider& Fenetre::getSlider2() {
    return slider2;
}

sf::Vector2f Fenetre::getGrilleOffset() const {
    return grilleOffset;
}

void Fenetre::gererEvenements(sf::Event& event, Grille& grille, float cellSize) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
        isDragging = true;
        dragStartPos = sf::Mouse::getPosition(window);
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
        isDragging = false;
    }

    if (event.type == sf::Event::MouseMoved && isDragging) {
        sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
        sf::Vector2f offset(
            static_cast<float>(currentMousePos.x - dragStartPos.x),
            static_cast<float>(currentMousePos.y - dragStartPos.y)
        );
        grilleOffset += offset;
        dragStartPos = currentMousePos;
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (boutonPause.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            pause = !pause;
            textePause.setString(pause ? "START" : "PAUSE");
            return;
        }

        if (avancer.estClique(mousePos)) {
            if (pause) {
                std::cout << "Bouton Avancer cliqué.\n";
                // Appelle la méthode pour avancer une itération
                grille.mettreAJour();
            }
            return;
        }
        if (reculer.estClique(mousePos)) {
            if (pause) {
                std::cout << "Bouton Reculer cliqué.\n";
                grille.revenirEnArriere(); // Revenir à l'état précédent
            }
            return;
        }


        if (activerClicBouton.estClique(mousePos)) {
            clicsGrilleActifs = !clicsGrilleActifs;
            activerClicBouton.setString(clicsGrilleActifs ? "Désactiver Modification" : "Activer Modification");
            return;
        }

        if (clicsGrilleActifs) {
            grille.changerCase(window, cellSize, event, grilleOffset);
        }
    }

    slider1.handleEvent(event, window);
}

void Fenetre::afficherPause(Grille& grille, float cellSize) {
    slider1.draw(window);

    if (pause) {
        avancer.afficher(window);        // Position fixe
        reculer.afficher(window);        // Position fixe
        activerClicBouton.afficher(window); // Position fixe
    }

    window.draw(boutonPause);
    window.draw(textePause);
}
