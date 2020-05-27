#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "58e86d7149754e328e4f2eb99d11c534"; //Enter the Auth code which was send by Blink

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "zam";  //Enter your WIFI Name
char pass[] = "12345678";  //Enter your WIFI Password
int sense_Pin = 0;
int value = 0;
#define DHTPIN 1          //

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;
WidgetLED led1(V7);
WidgetLED led2(V8);
WidgetLED led3(V1);
WidgetLED led4(V2);

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  if (isnan(h) || isnan(t)){
    Serial.println("Failed to read from sensor!");
    return;
  }
   value= analogRead(A0);
                                                                /*Serial.print("Gass LEVEL : ");
                                                                  
                                                                  
                                                                   Serial.println(value);
                                                                
                                                                        if(value>650)
                                                                        {
                                                                            led1.on();
                                                                            delay(1000);
                                                                        }
                                                                       else
                                                                       {
                                                                           led2.on();
                                                                           
                                                                            delay(1000);
                                                                    
                                                                       }
                                                                
                                                                      led1.off();
                                                                      led2.off();
                                                                      Blynk.virtualWrite(V4, value);*/
    Serial.print("Moisture LEVEL : ");
   Serial.println(value);

        if(value<900)
        {
            led3.on();
            Blynk.setProperty(V1, "color", "#D3435C");
            delay(1000);
        }
       else
       {
           led4.on();
           
            delay(1000);
    
       }

      led3.off();
      led4.off();
  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);  //V5 is for Humidity
  Serial.println (h);
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature
  Serial.println (t);
  
}

void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}
