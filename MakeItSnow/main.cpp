#pragma region imports
#include <SFML/Graphics.hpp> 
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include "Rooms.cpp"
#include "Workers.cpp"
#include "Menus.cpp"
using namespace sf;
using namespace std;
#pragma endregion imports

#pragma region publicVerables 
CircleShape MouseFolllowor;
Vector2f LocationOfRoom;

#define winWidth 1100
#define winHeight 1000

Menus MinigameMenu;
Menus WorkerMenu;
Menus BuildMenu;

int metal = 11;
int t = 0;
int i = 0;
int workernumber;

bool paused = false;
bool buildup = false;
bool click = true;

Rooms room[100];
Workers worker[100];
Rooms CargoHold;

RenderWindow window(sf::VideoMode(winWidth, winHeight), "Main");

string roomData[100];
string workerData[100];
#pragma endregion publicVerables 

void gridview(RenderWindow& wind) {
    vector<RectangleShape> v;
    for (int i = 0; i < 11; i++) {
        v.push_back(RectangleShape());
        v.back().setPosition(i * 100, 0);
        v.back().setFillColor(Color::White);
        v.back().setSize(Vector2f(2, 1000));
        wind.draw(v.back());
    }
    for (int j = 0; j < 10; j++) {
        v.push_back(RectangleShape());
        v.back().setPosition(0, j * 100);
        v.back().setFillColor(Color::White);
        v.back().setSize(Vector2f(1100, 2));
        wind.draw(v.back());
    }
}

void saveStuff(int numberOfRooms, int numberOfWorkers) {
    ofstream MyWorkerWriteFile("WorkerFile.txt");
    ofstream MyRoomWriteFile("RoomFile.txt");
    string ah;

    for (int j = 0; j < numberOfWorkers; j++) {
        MyWorkerWriteFile << workerData[j] << "\n";
    }
    MyWorkerWriteFile.close();
    string ds;
    for (int j = 0; j < numberOfRooms; j++) {
        ds = room[j].saveData();
        MyRoomWriteFile << ds << "\n";
        cout << ds << endl;
    }
    MyRoomWriteFile.close();
}
void loadstuff() {
    ifstream MyWorkerReadFile("WorkerFile.txt");
    ifstream MyRoomReadFile("RoomFile.txt");
    string h;
    string n;
    int roomNum = 0;
    int workerNum = 0;
    while (getline(MyWorkerReadFile, h)) {
        worker[workerNum].loadFile(h,window);
        workerNum++;
    }
    while (getline(MyRoomReadFile, n)) {
        room[roomNum].loadFile(n,window);
        cout << n << endl;
        roomNum++;
    }
    i += roomNum;
}

#pragma region menuMethods
void MinigameMethods(int num) {
    //bring up the minigames
    switch (num) {
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    }
}
void WorkerMenuMethods(int num) {
    switch (num) {
    case 0:
        //spawn worker
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    }
}
void BuildMenuMethods(int num) {
    switch (num) {
    case 0:
        //build elevater
        break;
    case 1:
        //build generater
        break;
    case 2:
        //build greenhouse
        break;
    case 3:
        //
        break;
    }
}
void createFile(string fileName) {
    ofstream MyWriteFile(fileName+".txt");
}
#pragma endregion menuMethods

int main()
{
    #pragma region defineMenu 
    MinigameMenu.setKey(Keyboard::B);
    MinigameMenu.createMenu(Vector2f(300, 400), Vector2f(300, 100));
    MinigameMenu.createTab(6);

    WorkerMenu.setKey(Keyboard::N);
    WorkerMenu.createMenu(Vector2f(300, 400), Vector2f(0, 0));
    WorkerMenu.createTab(6);

    BuildMenu.setKey(Keyboard::M);
    BuildMenu.createMenu(Vector2f(300, 400), Vector2f(800, 0));
    BuildMenu.createTab(6);
    #pragma endregion defineMenu

    #pragma region defineCargo
    CargoHold.setLocation(Vector2f(winWidth / 2, winHeight / 2));
    CargoHold.setFillColor(Color(255, 255, 255));
    CargoHold.setOutlineColor(Color(255, 255, 255));
    CargoHold.setOutlineThickness(10);
    #pragma endregion defineCargo

    #pragma region houseKeeping
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear(Color::Black);
       #pragma endregion houseKeeping

        #pragma region buttonStuff
        if (Keyboard::isKeyPressed(Keyboard::H)) {
            metal += 10;
            cout << metal;
        }
        if (Keyboard::isKeyPressed(Keyboard::G)) {
            gridview(window);
        }
        if (Keyboard::isKeyPressed(Keyboard::O)) {
            LocationOfRoom = room[i].desplayLocation(MouseFolllowor, click);
        }
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            saveStuff(i, i);
        }

        if (Keyboard::isKeyPressed(Keyboard::A)) {
            loadstuff();
        }
        #pragma endregion buttonStuff

        #pragma region RoomPlacement
        if (event.type == Event::MouseButtonPressed && click) {
            click = false;
            bool here = false;
            bool roomhere = false;
            int x = MouseFolllowor.getPosition().x;
            int y = MouseFolllowor.getPosition().y;

            for (int j = 0; j < 100; j++) {
                
                if (CargoHold.getLocation() == Vector2f((MouseFolllowor.getPosition().x - (x % 100)) - 100, MouseFolllowor.getPosition().y - (y % 100)) || room[j].getLocation() == Vector2f((MouseFolllowor.getPosition().x - (x % 100)) -100, MouseFolllowor.getPosition().y - (y % 100))) {
                    here = true;
                }
                else if (CargoHold.getLocation() == Vector2f((MouseFolllowor.getPosition().x - (x % 100)) + 100, MouseFolllowor.getPosition().y - (y % 100)) ||room[j].getLocation() == Vector2f((MouseFolllowor.getPosition().x - (x % 100)) + 100, MouseFolllowor.getPosition().y - (y % 100))) {
                    here = true;
                }
                else if (room[j].getLocation() == Vector2f((MouseFolllowor.getPosition().x - (x % 100)), MouseFolllowor.getPosition().y - (y % 100) - 100) || CargoHold.getLocation() == Vector2f((MouseFolllowor.getPosition().x - (x % 100)) - 100, MouseFolllowor.getPosition().y - (y % 100))) {
                    here = true;
                }
                else if (room[j].getLocation() == Vector2f((MouseFolllowor.getPosition().x - (x % 100)), MouseFolllowor.getPosition().y - (y % 100) + 100) || CargoHold.getLocation() == Vector2f((MouseFolllowor.getPosition().x - (x % 100)) + 100, MouseFolllowor.getPosition().y - (y % 100))) {
                    here = true;
                }
                if (room[j].getLocation() == Vector2f(MouseFolllowor.getPosition().x - (x % 100), MouseFolllowor.getPosition().y - (y % 100))) {
                    roomhere = true;
                    LocationOfRoom = room[j].desplayLocation(MouseFolllowor, click);
                    workernumber = worker[j].desplaynumber(MouseFolllowor, click);
                    cout << "w" << endl;
                }
            }
            if (metal >= 10 && here == true && roomhere == false) {
                room[i].setLocation(MouseFolllowor.getPosition());
                room[i].determinType(i % 3, CargoHold.getLocation().x);
                cout << MouseFolllowor.getPosition().x << endl;
                cout << MouseFolllowor.getPosition().y << endl;
                metal -= 10;
            }
            worker[i].setnumber(i);
            worker[workernumber].setRoom(LocationOfRoom);
            worker[i].setLocation(CargoHold.getLocation());
            cout << workernumber << endl;
            cout << to_string( LocationOfRoom.x) + " " + to_string(LocationOfRoom.y) << endl;
            //cout << i << endl;
            i++;
        }
        else if (event.type == Event::MouseButtonReleased) {
            click = true;
        }
        #pragma endregion RoomPlacement

        #pragma region Gameloop
        for (int j = 0; j < 100; j++) {
            CargoHold.spawn(window);

            LocationOfRoom = room[j].desplayLocation(MouseFolllowor, click);
            room[j].returnClick(MouseFolllowor);
            room[j].spawn(window);
            roomData[j] = room[j].saveData();

            WorkerMenuMethods(WorkerMenu.tabClick(MouseFolllowor, click));
            BuildMenuMethods(BuildMenu.tabClick(MouseFolllowor, click));
            MinigameMethods(MinigameMenu.tabClick(MouseFolllowor, click));

            worker[j].spawn(window);
            worker[j].moveToRoom(CargoHold.getLocation());
            worker[j].testOutput();
            workerData[j] = worker[i].saveTheData();
        }

        MinigameMenu.drawMenu(window);
        BuildMenu.drawMenu(window);
        WorkerMenu.drawMenu(window);
        #pragma endregion Gameloop

        #pragma region defineMouse
        MouseFolllowor.setPosition(Mouse::getPosition().x - 375, Mouse::getPosition().y - 70);
        MouseFolllowor.setRadius(10);
        window.draw(MouseFolllowor);
        #pragma endregion defineMouse
        window.display();
    }
    return 0;
}