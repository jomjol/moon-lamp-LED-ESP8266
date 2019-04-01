#include "LED-Server-Class.h"

void LEDBandServerLibrary::LEDBandServer::handleCommand(String _param, String _value, String _modus)
{
  if (_param.equals("setColor"))
  {
    String cs1, cs2, cs3, erg;
    int c1, c2, c3;
    int zw1, zw2;
    zw1 = _value.indexOf(',');
    zw2 = _value.indexOf(',', zw1+1);

    cs1 = _value.substring(0, zw1);
    cs2 = _value.substring(zw1+1, zw2);
    cs3 = _value.substring(zw2+1);

    c1 = cs1.toInt();
    c2 = cs2.toInt();
    c3 = cs3.toInt();

    setColor(c1, c2, c3);
    
    erg = "Farbe: " + cs1 + " - " + cs2 + " - " + cs3;
    send(200, "text/plain", erg); 
    delay(0);
    return;
  }
  if (_param.equals("getColor"))
  {
    String cs1, cs2, cs3, cs4, erg;
    cs1 = String(blue);
    cs2 = String(green);
    cs3 = String(red);
    cs4 = "false";
    if (isOn)
      cs4 = "true";
    erg = cs1 + "," + cs2 + "," + cs3 + "," + cs4;
    send(200, "text/plain", erg); 
    delay(0);
    return;
  }

  send(200, "text/plain", "Befehl unbekannt - Done"); 
}

void LEDBandServerLibrary::LEDBandServer::doLightOn()
{
  Serial.println("Light On");
  LightOn();
  send(200, "text/plain", "Light On");
}

void LEDBandServerLibrary::LEDBandServer::doLightOff()
{
  Serial.println("Light Off");
  LightOff();
  send(200, "text/plain", "Light Off");
}


void LEDBandServerLibrary::LEDBandServer::setup()
{
  LEDBandCommLibrary::LEDBandCommClass::setup();
  
  on("/on", std::bind(&LEDBandServer::doLightOn, this));
  on("/off", std::bind(&LEDBandServer::doLightOff, this));
  
  GitServerLibrary::ServerClass::setup();
}
