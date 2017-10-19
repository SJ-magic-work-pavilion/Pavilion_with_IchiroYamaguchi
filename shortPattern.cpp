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
	SHORT_PATTERN::Sp_On_High,
	SHORT_PATTERN::Sp_cos_forFlash,
	SHORT_PATTERN::Sp_Flash__1_1,
	SHORT_PATTERN::Sp_Flash__1_2,
	SHORT_PATTERN::Sp_Flash__2_2,
};
static const int Num_ShortPatterns = sizeof(pFunc) / sizeof(pFunc[0]);


const double SHORT_PATTERN::Lev_Flow_L = 0.02;
const double SHORT_PATTERN::Lev_Flash_L = 0.03;

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
		return Lev_Flow_L;
	}else{
		if(ProgressFrom <= Progress)	return 1;
		else							return Lev_Flow_L;
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
		if(ProgressFrom <= Progress)	return Lev_Flow_L;
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
	
	// return 0.5 * cos( TWO_PI * (Progress + phase_percent) / MAX_PROGRESS ) + 0.5; // Entrance -> 店
	return 0.5 * cos( TWO_PI * (Progress - phase_percent) / MAX_PROGRESS ) + 0.5; // 店 -> Entrance
}

/******************************
******************************/
double SHORT_PATTERN::Sp_On_High(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE)
{
	/********************
	********************/
	if(NUM_CHS <= N) { ERROR_MSG(); std::exit(1); }
	
	/********************
	********************/
	return 1;
}

/******************************
******************************/
double SHORT_PATTERN::Sp_cos_forFlash(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE)
{
	/********************
	********************/
	if(NUM_CHS <= N) { ERROR_MSG(); std::exit(1); }
	
	/********************
	********************/
	// const double PI = 3.14159265398979;
	const double diff = 20;
	double ofs = diff / NUM_CHS * N;
	
	double Amp = (1 - Lev_Flash_L) / 2;
	double center = Lev_Flash_L + Amp;
	
	if(Progress < ofs){
		return Lev_Flash_L;
	}else if(100 - diff + ofs < Progress){
		return Lev_Flash_L;
	}else{
		return center + Amp * cos( 2 * PI * (Progress - ofs) / (2 * (100 - diff)) );
	}
}

/******************************
******************************/
double SHORT_PATTERN::Sp_Flash__1_1(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE)
{
	/********************
	********************/
	if(NUM_CHS <= N) { ERROR_MSG(); std::exit(1); }
	
	/********************
	********************/
	const double tan = -(1.0 - Lev_Flash_L)/MAX_PROGRESS;
	
	if( (Progress < 0) || (MAX_PROGRESS < Progress) ){
		return Lev_Flash_L;
	}else{
		return 1 + tan * Progress;
	}
}

/******************************
******************************/
double SHORT_PATTERN::Sp_Flash__1_2(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE)
{
	/********************
	********************/
	if(NUM_CHS <= N) { ERROR_MSG(); std::exit(1); }
	
	/********************
	********************/
	if(N < NUM_CHS/2){
		const double tan = -(1.0 - Lev_Flash_L)/MAX_PROGRESS;
		
		if( (Progress < 0) || (MAX_PROGRESS < Progress) ){
			return Lev_Flash_L;
		}else{
			return 1 + tan * Progress;
		}
	}else{
	
		return Lev_Flash_L;
	}
}

/******************************
******************************/
double SHORT_PATTERN::Sp_Flash__2_2(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE)
{
	/********************
	********************/
	if(NUM_CHS <= N) { ERROR_MSG(); std::exit(1); }
	
	/********************
	********************/
	if(NUM_CHS/2 <= N){
		const double tan = -(1.0 - Lev_Flash_L)/MAX_PROGRESS;
		
		if( (Progress < 0) || (MAX_PROGRESS < Progress) ){
			return Lev_Flash_L;
		}else{
			return 1 + tan * Progress;
		}
	}else{
	
		return Lev_Flash_L;
	}
}

