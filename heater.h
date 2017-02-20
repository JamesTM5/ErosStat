void heatOnOff () {
  int level = digitalRead(DHT1PIN);
  int target = V24; 
  if (level <= target) {
    digitalWrite (RELAY1HEAT, HIGH);
  }
  else if (level > target) {
    digitalWrite (RELAY1HEAT, LOW);
  }
  else {
    Serial.print ("heater error");
  }
};
