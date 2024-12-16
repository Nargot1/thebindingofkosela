#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include "Floor.h"
#include "Room.h"
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
    for (int i = 0; i < root->ChildElementCount(); i++)
    {
        std::vector<Room> rooms;
        for (int i = 0; i < root->ChildElementCount(); i++)
        {
            XMLElement* node = currFloor->FirstChildElement();
            int width = node->FindAttribute("width")->IntValue();
            int height = node->FindAttribute("height")->IntValue();

            std::vector<sf::Vector2<int>> doors;
            std::vector<int> doorsId;
            std::vector<sf::Vector2<int>> stones;

            XMLElement* element = node->FirstChildElement();
            int eWidth = element->FindAttribute("x")->IntValue();
            int eHeight = element->FindAttribute("y")->IntValue();
            if (element->Name() == "Doors")
            {
                doors.push_back({ eWidth,eHeight });
                doorsId.push_back(element->FindAttribute("id")->IntValue());
            }
            else if (element->Name() == "Stone")
            {
                stones.push_back({ eWidth,eHeight });
            }

            XMLElement* nextElement = element->NextSiblingElement();
            for (int i = 0; i < node->ChildElementCount() - 1; i++)
            {
                int eWidth = nextElement->FindAttribute("x")->IntValue();
                int eHeight = nextElement->FindAttribute("y")->IntValue();
                if (nextElement->Name() == "Doors")
                {
                    doors.push_back({ eWidth,eHeight });
                    doorsId.push_back(element->FindAttribute("id")->IntValue());
                }
                else if (nextElement->Name() == "Stone")
                {
                    stones.push_back({ eWidth,eHeight });
                }
                nextElement = nextElement->NextSiblingElement();
            }
            rooms.push_back(Room(width, height, stones, doors, doorsId));
        }
        floors.push_back(Floor(rooms));
        currFloor = currFloor->NextSibling();
    }


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


        Floor& currFloor = floors.at(0);
        currFloor.Draw(window);

        window.display();
    }
}
