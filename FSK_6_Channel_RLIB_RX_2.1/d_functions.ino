// Reset function in software to kick start
void resetFunc() {

  //}
  /*
    void beep() {   // Sounder output
    pinMode(7, OUTPUT);
    digitalWrite(7, HIGH);   // Test. Turn the sounder on D7 on
    delay(500);              // wait
    digitalWrite(7, LOW);   // turn off
  */
}

void ACK() {     // Function to transmit an ACK and put radio to sleep
  radio.sleep();  // set to 'sleep' between Tx & Rx
  // wait a bit before transmitting again
  delay(500); // was 100

  // disable the interrupt service routine while processing the data
  enableInterrupt = false;
  // reset flag
  bool transmittedFlag = false;

  // you can also transmit byte array up to 64 bytes long

  // Test Telemetry data
  int amps = 95;
  int strength = abs(radio.getRSSI()); // make positive
  int volts = 107;

  byte byteArr1[] = {amps, strength, volts};

  // Print packet data received
  for (int i = 0; i < 3; i++)   //display all channels
  {
    Serial.print(byteArr[i]);
    Serial.print("\t"); //tab
  }

  // print telemetry data sent
  Serial.print("Telemetry sent");
  Serial.print("\n"); //newline
  int   tel1 = byteArr[0];
  int   tel2 = byteArr[1];
  int   tel3 = byteArr[2];
  Serial.print("\n"); //newline

  int state = radio.startTransmit(byteArr, 8);

  radio.sleep();    // set to 'sleep' between Tx & Rx
  state = radio.startReceive();  // put module back to listen mode
  enableInterrupt = true;
}
