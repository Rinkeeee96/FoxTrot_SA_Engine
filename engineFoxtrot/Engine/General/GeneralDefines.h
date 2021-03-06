#pragma once

		
#define EXPORT					false
#define DLLEXPORT				__declspec( dllexport )

#define ZERO					0
#define ONE						1

#define WINDOW_WIDTH			1920	
#define WINDOW_HEIGHT			1080
#define WINDOW_WIDTH_CENTER		WINDOW_WIDTH/2
#define WINDOW_HEIGHT_CENTER	WINDOW_HEIGHT/2

#define MESSAGE_WIDTH			150
#define MESSAGE_HEIGHT			30

#define RANDOM_NUMBER_SEED		134775813
#define RADIANS2DEGREE			57.29577951f
#define DEGREE2RADIANS			0.01745329252f

#define NO_RED					0
#define NO_BLUE					0
#define NO_GREEN				0

#define FULL_RED				255
#define FULL_BLUE				255
#define FULL_GREEN				255


#define PLAYER_ID				2

#define DELTATIME_TIMESTEP_PHYSICS 1
#define DELTATIME_TIMESTEP_RENDER 2