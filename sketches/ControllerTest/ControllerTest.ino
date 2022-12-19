/*******************************************************************************
 * 3DO controller input library.
 * https://github.com/sonik-br/ThreedoLib
 * 
 * The library depends on greiman's DigitalIO library.
 * https://github.com/greiman/DigitalIO
 * 
 * I recommend the usage of SukkoPera's fork of DigitalIO as it supports a few more platforms.
 * https://github.com/SukkoPera/DigitalIO
 * 
 * 
 * This sketch is ready to use on a Leonardo/Pro Micro but may work on any
 * arduino with the correct number of pins and proper setup.
*/

#include <ThreedoLib.h>

#define THREEDOPIN_CLOCK 4  // (db9 7)
#define THREEDOPIN_DOUT  5  // (db9 6)
#define THREEDOPIN_DIN   13 // (db9 9)

#define ENABLE_SERIAL_DEBUG

ThreedoPort<THREEDOPIN_CLOCK, THREEDOPIN_DOUT, THREEDOPIN_DIN> tdo;

#ifdef ENABLE_SERIAL_DEBUG
#define dstart(spd) do {Serial.begin (spd); while (!Serial) {}} while (0);
#define debug(...) Serial.print (__VA_ARGS__)
#define debugln(...) Serial.println (__VA_ARGS__)
#else
#define dstart(...)
#define debug(...)
#define debugln(...)
#endif


#define DIGITALSTATE(D) \
if(sc.digitalJustPressed(D)) { \
  debugln(F("Digital pressed: " #D)); \
} else if(sc.digitalJustReleased(D)) {\
  debugln(F("Digital released: " #D)); \
}

#define DEVICE(A, B) \
if(A == B) {\
  debug(#B); \
}

void printDeviceType (const ThreedoDeviceType_Enum d){
  DEVICE(d, THREEDO_DEVICE_NONE)
  DEVICE(d, THREEDO_DEVICE_NOTSUPPORTED)
  DEVICE(d, THREEDO_DEVICE_PAD)
}

void printButtons(const ThreedoController& sc) {
  DIGITALSTATE(THREEDO_DOWN)
  DIGITALSTATE(THREEDO_UP)
  DIGITALSTATE(THREEDO_RIGHT)
  DIGITALSTATE(THREEDO_LEFT)
  DIGITALSTATE(THREEDO_A)
  DIGITALSTATE(THREEDO_B)
  DIGITALSTATE(THREEDO_C)
  DIGITALSTATE(THREEDO_P)
  DIGITALSTATE(THREEDO_X)
  DIGITALSTATE(THREEDO_R)
  DIGITALSTATE(THREEDO_L)
}


void setup() {
  //Init the library.
  tdo.begin();
  
  delay(5);

  dstart (115200);
  debugln (F("Powered on!"));
}


void loop() {
  static unsigned long idleTimer = 0;
  static uint8_t lastControllerCount = 0;
  static ThreedoDeviceType_Enum dtype[THREEDO_MAX_CTRL];
  
  const unsigned long start = micros();
  
  //Call update to read the controller(s)
  tdo.update();

  //Time spent to read controller(s) in microseconds
  const unsigned long delta = micros() - start;

  //Get the number of connected devices
  const uint8_t joyCount = tdo.getControllerCount();
  //debugln(joyCount);
  if (lastControllerCount != joyCount) {
    debug(F("Connected devices: "));
    debugln(joyCount);
  }

  bool isIdle = true;
  for (uint8_t i = 0; i < joyCount; i++) {
    const ThreedoController& sc = tdo.get3doController(i);
    if (sc.stateChanged()) {
      isIdle = false;
      //hatData = sc.hat();
      //dtype = sc.deviceType();

      //Controller just connected.
      if (sc.deviceJustChanged()) {
        debug(F("Device changed from "));
        printDeviceType(dtype[i]);
        debug(F(" to "));
        dtype[i] = sc.deviceType();
        printDeviceType(dtype[i]);
        debugln();
      }

      //bool isPressed = sc.digitalPressed(THREEDO_A);
      
      printButtons(sc);
    }
    
  }

  //Controller has been disconnected?
  if (lastControllerCount > joyCount) {
    for (uint8_t i = joyCount; i < lastControllerCount; i++) {
      const ThreedoController& sc = tdo.get3doController(i);
      if (sc.stateChanged() && sc.deviceJustChanged()) {
        debugln(F("Device disconnected"));
        dtype[i] = THREEDO_DEVICE_NONE;
      }
    }
  }
  
  lastControllerCount = joyCount;

  if(isIdle) {
    if (millis() - idleTimer >= 3000) {
      idleTimer = millis();
      debug(F("Idle. Read time: "));
      debugln(delta);
    }
  } else {
    idleTimer = millis();
    debug(F("Read time: "));
    debugln(delta);
  }

  //Keep clock high for some time while pad stabilize it's data
  if(joyCount == 0 || lastControllerCount != joyCount) {
    //Nothing connected, or number of devices changed. Do a longer rest
    delayMicroseconds(500);
  } else {
    //100us per device seems enough
    delayMicroseconds(100*joyCount);
  }
  //Tested with 2 digital pads
  
}
