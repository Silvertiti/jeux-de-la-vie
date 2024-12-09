#include <SFML/Graphics.hpp>
#include <string>

class Bouton {

private:

    sf::RectangleShape fond;
    sf::Text text;
    sf::Font font;

public:
    Bouton(const std::string& texte);
    ~Bouton();
    //fonction pour le bouton  
    void setPosition(int x, int y);                            //position 
    void mettreFondVide();                           // couleur du fond (si pas par defaut)
    void afficher(sf::RenderWindow& window);                 //afficher le bouton                               
    bool estClique(const sf::Vector2i& mousePos) const;     //cliquable ou non pour implémentation avancer une iter     
    void setString(const std::string& nouveauTexte);
    void mettreAJour(sf::RenderWindow& window);
};

