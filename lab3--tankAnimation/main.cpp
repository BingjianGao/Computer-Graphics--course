#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:console")

#include "windows.h"

#include <gl/gl.h>            // standard OpenGL include
#include <gl/glu.h>           // OpenGL utilties
#include <glut.h>             // OpenGL utilties

#include "myvector.h"
#include "mymatrix.h"
#include"boundingsphere.h"
#include"myquat.h"

using namespace MyMathLibrary;

#include "stdlib.h"
#include "stdio.h"

#include "objloader.h"

ObjMesh* tankBody=NULL;
ObjMesh* tankTurret = NULL;
ObjMesh* tankMainGun = NULL;
ObjMesh* tankSecondaryGun = NULL;
ObjMesh* tankWheel = NULL;
                            //*************************task 3.1 low resolution
ObjMesh* tankBodyLow = NULL;
ObjMesh* tankTurretLow = NULL;
ObjMesh* tankMainGunLow = NULL;
ObjMesh* tankSecondaryGunLow = NULL;
ObjMesh* tankWheelLow = NULL;

void load_tank_objs(void);
void load_low_detail_tank_objs(void);


float zPos = -30.0;
//float zPos = -80.0;
float yRot = 0.0;
float xRot = 0.0;
static float angle_turret=0.0;
static float angle_MainGun = 0.0;
static float angle_SecondaryGun = 0.0;
static float angle_Wheels = 0.0;
static GLuint tankbody , turret, maingun, secondarygun, wheels; //*******display list 

BoundingSphere bstank;
BoundingSphere bstankbody;             //  *************task 2.2
BoundingSphere bsturret;
BoundingSphere bsmaingun;
BoundingSphere bssecondarygun;

GLfloat mbody[16];
GLfloat mturret[16];
GLfloat mmaingun[16];
GLfloat msecondarygun[16];

float tankbody_c1 = 1.0;    //********************task2.3
float tankbody_c2 = 1.0;
float tankbody_c3 = 1.0;
float turret_c1 = 1.0;
float turret_c2 = 1.0;
float turret_c3 = 1.0;
float maingun_c1 = 1.0;
float  maingun_c2 = 1.0;
float  maingun_c3 = 1.0;
float secondarygun_c1 = 1.0;
float secondarygun_c2 = 1.0;
float secondarygun_c3 = 1.0;
float tank_c1 = 1.0;
float tank_c2 = 1.0;
float tank_c3 = 1.0;

//prototypes for our callback functions
void draw(void);    //our drawing routine
void idle(void);    //what to do when nothing is happening
void key(unsigned char k, int x, int y);  //handle key presses
void reshape(int width, int height);      //when the window is resized
void init_drawing(void);                  //drawing intialisation
void draw_tank(void);
void draw_tank_low(void);
void buildsphere(void);    //**********task 2
void drawsphere(void);
void buildwholetanksphere(void);

void pointpenetrate(void);//**********task 2.3
MyPosition p = { 0.0, 0.0, 0.0 };




//our main routine
int main(int argc, char *argv[])
{
  //Initialise Glut and create a window
  glutInit(&argc, argv);
  //sets up our display mode
  //here we've selected an RGBA display with depth testing 
  //and double buffering enabled
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  //create a window and pass through the windows title
  glutCreateWindow("Basic Glut Application");

  //run our own drawing initialisation routine


  load_tank_objs();
  load_low_detail_tank_objs();       //*************task3.1
  init_drawing();

  

 


  //tell glut the names of our callback functions point to our 
  //functions that we defined at the start of this file
  glutReshapeFunc(reshape);
  glutKeyboardFunc(key);
  glutIdleFunc(idle);
  glutDisplayFunc(draw);

  //request a window size of 600 x 600
  glutInitWindowSize(600,600);
  glutReshapeWindow(600,600);

  //go into the main loop
  //this loop won't terminate until the user exits the 
  //application
  glutMainLoop();
  return 0;
}

void load_tank_objs(void)
{
  tankBody = LoadOBJ(".\\tankobjs\\tankbody.obj");
  tankTurret = LoadOBJ(".\\tankobjs\\tankturret.obj");
  tankMainGun = LoadOBJ(".\\tankobjs\\tankmaingun.obj");
  tankSecondaryGun = LoadOBJ(".\\tankobjs\\tanksecondarygun.obj");
  tankWheel = LoadOBJ(".\\tankobjs\\tankwheel.obj");
  SetTextures(tankBody->m_iMeshID, NULL, ".\\tankobjs\\texture.tga");
  
}
void load_low_detail_tank_objs(void)
{
	tankBodyLow = LoadOBJ(".\\tankobjs\\tankbodyLow.obj");
	tankTurretLow = LoadOBJ(".\\tankobjs\\tankturretLow.obj");
	tankMainGunLow = LoadOBJ(".\\tankobjs\\tankmaingunLow.obj");
	tankSecondaryGunLow = LoadOBJ(".\\tankobjs\\tanksecondarygunLow.obj");
	tankWheelLow = LoadOBJ(".\\tankobjs\\tankwheelLow.obj");
	//SetTextures(tankBody->m_iMeshID, NULL, ".\\tankobjs\\texture.tga");

}

void draw_tank(float x, float y, float z)
{
	
	glPushMatrix();  //************draw tank body
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x,y,z);
	glScalef(0.1,0.1,0.1);		//reduce the size of the tank on screen
	glGetFloatv(GL_MODELVIEW_MATRIX, mbody);
	//DrawOBJ(tankBody->m_iMeshID);
	//glCallList(tankbody);  //*************display list

	//*****************************************task1.4
	unsigned int i;
	glBegin(GL_TRIANGLES);
	for (i = 0; i < tankBody->m_iNumberOfFaces; i++)     
	{
		unsigned int j;
		ObjFace*tankf = &tankBody->m_aFaces[i];
		for (j = 0; j < 3; j++)
		{
			glTexCoord2f(tankBody->m_aTexCoordArray[tankf->m_aTexCoordIndicies[j]].u,
				tankBody->m_aTexCoordArray[tankf->m_aTexCoordIndicies[j]].v);
			glNormal3f(tankBody->m_aNormalArray[tankf->m_aNormalIndices[j]].x,
				tankBody->m_aNormalArray[tankf->m_aNormalIndices[j]].y,
				tankBody->m_aNormalArray[tankf->m_aNormalIndices[j]].z);
			glVertex3f(tankBody->m_aVertexArray[tankf->m_aVertexIndices[j]].x,
				tankBody->m_aVertexArray[tankf->m_aVertexIndices[j]].y,
				tankBody->m_aVertexArray[tankf->m_aVertexIndices[j]].z);
		}
	}
	    // get current matrix
	glEnd();


	//Use your own draw code here to draw the rest of the tank
	//Here's the code for each individual part
	//Each part is placed with respect to the origin
	//you'll need to add in glPushMatrix/glTranslatef/glRotatef/glPopMatrix commands as necessary
	//DrawOBJ(tankTurret->m_iMeshID);
	//DrawOBJ(tankMainGun->m_iMeshID);
	//DrawOBJ(tankSecondaryGun->m_iMeshID);
	//DrawOBJ(tankWheel->m_iMeshID);

	glPopMatrix();

	glPushMatrix();  //******************draw tank turret
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x, y + 1.5, z);
	glRotatef(angle_turret, 0.0, 1.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	glCallList(turret);
	//DrawOBJ(tankTurret->m_iMeshID);
	glGetFloatv(GL_MODELVIEW_MATRIX, mturret);
	glPopMatrix();

	glPushMatrix();  //******************draw tank maingun
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glRotatef(angle_turret, 0.0, 1.0, 0.0);
	glTranslatef(x+5.38, y-8.75 , z+1.1);
	glRotatef(angle_MainGun, 1.0, 0.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	glCallList(maingun);
	//DrawOBJ(tankMainGun->m_iMeshID);
	glGetFloatv(GL_MODELVIEW_MATRIX, mmaingun);
	glPopMatrix();

	glPushMatrix();  //******************draw tank sencondarygun
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glRotatef(angle_turret, 0.0, 1.0, 0.0);
	glTranslatef(x-1.25 , y+3.5 , z-1.35 );
	glRotatef(angle_SecondaryGun, 0.0, 1.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	glCallList(secondarygun);
	//DrawOBJ(tankSecondaryGun->m_iMeshID);
	glGetFloatv(GL_MODELVIEW_MATRIX, msecondarygun);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x-2.5 , y-1.15 , z );
	glScalef(0.1, 0.1, 0.1);
	glCallList(wheels);
	//DrawOBJ(tankWheel->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x - 2.5, y - 1.15, z-1.9);
	glScalef(0.1, 0.1, 0.1);
	glCallList(wheels);
	//DrawOBJ(tankWheel->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x - 2.5, y - 1.15, z - 3.8);
	glScalef(0.1, 0.1, 0.1);
	glCallList(wheels);
	//DrawOBJ(tankWheel->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x - 2.5, y - 1.15, z - 5.7);
	glScalef(0.1, 0.1, 0.1);
	glCallList(wheels);
	//DrawOBJ(tankWheel->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x - 2.5, y - 1.15, z+1.9);
	glScalef(0.1, 0.1, 0.1);
	glCallList(wheels);
	//DrawOBJ(tankWheel->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x - 2.5, y - 1.15, z + 4.2);
	glScalef(0.1, 0.1, 0.1);
	glCallList(wheels);
	//DrawOBJ(tankWheel->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x + 2.5, y - 1.15, z);
	glRotatef(180, 0.0, 1.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	glCallList(wheels);
	//DrawOBJ(tankWheel->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x + 2.5, y - 1.15, z - 1.9);
	glRotatef(180, 0.0, 1.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	glCallList(wheels);
	//DrawOBJ(tankWheel->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x + 2.5, y - 1.15, z - 3.8);
	glRotatef(180, 0.0, 1.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	glCallList(wheels);
	//DrawOBJ(tankWheel->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x + 2.5, y - 1.15, z - 5.7);
	glRotatef(180, 0.0, 1.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	glCallList(wheels);
	//DrawOBJ(tankWheel->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x + 2.5, y - 1.15, z + 1.9);
	glRotatef(180, 0.0, 1.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	glCallList(wheels);
	//DrawOBJ(tankWheel->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x + 2.5, y - 1.15, z + 4.2);
	glRotatef(180, 0.0, 1.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	glCallList(wheels);
	//DrawOBJ(tankWheel->m_iMeshID);
	glPopMatrix();

	printf("mBody\n");
	for (int i = 0; i<4; i++)
	{
		printf("%f|%f|%f|%f|\n", mbody[4 * i], mbody[4 * i + 1], mbody[4 * i + 2], mbody[4 * i + 3]);
	}
	printf("mTurret\n");
	for (int i = 0; i<4; i++)
	{
		printf("%f|%f|%f|%f|\n", mturret[4 * i], mturret[4 * i + 1], mturret[4 * i + 2], mturret[4 * i + 3]);
	}
	printf("mMainGun\n");
	for (int i = 0; i<4; i++)
	{
		printf("%f|%f|%f|%f|\n", mmaingun[4 * i], mmaingun[4 * i + 1], mmaingun[4 * i + 2], mmaingun[4 * i + 3]);
	}
	printf("mSecGun\n");
	for (int i = 0; i < 4; i++)
	{
		printf("%f|%f|%f|%f|\n", msecondarygun[4 * i], msecondarygun[4 * i + 1], msecondarygun[4 * i + 2], msecondarygun[4 * i + 3]);
	}
	printf("zpos:");
	printf("%f\n", zPos);
}
void draw_tank_low(float x, float y, float z)
{
	glDisable(GL_TEXTURE_2D);                 //**************task 3
	glDisable(GL_LIGHTING);
	glPushMatrix();  //************draw tank body
	
	glColor3ub(48, 41, 30);
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x, y, z);
	glScalef(0.1, 0.1, 0.1);		//reduce the size of the tank on screen
	
	DrawOBJ(tankBodyLow->m_iMeshID);
	//glCallList(tankbody);  //*************display list

	//Use your own draw code here to draw the rest of the tank
	//Here's the code for each individual part
	//Each part is placed with respect to the origin
	//you'll need to add in glPushMatrix/glTranslatef/glRotatef/glPopMatrix commands as necessary
	//DrawOBJ(tankTurret->m_iMeshID);
	//DrawOBJ(tankMainGun->m_iMeshID);
	//DrawOBJ(tankSecondaryGun->m_iMeshID);
	//DrawOBJ(tankWheel->m_iMeshID);

	glPopMatrix();
	
	glPushMatrix();  //******************draw tank turret
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x, y + 1.5, z);
	glRotatef(angle_turret, 0.0, 1.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	//glCallList(turret);
	DrawOBJ(tankTurretLow->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw tank maingun
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glRotatef(angle_turret, 0.0, 1.0, 0.0);
	glTranslatef(x + 5.38, y - 8.75, z + 1.1);
	glRotatef(angle_MainGun, 1.0, 0.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	//glCallList(maingun);
	DrawOBJ(tankMainGunLow->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw tank sencondarygun
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glRotatef(angle_turret, 0.0, 1.0, 0.0);
	glTranslatef(x - 1.25, y + 3.5, z - 1.35);
	glRotatef(angle_SecondaryGun, 0.0, 1.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	//glCallList(secondarygun);
	DrawOBJ(tankSecondaryGunLow->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x - 2.5, y - 1.15, z);
	glScalef(0.1, 0.1, 0.1);
	//glCallList(wheels);
	DrawOBJ(tankWheelLow->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x - 2.5, y - 1.15, z - 1.9);
	glScalef(0.1, 0.1, 0.1);
	//glCallList(wheels);
	DrawOBJ(tankWheelLow->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x - 2.5, y - 1.15, z - 3.8);
	glScalef(0.1, 0.1, 0.1);
	//glCallList(wheels);
	DrawOBJ(tankWheelLow->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x - 2.5, y - 1.15, z - 5.7);
	glScalef(0.1, 0.1, 0.1);
	//glCallList(wheels);
	DrawOBJ(tankWheelLow->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x - 2.5, y - 1.15, z + 1.9);
	glScalef(0.1, 0.1, 0.1);
	//glCallList(wheels);
	DrawOBJ(tankWheelLow->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x - 2.5, y - 1.15, z + 4.2);
	glScalef(0.1, 0.1, 0.1);
	//glCallList(wheels);
	DrawOBJ(tankWheelLow->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels

	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x + 2.5, y - 1.15, z);
	glRotatef(180, 0.0, 1.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	//glCallList(wheels);
	DrawOBJ(tankWheelLow->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels

	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x + 2.5, y - 1.15, z - 1.9);
	glRotatef(180, 0.0, 1.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	//glCallList(wheels);
	DrawOBJ(tankWheelLow->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels

	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x + 2.5, y - 1.15, z - 3.8);
	glRotatef(180, 0.0, 1.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	//glCallList(wheels);
	DrawOBJ(tankWheelLow->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels

	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x + 2.5, y - 1.15, z - 5.7);
	glRotatef(180, 0.0, 1.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	//glCallList(wheels);
	DrawOBJ(tankWheelLow->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels

	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x + 2.5, y - 1.15, z + 1.9);
	glRotatef(180, 0.0, 1.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	//glCallList(wheels);
	DrawOBJ(tankWheelLow->m_iMeshID);
	glPopMatrix();

	glPushMatrix();  //******************draw a lot of wheels
	glRotatef(angle_Wheels, 0.0, 1.0, 0.0);
	glTranslatef(x + 2.5, y - 1.15, z + 4.2);
	glRotatef(180, 0.0, 1.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	//glCallList(wheels);
	DrawOBJ(tankWheelLow->m_iMeshID);
	glPopMatrix();

	printf("zpos:");
		printf("%f\n", zPos);


	


}
//draw callback function - this is called by glut whenever the 
//window needs to be redrawn
void draw(void)
{
	
  //clear the current window
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //make changes to the modelview matrix
  glMatrixMode(GL_MODELVIEW);
  //initialise the modelview matrix to the identity matrix
  glLoadIdentity();

  glTranslatef(0.0,0.0,zPos);   //zPos=-30

  glRotatef(yRot,0.0,1.0,0.0);   //*******绕着y轴旋转
  glRotatef(xRot, 1.0, 0.0, 0.0);   //*******绕着y轴旋转

 
  //draw the tank on screen at a position
  draw_tank(0.0, 0.0, 0.0);

 // drawsphere();      //******************task2

  //draw_tank_low(0.0, 0.0, 0.0);                 //*************task3

  //flush what we've drawn to the buffer
  glFlush();
  //swap the back buffer with the front buffer
  glutSwapBuffers();
}

//idle callback function - this is called when there is nothing 
//else to do
void idle(void)
{
  //this is a good place to do animation
  //since there are no animations in this test, we can leave 
  //idle() empty
}

//key callback function - called whenever the user presses a 
//key
void key(unsigned char k, int x, int y)
{
  switch(k)
  {
    case 'd':      //*******"d""f"放大缩小
	  zPos--;
	  break;
	case 'f':
	  zPos++;
	  break;
	case 'r':  //**************"r""e"  视图左右旋转
	  yRot++;
	  break;
	case 'e':
		yRot--;
		break;
	case 'w':  //***************"w""q" 视图上下旋转
		xRot++;
		break;
	case 'q':
		xRot--;
		break;
	case'a':  //**********************"a""s"整车转
		angle_Wheels++;
		break;
	case's':
		angle_Wheels--;
		break;
	case'z':  //**********************"z""x"turret 转
		angle_turret++;
		break;
	case'x':
		angle_turret--;
		break;
	case'c':  //**********************"c""v"miangun 转
		angle_MainGun++;
		break;
	case'v':
		angle_MainGun--;
		break;
	case'b':  //**********************"c""v"secondarygun 转
		angle_SecondaryGun++;
		break;
	case'n':
		angle_SecondaryGun--;
		break;
	case't':
		p.x++;
		break;
	case'y':
		p.x--;
		break;
	case'u':
		p.y++;
		break;
	case'i':
		p.y--;
		break;
	case'o':
		p.z=p.z+1.0;
		break; 
	case'p':
		p.z=p.z-1.0;
		break;
    case 27: //27 is the ASCII code for the ESCAPE key
      exit(0);
      break;

  }
  glutPostRedisplay();
}

//reshape callback function - called when the window size changed
void reshape(int width, int height)
{
  //set the viewport to be the same width and height as the window
  glViewport(0,0,width, height);
  //make changes to the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //set up our projection type
  //we'll be using a perspective projection, with a 90 degree 
  //field of view
  gluPerspective(45.0, (float) width / (float) height, 1.0, 1000.0);
  //redraw the view during resizing
  draw();
}

//set up OpenGL before we do any drawing
//this function is only called once at the start of the program
void init_drawing(void)
{
	
	tankbody = glGenLists(5);        //  task display list
	turret = tankbody + 1;
	maingun = turret + 1;
	secondarygun = maingun + 1;
	wheels = secondarygun + 1;

	glNewList(tankbody, GL_COMPILE);
	DrawOBJ(tankBody->m_iMeshID);
	glEndList();

	glNewList(turret, GL_COMPILE);
	DrawOBJ(tankTurret->m_iMeshID);
	glEndList();

	glNewList(maingun, GL_COMPILE);
	DrawOBJ(tankMainGun->m_iMeshID);
	glEndList();

	glNewList(secondarygun, GL_COMPILE);
	DrawOBJ(tankSecondaryGun->m_iMeshID);
	glEndList();

	glNewList(wheels, GL_COMPILE);
	DrawOBJ(tankWheel->m_iMeshID);
	glEndList();
	
  //blend colours across the surface of the polygons
  //another mode to try is GL_FLAT which is flat shading
  glShadeModel(GL_SMOOTH);
  //turn lighting off
  glDisable(GL_LIGHTING);
  //enable OpenGL hidden surface removal
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);

  GLfloat specular[] = {0.2,0.2,0.2,1.0};
  GLfloat ambient[] = {1.0,1.0,1.0,1.0};
  GLfloat diffuse[] = {1.0,1.0,1.0,1.0};
  GLfloat position[] = {0.0,30.0,0.0,1.0};
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHTING);

  GLfloat position1[] = {10.0,30.0,0.0,1.0};
  glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, position1);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHTING);



  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_TEXTURE_2D);
 
}

void buildsphere(void)
{
	bstankbody = BoundingSphere(tankBody, mbody);   //**************调用boundingsphere class 里的函数，求出圆心和半径
	bsturret = BoundingSphere(tankTurret, mturret); 
	bsmaingun = BoundingSphere(tankMainGun, mmaingun);
	bssecondarygun = BoundingSphere(tankSecondaryGun, msecondarygun);

	buildwholetanksphere();


}
void buildwholetanksphere(void)
{
	int num = (tankBody->m_iNumberOfVertices
		+ tankTurret->m_iNumberOfVertices
		+ tankMainGun->m_iNumberOfVertices
		+ tankSecondaryGun->m_iNumberOfVertices);

	bstank.center.x = bstankbody.center.x*tankBody->m_iNumberOfVertices
		+ bsturret.center.x*tankTurret->m_iNumberOfVertices
		+ bsmaingun.center.x*tankMainGun->m_iNumberOfVertices
		+ bssecondarygun.center.x*tankSecondaryGun->m_iNumberOfVertices;
	bstank.center.x /= num;

	bstank.center.y = bstankbody.center.y*tankBody->m_iNumberOfVertices
		+ bsturret.center.y*tankTurret->m_iNumberOfVertices
		+ bsmaingun.center.y*tankMainGun->m_iNumberOfVertices
		+ bssecondarygun.center.y*tankSecondaryGun->m_iNumberOfVertices;
	bstank.center.y /= num;

	bstank.center.z = bstankbody.center.z*tankBody->m_iNumberOfVertices
		+ bsturret.center.z*tankTurret->m_iNumberOfVertices
		+ bsmaingun.center.z*tankMainGun->m_iNumberOfVertices
		+ bssecondarygun.center.z*tankSecondaryGun->m_iNumberOfVertices;
	bstank.center.z /= num;

	//***************************the radius of whole tank sphere

	const int lg[4] = { tankBody->m_iNumberOfVertices
		, tankTurret->m_iNumberOfVertices
		, tankMainGun->m_iNumberOfVertices
		, tankSecondaryGun->m_iNumberOfVertices };
	int num1 = lg[0] + lg[1] + lg[2] + lg[3];

	MyPosition*whole1 = new MyPosition[lg[0]];
	MyPosition*whole2 = new MyPosition[lg[1]];
	MyPosition*whole3 = new MyPosition[lg[2]];
	MyPosition*whole4 = new MyPosition[lg[3]];
	MyPosition*whole = new MyPosition[num1];

	for (int i = 0; i < lg[0]; i++)  //*************************将tankbody的点的坐标转换
	{
		
		whole1[i].x = mbody[0] * tankBody->m_aVertexArray[i].x + mbody[4] * tankBody->m_aVertexArray[i].y + mbody[8] * tankBody->m_aVertexArray[i].z + mbody[12];
		whole1[i].y = mbody[1] * tankBody->m_aVertexArray[i].x + mbody[5] * tankBody->m_aVertexArray[i].y + mbody[9] * tankBody->m_aVertexArray[i].z + mbody[13];
		whole1[i].z = mbody[2] * tankBody->m_aVertexArray[i].x + mbody[6] * tankBody->m_aVertexArray[i].y + mbody[10] * tankBody->m_aVertexArray[i].z + mbody[14];
	}

	for (int i = 0; i < lg[1]; i++)   //********************turret
	{

		whole2[i].x = mturret[0] * tankTurret->m_aVertexArray[i].x + mturret[4] * tankTurret->m_aVertexArray[i].y + mturret[8] * tankTurret->m_aVertexArray[i].z + mturret[12];
		whole2[i].y = mturret[1] * tankTurret->m_aVertexArray[i].x + mturret[5] * tankTurret->m_aVertexArray[i].y + mturret[9] * tankTurret->m_aVertexArray[i].z + mturret[13];
		whole2[i].z = mturret[2] * tankTurret->m_aVertexArray[i].x + mturret[6] * tankTurret->m_aVertexArray[i].y + mturret[10] * tankTurret->m_aVertexArray[i].z + mturret[14];
	}

	for (int i = 0; i < lg[2]; i++)  //*************************将miangun的点的坐标转换
	{

		whole3[i].x = mmaingun[0] * tankMainGun->m_aVertexArray[i].x + mmaingun[4] * tankMainGun->m_aVertexArray[i].y + mmaingun[8] * tankMainGun->m_aVertexArray[i].z + mmaingun[12];
		whole3[i].y = mmaingun[1] * tankMainGun->m_aVertexArray[i].x + mmaingun[5] * tankMainGun->m_aVertexArray[i].y + mmaingun[9] * tankMainGun->m_aVertexArray[i].z + mmaingun[13];
		whole3[i].z = mmaingun[2] * tankMainGun->m_aVertexArray[i].x + mmaingun[6] * tankMainGun->m_aVertexArray[i].y + mmaingun[10] * tankMainGun->m_aVertexArray[i].z + mmaingun[14];
	}

	for (int i = 0; i < lg[3]; i++)  //*************************将secondarygun的点的坐标转换
	{

		whole4[i].x = msecondarygun[0] * tankSecondaryGun->m_aVertexArray[i].x + msecondarygun[4] * tankSecondaryGun->m_aVertexArray[i].y + msecondarygun[8] * tankSecondaryGun->m_aVertexArray[i].z + msecondarygun[12];
		whole4[i].y = msecondarygun[1] * tankSecondaryGun->m_aVertexArray[i].x + msecondarygun[5] * tankSecondaryGun->m_aVertexArray[i].y + msecondarygun[9] * tankSecondaryGun->m_aVertexArray[i].z + msecondarygun[13];
		whole4[i].z = msecondarygun[2] * tankSecondaryGun->m_aVertexArray[i].x + msecondarygun[6] * tankSecondaryGun->m_aVertexArray[i].y + msecondarygun[10] * tankSecondaryGun->m_aVertexArray[i].z + msecondarygun[14];
	}

	memcpy(whole, whole1, lg[0] * sizeof(MyPosition));
	memcpy(whole+lg[0], whole2, lg[1] * sizeof(MyPosition));
	memcpy(whole+lg[0]+lg[1], whole3, lg[2] * sizeof(MyPosition));
	memcpy(whole+lg[0]+lg[1]+lg[2], whole4, lg[3] * sizeof(MyPosition));

	float r = 0.0;
	float temp_r = 0.0;

	for (int i = 0; i < num1; i++)
	{
		temp_r = powf(whole[i].x - bstank.center.x, 2) +
			powf(whole[i].y - bstank.center.y, 2) +
			powf(whole[i].z - bstank.center.z, 2);
		if (temp_r > r)
			r = temp_r;
	}
	bstank.radius = sqrt(r);
	printf("tank.center:");
	printf("%f,%f,%f\n", bstank.center.x, bstank.center.y, bstank.center.z);

}

void drawsphere(void)     
{
	buildsphere();
	pointpenetrate();
	//************************draw tankbody sphere
	glPushMatrix();
	
	glTranslatef(bstankbody.center.x, bstankbody.center.y, bstankbody.center.z-zPos);   //*************z轴要-zpos?? ，为什么？？？
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);   //*******才会有透明效果
	glDisable(GL_DEPTH_TEST);
	//glColor4f(1.0, 0.0, 0.0, 0.1);
	glColor4f(tankbody_c1, tankbody_c2, tankbody_c3, 0.1);//**********透明
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	GLUquadric* tankbodysphere = gluNewQuadric();
	gluQuadricDrawStyle(tankbodysphere, GLU_FILL);
	gluQuadricNormals(tankbodysphere, GLU_SMOOTH);
	gluSphere(tankbodysphere, bstankbody.radius, 25, 20);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();
	
	
	glPushMatrix();

	glTranslatef(bsturret.center.x, bsturret.center.y, bsturret.center.z -zPos);   
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glColor4f(turret_c1, turret_c2, turret_c3, 0.1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	GLUquadric*bsturretsphere = gluNewQuadric();
	gluQuadricDrawStyle(bsturretsphere, GLU_FILL);
	gluQuadricNormals(bsturretsphere, GLU_SMOOTH);
	gluSphere(bsturretsphere, bsturret.radius, 20, 20);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();
	
	glPushMatrix();

	glTranslatef(bsmaingun.center.x, bsmaingun.center.y, bsmaingun.center.z - zPos);   
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glColor4f(maingun_c1, maingun_c2, maingun_c3, 0.1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	GLUquadric*bsmaingunsphere = gluNewQuadric();
	gluQuadricDrawStyle(bsmaingunsphere, GLU_FILL);
	gluQuadricNormals(bsmaingunsphere, GLU_SMOOTH);
	gluSphere(bsmaingunsphere, bsmaingun.radius, 20, 15);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix(); //************************secondarygun sphere

	glTranslatef(bssecondarygun.center.x, bssecondarygun.center.y, bssecondarygun.center.z - zPos);   
	
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glColor4f(secondarygun_c1, secondarygun_c2, secondarygun_c3, 0.1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	GLUquadric*bssecondarygunsphere = gluNewQuadric();
	gluQuadricDrawStyle(bssecondarygunsphere, GLU_FILL);
	gluQuadricNormals(bssecondarygunsphere, GLU_SMOOTH);
	gluSphere(bssecondarygunsphere, bssecondarygun.radius, 15, 15);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();      //************************************the whole tank sphere

	glTranslatef(bstank.center.x, bstank.center.y, bstank.center.z - zPos);   //*************z轴要-zpos?? ，为什么？？？
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glColor4f(tank_c1, tank_c2, tank_c3, 0.1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	GLUquadric* tanksphere = gluNewQuadric();
	gluQuadricDrawStyle(tanksphere, GLU_FILL);
	gluQuadricNormals(tanksphere, GLU_SMOOTH);
	gluSphere(tanksphere, bstank.radius, 25, 20);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();
}

void pointpenetrate(void)
{
	//p.z = p.z - zPos;      //为什么tank旋转，红色的sphere也跟着变？？？？？
	glPushMatrix();
	glPointSize(10.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex3f(p.x, p.y, p.z-zPos);
	glEnd();
	glPopMatrix();

	printf("point:");
	printf("%f,%f,%f\n",p.x, p.y, p.z);

	float d1,d2,d3,d4,d5;
	d1 = sqrt(powf(p.x - bstank.center.x, 2) +  //******tank center
		powf(p.y - bstank.center.y, 2) +
		powf(p.z - bstank.center.z, 2));
	d2 = sqrt(powf(p.x - bstankbody.center.x, 2) +  //******tankbody center
		powf(p.y - bstankbody.center.y, 2) +
		powf(p.z - bstankbody.center.z, 2));
	d3 = sqrt(powf(p.x - bsturret.center.x, 2) +  //******turret center
		powf(p.y - bsturret.center.y, 2) +
		powf(p.z - bsturret.center.z, 2));
	d4 = sqrt(powf(p.x - bsmaingun.center.x, 2) +  //******maingun center
		powf(p.y - bsmaingun.center.y, 2) +
		powf(p.z - bsmaingun.center.z, 2));
	d5 = sqrt(powf(p.x - bssecondarygun.center.x, 2) +  //******sencondgun center
		powf(p.y - bssecondarygun.center.y, 2) +
		powf(p.z - bssecondarygun.center.z, 2));

	
	if (d1 < bstank.radius)
	{
		if (d2 < bstankbody.radius)
		{
			tankbody_c1 = 1.0;
			tankbody_c2 = 0.0;
			tankbody_c3 = 0.0;
		}
		else
		{
			tankbody_c1 = 1.0;
			tankbody_c2 = 1.0;
			tankbody_c3 = 1.0;
		}
		if (d3 < bsturret.radius)
		{
			turret_c1 = 1.0;
			turret_c2 = 0.0;
			turret_c3 = 0.0;
		}
		else
		{
			turret_c1 = 1.0;
			turret_c2 = 1.0;
			turret_c3 = 1.0;
		}
	
		if (d4 < bsmaingun.radius)
		{
			maingun_c1 = 1.0;
			maingun_c2 = 0.0;
			maingun_c3 = 0.0;
		}
		else
		{
			maingun_c1 = 1.0;
			maingun_c2 = 1.0;
			maingun_c3 = 1.0;
		}
		if (d5 < bssecondarygun.radius)
		{
			secondarygun_c1 = 1.0;
			secondarygun_c2 = 0.0;
			secondarygun_c3 = 0.0;
		}
		else
		{
			secondarygun_c1 = 1.0;
			secondarygun_c2 = 1.0;
			secondarygun_c3 = 1.0;
		};
		tank_c1 = 1.0;
		tank_c2 = 0.0;
		tank_c3 = 0.0;
	
    }
else{
	tank_c1 = 1.0;
	tank_c2 = 1.0;
	tank_c3 = 1.0;
    }
	
}