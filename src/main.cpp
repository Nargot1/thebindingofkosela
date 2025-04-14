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

        window.display();
    }

    for (auto& floor : floors) {
        delete floor;
    }
    floors.clear();

    return 0;
}

