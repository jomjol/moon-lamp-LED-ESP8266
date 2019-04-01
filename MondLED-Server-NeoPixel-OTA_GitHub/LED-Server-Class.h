#include "JomjolGitServerClass.h"
#include "JomjolGitLEDBandComm.h"

#ifndef _LEDBand_Server_Library
#define _LEDBand_Server_Library

namespace LEDBandServerLibrary
{

  class LEDBandServer: public LEDBandCommLibrary::LEDBandCommClass, public GitServerLibrary::ServerClass
  {
    private:
      void handleCommand(String _param, String _value, String _modus);

      void doLightOn();
      void doLightOff();


    public:
      LEDBandServer(int _pin, int _num_led) : LEDBandCommLibrary::LEDBandCommClass(_pin, _num_led), GitServerLibrary::ServerClass() {} ;

      void setup();
  };
}

#endif
