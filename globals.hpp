#ifndef globals_h__
#define globals_h__

#include <aksUtilityHeaders/singleton.hpp>
#include <vector>
#include <boost/algorithm/minmax.hpp>

namespace aks
{
    namespace visualization
    {
        class Globals : public aks::memory::Singleton<Globals>
        {
        public:
            std::vector< std::vector< float > > dataArray; 
            std::vector<float> mMins;
            std::vector<float> mMaxs;
            Globals() : mDataArrayInitialized( false ) { }
            bool IsDataArrayInitialized() const { return mDataArrayInitialized; }
            void SetDataArrayInitialization( const bool b )
            { 
                if( b != mDataArrayInitialized )
                {
                    mDataArrayInitialized = b; 
                    if ( mDataArrayInitialized )
                    {                   
                        for (unsigned int i(0); i < dataArray[0].size();  ++i)
                        {
                            float minTemp = dataArray[0][i];
                            float maxTemp = dataArray[0][i];
                            for ( unsigned int j(0); j < dataArray.size(); ++j)
                            {
                                if( dataArray[j][i] < minTemp )
                                    minTemp = dataArray[j][i];
                                else if( dataArray[j][i] > maxTemp )
                                    maxTemp = dataArray[j][i];
                            }
                            mMins.push_back( minTemp );
                            mMaxs.push_back( maxTemp );
                        }
                    }
                }
            }
        protected:
        private:
            bool mDataArrayInitialized;

        };
    }
}

#endif // globals_h__