#pragma once
#include "StatusEffect.h"
class Paralysis:	
	public StatusEffect
{
public:
	Paralysis();
	~Paralysis();

	int probabilityOfFailure;

	virtual string Name() override;
	virtual bool StatusEffectAction(Unit* unit) override;
};

