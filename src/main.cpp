#include <Arduino.h>
#include "leftGhostSmall.h"
#include "rightGhostSmall.h"
#include "centerGhostSmall.h"
#include <TFT_eSPI.h>
#include <AccelStepper.h>

#define BLINKSPEED 9
//stepper pins
#define IN1 18
#define IN2 4
#define IN3 5
#define IN4 6


void blinkMotion();
void drawEye(int x, int y, int i,int EYEPOSX, int EYEPOSY);
void drawBlink();
void eyeMove(int duration,int intensity,int speed,bool gap,bool move,bool hold,int rangeOfMotion);
void drawUnblink(int i);

TFT_eSPI tft = TFT_eSPI();

TFT_eSprite RightEye = TFT_eSprite(&tft);
TFT_eSprite LeftEye = TFT_eSprite(&tft);
TFT_eSprite background = TFT_eSprite(&tft);
TFT_eSprite unblink = TFT_eSprite(&tft);
TFT_eSprite blink = TFT_eSprite(&tft);
TFT_eSprite center = TFT_eSprite(&tft);
int EYEPOSX = 0;
int EYEPOSY = 0;
 int x = 130;
 int y = 60;
 int motion = 0;


   AccelStepper stepper(4, 18,5,4,7);
   //const int stepsPerRevolution = 2048;
  //Stepper myStepper(32, IN1, IN3, IN2, IN4);

void setup() {
stepper.setAcceleration(400.0);
stepper.setMaxSpeed(1000.0);
stepper.setSpeed(800.0);



 

 Serial.begin(115200);
  
  tft.init();
 

  tft.setSwapBytes(true);
  
  tft.setRotation(1);
 
  tft.fillScreen(TFT_BLACK);
  
   background.createSprite(250,250);

  
}

void loop() {
  //myStepper.setSpeed(400);
   //delay(500);  // needed to start-up task1

  //clockwise spin 
 

  blinkMotion();
  //myStepper.step(stepsPerRevolution/4);
 //myStepper.step(-stepsPerRevolution/4);
  
  stepper.runToNewPosition(2048/4);
 stepper.runToNewPosition(-2048/4);
   

  eyeMove(1000,10,1,true,true,false,3); 
  eyeMove(1000,5,2,true,false,false,1);
  blinkMotion();
  eyeMove(3000,20,4,true,false,true,4); 
  eyeMove(3000,0,1,false,true,true,2); 
}


void blinkMotion(){

 background.fillSprite(TFT_BLACK);
drawEye(x,y,motion,EYEPOSX,EYEPOSY);

  for (int i = -50; i < 90; i+=BLINKSPEED) 
  {
    blink.fillRect(0,i,165,45,0x0001);
   drawBlink();
    background.pushSprite(EYEPOSX,EYEPOSY);
  }
    blink.fillSprite(TFT_BLACK);
    drawEye(x,y,motion,EYEPOSX,EYEPOSY);
  } 
 


//draws motionless ghost eye
void drawEye(int x, int y,int motion,int EYEPOSX, int EYEPOSY){
  background.fillSprite(TFT_BLACK);
  //center eye setup
center.createSprite(35,35);
center.setSwapBytes(true);
  center.pushImage(0,0,35,35,centerGhostSmall);
  center.pushToSprite(&background,109,109,TFT_WHITE);
    //right eye setup
    RightEye.createSprite(61,133);
    RightEye.setSwapBytes(true);
     RightEye.pushImage(0,0,61,133,rightGhostSmall);
    RightEye.pushToSprite(&background,x,59,TFT_WHITE);

  //left eye setup
  LeftEye.createSprite(61,133);
  LeftEye.setSwapBytes(true);
  LeftEye.pushImage(0,0,61,133,leftGhostSmall);
  LeftEye.pushToSprite(&background,y,59,TFT_WHITE);
//push eye composite to screen
  background.pushSprite(EYEPOSX,EYEPOSY);
}

void drawBlink(){
    //blink setup
blink.createSprite(150,150);
   blink.pushRotated(&background,45,TFT_BLACK);
  blink.pushRotated(&background,135,TFT_BLACK);
  blink.pushRotated(&background,225,TFT_BLACK);
  blink.pushRotated(&background,315,TFT_BLACK);

}


void eyeMove(int duration,int intensity, int speed, bool gap,bool move,bool hold,int rangeOfMotion){
  int cycle = -1;
  int repeats = rangeOfMotion;
  while (repeats >= 1)
  {

    for (int i = 0; i < intensity; (i+=speed))
  {
       

    motion = i;
    if (move)
    {
      y = 60 - i;
    x = i + 130;
    }else
    {
      y = 60;
      x = 130;
    }
    
    if (gap)
    {
      if (repeats == 4)
    {
      EYEPOSX = i;
      EYEPOSY = -i;
    }else if(repeats == 3)
    {
      EYEPOSX = -i;
      EYEPOSY = -i;
    }else if (repeats == 2)
    {
      EYEPOSX = i;
      EYEPOSY = i;
    }else
    {
      EYEPOSX = -i;
      EYEPOSY = i;
    }
    }
    else{
         EYEPOSX = 0;
          EYEPOSY = 0;
    }
   
    
    drawEye(x,y,motion,EYEPOSX,EYEPOSY);
    

  }
  if (hold)
  {
    delay(duration);
  }
  
  
  for (int i = intensity; i > 0; (i-=speed))
  {
       

    motion = i;
    if (move)
    {
      y = 60 - i;
    x = i + 130;
    }else
    {
      y = 60;
      x = 130;
    }
    
    if (gap)
    {
      if (repeats == 4)
    {
      EYEPOSX = i;
      EYEPOSY = -i;
    }else if(repeats == 3)
    {
      EYEPOSX = -i;
      EYEPOSY = -i;
    }else if (repeats == 2)
    {
      EYEPOSX = i;
      EYEPOSY = i;
    }else
    {
      EYEPOSX = -i;
      EYEPOSY = i;
    }
    
    
    }
    else{
         EYEPOSX = 0;
          EYEPOSY = 0;
    }
   
    
    drawEye(x,y,motion,EYEPOSX,EYEPOSY);


  }
  delay(duration);
cycle = cycle * cycle;
    repeats--;
   
}
}