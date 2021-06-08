#ifndef __DB_H__
#define __DB_H__

#include <memory>
#include <sqlite3.h>
#include "profile.hpp"
#include "review.hpp"

bool createProfileTable(sqlite3* db);
bool insertProfile(sqlite3* db, Profile profile);

bool createReviewTable(sqlite3* db);
bool insertLeechReview(sqlite3* db, LeechReview review);

#endif