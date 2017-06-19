#ifndef Ray_H_
#define Ray_H_  
#pragma once
#include"Point.h"
#include"Object.h"
class Ray{
public:
	Point position;
	Vector3 direction;
	Vector3 color;

	Ray(){
		position=Point();
		direction=Vector3(0,1,0);
		color=Vector3(0);
	}
	Ray(Point po,Vector3 di){
		position=po;
		direction=di;
		color=Vector3(0);
		direction.normalize();
	}
	void setPosition(Point &p){
		position=p;
	}
	void setPosition(float x,float y,float z){
		position.x=x;
		position.y=y;
		position.z=z;
	}
	void setDirection(Vector3 &di){
		direction=di;
		direction.normalize();
	}
	void setDirection(float x,float y,float z){
		direction.x=x;
		direction.y=y;
		direction.z=z;
		direction.normalize();
	}
	Vector3 reflect(Vector3 &n){
		Vector3 result= direction-n*direction.dot(n)*2;
		result.normalize();
		return result;
	}
};
#endif