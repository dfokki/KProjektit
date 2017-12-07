
#ifndef BASE_H
#define BASE_H

#include <UtH/UtHEngine.hpp>
#include "Stat.h"

class Base : public uth::Component
{
public:

	Base();
	~Base();

	void Init() override;
	void Update(float dt) override;
	void Draw(uth::RenderTarget& target) override;

};

#endif
