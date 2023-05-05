#include <WiFi.h> 
#include "esp_wpa2.h" 
#include <M5StickCPlus.h>
#include <ArduinoMqttClient.h>
#define EAP_ANONYMOUS_IDENTITY "" 
#define EAP_IDENTITY "" 
#define EAP_PASSWORD "" 
#define WPA_PASSWORD "" 
//#define USE_EAP 
//SSID NAME
#ifdef USE_EAP
  const char* ssid = ""; // eduroam SSID
#else 
  const char* ssid = ""; // home SSID
#endif
const char broker[] = "eduoracle.ugavel.com";
int   port  = 1883;
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
//MQTT Topics
const char kitchen_red_light[] = "kitchen/red_light";
const char kitchen_green_light[] = "kitchen/green_light";
const char kitchen_blue_light[] ="kitchen/blue_light";
const char kitchen_white_light[] ="kitchen/white_light";
const char kitchen_off_light[] ="kitchen/off_light";
const char kitchen_party_light[] ="kitchen/party_light";
const char den_red_light[] = "den/red_light";
const char den_green_light[] = "den/green_light";
const char den_blue_light[] ="den/blue_light";
const char den_white_light[] ="den/white_light";
const char den_off_light[] ="den/off_light";
const char den_party_light[] ="den/party_light";

//User Options
const char *colors[] = {"red", "green", "blue", "white", "off", "party time"};
const char *rooms[] = {"kitchen" , "den"};


String colorname;
String roomname;
String on_off = "Off";
char buffer[100];
int a_wait = 0;
int b_wait = 0;
int c_wait = 0;
int color = 0;
int room = 0;
int BTNA = 37;
int BTNB = 39;
int BTNC = 26;

void setScreen(){
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLUE);
  M5.Lcd.setCursor(15, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
  roomname = rooms[room];
  M5.Lcd.setCursor(15, 10);
  M5.Lcd.print(roomname);
  M5.Lcd.setCursor(15, 90);
  colorname = colors[color];
  M5.Lcd.print(colorname);
  
}

void onMqttMessage(int messageSize){
  Serial.print(mqttClient.messageTopic());
}

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
  WiFi.disconnect(true);// disconnect form wifi to set new wifi connection
  WiFi.mode(WIFI_STA);// init wifi mode
  #ifdef USE_EAP
    esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_ANONYMOUS_IDENTITY, strlen(EAP_ANONYMOUS_IDENTITY));
    esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
    esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
    esp_wifi_sta_wpa2_ent_enable();
    WiFi.begin(ssid);//connect to wifi
  #else
    WiFi.begin(ssid,WPA_PASSWORD);
  #endif
  WiFi.setSleep(false);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Waiting for connection");
  }
  

  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  M5.Lcd.print(ip); 

  mqttClient.onMessage(onMqttMessage);
  mqttClient.setUsernamePassword("giiuser","giipassword");
  mqttClient.connect(broker, port);


  pinMode(BTNC, INPUT_PULLUP);

  setScreen();
}


void loop(){
  mqttClient.poll();  
  if(digitalRead(BTNA)== LOW && !a_wait){
    if(colors[color] == "red" && rooms[room] == "kitchen"){
      mqttClient.beginMessage(kitchen_red_light);
      mqttClient.print(room);
      mqttClient.endMessage();
    }
    if(colors[color] == "blue" && rooms[room] == "kitchen"){
      mqttClient.beginMessage(kitchen_blue_light);
      mqttClient.print(room);
      mqttClient.endMessage();
    }
    if(colors[color] == "green" && rooms[room] == "kitchen"){
      mqttClient.beginMessage(kitchen_green_light);
      mqttClient.print(room);
      mqttClient.endMessage();
    }
    if(colors[color] == "white" && rooms[room] == "kitchen"){
      mqttClient.beginMessage(kitchen_white_light);
      mqttClient.print(room);
      mqttClient.endMessage();
    }
    if(colors[color] == "off" && rooms[room] == "kitchen"){
      mqttClient.beginMessage(kitchen_off_light);
      mqttClient.print(room);
      mqttClient.endMessage();
    }
    if(colors[color] == "party time" && rooms[room] == "kitchen"){
      mqttClient.beginMessage(kitchen_party_light);
      mqttClient.print(room);
      mqttClient.endMessage();
    }
    if(colors[color] == "red" && rooms[room] == "den"){
      mqttClient.beginMessage(den_red_light);
      mqttClient.print(room);
      mqttClient.endMessage();
    }
    if(colors[color] == "blue" && rooms[room] == "den"){
      mqttClient.beginMessage(den_blue_light);
      mqttClient.print(room);
      mqttClient.endMessage();
    }
    if(colors[color] == "green" && rooms[room] == "den"){
      mqttClient.beginMessage(den_green_light);
      mqttClient.print(room);
      mqttClient.endMessage();
    }
    if(colors[color] == "white" && rooms[room] == "den"){
      mqttClient.beginMessage(den_white_light);
      mqttClient.print(room);
      mqttClient.endMessage();
    }
    if(colors[color] == "off" && rooms[room] == "den"){
      mqttClient.beginMessage(den_off_light);
      mqttClient.print(room);
      mqttClient.endMessage();
    }
    if(colors[color] == "party time" && rooms[room] == "den"){
      mqttClient.beginMessage(den_party_light);
      mqttClient.print(room);
      mqttClient.endMessage();
    }

  }
  if(digitalRead(BTNB)==LOW && !b_wait){
    room++;
    if (room>1){
      room=0;
    }
    setScreen();
  }
  if(digitalRead(BTNC)==LOW && !c_wait){
    color++;
    if (color>5){
      color=0;
    }
    setScreen();
  }
  if(digitalRead(BTNA)==HIGH){
    a_wait = 0;
  }
  if(digitalRead(BTNB)==HIGH){
    b_wait = 0;
  }
  if(digitalRead(BTNC)==HIGH){
    c_wait = 0;
  }
}