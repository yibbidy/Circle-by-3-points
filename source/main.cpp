// Contributors:  Justin Hutchison (yibbidy@gmail.com)

#include <windows.h>
#include "gl/glut.h"
#include <math.h>

int gWindowWidth = 0;
int gWindowHeight;
float gXs[3], gYs[3];

void DrawCircle() {
	const float PI = 3.141592654f;

	float A1 = 2*(gYs[0]-gYs[1]);
	float A2 = 2*(gYs[0]-gYs[2]);
	float B1 = gYs[1]*gYs[1] - gYs[0]*gYs[0] + gXs[1]*gXs[1] - gXs[0]*gXs[0];
	float B2 = gYs[2]*gYs[2] - gYs[0]*gYs[0] + gXs[2]*gXs[2] - gXs[0]*gXs[0];
	float C1 = 2*(gXs[2]-gXs[0]);
	float C2 = 2*(gXs[1]-gXs[0]);

	float b = (B2*C2 - B1*C1) / (A1*C1 - A2*C2);
	float a = (b*A1 + B1) / C2;
	float r = sqrt( pow(a-gXs[1], 2) + pow(b-gYs[1], 2) );

	glColor3f(1, 1, 1);
	glBegin(GL_LINE_STRIP);
	for( float t=0; t<=2*PI+0.1f; t+=0.1f ) {
		float x = r*cos(t) + a;
		float y = r*sin(t) + b;

		glVertex2f(x, y);
	}
	glEnd();
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0, 1, 0);
	glBegin(GL_POINTS);
	for( int i=0; i<3; ++i ) glVertex2f(gXs[i], gYs[i]);
	glEnd();

    DrawCircle();

	glutSwapBuffers();
}

void Reshape(GLint width, GLint height)
{
	gWindowWidth = width;
	gWindowHeight = height;

   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1, 1, -1, 1, -1, 1);
   glMatrixMode(GL_MODELVIEW);
}

void InitGraphics(void)
{
	glPointSize(8);

	gXs[0] = 0;
	gYs[0] = 0;
	gXs[1] = .5;
	gYs[1] = 0;
	gXs[2] = 0;
	gYs[2] = .8;

}

void MouseButton(int button, int state, int x, int y)
{
	static int count = 0;
	if( GLUT_DOWN == state ) {
		gXs[count%3] = x/(float)gWindowWidth * 2 - 1;
		gYs[count%3] = (gWindowHeight-y)/(float)gWindowHeight * 2 - 1;
		++count;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
  // GLUT Window Initialization:
  glutInit (&argc, argv);
  glutInitWindowSize (640, 480);
  glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE);
  glutCreateWindow ("Circle by 3 points");
  
  // Initialize OpenGL graphics state
  InitGraphics();

  // Register callbacks:
  glutDisplayFunc (Display);
  glutReshapeFunc (Reshape);
  glutMouseFunc (MouseButton);
  glutMainLoop ();
  return 0;
}
 
