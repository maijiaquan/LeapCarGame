#include "Car.h"
#include <cstdlib>
Car::Car(){
}

void Car::setup(){
        vt = v0;     //vel为单位时间内的位移量，单位时间 = 1/60 s
    
    //light
    lightL.setParent(car_main_box);
    lightR.setParent(car_main_box);
    
    lightL.move(0,20,-100);
    
    //lightL.move(-45,20,-51);
    //lightR.move(45,20,-51);
    lightL.tilt(-20);
    lightR.tilt(-20);
    lightL.setSpotlight();
    lightR.setSpotlight();
    lightL.setDiffuseColor(ofFloatColor::white);
    lightR.setDiffuseColor(ofFloatColor::white);
    lightL.setup();
    //lightR.setup();
    
    car_main_box_width = 70;
    car_main_box_height = 40;
    car_main_box_depth = 130;
    
    
    //随机生成颜色
    for(int i = 0; i < obnum; i++){
        colors[i].set((float)(rand()%255), (float)(rand()%255), (float)(rand()%255));
        materials[i].setDiffuseColor(colors[i]);
    }
    
    material.setDiffuseColor(ofColor(224,124,48)); //车颜色 224 124 48
    
    material2.setDiffuseColor(ofFloatColor::darkBlue);
    material3.setDiffuseColor(ofFloatColor::darkGoldenRod);
    material4.setDiffuseColor(ofFloatColor::darkGrey);
    material5.setDiffuseColor(ofFloatColor::darkRed);
    material6.setDiffuseColor(ofFloatColor::purple);
    material7.setDiffuseColor(ofFloatColor::darkSalmon);
    
    //设置车的位置 宽，高，深
    car_main_box.set(car_main_box_width, car_main_box_height, car_main_box_depth);
    car_main_box.setPosition(0, -30, 0 );
    
    
    //随机设置障碍物的位置和、固定尺寸
    for(int i = 0; i < obnum; i++){
        boxes[i].set(100, 100, 100);
        x_random[i] = (float)(rand()%1000- 500);
        z_random[i] = (float)(rand()%50000 - 50000);
        boxes[i].setPosition(x_random[i], 0.0, z_random[i]);
    }
}

void Car::draw(){
    //画门
    for(int j = 0; j< 10; j++){
        ofFloatColor c;
        if(j % 4 == 0){
            c.set(ofFloatColor::darkGoldenRod);
        }else if(j % 4 == 1){
            c.set(ofFloatColor::darkRed);

        }else if(j % 4 == 2){
            c.set(ofFloatColor::darkGreen);

        }else{
            c.set(ofFloatColor::darkBlue);
        }
        
        for(int i = 0; i <10; i++){
            material3.setDiffuseColor(c);
            material3.begin();
            gate[i].setPosition(-500+ i*100, 800, -4000 - j*3000);
            gate[i].draw();
            material3.end();
        }
        for(int i = 10; i < 18; i++){
            material3.setDiffuseColor(c);
            material3.begin();
            gate[i].setPosition(-500, (i-10)*100, -4000 - j*3000);
            gate[i].draw();
            material3.end();
        }
        for(int i = 18; i < 27; i++){
            material3.setDiffuseColor(c);
            material3.begin();
            gate[i].setPosition(500, (i-18)*100, -4000 - j*3000);
            gate[i].draw();
            material3.end();
        }

        
    }
    


    
    lightR.draw();
    lightL.draw();
    
    
    //画出所有障碍物
    for(int i = 0; i < obnum; i++){
        // int x_random = rand()%5000;
        // int z_random = rand()%5000;
        
        materials[i].begin();
        boxes[i].draw();
        materials[i].end();
        //materials[i].setDiffuseColor(ofFloatColor::darkGreen);
    }
    
    material.begin();
    car_main_box.draw();
    //wheel_left_up.draw();
    material.end();
    
    material2.begin();
    box2.setPosition(-100 * 2, 0, 100  * 2);
    //box2.draw();
    material2.end();
    
    material3.begin();
    box3.set(100,100,100);
    box3.setPosition(0, 0, -300 * 2);
    box3.draw();
    material3.end();
    
    material4.begin();
    box4.setPosition(200 * 2, 0, 200 * 2);
    //box4.draw();
    material4.end();
    
    material5.begin();
    box5.setPosition(200 * 2, 0, -100 * 2);
    //box5.draw();
    material5.end();
    
    material6.begin();
    box6.setPosition(-200 * 2, 0, 300 * 2);
    //box6.draw();
    material6.end();
    
    material7.begin();
    box7.setPosition(400 * 2, 0, 400 * 2);
    //box7.draw();
    material7.end();
}

void Car::update(){
    //setA(0.2);
    //vel += acceleration;
    //vel *= 0.9;
    //acceleration *= 0.99;
    
    //acceleration;
    
    
    if(vt <= 20.0){
        vt += acceleration;       //激活加速度
    }
    
    
    if(canfly){
        ofVec3f velVector_y = car_main_box.getYAxis() ;//车上方的单位向量
        car_main_box.move(velVector_y * vel_y); //移动
        vel_y += acceleration_gravity;    //激活重力加速度
        if(car_main_box.getY() < -30){
            setCanfly(false);
        }
    }
    
    if(car_main_box.getX()<-600 ||car_main_box.getX()>600  ){
        ofVec3f velVector_y = car_main_box.getYAxis() ;//车上方的单位向量
        car_main_box.move(velVector_y * vel_y); //移动
        vel_y += acceleration_gravity;    //激活重力加速度
    }
    
    
    
    velVector = car_main_box.getZAxis() ;   //车子前方的单位向量
    car_main_box.move(velVector * -vt);   //移动
}

void Car::brake(){
    //acceleration -= 0.1;
}

void Car::accellerate(){
    //acceleration += 0.1;
}

void Car::steer(float dir){
    car_main_box.rotate(dir, 0, 1, 0); // the rotation happens on the y axis
    
}