#ifndef HapticManager_H_
#define HapticManager_H_

class IFaceManager;

class IHapticManager
{
public:

    static IHapticManager *create();
    static void destroy(IHapticManager *&pInterface);

    virtual void setup(IFaceManager *pFaceManager) = 0;
    virtual void cleanup() = 0;

    virtual void UpdateHapticMapping(void) = 0;
	virtual void DisplayInfo(void)=0;
    virtual void drawCursor() = 0;
    virtual void feelPoints() = 0;


protected:

    IHapticManager() {}
    virtual ~IHapticManager() {}

};

#endif // HapticManager_H_