# Home Control System - with Security Aspect

**Group members:** William Lord, Judd Kenny, Danny Conner, and Cameron Blake
<br>
<br>



**Description of the desired functionality for the project/project (goals):**
Our proposed project will leverage the M5StickCPlus to implement motion detection with a lighting control system. The project entails utilizing a camera 
onboard a Raspberry Pi to detect motion and serve as a smart home hub and the M5StickCPlus to control the lighting of a light bulb. The Raspberry Pi will use a Zigbee USB Antenna to communicate with the lightbulbs while the M5 will use MQTT to communicate with the Raspberry Pi. To enhance user experience, we intend to procure a rotary encoder that will enable color changes of the light bulb by turning the encoder and use the button click of the encoder to set the color output (on/off). Additionally, our project will feature a security mode, which can be activated by double-clicking the M5StickCPlus button, which will detect motion, turn on the lights, and send an alert message to a designated phone or computer to notify the homeowner.
<br>
<br>




**Accomplishments for this project include:**
We integrated a Raspberry Pi, Zigbee Antenna, Smart lightbulbs, the M5StickCPlus, a rotary-encoder, and a graphical user interface via hardware connections and MQTT messaging. The lightbulbs are controlled by the M5/rotary-encoder to turn on/off and set the bulb color. The GUI does the same thing separate from the M5/rotary encoder. 
<br>
<br>



**Work Division:**<br>
<ins>William</ins> - I formatted the README.md file to look professional as well as ensured our ideas for the project were conveyed clearly and concisely in the README.md. I also added as many pictures as I could to the README.md to show progress that was made on the project. I also contributed the code to set up a GUI for the project. The GUI has the capability to control and display information for three smart bulbs when connected properly (Pictures of the GUI are below). I created a GUI similar to the one used in class, then I found another library that give the GUI have a more modern look and feel. I added the code for the modern GUI in the same file as the original GUI at the bottom. I changed the format of the final bulbcontrol.ino file to optimize the flow of the loop.
<br>


<ins>Danny</ins> - My primary responsibility for the project was handling the raspberry pi setup. I started by buying a raspi camera module and testing an example object identification OpenCV program. The camera feed would run but the program would return an error when it tried to draw boxes around objects and I could not determine the cause of this however I believe it is because the current version of OpenCV no longer supports the Pi Camera module v1. I then researched smart home communications and determined the Zigbee Communication Protocol to be the easiest to use as it is utilized by most "generic brand" smart bulbs. I used an open source home automation software called HomeAssistant and a Zigbee USB Antenna. HomeAssistant has an operating system that can be run directly on the raspberry pi, however; I wanted to be able to also run the camera program. I used Docker to install a container version of HomeAssistant on the Raspberry Pi OS. With the Raspi connected to Ethernet, HomeAssistant opens a socket which can be accessed from a laptop and pulls up a UI where devices, entities, and automations can be set up as extra .yaml scripts in HomeAssistant's configuration file. Despite not being able to run OpenCV, I still planned to add the RaspiCam module as a HomeAssistant entity and use an add on called Motion Eye to identify objects, but then learned that the raspi camera module integration is only avaible in the core version of the software, not the docker container or the OS version. This is why we ultimately did away with the camera, used the OS version of HomeAssistant, and had the Raspi run as a headless server. Since we had also done away with the dial functionality on the m5, I simplified the UI to use just the rotary encoder button and set up the MQTT messages. I then wrote test scripts for HomeAssistant to confirm I could turn the light on and off. 
<br>


<ins>Judd</ins> - For our final project, I contributed to researching and working on the initial code allowing the rotary encoder that we used to rotate through the color and brightness options and the button press to select a certain option. After manipulating a lot of code, and struggling with the rotation aspect, we decided to do away with the brightness and focus on changing the color. We were able to set up the M5StickCPlus screen as shown in the pictures and the final code allowed you to rotate between each room using the buttons on the side, rotate between the colors using the rotary encoder button, and then turn the light on and off with the set room and color with the M5 button. I then made a home assistant script for each color for each room for the based on the selection on the M5StickCPlus and they worked great!
<br>


<ins>Cameron</ins> - I mainly did research and code for the brightness and color switcher. As stated above lots of struggle went into trying to get two separate displays for the M5Stick one for brightness and one for color. This was so we could use the rotation of the encoder to change the colors and then switch it to brightness by pressing the encoder button, which led us to remove the brightness feature as was one of the least important parts of the project. Hence, why you see the brightness and color switcher and then the color switcher files. 
<br>
<br>






**Project Video Links:**
<br>
<ins>Final Product:</ins>
<br>
https://photos.app.goo.gl/rhYP5dnM88SUH3ks9
<br>
<ins>Progress Videos:</ins>
<br>
https://photos.app.goo.gl/HLFDnbQw88Mr456x8
<br>
https://photos.app.goo.gl/PXVQ2H7wsX6WASSs5
<br>
https://photos.app.goo.gl/UpkU7wVVnCcQPb919








**Images of Our Project:**
<br>
![single_light_bulb](https://github.com/elee2045sp23/semester-project-jud-william-danny/blob/main/single_light_bulb.jpg)
<br>
<br>
![single_light_bulb](https://github.com/elee2045sp23/semester-project-jud-william-danny/blob/main/m5_code_working.jpg)
<br>
<br>
![single_light_bulb](https://github.com/elee2045sp23/semester-project-jud-william-danny/blob/main/PXL_20230426_152059353.jpg)
<br>
<br>
![single_light_bulb](https://github.com/elee2045sp23/semester-project-jud-william-danny/blob/main/Original_GUI.png)
<br>
<br>
![single_light_bulb](https://github.com/elee2045sp23/semester-project-jud-william-danny/blob/main/Modern_GUI.png)
<br>
<br>
![single_light_bulb](https://github.com/elee2045sp23/semester-project-jud-william-danny/blob/main/blue_light.jpg)
<br>
![single_light_bulb](https://github.com/elee2045sp23/semester-project-jud-william-danny/blob/main/raspberry_pi_setup.jpg)

**Resources**
<br>
https://www.amazon.com/SONOFF-Gateway-Universal-Assistant-Wireless/dp/B09KXTCMSC/ref=asc_df_B09KXTCMSC/?tag=hyprod-20&linkCode=df0&hvadid=563598683736&hvpos=&hvnetw=g&hvrand=13744564945419614248&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9011068&hvtargid=pla-1571136511371&psc=1
<br>
https://www.amazon.com/Arducam-Megapixels-Sensor-OV5647-Raspberry/dp/B012V1HEP4/ref=asc_df_B012V1HEP4/?tag=&linkCode=df0&hvadid=385286500280&hvpos=&hvnetw=g&hvrand=12021522022216430507&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9011068&hvtargid=pla-820020083673&ref=&adgrpid=77282054583&th=1
<br>
https://www.amazon.com/Sengled-Multicolor-2000-6500K-Equivalent-SmartThings/dp/B073ZBYXKQ/ref=asc_df_B073ZBYXKQ/?tag=hyprod-20&linkCode=df0&hvadid=241989147482&hvpos=&hvnetw=g&hvrand=4672630734999774124&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9011068&hvtargid=pla-515852267037&psc=1
<br>
https://www.amazon.com/Philips-Hue-Bluetooth-compatible-Assistant/dp/B07QV9XB87/ref=asc_df_B07R2MQ2PY/?tag=&linkCode=df0&hvadid=344024276099&hvpos=&hvnetw=g&hvrand=1540466057292455920&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9011068&hvtargid=pla-785998933195&ref=&adgrpid=69357499815&th=1
<br>
https://www.home-assistant.io/installation/raspberrypi/
<br>
https://www.home-assistant.io/integrations/script/
<br>
https://www.amazon.com/Maxmoral-Encoder-Degrees-Compatible-Development/dp/B07M631J1Q/ref=asc_df_B07M631J1Q/?tag=hyprod-20&linkCode=df0&hvadid=309795598953&hvpos=&hvnetw=g&hvrand=11336123125338606885&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9011068&hvtargid=pla-634614360951&psc=1&tag=&ref=&adgrpid=61053849109&hvpone=&hvptwo=&hvadid=309795598953&hvpos=&hvnetw=g&hvrand=11336123125338606885&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9011068&hvtargid=pla-634614360951
<br>

