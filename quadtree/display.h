#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "point.hpp"

// Initializes the display
void init_display(sf::RenderWindow &window);

// Closes the display
void close_display(sf::RenderWindow &window);

// Clears the display
void clear_display(sf::RenderWindow &window);

// Draws a point
void draw_point(const Point &pt, sf::RenderWindow &window, const sf::Color &color);

// Draws a line
void draw_line( const Point &start, const Point &end, sf::RenderWindow &window, 
                const sf::Color &color = sf::Color::Blue);

// Draws text label
void draw_text(const std::string &text, float x, float y, sf::RenderWindow &window);

// Draws a rectangle
void draw_rectangle(const Point &LL, const Point &UR, sf::RenderWindow &window,
                    const sf::Color &lineColor = sf::Color::Transparent,
                    const sf::Color &fillColor = sf::Color::Black);

// Draws a circle
void draw_circle(const Point &center, float radius, 
                 sf::RenderWindow &window, const sf::Color &color);

// Draws an arrow
void draw_arrow(const Point &start, const Point &end, sf::RenderWindow &window, 
                const sf::Color &color = sf::Color::Blue);
