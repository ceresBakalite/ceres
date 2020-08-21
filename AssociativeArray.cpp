// AssociativeArray.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
  Notes:

  1. What follows are a simple set of short, sharp functions showing a means to handle otherwise complex virtual data 
     structures in a human readable way.

  Required:

    AssociativeArray.h
    AssociativeArrayInclusions.cpp

  Usage:

    See main()

  Alexander Munro - January 26, 2020

*/

#include <iostream>
#include "AssociativeArray.h"

int main()
{
    mapTableClass arObj;

    // build the associative array and display test results
    arObj.buildTestHarness();

    return 0;
};