/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "sj_common.h"

/************************************************************
************************************************************/
enum{
	NUM_POINTS = WIDTH,
};
enum{
	THREAD_SLEEP_MS = 1,
};

/************************************************************
class
************************************************************/

/**************************************************
**************************************************/
template <class T>
class THREAD__PARAM : public ofThread{
private:
	T val;

public:
	THREAD__PARAM()
	{
		val = 0;
	}

	/******************************
	description
		need lock()/unlock()
	******************************/
	T get(){
		return val;
	}
	
	/******************************
	description
		need lock()/unlock()
	******************************/
	void set(T _val){
		val = _val;
	}
	
	void threadedFunction(){
		while(isThreadRunning()) {
			lock();
			unlock();
			
			sleep(THREAD_SLEEP_MS);
		}
    }
};

/**************************************************
**************************************************/
class THREAD__VERTS : public ofThread{
private:
	ofVec3f Verts_Raw[NUM_POINTS];
	ofVec3f Verts_Monitor[NUM_POINTS];
	
	bool b_set;
	double NewVal;
	
	const bool b_TimeReverse;
	
public:
	THREAD__VERTS()
	: b_TimeReverse(false)
	{
		for(int i = 0; i < NUM_POINTS; i++){
			Verts_Raw[i].set(i, 0);
		}
	}

	/******************************
	description
		need lock()/unlock()
	******************************/
	/*
	const ofVec3f& operator[] (int i){
		if( (i < 0) || (NUM_POINTS <= i) ){
			printf("warning:%s\n", __FUNCTION__);
			i = 0;
		}
		
		return Verts_Raw[i];
	}
	*/
	
	/******************************
	description
		need lock()/unlock()
	******************************/
	const ofVec3f& get_MonitorVert(int id, const float Monitor_v_max){
		if( (id < 0) || (NUM_POINTS <= id) ){
			printf("warning:%s\n", __FUNCTION__);
			id = 0;
		}
		
		for(int i = 0; i < NUM_POINTS; i++){
			float Disp_SoundLevel = ofMap(Verts_Raw[i].y, 0, Monitor_v_max, 0, HEIGHT - MARGIN);
			Verts_Monitor[i].set(i, Disp_SoundLevel);
		}
		
		return Verts_Monitor[id];
	}
	
	/******************************
	description
		need lock()/unlock()
	******************************/
	float get_RawVal(int x){
		if( (0 <= x) && (x < NUM_POINTS) ){
			return Verts_Raw[x].y;
			
		}else{
			return -1;
		}
	}
	
	/******************************
	description
		need lock()/unlock()
	******************************/
	float get_Latest_RawVal(){
		if(b_TimeReverse)	return Verts_Raw[0].y;
		else				return Verts_Raw[NUM_POINTS - 1].y;
	}
	
	/******************************
	description
		need lock()/unlock()
	******************************/
	void set(double _val){
		if(isThreadRunning()){
			NewVal = _val;
			b_set = true;
		}
	}
	
	/******************************
	******************************/
	void threadedFunction(){
		while(isThreadRunning()) {
			lock();
			
			if(b_set){
				if(b_TimeReverse){
					for(int i = NUM_POINTS - 1; 0 < i; i--){
						Verts_Raw[i].set(i, Verts_Raw[i-1].y);
					}
					Verts_Raw[0].set(0, NewVal);
				}else{
					for(int i = 0; i < NUM_POINTS - 1; i++){
						Verts_Raw[i].set(i, Verts_Raw[i + 1].y);
					}
					Verts_Raw[NUM_POINTS - 1].set(NUM_POINTS - 1, NewVal);
				}
				
				b_set = false;
			}
			
			unlock();
			sleep(THREAD_SLEEP_MS);
		}
    }
};

