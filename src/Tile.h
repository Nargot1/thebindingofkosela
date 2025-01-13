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
    Tile() = default;
    Tile(sf::Vector2i &pos_in, TileType type_in, int width, int height);
    Tile(sf::Vector2i &pos_in, TileType type_in, int width, int height,WallDirection dir);
    void Draw(sf::RenderWindow &window) const;
    TileType GetType() const;
    sf::FloatRect GetRect() const;
private:
    static constexpr int size = 64;
    sf::FloatRect rect;

    TileType type = TileType::Empty;
    WallDirection wallDirection = WallDirection::None;

    sf::RectangleShape rectShape;
};