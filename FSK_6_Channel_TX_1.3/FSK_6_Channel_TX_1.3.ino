/*
   Uses RadioLib library
   For 6 channel radio control.
   For Adafruit RFM69HCW Radio Transceiver Breakout Board
   For Nano.
   Arduino serial data default is, serial baud rate (9600) and 8 data bits, no parity,no stop,LSB and not inverted - the default

   ppm reader for transmitter "buddy box" output.
   ppmReaderAccurate-1.1
   Thanks to Jonathan Askey for introducing this to me. RDF
   Fast and accurate PPM reader

   Note values will need to be halved to bring them back to real world values

   Source
   https://forum.arduino.cc/index.php?topic=85603.0

   Note due to increased accuracy values are read to 0.5us
   To get the array values back to real world full 'us' values the array value must be divided by 2

  Hardware connections
 *  * use pin 8 as ppm in

   Note - ICR = the "Input Capture Register"

*/

/*
   RadioLib RF69 Transmit with Interrupts Example

   This example transmits FSK packets with one second delays
   between them. Each packet contains up to 64 bytes
   of data, in the form of:
    - Arduino String
    - null-terminated char array (C-string)
    - arbitrary binary data (byte array)

   For default module settings, see the wiki page
   https://github.com/jgromes/RadioLib/wiki/Default-configuration#rf69sx1231

   For full API reference, see the GitHub Pages
   https://jgromes.github.io/RadioLib/

  Frequency set to 458.75 MHz and Bandwidth set to 62.5 (Module does not seem to work lower than this.)
   by RDF in the RF69.h file in Arduno/libraries/RadioLib/src/modules/RF 69/RF69.h
*/

/*
  Hardware notes:
  For Adafruit RFM69HCW Radio Transceiver Breakout Board
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
