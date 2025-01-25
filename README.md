# Database Developer Engine

## **Project Overview**

This project is a lightweight database engine implemented in C++. It serves as a foundation for learning database internals by handling core functionalities such as record insertion, retrieval, deletion, and page compaction. The engine is designed for educational purposes and can be extended to include advanced features like indexing, query processing, and transaction management.

---

## **Key Features**

1. **Record Management**
   - Insert records dynamically within a fixed-size page.
   - Retrieve records by slot ID.
   - Delete records and mark them as invalid.

2. **Page Compaction**
   - Efficiently reclaims space by compacting the page after record deletions.

3. **Storage Optimization**
   - Stores records from the end of the page backward to maximize space utilization.

4. **Error Handling**
   - Throws exceptions for invalid operations (e.g., out-of-range slot IDs).

---

## **Project Structure**

### **Classes**

1. **Page**
   - Manages a fixed-size memory buffer to store records.
   - Responsible for inserting, retrieving, deleting, and compacting records.

2. **RecordManager**
   - Manages multiple pages.
   - Provides higher-level operations for inserting, retrieving, and deleting records across pages.
   - Tracks free space on each page.

### **Files**

1. **Page.hpp**
   - Declares the `Page` class, its member variables, and methods.

2. **Page.cpp**
   - Implements the functionality of the `Page` class.

3. **RecordManager.hpp**
   - Declares the `RecordManager` class, which manages multiple `Page` objects.

4. **RecordManager.cpp**
   - Implements the functionality of the `RecordManager` class.

5. **testRecordManager.cpp**
   - Contains unit tests to verify the functionality of the `Page` and `RecordManager` classes.

---

## **Methods**

### **Page Class**

#### `insertRecord(const char* record, int size)`
- Inserts a record into the page.
- Returns the slot ID of the inserted record.
- Handles insufficient space gracefully by returning `-1`.

#### `getRecord(int slotId)`
- Retrieves a record by its slot ID.
- Returns the record as a `std::string`.
- Throws an exception if the slot ID is invalid or the record is deleted.

#### `deleteRecord(int slotId)`
- Marks a record as deleted by setting its offset to `-1`.

#### `compactPage()`
- Compacts the page by removing gaps left by deleted records.
- Updates the record offsets and frees up space.

#### `printPageInfo()`
- Displays page metadata, including:
  - Free space offset
  - Number of valid records
  - Record offsets

### **RecordManager Class**

#### `addPage()`
- Allocates a new page and adds it to the collection of pages.

#### `insertRecord(const char* record, int size)`
- Finds a page with enough space and inserts the record.
- If no page has enough space, allocates a new page and inserts the record.

#### `getRecord(int pageId, int slotId)`
- Retrieves a record from the specified page and slot.

#### `deleteRecord(int pageId, int slotId)`
- Deletes a record from the specified page and slot.

#### `compactAllPages()`
- Compacts all pages in the database to reclaim space.

#### `printAllPagesInfo()`
- Prints metadata for all pages managed by the RecordManager.

---

## **Usage Instructions**

### **Compilation and Execution**

Use a C++ compiler to build and run the project:

```bash
$ g++ -o testRecordManager testRecordManager.cpp RecordManager.cpp Page.cpp -std=c++11
$ ./testRecordManager
```

### **Example Workflow**

```cpp
#include <iostream>
#include "Page.hpp"
#include "RecordManager.hpp"

int main() {
    RecordManager recordManager;

    recordManager.insertRecord("Record1", 8);
    recordManager.insertRecord("Record2", 4);
    recordManager.insertRecord("Record3", 8);

    recordManager.printAllPagesInfo();

    std::cout << "Record from Page 0, Slot 1: " << recordManager.getRecord(0, 1) << std::endl;

    recordManager.deleteRecord(0, 1);
    recordManager.compactAllPages();

    recordManager.printAllPagesInfo();

    return 0;
}
```

### **Expected Output**

```
Page Info:
Free Space Offset: 4076
Number of Records: 3
Record Offsets: 4088 4084 4076
Record from Page 0, Slot 1: Record2
Page Info:
Free Space Offset: 4084
Number of Records: 2
Record Offsets: 4088 4084
```

---

## **Future Enhancements**

1. **Indexing**
   - Implement B+ Trees or hash indexes to improve query performance.

2. **Query Processor**
   - Support SQL-like queries for record manipulation.

3. **Transaction Management**
   - Add support for ACID transactions with logging and recovery.

4. **Concurrency Control**
   - Implement multi-threaded access with locking mechanisms or MVCC.

5. **Storage Expansion**
   - Allow multiple pages and implement a buffer manager for efficient memory use.

---

## **Technical Concepts Covered**

- Pointer arithmetic
- Low-level memory manipulation using `memcpy`
- Fixed-size memory management
- Record compaction and space reclamation
- Error handling and exception management

---

## **Requirements**

- C++11 or later
- Basic understanding of pointers, memory management, and file I/O

---

## **References**

1. *Database System Concepts* by Silberschatz, Korth, and Sudarshan
2. *The Architecture of Open Source Applications: Volume II* (PostgreSQL Chapter)
3. SQLite Documentation (for inspiration on lightweight database design)

---
