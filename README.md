# Alexa-Esp32-8-relays
Alexa join esp32 and 8 relays modules simultanead with web server 

![alt text](https://github.com/vniclos/Alexa-Esp32-8-relays/blob/main/images/hardware.jpg?raw=true)

### What this  project can do for you?
- You can integre 8 relays and esp32 devkit  and manage by Alexa and web integrated web server

- You can said:  "alexa" <commad>  belen 1" ... "Alexa" <command> belen 8" . command can be  "start", "stop" in you alexa language

- you can easy change the name of the relation alexa whith relays using the file mainDefines.h
  
  - You can manage the relays with internet browser (Whith out alexa) typing  by default "http://192.168.2.41 or the ip defined inn mainDefines.h 
  
  ## What i need for make on of this
  - esp32 dev kit
  - eightrelays kit
  - power supply 5 v
  - some wires
  - look figure


### project estructure files
```cpp
├───.pio
│   ├───build ...
│   └───libdeps
│       └───esp32doit-devkit-v1
│           ├───AsyncTCP               // need for FauxmoEsp
│           ├───ESP Async WebServer    // need for website run join with faxumo
│           ├───ESPAsyncTCP            // need for FauxmoEsp
│           ├───FauxmoESP              // Alexa emulation philips bulbe
│           └───sunset                 // calculate sunrise, sunset
├───lib
│   ├───ClsConfig                      // read and save configuration wifi, time and sunset configuration
│   ├───ClsTimeSun                     // for integrate time and sunset and easy split his use
│   ├───ClsRelay                       // for do array of relays and use more easy
│   └───ClsProgramation                // is used in Relay for use his programation 
├───src
│   ├───main.cpp
│   ├───mainDefines.h                  // define global variables and object (prefix g_)
│   ├───mainSetup.h                    // Setup task for split loops in tasks and set witch procesor use
│   ├───web_css.h                      // web evirorment, css stile sheet for web enviroment
│   ├───web_html_config.h              // web enviroment, html for config is used join class ClsConfig
│   ├───web_html_root.h                // web enviroment, html root page, it used for manage relays 
│   ├───web_js.h                       // web enviroment,  javascript library
│   ├───favicon.h                      // web enviroment,  svg used for favicon
│   └───web_svg.h                      // web enviroment,  image for more funny web page

```

### root web page

![alt text](images/root.jpg?raw=true)
### Config page
There are two areas WiFi and NTP 

WiFi is for connect to your Wifi area, it is for do access to Alexa Dot, and access to NTP server for get time, this area need decimal gps location for calculate sunrise and sunset for you location. then you can set programtion of relays on or off on sunshine or sunset.  Note this kit not have real clock, it use time library and NTP server for get date and time.

Remember set summer day light hour if in you country there are summer ajust time
![alt text](https://github.com/vniclos/Alexa-Esp32-8-relays/blob/main/images/config.jpg?raw=true)


