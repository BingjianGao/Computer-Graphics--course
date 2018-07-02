
#pragma once
//#include "windows.h"

#include <math.h>
#include "myvector.h"
//#include "mymatrix.h"
#include "objloader.h"
//#include <gl/gl.h>            // standard OpenGL include
//#include <gl/glu.h>           // OpenGL utilties
//#include <glut.h>             // OpenGL utilties

namespace MyMathLibrary
{
	class BoundingSphere
	{
	public:
		
		BoundingSphere(void);
		BoundingSphere(MyPosition&center, float radius);
		BoundingSphere(ObjMesh*pMesh, float m[16]);



		MyPosition center;
		float radius;

	};
}

