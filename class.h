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
            void set_Xposition_center(int i)
       		{
       			Xposition_center=i;
       		}
       		void set_Yposition_center(int i)
       		{
       			Yposition_center=i;
       		}
       		void set_Xposition(int i)
       		{
       			Xposition=i;
       		}
       		void set_Yposition(int i)
       		{
       			Yposition=i;
       		}
       		void set_angle(int i)
       		{
       			angle=i;
       		}
       		void set_speed(int i)
       		{
       			speed=i;
       		}
       		void set_Xspeed(int i)
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
       		void set_Yspeed(int i)
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
       		int get_Yposition_center()
       		{
       			return Yposition_center;
       		}
       		int get_Xposition_center()
       		{
       			return Xposition_center;
       		}
       		int get_Xposition()
       		{
       			return(Xposition);
       		}
       		int get_Yposition()
       		{
       			return(Yposition);
       		}
       		int get_angle()
       		{
       			return(angle);
       		}
       		int get_Xspeed()
       		{
       			return(Xspeed);
       		}
       		int get_Yspeed()
       		{
       			return(Yspeed);
       		}
       		void move()
       		{
       			Xposition+=Xspeed;
       			Yposition+=Yspeed;
       		}

       		void random_position()
       		{
       			int i=(int)(rand()%80)/20;
       			if (i==0)
       			{
       				set_Xposition(0);
       				set_Yposition(50+rand()%800);// bolandi safhe
       				//int j=(rand()%100)/50;
       				//if (j==0) j=(-1);
       				//set_angle(j*(rand()%70));
       			}
       			else if (i==1)
       			{
       				set_Yposition(0);
       				set_Xposition(100+rand()%1600);
       				//set_angle(190+rand()%160);
       			}
       			else if (i==2)
       			{
       				set_Xposition(1800);
       				set_Yposition(50+rand()%800);
       				//set_angle(100+rand()%160);
       			}
       			else if(i==3)
       			{
       				set_Yposition(1020);
       				set_Xposition(100+rand()%1600);
       				//set_angle(10+rand()%160);
       			}
       				//set_speed(10);
       				//set_Xspeed(1);
       				//set_Yspeed(1);
       		}
       	};

struct Clock
{
    uint32_t last_tick_time=0;
    uint32_t delta=0;

    int tick()
    {
        uint32_t tick_time = SDL_GetTicks();
        delta = tick_time - last_tick_time;
        last_tick_time = tick_time;
        return delta;
    }
}cl;



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
	public:
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

		/////////////////////////////
		void move(int i);
		void turn_around();

		void set_flag_weaponi(int i ,bool j)
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

		bool get_flag_weaponi(int i)
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

};




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
       	void collision_with_tank(SDL_Surface *SCREEN,Tank *tank,int i,Mix_Music *explosion);
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



class Power_up
       	{
       		private:
       			int Xposition;
       			int Yposition;
       			int Xposition_center;
       			int Yposition_center;
       			bool flag_exist;
       			bool flag_show;

    		public:
    			void set_flag_show(bool i)
    			{
    				flag_show=i;
    			}
    			void set_Xposition(int i)
    			{
    				Xposition=i;
    			}
    			void set_Yposition(int i)
    			{
    				Yposition=i;
    			}
    			void set_Xposition_center(int i)
    			{
    				Xposition_center=i;
    			}
    			void set_Yposition_center(int i)
    			{
    				Yposition_center=i;
    			}
    			void set_flag_exist(bool i)
    			{
    				flag_exist=i;
    			}
    			bool get_flag_show()
    			{
    				return (flag_show);
    			}

    			int  get_Xposition()
    			{
    				return Xposition;
    			}
    			int  get_Yposition()
    			{
    				return Yposition;
    			}
    			int get_Xposition_center()
    			{
    				return Xposition_center;
    			}
    			int get_Yposition_center()
    			{
    				return Yposition_center;
    			}
    			int get_flag_exist()
    			{
    				return flag_exist;
    			}
       	};




