#include "Fenetre.h"
#include "fenetrebonus.h"
#include <iostream>
#include "snake.h"


Fenetre::Fenetre(int largeur, int hauteur, const std::string& titre)
    : pause(true),
    avancer("Avancer"),
    reculer("Reculer"),
    exporter("Exporter"),
    ouvrirFenetreDesign("(?)"),
    texteZoom("Vitesse"),
    texteVitesse("Zoom"),
	snake(""),
    activerClicBouton("Activer Modification"),
    clicsGrilleActifs(false),
    slider1((largeur - 150), (hauteur - 100), 150.0f, 1.0f, 0.001f),
    slider2((largeur - 150), (hauteur - 50), 150.0f, 30.0f, 5.0f),
    grilleOffset(0.0f, 0.0f),
    isDragging(false)
{


    window.create(sf::VideoMode(largeur, hauteur), titre);

    // Bouton "Info"
    ouvrirFenetreDesign.setPosition(largeur - 50, hauteur - 155);
    ouvrirFenetreDesign.setBackGroundColorClear();

	// Bouton "Snake"
    snake.setPosition(largeur - 350, hauteur - 155);
    snake.setBackGroundColorClear();


    // Texte "Vitesse"
    texteVitesse.setPosition(largeur - 240, hauteur - 55);
    // Texte "Zoom"
    texteZoom.setPosition(largeur - 240, hauteur - 105);

    // Bouton "Exporter"
    exporter.setPosition(150, hauteur - 60);

    // Bouton "Pause/Start"
    boutonPause.setSize(sf::Vector2f(100, 40));
    boutonPause.setFillColor(sf::Color(32, 32, 32, 255));
    boutonPause.setPosition(10, hauteur - 60);

    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police." << std::endl;
        exit(-1);
    }

    // rectangle "interface"


    rectangle.setSize(sf::Vector2f(largeur, 300));
    rectangle.setFillColor(sf::Color(174, 174, 174, 255));
    rectangle.setPosition(0, hauteur - 150);

    textePause.setFont(font);
    textePause.setCharacterSize(20);
    textePause.setFillColor(sf::Color::White);
    textePause.setPosition(boutonPause.getPosition().x + 10, boutonPause.getPosition().y + 5);
    textePause.setString("START");

    // Bouton "Avancer"
    avancer.setPosition(10, hauteur - 120);

    // Bouton "Reculer"
    reculer.setPosition(150, hauteur - 120);

    // Bouton "Activer Modification"
    activerClicBouton.setPosition(300, hauteur - 100);
};


sf::RenderWindow& Fenetre::getWindow() {
    return window;
}

bool Fenetre::estPause() {
    return pause;
}

bool Fenetre::sontClicsGrilleActifs() {
    return clicsGrilleActifs;
}

Slider Fenetre::getSlider1() {
    return slider1;
}

Slider Fenetre::getSlider2() {
    return slider2;
}

sf::Vector2f Fenetre::getGrilleOffset() {
    return grilleOffset;
}


void Fenetre::mettreAJourBoutonPause(sf::RenderWindow& window) {
    sf::Vector2i positionSouris = sf::Mouse::getPosition(window);

    sf::Vector2f positionSourisFlottante(static_cast<float>(positionSouris.x), static_cast<float>(positionSouris.y));

    bool sourisSurBouton = boutonPause.getGlobalBounds().contains(positionSourisFlottante);

    if (sourisSurBouton) {
        boutonPause.setFillColor(sf::Color(64, 64, 64, 255)); 
    }
    else {
        boutonPause.setFillColor(sf::Color(32, 32, 32, 255)); 
    }
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
                grille.mettreAJour();
            }
            return;
        }

        if (reculer.estClique(mousePos)) {
            if (pause) {
                std::cout << "Bouton Reculer cliqué.\n";
                if (!grille.revenirEnArriere()) {
                    std::cout << "Impossible de reculer, aucun état enregistré.\n";
                }
            }
            return;
        }

        if (exporter.estClique(mousePos)) {
            if (pause) {
                std::cout << "Exportation de la grille...\n";
                grille.exporterGrille("grille_exportee.txt");
            }
            return;
        }

        if (ouvrirFenetreDesign.estClique(mousePos)) {
            FenetreTouche FenetreTouche(font);
            FenetreTouche.bouclePrincipaleTouche(); 
        }

        if (snake.estClique(mousePos)) {
            SnakeGame snake;
			snake.run();
        }


        if (activerClicBouton.estClique(mousePos)) {
            clicsGrilleActifs = !clicsGrilleActifs;
            activerClicBouton.setString(clicsGrilleActifs ? "Désactiver Modification" : "Activer Modification");
            return;
        }

        if (clicsGrilleActifs) {
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

            int col = static_cast<int>((worldPos.x - grilleOffset.x) / cellSize);
            int row = static_cast<int>((worldPos.y - grilleOffset.y) / cellSize);

            if (col >= 0 && col < grille.getColonnes() && row >= 0 && row < grille.getLignes()) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                    grille.definirCelluleImmortelle(row, col);
                    std::cout << "Cellule immortelle définie à (" << row << ", " << col << ").\n";
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
                    grille.definirCelluleIndestructible(row, col);
                    std::cout << "Cellule morte indestructible définie à (" << row << ", " << col << ").\n";
                }
                else {
                    grille.changerCase(window, cellSize, event, grilleOffset);
                }
            }
            else {
                std::cout << "Clic hors de la grille.\n";
            }
        }
    }


    slider1.gererEvenementSlider(event, window);
    slider2.gererEvenementSlider(event, window);
}


void Fenetre::afficherPause(Grille& grille, float cellSize) {
    window.draw(rectangle);
    slider2.afficher(window);
    slider1.afficher(window);
    texteVitesse.afficher(window);
    texteZoom.afficher(window);

    ouvrirFenetreDesign.afficher(window);

    mettreAJourBoutonPause(window);
    window.draw(boutonPause);
    window.draw(textePause);

    if (pause) {
        avancer.afficher(window);
        reculer.afficher(window);
        activerClicBouton.afficher(window);
        exporter.afficher(window);
		snake.afficher(window); 

        avancer.mettreAJour(window);
        reculer.mettreAJour(window);
        activerClicBouton.mettreAJour(window);
        exporter.mettreAJour(window);
    }
}