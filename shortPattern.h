/************************************************************
************************************************************/
#pragma once

#include "sj_common.h"

/************************************************************
************************************************************/
class SHORT_PATTERN{
private:
	enum{
		MAX_PROGRESS = 100,
	};
	
	static const double Lev_Flow_L;
	static const double Lev_Flash_L;
	
public:
	static void SpLev_test();
	
	static double Sp_FlowOn(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE);
	static double Sp_FlowOff(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE);
	static double Sp_cos(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE);
	static double Sp_On_High(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE);
	static double Sp_cos_forFlash(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE);
	static double Sp_Flash__1_1(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE);
	static double Sp_Flash__1_2(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE);
	static double Sp_Flash__2_2(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE);
};


/************************************************************
************************************************************/
typedef double (*FUNC_SP)(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE);
