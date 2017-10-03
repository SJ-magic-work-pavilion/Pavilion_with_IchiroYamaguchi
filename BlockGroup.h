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

struct BLOCK{
	vector<int> LogicalCh[MAX_LOGICAL_CHS];
	
	const BP_PATTERN_ID Bp_Pattern_id;
	int Progress_id;
	float t_From;
	
	double NumWavesInSpace;
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

