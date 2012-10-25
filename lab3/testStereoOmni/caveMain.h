#ifndef PointManipulationAfx_H_
#define PointManipulationAfx_H_

#if defined(WIN32)
// identifier was truncated to '255' characters in the debug information.
# pragma warning( disable: 4786 )
# include <windows.h>
#endif // WIN32

#if defined(WIN32) || defined(linux)
#include <cave_ogl.h>
#elif defined(__APPLE__)
# include <GLUT/glut.h>
#endif

#include <HD/hd.h>
#include <HDU/hduVector.h>

extern int theSphereId;
extern bool objectsAreTouched;

#endif // PointManipulationAfx_H_
