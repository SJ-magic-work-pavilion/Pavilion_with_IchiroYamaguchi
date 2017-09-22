/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
// #define MIC_ONLY
#define CHECK_LED_ANIM_ON_GUI

/************************************************************
************************************************************/
enum{
	WIDTH = 1280,
	HEIGHT = 720,
	
	MARGIN = 1,
};
enum{
	BUF_SIZE = 500,
};
enum COLOR_SURFACE{
	COLOR_FROM_RESTAURANT,
	COLOR_FROM_ENTRANCE,
	
	NUM_COLOR_SURFACES,
};

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class Noncopyable{
protected:
	Noncopyable() {}
	~Noncopyable() {}

private:
	void operator =(const Noncopyable& src);
	Noncopyable(const Noncopyable& src);
};

/**************************************************
**************************************************/
class LED_PARAM{
private:
	int R;
	int G;
	int B;
	
	int limit_singleVal(int val){
		if(255 < val)	val = 255;
		if(val < 0)		val = 0;
		
		return val;
	}
	
public:	
	LED_PARAM()
	: R(0), G(0), B(0)
	{
	}
	
	LED_PARAM(int r, int g, int b)
	: R(r), G(g), B(b)
	{
		limit();
	}
	
	LED_PARAM(const LED_PARAM& org)
	: R(org.R), G(org.G), B(org.B)
	{
		limit();
	}
	
    LED_PARAM& operator=(const LED_PARAM &org){
		R = org.R;
		G = org.G;
		B = org.B;
		
		limit();
		
        return *this;
    }
	
    void operator+=(const LED_PARAM &org){
		R += org.R;
		G += org.G;
		B += org.B;
		
		limit();
    }
	
	void limit()
	{
		if(255 < R)	R = 255;
		if(R < 0)	R = 0;
	
		if(255 < G)	G = 255;
		if(G < 0)	G = 0;
	
		if(255 < B)	B = 255;
		if(B < 0)	B = 0;
	}
	
	void clear()
	{
		R = 0; G = 0; B = 0;
	}
	
	void set_R(int r)	{ R = limit_singleVal(r); }
	int get_R() const	{ return R; }
	
	void set_G(int g)	{ G = limit_singleVal(g); }
	int get_G() const	{ return G; }
	
	void set_B(int b)	{ B = limit_singleVal(b); }
	int get_B() const	{ return B; }
};

LED_PARAM operator*(const LED_PARAM& org, const double k);
LED_PARAM operator+(const LED_PARAM& left, const LED_PARAM& right);
LED_PARAM operator-(const LED_PARAM& left, const LED_PARAM& right);

/************************************************************
************************************************************/
#define ERROR_MSG(); printf("Error in %s:%d\n", __FILE__, __LINE__);


