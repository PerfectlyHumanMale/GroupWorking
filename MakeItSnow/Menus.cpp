#include <SFML/Graphics.hpp> 
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;
class Menus {
    RectangleShape menu;
    Keyboard::Key setkey;
    bool up;
    Event event;
    RectangleShape tabs[];

public:
    void setKey(Keyboard::Key key) {
        setkey = key;
        up = false;
    }
    void drawMenu(Vector2f Size, Vector2f Location, RenderWindow& wind, CircleShape MouseFolllowor) {
        menu.setSize(Size);
        menu.setFillColor(Color(190, 190, 190));
        menu.setPosition(Location);

        if (Keyboard::isKeyPressed(setkey)) {
            up = true;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            up = false;
        }
        if (up) {
            wind.draw(menu);
        }
    }
};