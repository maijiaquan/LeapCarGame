#include "ofApp.h"
#include<iostream>
#include<cmath>

using namespace std;

//const int DIR_LEFT = 0;
//const int DIR_RIGHT = 1;
enum{DIR_LEFT, DIR_RIGHT};

const float ROTATE_PER_PRESSED = 3.0;   //每次方向键旋转角度
const float DIS_BOX_CAM = 240.0;         //camera初始距离
const float INIT_CAM_Y = 120.0;          //camera初始高度

int g_rotate_count = 0;              //保存旋转次数
float g_rad_a, g_ang_a;              //竖直方向上的夹角

float cam_x, cam_z,cam_y;
float box_x, box_y, box_z;


bool is_rotate_cam = false;

//--------------------------------------------------------------
void ofApp::setup(){
    car.setup();

    light.setup();
    light.setPosition(-100, 200,100);
    
    plane.set(1000, 1000);
    plane.rotate(270, 1, 0 , 0);
    plane.move(0, -49, 0);
    
    roadMaterial.setDiffuseColor(ofFloatColor::gray);
    roadMaterial.setShininess(0.1);
    
    ofEnableDepthTest();
    cam.setAutoDistance(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    car.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    //计算camera左右位移量
    float ang = g_rotate_count * ROTATE_PER_PRESSED;   //保存 总旋转角度
    float rad = angToRad(ang);
    float delta_z = DIS_BOX_CAM * cos(rad);
    float delta_x = DIS_BOX_CAM * sin(rad);
    
    cam.setPosition(box_x + delta_x, box_y + INIT_CAM_Y, box_z + delta_z);  //camera发生左右位移

    if(!is_rotate_cam){
        //rotateCam();
        is_rotate_cam = true;
    }
    
    //camera开始工作
    cam.begin();
        roadMaterial.begin();
            plane.draw();
        roadMaterial.end();
        car.draw();
    cam.end();
    
    //更新数据
    updateAng();
    updateInfo();
    showInfo();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case OF_KEY_UP:
            car.accellerate();
            break;
        case OF_KEY_DOWN:
            car.brake();
            break;
        case OF_KEY_LEFT:
            rotateAll(DIR_LEFT);
            break;
        case OF_KEY_RIGHT:
            rotateAll(DIR_RIGHT);
            break;
        case OF_KEY_COMMAND:
            //cam_y = cam_y + 1;
            rotateCamAxisY();
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

float ofApp::angToRad(float ang){
    float rad = pi * ang / 180;
    return rad;
}

float ofApp::radToAng(float rad){
    float ang = rad * 180 / pi;
    return ang;
}

void ofApp::rotateAll(int dir){
    ofVec3f rotate_axis_y;        //定义一个向量
    rotate_axis_y.set(0, 1, 0);   //向量方向为y轴正方向

    if(dir == DIR_LEFT){
        car.steer(ROTATE_PER_PRESSED);
        cam.rotate(ROTATE_PER_PRESSED, rotate_axis_y);
        g_rotate_count++;
    }
    
    else{
        car.steer(-ROTATE_PER_PRESSED);
        cam.rotate(-ROTATE_PER_PRESSED, rotate_axis_y);
        g_rotate_count--;
    }
}

//camera向下旋转
void ofApp::rotateCamAxisY(){
    ofVec3f rotate_n;       //定义一个向量，方向为camera、camera与地面的垂线、car所构成平面的法向量
    rotate_n.set(cam_y * (cam_z - box_z), 0 ,cam_y * (box_x - cam_x));
    cam.rotate(-g_ang_a, rotate_n);
}

//更新竖直方向上的夹角
void ofApp::updateAng(){
    g_rad_a = asin(cam_y / DIS_BOX_CAM);
    g_ang_a = radToAng(g_rad_a);
}

void ofApp::updateInfo(){
    box_x = car.getBox().getX();
    box_y = car.getBox().getY();
    box_z = car.getBox().getZ();
    
    cam_x = cam.getX();
    cam_y = cam.getY();
    cam_z = cam.getZ();
}

void ofApp::showInfo(){
    string str_obj_x = "Object x coordinate = " + ofToString(box_x);
    ofDrawBitmapStringHighlight(str_obj_x, 20, 20);
    string str_obj_y = "Object y coordinate = " + ofToString(box_y);
    ofDrawBitmapStringHighlight(str_obj_y, 20, 40);
    string str_obj_z = "Object z coordinate = " + ofToString(box_z);
    ofDrawBitmapStringHighlight(str_obj_z, 20, 60);
    
    string str_cam_x = "Camera x coordinate = " + ofToString(cam_x);
    ofDrawBitmapStringHighlight(str_cam_x, 20, 100);
    string str_cam_y = "Camera y coordinate = " + ofToString(cam_y);
    ofDrawBitmapStringHighlight(str_cam_y, 20, 120);
    string str_cam_z = "Camera z coordinate = " + ofToString(cam_z);
    ofDrawBitmapStringHighlight(str_cam_z, 20, 140);
    
    string str_ang_a = "Angle = " + ofToString(g_ang_a) + "°";
    ofDrawBitmapStringHighlight(str_ang_a, 20, 180);
    
    cout<<"anga = "<<g_ang_a<<endl;
    cout<<"anga = "<<g_ang_a<<endl;
    
    cout<<"distance = "<<cam.getDistance()<<endl;
}