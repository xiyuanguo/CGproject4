#ifndef Point_H_
#define Point_H_  
#pragma once
#include<iostream>
using namespace std;
typedef class Point{
public:
	float x,y,z;

	Point():x(0),y(0),z(0){}
	Point(float n):x(n),y(n),z(n){}
	Point(float a,float b,float c):x(a),y(b),z(c){}

	void operator+=(const Point& p){
		x+=p.x;
		y+=p.y;
		z+=p.z;
	}
	void operator+=(float i){
		x+=i;
		y+=i;
		z+=i;
	}
	void operator-=(const Point& p){
		x-=p.x;
		y-=p.y;
		z-=p.z;
	}
	void operator-=(float i){
		x-=i;
		y-=i;
		z-=i;
	}
	void operator*=(const Point& p){
		x*=p.x;
		y*=p.y;
		z*=p.z;
	}
	void operator*=(float i){
		x*=i;
		y*=i;
		z*=i;
	}
	void operator/=(const Point& p){
		x/=p.x;
		y/=p.y;
		z/=p.z;
	}
	void operator/=(float i){
		x/=i;
		y/=i;
		z/=i;
	}
	Point operator+(const Point& p) const{
		Point tmp=*this;
		tmp+=p;
		return tmp;
	}
	Point operator+(float i)const{
		Point tmp=*this;
		tmp+=i;
		return tmp;
	}
	Point operator-(const Point& p) const{
		Point tmp=*this;
		tmp-=p;
		return tmp;
	}
	Point operator-(float i)const{
		Point tmp=*this;
		tmp-=i;
		return tmp;
	}
	Point operator*(const Point& p) const{
		Point tmp=*this;
		tmp*=p;
		return tmp;
	}
	Point operator*(float i)const{
		Point tmp=*this;
		tmp*=i;
		return tmp;
	}
	Point operator/(const Point& p) const{
		Point tmp=*this;
		tmp/=p;
		return tmp;
	}
	Point operator/(float i)const{
		Point tmp=*this;
		tmp/=i;
		return tmp;
	}
	bool operator==(const Point& p)const{
		return x==p.x && y==p.y && z==p.z;
	}
	bool operator==(float n)const{
		return x==n && y==n && z==n;
	}
	bool operator!=(const Point& p)const{
		return !(*this==p);
	}
	bool operator!=(float n)const{
		return !(*this==n);
	}
	void setX(float i){
		x=i;
	}
	void setY(float i){
		y=i;
	}
	void setZ(float i){
		z=i;
	}
	float dot(Point &p){
		return x*p.x+y*p.y+z*p.z;
	}
	Point cross(Point &p){
		Point tmp;
		tmp.x=y*p.z-z*p.y;
		tmp.y=z*p.x-x*p.z;
		tmp.z=x*p.y-y*p.x;
		return tmp;
	}
	float abs(){
		return sqrt(x*x+y*y+z*z);
	}
	void normalize(){
		if(this->abs()!=0){
			*this/=this->abs();
		}
	}
	float distance(Point &p){
		return (*this-p).abs();
	}
	float getMax(){
		float result;
		result=x>y?x:y;
		result=result>z?result:z;
		return result;
	}
	friend ostream& operator<<(ostream &os,Point p);
}Vector3;
ostream &operator<<(ostream &os, Point p){
	os<<p.x<<" "<<p.y<<" "<<p.z<<endl;
	return os;
}
#endif