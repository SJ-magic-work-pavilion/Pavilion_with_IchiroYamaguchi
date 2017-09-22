/************************************************************
************************************************************/
#include "sj_common.h"

/************************************************************
************************************************************/

/******************************
******************************/
LED_PARAM operator*(const LED_PARAM& org, const double k)
{
	int R = int(org.get_R() * k);
	int G = int(org.get_G() * k);
	int B = int(org.get_B() * k);
	
	LED_PARAM ret(R, G, B);
	return ret;
}

/******************************
******************************/
LED_PARAM operator+(const LED_PARAM& left, const LED_PARAM& right)
{
	int R = left.get_R() + right.get_R();
	int G = left.get_G() + right.get_G();
	int B = left.get_B() + right.get_B();
	
	LED_PARAM ret(R, G, B);
	return ret;
}

/******************************
******************************/
LED_PARAM operator-(const LED_PARAM& left, const LED_PARAM& right)
{
	int R = left.get_R() - right.get_R();
	int G = left.get_G() - right.get_G();
	int B = left.get_B() - right.get_B();
	
	LED_PARAM ret(R, G, B);
	return ret;
}

