#include "ofMain.h"
#include "ofApp.h"

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
	printf("\t0:STANDING\n");
	printf("\t1:MIC_TEST\n");
	printf("\t2:GUI_SUMILATION\n");
	printf("\t3:LED_SUMILATION\n");
	printf("\t4:PLAY_RECED\n");
	printf("\n");
	
	printf("> DesignCategory\n");
	printf("\t0:LEV_MIC_SYNC\n");
	printf("\t1:PATTERN\n");
	printf("\t2:ALL_ON\n");
	printf("\t3:NUM_LEDS\n");
	printf("\n");
	
	printf("> Block Grouping\n");
	printf("\t0:FLOW\n");
	printf("\t1:SIN\n");
	printf("\n");
	
	/********************
	********************/
	int soundStream_DeviceId = -1;
	int _BootMode = 0;
	int _DesignCategory = -1;
	int _BlockGrouping_id = -1;
	
	if(2 <= argc) soundStream_DeviceId = atoi(argv[1]);
	if(3 <= argc) _BootMode = atoi(argv[2]);
	if(4 <= argc) _DesignCategory = atoi(argv[3]);
	if(5 <= argc) _BlockGrouping_id = atoi(argv[4]);
	
	ofRunApp(new ofApp(soundStream_DeviceId, _BootMode, _DesignCategory, _BlockGrouping_id));
}
