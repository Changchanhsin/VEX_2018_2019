// interface
int motor[16];
int SensorValue[4];

// Timing
#define T1 0
#define T2 1
#define T3 2
#define T4 3
int time1[4];
void clearTimer(int t){
  time1[t]=0;
}

// Joystick, Accelerometer, and Buttons.
#define Ch1          0x00
#define Ch2          0x01
#define Ch3          0x02
#define Ch4          0x03
#define Ch1Xmrt2     0x20
#define Ch2Xmrt2     0x21
#define Ch3Xmrt2     0x22
#define Ch4Xmrt2     0x23
#define AccelX       0x04
#define AccelY       0x05
#define AccelXXmrt2  0x24
#define AccelYXmrt2  0x25
#define Btn5U        0x06
#define Btn5D        0x07
#define Btn5L        0x08
#define Btn5R        0x09
#define Btn6U        0x10
#define Btn6D        0x11
#define Btn6L        0x12
#define Btn6R        0x13
#define Btn7U        0x14
#define Btn7D        0x15
#define Btn7L        0x16
#define Btn7R        0x17
#define Btn8U        0x18
#define Btn8D        0x19
#define Btn8L        0x1A
#define Btn8R        0x1B
#define Btn5UXmtr2   0x26
#define Btn5DXmtr2   0x27
#define Btn5LXmtr2   0x28
#define Btn5RXmtr2   0x29
#define Btn6UXmtr2   0x30
#define Btn6DXmtr2   0x31
#define Btn6LXmtr2   0x32
#define Btn6RXmtr2   0x33
#define Btn7UXmtr2   0x34
#define Btn7DXmtr2   0x35
#define Btn7LXmtr2   0x36
#define Btn7RXmtr2   0x37
#define Btn8UXmtr2   0x38
#define Btn8DXmtr2   0x39
#define Btn8LXmtr2   0x3A
#define Btn8RXmtr2   0x3B
int vexRT[0x40];

void __updateSystemValue()
{
  time1[0]+=10;
  time1[1]+=10;
  time1[2]+=10;
  time1[3]+=10;
  if(SensorValue[1]==1024)
    SensorValue[1]=0;
  else
    SensorValue[1]+=1;
  if(SensorValue[2]==127)
    SensorValue[2]=0;
  else
    SensorValue[2]+=1;
}
