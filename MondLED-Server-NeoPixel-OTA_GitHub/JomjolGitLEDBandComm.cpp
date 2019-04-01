#include "JomjolGitLEDBandComm.h"
#include <EEPROM.h>


// Constructor
LEDBandCommLibrary::LEDBandCommClass::LEDBandCommClass(int _pin, int _num_led)
{
  strip = Adafruit_NeoPixel(_num_led, _pin, NEO_GRB + NEO_KHZ800);
//  strip = Adafruit_NeoPixel(_num_led, _pin, NEO_GRBW + NEO_KHZ800);
  blue = 255; green = 255; red = 255;			// inital white;
  brightness = 255;
  isOn = false;
}

void LEDBandCommLibrary::LEDBandCommClass::UpdateLED()
{
	if (isOn)
	{
		LightOn();
	}
}


void LEDBandCommLibrary::LEDBandCommClass::setColor(int _blue, int _green, int _red, int _brightness)
{
	blue = _blue;
	green = _green;
	red = _red;
	brightness = _brightness;
	UpdateLED();
}

void LEDBandCommLibrary::LEDBandCommClass::setBlue(int _blue)
{
	blue = _blue;
	UpdateLED();
}

void LEDBandCommLibrary::LEDBandCommClass::setGreen(int _green)
{
	green = _green;
	UpdateLED();
}

void LEDBandCommLibrary::LEDBandCommClass::setRed(int _red)
{
	red = _red;
	UpdateLED();
}

void LEDBandCommLibrary::LEDBandCommClass::setBrightness(int _brightness)
{
	brightness = _brightness;
	UpdateLED();
}


void LEDBandCommLibrary::LEDBandCommClass::setup()
{
  strip.setBrightness(brightness);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  colorWipe(strip.Color(0, 0, 0, 0), 0); // Aus
  LoadFromEEPROM();
  UpdateLED();
}

void LEDBandCommLibrary::LEDBandCommClass::LightOn()
{
  Serial.println("LEDBandCommClass - LightOn");
  strip.show(); // Initialize all pixels to 'off'
  colorWipe(strip.Color(blue, green, red, brightness), 0);
  isOn = true;
  SaveToEEPROM();
}

void LEDBandCommLibrary::LEDBandCommClass::LightOff()
{
  Serial.println("LEDBandCommClass - LightOff");
  colorWipe(strip.Color(0, 0, 0, 0), 0); 
  isOn = false;
  SaveToEEPROM();
}


void LEDBandCommLibrary::LEDBandCommClass::colorWipe(uint32_t c, uint8_t wait)
{
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}


void LEDBandCommLibrary::LEDBandCommClass::SaveToEEPROM()
{
  byte b0, b1, b2, b3, b4;
  Serial.println("Speichere in EEPROM-Status");
  EEPROM.begin(50);

  b0 = isOn;
  b1 = red & 0xff;
  b2 = green & 0xff;
  b3 = blue & 0xff;
  b4 = brightness & 0xff;
  
  String erg;
    erg = String(b0) + "," + String(b1) + "," + String(b2) + "," + String(b3) + "," + String(b4);
  Serial.println(erg);

  EEPROM.write(0, b0);
  EEPROM.write(1, b1);
  EEPROM.write(2, b2);
  EEPROM.write(3, b3);
  EEPROM.write(4, b4);
  EEPROM.commit();                      // Only needed for ESP8266 to get data written
  EEPROM.end(); 
}

void LEDBandCommLibrary::LEDBandCommClass::LoadFromEEPROM()
{
	byte b0, b1, b2, b3, b4;
    EEPROM.begin(50);

    b0 = EEPROM.read(0);
    b1 = EEPROM.read(1);
    b2 = EEPROM.read(2);
    b3 = EEPROM.read(3);
    b4 = EEPROM.read(4);  
	
	String erg;
    erg = String(b0) + "," + String(b1) + "," + String(b2) + "," + String(b3) + "," + String(b4);
    Serial.println(erg);


	isOn = b0;
	red = b1;
	green = b2;
	blue = b3;
	brightness = b4;

    Serial.println("Speichere in EEPROM-Status");
}
