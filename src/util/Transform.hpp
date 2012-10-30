#ifndef UTILITY_TRANSFORM
#define UTILITY_TRANSFORM

#include <vector>

class Transform {
protected:
	static float identity[];

	static std::vector<float> getTranslateMatrix(const float x, const float y, const float z);
	static std::vector<float> getXRotationMatrix(const float angle);
	static std::vector<float> getYRotationMatrix(const float angle);
	static std::vector<float> getZRotationMatrix(const float angle);
	static std::vector<float> getScaleMatrix(const float scaleX, const float scaleY, const float scaleZ);

	static bool EpsilonEqual(const float left, const float right, const float epsilon);
public:
	Transform();

	std::vector<float> viewMatrix;

	void translate(float x, float y, float z);
	void rotate(float x, float y, float z);
	void scale(float x, float y, float z);

	void operator *=(const std::vector<float, std::allocator<float> > &a);

	void reset();
	void print();
	void print(std::vector<float> const mat);
};

#endif
