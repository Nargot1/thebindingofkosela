#pragma once
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>

class Tile {
public:
    enum class TileType
    {
        Empty,
        Wall,
        Blocked,
        Doors
    };
    enum class WallDirection
    {
        None,
        Left,
        Right,
        Top,
        Bottom,
        TopLeftCorner,
        BotLeftCorner,
        TopRightCorner,
        BotRightCorner,
    };

public:
    Tile(sf::Vector2f &pos_in, TileType type_in);
    Tile(sf::Vector2f &pos_in, TileType type_in, WallDirection dir);
    void Draw(sf::RenderWindow &window) const;
private:
    static constexpr int size = 16;
    sf::FloatRect rect;

    TileType type = TileType::Empty;
    WallDirection wallDirection = WallDirection::None;

    sf::RectangleShape rectShape;
};