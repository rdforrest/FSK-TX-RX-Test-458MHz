# FSK-TX-RX-Test-458MHz

Very simple and basic software to enable testing of FSK modulation system for model submarine use at 458 MHz using the RFM69HCW chip. This has been tested and gives a range of about 30m at a depth of 0.5m. Test details: https://www.theassociationofmodelsubmariners.com/t83p225-openlrs-on-458mhz-and-433mhz-and-submarines#11599Only 6 channels and 4 times a second refresh rate used to provide a minimalistic control system for test purposes only. Has a failsafe which is activated after 10 seconds of no signal. The failsafe values included in the receiver software are those for my model sub setup but can be changed in the software. Uses standard defaults for RadioLib but with Frequency set to 458.75 and Bandwidth set to 62.5kHz for the UK (Thanks to Simon H for the suggestion. Edit  by RDF in the RF69.h file in Arduno/libraries/RadioLib/src/modules/RF 69/RF69.h.) Thanks to Jonathan Askey for suggesting and providing the accurate ppm reader. (The simpler ppm routine by David Vella gives an interrupt clash.) The later RX  2.1 and TX 2.6 sketches work for radio control but the Telemetry function is not working. Any help would be appreciated. (Thanks to Simon H for the help.) Hardware: Nanos for TX and RX at 5v.


Standard Defaults: RF69/SX1231
Begin method:
Carrier frequency: 434.0 MHz
Bit rate: 48.0 kbps
Frequency deviation: 50.0 kHz (single-sideband)
Receiver bandwidth: 125.0 kHz
Output power: 10 dBm
Preamble length: 16 bits
Other:
Packet length mode: variable, maximum of RF69_MAX_PACKET_LENGTH bytes (length byte included in packet)
Sync word: 0x12 0xAD
Data shaping B-T product: 0 (plain 2-FSK, no Gaussian filter applied)
Encoding: NRZ (non-return to zero - no encoding)
CRC: enabled
Address filtering: disabled
AES encryption: disabled
Inaccessible:
Over-current protection: enabled
Automatically clear packet on CRC mismatch: enabled
