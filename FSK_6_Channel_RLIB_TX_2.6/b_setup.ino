
// include the library
#include <RadioLib.h>

unsigned int ppmValues[8];
int pulse = 0;

int ch1;
int ch2;
int ch3;
int ch4;
int ch5;
int ch6;

byte byteArr1[8];
byte byteArr[8];

// flag to indicate that a packet was received
volatile bool receivedFlag = false;

// RF69 has the following connections:
// CS pin:    10
// DIO0 pin:  2
// RESET pin: 3
//RF69 radio = new Module(10, 2, 3);
RF69 radio = new Module(4, 3, 2, 3); //RDF

// or using RadioShield
// https://github.com/jgromes/RadioShield
//RF69 radio = RadioShield.ModuleA;

// save transmission state between loops
int transmissionState = ERR_NONE;

void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT); // ppm input
  setup_timer1();

  // initialize RF69 with default settings
  Serial.print(F("[RF69] Initializing ... "));
  int state = radio.begin();
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
    beep ();
  }

  beep (); // Switch on beeps
  delay(500);
  beep ();

  // set the function that will be called
  // when packet transmission is finished
  radio.setDio0Action(setFlag);

  // NOTE: some RF69 modules use high power output,
  //       those are usually marked RF69H(C/CW).
  //       To configure RadioLib for these modules,
  //       you must call setOutputPower() with
  //       second argument set to true.
  /*
    Serial.print(F("[RF69] Setting high power module ... "));
    state = radio.setOutputPower(20, true);
    if (state == ERR_NONE) {
      Serial.println(F("success!"));
    } else {
      Serial.print(F("failed, code "));
      Serial.println(state);
      while (true);
    }
  */

  Serial.print(F("[RF69] Setting high power module ... "));
  state = radio.setOutputPower(20, true);
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

  // start transmitting the first packet
  Serial.print(F("[RF69] Sending first packet ... "));

  // you can transmit C-string or Arduino string up to
  // 64 characters long
  transmissionState = radio.startTransmit("Hello World!");

  // you can also transmit byte array up to 64 bytes long
  /*
    byte byteArr[] = {0x01, 0x23, 0x45, 0x67,
                      0x89, 0xAB, 0xCD, 0xEF};
    state = radio.startTransmit(byteArr, 8);
  */
}

// flag to indicate that a packet was sent
volatile bool transmittedFlag = false;

// disable interrupt when it's not needed
volatile bool enableInterrupt = true;

// this function is called when a complete packet
// is transmitted by the module
// IMPORTANT: this function MUST be 'void' type
//            and MUST NOT have any arguments!
void setFlag(void) {
  // check if the interrupt is enabled
  if (!enableInterrupt) {
    return;
  }

  // we sent a packet, set the flag
  transmittedFlag = true;
}
