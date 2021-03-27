// Timer routine for ppm
void setup_timer1() {
  //WGM -> Fast PWM
  //Prescaler -> 1/8
  //Compare Output Mode - > non-inverting mode
  //Input capture interrupt enable
  TIMSK1 &= ~( _BV(TOIE1) | _BV(ICIE1) | _BV(OCIE1A) | _BV(OCIE1B));
  TCCR1B &= ~(_BV(ICNC1));
  TCCR1A |= _BV(WGM11) | _BV(WGM10) | _BV(COM1A1) | _BV(COM1B1);
  TCCR1B |= _BV(WGM12) | _BV(WGM13) | _BV(ICES1);
  TCCR1B |= _BV(CS11);
  TCCR1B &= ~( _BV(CS12) | _BV(CS10) );
  TCCR1A &= ~( _BV(COM1A0) | _BV(COM1B0));
  TIMSK1 |= (1 << ICIE1);
  OCR1A = 0xFFFF;
  OCR1B = 0x0;
}

// Interrupt routine for ppm
ISR(TIMER1_CAPT_vect) {

  static unsigned int lasticr; //Input Capture Register at at last capture
  static unsigned char currentChannel; //current channel

  unsigned int licr;

  licr = ICR1 - lasticr;
  lasticr = ICR1;

  if (licr > 5000)
  { //pulse too long, means start of new frame
    currentChannel = 0;
  }
  else if (licr > 1000)
  {
    //pulse good, take reading, go to next channel
    ppmValues[currentChannel] = licr;
    if (currentChannel < 8)
    {
      currentChannel++;
    }
  }
  else {
    //too short, nothing to see here
  }

}

void beep() {   // Sounder output
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);   // Test. Turn the sounder on D7 on
  delay(500);              // wait
  digitalWrite(7, LOW);   // turn off
}

void ACK() {     // Function to receive an ACK and put radio to sleep
  radio.sleep();  // set to 'sleep' between Tx & Rx
  delay(500); //
  if (receivedFlag) {
    // disable the interrupt service routine while processing the data
    enableInterrupt = false;
    // reset flag
    bool receivedFlag = false;

    // you can read received data as an Arduino String
    //String str;
    //int state = radio.readData(str);

    // you can also read received data as byte array

    int state = radio.readData(byteArr, 8);


    if (state == ERR_NONE) {
      // packet was successfully received
      Serial.println(F("[RF69] Received packet!"));

      // Print packet data received
      for (int i = 2; i < 5; i++)   //display all channels
      {
        Serial.print(byteArr[i]);
        Serial.print("\t"); //tab
      }

      // print telemetry data
      Serial.print("Telemetry ");
      Serial.print("\n"); //newline
      int   tel1 = byteArr[2];
      int   tel2 = byteArr[3];
      int   tel3 = byteArr[4];
      Serial.print("\n"); //newline

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


      radio.sleep();    // set to 'sleep' between Tx & Rx
      // wait before transmitting again
      //  delay(500); // was 1000
      state = radio.startTransmit(byteArr, 8);
      // we're ready to send more packets,
      // enable interrupt service routine
      enableInterrupt = true;
    }

  }

}
