#include <M5Stack.h>
#include "vexdevice.h"
#include "truningpoint.h"

// MStack Faces' keyboard - begin
#define KEYBOARD_I2C_ADDR     0X08
#define KEYBOARD_INT          5

// MStack Faces' keyboard - end

#define task int

boolean bStopTasksBetweenModes = false;


//int main();
void __mapping_port__();
void __carLeft(int spd);
void __carRight(int spd);
void __showStatus();
#define event void
task autonomous();
bool __is_autonomous__=false;
task usercontrol();
bool __is_usercontrol__=false;
event init();
void pre_auton();

void __showIndelay(bool yn){
  if (yn==true)
    M5.Lcd.fillCircle(34, 5, 2, TFT_RED);
  else
    M5.Lcd.fillCircle(34, 5, 2, TFT_GREEN);
}

void wait1Msec(int t){
  __showIndelay(true);
  for(;t>0;t-=10){
    __mapping_port__();
    __showStatus();
    __updateSystemValue();
    delayMicroseconds(1);
  }
  __showIndelay(false);
}
void delay(int t){
  __showIndelay(true);
  for(;t>0;t-=10){
    __mapping_port__();
    __showStatus();
    __updateSystemValue();
    delayMicroseconds(1);
  }
  __showIndelay(false);
}

// debug
void writeDebugStreamLine(const char *sFormatString, ...){
  ;
}

float __car_delta_x__=0.0,__car_old_x__=20.0;
float __car_delta_y__=0.0,__car_old_y__=100.0;
float __car_move__=0.0;
float __car_degree__=-3.1415926/2.0;
float __car_left_move__=0.0;
float __car_right_move__=0.0;
float __car_wide__=20.0;
char __s__[100];

float __car_left__=0.0;
float __car_right__=0.0;

void __showMsg(int loc, char * s)
{
  if(loc<24)
    M5.lcd.drawString(s, 2, loc*10, 1);
  else
    M5.lcd.drawString(s, 282, (loc-24)*10, 1);
}

void __showMsgFloat(int loc, char * s, float f)
{
  char _s[100];
  sprintf(_s,s,f);
  if(loc<24)
    M5.lcd.drawString(_s, 2, loc*10, 1);
  else
    M5.lcd.drawString(_s, 282, (loc-24)*10, 1);
}

void __showMsgInt(int loc, char * s, int i)
{
  char _s[100];
  sprintf(_s, s,i);
  if(loc<24)
    M5.lcd.drawString(_s, 2, loc*10, 1);
  else
    M5.lcd.drawString(_s, 282, (loc-24)*10, 1);
}

void __showMsgInt1(int loc, char * s, int i)
{
  char _s[100];
  sprintf(_s, s,i);
  M5.lcd.drawString(_s, 282, loc*10, 1);
}

void __showMsgInt2(int loc, char * s, int i)
{
  char _s[100];
  sprintf(_s, s,i);
  M5.lcd.drawString(_s, 297, loc*10, 1);
}

void __setSpeedAndDegree()
{
  __car_degree__+=(__car_left_move__-__car_right_move__)/__car_wide__;
  __car_move__=(__car_right_move__+__car_left_move__)/2;
}


void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Wire.begin();
  pinMode(KEYBOARD_INT, INPUT_PULLUP);
  spr.setColorDepth(8);
  spr.createSprite(240, 240);
  M5.setWakeupButton(BUTTON_A_PIN);
  for(int i=0;i<0x40;i++)
    vexRT[i]=0;
  initField();
}


void __showStatus()
{
  int i;
  //spr.fillSprite(TFT_BLACK);
  spr.fillRect(0,0,240,240,TFT_LIGHTGREY);
  spr.fillRect(0,80,40,40,TFT_RED);
  spr.fillRect(0,160,40,40,TFT_RED);
  spr.fillRect(200,80,40,40,TFT_BLUE);
  spr.fillRect(200,160,40,40,TFT_BLUE);
  
  //M5.Lcd.drawLine(0, 0, 320, 240, TFT_BLACK);
  for (i=0;i<6;i++)
  {
    for(int j=0;j<6;j++)
    {
      spr.drawRect(i*40, j*40, 40, 40, TFT_DARKGREY);
    }
  }
  spr.fillRect(63, 123, 114, 34, TFT_WHITE);
  spr.drawRoundRect( 60, 120, 40, 40, 5, TFT_RED   );
  spr.drawRoundRect( 61, 121, 38, 38, 4, TFT_RED   );
  spr.drawRoundRect( 62, 122, 36, 36, 3, TFT_RED   );
  spr.drawRoundRect( 65, 125, 30, 30, 4, TFT_DARKGREY);
  spr.drawRoundRect( 70, 130, 20, 20, 4, TFT_DARKGREY);
  spr.drawRoundRect(140, 120, 40, 40, 5, TFT_BLUE  );
  spr.drawRoundRect(141, 121, 38, 38, 4, TFT_BLUE  );
  spr.drawRoundRect(142, 122, 36, 36, 3, TFT_BLUE  );
  spr.drawRoundRect(145, 125, 30, 30, 4, TFT_DARKGREY);
  spr.drawRoundRect(150, 130, 20, 20, 4, TFT_DARKGREY);
  spr.drawRoundRect(100, 120, 40, 40, 5, TFT_YELLOW);
  spr.drawRoundRect(101, 121, 38, 38, 4, TFT_YELLOW);
  spr.drawRoundRect(102, 122, 36, 36, 3, TFT_YELLOW);
  spr.drawRoundRect(105, 125, 30, 30, 4, TFT_DARKGREY);
  spr.drawRoundRect(110, 130, 20, 20, 4, TFT_DARKGREY);
  spr.drawRect( 38, 0, 4, 20, TFT_DARKGREY);
  spr.drawRect(118, 0, 4, 20, TFT_DARKGREY);
  spr.drawRect(198, 0, 4, 20, TFT_DARKGREY);
  for(i=0; i<9; i++)
    drawFlag(i/3,flags[i]);
  for(i=0; i<8; i++)
    drawDisc(discs[i][0],discs[i][1],discs[i][2]);
  for(i=0; i<20; i++)
    drawBall(balls[i][0],balls[i][1]);

  __setSpeedAndDegree();
  __car_delta_x__=cos(__car_degree__)*__car_move__;
  __car_delta_y__=sin(__car_degree__)*__car_move__;
  __car_old_x__+=__car_delta_x__;
  __car_old_y__+=__car_delta_y__;
  drawCar(__car_old_x__, __car_old_y__, __car_wide__, __car_degree__);

  __showMsgFloat(0,"L%3.1f ",__car_left_move__);
  __showMsgFloat(24,"R%3.1f ",__car_right_move__);

  for(i=0;i<16;i++)
    __showMsgInt(i+2,"%05d ",motor[i]);
  for(i=0;i<4;i++)
    __showMsgInt(i+19,"%05d ",SensorValue[i]);

  for(i=0;i<0x1B;i++)
  {
    __showMsgInt1(i+1,"%02X ",vexRT[i]);
    __showMsgInt2(i+1,"%02X ",vexRT[i+0x20]);
  }
  spr.pushSprite(40,0,TFT_BLACK);
}

void loop() {
  uint8_t key_val;
  int i;
  // put your main code here, to run repeatedly:
  if(digitalRead(KEYBOARD_INT) == LOW) {
    Wire.requestFrom(KEYBOARD_I2C_ADDR, 1);
    while (Wire.available()) { 
      uint8_t key_val = Wire.read();
      if(key_val != 0) {
        __is_usercontrol__=false;
        __is_autonomous__=false;
        switch (key_val) {
        case '9':  __showMsg(23, "M5.R+ ");  __car_right__+=16;  __carRight(__car_right__);  break;
        case '6':  __showMsg(23, "M5.R0 ");  __car_right__ = 0;  __carRight(__car_right__);  break;
        case '3':  __showMsg(23, "M5.R- ");  __car_right__-=16;  __carRight(__car_right__);  break;
        case '8':  __showMsg(23, "M5.+  ");  __car_right__+=16;  __carRight(__car_right__);
                                             __car_left__ +=16;  __carLeft(__car_left__)  ;  break;
        case '5':  __showMsg(23, "M5.0  ");  __car_right__ = 0;  __carRight(__car_right__);
                                             __car_left__  = 0;  __carLeft(__car_left__)  ;  break;
        case '2':  __showMsg(23, "M5.-  ");  __car_right__-=16;  __carRight(__car_right__);
                                             __car_left__ -=16;  __carLeft(__car_left__)  ;  break;
        case '7':  __showMsg(23, "M5.L+ ");  __car_left__ +=16;  __carLeft(__car_left__)  ;  break;
        case '4':  __showMsg(23, "M5.L0 ");  __car_left__  = 0;  __carLeft(__car_left__)  ;  break;
        case '1':  __showMsg(23, "M5.L- ");  __car_left__ -=16;  __carLeft(__car_left__)  ;  break;
        case 'M':  __showMsg(23, "UserCt");  __is_usercontrol__=true;  break;
        case '%':  __showMsg(23, "Autono");  __is_autonomous__ =true;  break;
        case 'A':  __showMsg(23, "InitAn");  pre_auton();  break;

        case 'q':  __showMsg(23, "RC.Ch3");  vexRT[Ch3]+=16; __is_usercontrol__=true; break;
        case 'a':  __showMsg(23, "RC.Ch3");  vexRT[Ch3]-=16; __is_usercontrol__=true; break;
        case 'o':  __showMsg(23, "RC.Ch1");  vexRT[Ch1]-=16; __is_usercontrol__=true; break;
        case 'p':  __showMsg(23, "RC.Ch1");  vexRT[Ch1]+=16; __is_usercontrol__=true; break;

        case 'w':  __showMsg(23, "RC.B7L");  vexRT[Btn7L]=1; __is_usercontrol__=true; break;
        case 'e':  __showMsg(23, "RC.B7R");  vexRT[Btn7R]=1; __is_usercontrol__=true; break;
        case 'r':  __showMsg(23, "RC.B8L");  vexRT[Btn8L]=1; __is_usercontrol__=true; break;
        case 't':  __showMsg(23, "RC:B7L");  vexRT[Btn7LXmtr2]=1; __is_usercontrol__=true; break;
        case 'y':  __showMsg(23, "RC:B7R");  vexRT[Btn7RXmtr2]=1; __is_usercontrol__=true; break;
        case 'u':  __showMsg(23, "RC:B8L");  vexRT[Btn8LXmtr2]=1; __is_usercontrol__=true; break;
        
        case 's':  __showMsg(23, "RC.B5U");  vexRT[Btn5U]=1; __is_usercontrol__=true; break;
        case 'd':  __showMsg(23, "RC.B6U");  vexRT[Btn6U]=1; __is_usercontrol__=true; break;
        case 'x':  __showMsg(23, "RC.B6D");  vexRT[Btn6D]=1; __is_usercontrol__=true; break;
        case 'f':  __showMsg(23, "RC.B8U");  vexRT[Btn8U]=1; __is_usercontrol__=true; break;
        case 'c':  __showMsg(23, "RC.B8D");  vexRT[Btn8D]=1; __is_usercontrol__=true; break;
        case 'g':  __showMsg(23, "RC:B5U");  vexRT[Btn5UXmtr2]=1; __is_usercontrol__=true; break;
        case 'h':  __showMsg(23, "RC:B6U");  vexRT[Btn6UXmtr2]=1; __is_usercontrol__=true; break;
        case 'j':  __showMsg(23, "RC:B7U");  vexRT[Btn7UXmtr2]=1; __is_usercontrol__=true; break;
        case 'n':  __showMsg(23, "RC:B7D");  vexRT[Btn7DXmtr2]=1; __is_usercontrol__=true; break;
        case 'k':  __showMsg(23, "RC:B8U");  vexRT[Btn8UXmtr2]=1; __is_usercontrol__=true; break;
        case 'm':  __showMsg(23, "RC:B8D");  vexRT[Btn8DXmtr2]=1; __is_usercontrol__=true; break;
        
        case ' ':  __showMsg(23, "RC----");
          for(i=0;i<0x40;i++){
            vexRT[i]=0;
          }
          __is_usercontrol__=true;
          break;
        }
      }
    }
  }
  if(__is_autonomous__==true)
    autonomous();
  if(__is_usercontrol__==true)
    usercontrol();
  __mapping_port__();
  __showStatus();
  
  if(M5.BtnA.wasPressed()) {
    M5.powerOFF();
  }

  M5.update();
  
  __updateSystemValue();
}
