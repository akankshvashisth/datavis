#ifndef app_h__
#define app_h__

#include <cstdlib>

namespace aks
{
    namespace visualization
    {
        class Application
        {
        protected:
            int height;
            int width;
        public:
            virtual const char* getTitle();
            virtual void initGraphics();
            virtual void setView();
            virtual void deinit();
            virtual void display();
            virtual void update();
            virtual void key(unsigned char key);
            virtual void resize(int width, int height);
            virtual void mouse(int button, int state, int x, int y);
            virtual void mouseDrag(int x, int y);
            void renderText(float x, float y, const char *text, void* font=NULL);
        };
    }
}



#endif // app_h__
