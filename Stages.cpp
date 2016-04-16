#include "Stages.h"

#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>

Stages::Stages()
{
}


Stages::~Stages()
{
}

/***********************************************************************************************/
/*                                          Shapes                                             */
/***********************************************************************************************/

// Pentagon
void Stages::pentagon(float rot_angle) {

	glPushMatrix();
	glTranslatef(1.0f, 1.0f, 0.0f);		//Translate to center of pentagon
	glRotatef(rot_angle, 0.0f, 1.0f, 0.0f);
	//glScalef(0.7f, 0.7f, 0.7f);				//draw pentagon at 70% size
	glBegin(GL_TRIANGLES); //Begin triangle coordinates
	glColor3f(0.0f, 0.75f, 0.0f);	//green

	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);

	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);

	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);

	glEnd();
	glPopMatrix();
}

// Trapezoid
void Stages::trapezoid(float rot_angle) {

	glPushMatrix();		//Save transformation draw_test
	glTranslatef(0.0f, -1.0f, 0.0f);	//translate to center of trapezoid
	glRotatef(rot_angle, 0.0f, 0.0f, 1.0f);	//Rotation angle and axis
	glBegin(GL_QUADS); //Begin quadrilateral coordinates

	glColor3f(0.5f, 0.0f, 0.8f);
	glVertex3f(-0.7f, -0.5f, 0.0f);			//Points are relative to center of trapezoid
	glColor3f(0.f, 0.9f, 0.0f);
	glVertex3f(0.7f, -0.5f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.4f, 0.5f, 0.0f);
	glColor3f(0.0f, 0.65f, 0.65f);
	glVertex3f(-0.4f, 0.5f, 0.0f);

	glEnd(); //End quadrilateral coordinates
	glPopMatrix();		//Restore transformation draw_test
}


// Triangle
void Stages::triangle(float rot_angle){	

	glTranslatef(-1.0f, 1.0f, 0.0f);
	glRotatef(rot_angle, 1.0f, 2.0f, 3.0f);	//Rotate around vector (1,2,3)
	glBegin(GL_TRIANGLES);

	glColor3f(1.0f, 0.7f, 0.8f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);

	glEnd(); //End triangle coordinates	
}


// Cube
void Stages::cube(float angle) {	

	glRotatef(angle, 1.0, 0.0, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidCube(2);
}


/**************************************************************************************************/
/*                                              Fog                                               */
/**************************************************************************************************/

void Stages::fog() {

	GLfloat density = 0.3; //set the density to 0.3 which is actually quite thick
	GLfloat fogColor[4] = { 0.5, 0.5, 0.5, 1.0 }; //set the for color to grey

	glFogi(GL_FOG_MODE, GL_EXP2); //set the fog mode to GL_EXP2
	glFogfv(GL_FOG_COLOR, fogColor); //set the fog color to our color chosen above
	glFogf(GL_FOG_DENSITY, density); //set the density to the value above
	glHint(GL_FOG_HINT, GL_NICEST); // set the fog to look the nicest, may slow down on older cards
}


/**************************************************************************************************/
/*                                             Text                                               */
/**************************************************************************************************/

void Stages::text(std::string menu, GLint x, GLint y) {

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);  // move in from the left and bottom edges 

	for (int i = 0; i < menu.length(); ++i) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, menu[i]);
	}
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


/***********************************************************************************************/
/*                                           Lighting                                          */
/***********************************************************************************************/

void Stages::lighting(float rot_angle) {

	glTranslatef(0.0f, 0.0f, -8.0f);

	//Add ambient light
	GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f }; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//Add positioned light
	GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = { 4.0f, 0.0f, 8.0f, 1.0f }; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	//Add directed light
	GLfloat lightColor1[] = { 0.5f, 0.2f, 0.2f, 1.0f }; //Color (0.5, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = { -1.0f, 0.5f, 0.5f, 0.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	glRotatef(rot_angle, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);

	//Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.5f, -1.0f, 1.5f);
	glVertex3f(1.5f, -1.0f, 1.5f);
	glVertex3f(1.5f, 1.0f, 1.5f);
	glVertex3f(-1.5f, 1.0f, 1.5f);

	//Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.5f, -1.0f, -1.5f);
	glVertex3f(1.5f, 1.0f, -1.5f);
	glVertex3f(1.5f, 1.0f, 1.5f);
	glVertex3f(1.5f, -1.0f, 1.5f);

	//Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, -1.0f, -1.5f);
	glVertex3f(-1.5f, 1.0f, -1.5f);
	glVertex3f(1.5f, 1.0f, -1.5f);
	glVertex3f(1.5f, -1.0f, -1.5f);

	//Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.5f, -1.0f, -1.5f);
	glVertex3f(-1.5f, -1.0f, 1.5f);
	glVertex3f(-1.5f, 1.0f, 1.5f);
	glVertex3f(-1.5f, 1.0f, -1.5f);

	glEnd();
}