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
We integrated a Raspberry Pi, Smart lightbulbs, a camera, the M5StickCPlus, a rotary-encoder, and a graphical user interface via hardware connections and MQTT messaging. The lightbulbs are controlled by the M5/rotary-encoder to turn on/off and set the bulb color. The GUI does the same thing separate from the M5/rotary encoder. The camera tracks motion and can turn the bulb on in a "security mode". 
<br>
<br>



**Work Division:**<br>
<ins>William</ins> - I formatted the README.md file to look professional as well as ensured our ideas for the project were conveyed clearly and concisely in the README.md. I also added as many pictures as I could to the README.md to show progress that was made on the project. I also contributed the code to set up a GUI for the project. The GUI has the capability to control and display information for three smart bulbs when connected properly (Pictures of the GUI are below). I created a GUI similar to the one used in class, then I found another library that give the GUI have a more modern look and feel. I added the code for the modern GUI in the same file as the original GUI at the bottom. I changed the format of the final bulbcontrol.ino file to optimize the flow of the loop.
<br>


<ins>Danny</ins> - [add stuff here]
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

