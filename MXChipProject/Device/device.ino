//Connecting_the_MXCHIP_to_wifi
#include <DevKitMQTTClient.h>
#include <AZ3166WiFi.h>

#include <RGB_LED.h>
#include <OledDisplay.h>
RGB_LED led;
const int num_Colors = 5;
int delayMs = 500; //(2000ms = 2s)
uint8_t colors[][num_Colors] = {//unsigned int
    {255, 0, 0}, // Red, 0 , 0
    {0, 255, 0}, // 0, Green, 0
    {0, 0, 255}, // 0, 0, Blue
    {128, 0, 128}, // Purple
    {255, 165, 0}, // Orange
};

void setup(){

WiFi.begin();  // initialise wifi
Screen.init();//initialise the display

DevKitMQTTClient_Init(true);// create conneciton to your IoT Hub that uses your device conneciton string
}

void loop(){
//Uses MQTT to send data to the cloud
void sendData(const char *data) {
    time_t t = time(NULL);
    char buf[sizeof "2011-10-08T07:07:09Z"];
    strftime(buf, sizeof buf, "%FT%TZ", gmtime(&t));

    EVENT_INSTANCE* message = DevKitMQTTClient_Event_Generate(data, MESSAGE);

    DevKitMQTTClient_Event_AddProp(message, "$$CreationTimeUtc", buf);
    DevKitMQTTClient_Event_AddProp(message, "$$MessageSchema", "temperature;v1");
    DevKitMQTTClient_Event_AddProp(message, "$$ContentType", "JSON");

    DevKitMQTTClient_SendEventInstance(message);
  }

int lcv = sizeof(colors) / num_Colors;// length of colour vector

for (int i = 0; i< lcv; i++){
led.setColor(colors[i][0], colors[i][1], colors[i][2]);
delay(delayMs);
Serial.printf("Color values: %d, %d, %d\n", colors[i][0], colors[i][1], colors[i][2]);
}
  // print a string to the screen with wrapped = false
    Screen.print("CMP2082M Module", false);
    delay(1000);
    // print a string to the screen with wrapped = true
    for(int i = 0; i<=3; i++)
    {
        char buf[100];
        sprintf(buf, "Haha, Hacked you!");
        Screen.print(i, buf);
    }
    delay(3000);
    // Clean up the screen
    Screen.clean();
    delay(1000);  
}