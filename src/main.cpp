#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include "Floor.h"
#include "Room.h"
#include "Kosela.h"
#include "Dummy.h"
#include <vector>

using namespace tinyxml2;

int main()
{
    auto window = sf::RenderWindow({1920u, 1080u}, "The Binding of Kosela");
    window.setFramerateLimit(60);

    std::vector<Floor> floors;
    
    FILE* file = fopen("../Rooms.xml", "rb");

    XMLDocument doc;
    doc.LoadFile(file);
    XMLNode* root = doc.FirstChildElement("Game");
    XMLNode* currFloor = root->FirstChildElement();
    for (int i = 0; i < root->ChildElementCount()-1; i++)
    {
        std::vector<Room> rooms;
        XMLElement* node = currFloor->FirstChildElement();
        for (int i = 0; i < root->ChildElementCount(); i++)
        {
            std::vector<sf::Vector2<int>> doors;
            std::vector<int> doorsId;
            std::vector<sf::Vector2<int>> stones;

            
            int width = node->FindAttribute("width")->IntValue();
            int height = node->FindAttribute("height")->IntValue();

            XMLElement* nextElement = node->FirstChildElement();
            for (int i = 0; i < node->ChildElementCount() - 1; i++)
            {
                std::vector<sf::Vector2<int>> doors;
                std::vector<int> doorsId;
                std::vector<sf::Vector2<int>> stones;

                int eWidth = nextElement->FindAttribute("x")->IntValue();
                int eHeight = nextElement->FindAttribute("y")->IntValue();
                std::string name = nextElement->Name();
                if (name == "Doors")
                {
                    doors.push_back({ eWidth,eHeight });
                    doorsId.push_back(node->FindAttribute("id")->IntValue());
                }
                else if (name == "Stone")
                {
                    stones.push_back({ eWidth,eHeight });
                }
                nextElement = nextElement->NextSiblingElement();
                rooms.push_back(Room(width, height, stones, doors, doorsId));
            }
            node = node->NextSiblingElement();
        }
        floors.push_back(Floor(rooms));
        currFloor = currFloor->NextSibling();
    }

    Kosela kosela;

    Dummy dummy;

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
        

        Floor* currFloor = &floors.at(0);

        kosela.update();

        currFloor->ActiveRoomPlayerCollision(kosela);



        currFloor->Draw(window);
        dummy.draw(window, sf::RenderStates::Default);
        kosela.draw(window,sf::RenderStates::Default);

        window.display();
    }
}
