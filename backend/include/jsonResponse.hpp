#include <cpprest/json.h>
#include "profile.hpp"

using namespace web;

namespace Response {
    json::value searchResult(std::vector<Profile> profiles)
    {
        auto response = json::value::object();
        response["serviceName"] = json::value::string("C++ operationSuccess");
        response["http_method"] = json::value::string("POST");

        std::vector<json::value> profilesJson;

        for(int i = 0; i < profiles.size(); i++) {
            Profile profile = profiles.at(i);
            auto profileJson = json::value::object();
            profileJson["id"] = json::value::number(profile.id);
            profileJson["ign"] = json::value::string(profile.ign);
            profileJson["score"] = json::value::number(profile.score);
            profileJson["numReviews"] = json::value::number(profile.reviews.size());
            profilesJson.push_back(profileJson);
        }

        response["searchResult"] = json::value::array(profilesJson);

        return response;
    }

    json::value profileResult(Profile profile)
    {
        auto response = json::value::object();
        response["serviceName"] = json::value::string("C++ operationSuccess");
        response["http_method"] = json::value::string("POST");
        response["name"] = json::value::string(profile.ign);
        response["score"] = json::value::number(profile.score);

        std::vector<json::value> reviewsJson;

        auto profileJson = json::value::object();
        for(int r = 0; r < profile.reviews.size(); r++) {
            Review* review = profile.reviews.at(r);
            auto reviewJson = json::value::object();
            reviewJson["type"] = json::value::number(review->type);
            reviewJson["description"] = json::value::string(review->description);
            reviewJson["timestamp"] = json::value::number(review->timestamp);
            reviewJson["promised"] = json::value::number(review->promised);
            reviewJson["actual"] = json::value::number(review->actual);
            reviewJson["price"] = json::value::number(review->price);
            reviewsJson.push_back(reviewJson);
        }

        response["reviews"] = json::value::array(reviewsJson);

        return response;
    }

    json::value reviewSuccess()
    {
        auto response = json::value::object();
        response["serviceName"] = json::value::string("C++ operationSuccess");
        response["http_method"] = json::value::string("POST");
        return response;
    }

    json::value operationFailure()
    {
        auto response = json::value::object();
        response["serviceName"] = json::value::string("C++ operationFailure");
        response["http_method"] = json::value::string("POST");
        return response;
    }

    json::value responseNotImpl()
    {
        auto response = json::value::object();
        response["Access-Control-Allow-Origin"] = json::value::string("*"); //temp
        response["serviceName"] = json::value::string("C++ Microservice Sample");
        response["http_method"] = json::value::string("POST");
        return response;
    }
}