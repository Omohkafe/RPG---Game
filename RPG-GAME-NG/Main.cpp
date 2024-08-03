#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

sf::Vector2f NormalizeVector(sf::Vector2f vector){

	float m = std::sqrt(vector.x * vector.x + vector.y * vector.y);

	sf::Vector2f normalizedVector;
	normalizedVector.x = vector.x / m;
	normalizedVector.y = vector.y / m;

	return normalizedVector;
};


int main() {

	// -------------------------- INITIZALIING ---------------------------------------
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(1010, 600), "RPG - GAME", sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close, settings);

	sf::Event event;
	// -------------------------- INITIZALIING ---------------------------------------


	// -------------------------- BULLET ---------------------------------------------
	
	std::vector<sf::RectangleShape> bullets; 
	float bulletSpeed = 1.05f; 
	

	// -------------------------- PLAYER ----------------------------------------------
	sf::Texture PlayerTexture;
	sf::Sprite PlayerSprite;

	if (PlayerTexture.loadFromFile("Assets/Player/Textures/spreadsheet.png")) {
		PlayerSprite.setTexture(PlayerTexture);
		PlayerSprite.setPosition(sf::Vector2f(50.f, 90.f));
		//PlayerSprite.setScale(sf::Vector2f(0.1f, 0.1f));


		unsigned short int IndexX = 2;
		unsigned short int IndexY = 1;

		std::cout << "Player loaded!" << std::endl;
		PlayerSprite.setTextureRect(sf::IntRect(IndexX * 72, IndexX * 0, 72, 86));
	}else {
		std::cout << "can't load player!" << std::endl;
	};

	// ------------------------ PLAYER -----------------------------------------------

		

	// ------------------------ SAMURAI ----------------------------------------------

	sf::Texture SamuraiTexture;
	sf::Sprite SamuraiSprite;

	if (SamuraiTexture.loadFromFile("Assets/Samurai/Textures/SamuraiEnemy.png")) {
		
		SamuraiSprite.setTexture(SamuraiTexture);
		SamuraiSprite.setPosition(sf::Vector2f(730.f, 345.f)); 
		//SamuraiSprite.setScale(sf::Vector2f(0.1f, 0.1f)); 

		unsigned short int XIndex = 1;
		unsigned short int YIndex = 1;

		std::cout << "enemy loaded!" << std::endl;
		SamuraiSprite.setTextureRect(sf::IntRect(XIndex * 128, YIndex * 1, 128, 128));

	}else{
		std::cout << "cant load image from file" << std::endl;
	};

	// ------------------------ SAMURAI ----------------------------------------------



	// -------------------------- Main Game Loop --------------------------------------
	// -------------------------- UPDATE ----------------------------------------------
	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window.close();
			}

		}

		// ---------------------- calculate the direction of the bullet -----------------
		//bullet.setPosition(bullet.getPosition() + bulletDirection * bulletSpeed); 

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			
			bullets.push_back(sf::RectangleShape(sf::Vector2f(20, 5)));
			bullets[bullets.size() - 1].setPosition(PlayerSprite.getPosition());

		};
	
		for (size_t i{ 0 }; i < bullets.size(); i++) {
			
			sf::Vector2f  bulletDirection = SamuraiSprite.getPosition() - bullets[i].getPosition();
			bulletDirection = NormalizeVector(bulletDirection);
			bullets[i].setPosition(bullets[i].getPosition() + bulletDirection * bulletSpeed); 
		}

		sf::Vector2f position = PlayerSprite.getPosition(); 

		// ------------------------- PLAYER DIRECTION TO THE RIGHT -----------------------
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		PlayerSprite.setPosition(position + sf::Vector2f(4, 0)); 

		// ------------------------- PLAYER DIRECTION TO THE LEFT ------------------------
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		PlayerSprite.setPosition(position + sf::Vector2f(-4, 0));

		// ------------------------- PLAYER DIRECTION TO THE UP --------------------------
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		PlayerSprite.setPosition(position + sf::Vector2f(0, -4));

		// ------------------------- PLAYER DIRECTION TO THE DOWN ------------------------
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			PlayerSprite.setPosition(position + sf::Vector2f(0, 4));


		window.clear(sf::Color::Black);
		window.draw(PlayerSprite);
		window.draw(SamuraiSprite); 

		for (size_t i{ 0 }; i < bullets.size(); i++) {
			window.draw(bullets[i]);
		}

		window.display();

	};


	return 0;
}