#include "include/review.hpp"

Review::~Review() {}

LeechReview::~LeechReview() {}
int LeechReview::getScore()
{
    int x = ((actual * 100 / promised) - 100);
    return x * 10;
}