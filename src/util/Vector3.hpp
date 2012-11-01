#ifndef UTILITY_VECTOR3
#define UTILITY_VECTOR3
/*
 *  Vector3.h
 *  grabber
 *
 *  Created by jbuszkiewic on 4/10/11.
 *
 */
#include <math.h>

class Vector3 {
	public:
	float x,y,z;
	
	Vector3() { zero(); }
	
	Vector3(const Vector3 &a) : x(a.x), y(a.y), z(a.z) {}
	
	Vector3(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {}
	
	Vector3 &operator =(const Vector3 &a) {
		x = a.x, y = a.y, z = a.z;
		return *this;
	}
	
	void truncate(double max);

	//Standard object maintence
	bool operator ==(const Vector3 &a) const {
		return x==a.x && y==a.y && z==a.z;
	}
	
	bool operator !=(const Vector3 &a) const {
		return x!=a.x && y!=a.y && z!=a.z;
	}
	
	//Vector operations
	
	//Set the vector to zero
	void zero() { x = y = z = 0.0f; }
	
	Vector3 operator -() const { return Vector3(-x, -y,-z); }
	
	Vector3 operator +(const Vector3 &a) const {
		return Vector3(x + a.x, y + a.y, z + a.z);
	}
	
	Vector3 operator -(const Vector3 &a) const {
		return Vector3(x - a.x, y - a.y, z - a.z);
	}
	
	Vector3 operator *(float a) const {
		return Vector3(x * a, y * a, z * a);
	}
	
	Vector3 operator /(float a) const {
        if(a == 0)
            return Vector3(0.0, 0.0, 0.0);
        
		float oneOverA = 1.0f / a;
		return Vector3(x * oneOverA, y * oneOverA, z * oneOverA);
	}
	
	Vector3 &operator +=(const Vector3 &a) {
		x += a.x; y += a.y; z += a.z;
		return *this;
	}
	
	Vector3 &operator -=(const Vector3 &a) {
		x -= a.x; y -= a.y; z -= a.z;
		return *this;
	}
	
	Vector3 &operator *=(const Vector3 &a) {
		x *= a.x; y *= a.y; z *= a.z;
		return *this;
	}

	Vector3 &operator *=(const float a) {
		x *= a; y *= a; z *= a;
		return *this;
	}
	
	Vector3 &operator /=(float a) {
		float oneOverA = 1.0f / a;
		x *= oneOverA; y *= oneOverA; z *= oneOverA;
		return *this;
	}
	
	void normalize()
	{
		float magSq = x*x + y*y + z*z;
		if(magSq > 0)
		{
			float oneOverMag = 1.0f / sqrt(magSq);
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;
		}
	}
	
    //Dot Product
	float operator *(const Vector3 &a) const {
		return x * a.x + y * a.y + z * a.z;
	}
};

inline float vectorMag(const Vector3 &a) {
	return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

inline float vectorMagSq(const Vector3 &a) {
	return (a.x*a.x + a.y*a.y + a.z*a.z);
}

inline Vector3 crossProduct(const Vector3 &a, const Vector3 &b) {
	return Vector3(
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x
	);
}

//Only use for 2d calculations, otherwise use crossProduct
inline Vector3 Perp(const Vector3 &a) {
	return Vector3(
		-a.y,
		a.x,
		0
	);
}

inline Vector3 operator *(float k, const Vector3 &v) {
	return Vector3(k*v.x, k*v.y, k*v.z);
}

inline float distance(const Vector3 &a, const Vector3 &b){
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dz = a.z - b.z;
	return sqrt(dx*dx + dy*dy + dz*dz);
}

extern const Vector3 kZeroVector;
#endif