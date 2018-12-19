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

using namespace std;
#define PI 3.1415


bool sound_flag=true;

class Tank
{
  private:
    int tankScreen_width;
    int tankScreen_height;
    int critical_dot[12][2]; // 0 is x  and  1 is y
    int R;
    int G;
    int B;
    bool flag_UP;
    bool flag_DOWN;
    bool flag_exist;
    bool flag_laser;
    int health;
    int Xposition;
    int Yposition;
    int Xposition_center;
    int Yposition_center;
    int speed;
    int Xspeed;
    int Yspeed;
    int angle;
    int omega;//change speed of angle
    int weapon_kind;//felan ye no tir
    int variable_for_shoot2;
    int variable_for_shoot3;
    int bulletNum;
    int score;
    int laser_x1;
    int laser_x2;
    int laser_y1;
    int laser_y2;
    int variable_for_fire;
    bool flag_weapon1;
    bool flag_weapon2;
    bool flag_weapon3;
    bool flag_shield;
  public:
    void set_flag_shield(bool i);
    bool get_flag_shield();
    void set_variable_for_fire(int i);
    int get_variable_for_fire();
    void set_R(int i);
    void set_G(int i);
    void set_B(int i);
    void set_tankScreen_width(int i);
    void set_tankScreen_height(int i);
    void set_flag_UP(bool i);
    void set_flag_DOWN(bool i);
    void set_flag_exist(bool i);
    void set_flag_laser(bool i);
    void check_collision(SDL_Surface *SCREEN);
    void set_critical_dots(SDL_Surface *SCREEN);
    void set_Xposition_center(int i);
    void set_Yposition_center(int i);
    void set_health(int i);
    void set_Xposition(int i);
    void set_Yposition(int i);
    void set_speed(int i);
    void set_Xspeed(int i);
    void set_Yspeed(int i);
    void set_angle(int i);//degree
    void set_omega(int i);
    void set_weapon_kind(int i);
    void set_variable_for_shoot2(int i);
    void set_variable_for_shoot3(int i);
    void set_bulletNum(int i);
    void set_score(int i);
    void set_laser_x1(int i);
    void set_laser_x2(int i);
    void set_laser_y1(int i);
    void set_laser_y2(int i);

    void get_tankScreen_width(int i);
    void get_tankScreen_height(int i);
    bool get_flag_UP();
    bool get_flag_DOWN();
    bool get_flag_exist();
    bool get_flag_laser();
    int get_R();
    int get_G();
    int get_B();
    int get_variable_for_shoot2();
    int get_variable_for_shoot3();
    int get_Xposition_center();
    int get_Yposition_center();
    int get_tankScreen_width();
    int get_tankScreen_height();
    int get_health();
    int get_Xposition();
    int get_Yposition();
    int get_speed();
    int get_Xspeed();
    int get_Yspeed();
    int get_angle();
    int get_omega();
    int get_weapon_kind();
    int get_bulletNum();
    int get_score();
    int get_critical_dot(int i,int j);
    int get_laser_x1();
    int get_laser_y1();
    int get_laser_x2();
    int get_laser_y2();

    void move(int i);
    void turn_around();

    void set_flag_weaponi(int i ,bool j);
    bool get_flag_weaponi(int i);
};


void Tank::set_flag_shield(bool i)
{
  flag_shield=i;
}

bool Tank::get_flag_shield()
{
  return(flag_shield);
}

void Tank::set_variable_for_fire(int i)
{
    variable_for_fire=i;
}
int Tank::get_variable_for_fire()
{
    return (variable_for_fire);
}

void Tank::set_score(int i)
{
    score=i;
}

void Tank::set_bulletNum(int i)
{
    bulletNum=i;
}

void Tank::set_R(int i)

{
    R=i;
}

void Tank::set_G(int i)
{
    G=i;
}

void Tank::set_B(int i)
{
    B=i;
}

void Tank::set_variable_for_shoot2(int i)
{
  variable_for_shoot2=i;
}

void Tank::set_variable_for_shoot3(int i)
{
  variable_for_shoot3=i;
}

void Tank::check_collision(SDL_Surface *SCREEN)
{
  bool flag=false;
  Uint32 *pixels = (Uint32 *) SCREEN->pixels;
  for(int j=0 ; j<=4 ; j++)
  {
        for(int k=-2 ; k<=2 ; k++)
        {
            Uint8 *color = (Uint8 *) & ( pixels[(critical_dot[j][1]+k) *SCREEN->w+(critical_dot[j][0]+k)] );
            if(color[2]>240 && color[1]>240 && color[0]>240) flag=true; //move(-1);//flag_UP=0;//
    }
  }

  for(int j=5 ; j<=9 ; j++)
  {
        for(int k=-2 ; k<=2 ; k++)
        {
            Uint8 *color = (Uint8 *) & ( pixels[(critical_dot[j][1]+k) *SCREEN->w+(critical_dot[j][0]+k)] );
            if(color[2]>240 && color[1]>240 && color[0]>240)flag_DOWN=0; //flag=true; //move(-1);
        }
  }
  if (flag==true)
  {
    move(-1);
  }
}
void Tank::set_critical_dots(SDL_Surface *SCREEN)
{
    critical_dot[0][0]=get_Xposition_center()+sqrt(pow((tankScreen_width/2),2)+pow((tankScreen_height/2),2))*cos(get_angle()/180.0*3.1415+atan2((tankScreen_width),(tankScreen_height)));//x   1
    critical_dot[0][1]=get_Yposition_center()-sqrt(pow((tankScreen_width/2),2)+pow((tankScreen_height/2),2))*sin(get_angle()/180.0*3.1415+atan2((tankScreen_width),(tankScreen_height)));//y

    critical_dot[2][0]=get_Xposition_center()+ (3*tankScreen_height/5)*cos(get_angle()/180.0*3.1415);//x   3
    critical_dot[2][1]=get_Yposition_center()-(3*tankScreen_height/5)*sin(get_angle()/180.0*3.1415);//y

    critical_dot[4][0]=get_Xposition_center()+sqrt(pow((tankScreen_height/2),2)+pow((tankScreen_width/2),2))*cos(get_angle()/180.0*3.1415-atan2((tankScreen_width),(tankScreen_height)));//x   5
    critical_dot[4][1]=get_Yposition_center()-sqrt(pow((tankScreen_height/2),2)+pow((tankScreen_width/2),2))*sin(get_angle()/180.0*3.1415-atan2((tankScreen_width),(tankScreen_height)));//y

    critical_dot[5][0]=get_Xposition_center()+sqrt(pow((tankScreen_height/2),2)+pow((tankScreen_width/2),2))*cos(PI+get_angle()/180.0*3.1415-atan2((tankScreen_width),(tankScreen_height)));//x   6
    critical_dot[5][1]=get_Yposition_center()-sqrt(pow((tankScreen_height/2),2)+pow((tankScreen_width/2),2))*sin(PI+get_angle()/180.0*3.1415-atan2((tankScreen_width),(tankScreen_height)));//y

    critical_dot[7][0]=get_Xposition_center()-(tankScreen_height/2)*cos(get_angle()/180.0*3.1415);//x   8
    critical_dot[7][1]=get_Yposition_center()+(tankScreen_height/2)*sin(get_angle()/180.0*3.1415);//y

    critical_dot[9][0]=get_Xposition_center()+sqrt(pow((tankScreen_height/2),2)+pow((tankScreen_width/2),2))*cos(PI+get_angle()/180.0*3.1415+atan2((tankScreen_width),(tankScreen_height)));//x   10
    critical_dot[9][1]=get_Yposition_center()-sqrt(pow((tankScreen_height/2),2)+pow((tankScreen_width/2),2))*sin(PI+get_angle()/180.0*3.1415+atan2((tankScreen_width),(tankScreen_height)));//y

    critical_dot[10][0]=get_Xposition_center()+(tankScreen_width/2)*cos(PI/2+get_angle()/180.0*3.1415);//x   11
    critical_dot[10][1]=get_Yposition_center()-(tankScreen_width/2)*sin(PI/2+get_angle()/180.0*3.1415);//y

    critical_dot[11][0]=get_Xposition_center()+(tankScreen_width/2)*cos(get_angle()/180.0*3.1415-PI/2);//x   12
    critical_dot[11][1]=get_Yposition_center()-(tankScreen_width/2)*sin(get_angle()/180.0*3.1415-PI/2);//y

    critical_dot[1][0]=get_Xposition_center()+sqrt(pow((tankScreen_height/2),2)+pow((tankScreen_width/4),2))*cos(get_angle()/180.0*3.1415+atan2((tankScreen_width),(tankScreen_height*2)));//x   2
    critical_dot[1][1]=get_Yposition_center()-sqrt(pow((tankScreen_height/2),2)+pow((tankScreen_width/4),2))*sin(get_angle()/180.0*3.1415+atan2((tankScreen_width),(tankScreen_height*2)));//y

    critical_dot[3][0]=get_Xposition_center()+sqrt(pow((tankScreen_height/2),2)+pow((tankScreen_width/4),2))*cos(get_angle()/180.0*3.1415-atan2((tankScreen_width),(tankScreen_height*2)));//x   4
    critical_dot[3][1]=get_Yposition_center()-sqrt(pow((tankScreen_height/2),2)+pow((tankScreen_width/4),2))*sin(get_angle()/180.0*3.1415-atan2((tankScreen_width),(tankScreen_height*2)));//y

    critical_dot[6][0]=get_Xposition_center()+sqrt(pow((tankScreen_height/2),2)+pow((tankScreen_width/4),2))*cos(PI+get_angle()/180.0*3.1415-atan2((tankScreen_width),(tankScreen_height*2)));//x   7
    critical_dot[6][1]=get_Yposition_center()-sqrt(pow((tankScreen_height/2),2)+pow((tankScreen_width/4),2))*sin(PI+get_angle()/180.0*3.1415-atan2((tankScreen_width),(tankScreen_height*2)));//y

    critical_dot[8][0]=get_Xposition_center()+sqrt(pow((tankScreen_height/2),2)+pow((tankScreen_width/4),2))*cos(PI+get_angle()/180.0*3.1415+atan2((tankScreen_width),(tankScreen_height*2)));//x   9
        critical_dot[8][1]=get_Yposition_center()-sqrt(pow((tankScreen_height/2),2)+pow((tankScreen_width/4),2))*sin(PI+get_angle()/180.0*3.1415+atan2((tankScreen_width),(tankScreen_height*2)));//y

}
void Tank::set_tankScreen_width(int i)
{
  tankScreen_width=i;
}
void Tank::set_tankScreen_height(int i)
{
  tankScreen_height=i;
}

void Tank::set_flag_UP(bool i)
{
  flag_UP=i;
}
void Tank::set_flag_DOWN(bool i)
{
  flag_DOWN=i;
}
void Tank::set_flag_exist(bool i)
{
    flag_exist=i;
}
void Tank::set_flag_laser(bool i)
{
    flag_laser=i;
}
void Tank::set_Xposition_center(int i)
{
  Xposition_center=i;
}
void Tank::set_Yposition_center(int i)
{
  Yposition_center=i;
}
void Tank::set_health(int i)
{
  health=i;
}
void Tank::set_Xposition(int i)
{
  Xposition=i;
}
void Tank::set_Yposition(int i)
{
  Yposition=i;
}
void Tank::set_speed(int i)
{
  speed=i;
}
void Tank::set_Xspeed(int i)
{
  if (i==1)
  {
    Xspeed=(float)get_speed()*cos((float)get_angle()*PI/180.0);
  }
  else if (i==-1)
  {
    Xspeed=(-1)*((float)get_speed()*cos((float)get_angle()*PI/180.0));
  }
  else if (i==0)
  {
    Xspeed=0;

  }
}
void Tank::set_Yspeed(int i)
{
  if (i==1)
  {
    Yspeed=(float)get_speed()*sin((float)get_angle()*PI/180.0);
  }
  else if(i==-1)
  {
    Yspeed=(-1)*((float)get_speed()*sin((float)get_angle()*PI/180.0));
  }
  else if (i==0)
  {
    Yspeed=0;
  }
}
void Tank::set_angle(int i)
{
  angle=i;
}
void Tank::set_weapon_kind(int i)
{
  weapon_kind=i;
}
void Tank::set_omega(int i)
{
  if (i==1)
  {
    omega=10;
  }
  else if (i==-1)
  {
    omega=-10;
  }
  else if (i==0)
  {
    omega=0;
  }
}

void Tank::set_laser_x1(int i)
{
    laser_x1=i;
}

void Tank::set_laser_x2(int i)
{
    laser_x2=i;
}

void Tank::set_laser_y1(int i)
{
    laser_y1=i;
}

void Tank::set_laser_y2(int i)
{
    laser_y2=i;
}

int Tank::get_score()
{
    return score;
}

int Tank::get_bulletNum()
{
    return bulletNum;
}

int Tank::get_R()
{
    return R;
}

int Tank::get_G()
{
    return G;
}

int Tank::get_B()
{
    return B;
}

int Tank::get_variable_for_shoot2()
{
  return(variable_for_shoot2);
}

int Tank::get_variable_for_shoot3()
{
  return(variable_for_shoot3);
}

bool Tank::get_flag_UP()
{
  return(flag_UP);
}
bool Tank::get_flag_DOWN()
{
  return(flag_DOWN);
}
bool Tank::get_flag_laser()
{
  return(flag_laser);
}
bool Tank::get_flag_exist()
{
    return flag_exist;
}
int Tank::get_tankScreen_width()
{
    return tankScreen_width;
}
int Tank::get_tankScreen_height()
{
    return tankScreen_height;
}
int Tank::get_Xposition_center()
{
  return(Xposition_center);
}
int Tank::get_Yposition_center()
{
  return(Yposition_center);
}
int Tank::get_health()
{
  return(health);
}
int Tank::get_Xposition()
{
  return(Xposition);
}
int Tank::get_Yposition()
{
  return(Yposition);
}
int Tank::get_speed()
{
  return(speed);
}
int Tank::get_Xspeed()
{
  return(Xspeed);
}
int Tank::get_Yspeed()
{
  return(Yspeed);
}
int Tank::get_angle()
{
  return(angle);
}
int Tank::get_omega()
{
  return(omega);
}
int Tank::get_weapon_kind()
{
  return(weapon_kind);
}
int Tank::get_critical_dot(int i,int j)
{
    return critical_dot[i][j];
}
int Tank::get_laser_x1()
{
    return laser_x1;
}
int Tank::get_laser_x2()
{
    return laser_x2;
}
int Tank::get_laser_y1()
{
    return laser_y1;
}
int Tank::get_laser_y2()
{
    return laser_y2;
}

void Tank::move(int i)
{
  if (i==1)
  {
    Xposition+=get_Xspeed();
    Yposition+=get_Yspeed();
  }
  else if(i==-1)
  {
    Xposition-=get_Xspeed();
    Yposition-=get_Yspeed();
  }
}

void Tank::turn_around()
{
  angle+=get_omega();
}

void Tank:: set_flag_weaponi(int i ,bool j)
{
  if (i==1)
  {
    flag_weapon1==j;
  }
  else if (i==2)
  {
    flag_weapon2=j;
  }
  else if (i==3)
  {
    flag_weapon3=j;
  }
}

bool Tank:: get_flag_weaponi(int i)
{
  if (i==1)
  {
    return flag_weapon1;
    }
    if (i==2)
    {
        return flag_weapon2;
    }
    if (i==3)
    {
        return flag_weapon3;
    }
}


