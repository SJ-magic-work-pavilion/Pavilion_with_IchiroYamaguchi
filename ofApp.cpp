/************************************************************
************************************************************/
#include "ofApp.h"
#include <time.h>

/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp(int _soundStream_DeviceId, int _BootMode, int _DesignCategory, int _BlockGrouping_id)
: soundStream_DeviceId(_soundStream_DeviceId)
, b_Reset_VolumeInput(true)
, b_Refresh_VolumeData(true)
, DesignManager(DESIGN_MANAGER::getInstance())
, gui_LedId_max(30)
, gui_LedId_min(-1)
, b__LedTest_ID_UpDown_byKey_DesignLight(true)
, fp_RecPlay(NULL)
, b_Rec(false)
{
	if(NUM_BOOT_MODE <= _BootMode){
		printf("> Boot mode:out of Range -> BOOT_MODE__LED_SIMULATION\n");
		BootMode = BOOT_MODE__LED_SIMULATION;
	}else{
		BootMode = BOOT_MODE(_BootMode);
	}
	
	argin_DesignCategory = _DesignCategory;
	argin_BlockGrouping_id = _BlockGrouping_id;
}

/******************************
******************************/
ofApp::~ofApp()
{
	if(fp_RecPlay) fclose(fp_RecPlay);
}

/******************************
******************************/
void ofApp::exit()
{
	/********************
	********************/
	if(IsEnable_LedManager()){
		DesignManager.exit();
	}

	/********************
	********************/
	try{
		/********************
		stop済みのthreadをさらにstopすると、Errorが出るようだ。
		********************/
		if(Thread_Verts_SoundLevel.isThreadRunning()){
			Thread_Verts_SoundLevel.waitForThread(true);
		}
		
	}catch(...){
		printf("Thread exiting Error\n");
	}
	
	/********************
	********************/
	printf("Good bye\n");
	
	std::exit(1);
}

//--------------------------------------------------------------
void ofApp::setup(){
	/********************
	test code.
	********************/
	// SHORT_PATTERN::SpLev_test();
	// test_BlockPattern();
	// test_BlockGrouping();
	
	/********************
	********************/
	if(IsEnable_PlayReced()){
		fp_RecPlay = fopen("../../../data/Rec.txt", "r");
		if(fp_RecPlay == NULL) { ERROR_MSG(); std::exit(1); }
	}
	
	/********************
	********************/
	srand((unsigned)time(NULL));
	
	/********************
	********************/
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	// ofSetFrameRate(30);
	
	ofSetWindowShape(WIDTH, HEIGHT);
	ofSetEscapeQuitsApp(false);
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofEnableSmoothing();
	
	/********************
	********************/
	soundStream.listDevices();
	if(soundStream_DeviceId == -1){
		ofExit();
	}
	soundStream.setDeviceID(soundStream_DeviceId);
	soundStream.setup(this, 0, 1, 44100, 1024, 2);
	
	/********************
	********************/
	gui.setup();
	
	GG_SoundFilter.setup("Sound Filter");
	GG_SoundFilter.add(LPF_Sound_ThreshSec.setup("LPF Snd Th_Sec", 0.3, 0, 3.0));
	GG_SoundFilter.add(gui_b_LimitVolDown.setup("b_LimitVolDown", false));
	GG_SoundFilter.add(gui_LimitVolDown_tan.setup("LimitDown tan", 0.2, 0.05, 0.5));
	GG_SoundFilter.add(Monitor_v_max.setup("v max", 0.5, 0.1, 2.0));
	gui.add(&GG_SoundFilter);
	
	GG_DirectFilter.setup("Direct Filter");
	GG_DirectFilter.add(LPF_Direct_NumLeds_ThreshSec.setup("Num Leds", 0, 0, 0.6));
	GG_DirectFilter.add(LPF_Direct_NumWaves_ThreshSec.setup("Num Waves", 0.3, 0, 0.6));
	gui.add(&GG_DirectFilter);
	
	GG_VolRange.setup("Vol Range");
	GG_VolRange.add(gui_Vol_thresh_L.setup("thresh L", 0.028, 0.01, 0.5));
	GG_VolRange.add(gui_Vol_thresh_H.setup("thresh H", 0.035, 0.01, 0.5));
	GG_VolRange.add(gui_Vol_thresh_P_L.setup("thresh_P L", 0.07, 0.01, 0.5));
	GG_VolRange.add(gui_Vol_thresh_P_H.setup("thresh_P H", 0.1, 0.01, 0.5));
	GG_VolRange.add(gui_Vol_Map_L.setup("Map L", 0.028, 0, 0.5));
	GG_VolRange.add(gui_Vol_Map_H.setup("Map H", 0.16, 0, 0.5));
	/*
	GG_VolRange.add(gui_Vol_thresh_L.setup("thresh L", 0.14, 0.01, 0.5));
	GG_VolRange.add(gui_Vol_thresh_H.setup("thresh H", 0.16, 0.01, 0.5));
	GG_VolRange.add(gui_Vol_Map_L.setup("Map L", 0.14, 0, 0.5));
	GG_VolRange.add(gui_Vol_Map_H.setup("Map H", 0.375, 0, 0.5));
	*/
	gui.add(&GG_VolRange);
	
	/* */
	ofColor initColor = ofColor(0, 0, 0, 255);
	ofColor minColor = ofColor(0, 0, 0, 0);
	ofColor maxColor = ofColor(255, 255, 255, 255);
	
	GG_LedTest.setup("Led Test");
	GG_LedTest.add(gui_DesignLight_Id.setup("DesignLight id", 0, gui_LedId_min, gui_LedId_max));
	GG_LedTest.add(gui_DesignLight_Color.setup("DesignLight color", initColor, minColor, maxColor));
	GG_LedTest.add(gui_SafetyLight_Id.setup("SafetyLight id", 0, gui_LedId_min, gui_LedId_max));
	GG_LedTest.add(gui_SafetyLight_Color.setup("SafetyLight color", initColor, minColor, maxColor));
	gui.add(&GG_LedTest);
	
	GG_VolSimulation.setup("Vol simulation");
	GG_VolSimulation.add(gui_b_VolSimulation.setup("b_Simulate", false));
	GG_VolSimulation.add(gui_Simulation_Volume.setup("volume", 0, 0, 0.5));
	gui.add(&GG_VolSimulation);
	
	/********************
	********************/
	for(int i = 0; i < NUM_POINTS; i++){
		Color_SoundLevel[i].set(0.1, 0.8, 1.0, 0.8);
	}
	Thread_Verts_SoundLevel.lock();
		// Vbo_SoundLevel.setVertexData(&Thread_Verts_SoundLevel[0], NUM_POINTS, GL_DYNAMIC_DRAW);
		Vbo_SoundLevel.setVertexData(&Thread_Verts_SoundLevel.get_MonitorVert(0, Monitor_v_max), NUM_POINTS, GL_DYNAMIC_DRAW);
	Thread_Verts_SoundLevel.unlock();
	Vbo_SoundLevel.setColorData(Color_SoundLevel, NUM_POINTS, GL_DYNAMIC_DRAW);
	
	Thread_Verts_SoundLevel.startThread(true, false); // blocking, non verbose
	
	/********************
	********************/
	png_id = 0;
	
	/********************
	********************/
	if(IsEnable_LedManager()){
		DesignManager.setup();
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	/********************
	********************/
	float Latest_RawVal;
	
	Thread_Verts_SoundLevel.lock();
		Vbo_SoundLevel.updateVertexData(&Thread_Verts_SoundLevel.get_MonitorVert(0, Monitor_v_max), NUM_POINTS);
		RawVolumeLevel_of_theMouse_x = Thread_Verts_SoundLevel.get_RawVal(mouseX);
		Latest_RawVal = Thread_Verts_SoundLevel.get_Latest_RawVal();
	Thread_Verts_SoundLevel.unlock();
	
	/********************
	********************/
	if(IsEnable_LedManager()){
		DesignManager.update_GuiParam(LPF_Direct_NumLeds_ThreshSec, LPF_Direct_NumWaves_ThreshSec);
		DesignManager.update(Latest_RawVal, gui_Vol_thresh_L, gui_Vol_thresh_H, gui_Vol_thresh_P_L, gui_Vol_thresh_P_H, gui_Vol_Map_L, gui_Vol_Map_H);
	}
}

/******************************
******************************/
void ofApp::draw_VolThresh()
{
	/* */
	int y_threshL = ofMap(gui_Vol_thresh_L, 0, Monitor_v_max, 0, HEIGHT - MARGIN);
	int y_threshH = ofMap(gui_Vol_thresh_H, 0, Monitor_v_max, 0, HEIGHT - MARGIN);
	
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	if(y_threshL < y_threshH)	ofSetColor(0, 0, 255, 60);
	else						ofSetColor(255, 0, 0, 80);
	
	ofDrawRectangle(0, y_threshL, WIDTH, y_threshH - y_threshL);
	
	/* */
	int y_threshPL = ofMap(gui_Vol_thresh_P_L, 0, Monitor_v_max, 0, HEIGHT - MARGIN);
	int y_threshPH = ofMap(gui_Vol_thresh_P_H, 0, Monitor_v_max, 0, HEIGHT - MARGIN);
	
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	if(y_threshPL < y_threshPH)	ofSetColor(0, 0, 255, 60);
	else						ofSetColor(255, 0, 0, 80);
	
	ofDrawRectangle(0, y_threshPL, WIDTH, y_threshPH - y_threshPL);
}

/******************************
******************************/
void ofApp::draw_VolMapRange()
{
	int y_MapL = ofMap(gui_Vol_Map_L, 0, Monitor_v_max, 0, HEIGHT - MARGIN);
	int y_MapH = ofMap(gui_Vol_Map_H, 0, Monitor_v_max, 0, HEIGHT - MARGIN);
	
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	if(y_MapL < y_MapH)	ofSetColor(0, 255, 0, 15);
	else				ofSetColor(255, 0, 0, 15);
	
	ofDrawRectangle(0, y_MapL, WIDTH, y_MapH - y_MapL);
}

/******************************
******************************/
void ofApp::draw_Graph()
{
	/********************
	********************/
	ofBackground(20);

	/********************
	********************/
	ofPushStyle();
	ofPushMatrix();
	
	ofTranslate(0, ofGetHeight() - MARGIN);
	ofScale(1, -1, 1);
	
	draw_VolMapRange();
	draw_VolThresh();
	
	glPointSize(1.5);
	Vbo_SoundLevel.draw(GL_LINE_STRIP, 0, NUM_POINTS);
	
	/* 横線 */
#if (PLATFORM == PLATFORM__MYMAC)
	ofSetColor(150);
#else
	ofSetColor(150, 40);
#endif
	ofSetLineWidth(1);
	const double y_step = (ofGetHeight() - MARGIN) / 10;
	for(int i = 0; i * y_step < ofGetHeight(); i++){
		int y = int(i * y_step + 0.5);
		ofLine(0, y, ofGetWidth(), y);
	}
	
	ofPopMatrix();
	ofPopStyle();
	
	/********************
	********************/
#if (PLATFORM == PLATFORM__MYMAC)
	ofSetColor(150);
#else
	ofSetColor(150, 40);
#endif
	ofSetLineWidth(1);
	const double x_step = 43.0664; // 1 sec
	for(int i = 0; i * x_step < ofGetWidth(); i++){
		int x = int(i * x_step + 0.5);
		ofLine(x, 0, x, ofGetHeight());
	}
	
	ofSetColor(255, 0, 0);
	ofSetLineWidth(2);
	ofLine(mouseX, 0, mouseX, ofGetHeight());
	
	char buf[BUF_SIZE];
	sprintf(buf, "RawVolume = %3.3f, FrameRate = %5.1f", RawVolumeLevel_of_theMouse_x, ofGetFrameRate());
	ofSetColor(ofColor::white);
	ofDrawBitmapString(buf, 250, 30);
}

//--------------------------------------------------------------
void ofApp::draw(){
	/********************
	********************/
	draw_Graph();
	
	/********************
	********************/
	if(IsEnable_LedManager()){
		ofColor copy_GuiColor = gui_DesignLight_Color;
		LED_PARAM sendColor_DesignLight(copy_GuiColor.r, copy_GuiColor.g, copy_GuiColor.b);
		
		copy_GuiColor = gui_SafetyLight_Color;
		LED_PARAM sendColor_SafetyLight(copy_GuiColor.r, copy_GuiColor.g, copy_GuiColor.b);
		
		DesignManager.draw(gui_DesignLight_Id, sendColor_DesignLight, gui_SafetyLight_Id, sendColor_SafetyLight);
	}
	
	/********************
	********************/
	if(b_Rec){
		ofSetColor(255, 0, 0, 100);
		ofDrawCircle(1230, 40, 15);
	}

	/********************
	********************/
	gui.draw();
}

/******************************
******************************/
void ofApp::Relpace_ch(char* buf, char from, char to)
{
	for(int i = 0; buf[i] != '\0'; i++){
		if(buf[i] == from){
			buf[i] = to;
		}
	}
}

/******************************
******************************/
double ofApp::ReadRecedData_FromFile()
{
	if(fp_RecPlay == NULL){
		ERROR_MSG(); std::exit(1);
	}
	
	char buf[BUF_SIZE];
	if(fgets(buf, BUF_SIZE, fp_RecPlay) == NULL){
		rewind(fp_RecPlay);
		
		if(fgets(buf, BUF_SIZE, fp_RecPlay) == NULL){
			ERROR_MSG(); std::exit(1);
		}
		printf("> Reced File Loop\n");
	}
	
	Relpace_ch(buf, '\n', '\0');
	string str_buf = buf;
	
	vector<string> str_val = ofSplitString(str_buf,",");
	
	return atof(str_val[1].c_str());
}

/******************************
******************************/
void ofApp::audioReceived(float *input, int bufferSize, int nChannels)
{
	/********************
	********************/
	static float t_LastINT = 0;
	float now = ofGetElapsedTimef();
	
	/********************
	********************/
	double v = 0;
	if(gui_b_VolSimulation){
		v = gui_Simulation_Volume;
		
	}else if(IsEnable_PlayReced()){
		v = ReadRecedData_FromFile();
		
	}else{
		for(int i = 0; i < bufferSize * nChannels; i++){
			v += input[i] * input[i];
		}
		v = sqrt(v / bufferSize);
	}
	
	if(b_Rec) fprintf(fp_RecPlay, "%f,%f\n", now, v);
	
	/********************
	********************/
	enum STATE{
		STATE_BOOT,
		STATE_MEAS,
	};
	static STATE state = STATE_BOOT;
	
	const int thresh_count_start = 5;
	static int c_INT = 0;
	static double v_sum = 0;
	static double Last_v_Sound = 0;
	
	switch(state){
		case STATE_BOOT:
			c_INT++;
			v_sum += v;
			
			if(thresh_count_start <= c_INT){
				Last_v_Sound = v_sum / thresh_count_start;
				state = STATE_MEAS;
			}
			break;
			
		case STATE_MEAS:
			if(b_Reset_VolumeInput){
				b_Reset_VolumeInput = false;
				state = STATE_BOOT;
				
				c_INT = 0;
				v_sum = 0;
				
			}else{
				double dt = now - t_LastINT;
				double v_Sound = v;
				
				/********************
				LPF
				********************/
				double alpha;
				
				if( (LPF_Sound_ThreshSec == 0) || (LPF_Sound_ThreshSec < dt) ){
					alpha = 1;
				}else{
					alpha = 1/LPF_Sound_ThreshSec * dt;
				}
				v_Sound = alpha * v_Sound + (1 - alpha) * Last_v_Sound;
				
				/********************
				Down limit
				********************/
				if(gui_b_LimitVolDown){
					double DownLimit_v = Last_v_Sound - gui_LimitVolDown_tan * (now - t_LastINT);
					v_Sound = max(v_Sound, DownLimit_v);
				}
				
				/********************
				********************/
				Last_v_Sound = v_Sound;
				
				/********************
				********************/
				if(b_Refresh_VolumeData){
					Thread_Verts_SoundLevel.lock();
					Thread_Verts_SoundLevel.set(v_Sound);
					Thread_Verts_SoundLevel.unlock();
				}
			}
			
			break;
	}
	
	t_LastINT = now;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
		case OF_KEY_DOWN:
			if(b__LedTest_ID_UpDown_byKey_DesignLight){
				if(gui_LedId_min < gui_DesignLight_Id) gui_DesignLight_Id = gui_DesignLight_Id - 1;
			}else{
				if(gui_LedId_min < gui_SafetyLight_Id) gui_SafetyLight_Id = gui_SafetyLight_Id - 1;
			}
			break;
			
		case OF_KEY_UP:
			if(b__LedTest_ID_UpDown_byKey_DesignLight){
				if(gui_DesignLight_Id < gui_LedId_max) gui_DesignLight_Id = gui_DesignLight_Id + 1;
			}else{
				if(gui_SafetyLight_Id < gui_LedId_max) gui_SafetyLight_Id = gui_SafetyLight_Id + 1;
			}
			break;
			
		case ' ':
		{
			enum{
				BUF_SIZE = 512,
			};
			char buf[BUF_SIZE];
			
			sprintf(buf, "image_%d.png", png_id);
			ofSaveScreen(buf);
			printf("%s saved\n", buf);
			
			png_id++;
		}
			break;
			
		case 'c':
			if(IsEnable_RecMic()){
				if(fp_RecPlay) fclose(fp_RecPlay);
				
				b_Rec = !b_Rec;
				if(b_Rec){
					fp_RecPlay = fopen("../../../data/Rec.txt", "w");
					if(fp_RecPlay == NULL){
						ERROR_MSG();
						std::exit(1);
					}
				}
			}
			
			break;

		case 'e':
			if(IsEnable_LedManager()){
				DesignManager.Escape_StateChart();
			}
			break;
			
		case 'g':
			if(IsEnable_LedManager()){
				DesignManager.Start_StateChart();
			}
			break;
			
		case 'r':
			b_Reset_VolumeInput = true;
			printf("\n> Reset\n");
			break;
			
		case 'p':
			b_Refresh_VolumeData = !b_Refresh_VolumeData;
			break;
			
		case 's':
			gui.saveToFile("gui.xml");
			printf("save setting\n");
			break;
			
		case 't':
			b__LedTest_ID_UpDown_byKey_DesignLight = !b__LedTest_ID_UpDown_byKey_DesignLight;
			break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
