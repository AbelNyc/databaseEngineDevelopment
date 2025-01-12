#ifndef PAGE_HPP
#define PAGE_HPP

#include <iostream>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <string>

class Page {
private:
    static const int PAGE_SIZE = 4096;  // Fixed size of the page in bytes
    char data[PAGE_SIZE];              // Buffer to store records
    int freeSpaceOffSet;              // Offset to track free space within the page
    int numRecords;                   // Number of records currently stored in the page
    std::vector<int> recordOffSets;   // Vector to store offsets of each record

public:
    // Constructor initializes the page with full free space
    Page();

    // Inserts a record into the page and returns the slot ID of the inserted record
    int insertRecord(const char* record, int size);

    // Retrieves a record by its slot ID
    std::string getRecord(int slotId);

    // Marks a record as deleted by setting its offset to -1
    void deleteRecord(int slotId);

    // Compacts the page by removing gaps from deleted records
    void compactPage();

    // Prints metadata about the page
    void printPageInfo();
};

#endif // PAGE_HPP
