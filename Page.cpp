#include <iostream>
#include <vector>
#include <cstring>
#include <stdexcept>
using namespace std;

class Page {
private:
    static const int PAGE_SIZE = 4096;
    char data[PAGE_SIZE];
    int freeSpaceOffSet;
    int numRecords;
    vector<int> recordOffSets;

public:
    Page() : freeSpaceOffSet(PAGE_SIZE), numRecords(0) {}

    int insertRecord(const char* record, int size) {
        if (freeSpaceOffSet - size < (numRecords + 1) * sizeof(int)) {
            cerr << "Not Enough space to insert record" << endl;
            return -1;
        }

        freeSpaceOffSet -= size;
        memcpy(data + freeSpaceOffSet, record, size);
        recordOffSets.push_back(freeSpaceOffSet);
        numRecords += 1;
        return numRecords - 1;
    }

    string getRecord(int slotId) {
        if (slotId < 0 || slotId >= numRecords) {
            throw out_of_range("Invalid slot ID");
        }

        int offset = recordOffSets[slotId];
        int nextOffset = (slotId == 0) ? PAGE_SIZE : recordOffSets[slotId - 1];
        int size = nextOffset - offset;

        return string(data + offset, size);
    }

    void deleteRecord(int slotId) {
        if (slotId < 0 || slotId >= numRecords) {
            throw out_of_range("Invalid slot ID");
        }

        recordOffSets[slotId] = -1; // Mark as deleted
    }

    void compactPage() {
        char temp[PAGE_SIZE];
        int tempFreeSpaceOffset = PAGE_SIZE;
        vector<int> newOffsets;

        for (int i = numRecords - 1; i >= 0; --i) {
            if (recordOffSets[i] == -1) continue; // Skip deleted records

            int offset = recordOffSets[i];
            int nextOffset = (i == 0) ? PAGE_SIZE : recordOffSets[i - 1];
            int size = nextOffset - offset;

            tempFreeSpaceOffset -= size;
            memcpy(temp + tempFreeSpaceOffset, data + offset, size);
            newOffsets.push_back(tempFreeSpaceOffset);
        }

        memcpy(data, temp, PAGE_SIZE);
        freeSpaceOffSet = tempFreeSpaceOffset;
        recordOffSets = vector<int>(newOffsets.rbegin(), newOffsets.rend());
    }

    void printPageInfo() {
        cout << "Page Info:" << endl;
        cout << "Free Space Offset: " << freeSpaceOffSet << endl;
        cout << "Number of Records: " << numRecords << endl;
        cout << "Record Offsets: ";
        for (int offset : recordOffSets) {
            cout << offset << " ";
        }
        cout << endl;
    }
};
