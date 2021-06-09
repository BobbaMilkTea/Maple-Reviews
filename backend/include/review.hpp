#ifndef __REVIEW_H__
#define __REVIEW_H__

#include <string>

enum ReviewType
{
    LeechEPM_T, LeechLvl_T
};

class Review
{
public:
    int id = 0;
    int seller = 0;
    int buyer = 0;
    ReviewType type;
    long timestamp;
    long promised = 0;
    long actual = 0;
    long price = 0;
    std::string description;

    virtual ~Review();
    virtual int getScore() = 0;
};

class LeechReview : public Review
{
public:

    virtual ~LeechReview();
    virtual int getScore();
};

#endif