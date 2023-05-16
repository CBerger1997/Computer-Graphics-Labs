#include "Tree.h"

void Tree::SetTransformations (glm::vec3 pos, glm::vec3 rot, float deg, glm::vec3 sc) {
	position = pos;
	rotation = rot;
	scale = sc;
	rotationDegrees = deg;
}

void Tree::ApplyTransformations () {
	model = glm::translate (model, position);
	model = glm::rotate (model, (float)glm::radians (rotationDegrees), rotation);
	model = glm::scale (model, scale);
}

void Tree::Move (glm::vec3 posVals) {
	position += posVals;

	model = glm::translate (model, position);
}

void Tree::Rotate (glm::vec3 rotVals, float degrees) {
	rotation = rotVals;
	rotationDegrees = degrees;

	model = glm::rotate (model, (float)glm::radians (rotationDegrees), rotation);
}

void Tree::Scale (glm::vec3 scVals) {
	scale += scVals;

	model = glm::scale (model, scale);
}