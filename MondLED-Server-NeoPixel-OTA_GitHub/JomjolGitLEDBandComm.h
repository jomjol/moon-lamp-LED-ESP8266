#ifndef _LEDBand_Comm_Library
#define _LEDBand_Comm_Library

#include <arduino.h>
#include <Adafruit_NeoPixel.h>


namespace LEDBandCommLibrary
{
  class LEDBandCommClass
  {
    private:
      Adafruit_NeoPixel strip; 

      int brightness;

      void colorWipe(uint32_t c, uint8_t wait);
	  
	  void SaveToEEPROM();
	  void LoadFromEEPROM();
	  void UpdateLED();

    public:
	  int blue, green, red;
	  bool isOn;

      LEDBandCommClass(int _pin, int _num_led);
	  
	  void setColor(int _blue, int _green, int _red, int _brightness = 255);
	  void setBlue(int _blue);
	  void setGreen(int _green);
	  void setRed(int _red);
	  void setBrightness(int _brightness);
	        
      void setup();

      void LightOn();
      void LightOff();
  };
}
#endif
