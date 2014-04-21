/*
 *  ofxCirclePacker.cpp
 *  Created by lukasz karluk on 22/12/09.
 *  http://julapy.com
 *
 */

#include "ofxCirclePacker.h"

ofxCirclePacker::ofxCirclePacker() {
	bPaused = false;
}

ofxCirclePacker::~ofxCirclePacker() {
	reset();
}

//-------------------------------------------------------------- pause.
void ofxCirclePacker::setPause(bool value) {
    bPaused = value;
}

void ofxCirclePacker::togglePause() {
	bPaused = !bPaused;
}

//-------------------------------------------------------------- setup.
void ofxCirclePacker::setup() {
    //
}

//-------------------------------------------------------------- add circle.
void ofxCirclePacker::addCircle(float x,
                                float y,
                                float radiusMin,
                                float radiusMax,
                                float radiusGrowth,
                                float gap,
                                const ofColor &colorFill,
                                const ofColor &colorStroke)
{
    if(bPaused == true) {
        return;
    }
    
    ofxCirclePackerItem * circle;
    circle = new ofxCirclePackerItem();
    
    circle->x               = x;
    circle->y               = y;
    circle->radius          = radiusMin;
    circle->radiusMin       = radiusMin;
    circle->radiusMax       = radiusMax;
    circle->radiusGrowth    = radiusGrowth;
    circle->gap             = gap;
    circle->colorFill       = colorFill;
    circle->colorStroke     = colorStroke;
    
    circlesToAdd.push_back(circle);
}


//-------------------------------------------------------------- update.
void ofxCirclePacker::update() {
	if(bPaused == true) {
		return;
    }
    
    ofxCirclePackerItem * c1;
    ofxCirclePackerItem * c2;
    
    //---------------------------------------------------------- add new circles.
    for(int i=0; i<circlesToAdd.size(); i++) {
        c1 = circlesToAdd[i];
        
        for(int j=0; j<circles.size(); j++) {
            c2 = circles[j];
            
            float d  = ofDist(c1->x, c1->y, c2->x, c2->y);
            float r1 = c1->getRadiusMax();
            float r2 = c2->bAlive ? c2->getRadiusMax() : c2->getRadius();
            float r  = r1 + r2;
            
            if(d <= r) {
                c1->neighbours.push_back(c2);
                c2->neighbours.push_back(c1);
            }
        }
        
        circles.push_back(c1);
    }
    circlesToAdd.clear();
    
	if(circles.size() == 0) {
		return;
    }
    
    int i, j, t;
	
    //---------------------------------------------------------- check collisions.
	for(i=0; i<circles.size(); i++) {
        c1 = circles[i];
        
		for(j=0; j<c1->neighbours.size(); j++) {
            c2 = c1->neighbours[j];
            
			if((c1->bAlive == false) && (c2->bAlive == false)) {
				continue;
            }
			
            float d  = ofDist(c1->x, c1->y, c2->x, c2->y);
            float r1 = (c1->bAlive == true) ? c1->getRadiusNext() : c1->getRadius();
            float r2 = (c2->bAlive == true) ? c2->getRadiusNext() : c2->getRadius();
            float r  = r1 + r2;
            
            if(r >= d) {
				c1->bAlive = false;
				c2->bAlive = false;
            }
		}
	}
	
    //---------------------------------------------------------- remove dead circles.
    i = 0;
    t = circles.size();
	for(i; i<t; i++) {
        c1 = circles[i];
        
		if(c1->count == 0 && c1->bAlive == false) {
            for( int j=0; j<c1->neighbours.size(); j++) {
                c2 = c1->neighbours[j];
                
                for(int k=0; k<c2->neighbours.size(); k++) {
                    if(c2->neighbours[k] == c1) {
                        c2->neighbours.erase(c2->neighbours.begin() + k);
                        break;
                    }
                }
            }
            
			circles.erase(circles.begin() + i);
            delete c1;
            
            --i;
            --t;
		}
	}
	
    //---------------------------------------------------------- update.
	for(i=0; i<circles.size(); i++) {
        c1 = circles[i];
        
		if(c1->bAlive == true) {
			c1->radius += c1->radiusGrowth;
			c1->count  += 1;
			
			if(c1->radius >= c1->radiusMax) {
                c1->radius = c1->radiusMax;
				c1->bAlive = false;
            }
		}
	}
}

//-------------------------------------------------------------- draw.
void ofxCirclePacker::draw() {
	for(int i=0; i<circles.size(); i++) {
        ofxCirclePackerItem * c = circles[i];
        
		ofFill();
        ofSetColor(c->colorFill);
		ofCircle(c->x, c->y, c->radius);
        
		ofNoFill();
        ofSetColor(c->colorStroke);
		ofCircle(c->x, c->y, c->radius);
	}
}

//-------------------------------------------------------------- reset.
void ofxCirclePacker::reset()
{
    for(int i=0; i<circlesToAdd.size(); i++) {
        delete circlesToAdd[i];
    }
    circlesToAdd.clear();
    
    for(int i=0; i<circles.size(); i++) {
        delete circles[i];
    }
	circles.clear();
}

//-------------------------------------------------------------- write / read from file.
void ofxCirclePacker::writeToFile(string filename) {
	// TODO.
}

void ofxCirclePacker::loadFromFile(string filename) {
	reset();
	
	// TODO.
}