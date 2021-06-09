//
//  Created by Ivan Mejia on 12/24/16.
//
// MIT License
//
// Copyright (c) 2016 ivmeroLabs.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include "include/listener.hpp"
#include <vector>
#include "include/db.hpp"
#include "include/jsonResponse.hpp"

using namespace web;
using namespace http;
using namespace Concurrency;

/*
{
    serviceName: "C++ operationSuccess",
    http_method: "POST",
    searchResult: [
        {
            id: 0,
            ign: 'milktea',
            score: 500
        },
        {
            id: 1,
            ign: 'milkerino',
            score: 500
        }
    ]
}
*/

void Listener::initRestOpHandlers()
{
    _listener.support(methods::GET, std::bind(&Listener::handleGet, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&Listener::handlePost, this, std::placeholders::_1));
}

static std::vector<std::string> _stringTokenise(std::string text, char delim)
{
    std::vector<std::string> tokens;
    std::stringstream checker(text);
    std::string tmp;

    while (getline(checker, tmp, delim))
    {
        tokens.push_back(tmp);
    }

    return tokens;
}

void Listener::handleGet(http_request message)
{
    std::string formDataStr = message.request_uri().to_string().substr(2);
    std::cout << "GET " << formDataStr << std::endl;
    std::vector<std::string> pair = _stringTokenise(formDataStr, '=');
    if (pair[0].compare("playerNameField") == 0)
    {
        Profile profile(db, pair[1]);
        http_response response(status_codes::OK);
        response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
        std::vector<Profile> profiles;
        if (profile.id != -1) {
            profile.fetchReviews();
            profiles.push_back(profile);
        }
        response.set_body(Response::searchResult(profiles));
        message.reply(response);
    }
    else if (pair[0].compare("playerName") == 0)
    {
        Profile profile(db, pair[1]);
        profile.fetchReviews();
        http_response response(status_codes::OK);
        response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
        response.set_body(Response::profileResult(profile));
        message.reply(response);
    }
}

static LeechReview _parseFormToReview(sqlite3* db, std::string formData)
{
    LeechReview review;
    std::vector<std::string> entries = _stringTokenise(formData, '&');
    for (std::string entry : entries)
    {
        std::vector<std::string> pair = _stringTokenise(entry, '=');
        if (pair.size() < 2) {
            continue;
        }
        else if ((pair[0].compare("theirNameField") == 0) || (pair[0].compare("yourNameField") == 0))
        {
            // create profile if does not exist
            Profile profile = Profile(db, pair[1]);
            if (profile.id == -1)
            {
                profile.ign = pair[1];
                insertProfile(db, profile);
                profile = Profile(db, pair[1]);
            }
            if (pair[0].compare("theirNameField") == 0)
                review.seller = profile.id;
            else
                review.buyer = profile.id;
        }
        else if (pair[0].compare("description") == 0)
            review.description = pair[1];
        else if (pair[0].compare("promised") == 0)
            review.promised = atol(pair[1].c_str());
        else if (pair[0].compare("actual") == 0)
            review.actual = atol(pair[1].c_str());
        else if (pair[0].compare("price") == 0)
            review.price = atol(pair[1].c_str());
    }
    return review;
}

void Listener::handlePost(http_request message)
{
    std::cout << "POST" << std::endl;
    std::string formDataStr = message.content_ready().get().extract_utf8string(true).get();

    LeechReview review = _parseFormToReview(db, formDataStr);
    if (insertLeechReview(db, review))
    {
        message.reply(status_codes::OK, Response::reviewSuccess());
    }

    message.reply(status_codes::OK, Response::operationFailure());
}

void Listener::setEndpoint(const std::string& value)
{
    uri endpointURI(value);
    uri_builder endpointBuilder;

    endpointBuilder.set_scheme(endpointURI.scheme());
    if (endpointURI.host() == "host_auto_ip4")
    {
        endpointBuilder.set_host(NetworkUtils::hostIP4());
    }
    else if (endpointURI.host() == "host_auto_ip6")
    {
        endpointBuilder.set_host(NetworkUtils::hostIP6());
    }
    endpointBuilder.set_port(endpointURI.port());
    endpointBuilder.set_path(endpointURI.path());

    _listener = listener::http_listener(endpointBuilder.to_uri());
}

std::string Listener::endpoint() const
{
    return _listener.uri().to_string();
}

pplx::task<void> Listener::accept()
{
    initRestOpHandlers();
    return _listener.open();
}

pplx::task<void> Listener::shutdown()
{
    return _listener.close();
}

std::vector<utility::string_t> Listener::requestPath(const http_request& message)
{
    auto relativePath = uri::decode(message.relative_uri().path());
    return uri::split_path(relativePath);
}