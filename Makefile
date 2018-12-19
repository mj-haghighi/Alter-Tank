#Copyright Notice:
#The files within this zip file are copyrighted by Lazy Foo' Productions (2004-2014)
#and may not be redistributed without written permission.

#OBJS specifies which files to compile as part of the project
OBJS = main.cpp functions.h Chopper.h Bullet.h Clock.h Power_up.h Tank.h

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf -lSDL_mixer

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main.out

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS)  -o $(OBJ_NAME)  $(COMPILER_FLAGS) $(LINKER_FLAGS)
