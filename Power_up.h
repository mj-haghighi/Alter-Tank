

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
#include "Clock.h"

using namespace std;
#define PI 3.1415

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
          void set_flag_show(bool i);
          void set_Xposition(int i);
          void set_Yposition(int i);
          void set_Xposition_center(int i);
          void set_Yposition_center(int i);
          void set_flag_exist(bool i);
          bool get_flag_show();
          int  get_Xposition();
          int  get_Yposition();
          int get_Xposition_center();
          int get_Yposition_center();
          int get_flag_exist();
        };


      void Power_up:: set_flag_show(bool i)
          {
            flag_show=i;
          }
          void Power_up:: set_Xposition(int i)
          {
            Xposition=i;
          }
          void Power_up:: set_Yposition(int i)
          {
            Yposition=i;
          }
          void Power_up:: set_Xposition_center(int i)
          {
            Xposition_center=i;
          }
          void Power_up:: set_Yposition_center(int i)
          {
            Yposition_center=i;
          }
          void Power_up:: set_flag_exist(bool i)
          {
            flag_exist=i;
          }
          bool Power_up:: get_flag_show()
          {
            return (flag_show);
          }

          int Power_up:: get_Xposition()
          {
            return Xposition;
          }
          int Power_up:: get_Yposition()
          {
            return Yposition;
          }
          int Power_up:: get_Xposition_center()
          {
            return Xposition_center;
          }
          int Power_up:: get_Yposition_center()
          {
            return Yposition_center;
          }
          int Power_up:: get_flag_exist()
          {
            return flag_exist;
          }
  