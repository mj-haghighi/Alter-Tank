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
#include "functions.h"

using namespace std;
#define PI 3.1415


int main()
{
	srand((unsigned)time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_INIT_JOYSTICK;
	Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
	explosion=Mix_LoadMUS("explosion.wav");
	plane=Mix_LoadMUS("Plane.mp3");
	emp=Mix_LoadMUS("EMP.mp3");
	Menu=Mix_LoadMUS("Menu.mp3");
	laser=Mix_LoadMUS("Laser.mp3");
	TTF_Font *font = TTF_OpenFont("font.ttf",18); // defining & loading font
	TTF_Font *font2 = TTF_OpenFont("font2.ttf",42); // defining & loading font
	SDL_Color font_color={0,255,127};  // font color


	int last_mouse_right_click_Xposition=0;
	int last_mouse_right_click_Yposition=0;
	int mouse_Xposition;
	int mouse_Yposition;
	int numbers_of_player_in_game=2;
	int map_number_in_game;

	bool shield_flag[4]={true,true,true,true};


   cout<<SDL_NumJoysticks()<<endl;
    stick1=SDL_JoystickOpen(0);
    stick2=SDL_JoystickOpen(1);
    cout<<SDL_JoystickOpened(0)<<endl<<SDL_JoystickOpened(1)<<endl;

	SCREEN=SDL_SetVideoMode(frame_width,frame_height,32,SDL_SWSURFACE);
	map_number_in_game=randomMap(max_numbers_of_map,map_number_in_game);

	const char* tankAddress[4]={"tank1.png","tank2.png","tank3.png","tank4.png"};
	const char* mapAddress[4]={"map1.png","map2.png","map3.png","map4.png"};
	const char* tankBGAddress[4]={"tank1z.png","tank2z.png","tank3z.png","tank4z.png"};
	const char* sparkAddress[4]={"spark1.png","spark2.png","spark3.png","spark4.png"};
    const char* chopperAddress[4]={"hele1.png","hele2.png","hele3.png","hele4.png"};
    const char* chopper_shadowAddress[4]={"helesh1.png","helesh2.png","helesh3.png","helesh4.png"};
    const char* heartAddress={"heart.png"};
    const char* fireAddress[6]={"fire1.png","fire2.png","fire3.png","fire4.png","fire5.png","fire6.png"};
    const char* power_upAddress[5]={"shoot.png","shoot2.png","shoot3.png","jon.png","Shield.png"};

    int spark_number=0;
    int chopper_number=0;
    shieldUG=IMG_Load("shield2.png");
    shieldBG=IMG_Load("shieldBG.png");

    rotatedShieldBG = rotozoomSurface(shieldBG,0,1.0,0);
    rotatedShieldUG = rotozoomSurface(shieldUG,0,1.0,0);

    heartScreen=IMG_Load(heartAddress);

	for (int i=0 ; i<max_numbers_of_player; i++)
	{
		tankScreen[i]=NULL;
    	tankScreen[i]=IMG_Load(tankAddress[i]);
    	rotatedTank[i]=rotozoomSurface(tankScreen[i],/*angle*/0,/*zoom*/1.0,0);
    	if (!(tankScreen[i]))
    			printf("%s\n",IMG_GetError());


        tankScreenBG[i]=NULL;
        tankScreenBG[i]=IMG_Load(tankBGAddress[i]);
        rotatedTankBG[i]=rotozoomSurface(tankScreenBG[i],/*angle*/0,/*zoom*/1.0,0);
        if(!(tankScreenBG[i]))
    			printf("%s\n",IMG_GetError());

		sparkScreen[i]=IMG_Load(sparkAddress[i]);
		if (!(sparkScreen[i]))
    			printf("%s\n",IMG_GetError());

	    mapScreen[i]=IMG_Load(mapAddress[i]);
	    if (!(mapScreen[i]))
    			printf("%s\n",IMG_GetError());

	}

    for (int i=0 ; i<5 ; i++)
  	{
  		power_upScreen[i]=NULL;
  		power_upScreen[i]=IMG_Load(power_upAddress[i]);
  		if (!(power_upAddress[i]))
  			printf("%s\n",IMG_GetError());
  	}


    for(int i=0 ; i<4 ; i++)
	{
        chopperShScreen[i]=NULL;
        chopperShScreen[i]=IMG_Load(chopper_shadowAddress[i]);
        rotatedShadow[i]=rotozoomSurface(chopperShScreen[i],0,1.0,0);
        if(!(chopperShScreen[i]))
    			printf("%s\n",IMG_GetError());
	}


	for(int i=0 ; i<4 ; i++)
	{
        chopperScreen[i]=NULL;
        chopperScreen[i]=IMG_Load(chopperAddress[i]);
        rotatedChopper[i]=rotozoomSurface(chopperScreen[i],0,1.0,0);
        if(!(chopperScreen[i]))
    			printf("%s\n",IMG_GetError());
	}

	for (int i=0 ; i<6 ; i++)
	{
		fireScreen[i]=IMG_Load(fireAddress[i]);
		if (!(fireScreen[i]))
		{
			printf("%s\n",IMG_GetError());
		}
	}


    if(sound_flag==true)
    Mix_PlayMusic(Menu,-1);

    Power_up *power_up=new Power_up[4];
    Bullet *bullet=new Bullet[41];
	Tank *tank=new Tank[4];
	Chopper chopper;


	for (int i=0 ; i<numbers_of_player_in_game ; i++)
	{
		tank[i].set_score(0);
		shield_flag[i]=false;
		tank[i].set_flag_laser(false);
	}
        tank[0].set_R(46); // setting RGB colors for the background of tanks
        tank[0].set_G(122);
        tank[0].set_B(201);

        tank[1].set_R(116);
        tank[1].set_G(80);
        tank[1].set_B(43);

        tank[2].set_R(10);
        tank[2].set_G(170);
        tank[2].set_B(77);

        tank[3].set_R(248);
        tank[3].set_G(70);
        tank[3].set_B(170);


	SDL_Rect fire_offset;
    SDL_Rect chopper_offset;
    SDL_Rect heart_offset[4];
    SDL_Rect tankInfo_offset;
	SDL_Rect spark_offset;
	SDL_Rect offset;
	SDL_Rect BG_offset;
	SDL_Rect power_up_offset;


	int power_up_number=0;
	int frame_number=0;
    int startTime=SDL_GetTicks();
	int winner_tank_number=0;
	int max_score=0;

    bool flag_timer=true;

	menu(SCREEN,numbers_of_player_in_game,event);

	while(true)
	{
        if(flag_timer==false)
        {
            max_score=0;
            flag_timer=true;
            SDL_Delay(100);
            for (int i=0 ; i<numbers_of_player_in_game ; i++)
            {
            	if (tank[i].get_score()>max_score)
            	{
            		winner_tank_number=i;
            		max_score=tank[i].get_score();
            	}
            }
			show_winner(SCREEN,event,font2,winner_tank_number,tank[winner_tank_number].get_score());
            menu(SCREEN,numbers_of_player_in_game,event);
            startTime=SDL_GetTicks();

            for (int i=0 ; i<numbers_of_player_in_game ; i++)
            {
                tank[i].set_score(0);
                shield_flag[i]=false;
                tank[i].set_flag_laser(false);
            }
        }

		map_number_in_game=randomMap(max_numbers_of_map,map_number_in_game);

	// initial power up atributes
	for (int i=0 ; i<5 ; i++)
	{
		power_up[i].set_Xposition(0);
		power_up[i].set_Yposition(0);
		power_up[i].set_Xposition_center(25);
		power_up[i].set_Yposition_center(25);
		power_up[i].set_flag_exist(false);
		power_up[i].set_flag_show(false);
	}
	// initial tank atributes
	for (int i=0 ; i<numbers_of_player_in_game ; i++)
	{
		tank[i].set_flag_shield(false);
        tank[i].set_flag_UP(false);
		tank[i].set_flag_DOWN(false);
		tank[i].set_flag_exist(true);
		tank[i].set_flag_laser(false);
		tank[i].set_Xposition(990);
		tank[i].set_Yposition(380);
		tank[i].set_Xposition_center(tankScreen[i]->w/2+tank[i].get_Xposition());
		tank[i].set_Yposition_center(tankScreen[i]->h/2+tank[i].get_Yposition());
		tank[i].set_health(10);
		tank[i].set_speed(8);
		tank[i].set_angle(90);
		tank[i].set_omega(0);
		tank[i].set_Xspeed(0);
		tank[i].set_Yspeed(0);
		tank[i].set_weapon_kind(1);// 1-> is normal veapon
		tank[i].set_tankScreen_width(tankScreen[i]->w);
		tank[i].set_tankScreen_height(tankScreen[i]->h);
		tank[i].set_variable_for_shoot2(30);
		tank[i].set_variable_for_shoot3(30);
		tank[i].set_bulletNum(10);
		tank[i].set_critical_dots(SCREEN);
		tank[i].set_flag_weaponi(1,true);
		tank[i].set_flag_weaponi(2,false);
		tank[i].set_flag_weaponi(3,false);
		tank[i].set_variable_for_fire(22);
	}

	//initial bullet atributes
	for(int i=0 ; i<=40 ; i++)
	{
        bullet[i].set_Xposition(0);
        bullet[i].set_Yposition(0);
        bullet[i].set_flag_exist(false);
        bullet[i].set_angle(0);
        bullet[i].set_speed(12);
        bullet[i].set_Xspeed(0);
        bullet[i].set_Yspeed(0);
        bullet[i].set_radius(5);
        bullet[i].set_existingTime(7000);
    }

    	//initial chopper atributes
		chopper.set_Xposition(-200);
		chopper.set_Yposition(-200);
		chopper.set_Xposition_center(chopperScreen[0]->w/2);
		chopper.set_Yposition_center(chopperScreen[0]->h/2);
    	chopper.set_angle(0);
    	chopper.set_speed(0);
    	chopper.set_Xspeed(0);
    	chopper.set_Yspeed(0);


    boxRGBA(SCREEN,0,0,frame_width,frame_height,100,100,100,255);
    SDL_BlitSurface(mapScreen[map_number_in_game],NULL,SCREEN,NULL);

	for(int i=0 ; i<numbers_of_player_in_game ; i++)
        random_position(SCREEN,tank,i);


    Mix_PauseMusic();

	bool Continue=true;
	while(Continue)
	{
        int currentTime=SDL_GetTicks();
        int passedTime=currentTime-startTime;
        int leftTime;
        if(passedTime>=gameTime)
        {
            flag_timer=false;
            leftTime=0;
        }
		else leftTime=gameTime-passedTime;


        int Min=leftTime/(60*1000);
        int sec=leftTime/1000-Min*60;

        SDL_WM_SetCaption(timeString(Min,sec),NULL);


            frame_number++;
            if(frame_number%800==700)
            {
                if(sound_flag==true)
                    Mix_PlayMusic(plane,0);
            }

       		if(frame_number%800==0)
       		{
				power_up_number = make_power_up(power_up,frame_height,frame_width);
				power_up[power_up_number].set_Xposition_center(power_up[power_up_number].get_Xposition()+power_upScreen[power_up_number]->w/2);
				power_up[power_up_number].set_Yposition_center(power_up[power_up_number].get_Yposition()+power_upScreen[power_up_number]->h/2);
       			chopper.random_position();
       			chopper.set_Xposition_center(chopper.get_Xposition()+rotatedChopper[0]->w/2);
				chopper.set_Yposition_center(chopper.get_Yposition()+rotatedChopper[0]->h/2);

       			if(chopper.get_Xposition()<power_up[power_up_number].get_Xposition())
       			{
       				chopper.set_angle( (int)(180 / 3.1415 * atan( (float)(power_up[power_up_number].get_Yposition_center()-chopper.get_Yposition_center()) / (float)(chopper.get_Xposition_center()-power_up[power_up_number].get_Xposition_center() )) ));
       			}
       			else
       			{
       				chopper.set_angle( 180 + (int)(180.0 / 3.14159265 * atan( (float)(power_up[power_up_number].get_Yposition_center()-chopper.get_Yposition_center()) / (float)(chopper.get_Xposition_center()-power_up[power_up_number].get_Xposition_center() )) ));
       			}

       			chopper.set_speed(10);
       			chopper.set_Xspeed(1);
       			chopper.set_Yspeed(1);
       		}

       		if (power_up[power_up_number].get_flag_exist()==true)
       		{
				check_if_chopper_drop_power_up(chopper,power_up,power_up_number);
       		}
       		if (power_up[power_up_number].get_flag_exist()==true && power_up[power_up_number].get_flag_show()==true)
       		{
 				check_if_power_up_is_gotten(power_up,tank,numbers_of_player_in_game ,power_up_number,shield_flag);
       		}

			if(frame_number==2401) frame_number=0;


			if (SDL_PollEvent(&event))
			{

/*W*/			if(event.type==SDL_QUIT)
				{
					exit(0);
				}
				else
				{
                    handle_move_event(tank,bullet,numbers_of_player_in_game,shield_flag);
                    handle_fire_event(tank,bullet,numbers_of_player_in_game,shield_flag);
				}
			}

			//checking tank health
            for(int i=0 ; i<numbers_of_player_in_game ; i++)
            {
                if(tank[i].get_health()<=0)
                {
                	tank[i].set_flag_exist(false);
                	if(tank[i].get_variable_for_fire()==22)
                		tank[i].set_variable_for_fire(0);
                }
            }

			boxRGBA(SCREEN,0,0,frame_width,frame_height,100,100,100,255);

/*H*/

			//set tank speed
        	for (int i=0 ; i<numbers_of_player_in_game ; i++)
			{
				SDL_FreeSurface(rotatedTank[i]);
				tank[i].turn_around();
/*I*/				rotatedTank[i]=rotozoomSurface(tankScreen[i],tank[i].get_angle()-90,1.0,0);
				if(tank[i].get_flag_UP()==true)
				{
					tank[i].set_Yspeed(-1);
					tank[i].set_Xspeed(1);
				}
				if(tank[i].get_flag_DOWN()==true)
				{
					tank[i].set_Xspeed(-1);
					tank[i].set_Yspeed(1);
				}
				if (tank[i].get_flag_UP()==false  &&  tank[i].get_flag_DOWN()==false)
/*L*/				{
					tank[i].set_Xspeed(0);
					tank[i].set_Yspeed(0);
				}
			}

			// tanks move
/*E*/     	for(int i=0;i<numbers_of_player_in_game;i++)
        	{
				tank[i].move(1);
        	}

			// bullets move
       		for(int i=39 ; i>=0 ; i--)
        	{
                if((SDL_GetTicks())-bullet[i].get_startTime()>=bullet[i].get_existingTime())
                    bullet[i].set_flag_exist(false);
/*T*/           if(bullet[i].get_flag_exist()==true)
            	{
               		filledCircleRGBA(SCREEN,bullet[i].get_Xposition(),bullet[i].get_Yposition(),5,255,165,0,255);
               		bullet[i].move();
            	}
        	}

            for(int i=0;i<numbers_of_player_in_game;i++)
			{
/*R*/           if(tank[i].get_flag_exist()==true)
                {
                    BG_offset.x=tank[i].get_Xposition();
                    BG_offset.y=tank[i].get_Yposition();
                    BG_offset.x-=rotatedTank[i]->w/2-tankScreen[i]->w/2;
                    BG_offset.y-=rotatedTank[i]->h/2-tankScreen[i]->h/2;
                    rotatedTankBG[i]=rotozoomSurface(tankScreenBG[i],tank[i].get_angle()-90,1.0,0);
                    SDL_BlitSurface(rotatedTankBG[i],NULL,SCREEN,&BG_offset);
                    SDL_FreeSurface(rotatedTankBG[i]);
                }
			}


            //checking laser shot
            for(int i=0 ; i<numbers_of_player_in_game ; i++)
            {
                if(tank[i].get_flag_laser()==true)
                {
                    shoot3(SCREEN,tank,numbers_of_player_in_game,i,shield_flag);
                    tank[i].set_flag_laser(false);
                    tank[i].set_weapon_kind(1);
                }

                if(tank[i].get_variable_for_shoot3() < 20)
				{
                    lineRGBA(SCREEN,tank[i].get_laser_x1(),tank[i].get_laser_y1(),tank[i].get_laser_x2(),tank[i].get_laser_y2(),255,0,0,255);
                    tank[i].set_variable_for_shoot3(tank[i].get_variable_for_shoot3()+1);
				}
            }


            //checking bullet collision with tanks
            for(int i=0 ; i<numbers_of_player_in_game ; i++)
            {
                if(tank[i].get_flag_exist()==true)
                    for(int j=0 ; j<40 ; j++)
                    {
                        if(bullet[j].get_flag_exist()==true)
                            bullet[j].collision_with_tank(SCREEN,tank,i,explosion,shield_flag);
                    }
            }


        	//blit all surface and set center of each tank
			for(int i=0;i<numbers_of_player_in_game;i++)
			{
                if(tank[i].get_flag_exist()==true)
                {
/*U*/			    tank[i].set_Xposition_center(tankScreen[i]->w/2+tank[i].get_Xposition());
                    tank[i].set_Yposition_center(tankScreen[i]->h/2+tank[i].get_Yposition());
                    offset.x=tank[i].get_Xposition();
                    offset.y=tank[i].get_Yposition();
                    offset.x-=rotatedTank[i]->w/2-tankScreen[i]->w/2;
                    offset.y-=rotatedTank[i]->h/2-tankScreen[i]->h/2;
                    SDL_BlitSurface(rotatedTank[i],NULL,SCREEN,&offset);
                    if (shield_flag[i]==true && tank[i].get_flag_shield()==true)
                    {
                        rotatedShieldUG=rotozoomSurface(shieldUG,tank[i].get_angle()-90,1.0,0);
                        SDL_BlitSurface(rotatedShieldUG,NULL,SCREEN,&offset);
                    }

                    tank[i].set_critical_dots(SCREEN);

                    //showing tank information under the map
                    tankInfo_offset.x=225+i*450;
                    tankInfo_offset.y=930;
                    heart_offset[i].x=175+i*450;
                    heart_offset[i].y=927;
                    SDL_BlitSurface(tankScreen[i],NULL,SCREEN,&tankInfo_offset);

                    //showing health
                    SDL_Surface *message =TTF_RenderText_Solid(font,NumToStr(tank[i].get_health()),font_color);
                    apply_surface(tankInfo_offset.x-25,tankInfo_offset.y,message,SCREEN);
                    SDL_BlitSurface(heartScreen,NULL,SCREEN,&heart_offset[i]);

                    //showing bullet number
                    message =TTF_RenderText_Solid(font,NumToStr(tank[i].get_bulletNum()),font_color);
                    filledCircleRGBA(SCREEN,tankInfo_offset.x-33,tankInfo_offset.y+61,5,255,165,0,255);
                    apply_surface(tankInfo_offset.x-25,tankInfo_offset.y+50,message,SCREEN);

                    //showing score
                    message =TTF_RenderText_Solid(font,"Score =",font_color);
                    apply_surface(tankInfo_offset.x+60,tankInfo_offset.y,message,SCREEN);
                    message =TTF_RenderText_Solid(font,NumToStr(tank[i].get_score()),font_color);
                    apply_surface(tankInfo_offset.x+122,tankInfo_offset.y,message,SCREEN);

                    //showing weapon kind
                    if(tank[i].get_weapon_kind()==1)
                    message =TTF_RenderText_Solid(font,"Normal",font_color);
                    else if(tank[i].get_weapon_kind()==2)
                    message =TTF_RenderText_Solid(font,"EMP",font_color);
                    else if(tank[i].get_weapon_kind()==3)
                    message =TTF_RenderText_Solid(font,"Laser",font_color);
                    apply_surface(tankInfo_offset.x+60,tankInfo_offset.y+50,message,SCREEN);
				}
			}

			//create animation for shoot2
			for (int i=0 ; i<numbers_of_player_in_game ; i++)
			{
				if (tank[i].get_variable_for_shoot2() < 20 )
				{
					if (spark_number>13)
					{
						spark_number=0;
					}
					spark_number++;
					spark_offset.x=tank[i].get_Xposition();
					spark_offset.y=tank[i].get_Yposition();
					spark_offset.x-=rotatedTank[i]->w/2-tankScreen[i]->w/2;
					spark_offset.y-=rotatedTank[i]->h/2-tankScreen[i]->h/2;
					rotatedSpark[spark_number%4]=rotozoomSurface(sparkScreen[spark_number%4],tank[i].get_angle()-90,1.0,0);
					SDL_BlitSurface(rotatedSpark[spark_number%4],NULL,SCREEN,&spark_offset);
					tank[i].set_variable_for_shoot2(tank[i].get_variable_for_shoot2()+1);
					if(tank[i].get_variable_for_shoot2() == 20 )
                        tank[i].set_health(tank[i].get_health()-5);
				}
			}

			//creat animation for tank fire
			for (int i=0 ; i<numbers_of_player_in_game ; i++)
			{
				if (tank[i].get_variable_for_fire()<=20)
				{
					fire_offset.x=tank[i].get_Xposition();
					fire_offset.y=tank[i].get_Yposition();
					fire_offset.x-=rotatedTank[i]->w/2-tankScreen[i]->w/2;
					fire_offset.y-=rotatedTank[i]->h/2-tankScreen[i]->h/2;
					//
					SDL_BlitSurface(fireScreen[frame_number%6],NULL,SCREEN,&fire_offset);
					tank[i].set_variable_for_fire(tank[i].get_variable_for_fire()+1);
				}
			}

            // map is included to surface
			SDL_BlitSurface(mapScreen[map_number_in_game],NULL,SCREEN,NULL);


			if (power_up[power_up_number].get_flag_show()==true && power_up[power_up_number].get_flag_exist()==true)
       		{
       			power_up_offset.x=power_up[power_up_number].get_Xposition();
       			power_up_offset.y=power_up[power_up_number].get_Yposition();
       			SDL_BlitSurface(power_upScreen[power_up_number],NULL,SCREEN,&power_up_offset);
       		}

			// check colision for tanks with walls
        	for(int i=0;i<numbers_of_player_in_game;i++)
				tank[i].check_collision(SCREEN);

        	// check colision of bullets with walls
        	for(int i=39 ; i>=0 ; i--)
       		{
            	if(bullet[i].get_flag_exist()==true)
          	    {
					bullet[i].check_collision(SCREEN);
           		}
       		}

       		// CHOPPER operation={movment and shadow creation}
       		chopper.move();

       		SDL_FreeSurface(rotatedShadow[frame_number%4]);
       		SDL_FreeSurface(rotatedChopper[frame_number%4]);
       		chopper_offset.x=chopper.get_Xposition();
       		chopper_offset.y=chopper.get_Yposition();
       		chopper_offset.y+=100;
       		rotatedShadow[frame_number%4]=rotozoomSurface(chopperShScreen[frame_number%4],chopper.get_angle()-90,1.5,0);
       		rotatedChopper[frame_number%4]=rotozoomSurface(chopperScreen[frame_number%4],chopper.get_angle()-90,2,0);
       		SDL_BlitSurface(rotatedShadow[frame_number%4],NULL,SCREEN,&chopper_offset);
       		chopper_offset.y=chopper.get_Yposition();
       		chopper_offset.x=chopper.get_Xposition();
       		SDL_BlitSurface(rotatedChopper[frame_number%4],NULL,SCREEN,&chopper_offset);
       		chopper.set_Xposition_center(chopper.get_Xposition()+rotatedChopper[0]->w/2);
			chopper.set_Yposition_center(chopper.get_Yposition()+rotatedChopper[0]->h/2);


    	    int time=cl.tick();
			SDL_Flip(SCREEN);
			if(time<10)
				SDL_Delay(10-time);
			else
				SDL_Delay(10);

			SDL_FreeSurface(SCREEN);

			if(frame_number%100==0)
        	{
            	Continue=check_game_end(tank,numbers_of_player_in_game);
        	}
		}
	}
	return 0;
}
