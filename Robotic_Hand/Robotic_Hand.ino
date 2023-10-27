#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"
#include <Servo.h>

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "broker.hivemq.com";
int port = 1883;
const char topic[] = "prabhjot-singh-deaf-link/test";

String command;

Servo thumb;
Servo first;
Servo middle;
Servo small;

int pos = 0;

void setup()
{
  Serial.begin(9600);

  while (!Serial)

    Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port))
  {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1)
      ;
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  Serial.print("Subscribing to topic: ");
  Serial.println(topic);

  // subscribe to a topic
  mqttClient.subscribe(topic);

  Serial.print("Waiting for messages on topic: ");
  Serial.println(topic);
  Serial.println();

  thumb.attach(6);
  first.attach(2);
  middle.attach(3);
  small.attach(4);

  reset();
}

void loop()
{
  // Parse the incoming message from the MQTT client and store its size in 'messageSize'
  int messageSize = mqttClient.parseMessage();

  // Check if 'messageSize' is non-zero (indicating that a message was received)
  if (messageSize)
  {
    // Create a character buffer 'messageBuffer' with enough space for the message
    char messageBuffer[messageSize + 1];

    // Read 'messageSize' bytes from the MQTT client and store them in 'messageBuffer'
    int bytesRead = mqttClient.readBytes(messageBuffer, messageSize);

    // Null-terminate the 'messageBuffer' to make it a C-style string
    messageBuffer[bytesRead] = '\0';

    // Print the received message to the serial monitor
    Serial.print("Received message: ");
    Serial.println(messageBuffer);

    if (strcmp(messageBuffer, "number 2") == 0)
    {
      reset();
      two();
    }

    if (strcmp(messageBuffer, "number 3") == 0)
    {
      reset();
      three();
    }

    if (strcmp(messageBuffer, "number 4") == 0)
    {
      reset();
      four();
    }

    if (strcmp(messageBuffer, "index finger") == 0)
    {
      reset();
      index_finger();
    }

    if (strcmp(messageBuffer, "thumb finger") == 0)
    {
      reset();
      thumb_finger();
    }

    if (strcmp(messageBuffer, "small finger") == 0)
    {
      reset();
      last_finger();
    }

    if (strcmp(messageBuffer, "reset") == 0)
    {
      reset();
    }

    Serial.println();
  }
}

void reset()
{
  Thumb_Down();
  First_Down();
  Middle_Down();
  Last_Down();
}

void four()
{
  Thumb_Up();
}

void three()
{
  Thumb_Up();
  Last_Up();
}

void two()
{
  Thumb_Up();
  First_Up();
  Middle_Up();
}

void index_finger()
{
  First_Up();
  delay(300);
  First_Down();
}

void thumb_finger()
{
  Thumb_Up();
  delay(300);
  Thumb_Down();
}

void last_finger()
{
  Last_Up();
  delay(300);
  Last_Down();
}

void Thumb_Up()
{
  for (pos = 135; pos >= 50; pos -= 1)
  {
    thumb.write(pos);
    delay(5);
  }
}

void Thumb_Down()
{
  for (pos = 50; pos <= 135; pos += 1)
  {
    thumb.write(pos);
    delay(5);
  }
}

void First_Up()
{
  for (pos = 180; pos >= 55; pos -= 1)
  {
    first.write(pos);
    delay(5);
  }
}

void First_Down()
{
  for (pos = 55; pos <= 180; pos += 1)
  {
    first.write(pos);
    delay(5);
  }
}

void Middle_Up()
{
  for (pos = 180; pos >= 20; pos -= 1)
  {
    middle.write(pos);
    delay(5);
  }
}

void Middle_Down()
{
  for (pos = 20; pos <= 180; pos += 1)
  {
    middle.write(pos);
    delay(5);
  }
}

void Last_Up()
{
  for (pos = 160; pos >= 35; pos -= 1)
  {
    small.write(pos);
    delay(5);
  }
}

void Last_Down()
{
  for (pos = 35; pos <= 160; pos += 1)
  {
    small.write(pos);
    delay(5);
  }
}
