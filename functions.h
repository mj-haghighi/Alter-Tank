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
#include "Power_up.h"

using namespace std;
#define PI 3.1415



//global variables

int frame_width=1800;
int frame_height=1020;
int gameTime=5*60*1000+1000;  // 5 min matches
int max_numbers_of_player=4;
int max_numbers_of_map=4;
SDL_Event event;
SDL_Surface* SCREEN = NULL;
SDL_Surface** tankScreen = new SDL_Surface*[max_numbers_of_player];
SDL_Surface** sparkScreen = new SDL_Surface*[max_numbers_of_player];
SDL_Surface** rotatedSpark = new SDL_Surface*[max_numbers_of_player];
SDL_Surface** mapScreen = new SDL_Surface*[max_numbers_of_map];
SDL_Surface** rotatedTank = new SDL_Surface*[max_numbers_of_player];
SDL_Surface** rotatedTankBG = new SDL_Surface*[max_numbers_of_player];
SDL_Surface** tankScreenBG = new SDL_Surface*[max_numbers_of_player];
SDL_Surface** chopperScreen = new SDL_Surface*[4];
SDL_Surface** rotatedChopper = new SDL_Surface*[4];
SDL_Surface** chopperShScreen = new SDL_Surface*[4];
SDL_Surface** rotatedShadow = new SDL_Surface*[4];
SDL_Surface** fireScreen = new SDL_Surface*[6];
SDL_Surface* heartScreen = new SDL_Surface;
SDL_Surface** power_upScreen = new SDL_Surface*[5];
SDL_Surface* shieldBG = new SDL_Surface;
SDL_Surface* shieldUG = new SDL_Surface;
SDL_Surface* rotatedShieldBG = new SDL_Surface;
SDL_Surface* rotatedShieldUG = new SDL_Surface;
SDL_Joystick *stick1=NULL;
SDL_Joystick *stick2=NULL;
Mix_Music *explosion;
Mix_Music *plane;
Mix_Music *emp;
Mix_Music *Menu;
Mix_Music *laser;



//function headers
void check_if_power_up_is_gotten(Power_up *power_up,Tank* tank,int numbers_of_player_in_game , int i,bool shield_flag [4]);
void check_if_chopper_drop_power_up(Chopper chopper,Power_up *power_up,int i);
int make_power_up(Power_up* power_up,int frame_height,int frame_width);
bool check_game_end(Tank *tank,int numbers_of_player_in_game);
int dictance(int x1 ,int y1 ,int x2,int y2);
int randomMap(int max_numbers_of_map,int mapNum);
void handle_move_event(Tank *tank,Bullet *bullet,int numbers_of_player_in_game,bool shield_flag[4]);
void handle_fire_event(Tank *tank,Bullet *bullet ,int numbers_of_player_in_game, bool shield_flag[4] );
void menu(SDL_Surface* SCREEN,int &numbers_of_player_in_game,SDL_Event &event);
void shift_bullets(Bullet *bullet);
void shoot(Tank *tank,Bullet *bullet , int i);
void shoot2(Tank *tank,int numbers_of_player_in_game,int k,bool shield_flag[4]);
void shoot3(SDL_Surface *SCREEN,Tank *tank,int numbers_of_player_in_game,int k,bool shield_flag[4]);
void apply_surface(int x,int y,SDL_Surface* source,SDL_Surface* destination);
char* NumToStr(int num);
char* timeString(int Min,int sec);
void random_position(SDL_Surface *SCREEN,Tank *tank,int i);
void show_winner(SDL_Surface* SCREEN,SDL_Event &event,TTF_Font* font,int i,int winner_score);



//functions
char *timeString(int Min,int sec)
{
    stringstream strs;
    if(sec<10)
    strs<<"AlterTank    "<<Min<<" : 0"<<sec;
    else strs<<"AlterTank    "<<Min<<" : "<<sec;
    string temp_str=strs.str();
    char* finall = new char(temp_str.length()+1);
    for(int i=0;i<temp_str.length();i++)
    {
        finall[i]=temp_str[i];
    }
    finall[temp_str.length()]='\0';
    return finall;
}


char* NumToStr(int num)  // for rectangle lives
{
    stringstream strs;
    strs<<num;
    string temp_str=strs.str();
    char* finall = new char(temp_str.length()+1);
    for(int i=0;i<temp_str.length();i++)
    {
        finall[i]=temp_str[i];
    }
    finall[temp_str.length()]='\0';
    return finall;
}

int  make_power_up(Power_up* power_up,int frame_height,int frame_width)
{
	int x = 200+rand()%1400;
	int y = 200+rand()%500;

	int i = rand()%100;
	if (i>=0 && i<20)
	{
		power_up[0].set_Xposition(x);
		power_up[0].set_Yposition(y);
		power_up[0].set_flag_exist(true);
		return(0);
	}
	else if (i>=20 && i<40)
	{
		power_up[1].set_Xposition(x);
		power_up[1].set_Yposition(y);
		power_up[1].set_flag_exist(true);
		return(1);
	}
	else if (i>=40 && i<60)
	{
		power_up[2].set_Xposition(x);
		power_up[2].set_Yposition(y);
		power_up[2].set_flag_exist(true);
		return(2);
	}
	else if (i>=60 && i<80)
	{
		power_up[3].set_Xposition(x);
		power_up[3].set_Yposition(y);
		power_up[3].set_flag_exist(true);
		return(3);
	}
    else if (i>=80 && i<=100)
    {
        power_up[4].set_Xposition(x);
        power_up[4].set_Yposition(y);
        power_up[4].set_flag_exist(true);
        return(4);  
    }
}

void check_if_chopper_drop_power_up(Chopper chopper,Power_up *power_up,int i)
{
        if (dictance(chopper.get_Xposition_center(),chopper.get_Yposition_center(),power_up[i].get_Xposition_center(),power_up[i].get_Yposition_center()) < 100 )
        {
            power_up[i].set_flag_show(true);
        }
}

void check_if_power_up_is_gotten(Power_up *power_up,Tank* tank,int numbers_of_player_in_game , int i,bool shield_flag[4])
{
	for (int j=0; j<numbers_of_player_in_game; j++)
	{
		if (dictance(tank[j].get_Xposition_center(),tank[j].get_Yposition_center(),power_up[i].get_Xposition_center(),power_up[i].get_Yposition_center())  < 65)
		{
			if (i==0)
			{
				tank[j].set_bulletNum(tank[j].get_bulletNum()+5);
			}
			else if (i==1)
			{
				tank[j].set_flag_weaponi(2,true);
				tank[j].set_weapon_kind(2);
			}
			else if (i==2)
			{
				tank[j].set_flag_weaponi(3,true);
				tank[j].set_weapon_kind(3);
			}
			else if (i==3)
			{
				tank[j].set_health(tank[j].get_health()+5);
			}
            else if (i==4)
            {
                //tank[j].set_flag_shield(true);
                shield_flag[j]=true;
                tank[j].set_flag_shield(true);
            }
			power_up[i].set_flag_exist(false);
			power_up[i].set_flag_show(false);

		}
	}
}

bool check_game_end(Tank *tank,int numbers_of_player_in_game)
{
	int k=0;
	int m=0;
	for (int i=0 ; i<numbers_of_player_in_game ; i++ )
	{
		if(tank[i].get_flag_exist()==true)
		{
			k++;
			m=i;
		}
	}
	if (k==1)
	{
		tank[m].set_score(tank[m].get_score() + 1);
		return (false);
	}
	else if (k==0)
	{
		return (false);
	}
	return (true);
}

void random_position(SDL_Surface *SCREEN,Tank *tank,int i)
{
    Uint32 *pixels = (Uint32 *) SCREEN->pixels;
    Uint8 *color=(Uint8 *) & ( pixels[(100) *SCREEN->w+(100)] );
    int x0;
    int y0;
    int angle;

    bool flag=true;
    while(flag)
    {
        x0=rand()%(frame_width-100)+50;
        y0=rand()%(frame_height-170)+50;
        int x=x0-sqrt(pow((tank[i].get_tankScreen_width()/2),2)+pow((tank[i].get_tankScreen_height()/2),2))*cos(tank[i].get_angle()/180.0*3.1415+PI/2-atan2(tank[i].get_tankScreen_height()/2,tank[i].get_tankScreen_width()/2));
        int y=y0+sqrt(pow((tank[i].get_tankScreen_width()/2),2)+pow((tank[i].get_tankScreen_height()/2),2))*sin(tank[i].get_angle()/180.0*3.1415+PI/2-atan2(tank[i].get_tankScreen_height()/2,tank[i].get_tankScreen_width()/2));


        color = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x)] );

        if( color[2]==100 && color[1]==100 && color[0]==100)
        {
                tank[i].set_Xposition_center(x);
                tank[i].set_Yposition_center(y);
                tank[i].set_critical_dots(SCREEN);
                int x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12;
                int y1,y2,y3,y4,y5,y6,y7,y8,y9,y10,y11,y12;

                x1=x+sqrt(pow((tank[i].get_tankScreen_height()/4),2)+pow((tank[i].get_tankScreen_width()/2),2))*cos(tank[i].get_angle()/180.0*3.1415-PI/2+atan2((tank[i].get_tankScreen_height()/4),(tank[i].get_tankScreen_width()/2))) ;
                y1=y-sqrt(pow((tank[i].get_tankScreen_height()/4),2)+pow((tank[i].get_tankScreen_width()/2),2))*sin(tank[i].get_angle()/180.0*3.1415-PI/2+atan2((tank[i].get_tankScreen_height()/4),(tank[i].get_tankScreen_width()/2))) ;

                x2=x+sqrt(pow((tank[i].get_tankScreen_height()/4),2)+pow((tank[i].get_tankScreen_width()/2),2))*cos(tank[i].get_angle()/180.0*3.1415+3*PI/2-atan2((tank[i].get_tankScreen_height()/4),(tank[i].get_tankScreen_width()/2))) ;
                y2=y-sqrt(pow((tank[i].get_tankScreen_height()/4),2)+pow((tank[i].get_tankScreen_width()/2),2))*sin(tank[i].get_angle()/180.0*3.1415+3*PI/2-atan2((tank[i].get_tankScreen_height()/4),(tank[i].get_tankScreen_width()/2))) ;

                x3= x+sqrt(pow((tank[i].get_tankScreen_width()/2),2)+pow((tank[i].get_tankScreen_height()/4),2))*cos(tank[i].get_angle()/180.0*3.1415+PI/2-atan2((tank[i].get_tankScreen_height()/4),(tank[i].get_tankScreen_width()/2)));
                y3= y-sqrt(pow((tank[i].get_tankScreen_width()/2),2)+pow((tank[i].get_tankScreen_height()/4),2))*sin(tank[i].get_angle()/180.0*3.1415+PI/2-atan2((tank[i].get_tankScreen_height()/4),(tank[i].get_tankScreen_width()/2)));

                x4= x+sqrt(pow((tank[i].get_tankScreen_width()/2),2)+pow((tank[i].get_tankScreen_height()/4),2))*cos(tank[i].get_angle()/180.0*3.1415+PI/2+atan2((tank[i].get_tankScreen_height()/4),(tank[i].get_tankScreen_width()/2)));
                y4= y-sqrt(pow((tank[i].get_tankScreen_width()/2),2)+pow((tank[i].get_tankScreen_height()/4),2))*sin(tank[i].get_angle()/180.0*3.1415+PI/2+atan2((tank[i].get_tankScreen_height()/4),(tank[i].get_tankScreen_width()/2)));

                x5=x+sqrt(pow((3*tank[i].get_tankScreen_height()/8),2)+pow((tank[i].get_tankScreen_width()/2),2))*cos(tank[i].get_angle()/180.0*3.1415-PI/2+atan2((3*tank[i].get_tankScreen_height()/8),(tank[i].get_tankScreen_width()/2))) ;
                y5=y-sqrt(pow((3*tank[i].get_tankScreen_height()/8),2)+pow((tank[i].get_tankScreen_width()/2),2))*sin(tank[i].get_angle()/180.0*3.1415-PI/2+atan2((3*tank[i].get_tankScreen_height()/8),(tank[i].get_tankScreen_width()/2))) ;

                x6=x+sqrt(pow((3*tank[i].get_tankScreen_height()/8),2)+pow((tank[i].get_tankScreen_width()/2),2))*cos(tank[i].get_angle()/180.0*3.1415+3*PI/2-atan2((3*tank[i].get_tankScreen_height()/8),(tank[i].get_tankScreen_width()/2))) ;
                y6=y-sqrt(pow((3*tank[i].get_tankScreen_height()/8),2)+pow((tank[i].get_tankScreen_width()/2),2))*sin(tank[i].get_angle()/180.0*3.1415+3*PI/2-atan2((3*tank[i].get_tankScreen_height()/8),(tank[i].get_tankScreen_width()/2))) ;

                x7=x+sqrt(pow((tank[i].get_tankScreen_height()/8),2)+pow((tank[i].get_tankScreen_width()/2),2))*cos(tank[i].get_angle()/180.0*3.1415-PI/2+atan2((tank[i].get_tankScreen_height()/8),(tank[i].get_tankScreen_width()/2))) ;
                y7=y-sqrt(pow((tank[i].get_tankScreen_height()/8),2)+pow((tank[i].get_tankScreen_width()/2),2))*sin(tank[i].get_angle()/180.0*3.1415-PI/2+atan2((tank[i].get_tankScreen_height()/8),(tank[i].get_tankScreen_width()/2))) ;

                x8=x+sqrt(pow((tank[i].get_tankScreen_height()/8),2)+pow((tank[i].get_tankScreen_width()/2),2))*cos(tank[i].get_angle()/180.0*3.1415+3*PI/2-atan2((tank[i].get_tankScreen_height()/8),(tank[i].get_tankScreen_width()/2))) ;
                y8=y-sqrt(pow((tank[i].get_tankScreen_height()/8),2)+pow((tank[i].get_tankScreen_width()/2),2))*sin(tank[i].get_angle()/180.0*3.1415+3*PI/2-atan2((tank[i].get_tankScreen_height()/8),(tank[i].get_tankScreen_width()/2))) ;

                x9= x+sqrt(pow((tank[i].get_tankScreen_width()/2),2)+pow((3*tank[i].get_tankScreen_height()/8),2))*cos(tank[i].get_angle()/180.0*3.1415+PI/2-atan2((3*tank[i].get_tankScreen_height()/8),(tank[i].get_tankScreen_width()/2)));
                y9= y-sqrt(pow((tank[i].get_tankScreen_width()/2),2)+pow((3*tank[i].get_tankScreen_height()/8),2))*sin(tank[i].get_angle()/180.0*3.1415+PI/2-atan2((3*tank[i].get_tankScreen_height()/8),(tank[i].get_tankScreen_width()/2)));

                x10= x+sqrt(pow((tank[i].get_tankScreen_width()/2),2)+pow((3*tank[i].get_tankScreen_height()/8),2))*cos(tank[i].get_angle()/180.0*3.1415+PI/2+atan2((3*tank[i].get_tankScreen_height()/8),(tank[i].get_tankScreen_width()/2)));
                y10= y-sqrt(pow((tank[i].get_tankScreen_width()/2),2)+pow((3*tank[i].get_tankScreen_height()/8),2))*sin(tank[i].get_angle()/180.0*3.1415+PI/2+atan2((3*tank[i].get_tankScreen_height()/8),(tank[i].get_tankScreen_width()/2)));

                x11= x+sqrt(pow((tank[i].get_tankScreen_width()/2),2)+pow((tank[i].get_tankScreen_height()/8),2))*cos(tank[i].get_angle()/180.0*3.1415+PI/2-atan2((tank[i].get_tankScreen_height()/8),(tank[i].get_tankScreen_width()/2)));
                y11= y-sqrt(pow((tank[i].get_tankScreen_width()/2),2)+pow((tank[i].get_tankScreen_height()/8),2))*sin(tank[i].get_angle()/180.0*3.1415+PI/2-atan2((tank[i].get_tankScreen_height()/8),(tank[i].get_tankScreen_width()/2)));

                x12= x+sqrt(pow((tank[i].get_tankScreen_width()/2),2)+pow((tank[i].get_tankScreen_height()/8),2))*cos(tank[i].get_angle()/180.0*3.1415+PI/2+atan2((tank[i].get_tankScreen_height()/8),(tank[i].get_tankScreen_width()/2)));
                y12= y-sqrt(pow((tank[i].get_tankScreen_width()/2),2)+pow((tank[i].get_tankScreen_height()/8),2))*sin(tank[i].get_angle()/180.0*3.1415+PI/2+atan2((tank[i].get_tankScreen_height()/8),(tank[i].get_tankScreen_width()/2)));


                bool f=true;

                color = (Uint8 *) & ( pixels[(y1) *SCREEN->w+(x1)] );
                if( color[2]>230 && color[1]>230 && color[0]>230 ) f=false;

                color = (Uint8 *) & ( pixels[(y2) *SCREEN->w+(x2)] );
                if( color[2]>230 && color[1]>230 && color[0]>230 ) f=false;

                color = (Uint8 *) & ( pixels[(y3) *SCREEN->w+(x3)] );
                if( color[2]>230 && color[1]>210 && color[0]>230 ) f=false;

                color = (Uint8 *) & ( pixels[(y4) *SCREEN->w+(x4)] );
                if( color[2]>230 && color[1]>230 && color[0]>230 ) f=false;

                color = (Uint8 *) & ( pixels[(y5) *SCREEN->w+(x5)] );
                if( color[2]>230 && color[1]>230 && color[0]>230 ) f=false;

                color = (Uint8 *) & ( pixels[(y6) *SCREEN->w+(x6)] );
                if( color[2]>230 && color[1]>230 && color[0]>230 ) f=false;

                color = (Uint8 *) & ( pixels[(y7) *SCREEN->w+(x7)] );
                if( color[2]>230 && color[1]>230 && color[0]>230 ) f=false;

                color = (Uint8 *) & ( pixels[(y8) *SCREEN->w+(x8)] );
                if( color[2]>230 && color[1]>230 && color[0]>230 ) f=false;

                color = (Uint8 *) & ( pixels[(y9) *SCREEN->w+(x9)] );
                if( color[2]>230 && color[1]>230 && color[0]>230 ) f=false;

                color = (Uint8 *) & ( pixels[(y10) *SCREEN->w+(x10)] );
                if( color[2]>230 && color[1]>230 && color[0]>230 ) f=false;

                color = (Uint8 *) & ( pixels[(y11) *SCREEN->w+(x11)] );
                if( color[2]>230 && color[1]>230 && color[0]>230 ) f=false;

                color = (Uint8 *) & ( pixels[(y12) *SCREEN->w+(x12)] );
                if( color[2]>230 && color[1]>230 && color[0]>230 ) f=false;


                if(f==true)
                for(int k=0 ; k<12 ; k++)
                {
                    color = (Uint8 *) & ( pixels[(tank[i].get_critical_dot(k,1)) *SCREEN->w+(tank[i].get_critical_dot(k,0))] );
                    if( color[2]>230 && color[1]>230 && color[0]>230 )
                    f=false;
                }

                if(f==true)
                {
                    tank[i].set_Xposition( x+sqrt(pow((tank[i].get_tankScreen_width()/2),2)+pow((tank[i].get_tankScreen_height()/2),2))*cos(tank[i].get_angle()/180.0*3.1415+atan2((tank[i].get_tankScreen_width()),(tank[i].get_tankScreen_height()))) );
                    tank[i].set_Yposition( y-sqrt(pow((tank[i].get_tankScreen_width()/2),2)+pow((tank[i].get_tankScreen_height()/4),2))*sin(tank[i].get_angle()/180.0*3.1415+atan2((tank[i].get_tankScreen_width()),(tank[i].get_tankScreen_height()))) );

                    tank[i].set_Xposition_center(x);
                    tank[i].set_Yposition_center(y);

                    flag=false;
                }
        }
    }
}

int randomMap(int max_numbers_of_map,int mapNum)
{
    int p=rand()%max_numbers_of_map;
    if(p==mapNum) randomMap(max_numbers_of_map,mapNum);
    else return p;
}

void shift_bullets(Bullet *bullet)
{
    bullet[40]=bullet[0];
    for(int i=1 ; i<=40 ; i++)
        bullet[i-1]=bullet[i];
}

void shoot(Tank *tank,Bullet *bullet , int i)  // Ordinary bullets
{
    bullet[0].set_Xposition(tank[i].get_Xposition_center() + (tank[i].get_tankScreen_height()/2)*cos(tank[i].get_angle()/180.0*3.1415));
    bullet[0].set_Yposition(tank[i].get_Yposition_center() - (tank[i].get_tankScreen_height()/2)*sin(tank[i].get_angle()/180.0*3.1415));
    bullet[0].set_angle(tank[i].get_angle());
    bullet[0].set_Xspeed(1);
    bullet[0].set_Yspeed(1);
    bullet[0].set_flag_exist(true);
    bullet[0].set_startTime((int)(SDL_GetTicks()));
    shift_bullets(bullet);
}

void shoot2(Tank *tank,int numbers_of_player_in_game,int k,bool shield_flag[4]) // EMP damage area
{
	for (int i ; i<numbers_of_player_in_game ; i++)
	{
		if (i!=k)
            if (tank[i].get_flag_exist()==true)
                if (dictance(tank[i].get_Xposition_center(),tank[i].get_Yposition_center(),tank[k].get_Xposition_center(),tank[k].get_Yposition_center())  <  500)
                {
                	if(shield_flag[i]==false)
                    tank[i].set_variable_for_shoot2(0);

                	if(shield_flag[i]==true)
                		shield_flag[i]=false;
                	if(tank[i].get_flag_shield()==true)
                	tank[i].set_flag_shield(false);
                }
	}
	if(sound_flag==true)
	Mix_PlayMusic(emp,0);
}

void shoot3(SDL_Surface *SCREEN,Tank *tank,int numbers_of_player_in_game,int k,bool shield_flag[4]) // Laser shot
{
    int x1 = tank[k].get_Xposition_center() + (tank[k].get_tankScreen_height()/2)*cos(tank[k].get_angle()/180.0*3.1415);
    int y1 = tank[k].get_Yposition_center() - (tank[k].get_tankScreen_height()/2)*sin(tank[k].get_angle()/180.0*3.1415);
    int x2,y2,n;
    int theta=tank[k].get_angle();
    double m=-1*tan(theta/180.0*3.1415);
    Uint32 *pixels = (Uint32 *) SCREEN->pixels;
    Uint8 *color;

    if(x1>tank[k].get_Xposition_center())
    {
        int x=1780;
        int y=y1+m*(x-x1);
        if(y>0 && y<900) n=1;
    }
    else if(x1<tank[k].get_Xposition_center())
    {
        int x=20;
        int y=y1+m*(x-x1);
        if(y>0 && y<900) n=2;
    }

    if(y1<tank[k].get_Yposition_center())
    {
        int y=20;
        int x=(y-y1+m*x1)/m;
        if(x>0 && x<1800) n=3;
    }
    else if(y1>tank[k].get_Yposition_center())
    {
        int y=900;
        int x=(y-y1+m*x1)/m;
        if(x>0 && x<1800) n=4;
    }

    if(n==1)  //Right
    {
        bool flag_hit=false;
        bool f=true;
        for(int x=x1 ; x<1800 ; x+=10)
        {
            int y=y1+m*(x-x1);
            color = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x)] );
            if(f==true)
            for(int i=0 ; i<numbers_of_player_in_game ; i++)
            {
                if( i!=k )
                {
                    if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10)
                    {
                        x2=x;
                        y2=y;
                        flag_hit=true;
                        if(shield_flag[i]==false)
                        tank[i].set_health(tank[i].get_health()-5);
                    	if(shield_flag[i]==true)
                    		shield_flag[i]=false;
                    	if(tank[i].get_flag_shield()==true)
                    		tank[i].set_flag_shield(false);
                        f=false;
                    }
                }
            }
            else break;
        }
        if(flag_hit==false)
        {
            x2=1780;
            y2=y1+m*(x2-x1);
        }
    }

    else if(n==2)  //Left
    {
        bool flag_hit=false;
        bool f=true;
        for(int x=x1 ; x>0 ; x-=10)
        {
            int y=y1+m*(x-x1);
            color = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x)] );
            if(f==true)
            for(int i=0 ; i<numbers_of_player_in_game ; i++)
            {
                if(i!=k)
                {
                    if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10)
                    {
                        x2=x;
                        y2=y;
                        flag_hit=true;
                        if(shield_flag[i]==false)
                        tank[i].set_health(tank[i].get_health()-5);
                    	if(shield_flag[i]==true)
                    		shield_flag[i]=false;
                    	if(tank[i].get_flag_shield()==true)
                    		tank[i].set_flag_shield(false);
                        f=false;
                    }
                }
            }
            else break;
        }
        if(flag_hit==false)
        {
            x2=20;
            y2=y1+m*(x2-x1);
        }
    }

    else if(n==3)  //Up
    {
        bool flag_hit=false;
        bool f=true;
        for(int y=y1 ; y>0 ; y-=10)
        {
            int x=(y-y1+m*x1)/m;
            color = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x)] );
            if(f==true)
            for(int i=0 ; i<numbers_of_player_in_game ; i++)
            {
                if(i!=k)
                {
                    if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10)
                    {
                        x2=x;
                        y2=y;
                        flag_hit=true;
                        if(shield_flag[i]==false)
                        tank[i].set_health(tank[i].get_health()-5);
                    	if(shield_flag[i]==true)
                    		shield_flag[i]=false;
                    	if(tank[i].get_flag_shield()==true)
                    		tank[i].set_flag_shield(false);
                        f=false;
                    }
                }
            }
            else break;
        }
        if(flag_hit==false)
        {
            y2=20;
            x2=(y2-y1+m*x1)/m;
        }
    }

    else if(n==4)  //Down
    {
        bool flag_hit=false;
        bool f=true;
        for(int y=y1 ; y<1020 ; y+=10)
        {
            int x=(y-y1+m*x1)/m;
            color = (Uint8 *) & ( pixels[(y) *SCREEN->w+(x)] );
            if(f==true)
            for(int i=0 ; i<numbers_of_player_in_game ; i++)
            {
                if(i!=k)
                {
                    if(color[2]>tank[i].get_R()-10 && color[2]<tank[i].get_R()+10 && color[1]>tank[i].get_G()-10 && color[1]<tank[i].get_G()+10 && color[0]>tank[i].get_B()-10 && color[0]<tank[i].get_B()+10)
                    {
                        x2=x;
                        y2=y;
                        flag_hit=true;
                        if(shield_flag[i]==false)
                        tank[i].set_health(tank[i].get_health()-5);
                    	if(shield_flag[i]==true)
                    		shield_flag[i]=false;
                    	if(tank[i].get_flag_shield()==true)
                    		tank[i].set_flag_shield(false);
                        f=false;
                    }
                }
            }
            else break;
        }
        if(flag_hit==false)
        {
            y2=880;
            x2=(y2-y1+m*x1)/m;
        }
    }

    tank[k].set_variable_for_shoot3(0);
    tank[k].set_laser_x1(x1);
    tank[k].set_laser_x2(x2);
    tank[k].set_laser_y1(y1);
    tank[k].set_laser_y2(y2);

    tank[k].set_flag_laser(false);

    if(sound_flag==true)
    Mix_PlayMusic(laser,0);

}

void handle_fire_event(Tank *tank,Bullet *bullet ,int numbers_of_player_in_game,bool shield_flag[4])
{
	if (event.type==SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_m:
			{
                if(tank[0].get_flag_exist()==true)
				if (numbers_of_player_in_game>=1)
				{
					switch(tank[0].get_weapon_kind())
					{
						case 1:
						{
                            if(tank[0].get_bulletNum()>0)
                            {
                                shoot(tank,bullet,0);
                                tank[0].set_bulletNum(tank[0].get_bulletNum()-1);
                            }
						} break;
						case 2:
						{
							if (tank[0].get_flag_weaponi(2)==true)
                            {
                                tank[0].set_flag_weaponi(2,false);
                                shoot2(tank,numbers_of_player_in_game,0,shield_flag);
                                tank[0].set_weapon_kind(1);
                            }
						} break;
						case 3:
						{
                            if (tank[0].get_flag_weaponi(3)==true)
                            {
                                tank[0].set_flag_weaponi(3,false);
                                tank[0].set_flag_laser(true);
                            }
						} break;
					}
				}
			} break;

            case SDLK_n:
			{
				if(tank[0].get_flag_exist()==true)
					if (tank[0].get_weapon_kind()==3)
					{
						tank[0].set_weapon_kind(1);
					}
					else if(tank[0].get_flag_weaponi(tank[0].get_weapon_kind()+1)==true)
					{
						tank[0].set_weapon_kind(tank[0].get_weapon_kind()+1);
					}
					else if (tank[0].get_weapon_kind()==1 && tank[0].get_flag_weaponi(3)==true)
					{
						tank[0].set_weapon_kind(3);
					}
					else if (tank[0].get_weapon_kind()==2 && tank[0].get_flag_weaponi(3)==false)
					{
						tank[0].set_weapon_kind(1);
					}
			}break;

			case SDLK_q:
			{
                if(tank[1].get_flag_exist()==true)
				if (numbers_of_player_in_game>=2)
				{
					switch(tank[1].get_weapon_kind())
					{
						case 1:
						{
							if(tank[1].get_bulletNum()>0)
                            {
                                shoot(tank,bullet,1);
                                tank[1].set_bulletNum(tank[1].get_bulletNum()-1);
                            }
						} break;
						case 2:
						{
							if (tank[1].get_flag_weaponi(2)==true)
								{
									shoot2(tank,numbers_of_player_in_game,1,shield_flag);
									tank[1].set_flag_weaponi(2,false);
									tank[1].set_weapon_kind(1);
								}
						} break;
						case 3:
						{
                            if(tank[1].get_flag_weaponi(3)==true)
                            {
                                tank[1].set_flag_weaponi(3,false);
                            }
                            tank[1].set_flag_laser(true);
						} break;
					}
				}
			} break;

			case SDLK_e:
			{
				if(tank[1].get_flag_exist()==true)
					if (tank[1].get_weapon_kind()==3)
					{
						tank[1].set_weapon_kind(1);
					}
					else if(tank[1].get_flag_weaponi(tank[1].get_weapon_kind()+1)==true)
					{
						tank[1].set_weapon_kind(tank[1].get_weapon_kind()+1);
					}
					else if (tank[1].get_weapon_kind()==1 && tank[1].get_flag_weaponi(3)==true)
					{
						tank[1].set_weapon_kind(3);
					}
					else if (tank[1].get_weapon_kind()==2 && tank[1].get_flag_weaponi(3)==false)
					{
						tank[1].set_weapon_kind(1);
					}
			}break;
		}
	}
}

int dictance(int x1 ,int y1 ,int x2,int y2)
{
	return(sqrt(pow(x1-x2,2)+pow(y1-y2,2)));
}


void handle_move_event(Tank *tank,Bullet *bullet,int numbers_of_player_in_game,bool shield_flag[4])
{

	if (numbers_of_player_in_game>=1)
	{
		if (event.type==SDL_KEYDOWN)
		{
		       //Adjust the velocit
			switch(event.key.keysym.sym)
			{
				case SDLK_UP:
            	{
           			tank[0].set_flag_UP(true);break;
       			}
      			case SDLK_DOWN:
   				{
      				tank[0].set_flag_DOWN(true);break;
      			}
            //for determining angle
           		case SDLK_LEFT:
       			{
       				tank[0].set_omega(1);break;
            	}
           		case SDLK_RIGHT:
       			{
           			tank[0].set_omega(-1);break;
           		}
			}
		}
		if (event.type==SDL_KEYUP)
		{
        //Adjust the velocit
        	switch( event.key.keysym.sym )
     	    {
           		case SDLK_UP:
           		{
           			tank[0].set_flag_UP(false);break;
           		}
            	case SDLK_DOWN:
            	{
           			tank[0].set_flag_DOWN(false);break;
           		}
        //for determining angle
           		case SDLK_LEFT:
           		{
           			tank[0].set_omega(0);break;
           		}
           		case SDLK_RIGHT:
           		{
         			tank[0].set_omega(0);break;
         		}
       		}
		}
	}

	if (numbers_of_player_in_game>=2)
	{

		if( event.type == SDL_KEYDOWN )//in ha rokh dad hastand halat nistand
  		{
        	//Adjust the velocity
      		switch( event.key.keysym.sym )
   			{
          		case SDLK_w:
           		{
           			tank[1].set_flag_UP(true);break;
            	}
      			case SDLK_s:
       			{
   			    	tank[1].set_flag_DOWN(true);break;
   				}
	            //for determining angle
            	case SDLK_a:
            	{
            		tank[1].set_omega(1); break;
            	}
            	case SDLK_d:
            	{
                	tank[1].set_omega(-1); break;
            	}
      		}
    	}
    //If a key was released
    	else if( event.type == SDL_KEYUP )
    	{
        //Adjust the velocit
        	switch( event.key.keysym.sym )
     		{
            	case SDLK_w:
            	{
            		tank[1].set_flag_UP(false);break;
            	}
            	case SDLK_s:
            	{
            		tank[1].set_flag_DOWN(false); break;
            	}
            //for determining angle
            	case SDLK_a:
            	{
            		tank[1].set_omega(0); break;
            	}
            	case SDLK_d:
            	{
            		tank[1].set_omega(0); break;
            	}
       		}
		}
	}

    if(numbers_of_player_in_game>=3)
    {
        if(event.type == SDL_JOYAXISMOTION)
        {
            //If joystick 0 has moved
            if( event.jaxis.which == 0 )
            {
                //If the Y axis changed
                if( event.jaxis.axis == 1 )
                {
                    //If the Y axis is neutral
                    if( ( event.jaxis.value > -8000 ) && ( event.jaxis.value < 8000 ) )
                    {
                        tank[2].set_flag_UP(false);
                        tank[2].set_flag_DOWN(false);
                    }
                    //If not
                    else
                    {
                        //Adjust the velocity
                        if( event.jaxis.value < 0 )
                        {
                            tank[2].set_flag_UP(true);
                        }
                        else
                        {
                            tank[2].set_flag_DOWN(true);
                        }
                    }
                }
            }
        }

        if(event.type==SDL_JOYBUTTONDOWN)
        {
            if(event.jbutton.which==0)
            switch(event.jbutton.button)
            {
                case 4:
                    tank[2].set_omega(1); break;

                case 5:
                    tank[2].set_omega(-1); break;

                case 3:
                    {
                        switch(tank[2].get_weapon_kind())
                        {
                            case 1:
                            {
                            	if(tank[2].get_flag_exist()==true)
                                if(tank[2].get_bulletNum()>0)
                                {
                                    shoot(tank,bullet,2);
                                    tank[2].set_bulletNum(tank[2].get_bulletNum()-1);
                                }
                            } break;
                            case 2:
                            {
                            	if(tank[2].get_flag_exist()==true)
                                if (tank[2].get_flag_weaponi(2)==true)
                                {
                                    tank[2].set_flag_weaponi(2,false);
                                    shoot2(tank,numbers_of_player_in_game,2,shield_flag);
                                    tank[2].set_weapon_kind(1);
                                }
                            } break;
                            case 3:
                            {
                            	if(tank[2].get_flag_exist()==true)
                                if (tank[2].get_flag_weaponi(3)==true)
                                {
                                    tank[2].set_flag_weaponi(3,false);
                                    tank[2].set_flag_laser(true);
                                }
                            } break;
                        }
                    }

                case 1:
                {
                    if(tank[2].get_flag_exist()==true)
					if (tank[2].get_weapon_kind()==3)
					{
						tank[2].set_weapon_kind(1);
					}
					else if(tank[2].get_flag_weaponi(tank[2].get_weapon_kind()+1)==true)
					{
						tank[2].set_weapon_kind(tank[2].get_weapon_kind()+1);
					}
					else if (tank[2].get_weapon_kind()==1 && tank[2].get_flag_weaponi(3)==true)
					{
						tank[2].set_weapon_kind(3);
					}
					else if (tank[2].get_weapon_kind()==2 && tank[2].get_flag_weaponi(3)==false)
					{
						tank[2].set_weapon_kind(1);
					}
                }break;
            }
        }

        if(event.type==SDL_JOYBUTTONUP)
        {
            if(event.jbutton.which==0)
            switch(event.jbutton.button)
            {
                case 4:
                    tank[2].set_omega(0); break;

                case 5:
                    tank[2].set_omega(0); break;
            }
        }
    }


    if(numbers_of_player_in_game>=4)
    {
        if(event.type == SDL_JOYAXISMOTION)
        {
            if(event.jaxis.which==1)
            {
                //If the Y axis changed
                if(event.jaxis.axis==1)
                {
                    //If the Y axis is neutral
                    if( (event.jaxis.value>-8000) && (event.jaxis.value<8000) )
                    {
                        tank[3].set_flag_UP(false);
                        tank[3].set_flag_DOWN(false);
                    }
                    //If not
                    else
                    {
                        //Adjust the velocity
                        if( event.jaxis.value < 0 )
                        {
                            tank[3].set_flag_UP(true);
                        }
                        else
                        {
                            tank[3].set_flag_DOWN(true);
                        }
                    }
                }
            }
        }


        if(event.type==SDL_JOYBUTTONDOWN)
        {
            if(event.jbutton.which==1)
            switch(event.jbutton.button)
            {
                case 4:
                    tank[3].set_omega(1); break;

                case 5:
                    tank[3].set_omega(-1); break;

                case 3:
                    {
                        switch(tank[3].get_weapon_kind())
                        {
                            case 1:
                            {	
                            	if(tank[3].get_flag_exist()==true)
                                if(tank[3].get_bulletNum()>0)
                                {
                                    shoot(tank,bullet,3);
                                    tank[3].set_bulletNum(tank[3].get_bulletNum()-1);
                                }
                            } break;
                            case 2:
                            {
                            	if(tank[3].get_flag_exist()==true)
                                if (tank[3].get_flag_weaponi(2)==true)
                                {
                                    tank[3].set_flag_weaponi(2,false);
                                    shoot2(tank,numbers_of_player_in_game,3,shield_flag);
                                    tank[3].set_weapon_kind(1);
                                }
                            } break;
                            case 3:
                            {
                            	if(tank[3].get_flag_exist()==true)
                                if (tank[3].get_flag_weaponi(3)==true)
                                {
                                    tank[3].set_flag_weaponi(3,false);
                                    tank[3].set_flag_laser(true);
                                }
                            } break;
                        }
                    }
                case 1:
                {
                    if(tank[3].get_flag_exist()==true)
					if (tank[3].get_weapon_kind()==3)
					{
						tank[3].set_weapon_kind(1);
					}
					else if(tank[3].get_flag_weaponi(tank[3].get_weapon_kind()+1)==true)
					{
						tank[3].set_weapon_kind(tank[3].get_weapon_kind()+1);
					}
					else if (tank[3].get_weapon_kind()==1 && tank[3].get_flag_weaponi(3)==true)
					{
						tank[3].set_weapon_kind(3);
					}
					else if (tank[3].get_weapon_kind()==2 && tank[3].get_flag_weaponi(3)==false)
					{
						tank[3].set_weapon_kind(1);
					}
                }break;
            }
        }

        if(event.type==SDL_JOYBUTTONUP)
        {
            if(event.jbutton.which==1)
            switch(event.jbutton.button)
            {
                case 4:
                    tank[3].set_omega(0); break;

                case 5:
                    tank[3].set_omega(0); break;
            }
        }
    }
}

void apply_surface(int x,int y,SDL_Surface* source,SDL_Surface* destination)
{
    SDL_Rect offset;
    offset.x=x;
    offset.y=y;

    SDL_BlitSurface(source,NULL,destination,&offset);
}

void menu(SDL_Surface* SCREEN,int &numbers_of_player_in_game,SDL_Event &event)
{
	int mouse_xpos=0;
	int mouse_ypos=0;
	SDL_Surface* setting=IMG_Load("setting.png");
	SDL_Surface* playgame=IMG_Load("playgame.png");
	SDL_Surface* singleplayer=IMG_Load("singleplayer.png");
	SDL_Surface* twoplayer=IMG_Load("twoplayer.png");
	SDL_Surface* threeplayer=IMG_Load("threeplayer.png");
	SDL_Surface* fourplayer=IMG_Load("fourplayer.png");
    SDL_Surface* mute=IMG_Load("mute.png");
    SDL_Surface* unmute=IMG_Load("voice.png");

	bool flag_show_playgame=true;
    bool flag_show_setting=true;
	int setting_xpos=600;
	int setting_ypos=550;
	SDL_Rect setting_offset;
	setting_offset.x=setting_xpos;
	setting_offset.y=setting_ypos;
	int playgame_xpos=600;
	int playgame_ypos=150;
	SDL_Rect playgame_offset;
	playgame_offset.x=playgame_xpos;
	playgame_offset.y=playgame_ypos;
	int singleplayer_xpos=600;
	int singleplayer_ypos=30;
	//int singleplayer_final_ypos=30;
	SDL_Rect singleplayer_offset;
	singleplayer_offset.x=singleplayer_xpos;
	singleplayer_offset.y=singleplayer_ypos;
	int twoplayer_xpos=600;
	int twoplayer_ypos=30;//240
	int twoplayer_final_ypos=240;
	SDL_Rect twoplayer_offset;
	twoplayer_offset.x=twoplayer_xpos;
	twoplayer_offset.y=twoplayer_ypos;
	int threeplayer_xpos=600;
	int threeplayer_ypos=30;//450
	int threeplayer_final_ypos=450;
	SDL_Rect threeplayer_offset;
	threeplayer_offset.x=threeplayer_xpos;
	threeplayer_offset.y=threeplayer_ypos;
	int fourplayer_xpos=600;
	int fourplayer_ypos=30;//660
	int fourplayer_final_ypos=660;
	SDL_Rect fourplayer_offset;
	fourplayer_offset.x=fourplayer_xpos;
	fourplayer_offset.y=fourplayer_ypos;

    int mute_xpos=800;
    int mute_ypos=200;
    SDL_Rect mute_offset;
    mute_offset.x=mute_xpos;
    mute_offset.y=mute_ypos;

    int unmute_xpos=800;
    int unmute_ypos=500;
    SDL_Rect unmute_offset;
    unmute_offset.x=unmute_xpos;
    unmute_offset.y=unmute_ypos;


	bool quit=true;
	int i=0;
	while(quit==true)
	{
		SDL_FreeSurface(SCREEN);
		boxRGBA(SCREEN,0,0,frame_width,frame_height,255,255,255,255);
		if (SDL_PollEvent(&event)){}
			if (event.type==SDL_QUIT)
			{
				exit(0);
			}
		mouse_xpos=event.motion.x;
		mouse_ypos=event.motion.y;

		if (mouse_xpos>playgame_xpos && mouse_xpos<playgame_xpos+playgame->w &&
			mouse_ypos>playgame_ypos && mouse_ypos<playgame_ypos+playgame->h && flag_show_setting==true)
		{
			flag_show_playgame=false;
		}
		else if (mouse_xpos<playgame_xpos || mouse_xpos>playgame_xpos+playgame->w)
		{
			flag_show_playgame=true;
			i=0;
		}
		if (flag_show_playgame==false && flag_show_setting==true)
		{
			for (; i<20 ; i++)
			{
				twoplayer_offset.y=twoplayer_ypos+i*(twoplayer_final_ypos-30)/20.0;
				threeplayer_offset.y=threeplayer_ypos+i*(threeplayer_final_ypos-30)/20.0;
				fourplayer_offset.y=fourplayer_ypos+i*(fourplayer_final_ypos-30)/20.0;

				SDL_BlitSurface(singleplayer,NULL,SCREEN,&singleplayer_offset);
				SDL_BlitSurface(twoplayer,NULL,SCREEN,&twoplayer_offset);
				SDL_BlitSurface(threeplayer,NULL,SCREEN,&threeplayer_offset);
				SDL_BlitSurface(fourplayer,NULL,SCREEN,&fourplayer_offset);
				SDL_Flip(SCREEN);
			}
		}
		if(i==20)
		{
				SDL_BlitSurface(singleplayer,NULL,SCREEN,&singleplayer_offset);
				SDL_BlitSurface(twoplayer,NULL,SCREEN,&twoplayer_offset);
				SDL_BlitSurface(threeplayer,NULL,SCREEN,&threeplayer_offset);
				SDL_BlitSurface(fourplayer,NULL,SCREEN,&fourplayer_offset);
				SDL_Flip(SCREEN);
				SDL_FreeSurface(SCREEN);

			if (SDL_PollEvent(&event))
			{
				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (mouse_xpos>singleplayer_offset.x && mouse_xpos<singleplayer_offset.x+singleplayer->w
						&& mouse_ypos>singleplayer_offset.y && mouse_ypos<singleplayer_offset.y + singleplayer->h)
					{
						numbers_of_player_in_game=1;
						return;
					}

					else if (mouse_xpos>twoplayer_offset.x && mouse_xpos<twoplayer_offset.x+twoplayer->w
						&& mouse_ypos>twoplayer_offset.y && mouse_ypos<twoplayer_offset.y + twoplayer->h)
					{
						numbers_of_player_in_game=2;
						return;
					}

					else if (mouse_xpos>threeplayer_offset.x && mouse_xpos<threeplayer_offset.x+threeplayer->w
						&& mouse_ypos>threeplayer_offset.y && mouse_ypos<threeplayer_offset.y + threeplayer->h)
					{
						numbers_of_player_in_game=3;
						return;
					}

					else if (mouse_xpos>fourplayer_offset.x && mouse_xpos<fourplayer_offset.x+fourplayer->w
						&& mouse_ypos>fourplayer_offset.y && mouse_ypos<fourplayer_offset.y + fourplayer->h)
					{
						numbers_of_player_in_game=4;
						return;
					}
				}
			}
		}


        if (mouse_xpos>setting_xpos && mouse_xpos<setting_xpos+setting->w &&
            mouse_ypos>setting_ypos && mouse_ypos<setting_ypos+setting->h && flag_show_playgame==true)
        {
            flag_show_setting=false;
        }
        else if (mouse_xpos<setting_xpos || mouse_xpos>setting_xpos+setting->w)
        {
            flag_show_setting=true;
        }

        
        if (flag_show_setting==false && flag_show_playgame==true)
        {
            SDL_BlitSurface(mute,NULL,SCREEN,&mute_offset);
            SDL_BlitSurface(unmute,NULL,SCREEN,&unmute_offset);
        }


        if (flag_show_setting==false && flag_show_playgame==true)
            if (SDL_PollEvent(&event))
            {
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (mouse_xpos>mute_offset.x && mouse_xpos<mute_offset.x+mute->w
                        && mouse_ypos>mute_offset.y && mouse_ypos<mute_offset.y + mute->h)
                    {
                        sound_flag=false;
			Mix_PauseMusic();
                    }

                    else if (mouse_xpos>unmute_offset.x && mouse_xpos<unmute_offset.x + unmute->w
                        && mouse_ypos>unmute_offset.y && mouse_ypos<unmute_offset.y + unmute->h)
                    {
                        sound_flag=true;
			Mix_ResumeMusic();
                    }
                }
            }

		if (flag_show_playgame==true && flag_show_setting==true)
		{
			SDL_BlitSurface(setting,NULL,SCREEN,&setting_offset);
			SDL_BlitSurface(playgame,NULL,SCREEN,&playgame_offset);
		}
		SDL_Flip(SCREEN);
	}

	Mix_PauseMusic();

	return ;
}

void show_winner(SDL_Surface* SCREEN,SDL_Event &event,TTF_Font* font,int i,int winner_score)
{
    if (SDL_PollEvent(&event)){}
    int mouse_xpos;
    int mouse_ypos;

    const char* tankAddress[4]={"tank1.png","tank2.png","tank3.png","tank4.png"};
    SDL_Surface* winner_tank=IMG_Load(tankAddress[i]);
    SDL_Surface* winner=IMG_Load("winner.png");
    SDL_Surface* back=IMG_Load("back.png");
    SDL_Rect winner_offset;
    SDL_Rect winner_tank_offset;
    SDL_Rect back_offset;

    winner_offset.x=715;
    winner_offset.y=360;

    winner_tank_offset.x=1005;
    winner_tank_offset.y=405;
    
    back_offset.x=0;
    back_offset.y=0;

    SDL_Color font_col={0,0,0};

    while(true)
    {

        if (SDL_PollEvent(&event))
        {
            if (event.type==SDL_QUIT)
            {
                exit(0);
            }
        }

        mouse_xpos=event.motion.x;
    	mouse_ypos=event.motion.y;
        SDL_FreeSurface(SCREEN);
        boxRGBA(SCREEN,0,0,frame_width,frame_height,255,255,255,255); 
        SDL_BlitSurface(winner,NULL,SCREEN,&winner_offset);
        SDL_BlitSurface(winner_tank,NULL,SCREEN,&winner_tank_offset);
        SDL_BlitSurface(back,NULL,SCREEN,&back_offset);
        SDL_Surface *message =TTF_RenderText_Solid(font,NumToStr(winner_score),font_col);
        apply_surface(857,483,message,SCREEN);

        if (SDL_PollEvent(&event)){}
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (mouse_xpos>back_offset.x && mouse_xpos<back_offset.x + back->w
                        && mouse_ypos>back_offset.y && mouse_ypos<back_offset.y + back->h)
                    {
                        break;
                    }
                }
        SDL_Flip(SCREEN);


    } 
}
