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
	ODE("10.7.189.7"),
	ODE("10.7.192.86"),
};
static const int NUM_ODES = sizeof(ode) / sizeof(ode[0]);

/********************
********************/
LED_LIGHT DesignLight[] = {																										
//				ODE id		AddressFrom																		Hardware(Start Address) setting 		
/*	0	*/	LED_LIGHT(	0	,	0	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	1050	,	450	,	0	),	5	),	//	1		
/*	1	*/	LED_LIGHT(	0	,	3	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	1050	,	435	,	0	),	5	),	//	4		
/*	2	*/	LED_LIGHT(	0	,	6	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	990	,	450	,	0	),	5	),	//	7		
/*	3	*/	LED_LIGHT(	0	,	9	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	990	,	435	,	0	),	5	),	//	10		
/*	4	*/	LED_LIGHT(	0	,	12	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	930	,	450	,	0	),	5	),	//	13		
/*	5	*/	LED_LIGHT(	0	,	15	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	930	,	435	,	0	),	5	),	//	16		
/*	6	*/	LED_LIGHT(	0	,	18	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	870	,	450	,	0	),	5	),	//	19		
/*	7	*/	LED_LIGHT(	0	,	21	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	870	,	435	,	0	),	5	),	//	22		
/*	8	*/	LED_LIGHT(	0	,	24	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	810	,	450	,	0	),	5	),	//	25		
/*	9	*/	LED_LIGHT(	0	,	27	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	810	,	435	,	0	),	5	),	//	28		
/*	10	*/	LED_LIGHT(	0	,	30	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	750	,	450	,	0	),	5	),	//	31		
/*	11	*/	LED_LIGHT(	0	,	33	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	750	,	435	,	0	),	5	),	//	34		
/*	12	*/	LED_LIGHT(	0	,	36	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	690	,	450	,	0	),	5	),	//	37		
/*	13	*/	LED_LIGHT(	0	,	39	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	690	,	435	,	0	),	5	),	//	40		
/*	14	*/	LED_LIGHT(	0	,	42	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	630	,	450	,	0	),	5	),	//	43		
/*	15	*/	LED_LIGHT(	0	,	45	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	630	,	435	,	0	),	5	),	//	46		
/*	16	*/	LED_LIGHT(	0	,	48	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	570	,	450	,	0	),	5	),	//	49		
/*	17	*/	LED_LIGHT(	0	,	51	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	570	,	435	,	0	),	5	),	//	52		
/*	18	*/	LED_LIGHT(	0	,	54	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	510	,	450	,	0	),	5	),	//	55		
/*	19	*/	LED_LIGHT(	0	,	57	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	510	,	435	,	0	),	5	),	//	58		
/*	20	*/	LED_LIGHT(	0	,	60	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	450	,	450	,	0	),	5	),	//	61		
/*	21	*/	LED_LIGHT(	0	,	63	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	450	,	435	,	0	),	5	),	//	64		
/*	22	*/	LED_LIGHT(	0	,	66	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	390	,	450	,	0	),	5	),	//	67		
/*	23	*/	LED_LIGHT(	0	,	69	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	390	,	435	,	0	),	5	),	//	70		
};																										
																										
const int NUM_DESIGN_LEDS = sizeof(DesignLight) / sizeof(DesignLight[0]);																										
																										
/********************																										
********************/																										
LED_LIGHT SafetyLight[] = {																										
//				ODE id		AddressFrom																		Hardware(Start Address) setting 		
/*	0	*/	LED_LIGHT(	0	,	72	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	1050	,	400	,	0	),	5	),	//	73		
/*	1	*/	LED_LIGHT(	0	,	75	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	1050	,	390	,	0	),	5	),	//	76		
/*	2	*/	LED_LIGHT(	0	,	78	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	930	,	400	,	0	),	5	),	//	79		
/*	3	*/	LED_LIGHT(	0	,	81	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	930	,	390	,	0	),	5	),	//	82		
/*	4	*/	LED_LIGHT(	0	,	84	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	810	,	400	,	0	),	5	),	//	85		
/*	5	*/	LED_LIGHT(	0	,	87	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	810	,	390	,	0	),	5	),	//	88		
/*	6	*/	LED_LIGHT(	0	,	90	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	690	,	400	,	0	),	5	),	//	91		
/*	7	*/	LED_LIGHT(	0	,	93	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	690	,	390	,	0	),	5	),	//	94		
/*	8	*/	LED_LIGHT(	0	,	96	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	570	,	400	,	0	),	5	),	//	97		
/*	9	*/	LED_LIGHT(	0	,	99	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	570	,	390	,	0	),	5	),	//	100		
/*	10	*/	LED_LIGHT(	0	,	102	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_RESTAURANT	,	true	,	ofPoint(	450	,	400	,	0	),	5	),	//	103		
/*	11	*/	LED_LIGHT(	0	,	105	,	LED_DEVICE_TYPE_0	,	COLOR_FROM_ENTRANCE	,	true	,	ofPoint(	450	,	390	,	0	),	5	),	//	106		
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
	for(int i = 0; i < NUM_ODES; i++){
		artnet.sendDmx(ode[i].get_IP(), ode[i].universe, SIZE_DMX_UNIVERSE);
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
		LED_TEST& LedTest = test_DesignLight;
		if(LedRole == 0){ // SafetyLight
			num_Leds = NUM_SAFETY_LEDS;
			LedLights = SafetyLight;
			LedTest = test_DesignLight;

		}else{ // DesignLight
			num_Leds = NUM_DESIGN_LEDS;
			LedLights = DesignLight;
			LedTest = test_SafetyLight;
			
		}
		
		/********************
		********************/
		for(int i = 0; i < num_Leds; i++){
			switch(LedLights[i].LedDeviceType){
				case LED_DEVICE_TYPE_0:
					if( (LedTest.LedId == -1) || (i == LedTest.LedId) ){
						/********************
						********************/
						int R = LedTest.LedParam.get_R() * (dimmer / 255);
						if(255 < R)	R = 255;
						if(R < 0)	R = 0;
	
						int G = LedTest.LedParam.get_G() * (dimmer / 255);
						if(255 < G)	G = 255;
						if(G < 0)	G = 0;
	
						int B = LedTest.LedParam.get_B() * (dimmer / 255);
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
	for(int i = 0; i < NUM_ODES; i++){
		artnet.sendDmx(ode[i].get_IP(), ode[i].universe, SIZE_DMX_UNIVERSE);
	}
}




