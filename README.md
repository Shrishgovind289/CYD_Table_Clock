# CYD_Table_Clock
I have created a basic Table Clock using the ESP32 based Cheap Yellow Display(CYD).

Developed ST7796U TFT driver for my CYD device. I could have used the TFT_eSPI but I was stuggling in configuring it so out of frustration manual developed the driver. Its a temporary and testing solution.
I do have plans to used Graphics library to create animations. The fonts.h file is not prefect but gets job done.

In this project I am using NTP Server to get the time data using my network.

Google GeoLocation API was used to get the live location of my device. It does it only once due to striction in number of API calls made in a day. Plus Once is more than enough.
Reference Code: https://github.com/gmag11/WifiLocation 

WeatherAPI.com was used to get weather data. https://www.weatherapi.com/

![V1](https://github.com/user-attachments/assets/b389e814-ec45-466e-8340-74e36d75b2b3)


Now that the inital version is complete as I proceed I may feature but the graphics part will take time.
