#ifndef VOID_RAY_CHILD_SPRITE
#define VOID_RAY_CHILD_SPRITE

#include <string>
#include "BaseEntity.hpp"
#include "Sprite.hpp"

class ChildSprite : public Sprite {
public:
	ChildSprite(BaseEntity* parent, std::string path, float offsetx);
};

#endif
