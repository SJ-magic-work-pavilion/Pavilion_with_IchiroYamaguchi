/************************************************************
************************************************************/
#pragma once

#include "ofMain.h"
#include "sj_common.h"
#include "BlockPattern.h"

/************************************************************
************************************************************/
enum{
	MAX_LOGICAL_CHS = 30,
};
enum F_COLORBAR{
	F_COLORBAR_SYNC,
	F_COLORBAR_COL0,
	F_COLORBAR_COL1,
	F_COLORBAR_STROBE,
};

struct BLOCK{
	/* */
	vector<int> LogicalCh[MAX_LOGICAL_CHS];
	
	const BP_PATTERN_ID Bp_Pattern_id;
	const F_COLORBAR f_ColorBar;
	
	int LogicalId[MAX_LOGICAL_CHS];
	
	/* */
	int Progress_id;
	float t_From;
	double Progress;
	
	double NumWavesInSpace;
	
	bool b_Blank;
};

struct BLOCK_GROUP{
	enum{
		MAX_BLOCKS = 10,
	};
	
	char BlockName[BUF_SIZE];
	int Weight;
	
	BLOCK Block[MAX_BLOCKS];
};

/************************************************************
************************************************************/
void test_BlockGrouping();
bool IsPeriodOfBlockGroup(BLOCK &block);

extern BLOCK_GROUP BlockGrouping[];
extern const int NUM_GROUPTYPES;

