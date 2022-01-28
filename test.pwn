#include <a_samp>
#include "confirm-box.inc"

public OnPlayerSpawn(playerid)
{
	ShowPlayerConfirmBox(playerid, DeagleBox, "Are you sure you want to get a Desert Eagle?", "Desert Eagle");
	return 1;
}

ConfirmBox:DeagleBox(playerid, response, selectable, controllable, Float:percent)
{
	if(response == CONFIRM_BOX_RESPONSE_NULL)
	{
		return SendClientMessage(playerid, 0xFF0000FF, "You just have to confirm, what's so hard?");
	}
	if(response == CONFIRM_BOX_RESPONSE_YES)
	{
		if(percent <= 25.00)
		{
			return SendClientMessage(playerid, 0xFF0000FF, "You confirmed too late, i'm sorry.");
		}
		SendClientMessage(playerid, -1, "You got a Desert Eagle.");
		GivePlayerWeapon(playerid, WEAPON_DEAGLE, 100);
	}
	return 1;
}

main() {

}
