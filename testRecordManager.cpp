#include <iostream>
#include "RecordManager.hpp"
#include <cassert>  // For assertions to validate test cases
#include <string>



void testInsertAndRetrieve() {
    RecordManager recordManager;

    // Insert records
    int page1 = recordManager.insertRecord("Record1", 8);
    int page2 = recordManager.insertRecord("Record2", 4);
    int page3 = recordManager.insertRecord("Record3", 8);

    // Assert that all records were inserted in the correct pages
    assert(page1 == 0);
    assert(page2 == 0);
    assert(page3 == 0);

    // Retrieve and verify records
    assert(recordManager.getRecord(0, 0) == "Record1");
    assert(recordManager.getRecord(0, 1) == "Record2");
    assert(recordManager.getRecord(0, 2) == "Record3");

    std::cout << "testInsertAndRetrieve passed.\n";
}

void testDeleteAndCompact() {
    RecordManager recordManager;

    // Insert records
    recordManager.insertRecord("Record1", 8);
    recordManager.insertRecord("Record2", 4);
    recordManager.insertRecord("Record3", 8);

    // Delete the second record
    recordManager.deleteRecord(0, 1);

    // Compact pages
    recordManager.compactAllPages();

    // Verify that remaining records are accessible
    assert(recordManager.getRecord(0, 0) == "Record1");
    assert(recordManager.getRecord(0, 1) == "Record3");  // Record3 shifts to slot 1 after compaction

    std::cout << "testDeleteAndCompact passed.\n";
}

void testMultiplePages() {
    RecordManager recordManager;

    // Insert enough records to fill one page and spill into another
    for (int i = 0; i < 100; ++i) {
        recordManager.insertRecord(("Record" + std::to_string(i)).c_str(), 40);
    }

    // Verify that records were distributed across multiple pages
    assert(recordManager.getRecord(0, 0) == "Record0");
    assert(recordManager.getRecord(1, 0) == "Record50");  // Assuming 50 records fit in the first page

    std::cout << "testMultiplePages passed.\n";
}

int main() {
    testInsertAndRetrieve();
    testDeleteAndCompact();
    testMultiplePages();

    std::cout << "All tests passed successfully!\n";
    return 0;
}
