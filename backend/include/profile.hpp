#ifndef __PROFILE_H__
#define __PROFILE_H__

#include <string>
#include <vector>
#include <sqlite3.h>
#include "review.hpp"

class Profile
{
public:
    int id = -1;
    std::string ign = "";
    int score = 500;
    std::vector<Review*> reviews;

    // Profile(sqlite3* db, int id);
    Profile(sqlite3* db, std::string ign);
    virtual ~Profile();
    void fetchReviews();
    // virtual void calcScore() = 0;
private:
    sqlite3* db = nullptr;
};


#endif