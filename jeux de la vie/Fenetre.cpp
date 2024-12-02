#include "Fenetre.h"
#include "slider.h" 
#include <iostream>
#include "Grille.h" 

 Slider& Fenetre::getSlider2()  {
    return slider2;
}

 Slider& Fenetre::getSlider1()  {
    return slider1;
}

Fenetre::Fenetre(int largeur, int hauteur, const std::string& titre) : 
    pause(true),
    avancer("Avancer"),                                       
    reculer("Reculer"),

    slider1(largeur - 20, hauteur - 200, 150, 1.0f, 0.001f),        // premier slider pour vitess
    slider2(largeur - 40 - 20, hauteur - 200, 150, 1, 100)          // deuxième slider pour zoom 
{
    window.create(sf::VideoMode(largeur, hauteur), titre);

    avancer.setPosition(150, hauteur - 45);
    reculer.setPosition(280, hauteur - 45);
      
    boutonPause.setSize(sf::Vector2f(100, 40));                     //taille du rectangle du bouton 
    boutonPause.setFillColor(sf::Color(200, 200, 200));             //couleur du fond 
    boutonPause.setPosition(10, hauteur - 45);                      //position du bouton 

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

void Fenetre::gererEvenements() {
    
    sf::Event event;

    while (window.pollEvent(event)) {
        
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y); 
            
            if (reculer.estClique(mousePos)) {
                std::cout << "Reculer d'une itération." << std::endl;
                //implementer la fonction pour avancer 
            }
            
            if (avancer.estClique(mousePos)) {
                std::cout << "avancer d'une itération." << std::endl;
                //implementer la fonction pour reculer
            }
            
            if (boutonPause.getGlobalBounds().contains((mousePos.x), (mousePos.y))) {
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
    
    slider2.draw(window);                   // slider2 en permanence
    slider1.draw(window);                   // slider1 en permanence 
        
    if (pause) {
        avancer.afficher(window);           // Bouton avancer en pause
        reculer.afficher(window);           // Bouton reculer en pause
    }


    window.draw(boutonPause);               // pause
    window.draw(textePause);                // txt de pause
}


