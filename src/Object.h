#ifndef Object_H_
#define Object_H_
#pragma once
#include"Point.h"
#include"Ray.h"
#include<iostream>
using namespace std;
class Object{
public:
	Vector3 kd;//¬˛∑¥…‰
	Vector3 kt;//Õ∏…‰
	Vector3 ks;//ÁR√Ê∑¥…‰

	Point position;
	int type;//0-plane,1-sphere

	Object():kd(0),kt(0),ks(0){
		position=0;
	}
	void setPosition(Point &p){
		position=p;
	}
	void setPosition(float x,float y,float z){
		position=Point(x,y,z);
	}
	void setKd(Vector3 &d){
		kd=Vector3(d);
	}
	void setKd(float n1,float n2,float n3){
		kd=Vector3(n1,n2,n3);
	}
	void setKt(Vector3 &t){
		kt=Vector3(t);
	}
	void setKt(float n1,float n2,float n3){
		kt=Vector3(n1,n2,n3);
	}
	void setKs(Vector3 &s){
		ks=Vector3(s);
	}
	void setKs(float n1,float n2,float n3){
		ks=Vector3(n1,n2,n3);
	}
	virtual bool isInSide(Point &p){return false;}
	virtual bool isNormalSide(Point &p){return false;}
	virtual bool isRayHit(Ray &r){
		return false;}
	virtual Point hitPoint(Ray &r){return 0;}
	virtual Vector3 getNormal(Point &p){return 0;}
};

class Plane:public Object{
public:
	Vector3 normal;

	Plane(){
		normal=Vector3(0,1,0);
		type=0;
	}
	Plane(Point &po,Vector3 &nor){
		position=po;
		normal=nor;
		type=0;
	}
	Plane(float px,float py,float pz,float nx,float ny,float nz){
		position=Point(px,py,pz);
		normal=(nx,ny,nz);
		type=0;
	}
	void setNormal(Vector3 &n){
		normal=n;
		normal.normalize();
	}
	void setNormal(float x,float y,float z){
		normal=Point(x,y,z);
		normal.normalize();
	}
	bool isInSide(Point &p){
		Point tmp(position-p);
		float dot=normal.dot(tmp);
		return ((dot<1e-5)||(dot>-1e-5))?true:false;
	}
	bool isNormalSide(Point &p){
		Point tmp(p-position);
		float dot=normal.dot(tmp);
		return dot>0?true:false;
	}
	bool isRayHit(Ray &r){
		if(isNormalSide(r.position)){
			/*cout<<"nor: "<<normal.x<<" "<<normal.y<<" "<<normal.z<<endl;
			cout<<"nor: "<<r.direction.x<<" "<<r.direction.y<<" "<<r.direction.z<<endl;
			cout<<endl;*/
			if(normal.dot(r.direction)<0){
				return true;
			}
		}
		return false;
	}
	Point hitPoint(Ray &r){
		float t;
		t=normal.dot(position-r.position)/normal.dot(r.direction);
		Point result=r.position+r.direction*t;
		return result;		
	}
	Vector3 getNormal(Point &p){
		return normal;
	}
};

class Sphere:public Object{
public:
	float radius;

	Sphere(){
		radius=1;
		type=1;
	}
	Sphere(Point &po,float r){
		position=po;
		radius=r;
		type=1;
	}
	Sphere(float px,float py,float pz,float r){
		position=Point(px,py,pz);
		radius=r;
		type=1;
	}
	void setRadius(float r){
		radius=r;
	}
	bool isInSide(Point &p){
		Point tmp(position-p);
		float d=tmp.abs();
		return ((d-radius<1e-5)||(d-radius>-1e-5))?true:false;
	}
	bool isNormalSide(Point &p){
		Point tmp(position-p);
		float d=tmp.abs();
		return d>radius+1e-2?true:false;
	}
	bool isRayHit(Ray &r){
		if(isNormalSide(r.position)){
			r.direction.normalize();
			float d=r.direction.cross(position-r.position).abs();
			return d<=radius?true:false;
		}
		return false;
	}

	Point hitPoint(Ray &r){
		Point result;
		if(isRayHit(r)){
			Vector3 p=r.position-position;
			float delta=p.dot(r.direction)*p.dot(r.direction)-p.dot(p)+radius*radius;
			float t1=-p.dot(r.direction)-sqrt(delta);
			float t2=-p.dot(r.direction)+sqrt(delta);
			float t=0;
			if(t1<0){
				if(t2>0){
					t=t2;
				}
			}else{
				t=t1;
			}
			result=r.position+r.direction*t;
		}
		return result;
	}
	Vector3 getNormal(Point &p){
		Vector3 nor=p-position;
		nor.normalize();
		return nor;
	}
};
#endif