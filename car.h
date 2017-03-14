#include "ofMain.h"
#include "cube.h"

class Car{
private:
    //Ctrl ctrl;
    //double g_v_y_dir;

    float car_main_box_width, car_main_box_height, car_main_box_depth;

    
    float vel_y;   //竖直方向上的速度
    float acceleration_gravity = -0.5;
    
        ofLight lightR, lightL;

    ofBoxPrimitive car_main_box;
    ofBoxPrimitive box2;
    ofBoxPrimitive box4;
    ofBoxPrimitive box5;
    ofBoxPrimitive box6;
    ofBoxPrimitive box7;
    
    ofCylinderPrimitive wheel_left_up, wheel_left_down, wheel_right_up, wheel_right_down;
    

    ofMaterial material;
    ofMaterial material2;
    ofMaterial material3;
    ofMaterial material4;
    ofMaterial material5;
    ofMaterial material6;
    ofMaterial material7;
    
    ofVec3f velVector;
    
public:
    
    int blood = 10;
    
    
    ofBoxPrimitive box3;

    float getVt(){return vt;}
    float getV0(){return v0;}
    float getA(){return acceleration;}
    float getG(){return acceleration_gravity;}

    float getVy(){return vel_y;}

    void setA(float a){acceleration = a;}
    void setVy(float v){vel_y = v;}
    void setCanfly(bool flag){canfly = flag;}
    
    Car();
    void setup();
    void draw();
    void update();
    void brake();
    void accellerate();
    void steer(float dir);
    ofBoxPrimitive getBox(){return car_main_box;};
    ofVec3f getVelVector(){return velVector;};
    //~Car();
    
    float v0 = 3.0;
    float vt;
    float acceleration = 1.0;
    
    int obnum = 200;
    
    ofBoxPrimitive gate [27];

    ofBoxPrimitive boxes [200];
    ofMaterial materials [200];
    float x_random [200];
    float z_random [200];
    ofColor colors[200];
    bool canfly;
    bool openleapfly = true;

    

};