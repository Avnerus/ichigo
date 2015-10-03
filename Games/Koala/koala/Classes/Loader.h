#ifndef __KOALA_LOADER_H__
#define __KOALA_LOADER_H__


namespace koala
{
    class Loader 
	{
    public:

		Loader				();
        virtual ~Loader		();

        void init			();
        void loadTextures	();
        void initDevice		();
        void initScripting  ();
    };    
}



#endif // __ICHIGO_FSMMANAGER_H__