#pragma region imports
#include <SFML/Graphics.hpp> 
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

#include <SFML/Audio.hpp>
#include <random>
#include <String>
#include <cstdlib>
#include <windows.h>
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

#define winWidth1 1100
#define winHeight1 1000

// define game render window size constants - Justin Simpson
#define winWidth 736
#define winHeight 552

Menus MinigameMenu;
Menus WorkerMenu;
Menus BuildMenu;

int steel = 80;
int t = 0;
int workernumber = 0;
int roomnumber = 0;
int numberofrooms = 0;
int numberofworkers = 0;

bool paused = false;
bool buildup = false;
bool click = true;

Rooms room[100];
Workers worker[100];
//vector <Rooms> room;
//vector <Workers> worker;
//Rooms myroom;
//Workers myworker;
Rooms CargoHold;

RenderWindow window(sf::VideoMode(winWidth1, winHeight1), "Main");

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

#pragma region astriod 
// A C++ SFML program with falling asteroids and a moving spaceship - Justin Simpson

const int NUM_FRAMES = 8; // Number of frames in the explosion animation
const int FRAME_WIDTH = 64; // Width of each frame in the explosion sprite sheet
const int FRAME_HEIGHT = 64; // Height of each frame in the explosion sprite sheet
// Function to display the Game Over screen
void displayGameOverScreen(sf::RenderWindow& windw)
{
	// Load font
	Font font;
	if (!font.loadFromFile("myFont.ttf")) {
		std::cout << "Error loading font!" << std::endl;
	}

	// Clear the window to black
	windw.clear(Color::Black);

	// Create the game over text
	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setString("Game Over!");
	gameOverText.setCharacterSize(40);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setStyle(sf::Text::Bold);

	// Set the position of the texts
	sf::Vector2u windowSize = windw.getSize();
	gameOverText.setPosition((windowSize.x - gameOverText.getLocalBounds().width) / 2, (windowSize.y - gameOverText.getLocalBounds().height) / 2);

	// Draw the texts
	windw.draw(gameOverText);

	// Display the window
	windw.display();

	while (true)
	{
		sf::Event event;
		while (windw.pollEvent(event))
		{
			// Closes the window
			if (event.type == Event::Closed)
				windw.close();
		}
	}
}

// Function to display the Game Over screen
void displayWinScreen(sf::RenderWindow& windw)
{
	// Load font
	Font font;
	if (!font.loadFromFile("myFont.ttf")) {
		std::cout << "Error loading font!" << std::endl;
	}

	// Clear the window to black
	windw.clear(Color::Black);

	// Create the You Won text
	Text winText;
	winText.setFont(font);
	winText.setString("You Won!");
	winText.setCharacterSize(40);
	winText.setFillColor(sf::Color::Blue);
	winText.setStyle(sf::Text::Bold);

	// Set the position of the texts
	sf::Vector2u windowSize = windw.getSize();
	winText.setPosition((windowSize.x - winText.getLocalBounds().width) / 2, (windowSize.y - winText.getLocalBounds().height) / 2);

	// Draw the texts
	windw.draw(winText);

	// Display the window
	windw.display();

	// Wait for the player to press space
	while (true)
	{
		sf::Event event;
		while (windw.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				windw.close();
		}
	}
}

void Asteroids() {
	// Create game the window - Justin Simpson
	RenderWindow winow(VideoMode(winWidth, winHeight), "Asteroids!");

	// Defining the score and setting it to 0
	int score = 0;

	// Set the framerate limit to 60 FPS
	winow.setFramerateLimit(60);

	// Texture set up
	Texture tex_background, tex_spaceship, tex_asteroid, tex_bullet, tex_scrapMetal, explosionTexture;
	tex_background.loadFromFile("stars.png");
	tex_spaceship.loadFromFile("spaceship.png");
	tex_asteroid.loadFromFile("asteroid.png");
	tex_bullet.loadFromFile("bullet.png");
	tex_scrapMetal.loadFromFile("scrapMetal.png");

	// Set up each sprite (Position, scale etc.)
	Sprite spr_background, spr_asteroid, spr_bullet, spr_spaceship, spr_scrapMetal, explosionSprite;

	spr_background.setTexture(tex_background);

	spr_spaceship.setTexture(tex_spaceship);
	spr_spaceship.scale(Vector2f(0.15f, 0.15f));
	spr_spaceship.setPosition(Vector2f(winWidth / 3, winHeight / 1.5)); // absolute position

	spr_asteroid.setTexture(tex_asteroid);
	spr_asteroid.scale(Vector2f(0.15f, 0.15f));
	spr_asteroid.setPosition(Vector2f(winWidth / 2, winHeight / 2));

	spr_bullet.setTexture(tex_bullet);
	spr_bullet.scale(Vector2f(0.15f, 0.15f));

	spr_scrapMetal.setTexture(tex_scrapMetal);
	spr_scrapMetal.scale(Vector2f(0.1f, 0.1f));

	explosionSprite.setTexture(explosionTexture);
	explosionSprite.setOrigin(FRAME_WIDTH / 2, FRAME_HEIGHT / 2); // Set the origin to the center of the sprite

	// Create a clock to track the elapsed time for the animation
	Clock clock;

	// Set up explosion sound
	SoundBuffer buffer;
	if (!buffer.loadFromFile("explosion.wav")) {
		// Error loading sound file
	}

	Sound explosionSound;
	explosionSound.setBuffer(buffer);

	// Set up dead sound
	SoundBuffer buffer1;
	if (!buffer1.loadFromFile("dead.wav")) {
		// Error loading sound file
	}

	Sound dead;
	dead.setBuffer(buffer1);

	// Set up metal sound
	SoundBuffer buffer2;
	if (!buffer2.loadFromFile("metal.wav")) {
		// Error loading sound file
	}

	Sound metal;
	metal.setBuffer(buffer2);

	// Set up custom font
	Font font;
	if (!font.loadFromFile("myFont.ttf")) {
		//cout << "Error loading font!" << endl;
	}

	// Set up sprite vectors
	vector<Sprite> asteroid;
	vector<Sprite> bullets;
	vector<Sprite> scrapMetal;

	// Gets the size of the window
	Vector2f spritePosition = spr_bullet.getPosition();

	// Set the time value to 0
	Time elapsedTime;

	// Run the program as long as the window is open
	while (winow.isOpen())
	{
		// Check all the window's events that were triggered since the last iteration of the loop
		Event event;
		while (winow.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				winow.close();
		}

		winow.clear();

		// Spaceship moves left when left key is pressed
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			spr_spaceship.setPosition(spr_spaceship.getPosition().x - 4, spr_spaceship.getPosition().y);
		}

		// Spaceship moves right when right key
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			spr_spaceship.setPosition(spr_spaceship.getPosition().x + 4, spr_spaceship.getPosition().y);
		}

		// Spaceship moves up when up key is pressed
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			spr_spaceship.move(0.0f, -4.0f);
		}

		// Spaceship moves down when down key is pressed
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			spr_spaceship.move(0.0f, 4.0f);
		}

		// Used to detect the width and height of the spaceship
		sf::Vector2f spaceshipPos = spr_spaceship.getPosition();
		const float spaceshipWidth = spr_spaceship.getGlobalBounds().width;
		const float spaceshipHeight = spr_spaceship.getGlobalBounds().height;

		// Check if the spaceship is outside the left side of the screen
		if (spaceshipPos.x < 0) {
			spr_spaceship.setPosition(0, spaceshipPos.y);
		}

		// Check if the spaceship is outside the right side of the screen
		if (spaceshipPos.x + spaceshipWidth > winWidth) {
			spr_spaceship.setPosition(winWidth - spaceshipWidth, spr_spaceship.getPosition().y);
		}

		// Check if the spaceship is outside the top side of the screen
		if (spaceshipPos.y < 0) {
			spr_spaceship.setPosition(spaceshipPos.x, 0);
		}

		// Check if the spaceship is outside the bottom side of the screen
		if (spaceshipPos.y + spaceshipHeight > winHeight) {
			spr_spaceship.setPosition(spr_spaceship.getPosition().x, winHeight - spaceshipHeight);
		}

		// clear the window with black color
		winow.clear(Color::Black);

		// Draw everything here...
		winow.draw(spr_background);
		winow.draw(spr_spaceship);

		// Set the min and max
		float min = 10;
		float max = 25;

		// Adds a new element at the end of the vector, after its current last element
		asteroid.push_back(Sprite(spr_asteroid));

		// Used to generate random numbers between 0.1 and 0.3
		float size = 0.1 + (rand() / (float)RAND_MAX) * 0.2;

		// Sets the next asteroids in the vectors radius to less than 6
		asteroid.back().setScale(size, size);

		// Set lastBullet to -1
		int lastBullet = -1;

		// Adds a new element at the end of the vector, after its current last element
		bullets.push_back(Sprite(spr_bullet));

		// Allows asteroids to constantly fall
		for (size_t i = 0; i < asteroid.size(); i++)
		{
			// set removed to 0
			size_t removed = 0;

			// A while loop to remove asteroids to prevent them from all coming down at once
			while (asteroid.size() - removed > 75)
			{
				// Remove a quarter of the asteroids from the vector
				asteroid.erase(asteroid.begin() + asteroid.size() / 4, asteroid.end());
				removed += asteroid.size() / 4;
			}

			// Allows the asteroids to have the swaying motion 
			asteroid[i].rotate(rand() % 3);

			// Sets the position of the next asteroids randomly across the top of the screen
			asteroid.back().setPosition(rand() % winWidth, -200);

			// Allows the asteroids to move down
			asteroid[i].move(0, 1);

			// If asteroids exit the bottom of the screen, remove them
			if (asteroid[i].getPosition().y > winHeight + 50) {

				// Remove the asteroid from the vector
				asteroid.erase(asteroid.begin() + i);
			}

			// Draws the asteroids according to the positon of i
			winow.draw(asteroid[i]);

			// Allows bullets to constantly shoot
			for (size_t j = lastBullet + 1; j < bullets.size(); j++)
			{
				// Sets the position of the next bullets to shoot from the ship
				bullets.back().setPosition(spr_spaceship.getPosition().x + 43, spr_spaceship.getPosition().y);

				// Draws the bullets according to j and allows the bullets to move
				winow.draw(bullets[j]);
				bullets[j].move(0, -4);

				// If a bullet collides with an asteroid
				if (Collision::PixelPerfectTest(bullets[j], asteroid[i])) {

					// Add a new scrap metal sprite to the vector
					scrapMetal.push_back(Sprite(spr_scrapMetal));

					// Set the position of the scrap metal sprite to the position of the destroyed asteroid
					scrapMetal.back().setPosition(asteroid[i].getPosition());

					// Play the explosion sound
					explosionSound.play();

					// Erase an asteroid once destroyed and decrement
					asteroid.erase(asteroid.begin() + i);
					j--;
				}

				// Remove bullets if they exit the screen (prevents lag)
				bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
					[&](const sf::Sprite& spr_bullet)
					{
						sf::Vector2u screenSize = winow.getSize();
				sf::Vector2f spritePosition = spr_bullet.getPosition();
				return spritePosition.x > screenSize.x || spritePosition.y > screenSize.y ||
					spritePosition.x < 0 || spritePosition.y < 0;
					}), bullets.end());

				// If spaceship collides with an asteroid
				if (Collision::PixelPerfectTest(spr_spaceship, asteroid[i])) {
					dead.play();

					// Displays game over screen
					//displayGameOverScreen(winow);
					winow.close();
				}
			}
		}

		// Update the index of the last bullet added to the game
		lastBullet = bullets.size() - 1;

		// Creates pieces of scrap metal
		for (int i = 0; i < scrapMetal.size(); i++) {

			// Move the scrap metal downwards and draws it
			scrapMetal[i].move(0, 2);
			winow.draw(scrapMetal[i]);

			// Check for a collision between the spaceship and the scrap metal
			if (Collision::PixelPerfectTest(spr_spaceship, scrapMetal[i])) {

				// Increment the score
				score++;
				steel++;

				metal.play();

				// Remove the scrap metal from the game and decrement
				scrapMetal.erase(scrapMetal.begin() + i);
				i--;
			}
		}

		// If the score reaches 50, Display the Win screen
		if (score == 50) {
			//displayWinScreen(winow);
			winow.close();
		}

		// Display the score on the screen
		sf::Text text;
		text.setFont(font); // Set the font for the text
		text.setString("Score: " + std::to_string(score)); // Set the text to display the current score
		text.setCharacterSize(45.0f); // Set the character size
		text.setFillColor(sf::Color::White); // Set the text color
		winow.draw(text); // Draw the text on the screen

		// end the current frame
		winow.display();

		elapsedTime = clock.getElapsedTime();
	}
}

#pragma endregion astriod 

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

	MyReasourseWriteFile << currentOxygen << "\n";
	MyReasourseWriteFile << currentHunger << "\n";
	MyReasourseWriteFile << currentPower << "\n";
	MyReasourseWriteFile << steel << "\n";
	MyReasourseWriteFile.close();

	string ah;

	for (int j = 0; j < numberOfWorkers; j++) {
		MyWorkerWriteFile << workerData[j] << "\n";
	}
	MyWorkerWriteFile.close();
	string ds;
	for (int j = 0; j < numberOfRooms; j++) {
		ds = room[j].saveData();
		MyRoomWriteFile << ds << "\n";
		//cout << ds << endl;
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
	int stuffarraye[5];
	int roomNum = 0;
	int workerNum = 0;
	int ResourseNum = 0;
	while (getline(MyWorkerReadFile, h)) {
		worker[workerNum].loadFile(h, window);
		workerNum++;
	}
	while (getline(MyRoomReadFile, n)) {
		room[roomNum].loadFile(n, window);
		roomNum++;
	}
	while (getline(MyResoursesReadFile, l)) {
		stuffarraye[ResourseNum] = stoi(l);
		ResourseNum++;
	}
	numberofrooms += roomNum;
}

#pragma region menuMethods
void MinigameMethods(int num) {
	switch (num) {
	case 1:
		Asteroids();
		break;
	}
}
void WorkerMenuMethods(int num) {
	switch (num) {
	case 1:
		worker[numberofworkers].setnumber(numberofworkers);
		worker[numberofworkers].setLocation(CargoHold.getLocation());
		workernumber = worker[numberofworkers].getnumber();
		worker[numberofworkers].setRoom(room[1].getLocation());
		numberofworkers++;
		cout << numberofworkers << " numberofworkers" << endl;
		cout << workernumber << " workernumber" << endl;
		break;
	case 2:
		cout << "2";
		break;
	case 3:
		cout << "3";
		break;
	}
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
	CargoHold.setLocation(Vector2f(winWidth1 / 2, winHeight1 / 2));
	CargoHold.setFillColor(Color(255, 255, 255));
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
			steel += 10;
		}
		if (Keyboard::isKeyPressed(Keyboard::G)) {
			gridview(window);
		}
		if (Keyboard::isKeyPressed(Keyboard::O)) {
			LocationOfRoom = room[numberofrooms].desplayLocation(MouseFolllowor, click);
			cout << LocationOfRoom.x  << "  " << LocationOfRoom.y << endl;
		}
		if (Keyboard::isKeyPressed(Keyboard::Q)) {
			saveStuff(numberofrooms, numberofworkers);
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			loadstuff();
		}
#pragma endregion buttonStuff

#pragma region roomplacement
		bool here = false;
		bool roomhere = false;
		bool elevator = false;
		int x = MouseFolllowor.getPosition().x;
		int y = MouseFolllowor.getPosition().y;
		for (int j = 0; j < 100; j++) {
			if (CargoHold.getLocation() == Vector2f((MouseFolllowor.getPosition().x - (x % 100)) - 100, MouseFolllowor.getPosition().y - (y % 100)) || room[j].getLocation() == Vector2f((MouseFolllowor.getPosition().x - (x % 100)) - 100, MouseFolllowor.getPosition().y - (y % 100))) {
				here = true;
			}
			else if (CargoHold.getLocation() == Vector2f((MouseFolllowor.getPosition().x - (x % 100)) + 100, MouseFolllowor.getPosition().y - (y % 100)) || room[j].getLocation() == Vector2f((MouseFolllowor.getPosition().x - (x % 100)) +100, MouseFolllowor.getPosition().y - (y % 100))) {
				here = true;
			}
			else if (room[j].getLocation() == Vector2f((MouseFolllowor.getPosition().x - (x % 100)), MouseFolllowor.getPosition().y - (y % 100) - 100) || CargoHold.getLocation() == Vector2f((MouseFolllowor.getPosition().x - (x % 100)), MouseFolllowor.getPosition().y - (y % 100) - 100)) {
				here = true;
			}
			else if (room[j].getLocation() == Vector2f((MouseFolllowor.getPosition().x - (x % 100)), MouseFolllowor.getPosition().y - (y % 100) + 100) || CargoHold.getLocation() == Vector2f((MouseFolllowor.getPosition().x - (x % 100)), MouseFolllowor.getPosition().y - (y % 100) + 100)) {
				here = true;
			}
			if (room[j].getLocation() == Vector2f(MouseFolllowor.getPosition().x - (x % 100), MouseFolllowor.getPosition().y - (y % 100))) {
				roomhere = true;
			}

			if (MouseFolllowor.getPosition().x - (x % 100) == CargoHold.getLocation().x) {
				elevator = true;
			}
			else {
				elevator = false;
			}
		}
		if (steel >= 10 && here == true && roomhere == false) {
				if (Keyboard::isKeyPressed(Keyboard::Num1) && elevator == false) {
					room[numberofrooms].setLocation(MouseFolllowor.getPosition());
					room[numberofrooms].determinType(0, CargoHold.getLocation().x);
					steel -= 10;
					numberofrooms++;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Num1) && elevator == true) {
					room[numberofrooms].setLocation(MouseFolllowor.getPosition());
					room[numberofrooms].determinType(3, CargoHold.getLocation().x);
					steel -= 10;
					numberofrooms++;
				}
				if (Keyboard::isKeyPressed(Keyboard::Num2) && elevator == false) {
					room[numberofrooms].setLocation(MouseFolllowor.getPosition());
					room[numberofrooms].determinType(1, CargoHold.getLocation().x);
					steel -= 10;
					numberofrooms++;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Num2) && elevator == true) {
					room[numberofrooms].setLocation(MouseFolllowor.getPosition());
					room[numberofrooms].determinType(3, CargoHold.getLocation().x);
					steel -= 10;
					numberofrooms++;
				}
				if (Keyboard::isKeyPressed(Keyboard::Num3) && elevator == false) {
					room[numberofrooms].setLocation(MouseFolllowor.getPosition());
					room[numberofrooms].determinType(2, CargoHold.getLocation().x);
					steel -= 10;
					numberofrooms++;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Num3) && elevator == true) {
					room[numberofrooms].setLocation(MouseFolllowor.getPosition());
					room[numberofrooms].determinType(3, CargoHold.getLocation().x);
					steel -= 10;
					numberofrooms++;
				}
			}
		
#pragma endregion roomplacement
#pragma region clickarea
		if (event.type == Event::MouseButtonPressed && click) {
			click = false;
			WorkerMenuMethods(WorkerMenu.tabClick(MouseFolllowor));
			MinigameMethods(MinigameMenu.tabClick(MouseFolllowor));
			BuildMenu.tabClick(MouseFolllowor);
			LocationOfRoom = MouseFolllowor.getPosition();
			//worker[workernumber].setRoom(LocationOfRoom);
			Vector2f aplace = Vector2f(MouseFolllowor.getPosition().x - (x % 100), MouseFolllowor.getPosition().y - (y % 100));
			worker[workernumber].setRoom(aplace);
			workernumber++;
		}
		else if (event.type == Event::MouseButtonReleased) {
			click = true;
		}
#pragma endregion clickarea

#pragma region Gameloop
		hungerdrain = 0.001 * numberofworkers;
		if (currentHunger > 0) {
			currentHunger -= hungerdrain;
		}
		powerdrain = 0.001 * numberofrooms;
		if (currentPower > 0) {
			currentPower -= powerdrain;
		}
		oxegyendrian = 0.001 * numberofworkers;
		if (currentOxygen > 0) {
			currentOxygen -= oxegyendrian;
		}
		CargoHold.spawn(window);
		for (int j = 0; j < 100; j++) {
			worker[j].moveToRoom(CargoHold.getLocation());
			workerData[j] = worker[j].saveTheData();

			workernumber = worker[j].desplaynumber(MouseFolllowor, click);
			//LocationOfRoom = room[j].desplayLocation(MouseFolllowor, click);

			room[j].spawn(window);
			worker[j].spawn(window);
			if (room[j].Output(worker[j].getLocation()) && room[j].getType() == 0 && currentOxygen < totalOxygen) {
				currentOxygen += 1;
				//cout << currentOxygen << endl;
			}
			else if (room[j].Output(worker[j].getLocation()) && room[j].getType() == 1 /*&& currentPower < totalPower*/) {
				currentPower += 1;
				cout << currentPower << endl;
			}
			else if (room[j].Output(worker[j].getLocation()) && room[j].getType() == 2 /*&& currentHunger < totalHunger*/) {
				currentHunger += 1;
				cout << currentHunger << endl;
			}
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
		MouseFolllowor.setPosition(Mouse::getPosition().x - 425, Mouse::getPosition().y - 80);
		MouseFolllowor.setRadius(10);
		window.draw(MouseFolllowor);
#pragma endregion defineMouse
		window.display();
	}
	return 0;
}