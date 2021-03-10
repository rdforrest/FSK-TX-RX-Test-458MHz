void loop() {
  wdt_reset(); //reset Watchdog in main loop
  currentMillis = millis(); // capture time for Failsafe function

  if (receivedFlag) {

    // reset the failsafe delay timer
    previousMillis = currentMillis;

    // Receive Section
    // disable the interrupt service routine while processing the data
    enableInterrupt = false;

    // reset flag
    receivedFlag = false;

    // you can read received data as an Arduino String
    //String str;
    //int state = radio.readData(str);

    // you can also read received data as byte array
    byte byteArr[8];
    int   state = radio.readData(byteArr, 8);

    // Print stick outputs
    for (int i = 2; i < 8; i++)   //display all channels
    {
      Serial.print(byteArr[i]);
      Serial.print("\t"); //tab
    }

    // print byte array
    Serial.print("Stick output  ");
    Serial.print("\n"); //newline
    ch1 = byteArr[2];
    ch2 = byteArr[3];
    ch3 = byteArr[4];
    ch4 = byteArr[5];
    ch5 = byteArr[6];
    ch6 = byteArr[7];
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
    servo1.write(ch1);
    servo2.write(ch2);
    servo3.write(ch3);
    servo4.write(ch4);
    servo5.write(ch5);
    servo6.write(ch6);

  }

  // Failsafe loop
  else {
    // set time interval (milliseconds)
    if (currentMillis - previousMillis >= 5000) {
      Serial.println("Failsafe activated");
      // FAILSAFE values (0 to 250)
      ch1 = 50;
      ch2 = 130;
      ch3 = 27;
      ch4 = 27;
      ch5 = 50;
      ch6 = 95;

      // failsafe servo.writes to (pos);
      servo1.write(ch1);
      servo2.write(ch2);
      servo3.write(ch3);
      servo4.write(ch4);
      servo5.write(ch5);
      servo6.write(ch6);


      // Reset the processor
      resetFunc();

    }

  }
}
