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

#include <vector>

#include "Poco/Net/HTTPRequestHandlerFactory.h"

//#include "ofxHTTPBaseTypes.h"
#include "ofxHTTPServerRouteHandler.h"

using std::vector;

using Poco::Net::HTTPRequestHandlerFactory;

//------------------------------------------------------------------------------
class ofxHTTPServerRouteManager : public HTTPRequestHandlerFactory {
public:
    
    ofxHTTPServerRouteManager(vector<ofxBaseHTTPServerRoutePtr>& _factories,
                              bool _bIsSecurePort)
    : factories(_factories), bIsSecurePort(_bIsSecurePort) { }
    
    virtual ~ofxHTTPServerRouteManager() { }

    HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request) {
        // We start with the last factory that was added.
        // Thus, factories with overlapping routes should be
        // carefully ordered.
        vector<ofxBaseHTTPServerRoutePtr>::reverse_iterator iter = factories.rbegin();
        while(iter != factories.rend()) {
            if((*iter)->canHandleRequest(request,bIsSecurePort)) {
                return (*iter)->createRequestHandler(request);
            }
            ++iter;
        }
        return new ofxHTTPServerRouteHandler(); // if we get to this point, we didn't find a matching route
    }
    
protected:
    vector<ofxBaseHTTPServerRoutePtr>& factories;
    bool bIsSecurePort; // TODO can we get this from teh HTTPServerRequest somehow?
};
