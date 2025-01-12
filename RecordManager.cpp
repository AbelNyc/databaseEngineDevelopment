#include "RecordManager.hpp"  // Include the header file for the class definition
#include <iostream>         // For console output
#include <stdexcept>        // For exception handling

// Constructor: Starts with a single page
RecordManager::RecordManager() {
    addPage();  // Add an initial page
}

// Adds a new Page object to the collection of pages
void RecordManager::addPage() {
    pages.emplace_back();  // Create and add a new Page object to the vector
}

// Inserts a record into an available page
int RecordManager::insertRecord(const char* record, int size) {
    for (size_t i = 0; i < pages.size(); ++i) {
        int slotId = pages[i].insertRecord(record, size);  // Try to insert in the current page
        if (slotId != -1) {  // If insertion was successful
            std::cout << "Inserted into Page " << i << ", Slot " << slotId << std::endl;
            return i;  // Return the page ID
        }
    }
    // If no page has enough space, create a new page and retry
    addPage();
    return insertRecord(record, size);  // Recursive call after adding a new page
}

// Retrieves a record from the specified page and slot
std::string RecordManager::getRecord(int pageId, int slotId) {
    if (pageId < 0 || pageId >= static_cast<int>(pages.size())) {  // Validate page ID
        throw std::out_of_range("Invalid page ID");
    }
    return pages[pageId].getRecord(slotId);  // Delegate retrieval to the Page class
}

// Deletes a record from the specified page and slot
void RecordManager::deleteRecord(int pageId, int slotId) {
    if (pageId < 0 || pageId >= static_cast<int>(pages.size())) {  // Validate page ID
        throw std::out_of_range("Invalid page ID");
    }
    pages[pageId].deleteRecord(slotId);  // Delegate deletion to the Page class
}

// Compacts all pages to reclaim space
void RecordManager::compactAllPages() {
    for (Page& page : pages) {  // Iterate over each page
        page.compactPage();  // Compact the page to remove gaps
    }
}

// Prints metadata of all pages
void RecordManager::printAllPagesInfo() {
    for (size_t i = 0; i < pages.size(); ++i) {  // Iterate through all pages
        std::cout << "Page " << i << ":" << std::endl;
        pages[i].printPageInfo();  // Print the info for each page
    }
}
