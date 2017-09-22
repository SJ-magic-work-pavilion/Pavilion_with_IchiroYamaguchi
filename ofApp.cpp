/************************************************************
************************************************************/
#include "ofApp.h"
#include <time.h>

/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp(int _soundStream_DeviceId)
: soundStream_DeviceId(_soundStream_DeviceId)
, b_Reset_VolumeInput(true)
, b_Refresh_VolumeData(true)
, DesignManager(DESIGN_MANAGER::getInstance())
, gui_LedId_max(20)
, gui_LedId_min(-1)
, b__LedTest_ID_UpDown_byKey_DesignLight(true)
{
}

/******************************
******************************/
ofApp::~ofApp()
{
}

/******************************
******************************/
void ofApp::exit()
{
	/********************
	********************/
#ifndef MIC_ONLY
	DesignManager.exit();
#endif

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
	srand((unsigned)time(NULL));
	
	/********************
	********************/
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
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
	GG_SoundFilter.add(Monitor_v_max.setup("v max", 1.0, 0.1, 2.0));
	gui.add(&GG_SoundFilter);
	
	GG_VolRange.setup("Vol Range");
	GG_VolRange.add(gui_Vol_thresh_L.setup("thresh L", 0.05, 0.01, 0.5));
	GG_VolRange.add(gui_Vol_thresh_H.setup("thresh H", 0.1, 0.01, 0.5));
	GG_VolRange.add(gui_Vol_Map_L.setup("Map L", 0, 0, 0.5));
	GG_VolRange.add(gui_Vol_Map_H.setup("Map H", 0.3, 0, 0.5));
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
#ifndef MIC_ONLY
	DesignManager.setup();
#endif
}

//--------------------------------------------------------------
void ofApp::update(){
	/********************
	********************/
	Thread_Verts_SoundLevel.lock();
	Vbo_SoundLevel.updateVertexData(&Thread_Verts_SoundLevel.get_MonitorVert(0, Monitor_v_max), NUM_POINTS);
	RawVolumeLevel_of_theMouse_x = Thread_Verts_SoundLevel.get_RawVal(mouseX);
	
#ifndef MIC_ONLY
	DesignManager.update(Thread_Verts_SoundLevel.get_Latest_RawVal(), gui_Vol_thresh_L, gui_Vol_thresh_H, gui_Vol_Map_L, gui_Vol_Map_H);
#endif
	
	Thread_Verts_SoundLevel.unlock();
}

/******************************
******************************/
void ofApp::draw_VolThresh()
{
	int y_threshL = ofMap(gui_Vol_thresh_L, 0, Monitor_v_max, 0, HEIGHT - MARGIN);
	int y_threshH = ofMap(gui_Vol_thresh_H, 0, Monitor_v_max, 0, HEIGHT - MARGIN);
	
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	if(y_threshL < y_threshH)	ofSetColor(0, 0, 255, 80);
	else						ofSetColor(255, 0, 0, 80);
	
	ofDrawRectangle(0, y_threshL, WIDTH, y_threshH - y_threshL);
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
	ofSetColor(150);
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
	ofSetColor(150);
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
#ifndef MIC_ONLY
	ofColor copy_GuiColor = gui_DesignLight_Color;
	LED_PARAM sendColor_DesignLight(copy_GuiColor.r, copy_GuiColor.g, copy_GuiColor.b);
	
	copy_GuiColor = gui_SafetyLight_Color;
	LED_PARAM sendColor_SafetyLight(copy_GuiColor.r, copy_GuiColor.g, copy_GuiColor.b);
	
	DesignManager.draw(gui_DesignLight_Id, sendColor_DesignLight, gui_SafetyLight_Id, sendColor_SafetyLight);
#endif
	
	/********************
	********************/
	gui.draw();
}

/******************************
******************************/
void ofApp::audioReceived(float *input, int bufferSize, int nChannels)
{
	/********************
	********************/
	double v = 0;
	if(gui_b_VolSimulation){
		v = gui_Simulation_Volume;
		
	}else{
		for(int i = 0; i < bufferSize * nChannels; i++){
			v += input[i] * input[i];
		}
		v = sqrt(v / bufferSize);
	}
	
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
	
	static float t_LastINT = 0;
	float now = ofGetElapsedTimef();
	
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
				********************/
				double alpha;
				
				if( (LPF_Sound_ThreshSec == 0) || (LPF_Sound_ThreshSec < dt) ){
					alpha = 1;
				}else{
					alpha = 1/LPF_Sound_ThreshSec * dt;
				}
				v_Sound = alpha * v_Sound + (1 - alpha) * Last_v_Sound;
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
			
		case 'e':
#ifndef MIC_ONLY
			DesignManager.Escape_StateChart();
#endif
			break;
			
		case 'g':
#ifndef MIC_ONLY
			DesignManager.Start_StateChart();
#endif
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
