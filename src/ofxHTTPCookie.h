/*==============================================================================
 
 Copyright (c) 2013 - Christopher Baker <http://christopherbaker.net>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ==============================================================================*/

#pragma once

#include "Poco/URI.h"
#include "Poco/String.h"
#include "Poco/Net/HTTPCookie.h"

#include "ofUtils.h"

using Poco::icompare;
using Poco::toLower;
using Poco::URI;
using Poco::Net::HTTPCookie;

class ofxHTTPCookie {
public:

    ofxHTTPCookie(const HTTPCookie& cookie, unsigned long long _createdAt = ofGetSystemTime());
    
    unsigned long long getCreatedAt() const;
    bool isExpired(unsigned long long expiredAt = ofGetSystemTime()) const;
    bool isSession() const;
    
    bool matchesDomain(const URI& uri) const;
    bool matchesPath(const URI& uri) const;
    bool matchesURI(const URI& uri, bool matchSessionCookies = true) const;
    // matches uri
    // makes sure the cookie, makes sure 
    
    bool matches(const ofxHTTPCookie& cookie) const;
    
    const HTTPCookie& getCookie() const;
    
    string toString() const;
    
protected:
    HTTPCookie cookie;
    unsigned long long createdAt;
    
    bool static endsWith(string const& fullString, string const& ending);
};