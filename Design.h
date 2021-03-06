/************************************************************
************************************************************/
#pragma once

#include <new> // placement new

#include "ofMain.h"

#include "sj_common.h"
#include "shortPattern.h"
#include "BlockPattern.h"
#include "BlockGroup.h"
#include "dmx.h"

/************************************************************
************************************************************/

/**************************************************
**************************************************/
struct COLOR_COMBINATION{
	/****************************************
	****************************************/
	/* */
	const LED_PARAM Color_calm;

	const LED_PARAM Color_0;
	const LED_PARAM Color_05;
	const LED_PARAM Color_1;
	
	LED_PARAM maxColor;
	
	/* */
	const LED_PARAM Color_SafetyLight;
	
	/****************************************
	****************************************/
	COLOR_COMBINATION() {}
	
	COLOR_COMBINATION(const double _calm_ratio, const LED_PARAM _0, const LED_PARAM _05, const LED_PARAM _1, const LED_PARAM _Color_SafetyLight)
	: Color_calm(_0 * _calm_ratio), Color_0(_0), Color_05(_05), Color_1(_1), Color_SafetyLight(_Color_SafetyLight)
	{
	}
	
	COLOR_COMBINATION(const LED_PARAM _calm, const LED_PARAM _0, const LED_PARAM _05, const LED_PARAM _1, const LED_PARAM _Color_SafetyLight)
	: Color_calm(_calm), Color_0(_0), Color_05(_05), Color_1(_1), Color_SafetyLight(_Color_SafetyLight)
	{
	}
};

struct COLOR_COMBINATION_SET{
	string Name;
	
	int Weight;
	COLOR_COMBINATION Combination[NUM_COLOR_SURFACES];
	
	COLOR_COMBINATION_SET(	string _Name,
							int _weight,
							double _calm0, LED_PARAM _0_0, LED_PARAM _0_05, LED_PARAM _0_1, LED_PARAM _Color_SafetyLight_0,
							double _calm1, LED_PARAM _1_0, LED_PARAM _1_05, LED_PARAM _1_1, LED_PARAM _Color_SafetyLight_1
							)
	: Weight(_weight)
	{
		Name = _Name;
		
		new(&Combination[COLOR_FROM_RESTAURANT]) COLOR_COMBINATION(_calm0, _0_0, _0_05, _0_1, _Color_SafetyLight_0);
		new(&Combination[COLOR_FROM_ENTRANCE]) COLOR_COMBINATION(_calm1, _1_0, _1_05, _1_1, _Color_SafetyLight_1);
	}
	
	COLOR_COMBINATION_SET(	string _Name,
							int _weight,
							LED_PARAM _calm0, LED_PARAM _0_0, LED_PARAM _0_05, LED_PARAM _0_1, LED_PARAM _Color_SafetyLight_0,
							LED_PARAM _calm1, LED_PARAM _1_0, LED_PARAM _1_05, LED_PARAM _1_1, LED_PARAM _Color_SafetyLight_1
							)
	: Weight(_weight)
	{
		Name = _Name;
		
		new(&Combination[COLOR_FROM_RESTAURANT]) COLOR_COMBINATION(_calm0, _0_0, _0_05, _0_1, _Color_SafetyLight_0);
		new(&Combination[COLOR_FROM_ENTRANCE]) COLOR_COMBINATION(_calm1, _1_0, _1_05, _1_1, _Color_SafetyLight_1);
	}
};

/**************************************************
**************************************************/
struct STROBE_COLOR_COMBINATION_SET{
	int Weight;
	LED_PARAM Color[NUM_COLOR_SURFACES];
	
	STROBE_COLOR_COMBINATION_SET( int _weight, const LED_PARAM Col_Restaurant, LED_PARAM Col_Entrance )
	: Weight(_weight)
	{
		new(&Color[COLOR_FROM_RESTAURANT])	LED_PARAM(Col_Restaurant);
		new(&Color[COLOR_FROM_ENTRANCE])	LED_PARAM(Col_Entrance);
	}
};

/**************************************************
**************************************************/
class FADER{
private:
	double tan;
	bool b_immediate;
	
public:
	double k;
	
	FADER(const double dt) // dtでkが0->1に変化.
	: k(0)
	{
		set(dt, true);
	}
	
	void set(const double dt, bool b_clear)
	{
		if(b_clear) k = 0;
		
		if(0 < dt){
			tan = 1.0/dt;
			b_immediate = false;
		}else{
			tan = 0;
			b_immediate = true;
		}
	}
	
	void update_Up(float dt)
	{
		if(b_immediate){
			k = 1.0;
		}else{
			k = k + tan * dt;
			if(1.0 < k) k = 1.0;
		}
	}
	
	void update_Down(float dt)
	{
		if(b_immediate){
			k = 0;
		}else{
			k = k - tan * dt;
			if(k < 0) k = 0;
		}
	}
};

/**************************************************
**************************************************/
class DESIGN_MANAGER{
private:
	/****************************************
	****************************************/
	enum STATE{
		STATE_ESCAPE,
		STATE_WAIT,
		STATE_RUN__VOLSYNC,
		STATE_RUN__PATTERN,
		STATE_ECHO,
		STATE_CALM,
		
		NUM__STATES,
	};
	enum SUB_STATE_RUN_PATTERN{
		SUB_STATE_RUN_PATTERN__FADE_UP,
		SUB_STATE_RUN_PATTERN__FADE_DOWN,
	};
	
	enum DESIGN_CATEGORY{
		DESIGN__LEV_MIC_SYNC,
		DESIGN__PATTERN,
		DESIGN__ALL_ON,
		DESIGN__NUM_LEDS,
		
		NUM__DESIGN_CATEGORIES,
	};
	
	/****************************************
	****************************************/
	/********************
	********************/
#ifdef LOG_DIRECT_FILTER
	FILE* fp_debug;
#endif

	/********************
	********************/
	double LevSync;
	double SpeedSync;
	
	static COLOR_COMBINATION_SET ColorCombination[];
	int ColorCombination_id;
	static int NUM_COLOR_COMBINATIONS;
	int* Weight_ColorCombination_id;
	
	static STROBE_COLOR_COMBINATION_SET StrobeColorCombination[];
	int StrobeColorCombination_id;
	static int NUM_STROBE_COLOR_COMBINATIONS;
	int* Weight_StrobeColorCombination_id;
	
	double LedNumSync;
	
	/********************
	********************/
	float LPF_Direct_NumLeds_ThreshSec;
	float LPF_Direct_NumWaves_ThreshSec;
	
	/********************
	********************/
	bool b_StateChart;
	STATE State;
	SUB_STATE_RUN_PATTERN SubState_RunPattern;
	
	DESIGN_CATEGORY DesignCategory;
	bool b_DesignPattern;
	
	int BlockGrouping_id;
	int* Weight_BlockGrouping_id;
	
	/* */
	FADER Fader_DesignLight;
	FADER Fader_SafetyLight;
	
	LED_PARAM CalmColor_max[NUM_COLOR_SURFACES];
	
	float t_calm_From;
	float t_Pattern_From;
	
	float t_now;
	float t_LastINT;
	
	vector<int> LedId_ExchangeTable_NumSync;
	
	
	DMX& dmx;
	
	
	/****************************************
	****************************************/
	/********************
	singleton
	********************/
	DESIGN_MANAGER();
	~DESIGN_MANAGER();
	DESIGN_MANAGER(const DESIGN_MANAGER&);				// Copy constructor. no define. 
	DESIGN_MANAGER& operator=(const DESIGN_MANAGER&);	// コピー代入演算子. no define.
	
	/********************
	********************/
	void fix_sync_maxColor(double vol, double Vol_Map_L, double Vol_Map_H);
	void StateChart(double vol, double Vol_thresh_L, double Vol_thresh_H, double Vol_thresh_P_L, double Vol_thresh_P_H);
	int Dice_index(int *Weight, int NUM);
	
	void Transition__to_WAIT();
	void Transition__to_RUN_VolSync();
	void Transition__to_RUN_Pattern();
	void Dice_DesignCategory();
	void Dice_BlockGrouping_id();
	void Dice_LogicalId(BLOCK* block);
	void Dice_LedId_NumLeds_Sync();
	void Dice_ColorCombination();
	
	double get_FilterOut(double Last, double Raw, double thresh_sec, double dt);
	
	void update_SafetyLight();
	void update_DesignLight(double vol, double Vol_Map_L, double Vol_Map_H);
	void update_DesignLight_calm();
	void update_DesignLight_wait();
	void update_DesignLight_Run_Echo(double vol, double Vol_Map_L, double Vol_Map_H);
	void update_DesignLight_Run_Echo__LevSync();
	void update_DesignLight_Run_Echo__AllOn();
	void update_DesignLight_Run_Echo__NumLeds();
	void update_DesignLight_Run_Echo__Pattern(double vol, double Vol_Map_L, double Vol_Map_H);
	
	void calProgress(BLOCK& Block, double t_now, double Duration);
	void draw_Infos();
	void draw_ColorInfos();
	
public:
	/****************************************
	****************************************/
	static DESIGN_MANAGER& getInstance(){
		static DESIGN_MANAGER inst;
		return inst;
	}
	
	
	void setup();
	void update(double vol, double Vol_thresh_L, double Vol_thresh_H, double Vol_thresh_P_L, double Vol_thresh_P_H, double Vol_Map_L, double Vol_Map_H);
	void draw(int test_DesignLight_id, LED_PARAM& test_DesignLight_Color, int test_SafetyLight_id, LED_PARAM& test_SafetyLight_Color);
	void exit();
	
	void Escape_StateChart();
	void Start_StateChart();
	
	void update_GuiParam(float _LPF_Direct_NumLeds_ThreshSec, float _LPF_Direct_NumWaves_ThreshSec);
};

