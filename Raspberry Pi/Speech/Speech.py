import speech_recognition as sr
import paho.mqtt.client as mqtt
import cv2;

client = mqtt.Client()
client.connect("broker.hivemq.com", 1883)

r = sr.Recognizer()
mic = sr.Microphone()

while True:
    with mic as source:
        audio = r.listen(source)
    
    try:
        words = r.recognize_google(audio)
        print(words)
        client.publish("prabhjot-singh-deaf-link/test", words, qos=0)

        if words == "exit":
            print("Goodbye")
            break
        
    except sr.UnknownValueError:
        print("Could not understand the audio.")
    except sr.RequestError as e:
        print("Could not request results; {e}")

