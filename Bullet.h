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
#include "Tank.h"

using namespace std;
#define PI 3.1415

class Bullet
{
    private:
        int Xposition;
        int Yposition;
        int speed;
        int Xspeed;
        int Yspeed;
        int angle;
        int radius;
        bool flag_exist;
        int startTime;
        int existingTime;
    public:
      void set_Xposition(int i);
      void set_Yposition(int i);
      void set_speed(int i);
      void set_Xspeed(int i);
      void set_Yspeed(int i);
      void set_flag_exist(bool i);
      void set_angle(int i);
      void move();
      void check_collision(SDL_Surface *SCREEN);
      void collision_with_tank(SDL_Surface *SCREEN,Tank *tank,int i,Mix_Music *explosion,bool shield_flag[4]);
      void set_radius(int i);
      void set_startTime(int i);
      void set_currentTime(int i);
      void set_existingTime(int i);
      int get_Xposition();
      int get_Yposition();
      int get_speed();
      int get_Xspeed();
      int get_Yspeed();
      int get_angle();
      int get_radius();
      int get_startTime();
      int get_existingTime();
      bool get_flag_exist();
};



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

        void Bullet::collision_with_tank(SDL_Surface *SCREEN,Tank *tank,int i,Mix_Music *explosion,bool shield_flag[4])
        {
            int x=Xposition;
            int y=Yposition;
            int Vx=Xspeed;
            int Vy=Yspeed;
            bool f=false;

            Uint32 *pixels = (Uint32 *) SCREEN->pixels;
            Uint8 *color;

            if(Vx>=0 && Vy<=0)
            {
                color = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x+radius+1)] );
                if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10 && flag_exist==true)
                {
                    if(tank[i].get_flag_shield()==false && shield_flag[i]==false)
                    {
                        tank[i].set_health(tank[i].get_health()-5);
                    }
                    f=true;
                    flag_exist=false;
                    if(sound_flag==true)
                            Mix_PlayMusic(explosion,0);

                }


                    color = (Uint8 *) & ( pixels[(y-radius-1) *SCREEN->w+(x)] );
                    if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10 && flag_exist==true)
                    {
                        if(tank[i].get_flag_shield()==false && shield_flag[i]==false)
                    {
                        tank[i].set_health(tank[i].get_health()-5);
                    }
                    f=true;
                    flag_exist=false;
                    if(sound_flag==true)
                            Mix_PlayMusic(explosion,0);
                    }
            }

            else if(Vx>=0 && Vy>=0)
            {
                color = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x+radius+1)] );
                if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10 && flag_exist==true)
                {
                    if(tank[i].get_flag_shield()==false && shield_flag[i]==false)
                    {
                        tank[i].set_health(tank[i].get_health()-5);
                    }
                    f=true;
                    flag_exist=false;
                    if(sound_flag==true)
                            Mix_PlayMusic(explosion,0);
                }

                    color = (Uint8 *) & ( pixels[(y-radius-1) *SCREEN->w+(x)] );
                    if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10 && flag_exist==true)
                    {
                       if(tank[i].get_flag_shield()==false && shield_flag[i]==false)
                    {
                        tank[i].set_health(tank[i].get_health()-5);
                    }
                    f=true;
                    flag_exist=false;
                    if(sound_flag==true)
                            Mix_PlayMusic(explosion,0);
                    }
            }

            else if(Vx<=0 && Vy<=0)
            {
                color = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x-radius-1)] );
                if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10 && flag_exist==true)
                {
                    if(tank[i].get_flag_shield()==false && shield_flag[i]==false)
                    {
                        tank[i].set_health(tank[i].get_health()-5);
                    }
                    f=true;
                    flag_exist=false;
                    if(sound_flag==true)
                            Mix_PlayMusic(explosion,0);
                }


                    color = (Uint8 *) & ( pixels[(y-radius-1) *SCREEN->w+(x)] );
                    if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10 && flag_exist==true)
                    {
                        if(tank[i].get_flag_shield()==false && shield_flag[i]==false)
                    {
                        tank[i].set_health(tank[i].get_health()-5);
                    }
                    f=true;
                    flag_exist=false;
                    if(sound_flag==true)
                            Mix_PlayMusic(explosion,0);
                    }
            }

            else if(Vx<=0 && Vy>=0)
            {
                color = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x-radius-1)] );
                if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10 && flag_exist==true)
                {
                    if(tank[i].get_flag_shield()==false && shield_flag[i]==false)
                    {
                        tank[i].set_health(tank[i].get_health()-5);
                    }
                      f=true;
                    flag_exist=false;
                    if(sound_flag==true)
                            Mix_PlayMusic(explosion,0);
                }

                    color = (Uint8 *) & ( pixels[(y-radius-1) *SCREEN->w+(x)] );
                    if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10 && flag_exist==true)
                    {
                        if(tank[i].get_flag_shield()==false && shield_flag[i]==false)
                    {
                        tank[i].set_health(tank[i].get_health()-5);
                    }
                    f=true;
                    flag_exist=false;
                    if(sound_flag==true)
                            Mix_PlayMusic(explosion,0);
                    }


            }
                    if(f==true)
                    {
                        if(tank[i].get_flag_shield()==true)
                        { 
                           tank[i].set_flag_shield(false);
                        }
                        if(shield_flag[i]==true)
                           shield_flag[i]=false;
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

