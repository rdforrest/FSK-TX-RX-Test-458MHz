void loop() {
  wdt_reset(); //reset Watchdog in main loop
  currentMillis = millis(); // capture time for Failsafe function

  // check if the receive flag is set
  if (receivedFlag) {

    // reset the failsafe delay timer
    previousMillis = currentMillis;

    // disable the interrupt service routine while
    // processing the data
    enableInterrupt = false;

    // reset flag
    receivedFlag = false;

    // you can read received data as an Arduino String
    //String str;
    //int state = radio.readData(str);

    // you can also read received data as byte array
    byte byteArr[8];
    int state = radio.readData(byteArr, 8);

    // Print stick outputs
    for (int i = 2; i < 8; i++)   //display all channels
    {
      Serial.print(byteArr[i]);
      Serial.print("\t"); //tab
    }

    // print byte array
    Serial.print("Stick output  ");
    Serial.print("\n"); //newline
    rudder = byteArr[2];
    stern_plane = byteArr[3];
    throttle = byteArr[4];
    dive = byteArr[5];
    aux1 = byteArr[6];
    aux2 = byteArr[7];
    Serial.print("\n"); //newline

    if (state == ERR_NONE) {
      // packet was successfully received
      // Serial.println(F("[RF69] Received packet!"));

      // print data of the packet
      // Serial.print(F("[RF69] Data:\t\t"));
      // Serial.println(str);

      // print RSSI (Received Signal Strength Indicator)
      // of the last received packet
      Serial.print(F("[RF69] RSSI:\t\t"));
      Serial.print(radio.getRSSI());
      Serial.println(F(" dBm"));

    } else if (state == ERR_CRC_MISMATCH) {
      // packet was received, but is malformed
      Serial.println(F("CRC error!"));

    } else {
      // some other error occurred
      Serial.print(F("failed, code "));
      Serial.println(state);

    }

    // put module back to listen mode
    radio.startReceive();

    // we're ready to receive more packets,
    // enable interrupt service routine
    enableInterrupt = true;

    // servo.writes to (pos);
    servo1.write(rudder);
    servo2.write(stern_plane);
    servo3.write(throttle);
    servo4.write(dive);
    servo5.write(aux1);
    servo6.write(aux2);

  }

  // Failsafe loop
  else {
    if (currentMillis - previousMillis >= interval) {
      Serial.println("Failsafe activated");
      // FAILSAFE values (0 to 250)
      rudder = 50;
      stern_plane = 50;
      throttle = 125;
      dive = 50;
      aux1 = 50;
      aux2 = 50;

      // failsafe servo.writes to (pos);
      servo1.write(rudder);
      servo2.write(stern_plane);
      servo3.write(throttle);
      servo4.write(dive);
      servo5.write(aux1);
      servo6.write(aux2);


      // Reset the processor
      resetFunc();

    }

  }
}
