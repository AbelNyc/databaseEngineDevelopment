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

### **Methods**

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

---

## **Usage Instructions**

### **Compilation and Execution**

Use a C++ compiler to build and run the project:

```bash
$ g++ -o database_engine main.cpp -std=c++11
$ ./database_engine
```

### **Example Workflow**

```cpp
#include <iostream>
#include "Page.h"

int main() {
    Page page;

    page.insertRecord("Record1", 8);
    page.insertRecord("Record2", 4);
    page.insertRecord("Record3", 8);

    page.printPageInfo();

    std::cout << "Record at Slot 1: " << page.getRecord(1) << std::endl;

    page.deleteRecord(1);
    page.compactPage();

    page.printPageInfo();

    return 0;
}
```

### **Expected Output**

```
Page Info:
Free Space Offset: 4076
Number of Records: 3
Record Offsets: 4088 4084 4076
Record at Slot 1: Record2
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

## **Contributors**
- [Your Name]

Feel free to modify and extend this project to deepen your understanding of database systems.

