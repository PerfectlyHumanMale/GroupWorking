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
    vector <RectangleShape> tabs;
    vector <bool> tabclick;
    int tabPostion = 5;
    vector <RectangleShape> icon;
    vector <Texture> iconTexture;
    vector <Text> tabText;
public:
    void setKey(Keyboard::Key key) {
        setkey = key;
        up = false;
    }
    void setIconText(String texture, int iconNumber) {
        Font font;
        font.loadFromFile("MakeItSnowBlacknorthdemo-mLE25.ttf");

        iconTexture[iconNumber].loadFromFile(texture);
        icon[iconNumber].setTexture(&iconTexture[iconNumber]);
        
    }
    void createTab(int tabnum) {
        for (int i = 0; i < tabnum; i++) {
            tabs.push_back(RectangleShape());
            tabs[i].setPosition(menu.getPosition().x + 5, menu.getPosition().y + tabPostion);
            tabs[i].setSize(Vector2f((menu.getSize().x - 10), 80));
            tabPostion += 85;
        }
    }
    void createMenu(Vector2f Size, Vector2f Location) {
        menu.setSize(Size);
        menu.setFillColor(Color(190, 190, 190));
        menu.setPosition(Location);
    }
    void drawMenu(RenderWindow& wind) {
        if (Keyboard::isKeyPressed(setkey)) {
            up = true;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            up = false;
        }
        if (up) {
            wind.draw(menu);
            for (int i = 0; i < tabs.size();i++) {
                wind.draw(tabs[i]);
            }
        }
    }
};