
#include "BoundingSphere.h"
using namespace MyMathLibrary;


BoundingSphere::BoundingSphere(void)
{
	this->center.x = 0.0;
	this->center.y = 0.0;
	this->center.z = 0.0;
	this->radius = 0.0;

}
BoundingSphere::BoundingSphere(MyPosition&p, float r)
{
	this->center.x = p.x;
	this->center.y = p.y;
	this->center.z = p.z;
	this->radius = r;
}

BoundingSphere::BoundingSphere(ObjMesh*pMesh, float m[16])
{
	
	int num = pMesh->m_iNumberOfVertices;
	float x = 0.0, y = 0.0, z = 0.0;
	float center_x=0.0, center_y=0.0, center_z=0.0;
	this->radius = 0.0;

	for (int i = 0; i < num; i++)
	{
		x = x + pMesh->m_aVertexArray[i].x;
		y = y + pMesh->m_aVertexArray[i].y;
		z = z + pMesh->m_aVertexArray[i].z;
	}
	center_x = x / num;  //*********************还未经过matrix操作前的center点
	center_y = y / num;
	center_z = z / num;

	float r0 = 0.0;
	float temp=0.0;
	int flag=0;

	for (int j=0; j < num; j++)
	{
		temp = powf(pMesh->m_aVertexArray[j].x - center_x, 2) +
			powf(pMesh->m_aVertexArray[j].y - center_y, 2) +
			powf(pMesh->m_aVertexArray[j].z - center_z, 2);
		if (temp > r0)
		{
			flag = j;
			r0 = temp;
		}
			
	}
	this->radius = sqrt(r0) / 10;
	/*
	this->radius = sqrt(powf(pMesh->m_aVertexArray[flag].x - center_x, 2) +
		powf(pMesh->m_aVertexArray[flag].y - center_y, 2) +
		powf(pMesh->m_aVertexArray[flag].z - center_z, 2)) / 10;
		*/
	/*
	this->center.x = m[0] * center_x + m[1] * center_y + m[2] * center_z + m[3];
	this->center.y = m[4] * center_x + m[5] * center_y + m[6] * center_z + m[7];
	this->center.z = m[8] * center_x + m[9] * center_y + m[10] * center_z + m[11];
	float mamam = 0.0;
	*/
	this->center.x = m[0] * center_x + m[4] * center_y + m[8] * center_z + m[12];
	this->center.y = m[1] * center_x + m[5] * center_y + m[9] * center_z + m[13];
	this->center.z = m[2] * center_x + m[6] * center_y + m[10] * center_z + m[14];
	

}

