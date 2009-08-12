#include <windows.h>
#include <cstring>
#include <iostream>
#include <GL/glut.h>
#include "app.hpp"
#include "globals.hpp"

namespace aks
{
	namespace visualization
	{		
		void Application::initGraphics()
		{
		    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		    glEnable(GL_DEPTH_TEST);
		    glShadeModel(GL_SMOOTH);
		
		    setView();
		}
		
		void Application::setView()
		{
		    glMatrixMode(GL_PROJECTION);
		    glLoadIdentity();
		    gluPerspective(60.0, (double)width/(double)height, 0.1, 500.0);
		    glMatrixMode(GL_MODELVIEW);
		}
		
		void Application::display()
		{
		    glClear(GL_COLOR_BUFFER_BIT);
            glLoadIdentity();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            gluLookAt(  0.0f, 5.0f, 15.0f,
                        0.0f, 0.0f, 0.0f,
                        0.0, 1.0, 0.0);
		}
		
		const char* Application::getTitle()
		{
		    return "Application - Aks...";
		}
		
		void Application::deinit()
		{
		}
		
		void Application::update()
		{
		    glutPostRedisplay();
		}
		
		void Application::key(unsigned char key)
		{
		}
		
		
		void Application::resize(int width, int height)
		{
		    // Avoid the divide by zero.
		    if (height <= 0) height = 1;
		
		    // Set the internal variables and update the view
		    Application::width = width;
		    Application::height = height;
		    glViewport(0, 0, width, height);
		    setView();
		}


		
		void Application::mouse(int button, int state, int x, int y)
		{
		}
		
		void Application::mouseDrag(int x, int y)
		{
		}
		
		// The following methods aren't intended to be overloaded
		void Application::renderText(float x, float y, const char *text, void *font)
		{
		    glDisable(GL_DEPTH_TEST);
		
		    // Temporarily set up the view in orthographic projection.
		    glMatrixMode(GL_PROJECTION);
		    glPushMatrix();
		    glLoadIdentity();
		    glOrtho(0.0, (double)width, 0.0, (double)height, -1.0, 1.0);
		
		    // Move to modelview mode.
		    glMatrixMode(GL_MODELVIEW);
		    glPushMatrix();
		    glLoadIdentity();
		
		    // Ensure we have a font
		    if (font == NULL) {
		        font = GLUT_BITMAP_HELVETICA_10;
		    }
		
		    // Loop through characters displaying them.
		    size_t len = strlen(text);
		
		    glRasterPos2f(x, y);
		    for (const char *letter = text; letter < text+len; letter++) {
		
		        // If we meet a newline, then move down by the line-height
		        // TODO: Make the line-height a function of the font
		        if (*letter == '\n') {
		            y -= 12.0f;
		            glRasterPos2f(x, y);
		        }
		        glutBitmapCharacter(font, *letter);
		    }
		
		    // Pop the matrices to return to how we were before.
		    glPopMatrix();
		    glMatrixMode(GL_PROJECTION);
		    glPopMatrix();
		    glMatrixMode(GL_MODELVIEW);
		
		    glEnable(GL_DEPTH_TEST);
		}
	}
}
