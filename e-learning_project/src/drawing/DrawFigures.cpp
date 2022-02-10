#include "../../include/drawing/DrawFigures.h"


void DrawFigures::drawQueenWhite(std::array<float,16> tm)
{	// Move to marker-position
	glMatrixMode(GL_MODELVIEW);
	using namespace dtools;
	glPushMatrix();
	// Load the transpose matrix
	glLoadMatrixf(tm.data());

	// Rotate 90 degrees in z-direction
	glRotated(180, 1, 0, 0);

	// Scale down!
	glScalef(0.03, 0.03, 0.03);

	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	drawCone(.3, .8, 40, 40);
	glTranslatef(0, 0, 0.9);
	glRotated(180, 1, 0, 0);
	drawCone(.2, .8, 40, 40);
	drawSphere(.2, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glTranslatef(0, 0, 0.9);
	glRotated(-90, 1, 0, 0);
	drawCone(.08, .4, 40, 40);
	glTranslatef(0, 0, 0.4);
	glColor4f(1, 0.6, 0, 1.0);
	drawSphere(.06, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glTranslatef(0, 0, 0.9);
	glRotated(-45, 1, 0, 0);
	drawCone(.08, .4, 40, 40);
	glTranslatef(0, 0, 0.4);
	glColor4f(1, 0, 0, 1.0);
	drawSphere(.06, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glTranslatef(0, 0, 0.9);
	drawCone(.08, .4, 40, 40);
	glTranslatef(0, 0, 0.4);
	glColor4f(0, 1, 0, 1.0);
	drawSphere(.06, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glTranslatef(0, 0, 0.9);
	glRotated(45, 1, 0, 0);
	drawCone(.08, .4, 40, 40);
	glTranslatef(0, 0, 0.4);
	glColor4f(0, 0, 1, 1.0);
	drawSphere(.06, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glTranslatef(0, 0, 0.9);
	glRotated(90, 1, 0, 0);
	drawCone(.08, .4, 40, 40);
	glTranslatef(0, 0, 0.4);
	glColor4f(0.81, 0, 1, 1.0);
	drawSphere(.06, 40, 40);
	glPopMatrix();
	glPopMatrix();
}

void DrawFigures::drawPawnWhite(std::array<float,16> tm)
{	// Move to marker-position
	glMatrixMode(GL_MODELVIEW);
	using namespace dtools;
	glPushMatrix();
	glLoadMatrixf(tm.data());
	glRotatef(-90, 1, 0, 0);
	glScalef(0.03, 0.03, 0.03);
	glColor4f(1, 1, 1, 1.0);
	glRotated(-90, 1, 0, 0);
	drawCone(.25, .6, 40, 40);
	glRotated(90, 1, 0, 0);
	glTranslatef(0, .6, 0.0);
	drawSphere(.2, 40, 40);
	glPopMatrix();
}
void DrawFigures::drawRookWhite(std::array<float,16> tm)
{	// Move to marker-position
	glMatrixMode(GL_MODELVIEW);
	using namespace dtools;
	glPushMatrix();
	glLoadMatrixf(tm.data());
	glRotatef(-90, 1, 0, 0);
	glScalef(0.03, 0.03, 0.03);
	glColor4f(1, 1, 1, 1.0);

	glRotated(-90, 1, 0, 0);
	drawCone(.25, 0.8, 40, 40);

	glScalef(1.2, 1.2, 1.2);
	glTranslatef(0, 0, 0.75);
	glRotated(-180, 1, 1, 0);
	drawCone(.2, 0.8, 40, 40);
	glTranslatef(0, 0, -0.3);
	glRotated(90, 1, 0, 0);

	glTranslatef(-0.075, .25, .15);
	drawCube(0, 0, 0, .1);

	glTranslatef(.175, 0, 0);
	drawCube(0, 0, 0, .09);

	glTranslatef(0.05, 0, -.15);
	drawCube(0, 0, 0, .1);

	glTranslatef(-0.15, 0, -.15);
	drawCube(0, 0, 0, .1);

	glTranslatef(-.15, 0, 0.15);
	drawCube(0, 0, 0, .1);

	glPopMatrix();
}

void DrawFigures::drawBishop(std::array<float,16> tm)
{
	using namespace dtools;
	// Load the transpose matrix
	glLoadMatrixf(tm.data());
	// Rotate 90 degrees in z-direction
	glRotated(180, 1, 0, 0);
	// Scale down!
	glScalef(0.03, 0.03, 0.03);

	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	drawCone(.3, .6, 40, 40);
	glTranslatef(0, 0, 0.7);
	glRotated(180, 1, 1, 0);
	drawCone(.25, .6, 40, 40);
	drawSphere(.25, 40, 40);
	glTranslatef(0, 0, -0.25);
	drawSphere(.15, 40, 40);
	glPopMatrix();

}

void DrawFigures::drawBishop2(std::array<float,16> tm)
{
	using namespace dtools;
	// Load the transpose matrix
	glLoadMatrixf(tm.data());
	// Rotate 90 degrees in z-direction
	glRotated(180, 1, 0, 0);
	// Scale down!
	glScalef(0.03, 0.03, 0.03);

	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	drawCone(.3, .8, 40, 40);
	glTranslatef(0, 0, 0.7);
	drawSphere(.25, 40, 40);
	drawCone(.25, .8, 4, 4);
	glPopMatrix();

}

void DrawFigures::drawKingWhite(std::array<float,16> tm)
{
	using namespace dtools;
	// Load the transpose matrix
	glLoadMatrixf(tm.data());
	// Rotate 90 degrees in z-direction
	glRotated(180, 1, 0, 0);
	// Scale down!
	glScalef(0.03, 0.03, 0.03);

	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	drawCone(.3, .6, 40, 40);
	glTranslatef(0, 0, 0.7);
	glRotated(180, 0, 1, 0);
	glRotated(-180, 1, 0, 0);
	drawCone(.25, .6, 40, 40);
	glRotated(180, 1, 1, 0);
	drawSphere(.25, 40, 40);
	glTranslatef(0, 0, -0.3);
	drawSphere(.15, 40, 40);
	glTranslatef(0, 0, -0.2);
	glRotated(180, 1, 1, 0);
	drawCube(0, 0, 0, 0.1);
	drawCube(0, 0, 0.1, 0.1);
	drawCube(0, 0, 0.2, 0.1);
	drawCube(0, 0, 0.3, 0.1);
	drawCube(0, 0.1, 0.2, 0.1);
	drawCube(0, -0.1, 0.2, 0.1);
	glPopMatrix();

}

void DrawFigures::drawKnightWhite(std::array<float,16> tm)
{
	using namespace dtools;
	// Load the transpose matrix
	glLoadMatrixf(tm.data());
	// Rotate 90 degrees in z-direction
	glRotated(180, 1, 0, 0);
	// Scale down!
	glScalef(0.03, 0.03, 0.03);

	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glRotated(180, 0, 0, 1);
	drawCone(.3, .8, 40, 40);
	glRotated(180, 0, 0, 1);
	glTranslatef(0, 0, 0.7);
	drawSphere(.25, 40, 40);
	glRotatef(120, 1, 0, 0);
	glTranslatef(0, 0, 0.25);
	drawSphere(.17, 40, 40);
	glPopMatrix();

	// Pretty hair, don't care
	glPushMatrix();
	glTranslatef(0, 0, 1);
	drawCube(0, 0, 0, 0.15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.2, 0.95);
	glRotated(180, 1, 0, 0);
	glRotatef(50, 1, 0, 0);
	drawCube(0, 0, 0, 0.15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.3, 0.75);
	drawCube(0, 0, 0, 0.15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.25, 0.55);
	glRotated(180, 1, 0, 0);
	glRotatef(50, 1, 0, 0);
	drawCube(0, 0, 0, 0.15);
	glPopMatrix();
}

void DrawFigures::drawQueenBlack(std::array<float, 16> tm)
{	// Move to marker-position
	glMatrixMode(GL_MODELVIEW);
	using namespace dtools;
	glPushMatrix();
	// Load the transpose matrix
	glLoadMatrixf(tm.data());

	// Rotate 90 degrees in z-direction
	glRotated(180, 1, 0, 0);

	// Scale down!
	glScalef(0.03, 0.03, 0.03);

	glPushMatrix();
	glColor4f(.1, .1, .1, 1);
	drawCone(.3, .8, 40, 40);
	glTranslatef(0, 0, 0.9);
	glRotated(180, 1, 0, 0);
	drawCone(.2, .8, 40, 40);
	drawSphere(.2, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glColor4f(.1, .1, .1, 1);
	glTranslatef(0, 0, 0.9);
	glRotated(-90, 1, 0, 0);
	drawCone(.08, .4, 40, 40);
	glTranslatef(0, 0, 0.4);
	glColor4f(1, 0.6, 0, 1.0);
	drawSphere(.06, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.0, 0.0, 0.0, 1.0);
	glTranslatef(0, 0, 0.9);
	glRotated(-45, 1, 0, 0);
	drawCone(.08, .4, 40, 40);
	glTranslatef(0, 0, 0.4);
	glColor4f(1, 0, 0, 1.0);
	drawSphere(.06, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glColor4f(.1, .1, .1, 1);
	glTranslatef(0, 0, 0.9);
	drawCone(.08, .4, 40, 40);
	glTranslatef(0, 0, 0.4);
	glColor4f(0, 1, 0, 1.0);
	drawSphere(.06, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glColor4f(.1, .1, .1, 1);
	glTranslatef(0, 0, 0.9);
	glRotated(45, 1, 0, 0);
	drawCone(.08, .4, 40, 40);
	glTranslatef(0, 0, 0.4);
	glColor4f(0, 0, 1, 1.0);
	drawSphere(.06, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glColor4f(.1, .1, .1, 1);
	glTranslatef(0, 0, 0.9);
	glRotated(90, 1, 0, 0);
	drawCone(.08, .4, 40, 40);
	glTranslatef(0, 0, 0.4);
	glColor4f(0.81, 0, 1, 1.0);
	drawSphere(.06, 40, 40);
	glPopMatrix();
	glPopMatrix();
}

void DrawFigures::drawPawnBlack(std::array<float, 16> tm)
{	// Move to marker-position
	glMatrixMode(GL_MODELVIEW);
	using namespace dtools;
	glPushMatrix();
	glLoadMatrixf(tm.data());
	glRotatef(-90, 1, 0, 0);
	glScalef(0.03, 0.03, 0.03);
	glColor4f(.1, .1, .1, 1);
	glRotated(-90, 1, 0, 0);
	drawCone(.25, .6, 40, 40);
	glRotated(90, 1, 0, 0);
	glTranslatef(0, .6, 0.0);
	drawSphere(.2, 40, 40);
	glPopMatrix();
}
void DrawFigures::drawRookBlack(std::array<float, 16> tm)
{	// Move to marker-position
	glMatrixMode(GL_MODELVIEW);
	using namespace dtools;
	glPushMatrix();
	glLoadMatrixf(tm.data());
	glRotatef(-90, 1, 0, 0);
	glScalef(0.03, 0.03, 0.03);
	glColor4f(.1, .1, .1, 1);

	glRotated(-90, 1, 0, 0);
	drawCone(.25, 0.8, 40, 40);

	glScalef(1.2, 1.2, 1.2);
	glTranslatef(0, 0, 0.75);
	glRotated(-180, 0, 1, 0);
	drawCone(.2, 0.8, 40, 40);
	glRotated(90, 1, 0, 0);


	glRotated(180, 0, 0, 1); 
	glTranslatef(-0.075, 0.01, .15);
	drawCube(0, 0, 0, .1);

	glTranslatef(.175, 0, 0);
	drawCube(0, 0, 0, .09);

	glTranslatef(0.05, 0, -.15);
	drawCube(0, 0, 0, .1);

	glTranslatef(-0.15, 0, -.15);
	drawCube(0, 0, 0, .1);

	glTranslatef(-.15, 0, 0.15);
	drawCube(0, 0, 0, .1);

	glPopMatrix();
}

void DrawFigures::drawBishopBlack(std::array<float, 16> tm)
{
	using namespace dtools;
	// Load the transpose matrix
	glLoadMatrixf(tm.data());
	// Rotate 90 degrees in z-direction
	glRotated(180, 1, 0, 0);
	// Scale down!
	glScalef(0.03, 0.03, 0.03);

	glPushMatrix();
	glColor4f(.1, .1, .1, 1);
	drawCone(.3, .6, 40, 40);
	glTranslatef(0, 0, 0.7);
	glRotated(180, 0, 1, 0);
	drawCone(.25, .6, 40, 40);
	drawSphere(.25, 40, 40);
	glTranslatef(0, 0, -0.25);
	drawSphere(.15, 40, 40);
	glPopMatrix();

}

void DrawFigures::drawBishop2Black(std::array<float, 16> tm)
{
	using namespace dtools;
	// Load the transpose matrix
	glLoadMatrixf(tm.data());
	// Rotate 90 degrees in z-direction
	glRotated(180, 1, 0, 0);

	// Scale down!
	glScalef(0.03, 0.03, 0.03);

	glPushMatrix();
	glColor4f(.1, .1, .1, 1);
	drawCone(.3, .8, 40, 40);
	glTranslatef(0, 0, 0.7);
	drawSphere(.25, 40, 40);
	drawCone(.25, .8, 4, 4);
	glPopMatrix();

}

void DrawFigures::drawKingBlack(std::array<float, 16> tm)
{
	using namespace dtools;
	// Load the transpose matrix
	glLoadMatrixf(tm.data());
	// Rotate 90 degrees in z-direction
	glRotated(180, 1, 0, 0);

	// Scale down!
	glScalef(0.03, 0.03, 0.03);

	glPushMatrix();
	glColor4f(.1, .1, .1, 1);
	drawCone(.3, .6, 40, 40);
	glTranslatef(0, 0, 0.7);
	glRotated(180, 0, 1, 0);
	drawCone(.25, .6, 40, 40);
	drawSphere(.25, 40, 40);
	glTranslatef(0, 0, -0.3);
	drawSphere(.15, 40, 40);
	glTranslatef(0, 0, -0.2);
	glRotated(180, 1, 0, 0);
	drawCube(0, 0, 0, 0.1);
	drawCube(0, 0, 0.1, 0.1);
	drawCube(0, 0, 0.2, 0.1);
	drawCube(0, 0, 0.3, 0.1);
	drawCube(0, 0.1, 0.2, 0.1);
	drawCube(0, -0.1, 0.2, 0.1);
	glPopMatrix();
}

void DrawFigures::drawKnightBlack(std::array<float, 16> tm)
{
	using namespace dtools;
	// Load the transpose matrix
	glLoadMatrixf(tm.data());
	// Rotate 90 degrees in z-direction
	glRotated(180, 1, 0, 0);

	// Scale down!
	glScalef(0.03, 0.03, 0.03);

	glPushMatrix();
	glColor4f(.1, .1, .1, 1);
	drawCone(.3, .8, 40, 40);
	glTranslatef(0, 0, 0.7);
	drawSphere(.25, 40, 40);
	glRotatef(120, 1, 0, 0);
	glTranslatef(0, 0, 0.25);
	drawSphere(.17, 40, 40);
	glPopMatrix();

	// Pretty hair, don't care
	glPushMatrix();
	glTranslatef(0, 0, 1);
	drawCube(0, 0, 0, 0.15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.2, 0.95);
	glRotatef(50, 1, 0, 0);
	drawCube(0, 0, 0, 0.15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.3, 0.75);
	drawCube(0, 0, 0, 0.15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.25, 0.55);
	glRotatef(50, 1, 0, 0);
	drawCube(0, 0, 0, 0.15);
	glPopMatrix();
}