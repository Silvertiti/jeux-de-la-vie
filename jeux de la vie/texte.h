#include <SFML/Graphics.hpp>
#include <string>

class Texte {

private:
    sf::Text text;
    sf::Font font;

public:
    Texte(const std::string& texte);
    ~Texte();
    //fonction pour le bouton  
    void setPosition(int x, int y);                         //position 
    void afficher(sf::RenderWindow& window);                //afficher le bouton 
    void setString(const std::string& nouveauTexte);
};

