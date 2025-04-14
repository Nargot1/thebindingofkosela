#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include "Floor.h"
#include "Room.h"
#include "Kosela.h"
#include "Dummy.h"
#include <vector>
#include <string>
#include <iostream>

using namespace tinyxml2;

int main()
{
    auto window = sf::RenderWindow({ 1920u, 1080u }, "The Binding of Kosela");
    window.setFramerateLimit(60);

    std::vector<Floor*> floors;

    FILE* file = fopen("../Rooms.xml", "rb");

    XMLDocument doc;
    doc.LoadFile(file);
    XMLNode* root = doc.FirstChildElement("Game");
    XMLNode* currFloorNode = root->FirstChildElement();
    for (int i = 0; i < root->ChildElementCount(); i++)
    {
        std::vector<Room*> rooms;
        for (XMLElement* node = currFloorNode->FirstChildElement(); node != currFloorNode->LastChildElement()->NextSiblingElement(); node = node->NextSiblingElement())
        {
            std::vector<sf::Vector2<int>> doors;
            std::vector<int> doorsId;
            std::vector<sf::Vector2<int>> stones;
            sf::Vector2i spawn{ 0,0 };
            std::vector<Enemy*> enemies;

            int width = node->FindAttribute("width")->IntValue();
            int height = node->FindAttribute("height")->IntValue();

            XMLElement* nextElement = node->FirstChildElement();
            for (int i = 0; i < node->ChildElementCount(); i++)
            {
                int eWidth = nextElement->FindAttribute("x")->IntValue();
                int eHeight = nextElement->FindAttribute("y")->IntValue();
                std::string name = nextElement->Name();
                if (name == "Doors")
                {
                    doors.push_back({ eWidth,eHeight });
                    doorsId.push_back(nextElement->FindAttribute("id")->IntValue());
                }
                else if (name == "Stone")
                {
                    stones.push_back({ eWidth,eHeight });
                }
                else if (name == "Spawn")
                {
                    spawn = { eWidth,eHeight };
                }
                else if (name == "Dummy")
                {
                    enemies.push_back(new Dummy(sf::Vector2i{ eWidth,eHeight }));
                }

                nextElement = nextElement->NextSiblingElement();
            }
            rooms.push_back(new Room(width, height, stones, doors, doorsId, spawn, enemies));
        }
        floors.push_back(new Floor(rooms));
        currFloorNode = currFloorNode->NextSibling();
    }

    Floor* currFloor = floors.at(0);
    int ncurrFloor = 1;
    int nFloors = floors.size();
    Kosela kosela(currFloor->GetActiveRoom()->GetSpawn());

    sf::Font font;
    font.loadFromFile("../arial.ttf");

    sf::Text hpText;
    hpText.setFont(font);
    hpText.setCharacterSize(30);
    hpText.setFillColor(sf::Color::White);
    hpText.setPosition(20, 20);

    bool gameStarted = false;

    float logoSin = 0.0f;

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        if (gameStarted) {
            if (kosela.IsAlive()) {
                Room* activeRoom = currFloor->GetActiveRoom();
                kosela.update(activeRoom);

                currFloor->Update(kosela);

                if (currFloor->ActiveRoomPlayerCollision(kosela))
                {
                    if (ncurrFloor < nFloors)
                    {
                        ncurrFloor++;
                        currFloor = floors.at(ncurrFloor - 1);
                    }
                }
            }

            currFloor->Draw(window);
            kosela.draw(window, sf::RenderStates::Default);

            hpText.setString("HP: " + std::to_string(kosela.hp) + "/100");
            window.draw(hpText);

            if (!kosela.IsAlive()) {
                sf::Text gameOverText;
                gameOverText.setFont(font);
                gameOverText.setCharacterSize(72);
                gameOverText.setFillColor(sf::Color::Red);
                gameOverText.setString("GAME OVER");

                sf::FloatRect textRect = gameOverText.getLocalBounds();
                gameOverText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                gameOverText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

                window.draw(gameOverText);
            }
        }
        else
        {
            sf::Text startText;
			startText.setFont(font);
			startText.setCharacterSize(32);
			startText.setFillColor(sf::Color::White);
			startText.setString("Press Enter to Start");

			sf::FloatRect textRect = startText.getLocalBounds();
			startText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			startText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

            sf::Texture logo;
            logo.loadFromFile("../logo.png");
            sf::Sprite logoSprite;
            logoSprite.setTexture(logo);
            logoSprite.setScale(3.0f, 3.0f);
            sf::Vector2f pos = {std::sin(logoSin)*10,std::sin(logoSin)*10};
            logoSprite.setPosition(window.getSize().x / 2.0f - logo.getSize().x*3 / 2.0f, window.getSize().y / 2.0f - logo.getSize().y*3 / 2.0f - 100+ pos.y);

            sf::Texture bomb;
            bomb.loadFromFile("../bombaanimacja.png",sf::IntRect{0,0,50,30});
            sf::Sprite bombSprite;
            bombSprite.setTexture(bomb);
            bombSprite.setScale(5.0f, 5.0f);
            bombSprite.setPosition(window.getSize().x / 2.0f - bombSprite.getScale().x / 2.0f + 450, window.getSize().y / 2.0f - bombSprite.getScale().y / 2.0f -350 + pos.y * -1);
            bombSprite.rotate(35);

            sf::Texture dummy;
            dummy.loadFromFile("../Dummy.png");
            sf::Sprite dummySprite;
            dummySprite.setTexture(dummy);
            dummySprite.setScale(7.0f, 7.0f);
            dummySprite.setPosition(window.getSize().x / 2.0f - dummySprite.getScale().x / 2.0f -800, window.getSize().y / 2.0f - dummySprite.getScale().y / 2.0f + 100);
            dummySprite.rotate(-35);

            logoSin += 0.02f;    

			window.draw(startText);
            window.draw(bombSprite);
            window.draw(logoSprite);
            window.draw(dummySprite);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				gameStarted = true;
			}
        }
        window.display();
    }

    for (auto& floor : floors) {
        delete floor;
    }
    floors.clear();

    return 0;
}

