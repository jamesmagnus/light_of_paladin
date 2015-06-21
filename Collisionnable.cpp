#include "Collisionnable.h"

#include <btBulletDynamicsCommon.h>

Collisionnable::Collisionnable(EShape shapeType)
{
	mpTransform = new btTransform();
	mpBody = nullptr;
	mpMotionState = nullptr;
	mMasse = 0.0;
	mInertie = btVector3(0.0, 0.0, 0.0);

	mType = shapeType;

	switch (shapeType)
	{
	case EShape::BOX:
		mpCollShape = new btBoxShape(btVector3(0.0, 0.0, 0.0));
		break;
	case EShape::SPHERE:
		mpCollShape = new btSphereShape(0.0);
	case EShape::CAPSULE:
		mpCollShape = new btCapsuleShape(0.0, 0.0);
		break;
	case EShape::CYLINDER:
		mpCollShape = new btCylinderShape(btVector3(0.0, 0.0, 0.0));
		break;
	case EShape::CONE:
		mpCollShape = new btConeShape(0.0, 0.0);
		break;
	case EShape::MULTI_SPHERES:
		mpCollShape = new btMultiSphereShape(nullptr, nullptr, 0);
		break;
	default:
		mpCollShape = new btBoxShape(btVector3(0.0, 0.0, 0.0));
		break;
	}

}


Collisionnable::~Collisionnable()
{
	delete mpTransform;
	mpTransform = nullptr;

	delete mpCollShape;
	mpCollShape = nullptr;

	delete mpMotionState;
	mpMotionState = nullptr;

	delete mpBody;
	mpBody = nullptr;
}

void Collisionnable::calcInertie()
{
	if (mMasse != 0.0)
	{
		mpCollShape->calculateLocalInertia(mMasse, mInertie);
	}
}

bool Collisionnable::createMotionState()
{
	if (mpMotionState == nullptr)
	{
		mpMotionState = new btDefaultMotionState(*mpTransform);
		return false;
	}

	return true;
}

bool Collisionnable::createBody()
{
	if (mpBody == nullptr)
	{
		btRigidBody::btRigidBodyConstructionInfo const c(mMasse, mpMotionState, mpCollShape, mInertie);

		mpBody = new btRigidBody(c);

		return false;
	}

	return true;
}
