#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

SimpleTimer timer;

char auth[] = "21f87ef2b5914aa180fde7226eb24f52";//"84282ada33444f34a23824f8ec00d7c1";
char ssid[] = "virginmedia6125068"; //"Hackspace_2_4";//"100AcreWood";//
char pass[] = "jnaascuw"; //"Hack_A_Day";"tiggerslikebouncing";//

bool Connected = false;

void CheckConnection(){
  Connected = Blynk.connected();
  if(!Connected){
    Serial.println("Not connected to Blynk server"); 
    Blynk.connect(3333);  // timeout set to 10 seconds and then continue without Blynk  
  }
  else{
    Serial.println("Connected to Blynk server");     
  }
};

void wifiServerConnect (){
    Serial.begin(74880);
  WiFi.begin(ssid, pass);  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  
  
  Blynk.config(auth);  // in place of Blynk.begin(auth, ssid, pass);
  Blynk.connect(3333);  // timeout set to 10 seconds and then continue without Blynk
  while (Blynk.connect() == false) {
    // Wait until connected
  }
  Serial.println("Connected to Blynk server");
  timer.setInterval(11000L, CheckConnection); // check if still connected every 11 seconds 
};

