/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <nelson.allison@aberdeencarshops.ca> wrote this file.  As long as you retain
 * this notice you can do whatever you want with this stuff. If we meet some day
 * , and you think this stuff is worth it, you can buy me a beer in return.
 * Nelson Allison
 * -----------------------------------------------------------------------------
 * 
 */
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm0 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x42);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x43);
Adafruit_PWMServoDriver pwm4 = Adafruit_PWMServoDriver(0x44);

int intensity = 0;
int Dark = A0;  // Input pin photo resistor
boolean Darkness_Falls = false;
boolean TurnedOn[80];
int TestButton = A1; // input for test button
int channel = 0;
int Sunset = 0;
int relay[]={2,3,4,5}; // Arduino pin numbers used for relay
int triggerType = LOW; // type LOW if low trigger and HIGH if high trigger relay is used
int relayON, relayOFF;// used for two different relay trigger type. Do not change
int i = 0;
unsigned long previousMillis[80];        // will store last time LED was updated
unsigned long currentMillis[80];
unsigned long interval[80];           // interval at which to blink (milliseconds)

void TestOn(){
    intensity =2000;
    for (channel=0; channel < 16; channel++) {
      pwm0.setPWM( channel, 0, intensity ); 
    }
    for (channel=0; channel < 16; channel++) {
      pwm1.setPWM( channel, 0, intensity ); 
    }
    for (channel=0; channel < 16; channel++) {
      pwm2.setPWM( channel, 0, intensity ); 
    }
    for (channel=0; channel < 16; channel++) {
      pwm3.setPWM( channel, 0, intensity ); 
    }
    for (channel=0; channel < 16; channel++) {
      pwm4.setPWM( channel, 0, intensity ); 
    }
    for (i = 0; i < 4; i++) {
      digitalWrite(relay[i], relayON);
    }
    delay (180000);
}

void TestOff(){
    intensity =0;
    for (channel=0; channel < 16; channel++) {
      pwm0.setPWM( channel, 0, intensity ); 
    }
    for (channel=0; channel < 16; channel++) {
      pwm1.setPWM( channel, 0, intensity ); 
    }
    for (channel=0; channel < 16; channel++) {
      pwm2.setPWM( channel, 0, intensity ); 
    }
    for (channel=0; channel < 16; channel++) {
      pwm3.setPWM( channel, 0, intensity ); 
    }
    for (channel=0; channel < 16; channel++) {
      pwm4.setPWM( channel, 0, intensity ); 
    }
    for (i = 0; i < 4; i++) {
      digitalWrite(relay[i], relayOFF);
    }
}

void gm_plant_on() {
  intensity =2000; //interior lights
  pwm2.setPWM( 0, 0, intensity );
  TurnedOn[17]=true;
}

void gm_plant_off() {
  intensity = 0; //interior lights
  pwm2.setPWM( 0, 0, intensity );
  TurnedOn[17]=false;
}

void caution_sign() { //this is a flashing led
  pwm3.setPWM( 15, 0, 2000);
  TurnedOn[63]=true;
}

void street_lights_on() {
    intensity = 2000;
    for (channel=0; channel < 14; channel++) {
      pwm0.setPWM( channel, 0, intensity );
      TurnedOn[channel] = true; 
      delay(100); 
    }
}

void street_lights_off() {
    intensity =0;
    for (channel=0; channel < 14; channel++) {
      pwm0.setPWM( channel, 0, intensity ); 
      TurnedOn[channel] = false; 
      delay(50); 
    }
}

void tower_on() {
  intensity =500;
  pwm1.setPWM( 1, 0, intensity ); 
  TurnedOn[1]= true;   
}

void tower_off() {
  intensity =0;
  pwm1.setPWM( 1, 0, intensity );
  TurnedOn[1]= false;   
}

void st_kitty_on() {
  intensity =2000;
  pwm1.setPWM( 2, 0, intensity );
  TurnedOn[2]= true;     
}

void st_kitty_off() {
  intensity =0;
  pwm1.setPWM( 2, 0, intensity );
  TurnedOn[2]= false;   
}

void meriton_lights_on() {
    intensity =2000;
    for (channel=14; channel < 16; channel++) {
      pwm0.setPWM( channel, 0, intensity ); 
      TurnedOn[channel] = true; 
      delay(50); 
    }
}

void meriton_lights_off() {
    intensity =0;
    for (channel=14; channel < 16; channel++) {
      pwm0.setPWM( channel, 0, intensity ); 
      TurnedOn[channel] = false; 
      delay(50); 
    }
}

void disco_dans_on() {
  pwm3.setPWM( 1, 0, intensity ); //inside lights 
  intensity =3000;
  TurnedOn[50]= true; 
  delay(2000); 
  intensity =2000;
  pwm3.setPWM( 0, 0, intensity ); //Porch light
  TurnedOn[49]= true;  
}

void disco_dans_off() {
  intensity =0;
  pwm3.setPWM( 0, 0, intensity );
  TurnedOn[49]= false;  
  delay(1500); 
  pwm3.setPWM( 1, 0, intensity );  
  TurnedOn[50]= false;  
}

void bowl_board_on() {
  intensity =1500;
  pwm3.setPWM( 2, 0, intensity );
  TurnedOn[51]= true;   
}

void bowl_board_off() {
  intensity =0;
  pwm3.setPWM( 2, 0, intensity );
  TurnedOn[51]= false; 
}

void bus_on() {
  digitalWrite(relay[0], relayON);
}

void bus_off() {
  digitalWrite(relay[0], relayOFF); 
}

void motel_office_on() { 
    intensity = 1000; //room lights
    pwm3.setPWM(3, 0, intensity ); 
    TurnedOn[52]= true; 
    intensity = 1000; //porch lights
    pwm3.setPWM(4, 0, intensity ); 
    TurnedOn[53]= true; 
    intensity = 1000; // vacancy sign
    pwm3.setPWM(5, 0, intensity ); 
    TurnedOn[54]= true; 
}

void motel_office_off() { 
      intensity = 0;
      pwm3.setPWM(3, 0, intensity );
      TurnedOn[52]= false;  
      pwm3.setPWM(4, 0, intensity );
      TurnedOn[53]= false;  
      pwm3.setPWM(5, 0, intensity );
      TurnedOn[54]= false;  
}

void motel_lights_on() { 
    intensity =1000; //porch lights
    for (channel=8; channel < 12; channel++) {
      pwm3.setPWM(channel, 0, intensity );
      TurnedOn[channel]= true;  
    }  
    intensity =2000; //room lights
    for (channel=12; channel < 16; channel++) {
      pwm3.setPWM(channel, 0, intensity );
      TurnedOn[channel]= true;   
    }  
}

void motel_lights_off() {
    intensity =0;
    for (channel=8; channel < 16; channel++) {
      pwm3.setPWM( channel, 0, intensity ); 
      TurnedOn[channel]= false;  
      delay(100); 
    }
}

void setup() {
  pwm0.begin();
  pwm0.setPWMFreq(60);  // This is the maximum PWM frequency
  delay(10);
  pwm1.begin();
  pwm1.setPWMFreq(60);  // This is the maximum PWM frequency
  delay(10);
  pwm2.begin();
  pwm2.setPWMFreq(60);  // This is the maximum PWM frequency
  delay(10);
  pwm3.begin();
  pwm3.setPWMFreq(60);  // This is the maximum PWM frequency
  delay(10);
  pwm4.begin();
  pwm4.setPWMFreq(60);  // This is the maximum PWM frequency
  delay(10);
  pinMode(TestButton, INPUT);
  pinMode(Dark, INPUT);
  if(triggerType)
    {
      relayON = HIGH;
      relayOFF = LOW;
    }
   else{
      relayON = LOW;
      relayOFF = HIGH; 
   }
  for(i=0; i < 4; i++)
  {    
    pinMode(relay[i], OUTPUT);// sent i(th) pin as output
    digitalWrite(relay[i], relayOFF); // Turn the relay OFF  
  }
  for(int k=0; k < 80; k++)
  {    
    TurnedOn[k] = false;
  }
}

void loop() {
  
  if (digitalRead (TestButton) == HIGH){
      TestOn();
      TestOff();
    }
  else {
    caution_sign();
    Sunset = analogRead (Dark);
    if (Sunset < 350) {
      if (Darkness_Falls == false) {
        for (int j=0; j<80; j++) {
          previousMillis[j] = millis();
        }
        street_lights_on();
        tower_on();
        delay (100);
        bus_on();
        gm_plant_on();
        delay (1000);
        st_kitty_on();
        meriton_lights_on();
        delay (2000);
        disco_dans_on();
        delay (1000);
        bowl_board_on();
        delay (1000);
        motel_office_on();
        motel_lights_on();
        Darkness_Falls = true;
      }
      else {  
        intensity =0;
        interval[17] = 240000;
        interval[53] = 100000;
        interval[60] = 300000;  
        interval[61] = 120000; 
        interval[62] = 280000; 
        interval[63] = 145000; 
        interval[50] = 180000;  
        currentMillis[17] = millis(); //st.kitty
        if(currentMillis[17] - previousMillis[17] > interval[17]) {
          pwm2.setPWM( 2, 0, intensity );        
        }
        currentMillis[53] = millis(); //Motel office
        if(currentMillis[53] - previousMillis[53] > interval[53]) {
          pwm3.setPWM( 3, 0, 150 );        
          pwm3.setPWM( 4, 0, 50 );        
        }
        currentMillis[60] = millis(); //room 1
        if(currentMillis[60] - previousMillis[60] > interval[60]) {
          pwm3.setPWM( 12, 0, intensity );        
        }
        currentMillis[61] = millis(); //room 2
        if(currentMillis[61] - previousMillis[61] > interval[61]) {
          pwm3.setPWM( 13, 0, intensity );        
        }
        currentMillis[62] = millis(); //room 2
        if(currentMillis[62] - previousMillis[62] > interval[62]) {
          pwm3.setPWM( 14, 0, intensity );        
        }
        currentMillis[63] = millis(); //room 4
        if(currentMillis[63] - previousMillis[63] > interval[63]) {
          pwm3.setPWM( 15, 0, intensity );
        }
        if (TurnedOn[50] == true) {  //disco dans interior
          currentMillis[50] = millis();
          if(currentMillis[50] - previousMillis[50] > interval[50]) {
            pwm3.setPWM( 1, 0, intensity );
            previousMillis[50] = currentMillis[50];
            interval[50] = 900000;
            TurnedOn[50] = false;
          } 
        }
        if (TurnedOn[50] == false) {  //disco dans interior
          currentMillis[50] = millis();
          if(currentMillis[50] - previousMillis[50] > interval[50]) {
            pwm3.setPWM( 1, 3000, intensity );
          } 
        }
      }
    }
    else {
      street_lights_off();
      tower_off();
      gm_plant_off();
      st_kitty_off();
      bus_off();
      meriton_lights_off();
      disco_dans_off();
      bowl_board_off();
      motel_lights_off();
      motel_office_off();
      Darkness_Falls = false;
    }
  }
}
