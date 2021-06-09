#include "include/profile.hpp"
#include "include/callbacks.hpp"

int _profileCallback(void* dest, int numCol, char** values, char** colName)
{
    Profile* profile = (Profile*)dest;
    for(int c = 0; c < numCol; c++) {
        if (std::string(colName[c]).compare("ID") == 0)
        {
            profile->id = atoi(values[c]);
        }
        else if (std::string(colName[c]).compare("IGN") == 0)
        {
            profile->ign = values[c];
        }
        else if (std::string(colName[c]).compare("Score") == 0)
        {
            profile->score = atoi(values[c]);
        }
    }

    return EXIT_SUCCESS;
}

int _leechReviewCallback(void* dest, int numCol, char** values, char** colName)
{
    Profile* profile = (Profile*)dest;
    LeechReview* newReview = new LeechReview();
    for(int c = 0; c < numCol; c++) {
        if (std::string(colName[c]).compare("ID") == 0)
        {
            newReview->id = atoi(values[c]);
        }
        else if (std::string(colName[c]).compare("Seller") == 0)
        {
            newReview->seller = atoi(values[c]);
        }
        else if (std::string(colName[c]).compare("Buyer") == 0)
        {
            newReview->buyer = atoi(values[c]);
        }
        else if (std::string(colName[c]).compare("Timestamp") == 0)
        {
            newReview->timestamp = atol(values[c]);
        }
        else if (std::string(colName[c]).compare("Description") == 0)
        {
            newReview->description = values[c];
        }
        else if (std::string(colName[c]).compare("Promised") == 0)
        {
            newReview->promised = atol(values[c]);
        }
        else if (std::string(colName[c]).compare("Actual") == 0)
        {
            newReview->actual = atol(values[c]);
        }
        else if (std::string(colName[c]).compare("Price") == 0)
        {
            newReview->price = atol(values[c]);
        }
    }
    profile->reviews.push_back(newReview);

    return EXIT_SUCCESS;
}