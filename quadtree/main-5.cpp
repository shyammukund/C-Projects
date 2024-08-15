#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <cassert>
#include <SFML/Graphics.hpp>
#include <fstream>

#include "point.hpp"
#include "display.h"
#include "quadtree.hpp"


using namespace sf;
using namespace std;

void printMenu(){
    vector<string> menu { "[I]nsert", "[P]rint Quadtree", "[R]ectangle Range Search", "[K]Nearest Neighbors", 
                  "[V]isualize", "[C]oordinates", "[Q]uadrants","[T]ree", "[E]xit" };
    cout << "\nQuadtree" << endl;
    for (auto& m : menu) {
        cout << m << endl;
    }
    cout << "Choose: ";
}
 
void visualize_qt(const QuadTree &qt, sf::RenderWindow &window, bool drawRegions, bool drawEdges, bool showCoordinates,
                  bool drawQueryRectangle, const Point &queryLL, const Point &queryUR,
                  bool drawQueryNeighbor, const Point &queryNeighbor, const std::vector<Point> &queryNeighborResults)
{
    //cout << "visuale_qt called \n";
    vector<Region> regions;

    qt.GetPointsAndRegions(regions);

    clear_display(window);

    // Draw nodes and their connections
    for (const auto &region : regions)
    {
        draw_circle(region.p, 5, window, sf::Color::Red);

        if (showCoordinates)
        {
            draw_text("(" + std::to_string(int(region.p.x)) + ", " + std::to_string(int(region.p.y)) + ")", region.p.x + 5, region.p.y, window);
        }

        if (drawRegions)
        {
            //cout << "Draw Regions\n";
            for (const auto &quad : region.quads)
            {
                //cout << "draw quadrants\n";
                draw_line(Point(region.p.x, quad.first.y), Point(region.p.x, quad.second.y), window);
                draw_line(Point(quad.first.x, region.p.y), Point(quad.second.x, region.p.y), window);
            }
        }

        if (drawEdges)
        {
            sf::Color Brown(165, 42, 42);
            for (const auto &child : region.children)
            {
                draw_arrow(region.p, child, window, Brown);
            }
        }
    }

    if (drawQueryRectangle)
    {
        draw_rectangle(queryLL, queryUR, window, sf::Color::Magenta, sf::Color::Transparent);
    }

    if (drawQueryNeighbor)
    {
        Point LL(queryNeighbor.x - 5, queryNeighbor.y - 5);
        Point UR(queryNeighbor.x + 5, queryNeighbor.y + 5);
        draw_rectangle(LL, UR, window, sf::Color::Transparent, sf::Color::Blue);

        for (const Point &p : queryNeighborResults)
        {
            draw_circle(p, 5, window, sf::Color(0, 100, 0));
        }
    }

    window.display();
}


void readPoints(char* name,vector<Point> &pts){
    string fileName{name};
    ifstream infile(fileName);
    double x, y;
    while (infile >> x >> y){
        pts.push_back(Point{x,y});
    }
}

int main(int argc, char* argv[]){

    if (argc > 2){
        cout << "Usage:: " << argv[0] << "To many arguments " << endl;
        cout << "Usage: " << argv[0] << " <input file>" << endl;
        return -1;
    }

    vector<Point> pts;
    if (argc > 1) {
        readPoints(argv[1],pts);
    }
    const int MAX_H = 800;
    const int MAX_W = 800;

    QuadTree tree (Point{0,0}, Point{MAX_W, MAX_H},pts);
    RenderWindow window; 

    bool showVisual = false;
    bool needsRedraw = false;
    bool showCoordinates = false;
    bool drawRegions = false;
    bool drawEdges = false;

    Point queryLL, queryUR;
    Point queryPoint;
    bool drawQueryRectangle = false;

    bool drawQueryNeighbor = false;
    Point queryNeighbor;
    vector<Point> kNeighbors;

    
    while (true){
        printMenu();
        char input;
        cin >> input;
        

        
        if (input == 'I' || input == 'i')
        {
            double x, y;
            cout << "Enter point (x y): ";
            cin >> x >> y;
            Point pt (x,y);
            tree.insert(pt);
            needsRedraw = true;
        }
        else if (input == 'P' || input == 'p'){
            tree.print();
        }
        else if (input == 'K' || input == 'k'){
            int k; 
            cout << "Enter your location : ";
            cin >> queryNeighbor.x >> queryNeighbor.y;
            cout << "Enter the number of neighbors you want to find: ";
            cin >> k;
            kNeighbors = tree.kNearestNeighbor(k,queryNeighbor);
            for (Point& p: kNeighbors){
                cout << p << endl;
            }
            drawQueryNeighbor = true;
            needsRedraw = true;
        }
        else if (input == 'V' || input == 'v'){
            showVisual = !showVisual;
            if (!showVisual && window.isOpen()){
                window.close();
                cout << "Window closing\n";
                showVisual = false;
                needsRedraw = false;
                showCoordinates = false;
                drawRegions = false;
                drawEdges = false;
                drawQueryRectangle = false;
                drawQueryNeighbor = false;
            }
            else if (showVisual && !window.isOpen()){
                needsRedraw = true;
                window.create(sf::VideoMode(MAX_W,MAX_H), "Quadtree Visual");
                init_display(window);
            }
        } 
        else if (input == 'R' || input == 'r'){

            cout << "Enter lower left point of the search Rectangle: " << endl;
            cin >> queryLL.x >> queryLL.y; 

            cout << "Enter upper right point of the search Rectangle: " << endl;
            cin >> queryUR.x >> queryUR.y;
            

            vector<Point> result = tree.rectRangeSearch(queryLL, queryUR);
            for (Point r: result){
                cout << "(" << r.x << "," << r.y << ")" << " " << endl;
            }
            drawQueryRectangle = true; // Set flag to draw the query rectangle
            needsRedraw = true;        // Mark the display for redraw

        }
        else if (input == 'C' || input == 'c'){
            showCoordinates = !showCoordinates;
            needsRedraw = true;
        } 
        else if (input == 'T' || input == 't') {
            drawEdges = !drawEdges;
            needsRedraw = true;
        }
        else if (input == 'E' || input == 'e'){
            cout << "Program Over" << endl;
            if (window.isOpen()){
                close_display(window);
            }
            break;
        }
        else if (input == 'Q' || input == 'q') {
            drawRegions = !drawRegions;
            needsRedraw = true;
        }
        else {
            cout << "Invalid Command Entered" << endl;
        }

    
        
        // Graphics processing loop
        if (showVisual && window.isOpen() && needsRedraw) {

            visualize_qt( tree, window,drawRegions, drawEdges, showCoordinates, drawQueryRectangle, 
                          queryLL, queryUR, drawQueryNeighbor,queryNeighbor, kNeighbors);
            needsRedraw = false;
            drawQueryNeighbor = false;
            drawQueryRectangle = false;
        }

        if (showVisual && window.isOpen()){
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    cout << "Polling ShowVisual" << showVisual << endl;
                    showVisual = false;
                }
            }

        } 

    }
    return 0;
}

