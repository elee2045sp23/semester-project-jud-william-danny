//#include "auth.h"
#include <M5StickCPlus.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "dannyswifi.h"
#include "esp_wpa2.h" //wpa2 library for connections to Enterprise networks

#define BUTTON_C_PIN 26
#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])

//WIFI
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWD;
const char* mqtt_server = MQTT_SERVER;
const char *rooms[] = {"bedroom1", "bedroom2", "bedroom3", "landing","toilet","livingroom", "utility" };
const char *colors[] = {"red" , "green", "blue"};
const char *brightnesses[] = {"low", "half", "full"};
int room = 0;
int color = 0;
int brightness = 0;
int encbutton = 0;
bool on = false;

//MQTT client
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");  
  }

  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
    
}




void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {

    Serial.print("Attempting MQTT connection...");
    String clientId = "MQTT_Werkplaats";
    // Attempt to connect
    if (client.connect(clientId.c_str(),"giiuser", "giipassword")) {
      Serial.println("connected");
      client.subscribe("hue/#");
     // client.subscribe("tkkrlab/spacestate");

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void setup() {
  WiFi.disconnect(true);  //disconnect form wifi to set new wifi connection
  WiFi.mode(WIFI_STA); //init wifi mode
  #ifdef USE_EAP
    esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_ANONYMOUS_IDENTITY, strlen(EAP_ANONYMOUS_IDENTITY));
    esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
    esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
    esp_wifi_sta_wpa2_ent_enable();
    WiFi.begin(ssid); //connect to wifi
  #else
    WiFi.begin(ssid,WIFI_PASSWD);
  #endif
  WiFi.setSleep(false);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting for connection");
  }
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  M5.Lcd.print(ip);
  M5.begin();
  M5.Lcd.setRotation(1);


  
  M5.Lcd.fillScreen(BLUE);
  M5.Lcd.setCursor(15, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
 
  String roomname = rooms[room];
  M5.Lcd.printf("wait");
  setup_wifi();
  Serial.begin(115200);
  M5.Lcd.fillScreen(BLUE);
  M5.Lcd.setCursor(15, 10);
  M5.Lcd.print(roomname);

  M5.Lcd.setCursor(15, 90);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  String colorname = colors[color];
  M5.Lcd.print(colorname);

  M5.Lcd.setCursor(150, 90);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  String brightnesslevel = brightnesses[brightness];
  M5.Lcd.print(brightnesslevel);
    
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(BUTTON_A_PIN, INPUT);
  pinMode(BUTTON_B_PIN, INPUT);
  pinMode(BUTTON_C_PIN, INPUT_PULLUP);
  
}




void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if(digitalRead(BUTTON_A_PIN) == 0) {
    String roomname = rooms[room]; //find out the name of the current room
    String mqqtstring = "hue/"+roomname;
    int str_len = mqqtstring.length() + 1; 
    char mqqt_char_array[str_len];
    mqqtstring.toCharArray(mqqt_char_array, str_len);
    if(on == false){
    client.publish(mqqt_char_array, "on");
    //client.publish("hue/bedroom2", "on");
    Serial.print(roomname+"..lights on !!");   
    M5.Lcd.fillRect(0, 60, 160, 30, GREEN);
    M5.Lcd.setCursor(20, 63);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.printf("light ON");
    }
    else if(on == true){
    client.publish(mqqt_char_array, "off");
    //client.publish("hue/bedroom2", "off");
    Serial.print("Button pressed..lights off !!");   
    M5.Lcd.fillRect(0, 60, 160, 30, RED);
    M5.Lcd.setCursor(10, 63);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(0xFFE0); 
    M5.Lcd.printf("light OFF"); 
    }
    delay(500); 
    
  };

    if(digitalRead(BUTTON_B_PIN) == 0) {
    room++;
    if (room>(ARRAY_SIZE(rooms)-1)) {room=0;}

    //update screen with new room name
    M5.Lcd.fillScreen(BLUE);
    M5.Lcd.setCursor(15, 10);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(3);
    String roomname = rooms[room];
    M5.Lcd.print(roomname);
    delay(300);
  };


  if (digitalRead(BUTTON_C_PIN) == 0) {
    if (color>(ARRAY_SIZE(colors)-1)) {color=0;}
    if (encbutton = 0){
        //input dial functionality to scroll thru color option 
        //update screen with new color name
        encbutton = 1;          
    }
    else if(encbutton = 1){
      //input dial functionality to scroll thru brightness options
      //update screen with new brightness 
      encbutton = 0;
    }

  };

}
