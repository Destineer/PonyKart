#include <vector>
#include <OgreConfigFile.h>
#include "Kernel/LKernel.h"
#include "Misc/direntSearch.h"
#include "Physics/Materials/PhysicsMaterial.h"
#include "Physics/Materials/PhysicsMaterialFactory.h"

using namespace std;
using namespace Ponykart::Physics;

PhysicsMaterialFactory::PhysicsMaterialFactory()
{
	defaultMat = new PhysicsMaterial();

	readMaterialsFromFiles();
}

void PhysicsMaterialFactory::readMaterialsFromFiles()
{
	// since we can run this whenever (like when we're tweaking files), we want to clear this first
	materials.clear();

	// get all of the filenames of the files in media/physicsmaterials
	vector<string> files = direntSearch("media/physicsmaterials/", ".physmat");

	for (string filename : files)
	{
		// rev up those files
		Ogre::ConfigFile cfile;
		cfile.load(filename, "=", true);

		auto sectionIterator = cfile.getSectionIterator();
		while (sectionIterator.hasMoreElements())
		{
			string matname = sectionIterator.peekNextKey();
			ostringstream ssF,ssB,ssAD,ssLD;
			ssF << PhysicsMaterial::DEFAULT_FRICTION;
			ssB << PhysicsMaterial::DEFAULT_BOUNCINESS;
			ssAD << PhysicsMaterial::DEFAULT_ANGULAR_DAMPING;
			ssLD << PhysicsMaterial::DEFAULT_LINEAR_DAMPING;

			PhysicsMaterial *mat = new PhysicsMaterial (
				atof(cfile.getSetting("Friction", matname, ssF.str()).c_str()),
				atof(cfile.getSetting("Bounciness", matname, ssB.str()).c_str()),
				atof(cfile.getSetting("AngularDamping", matname, ssAD.str()).c_str()),
				atof(cfile.getSetting("LinearDamping", matname, ssLD.str()).c_str())
			);

			materials[matname] = mat;
		}
	}
}

/// Gets a material from the map, or a default value if not found
PhysicsMaterial* PhysicsMaterialFactory::getMaterial(const string& materialName)
{
	auto matIt = materials.find(materialName);
	if (matIt != materials.end())
		return matIt->second;
	else if (materialName == "Default")
		return defaultMat;
	else
	{
		LKernel::log("[PhysicsMaterialFactory] Material \"" + materialName + "\" did not exist! Applying default...");
		return defaultMat;
	}
}

/// Only applies friction and bounciness. Use a RigidBodyConstructionInfo if you want to set the damping.
void PhysicsMaterialFactory::applyMaterial(btRigidBody* body, const string& material)
{
	PhysicsMaterial* mat = getMaterial(material);

	body->setFriction(mat->friction);
	body->setRestitution(mat->bounciness);
}

/// Applies friction, bounciness, angular damping, and linear damping
void PhysicsMaterialFactory::applyMaterial(btRigidBody::btRigidBodyConstructionInfo* info, const string& material)
{
	PhysicsMaterial* mat = getMaterial(material);

	info->m_friction = mat->friction;
	info->m_restitution = mat->bounciness;
	info->m_angularDamping = mat->angularDamping;
	info->m_linearDamping = mat->linearDamping;
}
