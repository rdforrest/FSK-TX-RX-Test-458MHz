#include <avr/wdt.h>
#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int rudder;
int stern_plane;
int throttle;
int dive;
int aux1;
int aux2;

byte byteArr[8];

unsigned long previousMillis = 0;     // for time delay used in Failsafe
const long interval = 5000;           // set time interval (milliseconds)
unsigned long currentMillis = millis();


// include the library
#include <RadioLib.h>

// RF69 has the following connections:
// CS pin:    10
// DIO0 pin:  2
// RESET pin: 3
//RF69 radio = new Module(10, 2, 3);
RF69 radio = new Module(4, 3, 2, 3); //RDF

// or using RadioShield
// https://github.com/jgromes/RadioShield
//RF69 radio = RadioShield.ModuleA;

void setup() {
  Serial.begin(9600);

  // make a delay before enable WDT
  // this delay help to complete all initial tasks
  delay(2000);
  wdt_enable(WDTO_4S); // For Nano
  // wdt_enable(WDT_PERIOD_4KCLK_gc); // For Nano Every

  servo1.attach(5);  // attaches the servo on a pin  to the servo object. Using pin 4 gives jitter problems.
  servo2.attach(6);
  servo3.attach(7);
  servo4.attach(8);
  servo5.attach(9);
  servo6.attach(10);


  // initialize RF69 with default settings
  Serial.print(F("[RF69] Initializing ... "));
  int state = radio.begin();
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

  // set the function that will be called
  // when new packet is received
  radio.setDio0Action(setFlag);

  // start listening for packets
  Serial.print(F("[RF69] Starting to listen ... "));
  state = radio.startReceive();
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

  // if needed, 'listen' mode can be disabled by calling
  // any of the following methods:
  //
  // radio.standby()
  // radio.sleep()
  // radio.transmit();
  // radio.receive();
  // radio.readData();
}

// flag to indicate that a packet was received
volatile bool receivedFlag = false;

// disable interrupt when it's not needed
volatile bool enableInterrupt = true;

// this function is called when a complete packet
// is received by the module
// IMPORTANT: this function MUST be 'void' type
//            and MUST NOT have any arguments!
void setFlag(void) {
  // check if the interrupt is enabled
  if (!enableInterrupt) {
    return;
  }

  // we got a packet, set the flag
  receivedFlag = true;
}
