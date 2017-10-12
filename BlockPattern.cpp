/************************************************************
************************************************************/
#include "BlockPattern.h"

/************************************************************
************************************************************/
/******************************
******************************/
void test_BlockPattern()
{
	printf("%d\n", NUM_PATTERN_TYPES_BP);
}

/************************************************************
************************************************************/
const struct BLOCK_PATTERN Bp[] = {					
	{	"FLOW_12",			
		1.5	, // Duration from[sec]		
		1	, // to		
		12	, // Num Logical chs		
		0	, // num waves from		
		0	, // to		
		{	//		
			{	SHORT_PATTERN::Sp_FlowOn	},
			{	SHORT_PATTERN::Sp_FlowOff	},
			{	NULL	},
		},			
	},				
	{	"FLOW_6",			
		1	, // Duration from[sec]		
		0.6	, // to		
		6	, // Num Logical chs		
		0	, // num waves from		
		0	, // to		
		{	//		
			{	SHORT_PATTERN::Sp_FlowOn	},
			{	SHORT_PATTERN::Sp_FlowOff	},
			{	NULL	},
		},			
	},				
	{	"SIN_12",			
		1.5	, // Duration from[sec]		
		1	, // to		
		12	, // Num Logical chs		
		0.5	, // num waves from		
		2	, // to		
		{	//		
			{	SHORT_PATTERN::Sp_cos	},
			{	NULL	},
		},			
	},				
	{	"SIN_6",			
		1	, // Duration from[sec]		
		0.6	, // to		
		6	, // Num Logical chs		
		0.25	, // num waves from		
		1	, // to		
		{	//		
			{	SHORT_PATTERN::Sp_cos	},
			{	NULL	},
		},			
	},				
	{	"STROBE_1",			
		0.15	, // Duration from[sec]		
		0.08	, // to		
		2	, // Num Logical chs		
		0	, // num waves from		
		0	, // to		
		{	//		
			{	SHORT_PATTERN::Sp_Flash__1_2	},
			{	NULL	},
		},			
	},				
	{	"STROBE_2",			
		0.15	, // Duration from[sec]		
		0.08	, // to		
		2	, // Num Logical chs		
		0	, // num waves from		
		0	, // to		
		{	//		
			{	SHORT_PATTERN::Sp_Flash__1_2	},
			{	SHORT_PATTERN::Sp_Flash__1_2	},
			{	SHORT_PATTERN::Sp_Flash__1_2	},
			{	SHORT_PATTERN::Sp_Flash__1_2	},
			{	SHORT_PATTERN::Sp_Flash__2_2	},
			{	SHORT_PATTERN::Sp_Flash__2_2	},
			{	SHORT_PATTERN::Sp_Flash__2_2	},
			{	SHORT_PATTERN::Sp_Flash__2_2	},
			{	NULL	},
		},			
	},				
	{	"ON_HIGH",			
		1	, // Duration from[sec]		
		1	, // to		
		1	, // Num Logical chs		
		0	, // num waves from		
		0	, // to		
		{	//		
			{	SHORT_PATTERN::Sp_On_High	},
			{	NULL	},
		},			
	},				
};					
					
const int NUM_PATTERN_TYPES_BP = sizeof(Bp) / sizeof(Bp[0]);					
