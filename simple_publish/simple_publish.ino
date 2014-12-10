// include process library
#include <Process.h>
#include "MQTTclient.h"

#define MQTT_HOST "85.119.83.194" // test.mosquitto.org

int sliderPin = A0;

int ledPin = 10;

void setup() {
  pinMode (sliderPin, INPUT);
    pinMode (ledPin, OUTPUT);

  Serial.begin(9600);
  Bridge.begin();

  // begin the client library (initialize host)
  mqtt.begin(MQTT_HOST, 1883);
  
 mqtt.subscribe("test/mqttclient/slider", updateBrightness);

}

void loop() {
  // put your main code here, to run repeatedly:

  mqtt.monitor();

  mqtt.publish("test/mqttclient/slider", analogRead(sliderPin));


    Serial.println(analogRead(sliderPin));
delay(100);
}

void updateBrightness(const String& topic, const String& subtopic, const String& message) {
  // print the topic and message
  Serial.print("topic: ");
  Serial.println(topic);
  Serial.print("message: ");
  Serial.println(message);

  int receivedValue = message.toInt();
  receivedValue= receivedValue/4;
  Serial.print("received val: ");
  Serial.println(receivedValue);
  
  analogWrite(ledPin,receivedValue );

}



