import tkinter as tk

topic_control_color = ""
topic_control_status = ""

def Bulb_on_off():
    light_status = 0 if bulb_on_off.get() == "ON" else 1
    client.publish(topic_control_status,bytearray([light_status]))
def tryGetColorValue(colorinput:tk.Entry):
    try:
        v = int(colorinput.get())
        if v > 255:
            v = 255
        elif v < 0:
            v = 0
        return v
    except:
        colorinput.delete(0,tk.END)
        colorinput.insert(0,"0")
        return 0
def sendColor():
    red = tryGetColorValue(Red_Entry)
    green = tryGetColorValue(Green_Entry)
    blue = tryGetColorValue(Blue_Entry)
    to_send = bytearray([red])#,green,blue])
    client.publish(topic_control_color,to_send)


root = tk.Tk() #creates window
root.title("Light Controller") #sets window title
#---------------------------------------------------------------------------------------------
bulb_state = tk.LabelFrame(root,text="Lightbulb") #creates first frame and sets frame title
bulb_state.pack(fill=tk.X, expand=1,padx=10)  #pack the labeled frame to fill the X direction and expand to fill any extra space, with a horizontal padding of 10
bulb_on_off = tk.StringVar(root,"Checking") #initial state of the lightbulb
bulb_time = tk.StringVar(root,"Waiting") #time of the last update
light_status_label = tk.Label(bulb_state,textvariable=bulb_on_off).pack() #displays the current state of bulb
light_time_label = tk.Label(bulb_state,textvariable=bulb_time).pack() #displays the time of the last bulb update
color_frame = tk.Frame(bulb_state,width=50,height=50) #separate frame for color info
color_frame.pack(fill=tk.X, expand=1,padx=10,pady=10) #pack the color frame to fill the X direction, expand to fill any extra space, with a horizontal padding of 10 and vertical padding of 10
#---------------------------------------------------------------------------------------------
control_frame = tk.LabelFrame(root,text="Light Control") #creates second frame and sets frame title
control_frame.pack(fill=tk.X, expand=1,padx=10) #pack the labeled frame to fill the X direction and expand to fill any extra space, with a horizontal padding of 10

#Turn bulbs on/off buttons
tk.Button(control_frame,text="Toggle Light One",command=Bulb_on_off).grid(row=0,column=1,columnspan=2) #creates toggle button to turn bulb on/off
tk.Button(control_frame,text="Toggle Light Two",command=Bulb_on_off).grid(row=0,column=3,columnspan=2) #creates toggle button to turn bulb on/off
tk.Button(control_frame,text="Toggle Light Three",command=Bulb_on_off).grid(row=0,column=5,columnspan=2) #creates toggle button to turn bulb on/off

#Set color buttons
tk.Button(control_frame,text="Set Color (bulb one)",command=sendColor).grid(row=5,column=1,columnspan=2) #creates button to set the color ofthe bulb
tk.Button(control_frame,text="Set Color (bulb two)",command=sendColor).grid(row=5,column=3,columnspan=2) #creates button to set the color ofthe bulb
tk.Button(control_frame,text="Set Color (bulb three)",command=sendColor).grid(row=5,column=5,columnspan=2) #creates button to set the color ofthe bulb

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
root.mainloop() #start the main event loop to display the GUI and handle user events
