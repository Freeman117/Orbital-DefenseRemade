#include "Turret.hpp"
Turret::Turret(uth::Texture* projectileTexture_)
{
	critAmount = 1;
	armorPenetration = 1;
	slowAmount = 1;
	penetrate = false;
	projectileTexture = projectileTexture_;
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
