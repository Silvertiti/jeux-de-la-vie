#include <SFML/Graphics.hpp>
#include <string>
#include "Bouton.h"
#include "Slider.h"
#include "Grille.h"
#include "Texte.h"

class Fenetre {
private:
    sf::RenderWindow window;
    Texte texteVitesse;
    Texte texteZoom;
    Bouton ouvrirFenetreDesign;
    Bouton snake;
    Bouton avancer;
    Bouton reculer;
    Slider slider1; // Vitesse
    Slider slider2; // Zoom
    sf::RectangleShape boutonPause;
    sf::Text textePause;
    sf::Font font;
    bool pause;
    Bouton activerClicBouton;
    bool clicsGrilleActifs;

    // Gestion du déplacement
    bool isDragging;
    sf::Vector2i dragStartPos;
    sf::Vector2f grilleOffset;
    sf::View grilleView;
    sf::View interfaceView;
    sf::RectangleShape rectangle;// Rectangle pour interface
    Bouton exporter; // Bouton pour exporter la grille
    void mettreAJourBoutonPause(sf::RenderWindow& window);
public:
    Fenetre(int largeur, int hauteur, const std::string& titre);
    sf::RenderWindow& getWindow();
    bool estPause();
    bool sontClicsGrilleActifs();
    Slider getSlider1();
    Slider getSlider2();
    sf::Vector2f getGrilleOffset();
    void gererEvenements(sf::Event& event, Grille& grille, float cellSize);
    void afficherPause(Grille& grille, float cellSize);


};