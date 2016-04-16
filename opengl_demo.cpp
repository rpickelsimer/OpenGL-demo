/*		opengl_demo.cpp
		
		Ryan Pickelsimer
		3/16/15
		Computer Graphics
		
		This program demonstrates several features of OpenGL including shapes, coloring, motion, lighting, text, and fog.
*/

//#include <iostream>
#include <stdlib.h>		// needed for "exit" function

#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>

#include "Stages.h"  // includes <iostream>

using namespace std;

// Rotation angle for polygons
float rot_angle = 30.0f;

// used in drawScene()
Stages stage;
int draw_test = 0;

/**************************************************************************************/
/*                                   Camera Controls                                  */
/**************************************************************************************/

// for moving camera
float deltaAngle = 0.0f;
float deltaMove = 0.0f;
float deltaStrafe = 0.0f;
// factor to translate left and right
float strafe = 0.0f;
// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;

void computeCameraPos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void computeCameraDir(float deltaAngle) {

	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}

void computeStrafe(float deltaStrafe) {

	strafe += deltaStrafe;
}


/***********************************************************************************************/
/*                                       Keyboard Controls                                     */
/***********************************************************************************************/

// ESC
void handleKeypress(unsigned char key,
	int x, int y) {		//The current mouse coordinates
	switch (key) {
	case 27:	//ESC key
		exit(0);	
		break;
	case 32:	//space bar
		draw_test += 1;
		break;
	}
}

// Camera UP, DOWN, ZOOM IN, ZOOM OUT
void handleSpecialKeypress(int key, int xx, int yy) {

	switch (key) {
	case GLUT_KEY_LEFT: deltaAngle = -0.005f; break;
	case GLUT_KEY_RIGHT: deltaAngle = 0.005f; break;
	case GLUT_KEY_UP: deltaMove = 0.5f; break;
	case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
	case GLUT_KEY_F1: deltaStrafe = 0.25f; break;
	case GLUT_KEY_F2: deltaStrafe = -0.25f; break;
	}
}

// Stop when key is released
void releaseKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT: deltaAngle = 0.0f; break;
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: deltaMove = 0; break;
	case GLUT_KEY_F1:
	case GLUT_KEY_F2: deltaStrafe = 0.0; break;
	}
}


/***********************************************************************************************/
/*                                         Update                                              */
/***********************************************************************************************/
void update(int value) {

	//increase rotation angle by 2 degrees
	rot_angle += 2.0f;
	if (rot_angle > 360) {
		rot_angle -= 360;
	}

	// update camera
	if (deltaMove)
		computeCameraPos(deltaMove);
	if (deltaAngle)
		computeCameraDir(deltaAngle);
	if (deltaStrafe)
		computeStrafe(deltaStrafe);

	glutPostRedisplay();	//tells Glut that scene has changed and needs to redraw
	glutTimerFunc(25, update, 0);	//call update again 25 milliseconds, 0 refers to the param value
}


/*********************************************************************************************/
/*                                      Console Window                                       */
/*********************************************************************************************/

//Move console window and display demo controls
void initConsoleWindow() {

	// Set console window to top left corner						//  User32.lib; User32.dll -> need this for .exe file?
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0,
		0,			// X pos
		0,			// Y pos
		100, 200, SWP_NOSIZE | SWP_NOZORDER);

	// Display demo controls in console window					
	cout << "CONTROLS" << endl << "--------" << endl;
	cout << "\nSPACE BAR: Next";
	cout << "\n\nLEFT ARROW: Move camera left";
	cout << "\nRIGHT ARROW: Move camera right";					// add strafe left strafe right
	cout << "\nUP ARROW: Zoom in";
	cout << "\nDOWN ARROW: Zoom out";
	cout << "\nF1: Strafe left";
	cout << "\nF2: Strafe right";
	cout << "\n\nESC: Quit";
	cout << endl << endl;

	// Five second countdown before demo starts
	int timer = 5;
	while (timer > -1)
	{
		cout << "\rPlease wait... " << timer;
		timer -= 1;
		Sleep(1000);
	}
}


/***********************************************************************************************/
/*                                       GLUT window resize                                    */
/***********************************************************************************************/

//Called when the window is resized
void handleResize(int w, int h) {
	//Tell OpenGl how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);	//Switch to setting the camera perspective --> allows transformations and animation, etc.
	//Only used in resizing window

	//Set the camera perspective
	glLoadIdentity();	//Reset the camera
	gluPerspective(45.0,			//The camera angle
		(double)w / (double)h,		//The width-to-height ratio
		1.0,						//The near z clipping coordinate	-->	don't draw things closer than 1 unit to eye
		200.0);						//The far z clipping coordinate		--> don't draw things further than 200 units from eye
}


/*********************************************************************************************/
/*                                          Draw                                             */
/*********************************************************************************************/

//Draws the 3D scene
void drawScene() {
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);		//Switch to the standard drawing perspective
	glLoadIdentity();				//Reset the drawing perspective
	//glRotatef(-_cameraAngle, 0.0f, 1.0f, 0.0f);		//Tip: rotate scene opposite direction instead of change camera angle

	// Set the camera
	gluLookAt(x, 1.0f, z,
		x + lx, 1.0f, z + lz,
		0.0f, 1.0f, 0.0f);

	glTranslatef(strafe, 1.0f, 0.0f);		// adjustment for more centered viewing	and strafe control


	if (draw_test > -1 && draw_test < 3) {					// 0 - 2 
		stage.pentagon(rot_angle);
		stage.text("Next: Space Bar", 350, 100);


		if (draw_test >0 && draw_test < 3) {				// 1 - 2
			stage.trapezoid(rot_angle);


			if (draw_test > 1 && draw_test < 3) {			// 2 
				//Set background color
				glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
				stage.triangle(rot_angle);
			}
		}
	}

	if (draw_test > 2 && draw_test < 5) {					// 3 - 4 cube
		stage.cube(rot_angle);


		if (draw_test == 4) {								// 4 fog
			glEnable(GL_FOG); //enable the fog
			stage.fog();
			stage.text("Zoom in and out with the up and down keys to see the fog effect!", 150, 100);
		}
	}

	
	if (draw_test == 5) {									// 5 Lighting
		
		glDisable(GL_FOG); //disable the fog

		glEnable(GL_LIGHTING); //Enable lighting
		glEnable(GL_LIGHT0); //Enable light #0
		glEnable(GL_LIGHT1); //Enable light #1
		glEnable(GL_NORMALIZE); //Automatically normalize normals

		stage.lighting(rot_angle);
		stage.text("Lighting", 370, 100);

	}


	if (draw_test > 5) {									// 6 End
		//Set background color
		glClearColor(1.0f, 1.0, 1.0, 1.0f);
		stage.text("Fin", 395, 300);

	}

	glutSwapBuffers();
}


/*************************************************************************************************/
/*                                            Main                                               */
/*************************************************************************************************/

int main(int argc, char** argv) {

	// Move console window and display demo controls
	initConsoleWindow();

	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	//Set window size
	glutInitWindowSize(800, 600);
	//Set Window position to center of screen
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 800) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - 600) / 2);
	//Create the window
	glutCreateWindow("MR. GLUT - Rpickelsimer");	

	//Makes 3D drawing work when something is in front of something else.
	glEnable(GL_DEPTH_TEST);
	//Enable color
	glEnable(GL_COLOR_MATERIAL);

	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(drawScene);

	glutKeyboardFunc(handleKeypress);
	glutSpecialFunc(handleSpecialKeypress);
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);

	glutReshapeFunc(handleResize);

	//Call update again 25 milliseconds after program starts
	glutTimerFunc(25, update, 0);

	//Start the main loop.
	glutMainLoop();		
	return 0;
}