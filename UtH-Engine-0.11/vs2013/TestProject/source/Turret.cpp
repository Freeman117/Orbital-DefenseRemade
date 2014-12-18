#include "Turret.hpp"
Turret::Turret()
{
	critAmount = 1;
	armorPenetration = 1;
	slowAmount = 1;
	penetrate = false;
}
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
