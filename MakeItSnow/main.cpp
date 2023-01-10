#pragma region imports
#include <SFML/Graphics.hpp> 
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include "Rooms.cpp"
#include "Workers.cpp"
#include "Collision.hpp"
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
int workernumber;
int numberofrooms = 0;
int numberofworkers = 0;

bool paused = false;
bool buildup = false;
bool click = true;

Rooms room[100];
Workers worker[100];
Rooms CargoHold;

RenderWindow window(sf::VideoMode(winWidth, winHeight), "Main");

float currentOxygen = 150;
float totalOxygen = 150 + numberofrooms * 20;
float oxegyendrian = 0;

RectangleShape outObar;
RectangleShape innerObar;

float currentHunger = 150;
float totalHunger = 150 + numberofworkers * 20;
float hungerdrain = 0;

RectangleShape outHbar;
RectangleShape innerHbar;

float hungerPercentage = ((float)currentHunger / (float)totalHunger) * 100;

float currentPower = 150;
float totalPower = 150 + numberofrooms * 20;
float powerdrain = 0;

RectangleShape outPbar;
RectangleShape innerPbar;

float powerPercentage = ((float)currentPower / (float)totalPower) * 100;
float oxygenPercentage = ((float)currentOxygen / (float)totalOxygen) * 100;

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
    ofstream MyReasourseWriteFile("ResourseFile.txt");

    //MyReasourseWriteFile << currentOxygen << "\n";
    //MyReasourseWriteFile << currentHunger << "\n";
    //MyReasourseWriteFile << currentPower << "\n";
    //MyReasourseWriteFile << metal << "\n";
    //MyReasourseWriteFile.close();

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
    ifstream MyResoursesReadFile("ResourseFile.txt");

    string h;
    string n;
    string l;
    int resoursesArray[3];
    int roomNum = 0;
    int workerNum = 0;
    int ResourseNum = 0;
    while (getline(MyWorkerReadFile, h)) {
        worker[workerNum].loadFile(h,window);
        workerNum++;
    }
    while (getline(MyRoomReadFile, n)) {
        room[roomNum].loadFile(n,window);
        roomNum++;
    }
    while (getline(MyResoursesReadFile, l)) {
        resoursesArray[ResourseNum] = stoi(l);
        ResourseNum++;
    }
    numberofrooms += roomNum;
}

#pragma region menuMethods
 
void MinigameMethods(int num) {
    
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

        #pragma region bars 
        totalOxygen = 150 + numberofworkers * 20;
        totalHunger = 150 + numberofworkers * 20;
        totalPower = 150 + numberofrooms * 20;

        outHbar.setOutlineColor(Color(255, 255, 255));
        outHbar.setOutlineThickness(2);
        outHbar.setSize(Vector2f(totalHunger, 40));
        outHbar.setPosition(Vector2f(10, 10));
        outHbar.setFillColor(Color::Black);

        innerHbar.setPosition(Vector2f(10, 10));
        innerHbar.setFillColor(Color::Red);
        innerHbar.setSize(Vector2f(currentHunger, 40));

        outPbar.setOutlineColor(Color(255, 255, 255));
        outPbar.setOutlineThickness(2);
        outPbar.setSize(Vector2f(totalPower, 40));
        outPbar.setPosition(Vector2f(10, 60));
        outPbar.setFillColor(Color::Black);

        innerPbar.setFillColor(Color::Yellow);
        innerPbar.setSize(Vector2f(currentPower, 40));
        innerPbar.setPosition(Vector2f(10, 60));

        outObar.setOutlineColor(Color(255, 255, 255));
        outObar.setOutlineThickness(2);
        outObar.setSize(Vector2f(totalOxygen, 40));
        outObar.setPosition(Vector2f(10, 110));
        outObar.setFillColor(Color::Black);

        innerObar.setFillColor(Color::Green);
        innerObar.setSize(Vector2f(currentOxygen, 40));
        innerObar.setPosition(Vector2f(10, 110));
        #pragma endregion bars 

        #pragma region buttonStuff
        if (Keyboard::isKeyPressed(Keyboard::H)) {
            metal += 10;
            cout << metal;
        }
        if (Keyboard::isKeyPressed(Keyboard::G)) {
            gridview(window);
        }
        if (Keyboard::isKeyPressed(Keyboard::O)) {
            LocationOfRoom = room[numberofrooms].desplayLocation(MouseFolllowor, click);
            //Asteroids();
        }
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            saveStuff(numberofrooms, numberofworkers);
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
                room[numberofrooms].setLocation(MouseFolllowor.getPosition());
                room[numberofrooms].determinType(numberofrooms % 3, CargoHold.getLocation().x);
                cout << MouseFolllowor.getPosition().x << endl;
                cout << MouseFolllowor.getPosition().y << endl;
                metal -= 10;
                numberofrooms++;
            }
            worker[numberofworkers].setnumber(numberofworkers);
            worker[workernumber].setRoom(LocationOfRoom);
            worker[numberofworkers].setLocation(CargoHold.getLocation());
            cout << workernumber << endl;
            cout << to_string( LocationOfRoom.x) + " " + to_string(LocationOfRoom.y) << endl;
        }
        else if (event.type == Event::MouseButtonReleased) {
            click = true;
        }
        #pragma endregion RoomPlacement

        #pragma region Gameloop
        hungerdrain = 0.1 * numberofworkers;
        currentHunger -= hungerdrain;

        powerdrain = 0.1 * numberofrooms;
        currentPower -= powerdrain;

        oxegyendrian = 0.1 * numberofworkers;
        currentOxygen -= oxegyendrian;
        for (int j = 0; j < 100; j++) {
            CargoHold.spawn(window);

            LocationOfRoom = room[j].desplayLocation(MouseFolllowor, click);
            room[j].returnClick(MouseFolllowor);
            room[j].spawn(window);
            if (room[j].Output(worker[j].getLocation()) >0 && room[j].getType() == 0 && currentOxygen<totalOxygen) {
                currentOxygen += room[j].Output(worker[j].getLocation());
            }
            else if (room[j].Output(worker[j].getLocation()) > 0 && room[j].getType() == 1 && currentPower < totalPower) {
                currentPower += room[j].Output(worker[j].getLocation());
            }
            else if(room[j].Output(worker[j].getLocation()) > 0 && room[j].getType() == 2 && currentHunger < totalHunger) {
                currentHunger += room[j].Output(worker[j].getLocation());
            }
            
            WorkerMenuMethods(WorkerMenu.tabClick(MouseFolllowor, click));
            BuildMenuMethods(BuildMenu.tabClick(MouseFolllowor, click));
            MinigameMethods(MinigameMenu.tabClick(MouseFolllowor, click));

            worker[j].spawn(window);
            worker[j].moveToRoom(CargoHold.getLocation());
            worker[j].Output();
            workerData[j] = worker[j].saveTheData();
        }

        window.draw(outObar);
        window.draw(innerObar);
        window.draw(outPbar);
        window.draw(innerPbar);
        window.draw(outHbar);
        window.draw(innerHbar);

        MinigameMenu.drawMenu(window);
        BuildMenu.drawMenu(window);
        WorkerMenu.drawMenu(window);
        #pragma endregion Gameloop

        #pragma region defineMouse
        MouseFolllowor.setPosition(Mouse::getPosition().x - 475, Mouse::getPosition().y - 70);
        MouseFolllowor.setRadius(10);
        window.draw(MouseFolllowor);
        #pragma endregion defineMouse
        window.display();
    }
    return 0;

    if (Keyboard::isKeyPressed(Keyboard::Space)) {
    }
}