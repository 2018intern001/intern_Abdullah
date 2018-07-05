#pragma once
#include "StatusEffect.h"
class Poison :
	public StatusEffect
{
public:
	Poison();
	~Poison();

	virtual string Name() override;
	virtual bool StatusEffectAction(Unit* unit) override;
};

