#include "NTPClock.h"
#include "ST7796U.h"

ST7796U time_display(LCD_CS, LCD_DC, LCD_RST, LCD_BL, LCD_SCK, LCD_MOSI);

NTPClock::NTPClock(const char* ntpServer)
  : _ntpServer(ntpServer) {}

void NTPClock::begin(const char* ssid, const char* password) 
{
  String region = detectRegionFromAPI();
  TimezoneInfo tz = getTimezoneOffsets(region);

  /*Serial.print("Detected Region: ");
  Serial.println(region);
  
  const char* c_region = region.c_str();
  char char_region[region.length() + 1];
  strcpy(char_region, c_region);
  
  time_display.printText(40, 120, "Detected Region:", 0xFFFF, 0x0000);  // White text on black
  time_display.printText(140, 120, char_region, 0xFFFF, 0x0000);  // White text on black
  
  Serial.print("GMT Offset (sec): ");
  Serial.println(tz.gmtOffset);
  Serial.print("DST Offset (sec): ");
  Serial.println(tz.daylightOffset);*/

  configTime(tz.gmtOffset, tz.daylightOffset, _ntpServer);

  // Wait for time to be set
  struct tm timeinfo;
  int retries = 0;
  while (!getLocalTime(&timeinfo) && retries < 10) {
    delay(500);
    retries++;
  }
  if (retries < 10) {
    Serial.println("Time synced successfully.");
  } else {
    Serial.println("Failed to sync time.");
  }
}

String NTPClock::detectRegionFromAPI() {
  HTTPClient http;
  String region = "Etc/UTC";

  http.begin("http://ip-api.com/json");
  int httpCode = http.GET();

  if (httpCode == 200) {
    String payload = http.getString();
    int tzIndex = payload.indexOf("\"timezone\":\"");
    if (tzIndex != -1) {
      tzIndex += 12;
      int endIndex = payload.indexOf("\"", tzIndex);
      region = payload.substring(tzIndex, endIndex);
    }
  } else {
    Serial.print("Timezone API error: ");
    Serial.println(httpCode);
  }

  http.end();
  return region;
}

NTPClock::TimezoneInfo NTPClock::getTimezoneOffsets(const String& region) {
  if (region == "America/New_York") {
    return {-5 * 3600, 3600};  // UTC-5, DST +1 hour
  } else if (region == "Europe/Berlin") {
    return {1 * 3600, 3600};   // UTC+1, DST +1 hour
  } else if (region == "Asia/Kolkata") {
    return {5 * 3600 + 1800, 0};  // UTC+5:30, no DST
  }
  // Default fallback UTC
  return {0, 0};
}

void NTPClock::printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }

  char timeStr[40];
  strftime(timeStr, sizeof(timeStr), "%A, %B %d %Y %H:%M:%S", &timeinfo);

  time_display.printText(40, 100, timeStr, 0xFFFF, 0x0000);  // White text on black
  Serial.println(timeStr);
}
