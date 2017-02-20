char* vPinNameList[] {"fog", "air", "uv", "pump", "led"};
int relayVPin[] {V31, V32, V33, V34, V35};
int relayDPin[] {RELAY2FOG, RELAY3AIR, RELAY4UV, RELAY5PUMP, RELAY6LED};
int ledVPinNameList[] {FogLED, AirLED, UVLED, PumpLED, LedLED};
char* Date;
char* Time;

 BLYNK_WRITE(fromApp) {
  sprintf(Date, "%02d/%02d/%04d",  day(), month(), year());
  sprintf(Time, "%02d:%02d:%02d", hour(), minute(), second());
  
  TimeInputParam t(param);

  int nowseconds;
  int startseconds;
  int stopseconds;
  char* vPinName;
  int fromApp;
  int toRelay;
  
  Serial.printf("Checked %i at:",vPinName);
  Serial.println(Time);
  
    if (t.hasStartTime()) // Process start time
    {
      Serial.println(String("relay due to start: ") + t.getStartHour() + ":" + t.getStartMinute());
    }
    if (t.hasStopTime()) // Process stop time
    {
      Serial.println(String("relay due to stop : ") + t.getStopHour() + ":" + t.getStopMinute());
    }
    
    nowseconds = ((hour() * 3600) + (minute() * 60) + second());
    startseconds = (t.getStartHour() * 3600) + (t.getStartMinute() * 60);
    if(nowseconds >= startseconds){    
      Serial.print("relay started at");
      Serial.println(String(" ") + t.getStartHour() + ":" + t.getStartMinute());
      if(nowseconds <= startseconds + 90){    // 90s on 60s timer ensures 1 trigger command is sent
      // code to operate the relay
       digitalWrite(toRelay, HIGH);
      }      
    }
    else{
      Serial.printf("%i not started today",vPinName);
      // nothing more to do here, waiting for change to be made later today      
    }
    stopseconds = (t.getStopHour() * 3600) + (t.getStopMinute() * 60);
    if(nowseconds >= stopseconds){
      Serial.printf("%i STOPPED at",vPinName);
      Serial.println(String(" ") + t.getStopHour() + ":" + t.getStopMinute());
      if(nowseconds <= stopseconds + 90){   // 90s on 60s timer ensures 1 trigger command is sent
      // code to operate the relay
      digitalWrite(toRelay, LOW);      
      }              
    }
    else if(nowseconds >= startseconds){  // only show if relay has already started today
        Serial.printf("%i is running",vPinName);
        // nothing more to do here, waiting for relay to be turned off later today
    }          
  else {
    Serial.printf("%i inactive",vPinName);
    // nothing to do, check again in 1 minute    
  }
  Serial.println();
};

void triggerRelayQuery(){
  if(year() != 1970){
    Blynk.syncVirtual(V17); // sync timeinput widget    
  }
  else {
  }
  for (int relay = 0; relay < 7; relay++) {
    char* vPinName = vPinNameList[relay];
    int fromApp = relayVPin[relay];
    int toRelay = relayDPin[relay];
    int ledName = ledVPinNameList[relay];
    BLYNK_WRITE();
    if (relayDPin[relay] = HIGH) {
      Blynk.virtualWrite(ledName, HIGH);
    }
    else if (relayDPin[relay] = LOW) {
      Blynk.virtualWrite(ledName, LOW);
    }
  }
};
