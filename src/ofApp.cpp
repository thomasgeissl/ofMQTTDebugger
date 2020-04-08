#include "ofApp.h"

ofApp::ofApp(std::string host, int port, std::string topic) : _host(host), _port(port), _topic(topic), _publisher(false)
{
}
ofApp::ofApp(std::string host, int port, std::string topic, std::string message) : _host(host), _port(port), _topic(topic), _message(message), _publisher(true)
{
}
void ofApp::setup()
{
    _client.begin(_host, _port);
    std::string name = "ofMQTTDebugger_";
    name += ofToString(ofRandomf());
    _client.connect(name);

    ofAddListener(_client.onOnline, this, &ofApp::onOnline);
    ofAddListener(_client.onOffline, this, &ofApp::onOffline);
    ofAddListener(_client.onMessage, this, &ofApp::onMessage);
}

void ofApp::update()
{
    _client.update();
}

void ofApp::exit()
{
    _client.disconnect();
}

void ofApp::onOnline()
{
    if (_publisher)
    {
        _client.publish(_topic, _message);
        ofExit();
    }
    else
    {
        _client.subscribe(_topic);
    }
}

void ofApp::onOffline()
{
}

void ofApp::onMessage(ofxMQTTMessage &msg)
{
    ofLog() << "message: " << msg.topic << " - " << msg.payload;
}
