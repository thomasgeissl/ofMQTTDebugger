#pragma once

#include "ofMain.h"
#include "ofxMQTT.h"

class ofApp : public ofBaseApp
{
public:
  ofApp(std::string host, int port, std::string topic);
  ofApp(std::string host, int port, std::string topic, std::string message);
  void setup();
  void update();
  void exit();

  void onOnline();
  void onOffline();
  void onMessage(ofxMQTTMessage &msg);

  ofxMQTT _client;
  std::string _host;
  int _port;
  std::string _topic;
  std::string _message;
  bool _publisher;
};