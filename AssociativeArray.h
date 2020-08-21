/*
  Notes:

  1. To be fair to the humble array, once nesting (the means to hold arrays within arrays) became common place, the map
     class was inevitable.  

     The test that follows defines a simple set of short, sharp functions showing a means to handle otherwise complex virtual data
     structures in a human readable way.

  Required:

     AssociativeArray.cpp
     AssociativeArrayInclusions.cpp

  Usage:

     See AssociativeArray.cpp main()

  Alexander Munro - January 26, 2020

*/

// include guard
#pragma once

#ifndef ASSOCIATIVEARRAY_H
#define ASSOCIATIVEARRAY_H

class mapTableClass 
{

    public:

        struct mapTable 
        {

            std::string col_1;
            std::string col_2;
            int col_3;

            mapTable(std::string col1, std::string col2, int col3)
            {
                col_1 = col1;
                col_2 = col2;
                col_3 = col3;
            };
        };

        static void buildTestHarness(); // build the associative array test harness and display results

    private:

        static int mapTableRowInsert(bool bSeekOrphans, std::string col1, std::string col2, int col3); // returns integer key value
        static int mapTableRowUpdate(int key, std::string col1, std::string col2, int col3); // returns 0
        static int mapTableRowErase(int key); // returns 0
        static int mapTableRowKey(bool bSeekOrphans); // returns next available integer key value (seeks orphans if true) 

        static void mapTableRowBulkTest(bool bSeekOrphans, int uBound); // inserts array rows between 1 and uBound
        static void displayRows(); // lists all array elements
};

#endif ASSOCIATIVEARRAY_H

