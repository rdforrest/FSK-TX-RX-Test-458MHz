
void loop() {

  // ppm input
  for (int i = 0; i < 8; i++)   //display all channels
  {
    ppmValues[i] = ((((ppmValues[i]) / 2) - 1000) / 4); // the array value is processed to bring it back to real world value
    byteArr[i] = ppmValues[i]; // Store in Byte array
    Serial.print(ppmValues[i]);
    Serial.print("  ");
  }

  // /*
  // Test
  Serial.print("\n"); //newline
  for (int i = 0; i < 8; i++)   //display all channels
  {
    Serial.print(byteArr[i]);
    Serial.print("\t"); //tab
  }
  Serial.print("\n"); //newline
  //*/

  // check if the previous transmission finished
  if (transmittedFlag) {
    // disable the interrupt service routine while
    // processing the data
    enableInterrupt = false;

    // reset flag
    transmittedFlag = false;

    if (transmissionState == ERR_NONE) {
      // packet was successfully sent
      Serial.println(F("transmission finished!"));

      // NOTE: when using interrupt-driven transmit method,
      //       it is not possible to automatically measure
      //       transmission data rate using getDataRate()

    } else {
      Serial.print(F("failed, code "));
      Serial.println(transmissionState);

    }

    // This delay was put into the ACK function to use the delay
    // wait before transmitting again
    //delay(250); // was 1000
    ACK ();  // Go to ACK function to receive data

    // send another one
    Serial.print(F("[RF69] Sending another packet ... "));

    // you can transmit C-string or Arduino string up to
    // 256 characters long
    //transmissionState = radio.startTransmit("Hello World!");

    // you can also transmit byte array up to 64 bytes long
    /*
      // Test
      byte byteArr[] = {0x01, 0x23, 0x45, 0x67,
                      0x89, 0xAB, 0xCD, 0xEF
                     };
    */

    int state = radio.startTransmit(byteArr, 8);


    // we're ready to send more packets,
    // enable interrupt service routine
    enableInterrupt = true;
  }

}
