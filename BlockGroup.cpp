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
		1	,	// weight			
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
				BP_FLOW	,	// Bp_Pattern_id	
			},				
			{// period				
				{// LogicalCh[]			
				},			
				BP_PERIOD	,	// Bp_Pattern_id	
			},				
		},					
	},						
	{	"SIN"	,				
		1	,	// weight			
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
				BP_SIN	,	// Bp_Pattern_id	
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
