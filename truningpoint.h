
TFT_eSprite spr = TFT_eSprite(&M5.Lcd);

#define BL(x,d) ((x)*40+20+(d)*4)

// field
int flags[9];
int balls[20][2];
int discs[8][3];

void initField()
{
  flags[0] = flags[1] = flags[2] = -1;
  flags[3] = flags[4] = flags[5] =  0;
  flags[6] = flags[7] = flags[8] =  1;
  
  balls[0][0]=BL(1,-1);balls[0][1]=BL(1,-1);
  balls[1][0]=BL(1, 1);balls[1][1]=BL(1, 1);
  balls[2][0]=BL(4, 1);balls[2][1]=BL(1,-1);
  balls[3][0]=BL(4,-1);balls[3][1]=BL(1, 1);
  balls[4][0]=BL(2, 0);balls[4][1]=BL(2, 0);
  balls[5][0]=BL(3, 0);balls[5][1]=BL(2, 0);
  balls[6][0]=BL(2, 0);balls[6][1]=BL(4, 0);
  balls[7][0]=BL(3, 0);balls[7][1]=BL(4, 0);
  balls[8][0]=BL(2, 0);balls[8][1]=BL(5,-1);
  balls[9][0]=BL(2, 0);balls[9][1]=BL(5, 1);
  balls[10][0]=BL(3, 0);balls[10][1]=BL(5,-1);
  balls[11][0]=BL(3, 0);balls[11][1]=BL(5, 1);
  balls[12][0]=64;balls[12][1]=124;
  balls[13][0]=64;balls[13][1]=155;
  balls[14][0]=175;balls[14][1]=124;
  balls[15][0]=175;balls[15][1]=155;
  balls[16][0]=46;balls[16][1]=46;
  balls[17][0]=46;balls[17][1]=46;
  balls[18][0]=46;balls[18][1]=46;
  balls[19][0]=46;balls[19][1]=46;
  
  discs[0][0]=60; discs[0][1]=60; discs[0][2]=-1;
  discs[1][0]=180;discs[1][1]=60; discs[1][2]=1;
  discs[2][0]=100;discs[2][1]=100;discs[2][2]=1;
  discs[3][0]=140;discs[3][1]=100;discs[3][2]=-1;
  discs[4][0]=100;discs[4][1]=180;discs[4][2]=1;
  discs[5][0]=140;discs[5][1]=180;discs[5][2]=-1;
  discs[6][0]=100;discs[6][1]=220;discs[6][2]=-1;
  discs[7][0]=140;discs[7][1]=220;discs[7][2]=1;
}

void drawCar(float  x, float  y, float  w, float  deg)
{
  float x1,y1,x2,y2,x3,y3,x4,y4;
  float pi=3.1415926;
  float pi1=pi/4;
  float pi2=pi*3/4;
  float pi3=pi*5/4;
  float pi4=pi*7/4;
  
  x1=cos(deg+pi1)*w+x;
  x2=cos(deg+pi2)*w+x;
  x3=cos(deg+pi3)*w+x;
  x4=cos(deg+pi4)*w+x;
  y1=sin(deg+pi1)*w+y;
  y2=sin(deg+pi2)*w+y;
  y3=sin(deg+pi3)*w+y;
  y4=sin(deg+pi4)*w+y;
  
  spr.fillTriangle(x1,y1,x2,y2,x3,y3,TFT_MAGENTA);
  spr.fillTriangle(x3,y3,x4,y4,x1,y1,TFT_MAGENTA);
  spr.drawLine((x1+x4)/2,(y1+y4)/2,(x1+x2)/2,(y1+y2)/2,TFT_WHITE);
  spr.drawLine((x1+x4)/2,(y1+y4)/2,(x3+x4)/2,(y3+y4)/2,TFT_WHITE);
  spr.drawLine((x3+x2)/2,(y3+y2)/2,(x1+x4)/2,(y1+y4)/2,TFT_WHITE);
}

void drawFlag(int loc, int stat)
{
  if(stat==-1)
  {
    spr.drawLine(loc*80+22,20,loc*80+37,20,TFT_BLUE);
    spr.drawLine(loc*80+42, 2,loc*80+42,20,TFT_RED);
  }
  if(stat==1)
  {
    spr.drawLine(loc*80+37, 2,loc*80+37,20,TFT_BLUE);
    spr.drawLine(loc*80+42,20,loc*80+59,20,TFT_RED);
  }
  if(stat==0)
  {
    spr.drawLine(loc*80+29, 9,loc*80+38,20,TFT_BLUE);
    spr.drawLine(loc*80+51, 9,loc*80+41,20,TFT_RED);
  }
  spr.fillCircle(loc*80+40,20,2,TFT_DARKGREY);
}

void drawBall(int locX, int locY)
{
  spr.fillCircle(locX, locY, 2, TFT_YELLOW);
}

void drawDisc(int locX, int locY, int stat)
{
  if(stat==-1)
    spr.fillCircle(locX, locY, 7, TFT_BLUE);
  if(stat==1)
    spr.fillCircle(locX, locY, 7, TFT_RED);
}
