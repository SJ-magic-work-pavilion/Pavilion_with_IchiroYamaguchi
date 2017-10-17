#include "ofMain.h"
#include "ofApp.h"
#include "sj_common.h"

//========================================================================
int main( int argc, char** argv ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	
	/********************
	********************/
	printf("exe [AudioInput id] [Boot mode] [PatternCategory] [Block Grouping]\n");
	printf("\n");
	
	printf("> Audio input id\n");
	printf("\n");
	
	printf("> Boot mode\n");
	printf("\t0:%-30s", "STANDING");
	printf("\t1:%-30s\n", "MIC_TEST");
	
	printf("\t2:%-30s", "GUI_SUMILATION");
	printf("\t3:%-30s\n", "LED_SUMILATION");
	
	printf("\t4:%-30s", "PLAY_RECED");
	printf("\n\n");
	
	printf("> DesignCategory\n");
	printf("\t0:%-30s", "LEV_MIC_SYNC");
	printf("\t1:%-30s\n", "PATTERN");
	
	printf("\t2:%-30s", "ALL_ON");
	printf("\t3:%-30s\n", "NUM_LEDS");
	printf("\n");
	
	
	int id = 0;
	printf("> Block Grouping\n");
	printf("Regular Direction : Restaurant->Entrance.\n");
	printf("Regular Site      : from Restaurant.\n");
	
	printf("\t%2d:%-30s", id++, "FLOW");
	printf("\t%2d:%-30s\n", id++, "FLOW_REV");
	
	printf("\t%2d:%-30s", id++, "FLOW_OUT");
	printf("\t%2d:%-30s\n", id++, "FLOW_IN");
	
	printf("\t%2d:%-30s", id++, "FLOW_TWIST");
	printf("\t%2d:%-30s\n", id++, "FLOW_TWIST_REV");
	
	printf("\t%2d:%-30s", id++, "FLOW_TWIST_OUT");
	printf("\t%2d:%-30s\n", id++, "FLOW_TWIST_IN");
	
	printf("\t%2d:%-30s", id++, "FLOW__AND__STOP");
	printf("\t%2d:%-30s\n", id++, "FLOW_REV__AND__STOP");
	
	printf("\t%2d:%-30s", id++, "STOP__AND__FLOW");
	printf("\t%2d:%-30s\n", id++, "STOP__AND__FLOW_REV");
	
	printf("\t%2d:%-30s", id++, "SIN");
	printf("\t%2d:%-30s\n", id++, "SIN_REV");
	
	printf("\t%2d:%-30s", id++, "SIN_OUT");
	printf("\t%2d:%-30s\n", id++, "SIN_IN");
	
	printf("\t%2d:%-30s", id++, "SIN_TWIST");
	printf("\t%2d:%-30s\n", id++, "SIN_TWIST_REV");
	
	printf("\t%2d:%-30s", id++, "SIN_TWIST_OUT");
	printf("\t%2d:%-30s\n", id++, "SIN_TWIST_IN");
	
	printf("\t%2d:%-30s", id++, "SIN__AND__STOP");
	printf("\t%2d:%-30s\n", id++, "SIN_REV__AND__STOP");
	
	printf("\t%2d:%-30s", id++, "STOP__AND__SIN");
	printf("\t%2d:%-30s\n", id++, "STOP__AND__SIN_REV");
	
	printf("\t%2d:%-30s", id++, "STROBE_1");
	printf("\t%2d:%-30s\n", id++, "STROBE_2");
	
	printf("\t%2d:%-30s", id++, "STROBE_3");
	printf("\t%2d:%-30s\n", id++, "STROBE_4");
	
	printf("\t%2d:%-30s", id++, "STROBE_6");
	printf("\t%2d:%-30s\n", id++, "STROBE_12");
	
	printf("\t%2d:%-30s", id++, "CAM_STROBE");
	printf("\n");
	printf("\n");
	
	/********************
	********************/
#ifdef SJ_RELEASE
	int soundStream_DeviceId = 2;
	int _BootMode = 3;
	int _DesignCategory = -1;
	int _BlockGrouping_id = -1;
	
	ofRunApp(new ofApp(soundStream_DeviceId, _BootMode, _DesignCategory, _BlockGrouping_id));
	
#else
	int soundStream_DeviceId = -1;
	int _BootMode = 0;
	int _DesignCategory = -1;
	int _BlockGrouping_id = -1;
	
	if(2 <= argc) soundStream_DeviceId = atoi(argv[1]);
	if(3 <= argc) _BootMode = atoi(argv[2]);
	if(4 <= argc) _DesignCategory = atoi(argv[3]);
	if(5 <= argc) _BlockGrouping_id = atoi(argv[4]);
	
	ofRunApp(new ofApp(soundStream_DeviceId, _BootMode, _DesignCategory, _BlockGrouping_id));
	
#endif
}
