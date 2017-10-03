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
};

class FADER{
private:
	const double tan;
	
public:
	double k;
	
	FADER(const double dt) // dtでkが0->1に変化.
	: tan(1.0/dt), k(0)
	{
	}
	
	void update_Up(float dt)
	{
		k = k + tan * dt;
		if(1.0 < k) k = 1.0;
	}
	
	void update_Down(float dt)
	{
		k = k - tan * dt;
		if(k < 0) k = 0;
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
		STATE_RUN,
		STATE_ECHO,
		STATE_CALM,
		
		NUM__STATES,
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
	
	int LedNumSync;
	
	/********************
	********************/
	float LPF_Direct_NumLeds_ThreshSec;
	float LPF_Direct_NumWaves_ThreshSec;
	
	/********************
	********************/
	bool b_StateChart;
	STATE State;
	
	DESIGN_CATEGORY DesignCategory;
	
	int BlockGrouping_id;
	int* Weight_BlockGrouping_id;
	
	/* */
	FADER Fader_DesignLight;
	FADER Fader_SafetyLight;
	
	FADER Fader_CalmColor;
	LED_PARAM CalmColor_pre[NUM_COLOR_SURFACES];
	
	float t_calm_From;
	
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
	void StateChart(double vol, double Vol_thresh_L, double Vol_thresh_H);
	int Dice_index(int *Weight, int NUM);
	
	void Transition__to_WAIT();
	void Transition__to_RUN();
	void Dice_DesignCategory();
	void Dice_BlockGrouping_id();
	void Dice_LedId_NumLeds_Sync();
	void Dice_ColorCombination();
	
	double get_FilterOut(double Last, double Raw, double thresh_sec, double dt);
	
	void update_SafetyLight();
	void update_DesignLight(double vol, double Vol_Map_L, double Vol_Map_H);
	void update_DesignLight_calm();
	void update_DesignLight_Run_Echo(double vol, double Vol_Map_L, double Vol_Map_H);
	void update_DesignLight_Run_Echo__LevSync();
	void update_DesignLight_Run_Echo__AllOn();
	void update_DesignLight_Run_Echo__NumLeds();
	void update_DesignLight_Run_Echo__Pattern(double vol, double Vol_Map_L, double Vol_Map_H);
	
	double calProgress(double t_now, double t_From, double Duration, double Speed);
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
	void update(double vol, double Vol_thresh_L, double Vol_thresh_H, double Vol_Map_L, double Vol_Map_H);
	void draw(int test_DesignLight_id, LED_PARAM& test_DesignLight_Color, int test_SafetyLight_id, LED_PARAM& test_SafetyLight_Color);
	void exit();
	
	void Escape_StateChart();
	void Start_StateChart();
	
	void update_GuiParam(float _LPF_Direct_NumLeds_ThreshSec, float _LPF_Direct_NumWaves_ThreshSec);
};

