#ifndef TREE_H
#define TREE_H

#include "GameObject.h"

class Tree : public GameObject {
public:
	void SetTransformations (glm::vec3, glm::vec3, float, glm::vec3);
	void ApplyTransformations ();
	void Rotate (glm::vec3, float);
	void Move (glm::vec3);
	void Scale (glm::vec3);
private:
	using GameObject::GameObject;
};

#endif // !TREE_H
