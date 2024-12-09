#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include "Floor.h"
#include "Room.h"
#include <vector>

using namespace tinyxml2;

int main()
{
    auto window = sf::RenderWindow({1920u, 1080u}, "The Binding of Kosela",sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    std::vector<Floor> floors;
    std::vector<Room> rooms;

    FILE* fil;
    fil = fopen("Rooms.xml", "r");

    XMLDocument doc;
    doc.LoadFile(fil);
    XMLNode* root = doc.RootElement();
    for (int i = 0; i < root->ChildElementCount(); i++)
    {
        XMLElement* node = root->FirstChildElement();
        int width = node->FindAttribute("wdith")->IntValue();
        int height = node->FindAttribute("height")->IntValue();

        std::vector<sf::Vector2<int>> doors;
        std::vector<int> doorsId;
        std::vector<sf::Vector2<int>> stones;
        XMLElement* element = node->FirstChildElement();
        int eWidth = element->FindAttribute("width")->IntValue();
        int eHeight = element->FindAttribute("height")->IntValue();
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
            int eWidth = nextElement->FindAttribute("width")->IntValue();
            int eHeight = nextElement->FindAttribute("height")->IntValue();
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
        floors.push_back(Floor(rooms));
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
        window.display();
    }
}
