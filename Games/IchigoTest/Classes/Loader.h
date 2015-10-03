#ifndef __ICHIGO_LOADER_H__
#define __ICHIGO_LOADER_H__


namespace it 
{
    class Loader 
	{
    public:

		Loader				();
        virtual ~Loader		();

        void init			();
        void loadTextures	();
        void initDevice		();
    };    
}



#endif // __ICHIGO_FSMMANAGER_H__