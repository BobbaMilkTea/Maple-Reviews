#include <iostream>
#include <ctime>
#include "include/db.hpp"
#include <sstream>

bool createProfileTable(sqlite3* db)
{
    std::string exec = "DROP TABLE PROFILE";
    char* errMsg = nullptr;
    sqlite3_exec(db, exec.c_str(), NULL, 0, &errMsg);

    exec = "CREATE TABLE PROFILE ("
        "ID             INTEGER         PRIMARY KEY AUTOINCREMENT NOT NULL, "
        "IGN            TEXT            NOT NULL, "
        "Score          INTEGER         NOT NULL, "
        "Registration   INTEGER         NOT NULL );";

    if (sqlite3_exec(db, exec.c_str(), NULL, 0, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Failed to create profile table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

bool createReviewTable(sqlite3* db)
{
    char* errMsg = nullptr;
    std::string exec = "DROP TABLE LEECHING_REVIEW";
    sqlite3_exec(db, exec.c_str(), NULL, 0, &errMsg);

    exec = "CREATE TABLE LEECHING_REVIEW ("
        "ID             INTEGER         PRIMARY KEY AUTOINCREMENT NOT NULL, "
        "Seller         INTEGER         NOT NULL, "
        "Buyer          INTEGER                 , "
        "Type           INTEGER         NOT NULL, "
        "Timestamp      INTEGER         NOT NULL, "
        "Description    TEXT                    , "
        "Promised       INTEGER         NOT NULL, "
        "Actual         INTEGER         NOT NULL, "
        "Price          INTEGER         NOT NULL);";

    if (sqlite3_exec(db, exec.c_str(), NULL, 0, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Failed to create review table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

bool insertProfile(sqlite3* db, Profile profile)
{
    char* errMsg = nullptr;
    std::stringstream exec;
    exec << "INSERT INTO PROFILE (IGN, Score, Registration) VALUES('"
        << profile.ign << "', "
        << profile.score << ", "
        << std::time(nullptr) << ");";
    
    std::cout << exec.str() << std::endl;

    if (sqlite3_exec(db, exec.str().c_str(), NULL, 0, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Failed to insert profile: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

bool insertLeechReview(sqlite3* db, LeechReview review)
{
    char* errMsg = nullptr;
    std::stringstream exec;
    exec << "INSERT INTO LEECHING_REVIEW (Seller, Buyer, Type, Timestamp, Description, Promised, Actual, Price) VALUES ("
        << review.seller << ", "
        << review.buyer << ", "
        << review.type << ", "
        << std::time(nullptr) << ", '"
        << review.description << "', "
        << review.promised << ", "
        << review.actual << ", "
        << review.price << ");";
    
    std::cout << exec.str() << std::endl;

    if (sqlite3_exec(db, exec.str().c_str(), NULL, 0, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Failed to insert leech review: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}