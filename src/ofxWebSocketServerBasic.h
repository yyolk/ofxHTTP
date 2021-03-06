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

#include "ofxHTTPServerBasic.h"
#include "ofxHTTPServerDefaultRoute.h"
#include "ofxWebSocketRoute.h"

//------------------------------------------------------------------------------
class ofxWebSocketServerBasic : public ofxHTTPServer {
public:
    typedef ofxHTTPServer::Settings             ServerSettings;
    typedef ofxHTTPServerDefaultRoute::Settings RouteSettings;
    typedef ofxWebSocketRoute::Settings         WebSocketSettings;
    
    struct Settings;
    
    ofxWebSocketServerBasic() { }
    virtual ~ofxWebSocketServerBasic() { }
    
    void loadSettings(Settings _settings = Settings()) {
        settings = _settings.server;
        
        defaultRoute = ofxHTTPServerDefaultRoute::Instance(_settings.route);
        websocket    = ofxWebSocketRoute::Instance(_settings.websocket);
        
        addRoute(defaultRoute);
        addRoute(websocket);
        
        bSettingsLoaded = true;
    }
    
    
    void broadcast(const ofxWebSocketFrame& frame) {
        if(websocket == NULL) {
            ofLogError("ofxWebSocketServerBasic::broadcast") << "call loadSettings first.";
            return;
        }
        
        websocket->broadcast(frame);
    }
    
    bool sendFrame(ofxWebSocketRouteHandler* handler, const ofxWebSocketFrame& frame) {
        if(websocket == NULL) {
            ofLogError("ofxWebSocketServerBasic::sendFrame") << "call loadSettings first.";
            return false;
        }
        
        return websocket->sendFrame(handler,frame);
    }
    
    void disconnect(ofxWebSocketRouteHandler* handler) {
        if(websocket == NULL) {
            ofLogError("ofxWebSocketServerBasic::disconnect") << "call loadSettings first.";
            return;
        }
        websocket->disconnect(handler);
    }
    
    void disconnectAll() {
        if(websocket == NULL) {
            ofLogError("ofxWebSocketServerBasic::disconnectAll") << "call loadSettings first.";
            return;
        }
        websocket->disconnectAll();
    }

    size_t getNumClientsConnected() {
        if(websocket == NULL) {
            ofLogError("ofxWebSocketServerBasic::getNumClientsConnected") << "call loadSettings first.";
            return -1;
        }
        return websocket->getNumClientsConnected();
    }


    template<class ListenerClass>
    void registerWebSocketEvents(ListenerClass * listener) {
        if(websocket == NULL) {
            ofLogError("ofxWebSocketServerBasic::registerWebSocketEvents") << "call loadSettings first.";
            return;
        }
        websocket->registerWebSocketEvents(listener);
    }
    
    template<class ListenerClass>
    void unregisterWebSocketEvents(ListenerClass * listener) {
        if(websocket == NULL) {
            ofLogError("ofxWebSocketServerBasic::unregisterWebSocketEvents") << "call loadSettings first.";
            return;
        }
        websocket->unregisterWebSocketEvents(listener);
    }
    
    struct Settings {
        ServerSettings    server;
        RouteSettings     route;
        WebSocketSettings websocket;
        
        Settings();
    };
    
    
    ofPtr<ofxHTTPServerDefaultRoute> defaultRoute;
    ofPtr<ofxWebSocketRoute>         websocket;

};

inline ofxWebSocketServerBasic::Settings::Settings() {
    server    = ServerSettings();
    route     = RouteSettings();
    websocket = WebSocketSettings();
}
