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
    void setIconText(String texture, int iconNumber, String desplayText) {
        Font font;
        font.loadFromFile("MakeItSnowBlacknorthdemo-mLE25.ttf");

        tabText[iconNumber].setFont(font);
        tabText[iconNumber].setString(desplayText);

        iconTexture[iconNumber].loadFromFile(texture);
        icon[iconNumber].setTexture(&iconTexture[iconNumber]);
    }
    void createTab(int tabnum) {
        for (int i = 0; i < tabnum; i++) {
            tabs.push_back(RectangleShape());
            tabs[i].setPosition(menu.getPosition().x + 5, menu.getPosition().y + tabPostion);
            tabs[i].setSize(Vector2f((menu.getSize().x - 10), 50));

            icon.push_back(RectangleShape());
            icon[i].setFillColor(Color(255, 0, 0));
            icon[i].setPosition(menu.getPosition().x + 5, menu.getPosition().y + tabPostion);
            icon[i].setSize(Vector2f(50, 50));

            tabText.push_back(Text());
            tabText[i].setPosition(menu.getPosition().x + 55, menu.getPosition().y + tabPostion);
            tabPostion += 55;
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
                wind.draw(icon[i]);
            }
        }
    }
};