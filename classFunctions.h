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
#include "class.h"

using namespace std;
#define PI 3.1415


//tank class funcitons
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
////////////////////////////////////////
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

//////////////////////////////////////
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



//bullet class functions

void Bullet::check_collision(SDL_Surface *SCREEN)
        {
            int x=Xposition;
            int y=Yposition;
            int Vx=Xspeed;
            int Vy=Yspeed;

            Uint32 *pixels = (Uint32 *) SCREEN->pixels;
            Uint8 *color;
            Uint8 *color2;

            if(Vx>=0 && Vy<=0)
            {
                color = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x+radius+7)] );
                color2 = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x+radius+1)] );
                if(color[2]>240 && color[1]>240 && color[0]>240) Xspeed*=(-1);
                else if(color2[2]>240 && color2[1]>240 && color2[0]>240) Xspeed*=(-1);


                color = (Uint8 *) & ( pixels[(y-radius-7) *SCREEN->w+(x)] );
                color2 = (Uint8 *) & ( pixels[(y-radius-1) *SCREEN->w+(x)] );
                if(color[2]>240 && color[1]>240 && color[0]>240) Yspeed*=(-1);
                else if(color2[2]>240 && color2[1]>240 && color2[0]>240) Yspeed*=(-1);
            }

            else if(Vx>=0 && Vy>=0)
            {
                color = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x+radius+7)] );
                color2 = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x+radius+1)] );
                if(color[2]>240 && color[1]>240 && color[0]>240) Xspeed*=(-1);
                else if(color2[2]>240 && color2[1]>240 && color2[0]>240) Xspeed*=(-1);

                color = (Uint8 *) & ( pixels[(y+radius+7) *SCREEN->w+(x)] );
                color2 = (Uint8 *) & ( pixels[(y+radius+1) *SCREEN->w+(x)] );
                if(color[2]>240 && color[1]>240 && color[0]>240) Yspeed*=(-1);
                else if(color2[2]>240 && color2[1]>240 && color2[0]>240) Yspeed*=(-1);
            }

            else if(Vx<=0 && Vy<=0)
            {
                color = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x-radius-7)] );
                color2 = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x-radius-1)] );
                if(color[2]>240 && color[1]>240 && color[0]>240) Xspeed*=(-1);
                else if(color2[2]>240 && color2[1]>240 && color2[0]>240) Xspeed*=(-1);

                color = (Uint8 *) & ( pixels[(y-radius-7) *SCREEN->w+(x)] );
                color2 = (Uint8 *) & ( pixels[(y-radius-1) *SCREEN->w+(x)] );
                if(color[2]>240 && color[1]>240 && color[0]>240) Yspeed*=(-1);
                else if(color2[2]>240 && color2[1]>240 && color2[0]>240) Yspeed*=(-1);
            }

            else if(Vx<=0 && Vy>=0)
            {
                color = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x-radius-7)] );
                color2 = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x-radius-1)] );
                if(color[2]>240 && color[1]>240 && color[0]>240) Xspeed*=(-1);
                else if(color2[2]>240 && color2[1]>240 && color2[0]>240) Xspeed*=(-1);

                color = (Uint8 *) & ( pixels[(y+radius+7) *SCREEN->w+(x)] );
                color2 = (Uint8 *) & ( pixels[(y+radius+1) *SCREEN->w+(x)] );
                if(color[2]>240 && color[1]>240 && color[0]>240) Yspeed*=(-1);
                else if(color2[2]>240 && color2[1]>240 && color2[0]>240) Yspeed*=(-1);
            }
        }


        void Bullet::collision_with_tank(SDL_Surface *SCREEN,Tank *tank,int i,Mix_Music *explosion)
        {
            int x=Xposition;
            int y=Yposition;
            int Vx=Xspeed;
            int Vy=Yspeed;

            Uint32 *pixels = (Uint32 *) SCREEN->pixels;
            Uint8 *color;

            if(Vx>=0 && Vy<=0)
            {
                color = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x+radius+1)] );
                if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10 && flag_exist==true)
                {
                    tank[i].set_health(tank[i].get_health()-5);
                    flag_exist=false;
                    Mix_PlayMusic(explosion,0);
                }


                    color = (Uint8 *) & ( pixels[(y-radius-1) *SCREEN->w+(x)] );
                    if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10 && flag_exist==true)
                    {
                        tank[i].set_health(tank[i].get_health()-5);
                        flag_exist=false;
                        Mix_PlayMusic(explosion,0);
                    }
            }

            else if(Vx>=0 && Vy>=0)
            {
                color = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x+radius+1)] );
                if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10 && flag_exist==true)
                {
                    tank[i].set_health(tank[i].get_health()-5);
                    flag_exist=false;
                    Mix_PlayMusic(explosion,0);
                }

                    color = (Uint8 *) & ( pixels[(y-radius-1) *SCREEN->w+(x)] );
                    if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10 && flag_exist==true)
                    {
                        tank[i].set_health(tank[i].get_health()-5);
                        flag_exist=false;
                        Mix_PlayMusic(explosion,0);
                    }
            }

            else if(Vx<=0 && Vy<=0)
            {
                color = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x-radius-1)] );
                if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10 && flag_exist==true)
                {
                    tank[i].set_health(tank[i].get_health()-5);
                    flag_exist=false;
                    Mix_PlayMusic(explosion,0);
                }


                    color = (Uint8 *) & ( pixels[(y-radius-1) *SCREEN->w+(x)] );
                    if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10 && flag_exist==true)
                    {
                        tank[i].set_health(tank[i].get_health()-5);
                        flag_exist=false;
                        Mix_PlayMusic(explosion,0);
                    }
            }

            else if(Vx<=0 && Vy>=0)
            {
                color = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x-radius-1)] );
                if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10 && flag_exist==true)
                {
                    tank[i].set_health(tank[i].get_health()-5);
                    flag_exist=false;
                    Mix_PlayMusic(explosion,0);
                }

                    color = (Uint8 *) & ( pixels[(y-radius-1) *SCREEN->w+(x)] );
                    if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10 && flag_exist==true)
                    {
                        tank[i].set_health(tank[i].get_health()-5);
                        flag_exist=false;
                        Mix_PlayMusic(explosion,0);
                    }
            }
        }

        void Bullet::move()
        {
            Xposition+=Xspeed;
            Yposition+=Yspeed;
        }

		void Bullet::set_Xposition(int i)
		{
			Xposition=i;
		}
		void Bullet::set_Yposition(int i)
		{
			Yposition=i;
		}
		void Bullet::set_angle(int i)
		{
			angle=i;
		}
		void Bullet::set_speed(int i)
		{
			speed=i;
		}
		void Bullet::set_Xspeed(int i)
		{
			if (i==1)
			{
				Xspeed=(float)get_speed()*cos((float)get_angle()*PI/180.0);
			}
			else if (i==0)
			{
				Xspeed=0;

			}
		}
		void Bullet::set_Yspeed(int i)
		{
			if (i==1)
			{
				Yspeed=(float)(-1)*get_speed()*sin((float)get_angle()*PI/180.0);
			}
			else if (i==0)
			{
				Yspeed=0;
			}
		}
		void Bullet::set_flag_exist(bool i)
		{
			flag_exist=i;
		}

		void Bullet::set_radius(int i)
        {
            radius=i;
        }

        void Bullet::set_startTime(int i)
        {
            startTime=i;
        }
        void Bullet::set_existingTime(int i)
        {
            existingTime=i;
        }


       	int Bullet::get_Xposition()
       	{
       		return(Xposition);
       	}
       	int Bullet::get_Yposition()
       	{
       		return(Yposition);
       	}
       	int Bullet::get_speed()
       	{
       		return (speed);
       	}
       	int Bullet::get_Xspeed()
       	{
       		return(Xspeed);
       	}
       	int Bullet::get_Yspeed()
       	{
       		return(Yspeed);
       	}
       	bool Bullet::get_flag_exist()
       	{
       		return(flag_exist);
       	}
       	int Bullet::get_angle()
       	{
       		return(angle);
       	}
       	int Bullet::get_radius()
       	{
       		return radius;
       	}
       	int Bullet::get_startTime()
       	{
            return startTime;
       	}
       	int Bullet::get_existingTime()
       	{
            return existingTime;
       	}
