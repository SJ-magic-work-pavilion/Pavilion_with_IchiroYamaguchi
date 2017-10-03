/************************************************************
************************************************************/
#include "Design.h"

/************************************************************
param
************************************************************/
static const double calmColor_DarkRatio = 0.3;

COLOR_COMBINATION_SET DESIGN_MANAGER::ColorCombination[] = {
	/*
	COLOR_COMBINATION_SET	(	1,
								LED_PARAM(50, 0, 0), LED_PARAM(200, 0, 0), LED_PARAM(255, 100, 0), LED_PARAM(255, 120, 255), LED_PARAM(255, 255, 255),	// COLOR_FROM_RESTAURANT
							),
	*/
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
};
int DESIGN_MANAGER::NUM_COLOR_COMBINATIONS = sizeof(ColorCombination)/sizeof(ColorCombination[0]);

/******************************
******************************/
int W_DesignCategory[] = {
	1, // DESIGN__LEV_MIC_SYNC,
	3, // DESIGN__PATTERN,
	1, // DESIGN__ALL_ON,
	1, // DESIGN__NUM_LEDS,
};


/************************************************************
func
************************************************************/

/******************************
******************************/
DESIGN_MANAGER::DESIGN_MANAGER()
: LevSync(0)
, SpeedSync(0)
, ColorCombination_id(0)
, LedNumSync(0)
, b_StateChart(true)
, State(STATE_ESCAPE)
, DesignCategory(DESIGN__ALL_ON) // 一応
, BlockGrouping_id(0)
, Fader_DesignLight(4.0)
, Fader_SafetyLight(2.0)
, Fader_CalmColor(Fader_SafetyLight)
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
void DESIGN_MANAGER::update(double vol, double Vol_thresh_L, double Vol_thresh_H, double Vol_Map_L, double Vol_Map_H)
{
	/********************
	********************/
	t_now = ofGetElapsedTimef();
	
	/********************
	********************/
	LevSync		= ofMap(vol, Vol_Map_L, Vol_Map_H, 0, 1.0, true);
	SpeedSync	= ofMap(vol, Vol_Map_L, Vol_Map_H, 1.0, 1.5, true);
	
	fix_sync_maxColor(vol, Vol_Map_L, Vol_Map_H);
	
	double LedNumSync_Raw	= ofMap(vol, Vol_Map_L, Vol_Map_H, 0, NUM_DESIGN_LEDS, true);
	LedNumSync = int( get_FilterOut(LedNumSync, LedNumSync_Raw, LPF_Direct_NumLeds_ThreshSec, t_now - t_LastINT) );
#ifdef LOG_DIRECT_FILTER
	if(DesignCategory == DESIGN__NUM_LEDS) fprintf(fp_debug, "%f,%f,%d\n", t_now, LedNumSync_Raw, LedNumSync);
#endif
	
	/********************
	********************/
	StateChart(vol, Vol_thresh_L, Vol_thresh_H);
	
	/********************
	********************/
	update_SafetyLight();
	update_DesignLight(vol, Vol_Map_L, Vol_Map_H);
	
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
			
		case STATE_CALM:
		case STATE_WAIT:
			update_DesignLight_calm();
			break;
			
		case STATE_RUN:
		case STATE_ECHO:
			update_DesignLight_Run_Echo(vol, Vol_Map_L, Vol_Map_H);
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
		COLOR_SURFACE ColorSurface = DesignLight[i].ColorSurface;
		
		// LED_PARAM Color_calm = ColorCombination[ColorCombination_id].Combination[ ColorSurface ].Color_calm;
		LED_PARAM Color_calm = CalmColor_pre[ColorSurface] * (1 - Fader_CalmColor.k) + ColorCombination[ColorCombination_id].Combination[ ColorSurface ].Color_calm * Fader_CalmColor.k;
		LED_PARAM Dynamic = ColorCombination[ColorCombination_id].Combination[ ColorSurface ].Color_0 * LevSync;
		
		DesignLight[i].LedParam = Color_calm * (1 - Fader_DesignLight.k) + Dynamic * (Fader_DesignLight.k);
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
		// LED_PARAM Color_calm = ColorCombination[ColorCombination_id].Combination[ ColorSurface ].Color_calm;
		LED_PARAM Color_calm = CalmColor_pre[ColorSurface] * (1 - Fader_CalmColor.k) + ColorCombination[ColorCombination_id].Combination[ ColorSurface ].Color_calm * Fader_CalmColor.k;
		
		DesignLight[i].LedParam = Color_calm * (1 - Fader_DesignLight.k);
	}
	
	/********************
	********************/
	for( int i = 0; !IsPeriodOfBlockGroup(BlockGrouping[BlockGrouping_id].Block[i]); i++ ){
		const int Bp_pattern_id = BlockGrouping[BlockGrouping_id].Block[i].Bp_Pattern_id;
		int &Progress_id = BlockGrouping[BlockGrouping_id].Block[i].Progress_id;
		double& NumWavesInSpace = BlockGrouping[BlockGrouping_id].Block[i].NumWavesInSpace;
		
		double Progress = calProgress(t_now, BlockGrouping[BlockGrouping_id].Block[i].t_From, Bp[Bp_pattern_id].Duration, SpeedSync);
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
			double Lev = Bp[Bp_pattern_id].ShortPattern_Param[Progress_id].pShortPattern(Progress, Bp[Bp_pattern_id].NUM_LOGICAL_CHS, j, NumWavesInSpace);
			
			/********************
			********************/
			LED_PARAM Dynamic[NUM_COLOR_SURFACES];
			
			LED_PARAM Color_max = ColorCombination[ColorCombination_id].Combination[ COLOR_FROM_RESTAURANT ].maxColor;
			Dynamic[COLOR_FROM_RESTAURANT] = Color_max * Lev * Fader_DesignLight.k;
			
			/* */
			Color_max = ColorCombination[ColorCombination_id].Combination[ COLOR_FROM_ENTRANCE ].maxColor;
			Dynamic[COLOR_FROM_ENTRANCE] = Color_max * Lev * Fader_DesignLight.k;
			
			/********************
			********************/
			for(int k = 0; k < BlockGrouping[BlockGrouping_id].Block[i].LogicalCh[j].size(); k++){
				int Led_physical_id = BlockGrouping[BlockGrouping_id].Block[i].LogicalCh[j][k];
				
				COLOR_SURFACE ColorSurface = DesignLight[Led_physical_id].ColorSurface;
				DesignLight[Led_physical_id].LedParam += Dynamic[ColorSurface];
			}
		}
		
		/********************
		********************/
		if(100 <= Progress){
			BlockGrouping[BlockGrouping_id].Block[i].t_From = t_now;
			
			Progress_id++;
			if(Bp[Bp_pattern_id].ShortPattern_Param[Progress_id].pShortPattern == NULL){
				Progress_id = 0;
			}
		}
	}
}

/******************************
******************************/
void DESIGN_MANAGER::update_DesignLight_Run_Echo__AllOn()
{
	for(int i = 0; i < NUM_DESIGN_LEDS; i++){
		COLOR_SURFACE ColorSurface = DesignLight[i].ColorSurface;
		
		// LED_PARAM Color_calm = ColorCombination[ColorCombination_id].Combination[ ColorSurface ].Color_calm;
		LED_PARAM Color_calm = CalmColor_pre[ColorSurface] * (1 - Fader_CalmColor.k) + ColorCombination[ColorCombination_id].Combination[ ColorSurface ].Color_calm * Fader_CalmColor.k;
		LED_PARAM Dynamic = ColorCombination[ColorCombination_id].Combination[ ColorSurface ].maxColor;
		
		DesignLight[i].LedParam = Color_calm * (1 - Fader_DesignLight.k) + Dynamic * (Fader_DesignLight.k);
	}
}

/******************************
******************************/
void DESIGN_MANAGER::update_DesignLight_Run_Echo__NumLeds()
{
	for(int i = 0; i < NUM_DESIGN_LEDS; i++){
		COLOR_SURFACE ColorSurface = DesignLight[i].ColorSurface;
		// LED_PARAM Color_calm = ColorCombination[ColorCombination_id].Combination[ ColorSurface ].Color_calm;
		LED_PARAM Color_calm = CalmColor_pre[ColorSurface] * (1 - Fader_CalmColor.k) + ColorCombination[ColorCombination_id].Combination[ ColorSurface ].Color_calm * Fader_CalmColor.k;
		
		DesignLight[i].LedParam = Color_calm * (1 - Fader_DesignLight.k);
	}
	
	for(int i = 0; i < LedNumSync; i++){
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
		LED_PARAM LedParam = CalmColor_pre[ColorSurface] * (1 - Fader_CalmColor.k) + ColorCombination[ColorCombination_id].Combination[ ColorSurface ].Color_calm * Fader_CalmColor.k;
		
		DesignLight[i].LedParam = LedParam;
	}
}

/******************************
******************************/
double DESIGN_MANAGER::calProgress(double t_now, double t_From, double Duration, double Speed)
{
	return 100 * (Speed * (t_now - t_From) / Duration);
}

/******************************
******************************/
void DESIGN_MANAGER::StateChart(double vol, double Vol_thresh_L, double Vol_thresh_H)
{
	enum SUB_STATE_RUN{
		SUB_STATE_RUN__VOL_WITHIN_RANGE,
		SUB_STATE_RUN__VOL_RANGE_OVER,
	};
	static SUB_STATE_RUN SubState_Run;
	
	Fader_CalmColor.update_Up(t_now - t_LastINT);
	
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
			if(Vol_thresh_H < vol){
				State = STATE_RUN;
				Transition__to_RUN();
				SubState_Run = SUB_STATE_RUN__VOL_WITHIN_RANGE; // 関数内staticなので、Transition__to_RUN()でなく、こちらで処理.
			}
			break;
			
		case STATE_RUN:
		{
			/********************
			********************/
			switch(SubState_Run){
				case SUB_STATE_RUN__VOL_WITHIN_RANGE:
					if(NUM_DESIGN_LEDS <= LedNumSync){
						if(DesignCategory == DESIGN__NUM_LEDS){
							Dice_LedId_NumLeds_Sync();
						}
						
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
			Fader_SafetyLight.update_Down(t_now - t_LastINT);
			Fader_DesignLight.update_Up(t_now - t_LastINT);
			
			
			if(vol < Vol_thresh_L){
				State = STATE_ECHO;
			}
		}
			
			break;
			
		case STATE_ECHO:
			Fader_SafetyLight.update_Down(t_now - t_LastINT);
			Fader_DesignLight.update_Down(t_now - t_LastINT);
			
			if(Vol_thresh_L < vol){
				State = STATE_RUN;
			}else if(Fader_DesignLight.k <= 0){
				State = STATE_CALM;
				t_calm_From = t_now;
			}
			break;
			
		case STATE_CALM:
		{
			Fader_SafetyLight.update_Down(t_now - t_LastINT);
			
			const double threshTime = 2.0;
			
			if(Vol_thresh_H < vol){
				State = STATE_RUN;
				Transition__to_RUN();
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
	Dice_DesignCategory();
	
	if(DesignCategory == DESIGN__PATTERN){
		Dice_BlockGrouping_id();
	}else if(DesignCategory == DESIGN__NUM_LEDS){
		Dice_LedId_NumLeds_Sync();
	}
	
	Fader_CalmColor.k = 0;
	for(int i = 0; i < NUM_COLOR_SURFACES; i++){
		CalmColor_pre[i] = ColorCombination[ColorCombination_id].Combination[i].Color_calm;
	}
	
	Dice_ColorCombination();
	
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
void DESIGN_MANAGER::Transition__to_RUN()
{
	Fader_DesignLight.k = 0;
	
	for( int i = 0; !IsPeriodOfBlockGroup(BlockGrouping[BlockGrouping_id].Block[i]); i++ ){
		BlockGrouping[BlockGrouping_id].Block[i].t_From = t_now;
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
		int j = rand() % (i + 1);
		
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
	int RandomNumber = rand() % TotalWeight;
	
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
		case STATE_RUN:
			sprintf(buf, "> STATE_RUN\n");

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
			sprintf(add_buf, "%-20s= DESIGN__LEV_MIC_SYNC\n", "DesignCategory");
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

