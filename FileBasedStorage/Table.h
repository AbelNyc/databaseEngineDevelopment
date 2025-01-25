#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <utility>

//struct to represent database row 
struct Row  {
    int id;
    char name[20];

    Row() : id(0) {std::memset(name, 0, sizeof(name));}
    Row(int id, const std::string& name) : id(id) 
    {
        std::memset(this->name, 0, sizeof(this->name));
        std::strncpy(this->name, name.c_str(), sizeof(this->name)-1);
    };
};
class Table {
   public:
     Table(const std::string& name);   
     ~Table(); 

     void insert(const Row& row);
     void update(const Row& row);
     std::vector<Row> select();
     void remove(const Row& row);
private:
    const std::string tableName;
    std::fstream dataFile;

    const int RECORD_SIZE = sizeof(Row);

    void openFile();
    void closeFile();

};

#endif 