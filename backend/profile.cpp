#include "include/profile.hpp"
#include "include/callbacks.hpp"
#include <iostream>

// Profile::Profile(sqlite3* _db, int _id): db(_db)
// {
//     std::string exec = "SELECT * FROM PROFILE WHERE ID = " + std::to_string(_id) + ";";
//     char* messageErr = nullptr;
//     if (sqlite3_exec(db, exec.c_str(), _profileCallback, this, &messageErr) != SQLITE_OK)
//     {
//         std::cerr << "Failed to select profile: " << messageErr << std::endl;
//         sqlite3_free(messageErr);
//     }
// }

Profile::Profile(sqlite3* _db, std::string _ign): db(_db)
{
    std::string exec = "SELECT * FROM PROFILE WHERE IGN = '" + _ign + "';";
    char* messageErr = nullptr;
    if (sqlite3_exec(db, exec.c_str(), _profileCallback, this, &messageErr) != SQLITE_OK)
    {
        std::cerr << "Failed to select profile: " << messageErr << std::endl;
        sqlite3_free(messageErr);
    }
}

Profile::~Profile() {}

void Profile::fetchReviews()
{
    std::string  exec = "SELECT * FROM LEECHING_REVIEW WHERE Seller = " + std::to_string(id) + ";";
    char* messageErr = nullptr;
    if (sqlite3_exec(db, exec.c_str(), _leechReviewCallback, this, &messageErr) != SQLITE_OK)
    {
        std::cerr << "Failed to select leeching_REVIEW: " << messageErr << std::endl;
        sqlite3_free(messageErr);
    }
}