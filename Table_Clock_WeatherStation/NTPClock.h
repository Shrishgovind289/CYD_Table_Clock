#ifndef NTP_CLOCK_H
#define NTP_CLOCK_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>

class NTPClock {
  public:
    NTPClock(const char* ntpServer = "pool.ntp.org");
    void begin(const char* ssid, const char* password);
    void printLocalTime();

  private:
    const char* _ntpServer;

    struct TimezoneInfo {
      long gmtOffset;     // seconds offset from UTC (negative means behind UTC)
      int daylightOffset; // seconds of daylight saving offset
    };

    String detectRegionFromAPI();
    TimezoneInfo getTimezoneOffsets(const String& region);
};

#endif


