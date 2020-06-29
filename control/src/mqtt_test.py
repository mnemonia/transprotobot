import paho.mqtt.client as mqtt

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    #client.subscribe("$SYS/#")
    client.subscribe("/transprotobot/pac/tc/velocity")
    client.subscribe("/transprotobot/pac/sc/angle")
    client.subscribe("/transprotobot/sil/wheel/velocity")
    client.subscribe('/transprotobot/sil/gps/fix')

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

print("Connecting..")
client.connect("test.mosquitto.org", 1883, 60)
# client.connect("192.168.100.106", 1883, 60)
print("Connected")

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
print("Wait for messages")
client.loop_forever()
print("finishing")
