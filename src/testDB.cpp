#include "../headers/testDB.h"
#include "../headers/storage.h"
#include <iostream>
#include <map>
#include <cstdlib>
//#include <direct.h>
#include <string.h>
#include <filesystem>
#include <fstream>

#pragma warning(disable: 4996)

namespace fs = std::filesystem;

testDB testDB::loadOrCreateDB(std::string dbName, std::string dbPath)
{
    try
    {
        return testDB::loadDB(dbName, dbPath);
    }
    catch(...)
    {
        return testDB::createDB(dbName, dbPath);
    }
};

testDB testDB::createDB(std::string dbName, std::string dbPath)
{
    std::string folderPath = dbPath + "/" + dbName;
    store::makeDir(folderPath);
    std::string dbfilePath = folderPath + "/" + dbName + ".db";
    std::string indexFilePath = folderPath + "/" + dbName + ".index";
    std::ofstream fil(indexFilePath.c_str());
    fil.close();
    fil.open(dbfilePath.c_str());
    fil.close();

    return testDB(dbName, folderPath, dbfilePath, indexFilePath);
};

testDB testDB::loadDB(std::string dbName, std::string dbPath)
{
    std::string folderPath = dbPath + "/" + dbName;
    if(fs::is_directory(folderPath))
    {
        std::string dbfilePath = folderPath + "/" + dbName + ".db";
        std::string indexFilePath = folderPath + "/" + dbName + ".index";
        if(fs::exists(dbfilePath) && fs::exists(indexFilePath))
        {
            return testDB(dbName, folderPath,dbfilePath,indexFilePath);
        }
    }
    throw std::runtime_error("Loading DB failed");
};

std::string testDB::getRecord(std::string id)
{
    if(index.find(id) == index.end())
    {
        throw std::runtime_error("no value found");
    }
    return store::readfromDB(this->dbFilePath, index[id]);
};

void testDB::putRecord(std::string id, std::string record)
{
    long pos = store::writeToDB(this->dbFilePath, record);
    index[id] = pos;
    store::writeToIndex(this->indexFilePath, id, pos);
};

std::string testDB::getIndexFilePath()
{
    return this->indexFilePath;
};

std::string testDB::getDbFilePath() 
{
    return this->dbFilePath;
};

testDB::testDB(std::string dbName, std::string dbFolderPath, std::string dbFilePath, std::string indexFilePath)
{
    this->dbFolderPath=dbFolderPath;
    this->dbName=dbName;
    this->dbFilePath=dbFilePath;
    this->indexFilePath=indexFilePath;
    store::loadIndex(indexFilePath,this->index);
};

std::unordered_map<std::string, std::string> testDB::getAllRecords()
{
    std::unordered_map<std::string,std::string> output;
    for(auto kv:this->index)
    {
        output[kv.first] = store::readfromDB(this->dbFilePath, kv.second);
    }
    return output;
}

void testDB::destroyDB() 
{
    store::deleteFolder(this->dbFolderPath);
}