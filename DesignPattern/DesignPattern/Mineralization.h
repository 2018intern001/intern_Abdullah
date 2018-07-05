#pragma once
#include "StatusEffect.h"
class Mineralization :
	public StatusEffect
{
public:
	Mineralization();
	~Mineralization();

	virtual string Name() override;
	virtual bool StatusEffectAction(Unit* unit) override;
};

