#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_Sensor.h>

char auth[] = "8133d7571ca6421bb11c281bc606f496"; //Enter the Auth code which was send by Blink

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "zam";  //Enter your WIFI Name
char pass[] = "12345678";  //Enter your WIFI Password
int value = 0;
SimpleTimer timer;
WidgetLED led1(V7);
WidgetLED led2(V8);

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
 
   value= analogRead(A0);
  Serial.print("Gass LEVEL : ");
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
                                                                      Blynk.virtualWrite(V4, value);

}

void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);
   timer.setInterval(1000L, sendSensor);

}

void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}
