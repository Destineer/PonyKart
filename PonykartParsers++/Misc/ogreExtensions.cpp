#include <LinearMath/btVector3.h>
#include <LinearMath/btQuaternion.h>
#include <OgreSceneManager.h>
#include "Core/Options.h"
#include "Core/OptionsEnums.h"
#include "Levels/Level.h"
#include "Muffin/MuffinDefinition.h"
#include "Misc/ogreExtensions.h"

using namespace Ponykart::Core;
using namespace PonykartParsers;
using namespace Ogre;

namespace Extensions
{
	Vector3 toOgreVector3(const btVector3& vec)
	{
		return Vector3(vec.getX(), vec.getY(), vec.getZ());
	}

	Quaternion toOgreQuaternion(const btQuaternion& quat)
	{
		return Quaternion(quat.getW(), quat.getX(), quat.getY(), quat.getZ());
	}

	ColourValue toColourValue(const Vector3& vec)
	{
		return ColourValue(vec.x, vec.y, vec.z);
	}

	ColourValue toColourValue(const Quaternion& quat)
	{
		return ColourValue(quat.x, quat.y, quat.z, quat.w);
	}

	Vector3 degreeVectorToRadianVector(const Ogre::Vector3& vec)
	{
		static const Real twopi = 6.28318530717958647692f; ///< 2*PI
		return Vector3((float)vec.x*twopi/360.f, (float)vec.y*twopi/360.f, (float)vec.z*twopi/360.f);
	}

	Vector3 radianVectorToDegreeVector(const Ogre::Vector3& vec)
	{
		static const Real twopi = 6.28318530717958647692f; ///< 2*PI
		return Vector3((float)vec.x*360.f/twopi, (float)vec.y*360.f/twopi, (float)vec.z*360.f/twopi);
	}

	Quaternion degreeVectorToGlobalQuaternion(const Vector3& vec)
	{
		return fromGlobalEulerDegrees(vec);
	}

	/// Given three euler radian angles of global axes, we make a new quaternion from those angles and return it.
	/** Keep in mind that this doesn't modify the original quaternion.
		@param rotX Rotation (in radians) on the global X axis
		@param rotY Rotation (in radians) on the global Y axis
		@param rotZ Rotation (in radians) on the global Z axis
		@return A new quaternion */
	Ogre::Quaternion fromGlobalEuler(Ogre::Radian rotX, Ogre::Radian rotY, Ogre::Radian rotZ)
	{
		return globalEulerToQuat(rotX, rotY, rotZ);
	}

	/// Given three euler radian angles from global axes, we make a new quaternion from those angles and return it.
	/** Keep in mind that this doesn't modify the original quaternion.
		@param radianRotations A vector3 representing the rotations on global axes, so that rotations.x represents the rotation on the X axis, etc.\n
		This must be in radians! Use fromGlobalEulerDegrees if your vector is in degrees!
		@return A new quaternion */
	Ogre::Quaternion fromGlobalEuler(const Ogre::Vector3& radianRotations)
	{
		return globalEulerToQuat(Radian(radianRotations.x), Radian(radianRotations.y), Radian(radianRotations.z));
	}

	Quaternion fromGlobalEulerDegrees(const Ogre::Vector3& degreeRotations)
	{
		return fromGlobalEuler(degreeVectorToRadianVector(degreeRotations));
	}

	Quaternion globalEulerToQuat(Radian rotX, Radian rotY, Radian rotZ)
	{
		Quaternion q1, q2, q3; // global axes
		q1.FromAngleAxis(rotX, Vector3::UNIT_X);
		q2.FromAngleAxis(rotY, Vector3::UNIT_Y);
		q3.FromAngleAxis(rotZ, Vector3::UNIT_Z);

		return q3 * q2 * q1;
	}

	void setupShadows(SceneManager* sceneMgr, Ponykart::Levels::Level& level)
	{
		if (Options::shadowDetail != ShadowDetailOption::None) 
		{
			sceneMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);
			sceneMgr->setShadowFarDistance(Options::getFloat("ShadowDistance"));
			Vector3 colorVec = level.getDefinition()->getVectorProperty("ShadowColour", Vector3(0.8f, 0.8f, 0.8f));
			sceneMgr->setShadowColour(toColourValue(colorVec));
		}
		else
			sceneMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_NONE);

		/*
		/// CODE COPYPASTED FROM THE C# PONYKART - UNTESTED AS OF YET ///
		sceneMgr.ShadowTechnique = ShadowTechnique.SHADOWTYPE_TEXTURE_MODULATIVE_INTEGRATED;

		sceneMgr.SetShadowTextureCountPerLightType(Light.LightTypes.LT_DIRECTIONAL, 3);
		sceneMgr.ShadowTextureCount = 3;
		sceneMgr.SetShadowTextureConfig(0, 1024, 1024, PixelFormat.PF_FLOAT32_R);
		sceneMgr.SetShadowTextureConfig(1, 512, 512, PixelFormat.PF_FLOAT32_R);
		sceneMgr.SetShadowTextureConfig(2, 512, 512, PixelFormat.PF_FLOAT32_R);
		sceneMgr.ShadowTextureSelfShadow = true;
		sceneMgr.ShadowCasterRenderBackFaces = false;
		sceneMgr.ShadowFarDistance = 150;
		sceneMgr.SetShadowTextureCasterMaterial("PSSM/shadow_caster");
		sceneMgr.SetShadowTextureFadeStart(0.7f);

		PSSMShadowCameraSetup pssm = new PSSMShadowCameraSetup();
		pssm.SplitPadding = 1f;
		pssm.CalculateSplitPoints(3, 0.01f, sceneMgr.ShadowFarDistance - 10);
		pssm.SetOptimalAdjustFactor(0, 2);
		pssm.SetOptimalAdjustFactor(1, 1f);
		pssm.SetOptimalAdjustFactor(2, 0.5f);
		pssm.UseSimpleOptimalAdjust = false;

		sceneMgr.SetShadowCameraSetup(new ShadowCameraSetupPtr(pssm));*/
	}

} // Extensions
