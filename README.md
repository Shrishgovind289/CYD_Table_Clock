# CYD_Table_Clock
I have created a basic Table Clock using the ESP32 based Cheap Yellow Display(CYD).

In this project I am using NTP Server to get the time data using my network.
Google GeoLocation API was used to get the live location of my device. It does it only once due to striction in number of API calls made in a day. Plus Once is more than enough.
Reference Code: https://github.com/gmag11/WifiLocation 
WeatherAPI.com was used to get weather data. https://www.weatherapi.com/
