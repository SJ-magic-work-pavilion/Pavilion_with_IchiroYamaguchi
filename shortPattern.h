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
	
public:
	static void SpLev_test();
	
	static double Sp_FlowOn(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE);
	static double Sp_FlowOff(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE);
	static double Sp_cos(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE);
};


/************************************************************
************************************************************/
typedef double (*FUNC_SP)(const double Progress, const int NUM_CHS, const int N, const double NUM_WAVES_IN_SPACE);
