#ifndef RECORD_MANAGER_H
#define RECORD_MANAGER_H
#include <vector>      // To manage multiple pages
#include "Page.hpp"
using namespace std;


class RecordManager {
    private:
     vector<Page> pages;
    public:
     RecordManager();

     void addPage();

     int insertRecord(const char* record, int size);

     string getRecord(int pageId, int slotId);

     void deleteRecord (int pageId, int slotId );

     void compactAllPages();

     void printAllPagesInfo();
};

#endif