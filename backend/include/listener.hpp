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

#ifndef __LISTENER_H__
#define __LISTENER_H__

#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>
#include "network_utils.hpp"
#include <cpprest/json.h> 
#include "db.hpp"

using namespace cfx;
using namespace web;
using namespace http::experimental;

class Listener {
public:
    Listener(sqlite3* _db): db(_db) {}
    ~Listener() {}
    void handleGet(http::http_request message);
    void handlePost(http::http_request message);
    void initRestOpHandlers();

    void setEndpoint(const std::string & value);
    std::string endpoint() const;
    pplx::task<void> accept();
    pplx::task<void> shutdown();

    std::vector<utility::string_t> requestPath(const http::http_request & message);
protected:
    listener::http_listener _listener;
private:
    sqlite3* db = nullptr;
};

#endif