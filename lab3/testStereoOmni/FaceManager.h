#ifndef FaceManager_H_
#define FaceManager_H_

/******************************************************************************
 IPointManager Interface
******************************************************************************/
class IFaceManager
{
public:
    static IFaceManager *create(void);
    static void destroy(IFaceManager *&fInterface);
    
    virtual void setup() = 0;
    virtual void cleanup() = 0;
	virtual void drawFaces()=0;
    virtual void drawFace(int i)=0;
	virtual int getNumFaces()=0;

protected:
    IFaceManager() {}
    virtual ~IFaceManager() {}

}; 

#endif // FaceManager_H_
