#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h> 

#include <DHT.h>
// DHT setup includes code from FROM ladyada, public domain
#define DHTPIN 27   // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

char* ssid = "791";
char* password = "waaaaiiii";
const char* device_id = "ESPMINE";
const char* sensor_id1 = "TCQ";
const char* sensor_id2 = "TCW";




  void connectWifi(){
  WiFi.begin(ssid, password); //Initiate the wifi connection here with the credentials earlier preset
  
    while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
  return;
}
void sendDataToWaziCloud(float value1, float value2) {
  
  // Check if the board is connected to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected.");
    connectWifi();
    return;
  }

  HTTPClient http;

  // Sending the first value
  String endpoint1 = "https://api.waziup.io/api/v2/devices/" + String(device_id) + "/sensors/" + String(sensor_id1) + "/value";
  http.begin(endpoint1);

  // Header content for the data to send
  http.addHeader("Content-Type", "application/json;charset=utf-8");
  http.addHeader("accept", "application/json;charset=utf-8");

  // Data to send
  String data1 = "{ \"value\": " + String(value1) + " }";

  int httpResponseCode1 = http.POST(data1);

  if (httpResponseCode1 > 0) {
    String response1 = http.getString();
    Serial.println("HTTP Response code: " + String(httpResponseCode1));
    Serial.println("Response: " + response1);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode1);
  }

  http.end();

  // Sending the second value
  String endpoint2 = "https://api.waziup.io/api/v2/devices/" + String(device_id) + "/sensors/" + String(sensor_id2) + "/value";
  http.begin(endpoint2);

  // Header content for the data to send
  http.addHeader("Content-Type", "application/json;charset=utf-8");
  http.addHeader("accept", "application/json;charset=utf-8");

  // Data to send
  String data2 = "{ \"value\": " + String(value2) + " }";

  int httpResponseCode2 = http.POST(data2);

  if (httpResponseCode2 > 0) {
    String response2 = http.getString();
    Serial.println("HTTP Response code: " + String(httpResponseCode2));
    Serial.println("Response: " + response2);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode2);
  }

  http.end();
}

  void setup() {
  Serial.begin(115200); //Set the baudrate to the board youre using (115200 is fine)
  delay(100);
  connectWifi();

  dht.begin();
}

  void loop(){
   // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensortftyv!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  sendDataToWaziCloud(t,h);
  delay(300000); // Wait for 5 minutes (in ms) to send the next generated random value
}

  

