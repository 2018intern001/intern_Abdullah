#pragma once
#include "StatusEffect.h"
class Normal :
	public StatusEffect
{
public:
	Normal();
	~Normal();

	virtual string Name();
	virtual bool StatusEffectAction(Unit* unit);
};

