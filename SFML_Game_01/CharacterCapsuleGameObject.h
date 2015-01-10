#pragma once

#include "CapsuleGameObject.h"
#include "AnimatedSpriteCollection.h"

class CharacterCapsuleGameObject : public CapsuleGameObject
{
public:
	CharacterCapsuleGameObject(int width, int height, std::vector<Component*> components);
	CharacterCapsuleGameObject(int x, int y, int width, int height, std::vector<Component*> components);

	virtual void update(World* world) override;
	virtual void render(Window* window) override;

	inline AnimatedSpriteCollection* getAnimatedSpriteCollection() { return &m_animationCollection; }
	inline void setActiveAnimation(int index) { m_animationCollection.setActiveAnimation(index); }

	bool keyLeft, keyRight;
private:
	AnimatedSpriteCollection m_animationCollection;
};

