#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>
#include <sstream>
#include <SDL/SDL_gfxPrimitives.h>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "Bullet.h"

using namespace std;
#define PI 3.1415

class Chopper

{
  private:
    int Xposition;
    int Yposition;
    int Xposition_center;
    int Yposition_center;
    int speed;
    int Xspeed;
    int Yspeed;
    int angle;
public:
    void set_Xposition_center(int i);
    void set_Yposition_center(int i);
    void set_Xposition(int i);
    void set_Yposition(int i);
    void set_angle(int i);
    void set_speed(int i);
    void set_Xspeed(int i);
    void set_Yspeed(int i);
    int get_Yposition_center();
    int get_Xposition_center();
    int get_Xposition();
    int get_Yposition();
    int get_angle();
    int get_Xspeed();
    int get_Yspeed();
    void move();
    void random_position();   		
       	};



void Chopper:: set_Xposition_center(int i)
    {
      Xposition_center=i;
    }
    void Chopper:: set_Yposition_center(int i)
    {
      Yposition_center=i;
    }
          void Chopper:: set_Xposition(int i)
          {
            Xposition=i;
          }
          void Chopper:: set_Yposition(int i)
          {
            Yposition=i;
          }
          void Chopper:: set_angle(int i)
          {
            angle=i;
          }
          void Chopper:: set_speed(int i)
          {
            speed=i;
          }
          void Chopper:: set_Xspeed(int i)
          {
            if (i==1)
            {
              Xspeed=speed*cos(angle/180.0*3.1415);
            }
            if (i==0)
            {
              Xspeed=0;
            }
          }
          void Chopper:: set_Yspeed(int i)
          {
            if (i==1)
            {
              Yspeed=(-1)*speed*sin(angle/180.0*3.1415);
            }
            if (i==0)
            {
              Yspeed=0;
            }
          }
          int Chopper:: get_Yposition_center()
          {
            return Yposition_center;
          }
          int Chopper:: get_Xposition_center()
          {
            return Xposition_center;
          }
          int Chopper:: get_Xposition()
          {
            return(Xposition);
          }
          int Chopper:: get_Yposition()
          {
            return(Yposition);
          }
          int Chopper:: get_angle()
          {
            return(angle);
          }
          int Chopper:: get_Xspeed()
          {
            return(Xspeed);
          }
          int Chopper:: get_Yspeed()
          {
            return(Yspeed);
          }
          void Chopper:: move()
          {
            Xposition+=Xspeed;
            Yposition+=Yspeed;
          }

          void Chopper:: random_position()
          {
            int i=(int)(rand()%80)/20;
            if (i==0)
            {
              set_Xposition(-100);
              set_Yposition(50+rand()%800);// bolandi safhe
            }
            else if (i==1)
            {
              set_Yposition(-100);
              set_Xposition(100+rand()%1600);
              //set_angle(190+rand()%160);
            }
            else if (i==2)
            {
              set_Xposition(1900);
              set_Yposition(50+rand()%800);
              //set_angle(100+rand()%160);
            }
            else if(i==3)
            {
              set_Yposition(1120);
              set_Xposition(100+rand()%1600);
              //set_angle(10+rand()%160);
            }
          }
