# samp-confirm-box

[![sampctl](https://img.shields.io/badge/sampctl-samp--confirm--box-2f2f2f.svg?style=for-the-badge)](https://github.com/GroWy/samp-confirm-box)

This library provides a simple [confirmation box](https://i.imgur.com/uyMuSAk.png) selectable or using keys, made using textdraws (better than dialogs).

## Installation

Simply install to your project:

```bash
sampctl package install denisbranisteanu/samp-confirm-box
```

Include in your code and begin using the library:

```pawn
#include <confirm-box>
```

## Functions
```pawn
ShowPlayerConfirmBox(playerid, callback[], description[], title[], confirm_time, bool:selectable, bool:controllable, bool:sound);

/*
    - callback: The function name to be called.
    - title: Confirmation Box's title.
    - description: Confirmation Box's description.
    - confirm_time: Displaying time in ms (eg: 1000ms who means 1 second).
    - selectable: Specify if the player needs to select the buttons instead of using keys Y/N.
    - controllable: Specify if the player will be able to move his character.
    - sound: Specify if the box will make sounds.
*/
```
Displays to the player the confirmation box.
```pawn
HidePlayerConfirmBox(playerid);
```
Hides the player's confirmation box.

## Definitions
`CONFIRMATION_BOX_TIME`: default value in milliseconds in how long the box will disappear.<br>
`CONFIRM_BOX_UPDATE_RATE`: default update rate for the timer, how smaller is, how smooth is the bar effect (low values may impact your performance).<br>
`CONFIRMATION_BOX_ERROR`: default error code returned by confirm-box functions in case of fail.<br>

**Responses**:<br>
`CONFIRM_BOX_RESPONSE_NULL`: when the confirmation time expires.<br>
`CONFIRM_BOX_RESPONSE_YES`: when the player confirm the box.<br>
`CONFIRM_BOX_RESPONSE_NO`: when the player cancel the box.<br>

## Callbacks
You will make the callback, every confirm box will call a callback made by you using the below syntax:
```pawn
ConfirmBox:MyCallback(playerid, response, selectable, controllable, Float:percent)
{
    /*
        playerid - Of course the id of the player.
        response - Response from the player. Check definitions for responses.
        selectable - If the confirmation box was selectable. 0 - No, 1 - Yes.
        controllable - If the player was able to move his character. 0 - No, 1 - Yes.
        percent - The percentage left before the response.
    */

    // the parameters are optional, depending on what you need, in what order
    // if you need just playerid and response, you can skip selectable, controllable and percent
    // but if you need percent, you can't skip all params before it.

    // here will be your code.
    return 1;
}
```

## Example
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

## Testing

To test, simply run the package:

```bash
sampctl package run
```
