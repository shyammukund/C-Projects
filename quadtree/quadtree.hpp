#pragma once

#include "point.hpp"
#include <vector>
#include <queue>
#include <iostream>
#include <tuple>
#include <cmath>
#include <cassert>
using namespace std;

string quadString(const int quad);

const int NE = 0;
const int NW = 1;
const int SE = 2;
const int SW = 3;

struct Region 
{
    Point p;
    vector<pair<Point, Point>> quads;
    vector<Point> children;
};


// Class to create a QuadTree Node

 class QTreeNode {
 public:
    Point pt;
    double x;
    double y;

    QTreeNode* nw;
    QTreeNode* ne;
    QTreeNode* sw;
    QTreeNode* se;

    QTreeNode(const Point &p)
        :pt(p), x(p.x), y(p.y), nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr)
    {
        //empty
    }
 };

 class QuadTree{

 private:
    QTreeNode* root;
    Point rootLL;
    Point rootUR;

    vector<Point> searchResults;

    // inserting points into the quad tree
    QTreeNode* insertHelp(QTreeNode* root, Point point ){
        if (root == nullptr){
            root = new QTreeNode(point);
            return root;
        }

        queue<QTreeNode*> q;
        q.push(root);
        while (!q.empty()){
            QTreeNode* current = q.front();
            q.pop();
            if (point.x >= current->x && point.y >= current->y){
                if (current->ne == nullptr){
                    current->ne = new QTreeNode(point);
                    return root;
                }
                else{
                    q.push(current->ne);
                }
            }
            else if (point.x < current->x && point.y >= current->y){
                if(current->nw == nullptr){
                    current->nw = new QTreeNode(point);
                    return root;
                }
                else{
                    q.push(current->nw);
                }
                
            }
            else if (point.x >= current->x && point.y < current->y){
                if (current->se == nullptr){
                    current->se = new QTreeNode(point);
                    return root;
                }
                else{
                    q.push(current->se);
                }
            }
            else if (point.x < current->x && point.y < current->y){
                if (current->sw == nullptr){
                    current->sw = new QTreeNode(point);
                    return root;
                }
                else{
                    q.push(current->sw);
                }
            }
        }
        return root;

    }

    // returns true if current node is within the search rectangle
    bool contains(const QTreeNode* node, Point& lL, Point& uR)
    {
        return (node->pt.x >= lL.x && node->pt.x <= uR.x) &&
                (node->pt.y >= lL.y && node->pt.y <= uR.y);
    }

    pair<Point, Point> getQuadBound(QTreeNode* current, const Point& ll, const Point& ur, int quad) {
        if (quad == NW) {
             return {Point {ll.x,current->pt.y}, Point{current->pt.x,ur.y} };
        }
        if (quad == NE) {
            return {current->pt, ur};
        }
        if (quad == SW) {
            return {ll, current->pt};
        }
        if (quad == SE) {
            return { Point{current->pt.x, ll.y},  Point{ur.x, current->pt.y}};
        }
        
        assert(false);
        pair<Point, Point> p;
        return p;
        
    }    

    // search pts represents the rectangle boundary. cBound pts rep the area owned by the current pt.
    void searchHelp(QTreeNode* root, Point searchLL, Point searchUR, Point cBoundLL, Point cBoundUR){ 
        
        if (root == nullptr){
            return;
        }

        QTreeNode* current = root;
        if (contains(current,searchLL,searchUR)){
            searchResults.push_back(current->pt);
        }

        if (current->ne != nullptr){
            searchHelp(current->ne,searchLL,searchUR,current->pt,cBoundUR);
        }
        
        if (current->nw != nullptr){
            Point nwLower (cBoundLL.x, current->pt.y);
            Point nwUpper (current->pt.x,cBoundUR.y);
            searchHelp(current->nw,searchLL,searchUR,nwLower,nwUpper);
        }

        if (current->se != nullptr){
            Point seLower (current->pt.x, cBoundUR.y); 
            Point seUpper (cBoundUR.x,current->pt.y);
            searchHelp(current->se,searchLL,searchUR,seLower,seUpper);
        }

        if (current->sw != nullptr){
            searchHelp(current->sw,searchLL,searchUR,cBoundLL,current->pt);
        }

    }

    vector< pair<int,int> > 
    searchOrder(QTreeNode* node,  const Point& q, const Point& ll, const Point& ur)
    {
        // vector of pairs.
        // pair:  quadrant number, sq of min distance from query point
        vector<pair<int,int>> order;
        int curQuad = -1;
        // make the first element the quadrant of q
        if (q.x >= node->x && q.y >= node->y){ // NE
            curQuad = NE;
        }
        else if (q.x < node->x && q.y >= node->y){
            curQuad = NW;
        }
        else if (q.x >= node->x && q.y < node->y){
            curQuad = SE;
        }
        else if (q.x < node->x && q.y < node->y){
            curQuad = SW ;
        }
        else {
            assert(false);
        }
        order.push_back(pair{curQuad,0});

        int x_dist = pow(abs(node->pt.x - q.x),2);
        int y_dist = pow(abs(node->pt.y - q.y),2);
        int longest_dist = x_dist + y_dist;

        if (curQuad == NW) {
            if (x_dist > y_dist){
                order.push_back(pair{SW,y_dist});
                order.push_back(pair{NE,x_dist});
                order.push_back(pair{SE,longest_dist});
            }
            else if (x_dist <= y_dist){
                order.push_back(pair{NE,x_dist});
                order.push_back(pair{SW,y_dist});
                order.push_back(pair{SE,longest_dist});
            }
        }
        else if (curQuad == NE) {
            if (x_dist > y_dist){
                order.push_back(pair{SE,y_dist});
                order.push_back(pair{NW,x_dist});
                order.push_back(pair{SW,longest_dist});
            }
            else if (x_dist <= y_dist){
                order.push_back(pair{NW,x_dist});
                order.push_back(pair{SE,y_dist});
                order.push_back(pair{SW,longest_dist});
            }
        }
        else if (curQuad == SW) {
            if (x_dist > y_dist){
                order.push_back(pair{NW,y_dist});
                order.push_back(pair{SE,x_dist});
                order.push_back(pair{NE,longest_dist});
            }
            else if (x_dist <= y_dist){
                order.push_back(pair{SE,x_dist});
                order.push_back(pair{NW,y_dist});
                order.push_back(pair{NE,longest_dist});
            }
        }
        else if (curQuad == SE) {
            if (x_dist > y_dist){
                order.push_back(pair{NE,y_dist});
                order.push_back(pair{SW,x_dist});
                order.push_back(pair{NW,longest_dist});
            }
            else if (x_dist <= y_dist){
                order.push_back(pair{SW,x_dist});
                order.push_back(pair{NE,y_dist});
                order.push_back(pair{NW,longest_dist});
            }
        }
        return order;
    }

    void kNearestNeighborsHelper(QTreeNode* node1, 
                                 const Point& ll, const Point& ur, 
                                 priority_queue<pair<double,Point>>& maxPQ, 
                                 const Point& pt, 
                                 int k)
    {
        QTreeNode* current = node1;
        if (current == nullptr){
            return;
        }
        
        double x_sq = (current->pt.x - pt.x) * (current->pt.x - pt.x);
        double y_sq = (current->pt.y - pt.y) * (current->pt.y - pt.y);
        double dist = sqrt(x_sq + y_sq);
        

        if (maxPQ.size() < static_cast<size_t>(k))
        {
            maxPQ.push(pair{dist, current->pt});   
        }
        else
        {
            if (dist < maxPQ.top().first){
                maxPQ.pop();
                maxPQ.push(pair{dist, current->pt});
            }
        }

        // vector of pairs.
        // pair:  quadrant number, sq of dist
        vector<pair<int,int>> order = searchOrder(current,pt,ll,ur);

       

        for (auto& ele: order){
            double minDist = sqrt(ele.second);
            if ( maxPQ.size() >= static_cast<size_t>(k) && minDist > maxPQ.top().first ) 
            {
                continue;
            }

            if (ele.first == NW ) {
                auto bounds = getQuadBound(current, ll, ur, ele.first);
                kNearestNeighborsHelper(current->nw,
                                        Point {ll.x,current->pt.y}, 
                                        Point{current->pt.x,ur.y}, 
                                        maxPQ, pt, k);
            }
            else if (ele.first == NE ) {
                auto bounds = getQuadBound(current, ll, ur, ele.first);

                kNearestNeighborsHelper(current->ne, current->pt, ur, maxPQ, pt, k);
            }
            else if (ele.first == SW ){
                auto bounds = getQuadBound(current, ll, ur, ele.first);
                kNearestNeighborsHelper(current->sw, ll, current->pt, maxPQ,pt,k);
            }
            else if (ele.first == SE){
                auto bounds = getQuadBound(current, ll, ur, ele.first);
                kNearestNeighborsHelper(current->se,
                                        Point{current->pt.x, ll.y}, 
                                        Point{ur.x, current->pt.y},
                                        maxPQ, pt, k);
            }
            else {
                assert(false);
            }

        }
    }


    void printNodeDetails(QTreeNode* node){
        
        cout << "Node: " << "(" << node->x << "," << node->y << ")" << endl;
        if (node->ne != nullptr){
            cout << "NE Child: " << "(" << node->ne->x << "," << node->ne->y << ")" << endl;
        }
        else{
            cout << "Node does not have NE Child" << endl;
        }

        if (node->nw != nullptr){
            cout << "NW Child: " << "(" << node->nw->x << "," << node->nw->y << ")" << endl;
        }
        else{
            cout << "Node does not have NW Child" << endl;
        }
        
        if (node->se != nullptr){
            cout << "SE Child: " << "(" << node->se->x << "," << node->se->y << ")" << endl;
        }
        else{
            cout << "Node does not have SE Child" << endl;
        }

        if (node->sw != nullptr){
            cout << "SW Child: " << "(" << node->sw->x << "," << node->sw->y << ")" << endl;
        }
        else{
            cout << "Node does not have SW Child" << endl;
        }
        cout<<endl;
    }

    // breadth first traversal of the quad tree
     void printHelp(QTreeNode* root){
        queue<QTreeNode*> q;
        q.push(root);
        while (!q.empty()){
            QTreeNode* current = q.front();
            q.pop();
            if (current != nullptr){
                printNodeDetails(current);
                q.push(current->ne);
                q.push(current->nw);
                q.push(current->se);
                q.push(current->sw);
            }
             
        } 
        cout << endl;
    }

    void destroyTree(QTreeNode* node){
        if (node != nullptr){
            destroyTree(node->ne);
            destroyTree(node->nw);
            destroyTree(node->se);
            destroyTree(node->sw);
            delete node;  
        }
    }
 public: 
    
    QuadTree(const Point& LL, const Point& UR){
        root = nullptr;
        this->rootLL = LL;
        this->rootUR = UR;
    }

    ~QuadTree(){
        destroyTree(root);
    }

    QuadTree(const Point& LL, const Point& UR, vector<Point>& points)
        : root{nullptr}, rootLL{LL}, rootUR{UR}
    {
        for (Point& p: points){
            insert(p);
        }
    }

    void insert(Point pt){
        root = insertHelp(root,pt);
    }

    vector<Point> rectRangeSearch(Point searchLL, Point searchUR){
        //Point lb (0,0);
        //Point ub (1000,1000);
        searchHelp(root, searchLL, searchUR, rootLL, rootUR); 
        return searchResults;
    }

    vector<Point> kNearestNeighbor(int k, Point p){
        if ( k == 0){
            return {};
        }
        priority_queue<pair<double,Point>> pq;
        vector<Point> result;
        //Point ll {0,0};
        //Point ur {1000,1000};
        kNearestNeighborsHelper(root, rootLL, rootUR, pq, p, k);

        cout << "Final k nearest neighbors:" << endl;
        while(!pq.empty()){
            Point current= pq.top().second;
            pq.pop();
            result.push_back(current);
        }
        reverse(result.begin(),result.end());
        return result; 
    }




    void print(){
        printHelp(root);
    }

    vector<Point> getPointbyDFS() const {
        vector<Point> result {{100, 300}, {200, 400}, {10, 20}, {800, 900}};
        return result;
    }

    void GetPointsAndRegions(std::vector<Region> &regions) const
    {
        collectPointsAndRegions(root, rootLL, rootUR, regions);
    }

    
    void collectPointsAndRegions(QTreeNode *node, const Point &LL, const Point &UR, std::vector<Region> &regions) const
    {
        if (!node)
            return;

        Region region;
        region.p = node->pt;

        vector<QTreeNode*> children {node->ne, node->nw, node->sw, node->se};
        for (int i = 0; i < 4; ++i)
        {
            if (children[i]) 
            {
                region.children.push_back(children[i]->pt);     // Add the child point to the children vector
                region.quads.push_back({LL, UR});               // Add the region to the quads vector
            }
        }

        regions.push_back(region);
        if (children[0])
            collectPointsAndRegions(children[0], node->pt, UR, regions); // NE
        if (children[1])
            collectPointsAndRegions(children[1], Point(LL.x, node->pt.y), Point(node->pt.x, UR.y), regions); // NW
        if (children[2])
            collectPointsAndRegions(children[2], LL, node->pt, regions); // SW
        if (children[3])
            collectPointsAndRegions(children[3], Point(node->pt.x, LL.y), Point(UR.x, node->pt.y), regions); // SE
    }


 };

