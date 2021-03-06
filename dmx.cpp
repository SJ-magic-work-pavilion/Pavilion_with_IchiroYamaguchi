/************************************************************
************************************************************/
#include "dmx.h"

/************************************************************
************************************************************/
class ODE{
private:
	char ch_IP[BUF_SIZE];
	
public:
	unsigned char universe[SIZE_DMX_UNIVERSE];
	
	ODE(const char* _ch_IP)
	{
		strcpy(ch_IP, _ch_IP);
		
		for(int i = 0; i < SIZE_DMX_UNIVERSE; i++){
			universe[i] = 0;
		}
	}
	const char* get_IP()
	{
		return ch_IP;
	}
};

/************************************************************
param
************************************************************/
/********************
********************/
static ODE ode[] = {
	ODE("10.7.196.107"),
};
static const int NUM_ODES = sizeof(ode) / sizeof(ode[0]);

/********************
********************/
LED_LIGHT DesignLight[] = {																										
//				ODE id		AddressFrom																		Hardware(Start Address) setting 		
/*	0	*/	LED_LIGHT(	0	,	0	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	1200	,	360	,	0	),	7	),	//	1		
/*	1	*/	LED_LIGHT(	0	,	3	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	1200	,	340	,	0	),	7	),	//	4		
/*	2	*/	LED_LIGHT(	0	,	6	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	1135	,	360	,	0	),	7	),	//	7		
/*	3	*/	LED_LIGHT(	0	,	9	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	1135	,	340	,	0	),	7	),	//	10		
/*	4	*/	LED_LIGHT(	0	,	12	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	1070	,	360	,	0	),	7	),	//	13		
/*	5	*/	LED_LIGHT(	0	,	15	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	1070	,	340	,	0	),	7	),	//	16		
/*	6	*/	LED_LIGHT(	0	,	18	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	1005	,	360	,	0	),	7	),	//	19		
/*	7	*/	LED_LIGHT(	0	,	21	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	1005	,	340	,	0	),	7	),	//	22		
/*	8	*/	LED_LIGHT(	0	,	24	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	940	,	360	,	0	),	7	),	//	25		
/*	9	*/	LED_LIGHT(	0	,	27	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	940	,	340	,	0	),	7	),	//	28		
/*	10	*/	LED_LIGHT(	0	,	30	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	875	,	360	,	0	),	7	),	//	31		
/*	11	*/	LED_LIGHT(	0	,	33	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	875	,	340	,	0	),	7	),	//	34		
/*	12	*/	LED_LIGHT(	0	,	36	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	810	,	360	,	0	),	7	),	//	37		
/*	13	*/	LED_LIGHT(	0	,	39	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	810	,	340	,	0	),	7	),	//	40		
/*	14	*/	LED_LIGHT(	0	,	42	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	745	,	360	,	0	),	7	),	//	43		
/*	15	*/	LED_LIGHT(	0	,	45	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	745	,	340	,	0	),	7	),	//	46		
/*	16	*/	LED_LIGHT(	0	,	48	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	680	,	360	,	0	),	7	),	//	49		
/*	17	*/	LED_LIGHT(	0	,	51	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	680	,	340	,	0	),	7	),	//	52		
/*	18	*/	LED_LIGHT(	0	,	54	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	615	,	360	,	0	),	7	),	//	55		
/*	19	*/	LED_LIGHT(	0	,	57	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	615	,	340	,	0	),	7	),	//	58		
/*	20	*/	LED_LIGHT(	0	,	60	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	550	,	360	,	0	),	7	),	//	61		
/*	21	*/	LED_LIGHT(	0	,	63	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	550	,	340	,	0	),	7	),	//	64		
/*	22	*/	LED_LIGHT(	0	,	66	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	485	,	360	,	0	),	7	),	//	67		
/*	23	*/	LED_LIGHT(	0	,	69	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	485	,	340	,	0	),	7	),	//	70		
};																										
																										
const int NUM_DESIGN_LEDS = sizeof(DesignLight) / sizeof(DesignLight[0]);																										
																										
/********************																										
********************/																										
LED_LIGHT SafetyLight[] = {																										
//				ODE id		AddressFrom																		Hardware(Start Address) setting 		
/*	0	*/	LED_LIGHT(	0	,	72	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	false	,	ofPoint(	1200	,	290	,	0	),	7	),	//	73		
/*	1	*/	LED_LIGHT(	0	,	75	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	false	,	ofPoint(	1190	,	290	,	0	),	7	),	//	76		
/*	2	*/	LED_LIGHT(	0	,	78	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	false	,	ofPoint(	1070	,	290	,	0	),	7	),	//	79		
/*	3	*/	LED_LIGHT(	0	,	81	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	false	,	ofPoint(	1060	,	290	,	0	),	7	),	//	82		
/*	4	*/	LED_LIGHT(	0	,	84	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	false	,	ofPoint(	940	,	290	,	0	),	7	),	//	85		
/*	5	*/	LED_LIGHT(	0	,	87	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	false	,	ofPoint(	930	,	290	,	0	),	7	),	//	88		
/*	6	*/	LED_LIGHT(	0	,	90	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	false	,	ofPoint(	810	,	290	,	0	),	7	),	//	91		
/*	7	*/	LED_LIGHT(	0	,	93	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	false	,	ofPoint(	800	,	290	,	0	),	7	),	//	94		
/*	8	*/	LED_LIGHT(	0	,	96	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	false	,	ofPoint(	680	,	290	,	0	),	7	),	//	97		
/*	9	*/	LED_LIGHT(	0	,	99	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	false	,	ofPoint(	670	,	290	,	0	),	7	),	//	100		
/*	10	*/	LED_LIGHT(	0	,	102	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	false	,	ofPoint(	550	,	290	,	0	),	7	),	//	103		
/*	11	*/	LED_LIGHT(	0	,	105	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	false	,	ofPoint(	540	,	290	,	0	),	7	),	//	106		
};																										
																										
const int NUM_SAFETY_LEDS = sizeof(SafetyLight) / sizeof(SafetyLight[0]);																										


/********************
********************/
LED_TEST test_DesignLight;
LED_TEST test_SafetyLight;


/************************************************************
function
************************************************************/

/******************************
******************************/
DMX::DMX()
{
}

/******************************
******************************/
DMX::~DMX()
{
	Send_AllZero_to_AllOde();
}

/******************************
******************************/
void DMX::exit()
{
}

/******************************
******************************/
void DMX::setup()
{
	/********************
	********************/
	//at first you must specify the Ip address of this machine
	//make sure the firewall is deactivated at this point
	artnet.setup("10.0.0.2");
}

/******************************
******************************/
void DMX::Send_AllZero_to_AllOde()
{
	for(int i = 0; i < NUM_ODES; i++){
		for(int j = 0; j < SIZE_DMX_UNIVERSE; j++){
			ode[i].universe[j] = 0;
		}
		
		artnet.sendDmx(ode[i].get_IP(), ode[i].universe, SIZE_DMX_UNIVERSE);
	}
}


/******************************
param
	dimmer	:0 - 255
******************************/
void DMX::draw(double dimmer)
{
	/********************
	********************/
	for(int LedRole = 0; LedRole < 2; LedRole++){
		/********************
		********************/
		int num_Leds;
		LED_LIGHT* LedLights;
		if(LedRole == 0){ // SafetyLight
			num_Leds = NUM_SAFETY_LEDS;
			LedLights = SafetyLight;

		}else{ // DesignLight
			num_Leds = NUM_DESIGN_LEDS;
			LedLights = DesignLight;
			
		}
		/********************
		********************/
		for(int i = 0; i < num_Leds; i++){
			switch(LedLights[i].LedDeviceType){
				case LED_DEVICE_TYPE_0:
					/********************
					********************/
					int R = LedLights[i].LedParam.get_R() * (dimmer / 255);
					if(255 < R)	R = 255;
					if(R < 0)	R = 0;
	
					int G = LedLights[i].LedParam.get_G() * (dimmer / 255);
					if(255 < G)	G = 255;
					if(G < 0)	G = 0;
	
					int B = LedLights[i].LedParam.get_B() * (dimmer / 255);
					if(255 < B)	B = 255;
					if(B < 0)	B = 0;
					
					/********************
					********************/
					ode[ LedLights[i].ODE_id ].universe[ LedLights[i].AddressFrom + 0 ] = (unsigned char)R;
					ode[ LedLights[i].ODE_id ].universe[ LedLights[i].AddressFrom + 1 ] = (unsigned char)G;
					ode[ LedLights[i].ODE_id ].universe[ LedLights[i].AddressFrom + 2 ] = (unsigned char)B;
					
					break;
			}
			
			/********************
			********************/
			LedLights[i].LedSimulation.draw();
		}
	}

	/********************
	********************/
	if(IsEnable_Dmx()){
		for(int i = 0; i < NUM_ODES; i++){
			artnet.sendDmx(ode[i].get_IP(), ode[i].universe, SIZE_DMX_UNIVERSE);
		}
	}
}

/******************************
******************************/
void DMX::draw_test(double dimmer)
{
	/********************
	********************/
	for(int LedRole = 0; LedRole < 2; LedRole++){
		/********************
		********************/
		int num_Leds;
		LED_LIGHT* LedLights;
		LED_TEST* LedTest;
		if(LedRole == 0){ // SafetyLight
			num_Leds = NUM_SAFETY_LEDS;
			LedLights = SafetyLight;
			LedTest = &test_SafetyLight;

		}else{ // DesignLight
			num_Leds = NUM_DESIGN_LEDS;
			LedLights = DesignLight;
			LedTest = &test_DesignLight;
			
		}
		
		/********************
		********************/
		for(int i = 0; i < num_Leds; i++){
			switch(LedLights[i].LedDeviceType){
				case LED_DEVICE_TYPE_0:
					if( (LedTest->LedId == -1) || (i == LedTest->LedId) ){
						/********************
						********************/
						int R = LedTest->LedParam.get_R() * (dimmer / 255);
						if(255 < R)	R = 255;
						if(R < 0)	R = 0;
	
						int G = LedTest->LedParam.get_G() * (dimmer / 255);
						if(255 < G)	G = 255;
						if(G < 0)	G = 0;
	
						int B = LedTest->LedParam.get_B() * (dimmer / 255);
						if(255 < B)	B = 255;
						if(B < 0)	B = 0;
						
						/********************
						********************/
						ode[ LedLights[i].ODE_id ].universe[ LedLights[i].AddressFrom + 0 ] = (unsigned char)R;
						ode[ LedLights[i].ODE_id ].universe[ LedLights[i].AddressFrom + 1 ] = (unsigned char)G;
						ode[ LedLights[i].ODE_id ].universe[ LedLights[i].AddressFrom + 2 ] = (unsigned char)B;
						
						LedLights[i].LedParam = LED_PARAM(R, G, B); // 画面上でのSimulationに反映するため.
						
					}else{
						ode[ LedLights[i].ODE_id ].universe[ LedLights[i].AddressFrom + 0 ] = 0;
						ode[ LedLights[i].ODE_id ].universe[ LedLights[i].AddressFrom + 1 ] = 0;
						ode[ LedLights[i].ODE_id ].universe[ LedLights[i].AddressFrom + 2 ] = 0;
						
						LedLights[i].LedParam = LED_PARAM(0, 0, 0); // 画面上でのSimulationに反映するため.
					}
					
					
					break;
			}
			
			/********************
			********************/
			LedLights[i].LedSimulation.draw();
		}
	}
	
	/********************
	********************/
	if(IsEnable_Dmx()){
		for(int i = 0; i < NUM_ODES; i++){
			artnet.sendDmx(ode[i].get_IP(), ode[i].universe, SIZE_DMX_UNIVERSE);
		}
	}
}




