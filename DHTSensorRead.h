//#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTTYPE DHT22 //also AM2302

DHT dht1(DHT1PIN, DHTTYPE);

class sensorRead
{
    int dhtDataPin;
    int vPinTemp;
    int vPinHum;
    int dhtState;
   
DHT* dht;

public:  //constructor creates a sensorRead, initialises member variables and state.
sensorRead(int pin, int vPin1, int vPin2, DHT* sensorIn)
  {
    dhtDataPin = pin; 
    vPinTemp = vPin1;
    vPinHum = vPin2;
    dhtState = LOW;
    dht = sensorIn;
  }

void update() {
    if(dhtState == HIGH)
    {
      dhtState = LOW; //don't poll again right now
      digitalWrite(dhtDataPin, dhtState);  // update the pin state
    }
    else if (dhtState == LOW)
    {
      dhtState = HIGH; //poll now
      digitalWrite(dhtDataPin, dhtState);  // update the pin state

      float h = dht->readHumidity();
      float t = dht->readTemperature();
      float f = dht->readTemperature(true);  // Read temperature as Fahrenheit (isFahrenheit = true)

     if (isnan(h) || isnan(t) || isnan(f))
     {
      Serial.printf("Failed to read from DHT sensor %i\n",dhtDataPin);
       return;
      } else {
        float hif = dht->computeHeatIndex(f, h);  // Compute heat index in Fahrenheit (the default)
        float hic = dht->computeHeatIndex(t, h, false);  // Compute heat index in Celsius (isFahreheit = false)
  
        Serial.printf("Read from DHT sensor %i\n",dhtDataPin);
        Serial.print("Humidity: ");
        Serial.print(h);
        Serial.print(" %\t");
        Serial.print("Temperature: ");
        Serial.print(t);
        Serial.print(" *C ");
        Serial.print(f);
        Serial.print(" *F\t");
        Serial.print("Heat index: ");
        Serial.print(hic);
        Serial.print(" *C ");
        Serial.print(hif);
        Serial.println(" *F");
      
        Blynk.virtualWrite(vPinTemp, t);
        Blynk.virtualWrite(vPinHum, h);
      }
   }
  }
};

sensorRead sensor1(DHT1PIN, V3, V4, &dht1); //arguments: pin no., Temp vPin no., Hum vPin no., DHT sensor to use

void readDhtSensors(){
  sensor1.update();
}
