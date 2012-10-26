#include <math.h>

float[16] Transform::getTranslateMatrix(float x, float y, float z){
	return {
		1 0 0 x
		0 1 0 y
		0 0 1 z
		0 0 0 1
	};
}

float[16] Transform::getXRotationMatrix(float angle){
	return {
		1 0          0           0   		
		0 cos(angle) -sin(angle) 0
		0 sin(angle) cos(angle)  0
		0 0          0           1
	};
}

float[16] Transform::getYRotationMatrix(float angle){
	return {
		cos(angle) -sin(angle) 0 0
		sin(angle) cos(angle)  0 0
		0 		   0           1 0
		0          0           0 1
	};
}

float[16] Transform::getZRotationMatrix(float angle){
	return {
		cos(angle)  0 sin(angle) 0
		0 		    1 0          0
		-sin(angle) 0 cos(angle) 0
		0           0 0          1
	};
}

float[16] Transform::getScaleMatrix(float scaleX, float scaleY, float scaleZ){
	return {
		scalex 0      0      0
		0      scaleY 0      0
		0      0      scaleZ 0
		0      0      0      1
	};
}


Transform::Transform() {
	this->transform = Transform::identity;
}

void Transform::Rotate(float x, float y, float z){
	this->transform *= Transform::getTranslateMatrix(x, y, z);
	this->transform *= Transform::getTranslateMatrix(x, y, z);
	this->transform *= Transform::getTranslateMatrix(x, y, z);
}
void Transform::Translate(float x, float y, float z){
	this->transform *= Transform::getTranslateMatrix(x, y, z);
}

void Transform::Scale(float x, float y, float z){
	this->transform *= Transform::getScaleMatrix(x, y, z);
}

Transform Transform::&operator *=(const Transform &a){

}

