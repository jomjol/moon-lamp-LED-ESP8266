#ifndef _Server_Library
#define _Server_Library

#if defined(ESP32)
  #include <WebServer.h>
  typedef WebServer BaseWebServer;
#else
  #include <ESP8266WebServer.h>
  typedef ESP8266WebServer BaseWebServer;
#endif

namespace GitServerLibrary
{
  class ServerClass: public BaseWebServer
  {
    private:
      virtual void doCommand();
	  virtual void doReset();
      virtual void handleCommand(String _param, String _value, String _modus);

      virtual void handleRoot();

    public:
      ServerClass(uint16_t port = 80) : BaseWebServer(port){};

      virtual void setup();
      virtual void loop();
  };
}

#endif
