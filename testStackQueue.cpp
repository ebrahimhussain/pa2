#define CATCH_CONFIG_MAIN
#include <iostream>
#include "cs221util/catch.hpp"
#include "stack.h"
#include "queue.h"
//using namespace cs221util;
using namespace std;

TEST_CASE("stack::basic functions","[weight=1][part=stack]"){
    cout << "Testing Stack..." << endl;
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intStack.push(i);
    }
    while (!intStack.isEmpty()) {
        result.push_back(intStack.pop());
    }
    REQUIRE( result == expected);
    cout << "Stack passed" << endl;
}
TEST_CASE("stack:test 2","[weight=1][part=stack2]") {

    cout << endl << "------------ TEST 2 " << endl << endl;
    Stack<int> stack;
    
    int s = 1;
    int l = 9;
    for (int k = s; k <= l; k++) {
        stack.push(k);
    }
    for (int k = s; k <= l; k++) {
        stack.pop();
        cout << endl;
    }

    REQUIRE(true == true);

    cout << endl << "------------ TEST 2 DONE " << endl << endl;
}
TEST_CASE("queue::basic functions","[weight=1][part=queue]"){
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intQueue.enqueue(i);
    }
    while (!intQueue.isEmpty()) {
        // cout << "is it empty yet?" << endl;
        result.push_back(intQueue.dequeue());
    }
    REQUIRE( result == expected);
    cout << "Queue passed" << endl;
}

