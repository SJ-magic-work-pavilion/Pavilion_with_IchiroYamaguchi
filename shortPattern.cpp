/************************************************************
************************************************************/
#include "ofMain.h"

#include "shortPattern.h"

/************************************************************
************************************************************/
static FUNC_SP pFunc[] = {
	SHORT_PATTERN::Sp_FlowOn,
	SHORT_PATTERN::Sp_FlowOff,
	SHORT_PATTERN::Sp_cos,
};
static const int Num_ShortPatterns = sizeof(pFunc) / sizeof(pFunc[0]);


/************************************************************
************************************************************/

/******************************
******************************/
void SHORT_PATTERN::SpLev_test()
{
	/********************
	e.g.
	********************/
	const int NUM_CHS = 10;
	const double NUM_WAVES_IN_SPACE = 2;
	
	/********************
	********************/
	for(int i = 0; i < Num_ShortPatterns; i++){
		for(int j = 0; j < NUM_CHS; j++){
			char buf[1000];
			sprintf(buf, "../../../Sp_%d_%d.csv", i, j);
			
			FILE* fp;
			fp = fopen(buf, "w");
			if(fp == NULL){
				printf("File open Error\n");
				std::exit(1);
			}
			
			const double offset = 20;
			for(int k = -offset; k < MAX_PROGRESS + offset; k += 1){
				double val = pFunc[i](k, NUM_CHS, j, NUM_WAVES_IN_SPACE);
				fprintf(fp, "%d,%f\n", k, val);
			}
			
			fclose(fp);
		}
	}
}

/******************************
******************************/
double SHORT_PATTERN::Sp_FlowOn(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE)
{
	/********************
	********************/
	if(NUM_CHS <= N) { ERROR_MSG(); std::exit(1); }
	
	/********************
	********************/
	const double PROGRESS_STEP = MAX_PROGRESS / NUM_CHS;
	const double ProgressFrom	= PROGRESS_STEP * N;
	
	if(Progress < 0){
		return 0;
	}else{
		if(ProgressFrom <= Progress)	return 1;
		else							return 0;
	}
}

/******************************
******************************/
double SHORT_PATTERN::Sp_FlowOff(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE)
{
	/********************
	********************/
	if(NUM_CHS <= N) { ERROR_MSG(); std::exit(1); }
	
	/********************
	********************/
	const double PROGRESS_STEP = MAX_PROGRESS / NUM_CHS;
	const double ProgressFrom	= PROGRESS_STEP * N;
	
	if(Progress < 0){
		return 1;
	}else{
		if(ProgressFrom <= Progress)	return 0;
		else							return 1;
	}
}

/******************************
******************************/
double SHORT_PATTERN::Sp_cos(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE)
{
	/********************
	********************/
	if(NUM_CHS <= N) { ERROR_MSG(); std::exit(1); }
	
	/********************
	********************/
	const double OFS_STEP = MAX_PROGRESS * NUM_WAVES_IN_SPACE / NUM_CHS;
	const double phase_percent = OFS_STEP * N;
	
	return 0.5 * cos( TWO_PI * (Progress + phase_percent) / MAX_PROGRESS ) + 0.5;
}



