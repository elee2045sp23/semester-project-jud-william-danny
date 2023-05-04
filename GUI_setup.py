import tkinter as tk
import paho.mqtt.client as mqtt
import time

broker = "info8000.ga"
topic_status_1 = ""
topic_status_2 = ""
topic_status_3 = ""

topic_control_color_for_bulb_1 = ""
topic_control_color_for_bulb_2 = ""
topic_control_color_for_bulb_3 = ""

topic_control_status_for_bulb_1 = ""
topic_control_status_for_bulb_2 = ""
topic_control_status_for_bulb_3 = ""

#Methods for each bulb on/off
def Bulb_on_off_1():
    light_status = 0 if bulb_on_off.get() == "ON" else 1
    client.publish(topic_control_status_for_bulb_1,bytearray([light_status]))
def Bulb_on_off_2():
    light_status = 0 if bulb_on_off_2.get() == "ON" else 1
    client.publish(topic_control_status_for_bulb_2,bytearray([light_status]))
def Bulb_on_off_3():
    light_status = 0 if bulb_on_off_3.get() == "ON" else 1
    client.publish(topic_control_status_for_bulb_3,bytearray([light_status]))
#Method 
def tryGetColorValue(provided_color:tk.Entry):
    try:
        color_number = int(provided_color.get())
        if color_number > 255:
            color_number = 255
        elif color_number < 0:
            color_number = 0
        return color_number
    except:
        provided_color.delete(0,tk.END)
        provided_color.insert(0,"0")
        return 0
#Methods to send color of each bulb
def sendColor_1():
    red = tryGetColorValue(Red_Entry)
    green = tryGetColorValue(Green_Entry)
    blue = tryGetColorValue(Blue_Entry)
    to_send = bytearray([red,green,blue])
    client.publish(topic_control_color_for_bulb_1,to_send)
def sendColor_2():
    red = tryGetColorValue(Red_Entry_2)
    green = tryGetColorValue(Green_Entry_2)
    blue = tryGetColorValue(Blue_Entry_2)
    to_send = bytearray([red,green,blue])
    client.publish(topic_control_color_for_bulb_2,to_send)
def sendColor_3():
    red = tryGetColorValue(Red_Entry_3)
    green = tryGetColorValue(Green_Entry_3)
    blue = tryGetColorValue(Blue_Entry_3)
    to_send = bytearray([red,green,blue])
    client.publish(topic_control_color_for_bulb_3,to_send)
#Methods to set the color of each bulb
def setColor_1(red,green,blue):
    color_frame_1.config(bg=f"#{red:02x}{green:02x}{blue:02x}")
def setColor_2(red,green,blue):
    color_frame_2.config(bg=f"#{red:02x}{green:02x}{blue:02x}")
def setColor_3(red,green,blue):
    color_frame_3.config(bg=f"#{red:02x}{green:02x}{blue:02x}")
def pumpMQTT():
    client.loop(0)
    root.after(10,pumpMQTT)
#Methods for MQTT for each bulb    
def onMessageFromLight_1(client_obj, userdata, message:mqtt.MQTTMessage):
    if message.topic == topic_status_1:
        on = int(message.payload[0])
        red = int(message.payload[1])
        green = int(message.payload[2])
        blue = int(message.payload[3])
        setColor_1(red,green,blue)
        if on:
            bulb_on_off.set("ON") 
        else:
            bulb_on_off.set("OFF") 
        bulb_time.set(time.ctime())
def onMessageFromLight_2(client_obj, userdata, message:mqtt.MQTTMessage):
    if message.topic == topic_status_2:
        on = int(message.payload[0])
        red = int(message.payload[1])
        green = int(message.payload[2])
        blue = int(message.payload[3])
        setColor_2(red,green,blue)
        if on:
            bulb_on_off_2.set("ON") 
        else:
            bulb_on_off_2.set("OFF") 
        bulb_time_2.set(time.ctime())
def onMessageFromLight_3(client_obj, userdata, message:mqtt.MQTTMessage):
    if message.topic == topic_status_3: 
        on = int(message.payload[0])
        red = int(message.payload[1])
        green = int(message.payload[2])
        blue = int(message.payload[3])
        setColor_3(red,green,blue)
        if on:
            bulb_on_off_3.set("ON") 
        else:
            bulb_on_off_3.set("OFF") 
        bulb_time_3.set(time.ctime())

#MQTT information/connection
client = mqtt.Client()
client.username_pw_set("giiuser","giipassword")
client.on_message = onMessageFromLight_1
client.on_message = onMessageFromLight_2
client.on_message = onMessageFromLight_3
client.connect(broker)
client.subscribe(topic_status_1,topic_status_2,topic_status_3)


#---------------------------------------------------------------------------------------------
#Create the window with a title
root = tk.Tk() 
root.title("Light Controller")
#---------------------------------------------------------------------------------------------
#Lightbulb 1
bulb_state = tk.LabelFrame(root,text="Lightbulb One") #creates first frame and sets frame title
bulb_state.pack(fill=tk.X, expand=1,padx=10)  #pack the labeled frame to fill the X direction and expand to fill any extra space, with a horizontal padding of 10
bulb_on_off = tk.StringVar(root,"Checking") #initial state of the lightbulb
bulb_time = tk.StringVar(root,"Waiting") #time of the last update
light_status_label = tk.Label(bulb_state,textvariable=bulb_on_off).pack() #displays the current state of bulb
light_time_label = tk.Label(bulb_state,textvariable=bulb_time).pack() #displays the time of the last bulb update
#Color Frame 1
color_frame_1 = tk.Frame(bulb_state,width=50,height=50) #creates the color frame for bulb one
color_frame_1.pack(fill=tk.X, expand=1,padx=10,pady=10) #pack the color frame to fill the X direction, expand to fill any extra space, with a horizontal padding of 10 and vertical padding of 10
setColor_1(red=0,blue=0,green=0) #sets the color of the frame for bulb one
#---------------------------------------------------------------------------------------------
#Lightbulb 2
bulb_state_2 = tk.LabelFrame(root,text="Lightbulb Two") #creates second frame and sets frame title
bulb_state_2.pack(fill=tk.X, expand=1,padx=10)  #pack the labeled frame to fill the X direction and expand to fill any extra space, with a horizontal padding of 10
bulb_on_off_2 = tk.StringVar(root,"Checking") #initial state of the lightbulb
bulb_time_2 = tk.StringVar(root,"Waiting") #time of the last update
light_status_label_2 = tk.Label(bulb_state_2,textvariable=bulb_on_off_2).pack() #displays the current state of bulb
light_time_label_2 = tk.Label(bulb_state_2,textvariable=bulb_time_2).pack() #displays the time of the last bulb update
#Color Frame 2
color_frame_2 = tk.Frame(bulb_state_2, width=50, height=50) #creates the color frame for bulb two
color_frame_2.pack(fill=tk.X, expand=1, padx=10, pady=10) #pack the color frame to fill the X direction, expand to fill any extra space, with a horizontal padding of 10 and vertical padding of 10
setColor_2(red=0,blue=0,green=0) #sets the color of the frame for bulb two
#---------------------------------------------------------------------------------------------
#Lightbulb 3
bulb_state_3 = tk.LabelFrame(root,text="Lightbulb Three") #creates third frame and sets frame title
bulb_state_3.pack(fill=tk.X, expand=1,padx=10)  #pack the labeled frame to fill the X direction and expand to fill any extra space, with a horizontal padding of 10
bulb_on_off_3 = tk.StringVar(root,"Checking") #initial state of the lightbulb
bulb_time_3 = tk.StringVar(root,"Waiting") #time of the last update
light_status_label_3 = tk.Label(bulb_state_3,textvariable=bulb_on_off_3).pack() #displays the current state of bulb
light_time_label_3 = tk.Label(bulb_state_3,textvariable=bulb_time_3).pack() #displays the time of the last bulb update
#Color Frame 3
color_frame_3 = tk.Frame(bulb_state_3, width=50, height=50) #creates the color frame for bulb three
color_frame_3.pack(fill=tk.X, expand=1, padx=10, pady=10) #pack the color frame to fill the X direction, expand to fill any extra space, with a horizontal padding of 10 and vertical padding of 10
setColor_3(red=0,blue=0,green=0) #sets the color of the frame for bulb three
#---------------------------------------------------------------------------------------------
#Control Frame
control_frame = tk.LabelFrame(root,text="Light Controls") #creates second frame and sets frame title
control_frame.pack(fill=tk.X, expand=1,padx=10) #pack the labeled frame to fill the X direction and expand to fill any extra space, with a horizontal padding of 10
#Turn bulbs on/off buttons
tk.Button(control_frame,text="Toggle Light One",command=Bulb_on_off_1).grid(row=0,column=1,columnspan=2) 
tk.Button(control_frame,text="Toggle Light Two",command=Bulb_on_off_2).grid(row=0,column=3,columnspan=2) 
tk.Button(control_frame,text="Toggle Light Three",command=Bulb_on_off_3).grid(row=0,column=5,columnspan=2) 
#Set color buttons
tk.Button(control_frame,text="Set Color (bulb one)",command=sendColor_1).grid(row=5,column=1,columnspan=2) 
tk.Button(control_frame,text="Set Color (bulb two)",command=sendColor_2).grid(row=5,column=3,columnspan=2) 
tk.Button(control_frame,text="Set Color (bulb three)",command=sendColor_3).grid(row=5,column=5,columnspan=2) 
#Red button
Red_Entry = tk.Entry(control_frame,width=20)
Red_Entry.grid(row=2,column=1)
tk.Label(control_frame,text="Red:").grid(row=2,column=0)
#Green button
Green_Entry = tk.Entry(control_frame,width=20)
Green_Entry.grid(row=3,column=1)
tk.Label(control_frame,text="Green:").grid(row=3,column=0)
#Blue button
Blue_Entry = tk.Entry(control_frame,width=20)
Blue_Entry.grid(row=4,column=1)
tk.Label(control_frame,text="Blue:").grid(row=4,column=0)
#Red button 2
Red_Entry_2 = tk.Entry(control_frame,width=20)
Red_Entry_2.grid(row=2,column=3)
tk.Label(control_frame,text="Red:").grid(row=2,column=2)
#Green button 2
Green_Entry_2 = tk.Entry(control_frame,width=20)
Green_Entry_2.grid(row=3,column=3)
tk.Label(control_frame,text="Green:").grid(row=3,column=2)
#Blue button 2
Blue_Entry_2 = tk.Entry(control_frame,width=20)
Blue_Entry_2.grid(row=4,column=3)
tk.Label(control_frame,text="Blue:").grid(row=4,column=2)
#Red button 3
Red_Entry_3 = tk.Entry(control_frame,width=20)
Red_Entry_3.grid(row=2,column=5)
tk.Label(control_frame,text="Red:").grid(row=2,column=4)
#Green button 3
Green_Entry_3 = tk.Entry(control_frame,width=20)
Green_Entry_3.grid(row=3,column=5)
tk.Label(control_frame,text="Green:").grid(row=3,column=4)
#Blue button 3
Blue_Entry_3 = tk.Entry(control_frame,width=20)
Blue_Entry_3.grid(row=4,column=5)
tk.Label(control_frame,text="Blue:").grid(row=4,column=4)
#---------------------------------------------------------------------------------------------
pumpMQTT() #messaging cycle
root.mainloop() #starts the main event loop to display the GUI and handle user events
