# confirm-box
This library provides a simple [confirmation box](https://i.imgur.com/uyMuSAk.png) selectable or using keys, made using textdraws (better than dialogs).  

# Installation
Simply download the include file and paste in your `pawno/includes` file (maybe in the future it will be possible with sampctl).  
Include in your code and begin using the library:
```pawn
#include <confirm-box>
```

# Functions
```pawn
ShowPlayerConfirmBox(playerid, callback[], description[], title[], confirm_time, bool:selectable, bool:controllable, bool:sound);
```
Displays to the player the confirmation box.
```pawn
HidePlayerConfirmBox(playerid);
```
Hides the player's confirmation box.

# Definitions
`CONFIRMATION_BOX_TIME`: default value in milliseconds in how long the box will disappear.  
`CONFIRM_BOX_UPDATE_RATE`: default update rate for the timer, how smaller is, how smooth is the bar effect (low values may impact your performance).<br>
`CONFIRMATION_BOX_ERROR`: default error code returned by confirm-box functions in case of fail.<br>

**Responses**:  
`CONFIRM_BOX_RESPONSE_NULL`: when the player doesn't confirm or cancel the confirmation box.<br>
`CONFIRM_BOX_RESPONSE_YES`: when the player confirm the box.<br>
`CONFIRM_BOX_RESPONSE_NO`: when the player cancel the box.<br>

# Callbacks
You will make the callback, every confirm box will call a callback made by you using the below syntax:
```pawn
ConfirmBox:MyCallback(playerid, response, selectable, controllable, percent)
{
    // the parameters are optional, depending on what you need.
    // here will be your code.
    return 1;
}
```

# Requirements
* Nothing, just be sure the sa-mp includes are included. Optionally, if you're using the y_hooks from YSI library, my library will detect it and it will also use too for a better way to hook callbacks.

# Notes
* Compatible with the latest version of **Pawn Community Compiler** (cur: 3.10.10).

# Example
There is an example of how to use it.

```pawn
CMD:deagle(playerid, params[])
{
	ShowPlayerConfirmBox(playerid, DeagleBox, "Are you sure you want to get a Desert Eagle? This will cost you $5.", "Desert Eagle");
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
```