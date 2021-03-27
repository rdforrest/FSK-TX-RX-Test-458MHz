// March 2021 This works with the exception of the Telemetry section.
/*
  Uses RadioLib library
  For 6 channel radio control.
  For Adafruit RFM69HCW Radio Transceiver Breakout Board
  For Nano
  Arduino serial data default is, serial baud rate (9600) and 8 data bits, no parity,no stop,LSB and not inverted - the default
*/

/*
   RadioLib RF69 Receive with Interrupts Example

   This example listens for FSK transmissions and tries to
   receive them. Once a packet is received, an interrupt is
   triggered.

   For default module settings, see the wiki page
   https://github.com/jgromes/RadioLib/wiki/Default-configuration#rf69sx1231

   For full API reference, see the GitHub Pages
   https://jgromes.github.io/RadioLib/

  Frequency set to 458.75 MHz and Bandwidth set to 62.5 (Module does not seem to work lower than this.)
   by RDF in the RF69.h file in Arduno/libraries/RadioLib/src/modules/RF 69/RF69.h

*/

/*
  Hardware notes:
  For Adafruit RF69 Radio Transceiver Breakout Board
  Connections for Nano (RDF)
  Board 5V to radio VIN
  Board GND to radio GND
  Board SCK (D13) to radio SCK
  Board MOSI (D11) to radio MOSI
  Board MISO (D12) to radio MISO
  Board (D4) to radio CS (or any other digital I/O pin)
  Board (D2) to radio RST (or any other digital I/O pin)
  Board (D3) to radio G0 (Interrupt)

  5v sounder on pin D7
*/

/*
  RadioHead library (good reference);
  http://www.airspayce.com/mikem/arduino/RadioHead/
*/
