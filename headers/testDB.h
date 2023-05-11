#pragma once
#include <string>
#include <unordered_map>

class testDB
{
    std::unordered_map <std::string, long> index;
    std::string dbName;
    std::string dbFolderPath;
    std::string dbFilePath;
    std::string indexFilePath;


public:
    static testDB createDB(std::string dbName, std::string dbPath);
    static testDB loadDB(std::string dbName, std::string dbPath);
    static testDB loadOrCreateDB(std::string dbName, std::string dbPath);

    testDB(std::string dbName, std:;string dbFolderPath, std::string dbFilePath, std::string indexFilePath);

    std::string getIndexFilePath();
    std::string getDbFilePath();

    std::string getAllRecords(std::string id);
    std::unordered_map<std::string,std::string> getAllRecords();
    void putRecord(std::string id, std::string record);

    void destroyDB();
};