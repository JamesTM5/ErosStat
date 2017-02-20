#include <WidgetRTC.h>
#include <TimeLib.h>
#include <SPI.h>

WidgetRTC rtc;

BLYNK_ATTACH_WIDGET(rtc, V17);

void printDigits(int digits)
{
  Serial.print(":");
  if (digits < 10) {
    Serial.print('0');
  }
  Serial.print(digits);
}

void clockDisplay()
{
// Using this code you can call hour(), minute(), ... at any time to sync other widgets and so on.
  
  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  String currentDate = String(day()) + " " + month() + " " + year();
  Serial.print("Current time: ");
  Serial.print(currentTime);
  Serial.print(" ");
  Serial.print(currentDate);
  Serial.println();

// Send time to the App
  Blynk.virtualWrite(V1, currentTime);
// Send date to the App
  Blynk.virtualWrite(V2, currentDate);
}



void activeToday(){        // check if clock time needs updating and trigger it
  if(year() != 1970){
    Blynk.syncVirtual(V17); // sync timeinput widget    
  }
}
