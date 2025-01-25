
#include "Table.h"

Table::Table(const std::string& name){
    openFile();
}

Table::~Table(){
    closeFile();
}

void Table::openFile(){
    std::string tableFile = tableName + ".dat";
    dataFile.open(tableFile, std::ios::in | std::ios::out| std::ios::binary);
    
    if(!dataFile){
     dataFile.open(tableFile,std::ios::out | std::ios::binary);
     dataFile.close();

    dataFile.open(tableFile, std::ios::in | std::ios::out| std::ios::binary);
    }
}

void Table::closeFile(){
   if(dataFile.is_open()){
    dataFile.close();
   };


}

void Table::insert(const Row& row){
    dataFile.seekp(0, std::ios::end);
    dataFile.write(reinterpret_cast<const char*>(&row), RECORD_SIZE);
    dataFile.flush();
};

std::vector<Row> Table::select(){
    std::vector<Row> results;
    dataFile.seekg(0, std::ios::beg);

    Row row;

     while (dataFile.read(reinterpret_cast<char*>(&row), RECORD_SIZE)) {  // Read binary data into row
        if (row.id != -1) {  // Ignore soft-deleted rows (marked with id = -1)
            results.push_back(row);  // Store the valid row in the vector
        }
    }

    return results;

};

void Table::remove(const Row& row){
    dataFile.seekg(0, std::ios::beg);

    Row temp;
     Row temp;  // Temporary row to hold data
    while (dataFile.read(reinterpret_cast<char*>(&temp), RECORD_SIZE)) {  // Read each row
        if (temp.id == row.id) {  // Check if the row matches the given ID
            dataFile.seekp(-RECORD_SIZE, std::ios::cur);  // Move write pointer back to overwrite
            
            temp.id = -1;  // Mark as deleted by setting ID to -1
            dataFile.write(reinterpret_cast<const char*>(&temp), RECORD_SIZE);  // Overwrite row
            dataFile.flush();  // Save changes
            return;  // Stop after marking as deleted
        }
    }
    
}



