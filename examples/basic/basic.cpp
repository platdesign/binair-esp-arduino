#include <Arduino.h>
#include <Binair.h>



void setup() {
  BINAIR("platdesign", "pdhue", "123", "uno", "3.0.2");
}



void loop() {
	Binair.check();
}
