#ifndef VOID_RAY_CHILD_SPRITE
#define VOID_RAY_CHILD_SPRITE

#include <string>
#include "util/Vector3.hpp"
#include "BaseEntity.hpp"
#include "Sprite.hpp"

class ChildSprite : public Sprite {
protected:
	Vector3 _origPosition;
public:
	ChildSprite(std::string path, float offsetx, float offsety);
	ChildSprite(BaseEntity* parent, std::string path, float offsetx, float offsety);
	void Update(double time_elapsed);
};

#endif
