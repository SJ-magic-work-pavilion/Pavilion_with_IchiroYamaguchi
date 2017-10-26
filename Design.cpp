/************************************************************
************************************************************/
#include "Design.h"

/************************************************************
param
************************************************************/

/********************
********************/
static const LED_PARAM BoostColorForSmoothAnimation(2, 2, 2);


/********************
Animationのsmoothさ確保のため、全体をboostしている。
この時に、色味をきちんと確認できるLevelは、
	(15, 2, 2)
********************/
static const double calmColor_DarkRatio = 0;
static const LED_PARAM JobitoColor(5, 0, 0);


COLOR_COMBINATION_SET DESIGN_MANAGER::ColorCombination[] = {
	//*
	COLOR_COMBINATION_SET	(	"Marriage to white",
								1,
								JobitoColor, LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 0), LED_PARAM(255, 255, 255), LED_PARAM(255, 255, 255),	// COLOR_FROM_RESTAURANT
								JobitoColor, LED_PARAM(0, 0, 255), LED_PARAM(0, 255, 255), LED_PARAM(255, 255, 255), LED_PARAM(255, 255, 255)		// COLOR_FROM_ENTRANCE
							),
	COLOR_COMBINATION_SET	(	"Marriage to Red",
								1,
								JobitoColor, LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 0), LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 255),	// COLOR_FROM_RESTAURANT
								JobitoColor, LED_PARAM(0, 0, 255), LED_PARAM(255, 0, 255), LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 255)		// COLOR_FROM_ENTRANCE
							),
	COLOR_COMBINATION_SET	(	"Marriage to Blue",
								1,
								JobitoColor, LED_PARAM(255, 0, 0), LED_PARAM(255, 0, 255), LED_PARAM(0, 0, 255), LED_PARAM(255, 255, 255),	// COLOR_FROM_RESTAURANT
								JobitoColor, LED_PARAM(0, 0, 255), LED_PARAM(0, 255, 255), LED_PARAM(0, 0, 255), LED_PARAM(255, 255, 255)		// COLOR_FROM_ENTRANCE
							),
	COLOR_COMBINATION_SET	(	"Lover",
								1,
								JobitoColor, LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 255), LED_PARAM(0, 0, 255), LED_PARAM(255, 255, 255),	// COLOR_FROM_RESTAURANT
								JobitoColor, LED_PARAM(0, 0, 255), LED_PARAM(255, 255, 255), LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 255)		// COLOR_FROM_ENTRANCE
							),
	COLOR_COMBINATION_SET	(	"Approach",
								1,
								JobitoColor, LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 0), LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 255),	// COLOR_FROM_RESTAURANT
								JobitoColor, LED_PARAM(0, 0, 255), LED_PARAM(0, 255, 255), LED_PARAM(0, 0, 255), LED_PARAM(255, 255, 255)		// COLOR_FROM_ENTRANCE
							),
	COLOR_COMBINATION_SET	(	"Family own way from R",
								1,
								JobitoColor, LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 0), LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 255),	// COLOR_FROM_RESTAURANT
								JobitoColor, LED_PARAM(255, 0, 0), LED_PARAM(255, 0, 255), LED_PARAM(0, 0, 255), LED_PARAM(255, 255, 255)		// COLOR_FROM_ENTRANCE
							),
	COLOR_COMBINATION_SET	(	"Family own way from B",
								1,
								JobitoColor, LED_PARAM(0, 0, 255), LED_PARAM(255, 0, 255), LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 255),	// COLOR_FROM_RESTAURANT
								JobitoColor, LED_PARAM(0, 0, 255), LED_PARAM(0, 255, 255), LED_PARAM(0, 0, 255), LED_PARAM(255, 255, 255)		// COLOR_FROM_ENTRANCE
							),
	COLOR_COMBINATION_SET	(	"Family Gathering",
								1,
								JobitoColor, LED_PARAM(255, 255, 255), LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 255), LED_PARAM(255, 255, 255),	// COLOR_FROM_RESTAURANT
								JobitoColor, LED_PARAM(255, 255, 255), LED_PARAM(0, 0, 255), LED_PARAM(255, 255, 255), LED_PARAM(255, 255, 255)		// COLOR_FROM_ENTRANCE
							),
	/*/
	COLOR_COMBINATION_SET	(	"Marriage to white",
								1,
								calmColor_DarkRatio, LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 0), LED_PARAM(255, 255, 255), LED_PARAM(255, 255, 255),	// COLOR_FROM_RESTAURANT
								calmColor_DarkRatio, LED_PARAM(0, 0, 255), LED_PARAM(0, 255, 255), LED_PARAM(255, 255, 255), LED_PARAM(255, 255, 255)		// COLOR_FROM_ENTRANCE
							),
	COLOR_COMBINATION_SET	(	"Marriage to Red",
								1,
								calmColor_DarkRatio, LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 0), LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 255),	// COLOR_FROM_RESTAURANT
								calmColor_DarkRatio, LED_PARAM(0, 0, 255), LED_PARAM(255, 0, 255), LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 255)		// COLOR_FROM_ENTRANCE
							),
	COLOR_COMBINATION_SET	(	"Marriage to Blue",
								1,
								calmColor_DarkRatio, LED_PARAM(255, 0, 0), LED_PARAM(255, 0, 255), LED_PARAM(0, 0, 255), LED_PARAM(255, 255, 255),	// COLOR_FROM_RESTAURANT
								calmColor_DarkRatio, LED_PARAM(0, 0, 255), LED_PARAM(0, 255, 255), LED_PARAM(0, 0, 255), LED_PARAM(255, 255, 255)		// COLOR_FROM_ENTRANCE
							),
	COLOR_COMBINATION_SET	(	"Lover",
								1,
								calmColor_DarkRatio, LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 255), LED_PARAM(0, 0, 255), LED_PARAM(255, 255, 255),	// COLOR_FROM_RESTAURANT
								calmColor_DarkRatio, LED_PARAM(0, 0, 255), LED_PARAM(255, 255, 255), LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 255)		// COLOR_FROM_ENTRANCE
							),
	COLOR_COMBINATION_SET	(	"Approach",
								1,
								calmColor_DarkRatio, LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 0), LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 255),	// COLOR_FROM_RESTAURANT
								calmColor_DarkRatio, LED_PARAM(0, 0, 255), LED_PARAM(0, 255, 255), LED_PARAM(0, 0, 255), LED_PARAM(255, 255, 255)		// COLOR_FROM_ENTRANCE
							),
	COLOR_COMBINATION_SET	(	"Family own way from R",
								1,
								calmColor_DarkRatio, LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 0), LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 255),	// COLOR_FROM_RESTAURANT
								calmColor_DarkRatio, LED_PARAM(255, 0, 0), LED_PARAM(255, 0, 255), LED_PARAM(0, 0, 255), LED_PARAM(255, 255, 255)		// COLOR_FROM_ENTRANCE
							),
	COLOR_COMBINATION_SET	(	"Family own way from B",
								1,
								calmColor_DarkRatio, LED_PARAM(0, 0, 255), LED_PARAM(255, 0, 255), LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 255),	// COLOR_FROM_RESTAURANT
								calmColor_DarkRatio, LED_PARAM(0, 0, 255), LED_PARAM(0, 255, 255), LED_PARAM(0, 0, 255), LED_PARAM(255, 255, 255)		// COLOR_FROM_ENTRANCE
							),
	COLOR_COMBINATION_SET	(	"Family Gathering",
								1,
								calmColor_DarkRatio, LED_PARAM(255, 255, 255), LED_PARAM(255, 0, 0), LED_PARAM(255, 255, 255), LED_PARAM(255, 255, 255),	// COLOR_FROM_RESTAURANT
								calmColor_DarkRatio, LED_PARAM(255, 255, 255), LED_PARAM(0, 0, 255), LED_PARAM(255, 255, 255), LED_PARAM(255, 255, 255)		// COLOR_FROM_ENTRANCE
							),
	//*/
};
int DESIGN_MANAGER::NUM_COLOR_COMBINATIONS = sizeof(ColorCombination)/sizeof(ColorCombination[0]);


/********************
********************/
STROBE_COLOR_COMBINATION_SET DESIGN_MANAGER::StrobeColorCombination[] = {
	STROBE_COLOR_COMBINATION_SET( 4, LED_PARAM(255, 255, 255), LED_PARAM(255, 255, 255) ),	// white
	STROBE_COLOR_COMBINATION_SET( 1, LED_PARAM(255, 0, 0), LED_PARAM(255, 0, 0) ),			// Red
	STROBE_COLOR_COMBINATION_SET( 1, LED_PARAM(0, 0, 255), LED_PARAM(0, 0, 255) ),			// Blue
	STROBE_COLOR_COMBINATION_SET( 1, LED_PARAM(255, 100, 0), LED_PARAM(255, 100, 0) ),		// orange
	STROBE_COLOR_COMBINATION_SET( 1, LED_PARAM(140, 0, 255), LED_PARAM(140, 0, 255) ),		// purple
};
int DESIGN_MANAGER::NUM_STROBE_COLOR_COMBINATIONS = sizeof(StrobeColorCombination)/sizeof(StrobeColorCombination[0]);


/******************************
******************************/
int W_DesignCategory[] = {
	3, // DESIGN__LEV_MIC_SYNC,
	5, // DESIGN__PATTERN,
	3, // DESIGN__ALL_ON,
	0, // DESIGN__NUM_LEDS,
};


/************************************************************
func
************************************************************/

/******************************
******************************/
DESIGN_MANAGER::DESIGN_MANAGER()
: LevSync(0)
, ColorCombination_id(0)
, StrobeColorCombination_id(0)
, LedNumSync(0)
, b_StateChart(true)
, State(STATE_ESCAPE)
, DesignCategory(DESIGN__ALL_ON) // 一応
, b_DesignPattern(false)
, BlockGrouping_id(0)
, Fader_DesignLight(4.0)
, Fader_SafetyLight(2.0)
, t_now(0)
, t_LastINT(0)
, dmx(DMX::getInstance())
, LPF_Direct_NumLeds_ThreshSec(0)
, LPF_Direct_NumWaves_ThreshSec(0)
{
	/********************
	********************/
#ifdef LOG_DIRECT_FILTER
	fp_debug = fopen("../../../data/debug.csv", "w");
#endif

	/********************
	********************/
	Weight_ColorCombination_id = new int[NUM_COLOR_COMBINATIONS];
	for(int i = 0; i < NUM_COLOR_COMBINATIONS; i++){
		Weight_ColorCombination_id[i] = ColorCombination[i].Weight;
	}
	
	/********************
	********************/
	Weight_StrobeColorCombination_id = new int[NUM_STROBE_COLOR_COMBINATIONS];
	for(int i = 0; i < NUM_STROBE_COLOR_COMBINATIONS; i++){
		Weight_StrobeColorCombination_id[i] = StrobeColorCombination[i].Weight;
	}
	
	/********************
	********************/
	Weight_BlockGrouping_id = new int[NUM_GROUPTYPES];
	for(int i = 0; i < NUM_GROUPTYPES; i++){
		Weight_BlockGrouping_id[i] = BlockGrouping[i].Weight;
	}
	
	/********************
	********************/
	LedId_ExchangeTable_NumSync.resize(NUM_DESIGN_LEDS);
	for(int i = 0; i < NUM_DESIGN_LEDS; i++){
		LedId_ExchangeTable_NumSync[i] = i;
	}
}

/******************************
******************************/
DESIGN_MANAGER::~DESIGN_MANAGER()
{
#ifdef LOG_DIRECT_FILTER
	fclose(fp_debug);
#endif
	
	delete [] Weight_BlockGrouping_id;
	delete [] Weight_StrobeColorCombination_id;
	delete [] Weight_ColorCombination_id;
}

/******************************
******************************/
void DESIGN_MANAGER::setup()
{
	dmx.setup();
}

/******************************
******************************/
void DESIGN_MANAGER::exit()
{
	dmx.exit();
}

/******************************
******************************/
void DESIGN_MANAGER::Escape_StateChart()
{
	b_StateChart = false;
	State = STATE_ESCAPE;
}

/******************************
******************************/
void DESIGN_MANAGER::Start_StateChart()
{
	b_StateChart = true;
}

/******************************
******************************/
void DESIGN_MANAGER::update_GuiParam(float _LPF_Direct_NumLeds_ThreshSec, float _LPF_Direct_NumWaves_ThreshSec)
{
	LPF_Direct_NumLeds_ThreshSec	= _LPF_Direct_NumLeds_ThreshSec;
	LPF_Direct_NumWaves_ThreshSec	= _LPF_Direct_NumWaves_ThreshSec;
}

/******************************
******************************/
void DESIGN_MANAGER::update(double vol, double Vol_thresh_L, double Vol_thresh_H, double Vol_thresh_P_L, double Vol_thresh_P_H, double Vol_Map_L, double Vol_Map_H)
{
	/********************
	********************/
	t_now = ofGetElapsedTimef();
	
	/********************
	********************/
	LevSync = ofMap(vol, Vol_Map_L, Vol_Map_H, 0.04, 1.0, true);
	
	fix_sync_maxColor(vol, Vol_Map_L, Vol_Map_H);
	
	double LedNumSync_Raw	= ofMap(vol, Vol_Map_L, Vol_Map_H, 0, NUM_DESIGN_LEDS, true);
	LedNumSync = get_FilterOut(LedNumSync, LedNumSync_Raw, LPF_Direct_NumLeds_ThreshSec, t_now - t_LastINT);
#ifdef LOG_DIRECT_FILTER
	if(DesignCategory == DESIGN__NUM_LEDS) fprintf(fp_debug, "%f,%f,%f\n", t_now, LedNumSync_Raw, LedNumSync);
#endif
	
	/********************
	********************/
	StateChart(vol, Vol_thresh_L, Vol_thresh_H, Vol_thresh_P_L, Vol_thresh_P_H);
	
	/********************
	********************/
	update_SafetyLight();
	
	// update_DesignLight(vol, Vol_Map_L, Vol_Map_H);
	update_DesignLight(vol, Vol_thresh_P_L, Vol_Map_H); // あえて、Vol_thresh_P_L をMap_Lとして使用.
	
	/********************
	********************/
	for(int i = 0; i < NUM_DESIGN_LEDS; i++){
		DesignLight[i].LedParam += BoostColorForSmoothAnimation;
	}
	
	/********************
	********************/
	t_LastINT = t_now;
}

/******************************
******************************/
double DESIGN_MANAGER::get_FilterOut(double Last, double Raw, double thresh_sec, double dt)
{
	if( (thresh_sec == 0) || (thresh_sec <= dt) ){
		return Raw;
	}else{
		double k = 1 / thresh_sec * dt;
		return (1 - k) * Last + k * Raw;
	}
}

/******************************
******************************/
void DESIGN_MANAGER::update_SafetyLight()
{
	if(State != STATE_ESCAPE){
		for(int i = 0; i < NUM_SAFETY_LEDS; i++){
			COLOR_SURFACE ColorSurface = SafetyLight[i].ColorSurface;
			LED_PARAM LedParam = ColorCombination[ColorCombination_id].Combination[ ColorSurface ].Color_SafetyLight;
			
			SafetyLight[i].LedParam = LedParam * Fader_SafetyLight.k;
		}
	}
}

/******************************
******************************/
void DESIGN_MANAGER::update_DesignLight(double vol, double Vol_Map_L, double Vol_Map_H)
{
	switch(State){
		case STATE_ESCAPE:
			/********************
			nothing.
			when this mode, system output test value(set in GUI).
			********************/
			break;
			
		case STATE_WAIT:
			update_DesignLight_wait();
			break;
			
		case STATE_RUN__VOLSYNC:
		case STATE_RUN__PATTERN:
		case STATE_ECHO:
			update_DesignLight_Run_Echo(vol, Vol_Map_L, Vol_Map_H);
			break;
			
		case STATE_CALM:
			update_DesignLight_calm();
			break;
			
		default:
			break;
	}
}

/******************************
******************************/
void DESIGN_MANAGER::update_DesignLight_Run_Echo(double vol, double Vol_Map_L, double Vol_Map_H)
{
	switch(DesignCategory){
		case DESIGN__LEV_MIC_SYNC:
			update_DesignLight_Run_Echo__LevSync();
			break;
			
		case DESIGN__PATTERN:
			update_DesignLight_Run_Echo__Pattern(vol, Vol_Map_L, Vol_Map_H);
			break;
			
		case DESIGN__ALL_ON:
			update_DesignLight_Run_Echo__AllOn();
			break;
			
		case DESIGN__NUM_LEDS:
			update_DesignLight_Run_Echo__NumLeds();
			break;
			
		default:
			break;
	}
}

/******************************
******************************/
void DESIGN_MANAGER::update_DesignLight_Run_Echo__LevSync()
{
	for(int i = 0; i < NUM_DESIGN_LEDS; i++){
		/********************
		********************/
		COLOR_SURFACE ColorSurface = DesignLight[i].ColorSurface;
		
		LED_PARAM Color_calm = CalmColor_max[ColorSurface];
		LED_PARAM Dynamic = ColorCombination[ColorCombination_id].Combination[ ColorSurface ].Color_0 * LevSync;
		
		/********************
		********************/
		int R = Dynamic.get_R();
		int G = Dynamic.get_G();
		int B = Dynamic.get_B();
		
		if(0 < R){
			R = int(R + DesignLight[i].Noise_Run_LevSync.get_SignedNoise_Fade(Fader_DesignLight.k, t_now));
			if(R <= 0) R = 1;
		}
		if(0 < G){
			G = int(G + DesignLight[i].Noise_Run_LevSync.get_SignedNoise_Fade(Fader_DesignLight.k, t_now));
			if(G <= 0) G = 1;
		}
		if(0 < B){
			B = int(B + DesignLight[i].Noise_Run_LevSync.get_SignedNoise_Fade(Fader_DesignLight.k, t_now));
			if(B <= 0) B = 1; 
		}
		
		Dynamic = LED_PARAM(R, G, B);
		
		/********************
		********************/
		DesignLight[i].LedParam = Color_calm * (1 - Fader_DesignLight.k) + Dynamic * (Fader_DesignLight.k);
	}
}

/******************************
******************************/
void DESIGN_MANAGER::calProgress(BLOCK& Block, double t_now, double Duration)
{
	Block.Progress += 100 * ((t_now - Block.t_From) / Duration);
	
	Block.t_From = t_now;

	if(100 < Block.Progress){
		Block.Progress -= 100;
		
		Block.Progress_id++;
		if(Bp[Block.Bp_Pattern_id].ShortPattern_Param[Block.Progress_id].pShortPattern == NULL){
			Block.Progress_id = 0;
		}
		
		Dice_LogicalId(&Block);
		
		if( Bp[Block.Bp_Pattern_id].BlankProbability == 0 ){
			Block.b_Blank = false;
		}else{
			int RandomNumber = (int)( ((double)rand() / ((double)RAND_MAX + 1)) * (Bp[Block.Bp_Pattern_id].BlankProbability) );
			
			if(Bp[Block.Bp_Pattern_id].BlankProbability - 1 <= RandomNumber){
				Block.b_Blank = true;
			}else{
				Block.b_Blank = false;
			}
		}
	}
}

/******************************
******************************/
void DESIGN_MANAGER::update_DesignLight_Run_Echo__Pattern(double vol, double Vol_Map_L, double Vol_Map_H)
{
	/********************
	********************/
	for(int i = 0; i < NUM_DESIGN_LEDS; i++){
		COLOR_SURFACE ColorSurface = DesignLight[i].ColorSurface;
		LED_PARAM Color_calm = CalmColor_max[ColorSurface];
		
		DesignLight[i].LedParam = Color_calm * (1 - Fader_DesignLight.k);
	}
	
	/********************
	********************/
	for( int i = 0; !IsPeriodOfBlockGroup(BlockGrouping[BlockGrouping_id].Block[i]); i++ ){
		const int Bp_pattern_id = BlockGrouping[BlockGrouping_id].Block[i].Bp_Pattern_id;
		int &Progress_id = BlockGrouping[BlockGrouping_id].Block[i].Progress_id;
		double& NumWavesInSpace = BlockGrouping[BlockGrouping_id].Block[i].NumWavesInSpace;
		
		double Duration = ofMap(vol, Vol_Map_L, Vol_Map_H, Bp[Bp_pattern_id].Duration_From, Bp[Bp_pattern_id].Duration_To, true);
		calProgress(BlockGrouping[BlockGrouping_id].Block[i], t_now, Duration);
		
		int _NumLogicalChs;
		if(BlockGrouping[BlockGrouping_id].Block[i].b_Blank){
			_NumLogicalChs = 0;
		}else{
			if(Bp[Bp_pattern_id].b_ValidCh_VolSync)	_NumLogicalChs = int( ofMap(vol, Vol_Map_L, Vol_Map_H, Bp[Bp_pattern_id].NUM_LOGICAL_CHS / 5, Bp[Bp_pattern_id].NUM_LOGICAL_CHS * 0.8, true) );
			else									_NumLogicalChs = Bp[Bp_pattern_id].NUM_LOGICAL_CHS;
		}
		
		double NumWavesInSpace_Raw = ofMap(vol, Vol_Map_L, Vol_Map_H, Bp[Bp_pattern_id].NumWaves_inSpace_From, Bp[Bp_pattern_id].NumWaves_inSpace_To, true);
		NumWavesInSpace = get_FilterOut(NumWavesInSpace, NumWavesInSpace_Raw, LPF_Direct_NumWaves_ThreshSec, t_now - t_LastINT);
		
#ifdef LOG_DIRECT_FILTER
		if( (DesignCategory == DESIGN__PATTERN) && (strcmp(BlockGrouping[BlockGrouping_id].BlockName, "SIN") == 0) ){
			fprintf(fp_debug, "%d,%f,%f,%f\n", i, t_now, NumWavesInSpace_Raw, NumWavesInSpace);
		}
#endif
		
		/********************
		********************/
		for(int j = 0; j < Bp[Bp_pattern_id].NUM_LOGICAL_CHS; j++){
			/********************
			********************/
			double Progress;
			if(j < _NumLogicalChs)	{ Progress = BlockGrouping[BlockGrouping_id].Block[i].Progress; }
			else					{ Progress = 100; } // Block[]内のProgressは進んでいくが、pShortPattern()に渡すProgressは、100%で止まり、Blank明けを待つ.

			int Nth = BlockGrouping[BlockGrouping_id].Block[i].LogicalId[j];
			// double Lev = Bp[Bp_pattern_id].ShortPattern_Param[Progress_id].pShortPattern(Progress, Bp[Bp_pattern_id].NUM_LOGICAL_CHS, Nth, NumWavesInSpace);
			double Lev = Bp[Bp_pattern_id].ShortPattern_Param[Progress_id].pShortPattern(Progress, Bp[Bp_pattern_id].NUM_LOGICAL_CHS, j, NumWavesInSpace);
			
			/********************
			********************/
			LED_PARAM Dynamic[NUM_COLOR_SURFACES];
			LED_PARAM Color_max;
			for(int surface = 0; surface < NUM_COLOR_SURFACES; surface++){
				switch(BlockGrouping[BlockGrouping_id].Block[i].f_ColorBar){
					case F_COLORBAR_SYNC:
						Color_max = ColorCombination[ColorCombination_id].Combination[ surface ].maxColor;
						break;
					case F_COLORBAR_COL0:
						Color_max = ColorCombination[ColorCombination_id].Combination[ surface ].Color_0;
						break;
					case F_COLORBAR_COL1:
						Color_max = ColorCombination[ColorCombination_id].Combination[ surface ].Color_1;
						break;
					case F_COLORBAR_STROBE:
						Color_max = StrobeColorCombination[StrobeColorCombination_id].Color[ surface ];
						break;
					default:
						Color_max = ColorCombination[ColorCombination_id].Combination[ surface ].maxColor;
						break;
				}
				Dynamic[surface] = Color_max * Lev * Fader_DesignLight.k;
			}
			
			/********************
			********************/
			for(int k = 0; k < BlockGrouping[BlockGrouping_id].Block[i].LogicalCh[Nth].size(); k++){
				int Led_physical_id = BlockGrouping[BlockGrouping_id].Block[i].LogicalCh[Nth][k];
				
				COLOR_SURFACE ColorSurface = DesignLight[Led_physical_id].ColorSurface;
				DesignLight[Led_physical_id].LedParam += Dynamic[ColorSurface];
			}
		}
	}
}

/******************************
******************************/
void DESIGN_MANAGER::update_DesignLight_Run_Echo__AllOn()
{
	for(int i = 0; i < NUM_DESIGN_LEDS; i++){
		/********************
		********************/
		COLOR_SURFACE ColorSurface = DesignLight[i].ColorSurface;
		
		LED_PARAM Color_calm = CalmColor_max[ColorSurface];
		LED_PARAM Dynamic = ColorCombination[ColorCombination_id].Combination[ ColorSurface ].maxColor;
		
		/********************
		********************/
		int R = Dynamic.get_R();
		int G = Dynamic.get_G();
		int B = Dynamic.get_B();
		
		if(0 < R){
			R = int(R + DesignLight[i].Noise_Run_LevSync.get_SignedNoise_Fade(Fader_DesignLight.k, t_now, 0 * 100));
			if(R <= 0) R = 1;
		}
		if(0 < G){
			G = int(G + DesignLight[i].Noise_Run_LevSync.get_SignedNoise_Fade(Fader_DesignLight.k, t_now, 1 * 100));
			if(G <= 0) G = 1;
		}
		if(0 < B){
			B = int(B + DesignLight[i].Noise_Run_LevSync.get_SignedNoise_Fade(Fader_DesignLight.k, t_now, 2 * 100));
			if(B <= 0) B = 1; 
		}
		
		Dynamic = LED_PARAM(R, G, B);
		
		/********************
		********************/
		DesignLight[i].LedParam = Color_calm * (1 - Fader_DesignLight.k) + Dynamic * (Fader_DesignLight.k);
	}
}

/******************************
******************************/
void DESIGN_MANAGER::update_DesignLight_Run_Echo__NumLeds()
{
	for(int i = 0; i < NUM_DESIGN_LEDS; i++){
		COLOR_SURFACE ColorSurface = DesignLight[i].ColorSurface;
		DesignLight[i].LedParam = ColorCombination[ColorCombination_id].Combination[i].Color_calm; // no fade.
	}
	
	for(int i = 0; i < int(LedNumSync); i++){
		int LedId = LedId_ExchangeTable_NumSync[i];
	
		COLOR_SURFACE ColorSurface = DesignLight[LedId].ColorSurface;
		LED_PARAM Dynamic = ColorCombination[ColorCombination_id].Combination[ ColorSurface ].maxColor;
		
		DesignLight[LedId].LedParam += Dynamic * (Fader_DesignLight.k);
	}
}

/******************************
******************************/
void DESIGN_MANAGER::update_DesignLight_calm()
{
	for(int i = 0; i < NUM_DESIGN_LEDS; i++){
		COLOR_SURFACE ColorSurface = DesignLight[i].ColorSurface;
		LED_PARAM LedParam = CalmColor_max[ColorSurface] * Fader_DesignLight.k;
		
		DesignLight[i].LedParam = LedParam;
	}
}

/******************************
******************************/
void DESIGN_MANAGER::update_DesignLight_wait()
{
	for(int i = 0; i < NUM_DESIGN_LEDS; i++){
		/********************
		********************/
		COLOR_SURFACE ColorSurface = DesignLight[i].ColorSurface;
		
		int R = CalmColor_max[ColorSurface].get_R();
		int G = CalmColor_max[ColorSurface].get_G();
		int B = CalmColor_max[ColorSurface].get_B();
		
		if(0 < R){
			R = int(R + DesignLight[i].Noise_Calm.get_Noise(t_now));
			if(R <= 0) R = 1;
		}
		if(0 < G){
			G = int(G + DesignLight[i].Noise_Calm.get_Noise(t_now));
			if(G <= 0) G = 1;
		}
		if(0 < B){
			B = int(B + DesignLight[i].Noise_Calm.get_Noise(t_now));
			if(B <= 0) B = 1;
		}
		
		DesignLight[i].LedParam = LED_PARAM(R, G, B) * Fader_DesignLight.k;
	}
}

/******************************
******************************/
void DESIGN_MANAGER::StateChart(double vol, double Vol_thresh_L, double Vol_thresh_H, double Vol_thresh_P_L, double Vol_thresh_P_H)
{
	enum SUB_STATE_RUN{
		SUB_STATE_RUN__VOL_WITHIN_RANGE,
		SUB_STATE_RUN__VOL_RANGE_OVER,
	};
	static SUB_STATE_RUN SubState_Run;
	
	switch(State){
		case STATE_ESCAPE:
			if( b_StateChart && (vol < Vol_thresh_L) ){
				State = STATE_WAIT;
				Transition__to_WAIT();
				
				Fader_SafetyLight.k = 0;
			}
			break;
			
		case STATE_WAIT:
			Fader_SafetyLight.update_Up(t_now - t_LastINT);
			Fader_DesignLight.update_Up(t_now - t_LastINT);
			
			if(Vol_thresh_H < vol){
				State = STATE_RUN__VOLSYNC;
				Transition__to_RUN_VolSync();
				SubState_Run = SUB_STATE_RUN__VOL_WITHIN_RANGE; // 関数内staticなので、Transition__to_RUN()でなく、こちらで処理.
			}
			break;
			
		case STATE_RUN__VOLSYNC:
			/********************
			********************/
			Fader_SafetyLight.update_Down(t_now - t_LastINT);
			Fader_DesignLight.update_Up(t_now - t_LastINT);
			
			/********************
			********************/
			switch(SubState_Run){
				case SUB_STATE_RUN__VOL_WITHIN_RANGE:
					if(NUM_DESIGN_LEDS <= LedNumSync){
						if(DesignCategory == DESIGN__NUM_LEDS) { Dice_LedId_NumLeds_Sync(); }
						SubState_Run = SUB_STATE_RUN__VOL_RANGE_OVER;
					}
					break;
					
				case SUB_STATE_RUN__VOL_RANGE_OVER:
					if(LedNumSync < NUM_DESIGN_LEDS){
						SubState_Run = SUB_STATE_RUN__VOL_WITHIN_RANGE;
					}
					break;
			}
			
			/********************
			********************/
			if( (Vol_thresh_P_H < vol) && b_DesignPattern ){
				State = STATE_RUN__PATTERN;
				Transition__to_RUN_Pattern();
				
			}else if(vol < Vol_thresh_L){
				State = STATE_ECHO;
				for(int i = 0; i < NUM_COLOR_SURFACES; i++) { CalmColor_max[i] = LED_PARAM(0, 0, 0); }
				Fader_DesignLight.set(5.0, false);
			}
			break;
			
		case STATE_RUN__PATTERN:
		{
			/********************
			********************/
			Fader_SafetyLight.update_Down(t_now - t_LastINT);
			
			if(SubState_RunPattern == SUB_STATE_RUN_PATTERN__FADE_UP)	Fader_DesignLight.update_Up(t_now - t_LastINT);
			else														Fader_DesignLight.update_Down(t_now - t_LastINT);
			
			/********************
			********************/
			const double threshTime = 20.0;
			
			if(vol < Vol_thresh_L){
				State = STATE_ECHO;
				for(int i = 0; i < NUM_COLOR_SURFACES; i++) { CalmColor_max[i] = LED_PARAM(0, 0, 0); }
				Fader_DesignLight.set(5.0, false);
				
			}else if(Fader_DesignLight.k <= 0){
				State = STATE_RUN__VOLSYNC;
				for(int i = 0; i < NUM_COLOR_SURFACES; i++) { CalmColor_max[i] = LED_PARAM(0, 0, 0); }
				Fader_DesignLight.set(1.0, false);
				
				DesignCategory = DESIGN__LEV_MIC_SYNC;
				
				if(threshTime < t_now - t_Pattern_From) { b_DesignPattern = false; }
			}
			
			/* */
			switch(SubState_RunPattern){
				case SUB_STATE_RUN_PATTERN__FADE_UP:
					if( (vol < Vol_thresh_P_L) || (threshTime < t_now - t_Pattern_From) ){
						for(int i = 0; i < NUM_COLOR_SURFACES; i++) { CalmColor_max[i] = LED_PARAM(0, 0, 0); }
						Fader_DesignLight.set(2.0, false);
						SubState_RunPattern = SUB_STATE_RUN_PATTERN__FADE_DOWN;
					}
					break;
				case SUB_STATE_RUN_PATTERN__FADE_DOWN:
					if( (Vol_thresh_P_H < vol) && (t_now - t_Pattern_From <= threshTime) ){
						SubState_RunPattern = SUB_STATE_RUN_PATTERN__FADE_UP;
					}
					break;
			}
		}
			break;
			
		case STATE_ECHO:
			Fader_SafetyLight.update_Down(t_now - t_LastINT);
			Fader_DesignLight.update_Down(t_now - t_LastINT);
			
			if(Vol_thresh_L < vol){
				if(DesignCategory == DESIGN__PATTERN)	{ State = STATE_RUN__PATTERN; }
				else									{ State = STATE_RUN__VOLSYNC; }
				
				Fader_DesignLight.set(0.5, false);
				
			}else if(Fader_DesignLight.k <= 0){
				State = STATE_CALM;
				t_calm_From = t_now;
			}
			break;
			
		case STATE_CALM:
		{
			Fader_SafetyLight.update_Down(t_now - t_LastINT);
			// Fader_DesignLight: no touch.
			
			const double threshTime = 2.0;
			
			if(Vol_thresh_H < vol){
				State = STATE_RUN__VOLSYNC;
				Transition__to_RUN_VolSync();
				if(b_DesignPattern){
					DesignCategory = DESIGN__LEV_MIC_SYNC;
				}
				
				SubState_Run = SUB_STATE_RUN__VOL_WITHIN_RANGE; // 関数内staticなので、Transition__to_RUN()でなく、こちらで処理.
				
			}else if(threshTime < t_now - t_calm_From){
				State = STATE_WAIT;
				Transition__to_WAIT();
			}
		}
			break;
			
		default:
			break;
	}
}

/******************************
******************************/
void DESIGN_MANAGER::Transition__to_WAIT()
{
	/********************
	********************/
	b_DesignPattern = false;
	
	/********************
	********************/
	Dice_DesignCategory();
	
	if(DesignCategory == DESIGN__PATTERN){
		Dice_BlockGrouping_id();
		
		/* 時間差 設定 */
		b_DesignPattern = true;
		DesignCategory = DESIGN__LEV_MIC_SYNC;
		
	}else if(DesignCategory == DESIGN__NUM_LEDS){
		Dice_LedId_NumLeds_Sync();
	}
	
	Dice_ColorCombination();
	for(int i = 0; i < NUM_COLOR_SURFACES; i++){
		CalmColor_max[i] = ColorCombination[ColorCombination_id].Combination[i].Color_calm;
	}
	
	Fader_DesignLight.set(2.0, true);
	
	/********************
	********************/
	LedNumSync = 0;
	
	for( int i = 0; !IsPeriodOfBlockGroup(BlockGrouping[BlockGrouping_id].Block[i]); i++ ){
		const int Bp_pattern_id = BlockGrouping[BlockGrouping_id].Block[i].Bp_Pattern_id;
		BlockGrouping[BlockGrouping_id].Block[i].NumWavesInSpace = Bp[Bp_pattern_id].NumWaves_inSpace_From;
	}
}

/******************************
******************************/
void DESIGN_MANAGER::Transition__to_RUN_VolSync()
{
	for(int i = 0; i < NUM_COLOR_SURFACES; i++){
		CalmColor_max[i] = CalmColor_max[i] * Fader_DesignLight.k;
	}
	
	Fader_DesignLight.set(0.5, true);
}

/******************************
******************************/
void DESIGN_MANAGER::Transition__to_RUN_Pattern()
{
	DesignCategory = DESIGN__PATTERN;
	
	for( int i = 0; !IsPeriodOfBlockGroup(BlockGrouping[BlockGrouping_id].Block[i]); i++ ){
		BlockGrouping[BlockGrouping_id].Block[i].t_From = t_now;
		BlockGrouping[BlockGrouping_id].Block[i].Progress = 0;
		BlockGrouping[BlockGrouping_id].Block[i].b_Blank = false;
		
		Dice_LogicalId(&BlockGrouping[BlockGrouping_id].Block[i]);
	}
	
	t_Pattern_From = t_now;
	SubState_RunPattern = SUB_STATE_RUN_PATTERN__FADE_UP;
}

/******************************
description
	fisher yates法
	偏りをなくすため、回を追うごとに乱数範囲を狭めていくのがコツ
	http://www.fumiononaka.com/TechNotes/Flash/FN0212003.html
******************************/
void DESIGN_MANAGER::Dice_LogicalId(BLOCK* block)
{
	/********************
	********************/
	for(int i = 0; i < MAX_LOGICAL_CHS; i++){
		block->LogicalId[i] = i;
	}
	
	/********************
	********************/
	if( Bp[block->Bp_Pattern_id].b_LogicalID_Random ){
		int i = Bp[block->Bp_Pattern_id].NUM_LOGICAL_CHS;
		
		while(i--){
			// int j = rand() % (i + 1);
			int j = (int)( ((double)rand() / ((double)RAND_MAX + 1)) * (i + 1) );
			
			int temp = block->LogicalId[i];
			block->LogicalId[i] = block->LogicalId[j];
			block->LogicalId[j] = temp;
		}
	}
}

/******************************
description
	fisher yates法
	偏りをなくすため、回を追うごとに乱数範囲を狭めていくのがコツ
	http://www.fumiononaka.com/TechNotes/Flash/FN0212003.html
******************************/
void DESIGN_MANAGER::Dice_LedId_NumLeds_Sync()
{
	int i= NUM_DESIGN_LEDS;
	
	while(i--){
		// int j = rand() % (i + 1);
		int j = (int)( ((double)rand() / ((double)RAND_MAX + 1)) * (i + 1) );
		
		int temp = LedId_ExchangeTable_NumSync[i];
		LedId_ExchangeTable_NumSync[i] = LedId_ExchangeTable_NumSync[j];
		LedId_ExchangeTable_NumSync[j] = temp;
	}
}

/******************************
******************************/
void DESIGN_MANAGER::Dice_ColorCombination()
{
	ColorCombination_id = Dice_index( Weight_ColorCombination_id, NUM_COLOR_COMBINATIONS );
	StrobeColorCombination_id = Dice_index( Weight_StrobeColorCombination_id, NUM_STROBE_COLOR_COMBINATIONS );
}

/******************************
******************************/
void DESIGN_MANAGER::Dice_DesignCategory()
{
	if( (argin_DesignCategory != -1) && (NUM__DESIGN_CATEGORIES <= argin_DesignCategory) ){
		printf("> Design Category:Out of range -> Dice\n");
		argin_DesignCategory = -1;
	}
	
	if( (argin_DesignCategory != -1) && (argin_DesignCategory < NUM__DESIGN_CATEGORIES) ){
		DesignCategory = (DESIGN_CATEGORY)argin_DesignCategory;
		
	}else{
		if(NUM__DESIGN_CATEGORIES != sizeof(W_DesignCategory)/sizeof(W_DesignCategory[0])){
			ERROR_MSG(); std::exit(1);
		}
		
		DesignCategory = (DESIGN_CATEGORY)Dice_index( W_DesignCategory, NUM__DESIGN_CATEGORIES );
	}
}

/******************************
******************************/
void DESIGN_MANAGER::Dice_BlockGrouping_id()
{
	if( (argin_BlockGrouping_id != -1) && (NUM_GROUPTYPES <= argin_BlockGrouping_id) ){
		printf("> BlockGrouping id:Out of range -> Dice\n");
		argin_BlockGrouping_id = -1;
	}
	
	if( (argin_BlockGrouping_id != -1) && (argin_BlockGrouping_id < NUM_GROUPTYPES) ){
		BlockGrouping_id = argin_BlockGrouping_id;
		
	}else{
		BlockGrouping_id = Dice_index(Weight_BlockGrouping_id, NUM_GROUPTYPES);
	}
	
	for( int i = 0; !IsPeriodOfBlockGroup(BlockGrouping[BlockGrouping_id].Block[i]); i++ ){
		BlockGrouping[BlockGrouping_id].Block[i].Progress_id = 0;
	}
}

/******************************
******************************/
void DESIGN_MANAGER::fix_sync_maxColor(double vol, double Vol_Map_L, double Vol_Map_H)
{
	for(int surface = 0; surface < int(NUM_COLOR_SURFACES); surface++){
		double ColorBarRatio =  ofMap(vol, Vol_Map_L, Vol_Map_H, 0, 1.0, true);
		
		const LED_PARAM *ColorFrom;
		const LED_PARAM *ColorTo;
			
		if(ColorBarRatio < 0.5){
			ColorBarRatio *= 2; // 0 - 0.5 to 0 - 1.0
			
			ColorFrom	= &ColorCombination[ColorCombination_id].Combination[surface].Color_0;
			ColorTo		= &ColorCombination[ColorCombination_id].Combination[surface].Color_05;
			
		}else{
			ColorBarRatio = (ColorBarRatio - 0.5) * 2; // 0.5 - 1.0 to 0 - 1.0
			
			ColorFrom	= &ColorCombination[ColorCombination_id].Combination[surface].Color_05;
			ColorTo		= &ColorCombination[ColorCombination_id].Combination[surface].Color_1;
		}
		
		int R = int((1 - ColorBarRatio) * ColorFrom->get_R() + ColorBarRatio * ColorTo->get_R());
		int G = int((1 - ColorBarRatio) * ColorFrom->get_G() + ColorBarRatio * ColorTo->get_G());
		int B = int((1 - ColorBarRatio) * ColorFrom->get_B() + ColorBarRatio * ColorTo->get_B());

		ColorCombination[ColorCombination_id].Combination[surface].maxColor = LED_PARAM(R, G, B);
	}
}

/******************************
******************************/
int DESIGN_MANAGER::Dice_index(int *Weight, int NUM)
{
	/***********************
	cal sum of Weight
	***********************/
	int TotalWeight = 0;
	int i;
	for(i = 0; i < NUM; i++){
		TotalWeight += Weight[i];
	}
	
	if(TotalWeight == 0) { ERROR_MSG(); std::exit(1); }
	
	/***********************
	random number
	***********************/
	// int RandomNumber = rand() % TotalWeight;
	int RandomNumber = (int)( ((double)rand() / ((double)RAND_MAX + 1)) * (TotalWeight) );
	
	/***********************
	define play mode
	***********************/
	int index;
	for(TotalWeight = 0, index = 0; /* */; index++){
		TotalWeight += Weight[index];
		if(RandomNumber < TotalWeight) break;
	}
	
	return index;
}

/******************************
******************************/
void DESIGN_MANAGER::draw_Infos()
{
	/********************
	********************/
	char buf[BUF_SIZE];
	char add_buf[BUF_SIZE];
	
	/********************
	********************/
	switch(State){
		case STATE_ESCAPE:
			sprintf(buf, "> STATE_ESCAPE\n");
			break;
		case STATE_WAIT:
			sprintf(buf, "> STATE_WAIT\n");
			break;
		case STATE_RUN__VOLSYNC:
			sprintf(buf, "> STATE_RUN__VOLSYNC\n");
			break;
		case STATE_RUN__PATTERN:
			if(SubState_RunPattern == SUB_STATE_RUN_PATTERN__FADE_DOWN) sprintf(buf, "> STATE_RUN__PATTERN(Fade Down)\n");
			else														sprintf(buf, "> STATE_RUN__PATTERN\n");
			break;
		case STATE_ECHO:
			sprintf(buf, "> STATE_ECHO\n");
			break;
		case STATE_CALM:
			sprintf(buf, "> STATE_CALM\n");
			break;
		default:
			sprintf(buf, "> XXXXXXXXXX\n");
			break;
	}
	
	/********************
	********************/
	sprintf(add_buf, "%-20s= %.2f\n%-20s= %.2f\n", "Design k", Fader_DesignLight.k, "Safety k", Fader_SafetyLight.k);
	strcat(buf, add_buf);
	
	/********************
	********************/
	sprintf(add_buf, "%-20s= %d (%s)\n", "ColorCombination_id", ColorCombination_id, ColorCombination[ColorCombination_id].Name.c_str());
	strcat(buf, add_buf);
	
	sprintf(add_buf, "%-20s= (%4d,%4d,%4d)/(%4d,%4d,%4d)\n",	"Fix:StrobeColor", 
																StrobeColorCombination[StrobeColorCombination_id].Color[COLOR_FROM_RESTAURANT].get_R(),
																StrobeColorCombination[StrobeColorCombination_id].Color[COLOR_FROM_RESTAURANT].get_G(),
																StrobeColorCombination[StrobeColorCombination_id].Color[COLOR_FROM_RESTAURANT].get_B(),
																StrobeColorCombination[StrobeColorCombination_id].Color[COLOR_FROM_ENTRANCE].get_R(),
																StrobeColorCombination[StrobeColorCombination_id].Color[COLOR_FROM_ENTRANCE].get_G(),
																StrobeColorCombination[StrobeColorCombination_id].Color[COLOR_FROM_ENTRANCE].get_B() 
																);
	strcat(buf, add_buf);
	
	/********************
	********************/
	sprintf(add_buf, "%-20s= ", "LedExchange");
	for(int i = 0; i < NUM_DESIGN_LEDS; i++){
		if(i % 10 == 0) strcat(add_buf, "\n");
		
		char add2[BUF_SIZE];
		sprintf(add2, "%4d, ", LedId_ExchangeTable_NumSync[i]);
		strcat(add_buf, add2);
	}
	strcat(add_buf, "\n\n");
	strcat(buf, add_buf);
	
	/********************
	********************/
	switch(DesignCategory){
		case DESIGN__LEV_MIC_SYNC:
			if(b_DesignPattern){
				sprintf(add_buf, "%-20s= DESIGN__LEV_MIC_SYNC (-> DESIGN__PATTERN : %s)\n", "DesignCategory", BlockGrouping[BlockGrouping_id].BlockName);
			}else{
				sprintf(add_buf, "%-20s= DESIGN__LEV_MIC_SYNC\n", "DesignCategory");
			}
			break;
		case DESIGN__PATTERN:
			sprintf(add_buf, "%-20s= DESIGN__PATTERN\n%-20s= %s\n", "DesignCategory", "BlockName", BlockGrouping[BlockGrouping_id].BlockName);
			break;
		case DESIGN__ALL_ON:
			sprintf(add_buf, "%-20s= DESIGN__ALL_ON\n", "DesignCategory");
			break;
		case DESIGN__NUM_LEDS:
			sprintf(add_buf, "%-20s= DESIGN__NUM_LEDS\n", "DesignCategory");
			break;
		default:
			break;
	}
	strcat(buf, add_buf);

	/********************
	********************/
	ofSetColor(ofColor::white);
	ofDrawBitmapString(buf, 250, 60);
}

/******************************
******************************/
void DESIGN_MANAGER::draw_ColorInfos()
{
	/********************
	********************/
	int ofs_x = 900;
	int ofs_y = 60;
	int Bar_W = 200;
	int Bar_H = 10;
	int space_y = 30;
	int space_x = Bar_W/2;
	int radius = 8;
	int radius_Strobe = 6;
	
	/********************
	********************/
	ofSetColor(255, 255, 255, 80);
	ofDrawRectangle(ofs_x, ofs_y, Bar_W, Bar_H);
	
	ofSetColor(0, 255, 255, 80);
	int LevSync_Bar_W = ofMap(LevSync, 0, 1.0, 0, Bar_W, true);
	ofDrawRectangle(ofs_x, ofs_y, LevSync_Bar_W, Bar_H);
	
	ofSetColor(	ColorCombination[ColorCombination_id].Combination[COLOR_FROM_RESTAURANT].Color_0.get_R(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_RESTAURANT].Color_0.get_G(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_RESTAURANT].Color_0.get_B(),
				255);
	ofDrawCircle(ofs_x + space_x * 0, ofs_y + space_y * 1, radius);
	
	ofSetColor(	ColorCombination[ColorCombination_id].Combination[COLOR_FROM_RESTAURANT].Color_05.get_R(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_RESTAURANT].Color_05.get_G(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_RESTAURANT].Color_05.get_B(),
				255);
	ofDrawCircle(ofs_x + space_x * 1, ofs_y + space_y * 1, radius);
	
	ofSetColor(	ColorCombination[ColorCombination_id].Combination[COLOR_FROM_RESTAURANT].Color_1.get_R(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_RESTAURANT].Color_1.get_G(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_RESTAURANT].Color_1.get_B(),
				255);
	ofDrawCircle(ofs_x + space_x * 2, ofs_y + space_y * 1, radius);
	
	ofSetColor(	ColorCombination[ColorCombination_id].Combination[COLOR_FROM_RESTAURANT].maxColor.get_R(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_RESTAURANT].maxColor.get_G(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_RESTAURANT].maxColor.get_B(),
				255);
	ofDrawCircle(ofs_x + space_x * 3, ofs_y + space_y * 1, radius);
	
	{
		LED_PARAM color = ColorCombination[ColorCombination_id].Combination[COLOR_FROM_RESTAURANT].maxColor * Fader_DesignLight.k + ColorCombination[ColorCombination_id].Combination[COLOR_FROM_RESTAURANT].Color_calm * (1 - Fader_DesignLight.k);
		ofSetColor(	color.get_R(),
					color.get_G(),
					color.get_B(),
					255);
		ofDrawCircle(ofs_x + space_x * 3, ofs_y + space_y * 2, radius);
	}
	
	ofSetColor(	ColorCombination[ColorCombination_id].Combination[COLOR_FROM_RESTAURANT].Color_calm.get_R(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_RESTAURANT].Color_calm.get_G(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_RESTAURANT].Color_calm.get_B(),
				255);
	ofDrawCircle(ofs_x + space_x * 3, ofs_y + space_y * 3, radius);
	
	// strobe
	ofSetColor(	StrobeColorCombination[StrobeColorCombination_id].Color[COLOR_FROM_RESTAURANT].get_R(),
				StrobeColorCombination[StrobeColorCombination_id].Color[COLOR_FROM_RESTAURANT].get_G(),
				StrobeColorCombination[StrobeColorCombination_id].Color[COLOR_FROM_RESTAURANT].get_B(),
				255);
	// ofDrawCircle(ofs_x + space_x * 0, ofs_y + space_y * 2, radius_Strobe);
	ofDrawRectangle(ofs_x + space_x * 0 - radius_Strobe, ofs_y + space_y * 2 - radius_Strobe, radius_Strobe * 2, radius_Strobe * 2);
	
	/********************
	********************/
	ofs_y += space_y * 3;
	ofSetColor(	ColorCombination[ColorCombination_id].Combination[COLOR_FROM_ENTRANCE].Color_0.get_R(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_ENTRANCE].Color_0.get_G(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_ENTRANCE].Color_0.get_B(),
				255);
	ofDrawCircle(ofs_x + space_x * 0, ofs_y + space_y * 1, radius);
	
	ofSetColor(	ColorCombination[ColorCombination_id].Combination[COLOR_FROM_ENTRANCE].Color_05.get_R(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_ENTRANCE].Color_05.get_G(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_ENTRANCE].Color_05.get_B(),
				255);
	ofDrawCircle(ofs_x + space_x * 1, ofs_y + space_y * 1, radius);
	
	ofSetColor(	ColorCombination[ColorCombination_id].Combination[COLOR_FROM_ENTRANCE].Color_1.get_R(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_ENTRANCE].Color_1.get_G(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_ENTRANCE].Color_1.get_B(),
				255);
	ofDrawCircle(ofs_x + space_x * 2, ofs_y + space_y * 1, radius);
	
	ofSetColor(	ColorCombination[ColorCombination_id].Combination[COLOR_FROM_ENTRANCE].maxColor.get_R(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_ENTRANCE].maxColor.get_G(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_ENTRANCE].maxColor.get_B(),
				255);
	ofDrawCircle(ofs_x + space_x * 3, ofs_y + space_y * 1, radius);
	
	{
		LED_PARAM color = ColorCombination[ColorCombination_id].Combination[COLOR_FROM_ENTRANCE].maxColor * Fader_DesignLight.k + ColorCombination[ColorCombination_id].Combination[COLOR_FROM_ENTRANCE].Color_calm * (1 - Fader_DesignLight.k);
		ofSetColor(	color.get_R(),
					color.get_G(),
					color.get_B(),
					255);
		ofDrawCircle(ofs_x + space_x * 3, ofs_y + space_y * 2, radius);
	}
	
	ofSetColor(	ColorCombination[ColorCombination_id].Combination[COLOR_FROM_ENTRANCE].Color_calm.get_R(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_ENTRANCE].Color_calm.get_G(),
				ColorCombination[ColorCombination_id].Combination[COLOR_FROM_ENTRANCE].Color_calm.get_B(),
				255);
	ofDrawCircle(ofs_x + space_x * 3, ofs_y + space_y * 3, radius);
	
	// strobe
	ofSetColor(	StrobeColorCombination[StrobeColorCombination_id].Color[COLOR_FROM_ENTRANCE].get_R(),
				StrobeColorCombination[StrobeColorCombination_id].Color[COLOR_FROM_ENTRANCE].get_G(),
				StrobeColorCombination[StrobeColorCombination_id].Color[COLOR_FROM_ENTRANCE].get_B(),
				255);
	// ofDrawCircle(ofs_x + space_x * 0, ofs_y + space_y * 2, radius_Strobe);
	ofDrawRectangle(ofs_x + space_x * 0 - radius_Strobe, ofs_y + space_y * 2 - radius_Strobe, radius_Strobe * 2, radius_Strobe * 2);
}

/******************************
******************************/
void DESIGN_MANAGER::draw(int test_DesignLight_id, LED_PARAM& test_DesignLight_Color, int test_SafetyLight_id, LED_PARAM& test_SafetyLight_Color)
{
	/***********************
	***********************/
	if(State == STATE_ESCAPE){
		test_DesignLight.LedId = test_DesignLight_id;
		test_DesignLight.LedParam = test_DesignLight_Color;
		
		test_SafetyLight.LedId = test_SafetyLight_id;
		test_SafetyLight.LedParam = test_SafetyLight_Color;
		
		dmx.draw_test(255);
		
	}else{
		dmx.draw(255);
	}
	
	/***********************
	***********************/
	draw_Infos();
	
	if(IsEnable_GuiSimulation()){
		draw_ColorInfos();
	}
}

