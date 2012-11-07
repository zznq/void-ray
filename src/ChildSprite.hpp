#ifndef AI_CHILDSPRITE
#define AI_CHILDSPRITE

#include <string>
#include "BaseEntity.hpp"
#include "Sprite.hpp"

class ChildSprite : public Sprite {
public:
	ChildSprite(BaseEntity* parent, std::string path, float offsetx);
};

#endif
