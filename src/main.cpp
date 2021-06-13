// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const double VCC = 3.3;             // NodeMCU on board 3.3v vcc
const double R2 = 10000;            // 10k ohm series resistor
const double adc_resolution = 1023; // 10-bit adc

const double A = 0.001129148; // thermistor equation parameters
const double B = 0.000234125;
const double C = 0.0000000876741;

WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 3600 * 2;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

// Replace with your network credentials
const char *ssid = "Galaxy M51EC87";
const char *password = "wxmy8436";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliary variables to store the current output state
String outputStateLED = "off";

// Assign output variable to GPIO pin
const int outputLED = 4;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup()
{
  Serial.begin(115200);
  // Initialize the output variable as output
  pinMode(outputLED, OUTPUT);
  // Set output to LOW
  digitalWrite(outputLED, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

float temperature()
{
  double Vout, Rth, temperature, adc_value;

  adc_value = analogRead(A0);
  // extern calculate_temperature(double adc_value);
  // temperature = calculate_temperature(adc_value);
  Vout = (adc_value * VCC) / adc_resolution;
  Rth = (VCC * R2 / Vout) - R2;

  /*  Steinhart-Hart Thermistor Equation:
 *  Temperature in Kelvin = 1 / (A + B[ln(R)] + C[ln(R)]^3)
 *  where A = 0.001129148, B = 0.000234125 and C = 8.76741*10^-8  */
  temperature = (1 / (A + (B * log(Rth)) + (C * pow((log(Rth)), 3)))); // Temperature in kelvin

  temperature = temperature - 273.15; // Temperature in degree celsius

  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" degree celsius");
  return temperature;
}

void loop()
{
  WiFiClient client = server.available(); // Listen for incoming clients

  timeClient.update();
  String formattedTime = timeClient.getFormattedTime();

  if (client)
  {                                // If a new client connects,
    Serial.println("New Client."); // print a message out in the serial port
    String currentLine = "";       // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime)
    { // loop while the client's connected
      currentTime = millis();
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c);        // print it out the serial monitor
        header += c;
        if (c == '\n')
        { // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIO on and off
            if (header.indexOf("GET /led/on") >= 0)
            {
              Serial.println("LED on");
              outputStateLED = "on";
              digitalWrite(outputLED, HIGH);
            }
            else if (header.indexOf("GET /led/off") >= 0)
            {
              Serial.println("LED off");
              outputStateLED = "off";
              digitalWrite(outputLED, LOW);
            }

            float read_temperature = temperature();

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<meta http-equiv=\"refresh\" content=\"3\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");

            // CSS to style the on/off button
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>ESP8266 Web Server</h1>");

            // Display current state, and ON/OFF buttons for LED
            client.println("<p>LED - State " + outputStateLED + "</p>");
            // If the outputStateLED is off, it displays the ON button
            if (outputStateLED == "off")
            {
              client.println("<p><a href=\"/led/on\"><button class=\"button\">ON</button></a></p>");
            }
            else
            {
              client.println("<p><a href=\"/led/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println("<p><b>Temperature</b></p>");
            client.printf("%.2f %s", read_temperature, "<sup>o</sup>C");

            client.printf("<p>Time: %s</p>", formattedTime.c_str());

            // display message that is depends on temperature
            if (read_temperature > 65 && read_temperature < 75)
            {
              client.println("<p style='color: #F3F092; font-size:x-large;'><b>good for white tea</b></p>");
            }
            else if (read_temperature > 75 && read_temperature < 85)
            {
              client.println("<p style='color: #C8DC6F; font-size:x-large;'><b>good for green tea</b></p>");
            }
            else if (read_temperature > 85 && read_temperature < 95)
            {
              client.println("<p style='color: #3B150F; font-size:x-large;'><b>good for black tea</b></p>");
            }
            else if (read_temperature < 0)
            {
              client.println("<p style='color: aqua; font-size:x-large;'><b>Defrost the water first</b></p>");
            }
            else if (read_temperature > 100)
            {
              client.println("<p style='color: firebrick; font-size:x-large;'><b>Water too hot!</b></p>");
            }
            else
            {
              client.println("<p style='color: blue; font-size:x-large;'><b>Normal Water</b></p>");
            }

            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          }
          else
          { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        }
        else if (c != '\r')
        {                   // if you got anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}