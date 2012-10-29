#ifndef UTILITY_TRANSFORM
#define UTILITY_TRANSFORM

#include <vector>

typedef float* TransformMatrix;

class Transform {
protected:
	static float identity[];

	static std::vector<float> getTranslateMatrix(const float x, const float y, const float z);
	static std::vector<float> getXRotationMatrix(const float angle);
	static std::vector<float> getYRotationMatrix(const float angle);
	static std::vector<float> getZRotationMatrix(const float angle);
	static std::vector<float> getScaleMatrix(const float scaleX, const float scaleY, const float scaleZ);

public:
	Transform();

	std::vector<float> transform;

	void translate(float x, float y, float z);
	void rotate(float x, float y, float z);
	void scale(float x, float y, float z);

/*
	float* toGLMatrix();

	std::vector<float> &operator *=(const std::vector<float> &a);
*/
};

#endif
