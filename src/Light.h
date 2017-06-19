#ifndef Light_H_
#define Light_H_
#pragma once
#include"Point.h"
class Light{
public:
	Point position;//��Դλ��
	Vector3 color;//��Դ�ɫ
	float Ia;

	Light(){
		position=0;
		color=1;
		Ia=1;
	}
	void setPosition(Point &p){
		position=p;
	}
	void setPosition(float x,float y,float z){
		position.x=x;
		position.y=y;
		position.z=z;
	}
	void setColor(Vector3 &v){
		color=v;
	}
	void setColor(float r,float g,float b){
		color.x=r;
		color.y=g;
		color.z=b;
	}
	void setIa(float a){
		Ia=a;
	}
};
#endif