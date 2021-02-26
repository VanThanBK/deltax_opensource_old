
#pragma once

//robot geometry
//
//
//
//											/ \             RD_RF    
//										   /   \             /
//										  /     \ Theta2    /                                   ^ Y   ^ Z
//										 /       \ ________/____                                |    /
//                           Theta3     /         \            /                                |   /
//                                     /     *O    \          /                                 |  /
//                        RD_F_______ /             \        /                                  | /
//            ^                      /               \      /                                 __|/_____________>
//            |                      -----------------     /                                    |O             X
//            |                           Theta1          /
//            |                                          /_______RD_RE
//            |                                         /
//            |                                        /
//            |                                       /
//			  | 							    / \  /
//            |                      RD_E_____ /   \/
//     RD_B   |                               /  *  \     RD_U
//            |                               -------    /
//			  | 								 |      /
//			  | 					RD_W________ |_____/_
//			  | 										|
//			  | 										| _______RD_V
//			  |											^
//____________|__________________________________________________________________________________________________________
//

#ifdef DELTA_X_PULY_L
#define DEFAULT_RD_F	354.64   // SB			//size L
#define DEFAULT_RD_E	120.0	// SP = RD_E / 2
#define DEFAULT_RD_RF	150.0	// L
#define DEFAULT_RD_RE	415.0   // l

#define DEFAULT_RD_W	0.0
#define DEFAULT_RD_U	0.0
#define DEFAULT_RD_V	0.0

#define DEFAULT_MOVING_AREA_X		200
#define DEFAULT_MOVING_AREA_Y		200
#define DEFAULT_MOVING_AREA_Z	    500

#define DEFAULT_MOVING_AREA_LARGEST_DIAMETER	250			//mm

#define THETA1_HOME_POSITION -41.2				//deg
#define THETA2_HOME_POSITION -41.2
#define THETA3_HOME_POSITION -41.2

#define THETA1_STEPS_PER_2PI  9600				//200*16*3
#define THETA2_STEPS_PER_2PI  9600
#define THETA3_STEPS_PER_2PI  9600
#endif // DELTA_X_PULY_L


#ifdef DELTA_X_PULY_S
#define DEFAULT_RD_F	259.04   // SB			//size S  258.64 + 0.4
#define DEFAULT_RD_E	120.0	// SP = RD_E / 2
#define DEFAULT_RD_RF	130.0	// L
#define DEFAULT_RD_RE	315.0   // l

#define DEFAULT_RD_W	0.0
#define DEFAULT_RD_U	0.0
#define DEFAULT_RD_V	0.0

#define DEFAULT_MOVING_AREA_X		170
#define DEFAULT_MOVING_AREA_Y		170
#define DEFAULT_MOVING_AREA_Z	    402

#define DEFAULT_MOVING_AREA_LARGEST_DIAMETER	170			//mm

#define THETA1_HOME_POSITION -38.5				//deg -41.2	
#define THETA2_HOME_POSITION -38.5
#define THETA3_HOME_POSITION -38.5

#define THETA1_STEPS_PER_2PI  9600				//200*16*3
#define THETA2_STEPS_PER_2PI  9600
#define THETA3_STEPS_PER_2PI  9600
#endif // DELTA_X_PULY_S

#ifdef DELTA_X_PLANNET
#define DEFAULT_RD_F	295.0   // SB			//size plannet
#define DEFAULT_RD_E	120.0	// SP = RD_E / 2
#define DEFAULT_RD_RF	145.0	// L
#define DEFAULT_RD_RE	356.0   // l

#define DEFAULT_RD_W	0.0
#define DEFAULT_RD_U	0.0
#define DEFAULT_RD_V	0.0

#define DEFAULT_MOVING_AREA_X		180.0
#define DEFAULT_MOVING_AREA_Y		180.0
#define DEFAULT_MOVING_AREA_Z	    400.0

#define DEFAULT_MOVING_AREA_LARGEST_DIAMETER	210.0			//mm

#define THETA1_HOME_POSITION -29.9				//deg
#define THETA2_HOME_POSITION -29.9
#define THETA3_HOME_POSITION -29.9

#define THETA1_STEPS_PER_2PI  12800				//200*16*4
#define THETA2_STEPS_PER_2PI  12800
#define THETA3_STEPS_PER_2PI  12800
#endif // DELTA_X_PLANNET
