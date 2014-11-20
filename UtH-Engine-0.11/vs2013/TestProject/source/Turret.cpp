#include "Turret.hpp"

bool Turret::CanShoot()
{
	if (cooldown >= reloadSpeed)
	{
		cooldown = 0;
		return true;
	}
	else
		return false;
}
