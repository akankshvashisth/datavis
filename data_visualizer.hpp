#ifndef data_visualizer_h__
#define data_visualizer_h__

#include <windows.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "app.hpp"
#include "globals.hpp"


namespace aks
{
    namespace visualization
    {
        class DataVisualizer : public Application
        {
        public:
            DataVisualizer( void ) 
                : theta(90.0f), 
                  phi(270.0f), 
                  camDistance(25.0f), 
                  last_x(0), 
                  last_y(0), 
                  resolution(1),
                  isInstructions(true),
                  isBackroundWhite(true),
                  hasBGColorChanged(false)

            {
                camEye[0] = 6.0f;
                camEye[1] = 6.0f;
                camEye[2] = 6.0f;

                camCenter[0] = 0.0f;
                camCenter[1] = 0.0f;
                camCenter[2] = 0.0f;
            }
        //////////////////////////////////////////////////////////////////////////
            virtual void display()
            {
                DrawCamera();
                SetBackgroundColor();
                DrawData();
                DrawGrid();
                DrawInstructions();
            }

            void DrawCamera()
            {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glLoadIdentity();
                gluLookAt(camDistance, 0, 0,  0, 0, 0,  0, 1.0f, 0);
                glRotatef(-phi, 0, 0, 1);
                glRotatef(theta, 0, 1, 0);
                glTranslatef(-camEye[0], -camEye[1], -camEye[2]);
            }
            void SetBackgroundColor()
            {
                if (hasBGColorChanged)
                {
	                if(!isBackroundWhite)
	                    glClearColor(0.0, 0.0, 0.0, 1.0);
	                else
	                    glClearColor(1.0, 1.0, 1.0, 1.0);
                }
            }
            void DrawInstructions()
            {
                if(isInstructions)
                {
	                if(isBackroundWhite)
	                    glColor3f(0.0, 0.0, 0.0);
	                else
	                    glColor3f(1.0, 1.0, 1.0);
	                renderText(width-100, height-10, "Instructions :");
                }
            }

            void DrawData( )
            {
                std::vector<float> mins = Globals::GetInstance().mMins;
                std::vector<float> maxs = Globals::GetInstance().mMaxs;

                unsigned int rangeSetter(2);

                //using namespace aks::visualization;
                for (unsigned int i(0); i < Globals::GetInstance().dataArray.size()-1; i+=resolution)
                {
                    glColor3f( Globals::GetInstance().dataArray[i][rangeSetter]*2/maxs[rangeSetter], 
                        (Globals::GetInstance().dataArray[i][rangeSetter]/maxs[rangeSetter])-1.0f, 
                        1.0 - ((Globals::GetInstance().dataArray[i][rangeSetter]-mins[rangeSetter])/maxs[rangeSetter]-mins[rangeSetter]) );
                    glPushMatrix();
                    glBegin(GL_LINES);
                    glVertex3f( Globals::GetInstance().dataArray[i][0],
                        Globals::GetInstance().dataArray[i][1],
                        Globals::GetInstance().dataArray[i][2] );
                    glVertex3f( Globals::GetInstance().dataArray[i+1][0],
                        Globals::GetInstance().dataArray[i+1][1],
                        Globals::GetInstance().dataArray[i+1][2]);
                    glEnd();

                    glPopMatrix();
                }
            }

            void DrawGrid(  )
            {
                std::vector<float> mins = Globals::GetInstance().mMins;
                std::vector<float> maxs = Globals::GetInstance().mMaxs;

                if (isBackroundWhite)
                    glColor3f(0.5, 0.5, 0.5);
                else
                    glColor3f(0.5, 0.5, 0.5);

                for (float i(mins[0]) ; i < maxs[0]; i += 1.0)
                {
                    glPushMatrix();
                        glBegin(GL_LINES);
                            glVertex3f( i, mins[1], 0.0f );
                            glVertex3f( i, maxs[1], 0.0f );
                        glEnd();
                    glPopMatrix();
                }

                if (isBackroundWhite)
                    glColor3f(0.8, 0.8, 0.8);
                else
                    glColor3f(0.2, 0.2, 0.2);

                for (float i(mins[1]) ; i < maxs[1]; i += 1.0)
                {
                    glPushMatrix();
                        glBegin(GL_LINES);
                            glVertex3f( mins[0], i, 0.0f );
                            glVertex3f( maxs[0], i, 0.0f );
                        glEnd();
                    glPopMatrix();
                }
            }
            //////////////////////////////////////////////////////////////////////////
            const char* getTitle()
            {
                return "Data Visualizer - Aks...";
            }
        //////////////////////////////////////////////////////////////////////////
            void mouse(int button, int state, int x, int y)
            {
                last_x = x;
                last_y = y;
            }
        //////////////////////////////////////////////////////////////////////////
            void mouseDrag(int x, int y)
            {
                theta += (x - last_x)*0.25f;
                phi += (y - last_y)*0.25f;

                //if (phi < -0.0f) phi = -0.0f;
                //else if (phi > 80.0f) phi = 80.0f;

                last_x = x;
                last_y = y;
            }
        //////////////////////////////////////////////////////////////////////////
        protected:
            float theta;
            float phi;
            float camDistance;
            int last_x, last_y;
            unsigned int resolution;
            bool isInstructions;
            bool isBackroundWhite;
            float camEye[3];
            float camCenter[3];
            float hasBGColorChanged;
        private:
        };

        Application* getApplication();
    }
}












#endif // data_visualizer_h__
