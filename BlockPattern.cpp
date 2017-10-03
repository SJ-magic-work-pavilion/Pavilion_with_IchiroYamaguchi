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
	{	"FLOW",			
		1	, // Duration[sec]		
		12	, // Num Logical chs		
		0	, // num waves from		
		0	, // to		
		{	//		
			{	SHORT_PATTERN::Sp_FlowOn	},
			{	SHORT_PATTERN::Sp_FlowOff	},
			{	NULL	},
		},			
	},				
	{	"SIN",			
		1	, // Duration[sec]		
		12	, // Num Logical chs		
		0.5	, // num waves from		
		1.5	, // to		
		{	//		
			{	SHORT_PATTERN::Sp_cos	},
			{	NULL	},
		},			
	},				
};					
					
const int NUM_PATTERN_TYPES_BP = sizeof(Bp) / sizeof(Bp[0]);					
