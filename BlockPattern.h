/************************************************************
************************************************************/
#pragma once

#include "ofMain.h"

#include "sj_common.h"
#include "shortPattern.h"

/************************************************************
************************************************************/
enum{
	MAX_SHORTPATTERN_INDEX = 10,
};
enum BP_PATTERN_ID{
	BP_PERIOD = -1,
	
	BP_FLOW = 0,
	BP_SIN,
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
	double Duration;
	const int NUM_LOGICAL_CHS;
	const double NumWaves_inSpace_From;
	const double NumWaves_inSpace_To;
	
	const SP_AND_PARAM ShortPattern_Param[MAX_SHORTPATTERN_INDEX];
};


/************************************************************
************************************************************/
void test_BlockPattern();

/************************************************************
************************************************************/
extern const struct BLOCK_PATTERN Bp[];
extern const int NUM_PATTERN_TYPES_BP;
