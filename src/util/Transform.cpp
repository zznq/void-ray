#include <math.h>

#include "Transform.hpp"

float Transform::identity[] = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};


std::vector<float> Transform::getTranslateMatrix(const float x, const float y, const float z) {
	float translate[16] = {
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1
		};

	return std::vector<float>(translate, translate + 16);
}

std::vector<float> Transform::getXRotationMatrix(const float angle){
	float rotate[16] = {
		1, 0,          0,           0,   		
		0, cos(angle), -sin(angle), 0,
		0, sin(angle), cos(angle),  0,
		0, 0,          0,           1
	};

	return std::vector<float>(rotate, rotate + 16);
}

std::vector<float> Transform::getYRotationMatrix(const float angle){
	float rotate[16] = {
		cos(angle), -sin(angle), 0, 0,
		sin(angle), cos(angle),  0, 0,
		0, 		    0,           1, 0,
		0,          0,           0, 1
	};

	return std::vector<float>(rotate, rotate + 16);
}

std::vector<float> Transform::getZRotationMatrix(const float angle){
	float rotate[16] = {
		cos(angle),  0, sin(angle), 0,
		0, 		     1, 0,          0,
		-sin(angle), 0, cos(angle), 0,
		0,           0, 0,          1
	};

	return std::vector<float>(rotate, rotate + 16);
}

std::vector<float> Transform::getScaleMatrix(const float scaleX, const float scaleY, const float scaleZ){
	float scale[16] = {
		scaleX, 0,      0,      0,
		0,      scaleY, 0,      0,
		0,      0,      scaleZ, 0,
		0,      0,      0,      1
	};

	return std::vector<float>(scale, scale + 16);
}


Transform::Transform() {
	this->transform = std::vector<float>(Transform::identity, Transform::identity + 16);
}

void Transform::translate(const float x, const float y, const float z){
	//this->transform *= Transform::getTranslateMatrix(x, y, z);
}

void Transform::rotate(const float x, const float y, const float z){
	//this->transform *= Transform::getTranslateMatrix(x, y, z);
	//this->transform *= Transform::getTranslateMatrix(x, y, z);
	//this->transform *= Transform::getTranslateMatrix(x, y, z);
}

void Transform::scale(const float x, const float y, const float z){
	//this->transform *= Transform::getScaleMatrix(x, y, z);
}

/*
std::vector<float> Transform::&operator *=(const std::vector<float> &a){
}
*/
