/************************************************************
************************************************************/
#include "sj_common.h"

/************************************************************
************************************************************/
BOOT_MODE BootMode = BOOT_MODE__STANDING;
int argin_DesignCategory = -1;
int argin_BlockGrouping_id = -1;

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

/******************************
******************************/
bool IsEnable_LedManager()
{
	if(BootMode != BOOT_MODE__MIC_TEST){
		return true;
	}else{
		return false;
	}
}

/******************************
******************************/
bool IsEnable_GuiSimulation()
{
	if( (BootMode == BOOT_MODE__GUI_SIMULATION) || (BootMode == BOOT_MODE__LED_SIMULATION) || (BootMode == BOOT_MODE__PLAY_RECED) ){
		return true;
	}else{
		return false;
	}
}

/******************************
******************************/
bool IsEnable_Dmx()
{
	if( (BootMode == BOOT_MODE__STANDING) || (BootMode == BOOT_MODE__LED_SIMULATION) || (BootMode == BOOT_MODE__PLAY_RECED) ){
		return true;
	}else{
		return false;
	}
}

/******************************
******************************/
bool IsEnable_RecMic()
{
	if( BootMode == BOOT_MODE__MIC_TEST ){
		return true;
	}else{
		return false;
	}
}

/******************************
******************************/
bool IsEnable_PlayReced()
{
	if( BootMode == BOOT_MODE__PLAY_RECED ){
		return true;
	}else{
		return false;
	}
}
