#include "../headers/testDB.h"
#include <stdlib.h>
#include "../headers/catch.hpp"
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("create a new database", "[createDB]")
{
    SECTION("Default settings")
    {
        std::string dbName("nameDB");
        testDB db = testDB::createDB(dbName, "./test-dir/testdb");

        REQUIRE(fs::is_regular_file(fs::status(db.getIndexFilePath())));
        REQUIRE(fs::is_regular_file(fs::status(db.getDbFilePath())));

        db.destroyDB();

        REQUIRE(fs::exists(fs::status(db.getIndexFilePath())));
        REQUIRE(fs::exists(fs::status(db.getDbFilePath())));
    }
}

TEST_CASE("read existing database", "[createDB]")
{
    SECTION("Default settings")
    {
        std::string dbName("nameDB");
        testDB db = testDB::createDB(dbName, "./test-dir/testdb");

        testDB db2 = testDB::loadDB(dbName, "./test-dir/testdb");

        //this should create index and db files
		REQUIRE(fs::is_regular_file(fs::status(db.getIndexFilePath())));
		REQUIRE(fs::is_regular_file(fs::status(db.getDbFilePath())));

		db2.destroyDB();
		//now the files must be deleted
		REQUIRE(fs::exists(fs::status(db.getIndexFilePath())));
		REQUIRE(fs::exists(fs::status(db.getDbFilePath())));
    }
}