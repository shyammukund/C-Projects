#include "display.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;
using std::endl;

void init_display(sf::RenderWindow &window)
{
    // Custom initialization logic if needed
}

void close_display(sf::RenderWindow &window)
{
    // Custom cleanup logic if needed
}

void clear_display(sf::RenderWindow &window)
{
    window.clear(sf::Color(245, 245, 245)); // Off-white background color
}

void draw_point(const Point &pt, sf::RenderWindow &window, const sf::Color &color)
{
    float size = 10.0f;              // Diameter of the point
    sf::CircleShape shape(size / 2); // Circle with radius size / 2
    shape.setFillColor(color);
    shape.setPosition(pt.x - size / 2, window.getSize().y - pt.y - size / 2); // Adjust position to center the point
    window.draw(shape);
}

void draw_line(const Point &start, const Point &end, sf::RenderWindow &window, const sf::Color &color)
{
    sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(start.x, window.getSize().y - start.y), color), // Invert y-coordinate
            sf::Vertex(sf::Vector2f(end.x, window.getSize().y - end.y), color)      // Invert y-coordinate
        };
    window.draw(line, 2, sf::Lines);
}

void draw_text(const std::string &text, float x, float y, sf::RenderWindow &window)
{
    sf::Font font;
    if (!font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf"))
    {
        std::cerr << "Error loading font\n";
        return;
    }

    sf::Text sf_text(text, font, 12);
    sf_text.setFillColor(sf::Color::Black);
    sf_text.setPosition(x, window.getSize().y - y); // Invert y-coordinate
    window.draw(sf_text);
}

void draw_rectangle(const Point &LL, const Point &UR, sf::RenderWindow &window,
                    const sf::Color &lineColor, const sf::Color &fillColor)
{
    sf::RectangleShape rectangle;
    rectangle.setPosition(sf::Vector2f(LL.x, window.getSize().y - UR.y)); // Set position to lower-left corner
    rectangle.setSize(sf::Vector2f(UR.x - LL.x, UR.y - LL.y));            // Set size based on width and height
    rectangle.setOutlineColor(lineColor);                                 // Set the outline color
    rectangle.setOutlineThickness(1);                                     // Set the thickness of the outline
    rectangle.setFillColor(fillColor);                                    // Set the fill color
    window.draw(rectangle);
}

void draw_circle(const Point &center, float radius, sf::RenderWindow &window, const sf::Color &color)
{
    sf::CircleShape circle(radius);
    circle.setFillColor(color);
    circle.setPosition(center.x - radius, window.getSize().y - center.y - radius); // Adjust for SFML coordinate system
    window.draw(circle);
}

void draw_arrow(const Point &start, const Point &end, sf::RenderWindow &window, const sf::Color &color)
{
    draw_line(start, end, window, color);

    sf::Vector2f direction(end.x - start.x, end.y - start.y);
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length;

    sf::Vector2f perpendicular(-direction.y, direction.x);
    float arrowSize = 8.0f;

    sf::ConvexShape arrowhead;
    arrowhead.setPointCount(3);
    arrowhead.setPoint(0, sf::Vector2f(end.x, window.getSize().y - end.y));
    arrowhead.setPoint(1, sf::Vector2f(end.x - arrowSize * direction.x + arrowSize * perpendicular.x, window.getSize().y - (end.y - arrowSize * direction.y + arrowSize * perpendicular.y)));
    arrowhead.setPoint(2, sf::Vector2f(end.x - arrowSize * direction.x - arrowSize * perpendicular.x, window.getSize().y - (end.y - arrowSize * direction.y - arrowSize * perpendicular.y)));
    arrowhead.setFillColor(color);

    window.draw(arrowhead);
}
