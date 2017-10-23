/************************************************************
************************************************************/
#pragma once

#include "ofMain.h"

#include "sj_common.h"
#include "shortPattern.h"

/************************************************************
************************************************************/
enum{
	MAX_SHORTPATTERN_INDEX = 30,
};
enum BP_PATTERN_ID{
	BP_PERIOD = -1,
	
	BP_FLOW_12 = 0,
	BP_FLOW_6,
	BP_SIN_12,
	BP_SIN_6,
	BP_STROBE_24,
	BP_STROBE_1,
	BP_STROBE_2,
	BP_ON_HIGH,
};


/************************************************************
class/ struct
************************************************************/
/**************************************************
**************************************************/
struct SP_AND_PARAM{
	const FUNC_SP pShortPattern;
};

/**************************************************
**************************************************/
struct BLOCK_PATTERN{
	char name[BUF_SIZE];
	const double Duration_From;
	const double Duration_To;
	
	const int NUM_LOGICAL_CHS;
	const double NumWaves_inSpace_From;
	const double NumWaves_inSpace_To;
	
	const bool b_LogicalID_Random;
	const bool b_ValidCh_VolSync;
	
	const int BlankProbability;
	
	const SP_AND_PARAM ShortPattern_Param[MAX_SHORTPATTERN_INDEX];
};


/************************************************************
************************************************************/
void test_BlockPattern();

/************************************************************
************************************************************/
extern const struct BLOCK_PATTERN Bp[];
extern const int NUM_PATTERN_TYPES_BP;
