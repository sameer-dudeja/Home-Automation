#include <ESP8266WiFi.h>
const char* ssid = "zam";
const char* password = "12345678";
int value;
int flag;
WiFiServer server(80);

void setup() {
  
  Serial.begin(115200);
  delay(10);
 value= analogRead(A0);
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  

  server.begin();
  Serial.println("Web server running. Waiting for the ESP IP...");
  delay(1000);
  Serial.println(WiFi.localIP());
}
void loop() {
  WiFiClient client = server.available();
 
  if (client) {
    Serial.println("New client");
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        if (c == '\n' && blank_line) 
        {          
              Serial.print("Gas LEVEL : ");
              Serial.println(value);
              if(value>650)
               {
                flag=0;
                              }
                else
               {
               flag=1;
                     }
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<head></head><body><h3>");
            
             if(flag>0)
            {
              client.println("<h1>Gas Level is Controlled</h1>");
            }
            else
            client.println("<h1>Gas Level Overflow</h1>");
             client.println(value);
            client.println("</h3>");
            client.println("</body></html>");     
            break;
        }
        if (c == '\n') {
     
          blank_line = true;
        }
        else if (c != '\r') {
      
          blank_line = false;
        }
      }
    }  
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
  }
}   
