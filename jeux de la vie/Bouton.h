

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

    void setPosition(int x, int y);
    void setBackgroundColor(sf::Color c);
    void afficher(sf::RenderWindow& window);
    bool estClique(const sf::Vector2i& mousePos) const; //pour implémentation avancer une iter

};

