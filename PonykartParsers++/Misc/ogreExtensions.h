#ifndef OGREEXTENSIONS_H_INCLUDED
#define OGREEXTENSIONS_H_INCLUDED

// MSVC needs to be told what to export in the DLL
#ifndef DLLEXPORT
#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif
#endif

#include <OgreColourValue.h>
#include <OgreQuaternion.h>
#include <OgreVector3.h>

class btVector3;
class btQuaternion;

namespace Ponykart{ namespace Levels{ class Level; } }

namespace Extensions
{
	DLLEXPORT Ogre::Vector3 toOgreVector3(const btVector3& vec);
	DLLEXPORT Ogre::Quaternion toOgreQuaternion(const btQuaternion& quat);
	DLLEXPORT Ogre::ColourValue toColourValue(const Ogre::Vector3& vec);
	DLLEXPORT Ogre::ColourValue toColourValue(const Ogre::Quaternion& quat);
	DLLEXPORT Ogre::Vector3 degreeVectorToRadianVector(const Ogre::Vector3& vec); ///< If you have a vector to be used for rotation but it's in degrees and you want radians, use this!
	DLLEXPORT Ogre::Vector3 radianVectorToDegreeVector(const Ogre::Vector3& vec); /// If you have a vector to be used for rotation but it's in radians and you want degrees, use this!
	DLLEXPORT Ogre::Quaternion degreeVectorToGlobalQuaternion(const Ogre::Vector3& vec); ///< Creates a quaternion from a global degree vector.
	DLLEXPORT Ogre::Quaternion fromGlobalEuler(Ogre::Radian rotX, Ogre::Radian rotY, Ogre::Radian rotZ);
	DLLEXPORT Ogre::Quaternion fromGlobalEuler(const Ogre::Vector3& radianRotations);
	DLLEXPORT Ogre::Quaternion fromGlobalEulerDegrees(const Ogre::Vector3& degreeRotations); ///< Given three euler degree angles from global axes, we make a new quaternion from those angles and return it.
	DLLEXPORT Ogre::Quaternion globalEulerToQuat(Ogre::Radian rotX, Ogre::Radian rotY, Ogre::Radian rotZ);

	DLLEXPORT void setupShadows(Ogre::SceneManager* sceneMgr, Ponykart::Levels::Level& level);
} // Extensions

#endif // OGREEXTENSIONS_H_INCLUDED
