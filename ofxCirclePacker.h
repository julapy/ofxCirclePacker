/*
 *  ofxCirclePacker.h
 *  julapy_sydfest
 *
 *  Created by lukasz karluk on 22/12/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

class ofxCirclePackerItem
{
public:
    
    ofxCirclePackerItem ()
    {
        x               = 0;
        y               = 0;
        radius          = 0;
        radiusMin       = 0;
        radiusMax       = 0;
        radiusGrowth    = 0;
        gap             = 0;
        
        count           = 0;
        bAlive          = true;
    }
    
    float getRadius     () { return radius + gap; }
    float getRadiusNext () { return radius + radiusGrowth + gap; }
    
    float x;
    float y;
    float radius;
    float radiusMin;
    float radiusMax;
    float radiusGrowth;
    float gap;

    ofColor colorFill;
    ofColor colorStroke;

	int	count;
	bool bAlive;
};

class ofxCirclePacker : public ofBaseApp
{
public :
    
	 ofxCirclePacker ();
	~ofxCirclePacker ();
    
    void setup  ();
	void update ();
	void draw	();
	void reset	();
	
	void setPause       ( bool value );
    void togglePause	();
	
	void addCircle
    ( 
        float x,
        float y,
        float radiusMin,
        float radiusMax,
        float radiusGrowth,
        float gap,
        const ofColor &colorFill,
        const ofColor &colorStroke
    );
	
	void writeToFile	( string filename = "circle_data.xml" );
	void loadFromFile	( string filename = "circle_data.xml" );
	
    vector<ofxCirclePackerItem*> circlesToAdd;
    vector<ofxCirclePackerItem*> circles;
	
	bool bPaused;
};