#define CATCH_CONFIG_MAIN

#include <iostream>
#include <limits.h>
#include <sys/stat.h>
#include <vector>

#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"
#include "cs221util/catch.hpp"

#include "decoder.h"
#include "treasureMap.h"

using namespace std;
using namespace cs221util;


#define IMAGEDIR "images/"
#define SOLNIMGDIR "soln_images/"

/**
 * Test Cases
 * these are just examples of a logical flow similar to 
 * that of main.cpp. We suggest decoupling the embedding
 * tests from the decoding tests, but we leave it to you
 * to do so.
 */


// TEST_CASE("treasureMap::gray test", "[weight=1][part=treasure_grayed]")
// {
//     PNG maze;
//     maze.readFromFile("images/snake.png");
//     pair<int, int> start(1, 1);
//     PNG base;
//     base.readFromFile("images/sunshine.png");

//     cout << "making map" << endl;
//     treasureMap M(base, maze, start);
//     PNG map_gray = M.renderMaze();
//     map_gray.writeToFile("images/maze_test_out.png");

//     REQUIRE(true == true);
// }


// TEST_CASE("treasureMap::basic no cycles", "[weight=1][part=treasureMap]")
// {

// 	PNG maze;
// 	maze.readFromFile("images/snake.png");
// 	pair<int,int> start(1,1);

//     PNG base;
//     base.readFromFile("images/sunshine.png");

//     treasureMap M(base, maze, start);

//     PNG treasure = M.renderMap();
// 	treasure.writeToFile("images/embeddedsnake_out.png");
//     PNG treasureans;
//     treasureans.readFromFile("images/embeddedsnake.png");
//     REQUIRE( treasure == treasureans );

//     PNG treasuremaze = M.renderMaze();
// 	//treasuremaze.writeToFile("images/greyedsnake.png");
//     PNG treasuremazeans;
// 	treasuremazeans.readFromFile("images/greyedsnake.png");
//     REQUIRE( treasuremaze == treasuremazeans );

//     decoder dec(treasure,start);

//     PNG soln = dec.renderSolution();
//     //soln.writeToFile("images/solnsnake.png");
//     PNG solnans;
//     solnans.readFromFile("images/solnsnake.png");
//     REQUIRE( soln == solnans );

//     PNG solnmaze = dec.renderMaze();
//     //solnmaze.writeToFile("images/solnsnakemaze.png");
//     PNG solnmazeans;
//     solnmazeans.readFromFile("images/solnsnakemaze.png");
//     REQUIRE( solnmaze == solnmazeans );

// }

TEST_CASE("decoder::basic cycles", "[weight=1][part=decoder]")
{
    // MAKE EMBEDDED TREASUREMAP
	PNG maze;
	maze.readFromFile("images/maze.png");
	pair<int,int> start(1,1);
    PNG base;
    base.readFromFile("images/sunshine.png");
    treasureMap M(base, maze, start);

    PNG treasure = M.renderMap(); // make hidden
    PNG treasureans;
    treasureans.readFromFile("images/embeddedmaze.png");
    // TEST1: MAKE SURE TREASUREMAP HIDDEN WORKS
    cout << "test1: make sure treasuremap hidden works" << endl;
    REQUIRE( treasure == treasureans );

    PNG treasuremaze = M.renderMaze();
    PNG treasuremazeans;
	treasuremazeans.readFromFile("images/greyedmaze.png");
    // TEST2 MAKE SURE GRAY WORKS
    cout << "test2: make sure treasuremap gray works" << endl;
    REQUIRE( treasuremaze == treasuremazeans );

    cout << "hidden r: " << (int) treasure.getPixel(2, 1)->r << endl;
    cout << "base r: " << (int)base.getPixel(2, 1)->r << endl;

    decoder dec(treasure,start);


    cout << "test3: make sure decoder gray works" << endl;
    PNG solnmaze = dec.renderMaze();
    solnmaze.writeToFile("images/solnmazemaze_out.png");
    PNG solnmazeans;
    solnmazeans.readFromFile("images/solnmazemaze.png");

    REQUIRE( solnmaze == solnmazeans );

    
    // PNG soln = dec.renderSolution();
    // //soln.writeToFile("images/solnmaze.png");
    // PNG solnans;
    // solnans.readFromFile("images/solnmaze.png");
    // REQUIRE( soln == solnans );

}


