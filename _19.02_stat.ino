#include "blynk.h"
#include "rtc.h"
#include "pinList.h"
#include "DHTSensorRead.h"
#include "heater.h"
#include "relayManagement.h"

void setup() {

  wifiServerConnect();
  
  delay(1000);
  
  rtc.begin();
  Blynk.syncAll();

  dht1.begin();

  timer.setInterval(4000L, clockDisplay);
  timer.setInterval(2000L, activeToday);
  timer.setInterval(2000L, readDhtSensors);
  timer.setInterval(4000L, heatOnOff);
  timer.setInterval(60000L, triggerRelayQuery);
}

void loop() {
  if(Connected){
    Blynk.run();
  }
  
  timer.run();
}
