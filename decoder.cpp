#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;

decoder::decoder(const PNG & tm, pair<int,int> s):start(s),mapImg(tm) {
   /* YOUR CODE HERE */
   this->start = s;
   this->mapImg = tm;
   renderMaze(); // render the maze to set maze distances
}

PNG decoder::renderSolution(){

/* YOUR CODE HERE */
   return PNG();
}

PNG decoder::renderMaze(){
   PNG maze_render(this->mapImg);

   unsigned int height = this->mapImg.height();
   unsigned int width = this->mapImg.width();

   int start_x = this->start.first;
   int start_y = this->start.second;

   vector<vector<bool>> visited(height, vector<bool>(width, false));
   Queue<pair<int,int>> queue;
   vector<vector<int>> distance(height, vector<int>(width, 0));

   visited.at(start_y).at(start_x) = true;
   queue.enqueue(this->start);

   while (!queue.isEmpty()) {
        // get pixel
        pair<int,int> curr = queue.dequeue();
        int curr_distance = distance.at(curr.second).at(curr.first);

        vector<pair<int,int>> ns = neighbors(curr);
        for (size_t i=0; i < ns.size(); i++) {
            pair<int,int> neighbor = ns.at(i);
            if (decoder::good(visited, distance, curr, neighbor)) {
               // if its good, it will be visited at some point
               visited.at(neighbor.second).at(neighbor.first) = true;
               distance.at(neighbor.second).at(neighbor.first) = curr_distance + 1;
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

   this->maze = visited;
   this->distances = distance;

   return maze_render;
}

void decoder::setGrey(PNG & im, pair<int,int> loc){
   int x = loc.first;
   int y = loc.second;

   RGBAPixel* pixel = im.getPixel(x, y);
    
   pixel->r = 2 * (pixel->r/4);
   pixel->g = 2 * (pixel->g/4);
   pixel->b = 2 * (pixel->b/4);
}

pair<int,int> decoder::findSpot(){
   int treasure_x = -1;
   int treasure_y = -1;
   int max_distance = -1;

   for (unsigned int y = 0; y < this->maze.size(); y++) { // go through each row
      for (unsigned int x = 0; x < this->maze[y].size(); x++) { // go through each column
         if (maze.at(y).at(x) && this->distances.at(y).at(x) > max_distance) {
               max_distance = this->distances.at(y).at(x);
               treasure_x = x;
               treasure_y = y;
         }
      }
   }

   pair<int,int> treasure_location;
   treasure_location.first = treasure_x;
   treasure_location.second = treasure_y;

   return treasure_location;
}

int decoder::pathLength(){
   pair<int, int> treasure_location = findSpot();
   int treasure_x = treasure_location.first;
   int treasure_y = treasure_location.second;

   if (treasure_x == -1 || treasure_y == -1) {
      return -1;
   }

   return distances[treasure_y][treasure_x];
}

bool decoder::good(vector<vector<bool>> & v, vector<vector<int>> & d, pair<int,int> curr, pair<int,int> next){
   // same as treasureMap?
   unsigned long height = v.size();
   unsigned long width = v.at(0).size();

   unsigned long x = next.first;
   unsigned long y = next.second;

   // check if in image bounds
   bool within_x = (0 <= x) && (x < width);
   bool within_y = (0 <= y) && (y < height);
   bool within_bounds = within_x && within_y;

   bool unvisited = false;
   bool encoded = false;

   if (within_bounds){
      // check if unvisisted
      unvisited = !v.at(y).at(x);

      // check if follows encoding pattern
      RGBAPixel* next_pixel = this->mapImg.getPixel(x, y);
      encoded = this->compare(*next_pixel, d.at(curr.second).at(curr.first));
      // was previously d[y]d[x]
   }

   return unvisited && encoded;
}

vector<pair<int,int>> decoder::neighbors(pair<int,int> curr) {
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


bool decoder::compare(RGBAPixel p, int d){
   int p_val = (p.r % 4)*16 + (p.g % 4)*4 + (p.b % 4);
   return (p_val == (d + 1) % 64);
}
