#include "arduino_secrets.h"
/* 
  Sketch generated by the Arduino IoT Cloud Thing "Untitled"
  https://create.arduino.cc/cloud/things/ac381c83-fa10-4cfe-a345-ee185259f9b8 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  CloudContactSensor isRaining;
  CloudTemperatureSensor moduleTemp;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include "temperature.h"

#define LED_BUILTIN 2
#define PIN_D15_RAIN_METER 15 
// ESP32 DEV KIT V1: D15=GPIO15

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_D15_RAIN_METER, INPUT);
  
}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  
  moduleTemp = readCelsius();

  // u_int rainMeter = analogRead(PIN_D15_RAIN_METER);

  // rainingPercentage = analogRead(PIN_D15_RAIN_METER);
  
  // rainMeter = map(rainMeter, 0, 1023, 0, 100);
  // bool isSunny = (rainMeter < 20);

  bool isSunny = digitalRead(PIN_D15_RAIN_METER);
  isRaining = !isSunny;

  digitalWrite(LED_BUILTIN, isRaining ? HIGH : LOW);
  
  delay(1000);
}

void toggleLED() {
  bool isOn = !digitalRead(LED_BUILTIN);
  digitalWrite(LED_BUILTIN, isOn ? HIGH : LOW);
}