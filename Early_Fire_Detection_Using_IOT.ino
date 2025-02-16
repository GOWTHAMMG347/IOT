#include <SoftwareSerial.h> 

#define RX 12
#define TX 13

// WiFi Credentials & ThingSpeak API
String AP = "shreyas";       // WiFi SSID
String PASS = "shreyas07";   // WiFi Password
String API = "OB8W1YUPJPMFZT83";  // ThingSpeak API Key
String HOST = "api.thingspeak.com";
String PORT = "80";

// Communication Variables
int countTrueCommand;
int countTimeCommand;
boolean found = false;

// Sensor, Buzzer, and Pump Pins
int flameSensorPin = 4;  // Flame Sensor (Digital Output)
int buzzerPin = 3;       // Buzzer Output
int pumpPin = 5;         // Relay (Water Pump Control)
int sensorValue = 0;     // Sensor Reading

SoftwareSerial esp8266(RX, TX);

void setup() {
  Serial.begin(9600);
  esp8266.begin(115200);

  sendCommand("AT", 5, "OK");
  sendCommand("AT+CWMODE=1", 5, "OK");
  sendCommand("AT+CWJAP=\"" + AP + "\",\"" + PASS + "\"", 20, "OK");

  pinMode(flameSensorPin, INPUT); // Fire Sensor Input
  pinMode(buzzerPin, OUTPUT);      // Buzzer Output
  pinMode(pumpPin, OUTPUT);        // Relay Output (Water Pump)
  
  digitalWrite(pumpPin, LOW); // Ensure Pump is OFF initially
}

void loop() {
  sensorValue = digitalRead(flameSensorPin); // Read Flame Sensor (0 = No Fire, 1 = Fire Detected)

  if (sensorValue == LOW) { // No Fire Detected
    Serial.println(sensorValue);
    Serial.println("No fire detected\n");
    digitalWrite(buzzerPin, LOW); // Turn off Buzzer
    digitalWrite(pumpPin, LOW);   // Turn off Water Pump
  } else { // Fire Detected
    Serial.println(sensorValue);
    Serial.println("🔥 Fire detected! Activating water pump! 🔥");
    digitalWrite(buzzerPin, HIGH); // Turn on Buzzer
    digitalWrite(pumpPin, HIGH);   // Turn on Water Pump
  }

  // Send Data to ThingSpeak
  String getData = "GET /update?api_key=" + API + "&field1=" + String(sensorValue);
  sendCommand("AT+CIPMUX=1", 5, "OK");
  sendCommand("AT+CIPSTART=0,\"TCP\",\"" + HOST + "\"," + PORT, 15, "OK");
  sendCommand("AT+CIPSEND=0," + String(getData.length() + 4), 4, ">");
  esp8266.println(getData);
  delay(500);
  countTrueCommand++;
  sendCommand("AT+CIPCLOSE=0", 5, "OK");

  delay(2000); // Delay before the next reading
}

void sendCommand(String command, int maxTime, char readReply[]) {
  Serial.print(countTrueCommand);
  Serial.print(". AT command => ");
  Serial.print(command);
  Serial.print(" ");
  
  while (countTimeCommand < (maxTime * 1)) {
    esp8266.println(command);
    if (esp8266.find(readReply)) {
      found = true;
      break;
    }
    countTimeCommand++;
  }

  if (found) {
    Serial.println("Connected");
    Serial.println("Data Transferred successfully");
    countTrueCommand++;
    countTimeCommand = 0;
  } else {
    Serial.println("Connecting...");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  found = false;
}