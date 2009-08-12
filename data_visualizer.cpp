
#include "data_visualizer.hpp"

namespace aks
{
    namespace visualization
    {
        Application* getApplication()
        {
            return new DataVisualizer();
        }
    }
}