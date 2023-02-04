### Compress  project with all his dependences

#### project estructure files
```c
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

```c
