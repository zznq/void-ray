#ifndef UTILITY_TRANSFORM
#define UTILITY_TRANSFORM

typedef float[16] TransformMatrix;

class Transform {
private:
	static const float[16] identity = {
		1 0 0 0
		0 1 0 0
		0 0 1 0
		0 0 0 1
	};
	static float[16] getTranslateMatrix(float x, float y, float z);
	static float[16] getXRotationMatrix(float angle);
	static float[16] getYRotationMatrix(float angle);
	static float[16] getZRotationMatrix(float angle);
	static float[16] getScaleMatrix(float scaleX, float scaleY, float scaleZ);
protected:
	Transform();

	float transform[16];

	float[16] multiplayMatrix(TransformMatrix left, TransformMatrix right);
	void rotate(float x, float y, float z);
	void translate(float x, float y, float z);
	void scale(float x, float y, float z);

	float[16] toGLMatrix();

	float[16] &operator *=(const float[16] &a);
};

#endif
