/*
  Notes:

  1. To be fair to the humble array, once nesting (the means to hold arrays within arrays) became common place, the map
     class was inevitable.  Whether it adds, or for that matter simplifies, a great deal towards the art of array
     manipulation is open to debate.

     What follows are a simple set of short, sharp functions showing a means to handle otherwise complex virtual data
     structures in a human readable way.

  Required:

      1. map<int, mapTable> mapTableRow;
      2. map<int, mapTable>::iterator mapItr
      3. mapTableRowInsert(bool bSeekOrphans, std::string col1, std::string col2, int col3)
      4. mapTableRowUpdate(int key, std::string col1, std::string col2, int col3)
      5. mapTableRowErase(int key)
      6. mapTableRowKey(bool bSeekOrphans)
      7. buildTestHarness()
      8. mapTableRowBulkTest(bool bSeekOrphans, int uBound)
      9. displayRows()

      AssociativeArray.h
      AssociativeArray.cpp

  Usage:

      See main()

  Alexander Munro - January 26, 2020

*/

// include guard
#pragma once

#include <iostream>
#include <string>
#include <map>

#include "AssociativeArray.h"

namespace mapRow
{
    std::map<int, mapTableClass::mapTable>::iterator mapItr;
    std::map<int, mapTableClass::mapTable> mapTableRow;
};

using namespace mapRow;

int mapTableClass::mapTableRowInsert(bool bSeekOrphans, std::string col1, std::string col2, int col3)
{
    int key = mapTableRowKey(bSeekOrphans);
    mapTableRow.insert({ key, mapTable(col1, col2, col3) });

    return key;
};

int mapTableClass::mapTableRowUpdate(int key, std::string col1, std::string col2, int col3)
{
    mapItr = mapTableRow.find(key);

    if (mapItr != mapTableRow.end())
    {
        mapItr->second.col_1 = col1;
        mapItr->second.col_2 = col2;
        mapItr->second.col_3 = col3;
    };

    return 0;
};

int mapTableClass::mapTableRowErase(int key)
{
    if (mapTableRow.find(key) == mapTableRow.end()) return 0;

    // drop element by key
    mapTableRow.erase(key);

    return 0;
};

int mapTableClass::mapTableRowKey(bool bSeekOrphans)
{
    // establish a default key value
    int key = mapTableRow.size() + 1;

    if (bSeekOrphans)
    {
        int uBound = key;

        for (key = 1; key < uBound; key++)
        {
            if (mapTableRow.find(key) == mapTableRow.end()) return key;
        };
    };

    return key;
};

void mapTableClass::buildTestHarness()
{
    bool bSeekOrphans = true; // attempt to fill rows where a key is missing
    int uBound = 240;  // the number of rows to add to the bulk test set

    std::cout << "\nPopulate the array and capture two key values\n" << std::endl;

    mapTableRowInsert(bSeekOrphans, "aaa", "AA", 11);
    mapTableRowInsert(bSeekOrphans, "bbb", "BB", 22);
    int key1 = mapTableRowInsert(bSeekOrphans, "ccc", "CC", 33);
    mapTableRowInsert(bSeekOrphans, "ddd", "DD", 44);
    int key2 = mapTableRowInsert(bSeekOrphans, "eee", "EE", 55);
    mapTableRowInsert(bSeekOrphans, "fff", "FF", 66);

    displayRows();

    std::cout << "Update two array elements by referencing the captured key values\n" << std::endl;

    mapTableRowUpdate(key1, "UPDATE_FIRST_ROW", "CCC", -33);
    mapTableRowUpdate(key2, "UPDATE_SECOND_ROW", "EEE", -55);

    displayRows();

    std::cout << "Delete two array elements using the same key values\n" << std::endl;

    mapTableRowErase(key1);
    mapTableRowErase(key2);

    displayRows();

    std::cout << "Setting bSeekOrphans to true, insert three new array elements\n" << std::endl;

    mapTableRowInsert(bSeekOrphans, "REPLACE_ROW", "TEST", -999000);
    mapTableRowInsert(bSeekOrphans, "REPLACE_ROW", "TEST", -800000);
    mapTableRowInsert(bSeekOrphans, "NEW_ROW", "GG", 77);

    displayRows();

    std::cout << "Create a larger array. Set bSeekOrphans to false. Each new row will now be inserted incrementally at the end of the array" << std::endl;
    std::cout << "regardless of orphans (very fast). Once populated, delete one row towards the end of the array creating a new orphan." << std::endl;
    std::cout << "Reset bSeekOrphans to true and insert a new row. This orphaned row will now be populated.\n" << std::endl;

    // bSeekOrphans is reset to false
    mapTableRowBulkTest(false, uBound);

    // bSeekOrphans is reset to true
    mapTableRowErase(uBound);
    mapTableRowInsert(bSeekOrphans, "REINSERTED_ROW", "TEST", 345678);

    // display all new inserted rows
    displayRows();
};

void mapTableClass::mapTableRowBulkTest(bool bSeekOrphans, int uBound)
{
    for (int i = 1; i < uBound; i++)
    {
        mapTableRowInsert(bSeekOrphans, "LRG" + std::to_string(i), "Test" + std::to_string(i), i + 1);
    };
};

void mapTableClass::displayRows()
{
    for (mapItr = mapTableRow.begin(); mapItr != mapTableRow.end(); mapItr++)
    {
        std::cout << "The row with key " << mapItr->first << " has " << mapItr->second.col_1 << " in col_1; " << mapItr->second.col_2 << " in col_2; " << mapItr->second.col_3 << " in col_3; \n";
    };
    std::cout << "\n";
};