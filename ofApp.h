#pragma once
//#include "ofxLeapMotion2.h"

#include "ofMain.h"
#include "Car.h"

class ofApp : public ofBaseApp{
    
private:
    Car car;
    ofEasyCam cam;
    
    ofPlanePrimitive plane;
    ofMaterial roadMaterial;
    ofLight light;
    
    
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
public:
    float angToRad(float ang);
    float radToAng(float rad);
    
    void rotateAll(int dir);
    void rotateCamAxisY();
    void showInfo();      
    void updateAng();
    void updateInfo();
};
