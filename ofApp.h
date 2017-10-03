/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxGui.h"

#include "sj_common.h"
#include "threadParam.h"

// #include "shortPattern.h"
// #include "BlockPattern.h"
// #include "BlockGroup.h"
#include "Design.h"

/************************************************************
************************************************************/

class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	/********************
	********************/
	int soundStream_DeviceId;
	ofSoundStream soundStream;
	
	/********************
	********************/
	ofxPanel gui;
	
	ofxGuiGroup GG_SoundFilter;
	ofxFloatSlider LPF_Sound_ThreshSec; // 大:緩やか
	ofxToggle gui_b_LimitVolDown;
	ofxFloatSlider gui_LimitVolDown_tan; // 小:緩やか
	ofxFloatSlider Monitor_v_max;
	
	ofxGuiGroup GG_DirectFilter;
	ofxFloatSlider LPF_Direct_NumLeds_ThreshSec; // 大:緩やか
	ofxFloatSlider LPF_Direct_NumWaves_ThreshSec; // 大:緩やか
	
	ofxGuiGroup GG_VolRange;
	ofxFloatSlider gui_Vol_thresh_L;
	ofxFloatSlider gui_Vol_thresh_H;
	ofxFloatSlider gui_Vol_Map_L;
	ofxFloatSlider gui_Vol_Map_H;
	
	ofxGuiGroup GG_LedTest;
	ofxIntSlider	gui_DesignLight_Id;
	ofxColorSlider	gui_DesignLight_Color;
	ofxIntSlider	gui_SafetyLight_Id;
	ofxColorSlider	gui_SafetyLight_Color;
	
	const int gui_LedId_max;
	const int gui_LedId_min;
	bool b__LedTest_ID_UpDown_byKey_DesignLight;
	
	ofxGuiGroup GG_VolSimulation;
	ofxToggle gui_b_VolSimulation;
	ofxFloatSlider	gui_Simulation_Volume;
	
	
	/********************
	********************/
	ofVbo Vbo_SoundLevel;
	THREAD__VERTS Thread_Verts_SoundLevel;
	ofFloatColor Color_SoundLevel[NUM_POINTS];
	
	/********************
	********************/
	int png_id;
	bool b_Reset_VolumeInput;
	bool b_Refresh_VolumeData;
	float RawVolumeLevel_of_theMouse_x;
	
	/********************
	********************/
	DESIGN_MANAGER& DesignManager;
	
	/********************
	********************/
	FILE* fp_RecPlay;
	bool b_Rec;
	
	/****************************************
	****************************************/
	void Relpace_ch(char* buf, char from, char to);
	double ReadRecedData_FromFile();
	
	void draw_VolThresh();
	void draw_VolMapRange();

	
public:
	/****************************************
	****************************************/
	ofApp(int _soundStream_DeviceId, int _BootMode, int _DesignCategory, int _BlockGrouping_id);
	void audioReceived(float *input, int bufferSize, int nChannels);
	
	~ofApp();
	void exit();
	
	void setup();
	void update();
	void draw();
	
	void draw_Graph();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
};
