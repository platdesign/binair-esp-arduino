#include <Arduino.h>
#include <Binair.h>



void setup() {
  BINAIR("[vendor]", "[product]", "[token]", "[platform]", "[version]");
}


void loop() {
	Binair.check();
}
