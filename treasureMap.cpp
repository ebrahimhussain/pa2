#include "treasureMap.h"
#include "queue.h"
using namespace std;

treasureMap::treasureMap(const PNG & baseim, const PNG & mazeim, pair<int,int> s)
{
    this->start = s;
    this->base = baseim;
    this->maze = mazeim;
}

void treasureMap::setGrey(PNG & im, pair<int,int> loc){

    int x = loc.first;
    int y = loc.second;

    RGBAPixel* pixel = im.getPixel(x, y);
    
    pixel->r = 2 * (pixel->r/4);
    pixel->g = 2 * (pixel->g/4);
    pixel->b = 2 * (pixel->b/4);
}

void treasureMap::setLOB(PNG & im, pair<int,int> loc, int d){

    int x = loc.first;
    int y = loc.second;

    RGBAPixel* pixel = im.getPixel(x, y);

    int rbits = ((d % 64) >> 4) & 0x03;
    int gbits = ((d % 64) >> 2) & 0x03;
    int bbits = (d % 64) & 0x03;

    pixel->r = (pixel->r & 0xFC) | rbits;
    pixel->g = (pixel->g & 0xFC) | gbits;
    pixel->b = (pixel->b & 0xFC) | bbits;

}

PNG treasureMap::renderMap(){

    PNG map_render(this->base);

    unsigned int height = this->maze.height();
    unsigned int width = this->maze.width();

    int start_x = this->start.first;
    int start_y = this->start.second;

    vector<vector<bool>> visited(height, vector<bool>(width, false));
    vector<vector<int>> distance(height, vector<int>(width, 0));
    Queue<pair<int,int>> queue;
    
    visited.at(start_y).at(start_x) = true;
    setLOB(map_render, this->start, 0);
    queue.enqueue(this->start);

    while (!queue.isEmpty()) {
        pair<int,int> curr = queue.dequeue();
        int curr_distance = distance.at(curr.second).at(curr.first);
        vector<pair<int,int>> ns = neighbors(curr);
        for (size_t i=0; i < ns.size(); i++) {
            pair<int,int> neighbor = ns.at(i);
            if (good(visited, curr, neighbor)) {
                visited.at(neighbor.second).at(neighbor.first) = true;
                distance.at(neighbor.second).at(neighbor.first) = curr_distance + 1;
                setLOB(map_render, neighbor, curr_distance + 1);
                queue.enqueue(neighbor);
            }
        }
    }

    return map_render;
}

// traverse and set gray
PNG treasureMap::renderMaze(){

    PNG maze_render(this->base);

    unsigned int height = this->maze.height();
    unsigned int width = this->maze.width();

    int start_x = this->start.first;
    int start_y = this->start.second;

    vector<vector<bool>> visited(height, vector<bool>(width, false));
    Queue<pair<int,int>> queue;
    
    visited.at(start_y).at(start_x) = true;
    queue.enqueue(this->start);

    while (!queue.isEmpty()) {
        // get pixel
        pair<int,int> curr = queue.dequeue();
        vector<pair<int,int>> ns = neighbors(curr);
        for (size_t i=0; i < ns.size(); i++) {
            pair<int,int> neighbor = ns.at(i);
            if (good(visited, curr, neighbor)) {
                // if its good, it will be visited at some point
                visited.at(neighbor.second).at(neighbor.first) = true;
                setGrey(maze_render, neighbor);
                queue.enqueue(neighbor);
            }
        }
    }

    int sx = (start_x-3 < 0)? 0: start_x-3;
    int bx = (start_x+3 > width)? width: start_x+3;
    int sy = (start_y-3 < 0)? 0: start_y-3;
    int by = (start_y+3 > height)? height: start_y+3;

    for (int x =sx; x <= bx; x++) {
        for (int y = sy; y <= by; y++) {
            RGBAPixel* pixel = maze_render.getPixel(x, y);
            pixel->r = 255;
            pixel->g = 0; 
            pixel->b = 0; 
        }
    }

    return maze_render;
}

bool treasureMap::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){
    unsigned long height = v.size();
    unsigned long width = v.at(0).size();

    unsigned long x = next.first;
    unsigned long y = next.second;

    // check if in image bounds
    bool within_x = (0 <= x) && (x < width);
    bool within_y = (0 <= y) && (y < height);
    bool within_bounds = within_x && within_y;

    bool unvisited = false;
    bool same_color = false;

    if (within_bounds){
        // check if unvisisted
        unvisited = !v.at(y).at(x);

        // check same color
        RGBAPixel* curr_maze_pixel = this->maze.getPixel(curr.first,curr.second);
        RGBAPixel* next_pixel = this->maze.getPixel(x, y);
        same_color = *curr_maze_pixel == *next_pixel;
    }

    return unvisited && same_color;
}

vector<pair<int,int>> treasureMap::neighbors(pair<int,int> curr) {
    vector<pair<int, int>> neighbors;
    int x = curr.first;
    int y = curr.second;
    pair<int,int> left(x-1, y);
    pair<int,int> below(x, y+1);
    pair<int,int> right(x+1, y);
    pair<int,int> above(x,y-1);
    neighbors.push_back(left);
    neighbors.push_back(below);
    neighbors.push_back(right);
    neighbors.push_back(above);
    return neighbors;
}

