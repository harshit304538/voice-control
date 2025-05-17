#include <WiFi.h>

// Define your network credentials
const char* ssid = "Your_WIFI_Name";       // Your WiFi SSID
const char* password = "Your_Password";  // Your WiFi password

WiFiServer server(80);  // Web server listens on port 80

// Define the 4 LED pins
#define LED1_PIN LED_BUILTIN  // Pin for LED 1
#define LED2_PIN 13  // Pin for LED 2
#define LED3_PIN 14  // Pin for LED 3
#define LED4_PIN 15  // Pin for LED 4

bool led1Status = false;  // Track LED 1 status
bool led2Status = false;  // Track LED 2 status
bool led3Status = false;  // Track LED 3 status
bool led4Status = false;  // Track LED 4 status

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Initialize the LED pins
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  
  // Ensure LEDs are OFF initially
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);
  digitalWrite(LED4_PIN, LOW);

  // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    digitalWrite(LED1_PIN,HIGH);
    delay(1000);
    Serial.print(".");
    digitalWrite(LED1_PIN,HIGH);
  }

  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());  // Print the IP address of the Pico W

  // Start the server
  server.begin();
}

void loop() {

  if  (WiFi.status() != WL_CONNECTED){
    Serial.println("Not connected to WIFI\n");
    Serial.println("connecting to WiFI");

    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, password);
      delay(1000);
      Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());  // Print the IP address of the Pico W
  }
  // Check if a client has connected
  WiFiClient client = server.available();

  if (client) {

    // Wait for the client to send a request
    while (client.connected()) {
      if (client.available()) {
        // Read the HTTP request from the client
        String request = client.readStringUntil('\r');
        Serial.println(request);

        // Handle LED control based on the request
        if (request.indexOf("/LED1=HIGH") != -1) {
          led1Status = true;
          digitalWrite(LED1_PIN, HIGH);
        }
        if (request.indexOf("/LED1=LOW") != -1) {
          led1Status = false;
          digitalWrite(LED1_PIN, LOW);
        }
        if (request.indexOf("/LED2=HIGH") != -1) {
          led2Status = true;
          digitalWrite(LED2_PIN, HIGH);
        }
        if (request.indexOf("/LED2=LOW") != -1) {
          led2Status = false;
          digitalWrite(LED2_PIN, LOW);
        }
        if (request.indexOf("/LED3=HIGH") != -1) {
          led3Status = true;
          digitalWrite(LED3_PIN, HIGH);
        }
        if (request.indexOf("/LED3=LOW") != -1) {
          led3Status = false;
          digitalWrite(LED3_PIN, LOW);
        }
        if (request.indexOf("/LED4=HIGH") != -1) {
          led4Status = true;
          digitalWrite(LED4_PIN, HIGH);
        }
        if (request.indexOf("/LED4=LOW") != -1) {
          led4Status = false;
          digitalWrite(LED4_PIN, LOW);
        }
        if (request.indexOf("/LED=OFF") != -1) {
          // Turn off all LEDs
          led1Status = false;
          digitalWrite(LED1_PIN, LOW);
          led2Status = false;
          digitalWrite(LED2_PIN, LOW);
          led3Status = false;
          digitalWrite(LED3_PIN, LOW);
          led4Status = false;
          digitalWrite(LED4_PIN, LOW);     
  
        }
            // Handle the /status endpoint
       
        // Send an HTTP response
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();

        // HTML content for the webpage
        client.println("<!DOCTYPE HTML>");
        client.println("<html>");
        client.println("<head>");
        client.println("<title>LED Control</title>");
        client.println("<style>");
        client.println("body { font-family: 'Arial', sans-serif; background-color: #2f2f2f; color: #fff; text-align: center; padding: 50px; }");
        client.println("h1 { color: #4CAF50; }");
        client.println(".led-button { font-size: 20px; margin: 10px; padding: 10px 20px; border-radius: 5px; cursor: pointer; border: none; }");
        client.println(".on { background-color: #4CAF50; color: white; }");
        client.println(".off { background-color: #f44336; color: white; }");
        client.println("</style>");
        client.println("<script>");
        client.println("setTimeout(function(){");
        client.println("  window.location.href = 'http://192.168.40.240';"); // This will reload the page after 5 seconds without turning off LEDs
        client.println("}, 5000);");  // 5000 milliseconds = 5 seconds
        client.println("</script>");
        client.println("</head>");
        client.println("<body>");

        // Display LED status
        client.println("<h1>LED Control with Buttons</h1>");
        client.println("<div>");

        // LED control buttons
        client.println("<form action='/LED1=HIGH'><button class='led-button on' type='submit'>Turn LED 1 ON</button></form>");
        client.println("<form action='/LED1=LOW'><button class='led-button off' type='submit'>Turn LED 1 OFF</button></form>");
        client.println("<form action='/LED2=HIGH'><button class='led-button on' type='submit'>Turn LED 2 ON</button></form>");
        client.println("<form action='/LED2=LOW'><button class='led-button off' type='submit'>Turn LED 2 OFF</button></form>");
        client.println("<form action='/LED3=HIGH'><button class='led-button on' type='submit'>Turn LED 3 ON</button></form>");
        client.println("<form action='/LED3=LOW'><button class='led-button off' type='submit'>Turn LED 3 OFF</button></form>");
        client.println("<form action='/LED4=HIGH'><button class='led-button on' type='submit'>Turn LED 4 ON</button></form>");
        client.println("<form action='/LED4=LOW'><button class='led-button off' type='submit'>Turn LED 4 OFF</button></form>");
        client.println("<form action='/LED=OFF'><button class='led-button off' type='submit'>Turn All LEDs OFF</button></form>");

        client.println("</div>");
        client.println("<div>");
        // Display current LED status
        client.println("<h2>Current LED Status:</h2>");
        client.println("<p>LED 1: " + String(led1Status ? "ON" : "OFF") + "</p>");
        client.println("<p>LED 2: " + String(led2Status ? "ON" : "OFF") + "</p>");
        client.println("<p>LED 3: " + String(led3Status ? "ON" : "OFF") + "</p>");
        client.println("<p>LED 4: " + String(led4Status ? "ON" : "OFF") + "</p>");
        client.println("</div>");

        client.println("</body>");
        client.println("</html>");

        break;  // End the connection after sending the response
      }
    }

    // Close the client connection
   
  }
}
