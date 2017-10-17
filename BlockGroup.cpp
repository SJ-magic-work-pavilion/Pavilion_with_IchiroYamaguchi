/************************************************************
************************************************************/
#include "BlockGroup.h"

/************************************************************
************************************************************/

/******************************
******************************/
void test_BlockGrouping()
{
	char buf[1000];
	sprintf(buf, "../../../BlockGroup.txt");
	FILE* fp;
	fp = fopen(buf, "w");
	if(fp == NULL){
		printf("File open Error\n");
		std::exit(1);
	}
	
	for(int i = 0; i < NUM_GROUPTYPES; i++){
		fprintf(fp, "/*****************************************************\n");
		fprintf(fp, "BlockGrouping name = %s\n", BlockGrouping[i].BlockName);
		fprintf(fp, "*****************************************************\n");
		
		for(int j = 0; !IsPeriodOfBlockGroup(BlockGrouping[i].Block[j]); j++){
			fprintf(fp, "/************************************************\n");
			fprintf(fp, "block %d\n", j);
			fprintf(fp, "************************************************/\n");
			fprintf(fp, "> Bp name = %s\n", Bp[BlockGrouping[i].Block[j].Bp_Pattern_id].name);
			
			fprintf(fp, "> Logical chs\n");
			for(int k = 0; k < MAX_LOGICAL_CHS; k++){
				if(BlockGrouping[i].Block[j].LogicalCh[k].size()){
					fprintf(fp, "> Logical %4d:(size = %4d) = ", k, int(BlockGrouping[i].Block[j].LogicalCh[k].size()));
					for(int m = 0; m < BlockGrouping[i].Block[j].LogicalCh[k].size(); m++){
						fprintf(fp, "%4d, ", BlockGrouping[i].Block[j].LogicalCh[k][m]);
					}
					fprintf(fp, "\n");
				}
			}
		}
		
		fprintf(fp, "\n");
	}
	
	fclose(fp);
}

/******************************
******************************/
bool IsPeriodOfBlockGroup(BLOCK &block)
{
	if(block.Bp_Pattern_id == BP_PERIOD)	return true;
	else									return false;
}

/************************************************************
************************************************************/
BLOCK_GROUP BlockGrouping[] = {							
	{	"FLOW"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	0, 1,	},
					{	2, 3,	},
					{	4, 5,	},
					{	6, 7,	},
					{	8, 9, 	},
					{	10, 11, 	},
					{	12, 13, 	},
					{	14, 15, 	},
					{	16, 17, 	},
					{	18, 19, 	},
					{	20, 21, 	},
					{	22, 23, 	},
				},			
				BP_FLOW_12	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"FLOW_REV"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	22, 23, 	},
					{	20, 21, 	},
					{	18, 19, 	},
					{	16, 17, 	},
					{	14, 15, 	},
					{	12, 13, 	},
					{	10, 11, 	},
					{	8, 9, 	},
					{	6, 7,	},
					{	4, 5,	},
					{	2, 3,	},
					{	0, 1,	},
				},			
				BP_FLOW_12	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"FLOW_OUT"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	10, 11, 12, 13, 	},
					{	8, 9, 14, 15, 	},
					{	6, 7, 16, 17, 	},
					{	4, 5, 18, 19, 	},
					{	2, 3, 20, 21,	},
					{	0, 1, 22, 23, 	},
				},			
				BP_FLOW_6	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"FLOW_IN"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	0, 1, 22, 23, 	},
					{	2, 3, 20, 21,	},
					{	4, 5, 18, 19, 	},
					{	6, 7, 16, 17, 	},
					{	8, 9, 14, 15, 	},
					{	10, 11, 12, 13, 	},
				},			
				BP_FLOW_6	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"FLOW_TWIST"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	0, 23, 	},
					{	2, 21, 	},
					{	4, 19, 	},
					{	6, 17, 	},
					{	8, 15, 	},
					{	10, 13, 	},
					{	12, 11, 	},
					{	14, 9, 	},
					{	16, 7, 	},
					{	18, 5, 	},
					{	20, 3, 	},
					{	22, 1, 	},
				},			
				BP_FLOW_12	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"FLOW_TWIST_REV"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	1, 22, 	},
					{	3, 20, 	},
					{	5, 18, 	},
					{	7, 16, 	},
					{	9, 14, 	},
					{	11, 12, 	},
					{	13, 10, 	},
					{	15, 8, 	},
					{	17, 6, 	},
					{	19, 4, 	},
					{	21, 2, 	},
					{	23, 0, 	},
				},			
				BP_FLOW_12	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"FLOW_TWIST_OUT"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	10, 12, 1, 23, 	},
					{	8, 14, 3, 21, 	},
					{	6, 16, 5, 19, 	},
					{	4, 18, 7, 17, 	},
					{	2, 20, 9, 15, 	},
					{	0, 22, 11, 13, 	},
				},			
				BP_FLOW_6	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"FLOW_TWIST_IN"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	11, 13, 0, 22, 	},
					{	9, 15, 2, 20, 	},
					{	7, 17, 4, 18, 	},
					{	5, 19, 6, 16, 	},
					{	3, 21, 8, 14, 	},
					{	1, 23, 10, 12, 	},
				},			
				BP_FLOW_6	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"FLOW__AND__STOP"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	0, 	},
					{	2, 	},
					{	4, 	},
					{	6, 	},
					{	8, 	},
					{	10, 	},
					{	12, 	},
					{	14, 	},
					{	16, 	},
					{	18, 	},
					{	20, 	},
					{	22, 	},
				},			
				BP_FLOW_12	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// Block[0]				
				{// LogicalCh[]			
					{	1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 	},
				},			
				BP_ON_HIGH	,	// Bp_Pattern_id	
				false	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"FLOW_REV__AND__STOP"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	22, 	},
					{	20, 	},
					{	18, 	},
					{	16, 	},
					{	14, 	},
					{	12, 	},
					{	10, 	},
					{	8, 	},
					{	6, 	},
					{	4, 	},
					{	2, 	},
					{	0, 	},
				},			
				BP_FLOW_12	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// Block[0]				
				{// LogicalCh[]			
					{	1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 	},
				},			
				BP_ON_HIGH	,	// Bp_Pattern_id	
				false	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"STOP__AND__FLOW"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	1, 	},
					{	3, 	},
					{	5, 	},
					{	7, 	},
					{	9, 	},
					{	11, 	},
					{	13, 	},
					{	15, 	},
					{	17, 	},
					{	19, 	},
					{	21, 	},
					{	23, 	},
				},			
				BP_FLOW_12	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// Block[0]				
				{// LogicalCh[]			
					{	0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 	},
				},			
				BP_ON_HIGH	,	// Bp_Pattern_id	
				false	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"STOP__AND__FLOW_REV"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	23, 	},
					{	21, 	},
					{	19, 	},
					{	17, 	},
					{	15, 	},
					{	13, 	},
					{	11, 	},
					{	9, 	},
					{	7, 	},
					{	5, 	},
					{	3, 	},
					{	1, 	},
				},			
				BP_FLOW_12	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// Block[0]				
				{// LogicalCh[]			
					{	0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 	},
				},			
				BP_ON_HIGH	,	// Bp_Pattern_id	
				false	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"SIN"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	0, 1,	},
					{	2, 3,	},
					{	4, 5,	},
					{	6, 7,	},
					{	8, 9, 	},
					{	10, 11, 	},
					{	12, 13, 	},
					{	14, 15, 	},
					{	16, 17, 	},
					{	18, 19, 	},
					{	20, 21, 	},
					{	22, 23, 	},
				},			
				BP_SIN_12	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"SIN_REV"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	22, 23, 	},
					{	20, 21, 	},
					{	18, 19, 	},
					{	16, 17, 	},
					{	14, 15, 	},
					{	12, 13, 	},
					{	10, 11, 	},
					{	8, 9, 	},
					{	6, 7,	},
					{	4, 5,	},
					{	2, 3,	},
					{	0, 1,	},
				},			
				BP_SIN_12	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"SIN_OUT"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	10, 11, 12, 13, 	},
					{	8, 9, 14, 15, 	},
					{	6, 7, 16, 17, 	},
					{	4, 5, 18, 19, 	},
					{	2, 3, 20, 21,	},
					{	0, 1, 22, 23, 	},
				},			
				BP_SIN_6	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"SIN_IN"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	0, 1, 22, 23, 	},
					{	2, 3, 20, 21,	},
					{	4, 5, 18, 19, 	},
					{	6, 7, 16, 17, 	},
					{	8, 9, 14, 15, 	},
					{	10, 11, 12, 13, 	},
				},			
				BP_SIN_6	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"SIN_TWIST"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	0, 23, 	},
					{	2, 21, 	},
					{	4, 19, 	},
					{	6, 17, 	},
					{	8, 15, 	},
					{	10, 13, 	},
					{	12, 11, 	},
					{	14, 9, 	},
					{	16, 7, 	},
					{	18, 5, 	},
					{	20, 3, 	},
					{	22, 1, 	},
				},			
				BP_SIN_12	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"SIN_TWIST_REV"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	1, 22, 	},
					{	3, 20, 	},
					{	5, 18, 	},
					{	7, 16, 	},
					{	9, 14, 	},
					{	11, 12, 	},
					{	13, 10, 	},
					{	15, 8, 	},
					{	17, 6, 	},
					{	19, 4, 	},
					{	21, 2, 	},
					{	23, 0, 	},
				},			
				BP_SIN_12	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"SIN_TWIST_OUT"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	10, 12, 1, 23, 	},
					{	8, 14, 3, 21, 	},
					{	6, 16, 5, 19, 	},
					{	4, 18, 7, 17, 	},
					{	2, 20, 9, 15, 	},
					{	0, 22, 11, 13, 	},
				},			
				BP_SIN_6	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"SIN_TWIST_IN"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	11, 13, 0, 22, 	},
					{	9, 15, 2, 20, 	},
					{	7, 17, 4, 18, 	},
					{	5, 19, 6, 16, 	},
					{	3, 21, 8, 14, 	},
					{	1, 23, 10, 12, 	},
				},			
				BP_SIN_6	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"SIN__AND__STOP"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	0, 	},
					{	2, 	},
					{	4, 	},
					{	6, 	},
					{	8, 	},
					{	10, 	},
					{	12, 	},
					{	14, 	},
					{	16, 	},
					{	18, 	},
					{	20, 	},
					{	22, 	},
				},			
				BP_SIN_12	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// Block[0]				
				{// LogicalCh[]			
					{	1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 	},
				},			
				BP_ON_HIGH	,	// Bp_Pattern_id	
				false	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"SIN_REV__AND__STOP"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	22, 	},
					{	20, 	},
					{	18, 	},
					{	16, 	},
					{	14, 	},
					{	12, 	},
					{	10, 	},
					{	8, 	},
					{	6, 	},
					{	4, 	},
					{	2, 	},
					{	0, 	},
				},			
				BP_SIN_12	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// Block[0]				
				{// LogicalCh[]			
					{	1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 	},
				},			
				BP_ON_HIGH	,	// Bp_Pattern_id	
				false	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"STOP__AND__SIN"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	1, 	},
					{	3, 	},
					{	5, 	},
					{	7, 	},
					{	9, 	},
					{	11, 	},
					{	13, 	},
					{	15, 	},
					{	17, 	},
					{	19, 	},
					{	21, 	},
					{	23, 	},
				},			
				BP_SIN_12	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// Block[0]				
				{// LogicalCh[]			
					{	0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 	},
				},			
				BP_ON_HIGH	,	// Bp_Pattern_id	
				false	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"STOP__AND__SIN_REV"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	23, 	},
					{	21, 	},
					{	19, 	},
					{	17, 	},
					{	15, 	},
					{	13, 	},
					{	11, 	},
					{	9, 	},
					{	7, 	},
					{	5, 	},
					{	3, 	},
					{	1, 	},
				},			
				BP_SIN_12	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// Block[0]				
				{// LogicalCh[]			
					{	0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 	},
				},			
				BP_ON_HIGH	,	// Bp_Pattern_id	
				false	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"STROBE_1"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 	},
				},			
				BP_STROBE_1	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"STROBE_2"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	0, 2, 4, 6, 8, 10, 13, 15, 17, 19, 21, 23,	},
					{	1, 3, 5, 7, 9, 11, 12, 14, 16, 18, 20, 22,	},
				},			
				BP_STROBE_2	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"STROBE_3"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	0, 2, 4, 6, 9, 11, 13, 15, 16, 18, 20, 22, 	},
					{	1, 3, 5, 7, 8, 10, 12, 14, 17, 19, 21, 23, 	},
				},			
				BP_STROBE_2	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"STROBE_4"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	0, 2, 4, 7, 9, 11, 12, 14, 16, 19, 21, 23, 	},
					{	1, 3, 5, 6, 8, 10, 13, 15, 17, 18, 20, 22, 	},
				},			
				BP_STROBE_2	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"STROBE_6"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	0, 2, 5, 7, 8, 10, 13, 15, 16, 18, 21, 23, 	},
					{	1, 3, 4, 6, 9, 11, 12, 14, 17, 19, 20, 22, 	},
				},			
				BP_STROBE_2	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"STROBE_12"	,				
		0	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	0, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23, 	},
					{	1, 2, 5, 6, 9, 10, 13, 14, 17, 18, 21, 22, 	},
				},			
				BP_STROBE_2	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"CAM_STROBE"	,				
		1	,	// weight			
		{ // Block					
			{// Block[0]				
				{// LogicalCh[]			
					{	0,	},
					{	1,	},
					{	2,	},
					{	3,	},
					{	4,	},
					{	5,	},
					{	6,	},
					{	7,	},
					{	8,	},
					{	9,	},
					{	10,	},
					{	11,	},
					{	12,	},
					{	13,	},
					{	14,	},
					{	15,	},
					{	16,	},
					{	17,	},
					{	18,	},
					{	19,	},
					{	20,	},
					{	21,	},
					{	22,	},
					{	23,	},
				},			
				BP_STROBE_24	,	// Bp_Pattern_id	
				true	,	// b_ColorSync	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
};							
							
const int NUM_GROUPTYPES = sizeof(BlockGrouping) / sizeof(BlockGrouping[0]);							
