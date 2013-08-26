#include "SceneObjectUnitPlane.h"
#include "randf.h"
#include <math.h>

const SceneObjectVTable sceneObjectUnitPlaneVTable = (SceneObjectVTable) {
	&sceneObjectUnitPlaneIntersectRay,
	&sceneObjectUnitPlaneEmitPhotons
};

SceneObjectUnitPlane makeSceneObjectUnitPlane (const Plane plane, const Material *material) {

	return (SceneObjectUnitPlane) {makeSceneObject(&sceneObjectUnitPlaneVTable), plane, material};
}

defineAllocator(SceneObjectUnitPlane)

Intersection sceneObjectUnitPlaneIntersectRay(const SceneObject *superobject, const Ray ray) {

	const SceneObjectUnitPlane *object = (SceneObjectUnitPlane *) superobject;
	
	Intersection intersection = pIntersect(object->plane, ray);

	if (intersection.hitType) {

		// Intersection outside the unit cube should be ignored.
		if (
			intersection.position.x < -1 || intersection.position.x > 1 ||
			intersection.position.y < -1 || intersection.position.y > 1 ||
			intersection.position.z < -1 || intersection.position.z > 1
		) {
			
			intersection.hitType = missed;
			
			// Return early.
			return intersection;
		}

		intersection.material = object->material;
	}

	return intersection;
}

bool sceneObjectUnitPlaneEmitPhotons(const SceneObject *superobject, const int numPhotons, PhotonContainer *photons) {

	// TODO: Implement this. Use code from SceneObjectSphere.

	return false;
}
