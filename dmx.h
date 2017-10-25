/************************************************************
************************************************************/
#pragma once

#include "ofMain.h"
#include "ofxArtnet.h"

#include "sj_common.h"

/************************************************************
************************************************************/
enum{
	SIZE_DMX_UNIVERSE = 512,
};
enum LED_DEVICE_TYPE{
	LED_DEVICE_TYPE_0,
};

/************************************************************
class
************************************************************/
class LED_SIMULATION{
private:
	bool b_Simulate;
	ofPoint pos;
	const int radius;
	LED_PARAM* LedParam;
	
public:	
	LED_SIMULATION(bool _b_Simulate, ofPoint _pos, int _radius, LED_PARAM* _LedParam)
	: b_Simulate(_b_Simulate), pos(_pos), radius(_radius), LedParam(_LedParam)
	{
	}
	
	void draw(){
		if(IsEnable_GuiSimulation()){
			if(b_Simulate){
				ofEnableAlphaBlending();
				ofEnableBlendMode(OF_BLENDMODE_ADD);
				
				ofSetColor(LedParam->get_R(), LedParam->get_G(), LedParam->get_B(), 230);
				ofDrawCircle(pos, radius);
				
				ofDisableAlphaBlending();
			}
		}
	}
};

class NOISE_PARAM{
private:
	const double Amp;
	const double Amp_min;
	
	const double Freq_sec;
	const double ofs_sec;
	
public:
	NOISE_PARAM(double _Amp, double Freq_min, double Freq_max, double ofs_min, double ofs_max)
	: Freq_sec(ofRandom(Freq_min, Freq_max))
	, ofs_sec(ofRandom(ofs_min, ofs_max))
	, Amp(_Amp)
	, Amp_min(_Amp/5)
	{
	}
	
	double get_SignedNoise(double t){
		return Amp * ofSignedNoise(t * Freq_sec + ofs_sec);
	}
	double get_SignedNoise_Fade(double Fade, double t){
		double _Amp = ofMap(Fade, 0, 1, Amp_min, Amp);
		return _Amp * ofSignedNoise(t * Freq_sec + ofs_sec);
	}
	
	double get_SignedNoise(double t, double param1){
		return Amp * ofSignedNoise(t * Freq_sec + ofs_sec, param1);
	}
	double get_SignedNoise_Fade(double Fade, double t, double param1){
		double _Amp = ofMap(Fade, 0, 1, Amp_min, Amp);
		return _Amp * ofSignedNoise(t * Freq_sec + ofs_sec, param1);
	}
	
	double get_Noise(double t){
		return Amp * ofNoise(t * Freq_sec + ofs_sec);
	}
	double get_Noise_Fade(double Fade, double t){
		double _Amp = ofMap(Fade, 0, 1, Amp_min, Amp);
		return _Amp * ofNoise(t * Freq_sec + ofs_sec);
	}
	
	double get_Noise(double t, double param1){
		return Amp * ofNoise(t * Freq_sec + ofs_sec, param1);
	}
	double get_Noise_Fade(double Fade, double t, double param1){
		double _Amp = ofMap(Fade, 0, 1, Amp_min, Amp);
		return _Amp * ofNoise(t * Freq_sec + ofs_sec, param1);
	}
};

struct LED_LIGHT{
	const int ODE_id;
	const int AddressFrom;
	const enum LED_DEVICE_TYPE LedDeviceType;
	const enum COLOR_SURFACE ColorSurface;
	
	LED_SIMULATION LedSimulation;
	
	NOISE_PARAM Noise_Run_LevSync;
	NOISE_PARAM Noise_Run_ColSync;
	NOISE_PARAM Noise_Calm;
	
	LED_PARAM LedParam;
	
	LED_LIGHT(int _ODE_id, int _AddressFrom, enum LED_DEVICE_TYPE _LedDeviceType, COLOR_SURFACE _ColorSurface, bool _b_Simulate = false, ofPoint _pos = ofPoint(0, 0, 0), int _radius = 1)
	: ODE_id(_ODE_id), AddressFrom(_AddressFrom), LedDeviceType(_LedDeviceType), ColorSurface(_ColorSurface), LedSimulation(_b_Simulate, _pos, _radius, &LedParam)
	, Noise_Run_LevSync(30, 0.5, 2.0, 0, 1000), Noise_Run_ColSync(20, 0.5, 2.0, 0, 1000), Noise_Calm(0, 0.5, 2.0, 0, 1000)
	{
	}
};

struct LED_TEST{
	LED_PARAM LedParam;
	int LedId;
	
	LED_TEST()
	{
		clear();
	}
	
	void clear()
	{
		LedId = 0;
		LedParam.clear();
	}
};

/**************************************************
**************************************************/
class DMX{
private:
	/****************************************
	****************************************/
	ofxArtnet artnet;
	
	/****************************************
	****************************************/
	void Send_AllZero_to_AllOde();
	
	/********************
	singleton
	********************/
	DMX();
	~DMX();
	DMX(const DMX&);				// Copy constructor. no define. 
	DMX& operator=(const DMX&);		// コピー代入演算子. no define.
	
public:
	/****************************************
	****************************************/
	static DMX& getInstance(){
		static DMX inst;
		return inst;
	}
	
	void setup();
	void draw(double dimmer);
	void draw_test(double dimmer);
	void exit();
};


/************************************************************
************************************************************/
extern LED_LIGHT DesignLight[];
extern const int NUM_DESIGN_LEDS;

extern LED_LIGHT SafetyLight[];
extern const int NUM_SAFETY_LEDS;

extern LED_TEST test_DesignLight;
extern LED_TEST test_SafetyLight;


