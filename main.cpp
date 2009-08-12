#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include <stdlib.h>
#include <math.h>
#include <aksUtilityHeaders/containerPrint.hpp>

#include <windows.h>
#include <HiResTime/hiResTime.hpp>

#include <GL/glut.h>

#include "app.hpp"
#include "data_visualizer.hpp"
#include "globals.hpp"

using namespace aks::visualization;

using namespace std;

template< typename T >
bool ReadTable(const char* FileName, std::vector< std::vector< T > >& v, const char& c) 
{
    string s, line, segments;
    vector<T> temp;
    cout << "Opening file : " << FileName << endl;
    aks::time::HighResStopWatch watch;
    watch.startTimer();
        ifstream in;
        in.open(FileName, ios::in);
    watch.stopTimer();
    cout << "File opened : " << FileName << " in " << watch.getElapsedTime() << " seconds\n" << endl;

    cout << "Loading file : " << FileName << endl;
    watch.startTimer();
        while(getline(in,line)) 
        { 
            stringstream ss2;
            ss2 << line;
            while (getline(ss2,segments,c)) 
            {
                temp.push_back( (T)atof(segments.c_str()) );
            }
            v.push_back(temp);
            temp.clear();
        }
    watch.stopTimer();
    cout << "File loaded : " << FileName << " in " << watch.getElapsedTime() << " seconds\n" << endl;

    cout << "Closing file : " << FileName << endl;
    watch.startTimer();
        in.close();
    watch.stopTimer();
    cout << "File closed : " << FileName << " in " << watch.getElapsedTime() << " seconds\n"  << endl;

    if( v.size() != 0 )
    {
        Globals::GetInstance().SetDataArrayInitialization( true );
        cout << "Acquired data array with : " << v.size() << " rows and " << v[0].size() << " columns\n";
        return true;
    }
    else
        cout << "No data acquired! Quitting\n";
    return false;
    
}

extern Application* getApplication();

// Store the global application object.
Application* app;

void createWindow(const char* title)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640,640);
    glutInitWindowPosition(0,0);
    glutCreateWindow(title);
}

void update() { app->update(); }

void display()
{
    app->display();

    // Update the displayed content.
    glFlush();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) { app->mouse(button, state, x, y); }

void reshape(int width, int height) { app->resize(width, height); }

void keyboard(unsigned char key, int x, int y) { app->key(key); }

void motion(int x, int y) { app->mouseDrag(x, y); }

int main(int argc, char *argv[])
{
    const char* FileName;
    if(argc > 1)
    {
         FileName = argv[1];
         std::cout << "Received file name as : " << FileName << std::endl;
         char ch;
         if (argc > 2)
         {
             std::cout << "Received delimiter as : " << *argv[2] << std::endl;
             switch (*argv[2])
             {
                 case 's' : ch = ' '; break;
                 case 't' : ch = '\t'; break;
                 case 'c' : ch = ','; break;
                 default  : ch = ' '; break;
             }
         }
         else
             ch = ' ';

         std::cout << "\n";

        if( ReadTable(FileName, aks::visualization::Globals::GetInstance().dataArray, ch) )
        {
	        glutInit(&argc, argv);
	
	        app = aks::visualization::getApplication();
	        createWindow(app->getTitle());
	
	        glutReshapeFunc(reshape);
	        glutKeyboardFunc(keyboard);
	        glutDisplayFunc(display);
	        glutIdleFunc(update);
	        glutMouseFunc(mouse);
	        glutMotionFunc(motion);
	
	        app->initGraphics();
	        glutMainLoop();
	
	        app->deinit();
	        delete app;
        }
    }

    return 0;
}


