#ifndef Scene_H_
#define Scene_H_  
#pragma once
#include"Point.h"
#include"Light.h"
#include"Object.h"
#include"Ray.h"
#include<vector>
#include<iostream>
using namespace std;
class Scene{
public:
	Point eye;//視點
	Point lb;//左下
	Point rt;//右上
	int width;
	int height;
	int maxDepth;
	vector<Object*> objects;//物件數組
	vector<Light*> lights;//光源數組
	Vector3 *buffer;//位圖
	Scene();
	void setLight();
	void setObject();
	Vector3 rayTracing(Ray &ray,int depth);
	Vector3 rayShading(Object *object,Ray &ray,int depth);
	int nearestObject(Ray &ray);
	float rayToObject(Ray &ray,Object *obj);
	void writeBuffer();
	void display();
};
Scene::Scene(){
	eye=Point(0,60,-5);
	width=400;
	height=400;
	maxDepth=20;
	int screenSize=20;
	lb=Point(-screenSize,eye.y-screenSize,0);
	rt=Point(screenSize,eye.y+screenSize,0);
	buffer=new Vector3[width*height];
	setLight();
	setObject();	
}
void Scene::setLight(){
	Light *l=new Light();
	l->setPosition(0,100,20);
	
	l->setColor(1,1,1);
	l->setIa(2);
	lights.push_back(l);

	l=new Light();
	l->setPosition(-20,150,-50);
	l->setColor(1,1,1);
	lights.push_back(l);
}
void Scene::setObject(){
	Plane *o=new Plane();

	//floor
	o->setPosition(Point(0));
	o->setNormal(Vector3(0,1,0));
	o->setKd(0.5,1,0.5);
	//o->setKs(0.5,0.5,0.5);
	objects.push_back(o);
	//ceiling
	o=new Plane();
	o->setPosition(0,200,0);
	o->setNormal(Vector3(0,-1,0));
	o->setKd(0.5,1,0.5);
	//o->setKs(0.8,0.8,0.8);
	objects.push_back(o);

	//left
	o=new Plane();
	o->setPosition(-100,0,20);
	o->setNormal(10,0,0);
	o->setKd(0.1,0.1,0.1);
	o->setKs(0.8,0.8,0.8);
	objects.push_back(o);
	//right
	o=new Plane();
	o->setPosition(100,0,20);
	o->setNormal(-10,0,0);
	o->setKd(0.1,0.1,0.1);
	o->setKs(0.8,0.8,0.8);
	objects.push_back(o);

	//font
	o=new Plane();
	o->setPosition(0,0,100);
	o->setNormal(0,0,-1);
	o->setKd(0.9,0.8,0.2);
	//o->setKs(0.5,0.5,0.5);
	objects.push_back(o);
	//begind
	/*o=new Plane();
	o->setPosition(0,0,-100);
	o->setNormal(0,0,1);
	o->setKd(0.9,0.8,0);
	//o->setKs(0.5,0.5,0.5);
	objects.push_back(o);*/

	Sphere *s=new Sphere();
	s->setPosition(20,30,40);
	s->setRadius(20);
	s->setKd(0.2,0.2,1);
	//s->setKs(0.4,0.4,0.8);
	s->setKt(0.6,0.6,0.6);
	objects.push_back(s);

	s=new Sphere();
	s->setPosition(0,60,80);
	s->setRadius(40);
	s->setKd(0.1,0.1,0);
	s->setKs(0.8,0.8,0.8);
	objects.push_back(s);
}
void Scene::display(){
	buffer=new Vector3[width*height];
	writeBuffer();
	glRasterPos2f(-1,-1);
	glDrawPixels(width,height,GL_RGB,GL_FLOAT,(const GLvoid*)buffer);
}
void Scene::writeBuffer(){
	Point screen(width-1,height-1,1);
	Ray r(eye,Vector3(1));
	Vector3 color;
	int index=0;
	int percent;
	int a=0;
	for(int j=0;j<height;j++){
		for(int i=0;i<width;i++){
			Point screenPoint=Point(i,j,0)/screen*(rt-lb)+lb;
			screenPoint.z=screen.z;
			r.setDirection((screenPoint-eye));
			color=rayTracing(r,1);
			buffer[index++]=color;
			/*if(color==0){
				buffer[index-1]=buffer[index-2];
			}*/
			percent=index%(height*width/100);
			if(percent==0){
				char t = 8;
				cout<<a++<<"%";
				for(int i=0;i<10; i++){
					cout << t;
				}
			}
		}
	}
}
Vector3 Scene::rayTracing(Ray &ray,int depth){
	int nearIndex=nearestObject(ray);
	if(nearIndex>=0){
		//cout<<"near: "<<nearIndex;
		return rayShading(objects[nearIndex],ray,depth);
	}
	return 0;
}
Vector3 Scene::rayShading(Object *object,Ray &ray,int depth){
	Vector3 color=0;
	Point hitPoint=object->hitPoint(ray);
	Vector3 sRay;
	Ray shadowRay,rRay,tRay;
	Vector3 rColor=0,sColor=0,tColor=0;
	for(int i=0;i<lights.size();i++){
		if(object->isNormalSide(lights[i]->position)){
			sRay=lights[i]->position-hitPoint;
			sRay.normalize();
			shadowRay.position=lights[i]->position;
			shadowRay.direction=hitPoint-lights[i]->position;
			shadowRay.direction.normalize();
			int nearIndex=nearestObject(shadowRay);
			if(objects[nearIndex]==object){
				sColor+=lights[i]->color*object->kd*sRay.dot(object->getNormal(hitPoint))*lights[i]->Ia;
			}else{
				sColor+=lights[i]->color*object->kd*sRay.dot(object->getNormal(hitPoint))*lights[i]->Ia;
				sColor*=objects[nearIndex]->kt;
			}
		}
	}
	if(depth<maxDepth){
			if(object->ks!=0){
				rRay.position=hitPoint;
				rRay.direction=ray.reflect(object->getNormal(hitPoint));
				rColor=rayTracing(rRay,depth+1);
				if(object->type==1){
					//cout<<"rcolor: "<<rColor<<endl;
				}
				rColor+=rColor*object->ks;
			}
			if(object->kt!=0){
				tRay.position=hitPoint;
				tRay.direction=ray.direction;//未加折射率
				tColor=rayTracing(tRay,depth+1);
			}
		}
		float a=object->kd.abs();
		float b=object->ks.abs();
		float c=object->kt.abs();
		if(a+b!=0){
			color+=(sColor*a+rColor*b+tColor*c)/(a+b*2+c);
		}
	if(color.getMax()>1){
		color/=color.getMax();
		//cout<<"color: "<<color.x<<" "<<color.y<<" "<<color.z<<endl;
	}
	return color;
}
int Scene::nearestObject(Ray &ray){
	float nearDistance=1e10;
	int nearIndex=-1;
	for(int i=0;i<objects.size();i++){
		if(objects[i]->isRayHit(ray)){
			float temp=rayToObject(ray,objects[i]);
			if(temp<nearDistance){
				nearDistance=temp;
				nearIndex=i;
			}
		}
	}
	return nearIndex;
}
float Scene::rayToObject(Ray &ray,Object *obj){
	if(obj->isNormalSide(ray.position)){
		Vector3 distance;
		distance=obj->hitPoint(ray)-ray.position;
		return distance.abs();
	}
	return -1;
}
#endif