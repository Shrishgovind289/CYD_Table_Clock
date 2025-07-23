#include "ST7796U.h"
#include "NTPClock.h"
#include "WeatherStation.h"

ST7796U tft(LCD_CS, LCD_DC, LCD_RST, LCD_BL, LCD_SCK, LCD_MOSI);

const char* ssid = "SSID";
const char* password = "PASSWORD";
const char* googleApiKey = "YOUR_GOOGLE_API";
String weatherApiKey = "YOUR_WEATHER_API";

NTPClock ntpclock("pool.ntp.org");
WeatherStation weatherStation(googleApiKey, weatherApiKey);

void setup() {
  Serial.begin(115200);
  
  tft.begin();
  tft.fillScreen(0x0000);          // Black screen
  tft.printText(60, 40, "Hello, Mr. Revankar", 0xFFFF, 0x0000);  // White text on black

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");

  ntpclock.begin(ssid, password);          // sync time via NTP
  weatherStation.begin(ssid, password); // wifi + weather init

  weatherStation.updateLocationOnce();  // get lat/lon once in setup()
}

void loop() {
  weatherStation.updateWeather();  // fetch weather every 10 seconds using fixed latlon
  ntpclock.printLocalTime();           // print time
  delay(1000);
}
