
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



