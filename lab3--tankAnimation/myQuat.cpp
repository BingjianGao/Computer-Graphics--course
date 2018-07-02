#include "MyQuat.h"

using namespace MyMathLibrary;

///YOUR CODE FROM ANIMATION TRACK LAB 2 HERE
MyQuat::MyQuat(void)
{
	this->w = this->v.x = this->v.y = this->v.z = 0.0;

}
MyQuat::MyQuat(float angleDeg, MyVector &axis)
{
	float radangle = angleDeg*M_PI / 180;
	axis.normalise();
	this->w = cos(radangle / 2.0);
	this->v.x = axis.x*sin(radangle / 2.0);
	this->v.y = axis.y*sin(radangle / 2.0);
	this->v.z = axis.z*sin(radangle / 2.0);
}
MyQuat::MyQuat(MyPosition &p)
{
	this->w = 0.0;
	this->v.x = p.x;
	this->v.y = p.y;
	this->v.z = p.z;

}
MyQuat MyQuat::addTo(const MyQuat &other) const
{
	MyQuat result;
	result.w = this->w + other.w;
	result.v.x = this->v.x + other.v.x;
	result.v.y = this->v.y + other.v.y;
	result.v.z = this->v.z + other.v.z;
	return result;
}
MyQuat MyQuat::multiplyBy(const MyQuat &other) const
{


	MyQuat result;
	result.w = this->w*other.w - this->v.getDotProduct(other.v);
	result.v.x = (this->v.y*other.v.z - this->v.z*other.v.y) + this->w*other.v.x + other.w*this->v.x;
	result.v.y = (this->v.z*other.v.x - this->v.x*other.v.z) + this->w*other.v.y + other.w*this->v.y;
	result.v.z = (this->v.x*other.v.y - this->v.y*other.v.x) + this->w*other.v.z + other.w*this->v.z;
	return result;

}
float MyQuat::getMagnitude(void) const
{
	float result;
	result = sqrt((this->w*this->w) + (this->v.x*this->v.x) + (this->v.y*this->v.y) + (this->v.z*this->v.z));
	return result;
}
void MyQuat::normalise(void)
{
	this->w /= getMagnitude();
	this->v.x /= getMagnitude();
	this->v.y /= getMagnitude();
	this->v.z /= getMagnitude();
}
MyQuat MyQuat::getConjugate(void) const
{
	MyQuat result;
	result.w = this->w;
	result.v.x = -this->v.x;
	result.v.y = -this->v.y;
	result.v.z = -this->v.z;
	return result;
}
MyQuat MyQuat::getInverse(void) const// have question in this part
{
	MyQuat result;
	result.w = this->w;
	result.v.x = this->v.x;
	result.v.y = this->v.y;
	result.v.z = this->v.z;
	result.normalise();
	result.getConjugate();
	return result;
}
MyMatrix MyQuat::convertToRotationMatrix(void) const
{
	MyMatrix result;
	//	this->normalise();  //need normalise????

	GLfloat Matrix[16]
	{1.0 - 2.0*this->v.y*this->v.y - 2.0*this->v.z*this->v.z, 2.0*this->v.x*this->v.y - 2.0*this->v.z*this->w, 2.0*this->v.x*this->v.z + 2.0*this->v.y*this->w, 0.0,
	2.0*this->v.x*this->v.y + 2.0*this->v.z*this->w, 1.0 - 2.0*this->v.x*this->v.x - 2.0*this->v.z*this->v.z, 2.0*this->v.y*this->v.z - 2.0*this->v.x*this->w, 0.0,
	2.0*this->v.x*this->v.z - 2.0*this->v.y*this->w, 2.0*this->v.y*this->v.z + 2.0*this->v.x*this->w, 1.0 - 2.0*this->v.x*this->v.x - 2.0*this->v.y*this->v.y, 0.0,
	0.0, 0.0, 0.0, 1.0};
	result = result.setMyMatrix(Matrix);  //**************矩阵可以直接相等赋值？？
	return result;
}