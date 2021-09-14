//////////////////////////////////////////////////
//////    Definitions                      //////
////////////////////////////////////////////////

#if !defined _samp_included
	#error Include "a_samp" doesn't exist.
#endif

#if defined _INC_y_hooks
	#include <YSI_Coding\y_hooks>
#endif

#if defined confirm_box_include
	#endinput
#endif

#define confirm_box_include

#define CONFIRM_BOX_RESPONSE_NULL		-1
#define CONFIRM_BOX_RESPONSE_YES		0
#define CONFIRM_BOX_RESPONSE_NO 		1

#if !defined CONFIRMATION_BOX_TIME
	#define CONFIRMATION_BOX_TIME		10 * 1000
#endif

#if !defined CONFIRM_BOX_UPDATE_RATE
	#define CONFIRM_BOX_UPDATE_RATE 	80
#endif

#if !defined CONFIRMATION_BOX_ERROR
	#define CONFIRMATION_BOX_ERROR		404
#endif

#define ShowPlayerConfirmBox(%0,%1, \
	Internal_ShowPlayerConfirmBox(%0,#%1,

#define ConfirmBox:%0(%1,%2,%3,%4,%5) \
	forward CB_%0(%1,%2,%3,%4,%5); public CB_%0(%1,%2,%3,%4,%5)

//////////////////////////////////////////////////
//////    Forwards                         //////
////////////////////////////////////////////////

forward OnConfirmBoxUpdate(playerid);

//////////////////////////////////////////////////
//////    Enumerations                     //////
////////////////////////////////////////////////

enum confirmBoxEnum {
	cb_functionName[32],

	bool: cb_controllable,
	bool: cb_selectable,
	bool: cb_sound,

	PlayerText: cb_textdraw[3],
	Float: cb_percent,

	cb_timer,
	cb_ms
};

//////////////////////////////////////////////////
//////    Declarations                     //////
////////////////////////////////////////////////

static
	ConfirmBoxData[MAX_PLAYERS + 1][confirmBoxEnum],

	Text: ConfirmBoxTD[6 + 1];

//////////////////////////////////////////////////
//////    Functions                        //////
////////////////////////////////////////////////

stock Internal_ShowPlayerConfirmBox(playerid, const callback[], const description[], const title[], confirm_time = CONFIRMATION_BOX_TIME, bool: selectable = false, bool: controllable = true, bool: sound = false) {
	if(!IsPlayerConnected(playerid)) return CONFIRMATION_BOX_ERROR;

	format(ConfirmBoxData[playerid][cb_functionName], 32, "CB_%s", callback);

	ConfirmBoxData[playerid][cb_timer] = SetTimerEx("OnConfirmBoxUpdate", CONFIRM_BOX_UPDATE_RATE, 1, "d", playerid);

	ConfirmBoxData[playerid][cb_controllable] = controllable;
	ConfirmBoxData[playerid][cb_selectable] = selectable;
	ConfirmBoxData[playerid][cb_sound] = sound;

	ConfirmBoxData[playerid][cb_ms] = confirm_time;
	ConfirmBoxData[playerid][cb_percent] = 0.00;

	for(new i; i < 6; i++) {
		TextDrawShowForPlayer(playerid, ConfirmBoxTD[i]);
	}

	ConfirmBoxData[playerid][cb_textdraw][0] = CreatePlayerTextDraw(playerid, 318.000000, 187.000000, title);
	PlayerTextDrawFont(playerid, ConfirmBoxData[playerid][cb_textdraw][0], 2);
	PlayerTextDrawLetterSize(playerid, ConfirmBoxData[playerid][cb_textdraw][0], 0.216666, 1.350000);
	PlayerTextDrawTextSize(playerid, ConfirmBoxData[playerid][cb_textdraw][0], 400.000000, 167.000000);
	PlayerTextDrawSetOutline(playerid, ConfirmBoxData[playerid][cb_textdraw][0], 1);
	PlayerTextDrawSetShadow(playerid, ConfirmBoxData[playerid][cb_textdraw][0], 0);
	PlayerTextDrawAlignment(playerid, ConfirmBoxData[playerid][cb_textdraw][0], 2);
	PlayerTextDrawColor(playerid, ConfirmBoxData[playerid][cb_textdraw][0], -1);
	PlayerTextDrawBackgroundColor(playerid, ConfirmBoxData[playerid][cb_textdraw][0], 255);
	PlayerTextDrawBoxColor(playerid, ConfirmBoxData[playerid][cb_textdraw][0], 50);
	PlayerTextDrawUseBox(playerid, ConfirmBoxData[playerid][cb_textdraw][0], 0);
	PlayerTextDrawSetProportional(playerid, ConfirmBoxData[playerid][cb_textdraw][0], 1);
	PlayerTextDrawSetSelectable(playerid, ConfirmBoxData[playerid][cb_textdraw][0], 0);
	PlayerTextDrawShow(playerid, ConfirmBoxData[playerid][cb_textdraw][0]);

	ConfirmBoxData[playerid][cb_textdraw][1] = CreatePlayerTextDraw(playerid, 318.000000, 206.000000, description);
	PlayerTextDrawFont(playerid, ConfirmBoxData[playerid][cb_textdraw][1], 1);
	PlayerTextDrawLetterSize(playerid, ConfirmBoxData[playerid][cb_textdraw][1], 0.200000, 1.050000);
	PlayerTextDrawTextSize(playerid, ConfirmBoxData[playerid][cb_textdraw][1], 400.000000, 167.000000);
	PlayerTextDrawSetOutline(playerid, ConfirmBoxData[playerid][cb_textdraw][1], 1);
	PlayerTextDrawSetShadow(playerid, ConfirmBoxData[playerid][cb_textdraw][1], 0);
	PlayerTextDrawAlignment(playerid, ConfirmBoxData[playerid][cb_textdraw][1], 2);
	PlayerTextDrawColor(playerid, ConfirmBoxData[playerid][cb_textdraw][1], -1);
	PlayerTextDrawBackgroundColor(playerid, ConfirmBoxData[playerid][cb_textdraw][1], 255);
	PlayerTextDrawBoxColor(playerid, ConfirmBoxData[playerid][cb_textdraw][1], 50);
	PlayerTextDrawUseBox(playerid, ConfirmBoxData[playerid][cb_textdraw][1], 0);
	PlayerTextDrawSetProportional(playerid, ConfirmBoxData[playerid][cb_textdraw][1], 1);
	PlayerTextDrawSetSelectable(playerid, ConfirmBoxData[playerid][cb_textdraw][1], 0);
	PlayerTextDrawShow(playerid, ConfirmBoxData[playerid][cb_textdraw][1]);

	ConfirmBoxData[playerid][cb_textdraw][2] = CreatePlayerTextDraw(playerid, 234.000000, 268.000000, "_");
	PlayerTextDrawFont(playerid, ConfirmBoxData[playerid][cb_textdraw][2], 1);
	PlayerTextDrawLetterSize(playerid, ConfirmBoxData[playerid][cb_textdraw][2], 0.600000, 0.150004);
	PlayerTextDrawTextSize(playerid, ConfirmBoxData[playerid][cb_textdraw][2], 402.000000, 0.000000);
	PlayerTextDrawSetOutline(playerid, ConfirmBoxData[playerid][cb_textdraw][2], 1);
	PlayerTextDrawSetShadow(playerid, ConfirmBoxData[playerid][cb_textdraw][2], 0);
	PlayerTextDrawAlignment(playerid, ConfirmBoxData[playerid][cb_textdraw][2], 1);
	PlayerTextDrawColor(playerid, ConfirmBoxData[playerid][cb_textdraw][2], -1);
	PlayerTextDrawBackgroundColor(playerid, ConfirmBoxData[playerid][cb_textdraw][2], 255);
	PlayerTextDrawBoxColor(playerid, ConfirmBoxData[playerid][cb_textdraw][2], 759266815);
	PlayerTextDrawUseBox(playerid, ConfirmBoxData[playerid][cb_textdraw][2], 1);
	PlayerTextDrawSetProportional(playerid, ConfirmBoxData[playerid][cb_textdraw][2], 1);
	PlayerTextDrawSetSelectable(playerid, ConfirmBoxData[playerid][cb_textdraw][2], 0);
	PlayerTextDrawShow(playerid, ConfirmBoxData[playerid][cb_textdraw][2]);
	
	if(selectable) {
		SelectTextDraw(playerid, 0xfb8c00ff);
	}

	if(!controllable) {
		TogglePlayerControllable(playerid, false);
	}

	if(sound) {
		PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
	}
	return 1;
}

stock HidePlayerConfirmBox(playerid) {
	if(!IsPlayerConnected(playerid)) return CONFIRMATION_BOX_ERROR;

	if(ConfirmBoxData[playerid][cb_timer] != -1) {
		KillTimer(ConfirmBoxData[playerid][cb_timer]);
		ConfirmBoxData[playerid][cb_timer] = -1;

		for(new i; i < 6; i++) {
			if(i < 3) {
				PlayerTextDrawDestroy(playerid, ConfirmBoxData[playerid][cb_textdraw][i]);
				ConfirmBoxData[playerid][cb_textdraw][i] = PlayerText: 0xFFFF;
			}

			TextDrawHideForPlayer(playerid, ConfirmBoxTD[i]);
		}

		if(ConfirmBoxData[playerid][cb_selectable]) {
			CancelSelectTextDraw(playerid);
		}

		if(!ConfirmBoxData[playerid][cb_controllable]) {
			TogglePlayerControllable(playerid, true);
		}

		memcpy(ConfirmBoxData[playerid], ConfirmBoxData[MAX_PLAYERS], 0, sizeof ConfirmBoxData[] * 4, sizeof ConfirmBoxData[]);
	}
	return 1;
}

//////////////////////////////////////////////////
//////    Internal Callbacks               //////
////////////////////////////////////////////////

public OnConfirmBoxUpdate(playerid) {
	if(ConfirmBoxData[playerid][cb_timer] != -1) {
		ConfirmBoxData[playerid][cb_percent] += (100.00 / (float(ConfirmBoxData[playerid][cb_ms]) / float(CONFIRM_BOX_UPDATE_RATE)));

		PlayerTextDrawTextSize(playerid, ConfirmBoxData[playerid][cb_textdraw][2], 402.00 - ((170.70 / 100.00) * ConfirmBoxData[playerid][cb_percent]), 0.00);
		PlayerTextDrawShow(playerid, ConfirmBoxData[playerid][cb_textdraw][2]);

		if(ConfirmBoxData[playerid][cb_percent] >= 100.00) {
			if(ConfirmBoxData[playerid][cb_sound]) {
				PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
			}

			CallLocalFunction(ConfirmBoxData[playerid][cb_functionName], "ddddf", playerid, CONFIRM_BOX_RESPONSE_NULL, _:ConfirmBoxData[playerid][cb_selectable], _:ConfirmBoxData[playerid][cb_controllable], 0.00);
			HidePlayerConfirmBox(playerid);
		}
	}
	return 1;
}

//////////////////////////////////////////////////
//////    Callbacks                        //////
////////////////////////////////////////////////

#if defined _INC_y_hooks
	hook OnGameModeInit() {
#else
	public OnGameModeInit() {
#endif

	ConfirmBoxTD[0] = TextDrawCreate(318.000000, 182.000000, "_");
	TextDrawFont(ConfirmBoxTD[0], 1);
	TextDrawLetterSize(ConfirmBoxTD[0], 0.600000, 10.300003);
	TextDrawTextSize(ConfirmBoxTD[0], 298.500000, 175.000000);
	TextDrawSetOutline(ConfirmBoxTD[0], 1);
	TextDrawSetShadow(ConfirmBoxTD[0], 0);
	TextDrawAlignment(ConfirmBoxTD[0], 2);
	TextDrawColor(ConfirmBoxTD[0], -1);
	TextDrawBackgroundColor(ConfirmBoxTD[0], 255);
	TextDrawBoxColor(ConfirmBoxTD[0], 926365695);
	TextDrawUseBox(ConfirmBoxTD[0], 1);
	TextDrawSetProportional(ConfirmBoxTD[0], 1);
	TextDrawSetSelectable(ConfirmBoxTD[0], 0);

	ConfirmBoxTD[1] = TextDrawCreate(318.000000, 184.000000, "_");
	TextDrawFont(ConfirmBoxTD[1], 1);
	TextDrawLetterSize(ConfirmBoxTD[1], 0.600000, 9.800004);
	TextDrawTextSize(ConfirmBoxTD[1], 298.500000, 171.500000);
	TextDrawSetOutline(ConfirmBoxTD[1], 1);
	TextDrawSetShadow(ConfirmBoxTD[1], 0);
	TextDrawAlignment(ConfirmBoxTD[1], 2);
	TextDrawColor(ConfirmBoxTD[1], -1);
	TextDrawBackgroundColor(ConfirmBoxTD[1], 255);
	TextDrawBoxColor(ConfirmBoxTD[1], 421075455);
	TextDrawUseBox(ConfirmBoxTD[1], 1);
	TextDrawSetProportional(ConfirmBoxTD[1], 1);
	TextDrawSetSelectable(ConfirmBoxTD[1], 0);

	ConfirmBoxTD[2] = TextDrawCreate(318.000000, 186.000000, "_");
	TextDrawFont(ConfirmBoxTD[2], 1);
	TextDrawLetterSize(ConfirmBoxTD[2], 0.600000, 1.550005);
	TextDrawTextSize(ConfirmBoxTD[2], 298.500000, 168.500000);
	TextDrawSetOutline(ConfirmBoxTD[2], 1);
	TextDrawSetShadow(ConfirmBoxTD[2], 0);
	TextDrawAlignment(ConfirmBoxTD[2], 2);
	TextDrawColor(ConfirmBoxTD[2], -1);
	TextDrawBackgroundColor(ConfirmBoxTD[2], 255);
	TextDrawBoxColor(ConfirmBoxTD[2], 926365695);
	TextDrawUseBox(ConfirmBoxTD[2], 1);
	TextDrawSetProportional(ConfirmBoxTD[2], 1);
	TextDrawSetSelectable(ConfirmBoxTD[2], 0);

	ConfirmBoxTD[3] = TextDrawCreate(318.000000, 206.000000, "_");
	TextDrawFont(ConfirmBoxTD[3], 1);
	TextDrawLetterSize(ConfirmBoxTD[3], 0.600000, 6.250007);
	TextDrawTextSize(ConfirmBoxTD[3], 298.500000, 168.500000);
	TextDrawSetOutline(ConfirmBoxTD[3], 1);
	TextDrawSetShadow(ConfirmBoxTD[3], 0);
	TextDrawAlignment(ConfirmBoxTD[3], 2);
	TextDrawColor(ConfirmBoxTD[3], -1);
	TextDrawBackgroundColor(ConfirmBoxTD[3], 255);
	TextDrawBoxColor(ConfirmBoxTD[3], 926365695);
	TextDrawUseBox(ConfirmBoxTD[3], 1);
	TextDrawSetProportional(ConfirmBoxTD[3], 1);
	TextDrawSetSelectable(ConfirmBoxTD[3], 0);

	ConfirmBoxTD[4] = TextDrawCreate(282.000000, 249.000000, "Y");
	TextDrawFont(ConfirmBoxTD[4], 2);
	TextDrawLetterSize(ConfirmBoxTD[4], 0.191666, 1.200000);
	TextDrawTextSize(ConfirmBoxTD[4], 9.000000, 35.500000);
	TextDrawSetOutline(ConfirmBoxTD[4], 0);
	TextDrawSetShadow(ConfirmBoxTD[4], 0);
	TextDrawAlignment(ConfirmBoxTD[4], 2);
	TextDrawColor(ConfirmBoxTD[4], -1);
	TextDrawBackgroundColor(ConfirmBoxTD[4], 255);
	TextDrawBoxColor(ConfirmBoxTD[4], 9109704);
	TextDrawUseBox(ConfirmBoxTD[4], 1);
	TextDrawSetProportional(ConfirmBoxTD[4], 1);
	TextDrawSetSelectable(ConfirmBoxTD[4], 1);

	ConfirmBoxTD[5] = TextDrawCreate(353.000000, 249.000000, "N");
	TextDrawFont(ConfirmBoxTD[5], 2);
	TextDrawLetterSize(ConfirmBoxTD[5], 0.191666, 1.200000);
	TextDrawTextSize(ConfirmBoxTD[5], 9.000000, 35.500000);
	TextDrawSetOutline(ConfirmBoxTD[5], 0);
	TextDrawSetShadow(ConfirmBoxTD[5], 0);
	TextDrawAlignment(ConfirmBoxTD[5], 2);
	TextDrawColor(ConfirmBoxTD[5], -1);
	TextDrawBackgroundColor(ConfirmBoxTD[5], -1962934017);
	TextDrawBoxColor(ConfirmBoxTD[5], -1962934072);
	TextDrawUseBox(ConfirmBoxTD[5], 1);
	TextDrawSetProportional(ConfirmBoxTD[5], 1);
	TextDrawSetSelectable(ConfirmBoxTD[5], 1);

	ConfirmBoxData[MAX_PLAYERS][cb_functionName] = 0x00;

	ConfirmBoxData[MAX_PLAYERS][cb_textdraw][0] = 
	ConfirmBoxData[MAX_PLAYERS][cb_textdraw][1] = 
	ConfirmBoxData[MAX_PLAYERS][cb_textdraw][2] = PlayerText: 0xFFFF;

	ConfirmBoxData[MAX_PLAYERS][cb_controllable] = true;
	ConfirmBoxData[MAX_PLAYERS][cb_selectable] = 
	ConfirmBoxData[MAX_PLAYERS][cb_sound] = false;

	ConfirmBoxData[MAX_PLAYERS][cb_percent] = 0.00;

	ConfirmBoxData[MAX_PLAYERS][cb_timer] = -1;
	ConfirmBoxData[MAX_PLAYERS][cb_ms] = 0;

	#if !defined _INC_y_hooks
		#if defined CB_OnGameModeInit
			return CB_OnGameModeInit();
		#else
			return 1;
		#endif
	#endif
}

#if !defined _INC_y_hooks
	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif

	#define OnGameModeInit CB_OnGameModeInit

	#if defined CB_OnGameModeInit
		forward CB_OnGameModeInit();
	#endif
#endif

#if defined _INC_y_hooks
	hook OnPlayerConnect(playerid) {
#else
	public OnPlayerConnect(playerid) {
#endif

	memcpy(ConfirmBoxData[playerid], ConfirmBoxData[MAX_PLAYERS], 0, sizeof ConfirmBoxData[] * 4, sizeof ConfirmBoxData[]);

	#if !defined _INC_y_hooks
		#if defined CB_OnPlayerConnect
			return CB_OnPlayerConnect(playerid);
		#else
			return 1;
		#endif
	#endif
}

#if !defined _INC_y_hooks
	#if defined _ALS_OnPlayerConnect
		#undef OnPlayerConnect
	#else
		#define _ALS_OnPlayerConnect
	#endif

	#define OnPlayerConnect CB_OnPlayerConnect

	#if defined CB_OnPlayerConnect
		forward CB_OnPlayerConnect(playerid);
	#endif
#endif

#if defined _INC_y_hooks
	hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
#else
	public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
#endif

	if(ConfirmBoxData[playerid][cb_timer] != -1 && !ConfirmBoxData[playerid][cb_selectable]) {
		if(newkeys & KEY_YES) {
			if(ConfirmBoxData[playerid][cb_sound]) {
				PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
			}

			CallLocalFunction(ConfirmBoxData[playerid][cb_functionName], "ddddf", playerid, CONFIRM_BOX_RESPONSE_YES, _:ConfirmBoxData[playerid][cb_selectable], _:ConfirmBoxData[playerid][cb_controllable], (100.00 - ConfirmBoxData[playerid][cb_percent]));
			HidePlayerConfirmBox(playerid);
		}

		if(newkeys & KEY_NO) {
			if(ConfirmBoxData[playerid][cb_sound]) {
				PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
			}

			CallLocalFunction(ConfirmBoxData[playerid][cb_functionName], "ddddf", playerid, CONFIRM_BOX_RESPONSE_NO, _:ConfirmBoxData[playerid][cb_selectable], _:ConfirmBoxData[playerid][cb_controllable], (100.00 - ConfirmBoxData[playerid][cb_percent]));
			HidePlayerConfirmBox(playerid);
		}
	}

	#if !defined _INC_y_hooks
		#if defined CB_OnPlayerKeyStateChange
			return CB_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
		#else
			return 1;
		#endif
	#endif
}

#if !defined _INC_y_hooks
	#if defined _ALS_OnPlayerKeyStateChange
		#undef OnPlayerKeyStateChange
	#else
		#define _ALS_OnPlayerKeyStateChange
	#endif

	#define OnPlayerKeyStateChange CB_OnPlayerKeyStateChange

	#if defined CB_OnPlayerKeyStateChange
		forward CB_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#endif
#endif

#if defined _INC_y_hooks
	hook OnPlayerClickTD(playerid, Text:clickedid) {
#else
	public OnPlayerClickTextDraw(playerid, Text:clickedid) {
#endif

	if(ConfirmBoxData[playerid][cb_timer] != -1 && ConfirmBoxData[playerid][cb_selectable]) {
		if(clickedid == Text:0xFFFF || clickedid == ConfirmBoxTD[5]) {
			if(ConfirmBoxData[playerid][cb_sound]) {
				PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
			}

			CallLocalFunction(ConfirmBoxData[playerid][cb_functionName], "ddddf", playerid, CONFIRM_BOX_RESPONSE_NO, _:ConfirmBoxData[playerid][cb_selectable], _:ConfirmBoxData[playerid][cb_controllable], (100.00 - ConfirmBoxData[playerid][cb_percent]));
			HidePlayerConfirmBox(playerid);
		}

		if(clickedid == ConfirmBoxTD[4]) {
			if(ConfirmBoxData[playerid][cb_sound]) {
				PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
			}

			CallLocalFunction(ConfirmBoxData[playerid][cb_functionName], "ddddf", playerid, CONFIRM_BOX_RESPONSE_YES, _:ConfirmBoxData[playerid][cb_selectable], _:ConfirmBoxData[playerid][cb_controllable], (100.00 - ConfirmBoxData[playerid][cb_percent]));
			HidePlayerConfirmBox(playerid);
		}
	}

	#if !defined _INC_y_hooks
		#if defined CB_OnPlayerClickTextDraw
			return CB_OnPlayerClickTextDraw(playerid, Text:clickedid);
		#else
			return 1;
		#endif
	#endif
}

#if !defined _INC_y_hooks
	#if defined _ALS_OnPlayerClickTextDraw
		#undef OnPlayerClickTextDraw
	#else
		#define _ALS_OnPlayerClickTextDraw
	#endif

	#define OnPlayerClickTextDraw CB_OnPlayerClickTextDraw

	#if defined CB_OnPlayerClickTextDraw
		forward CB_OnPlayerClickTextDraw(playerid, Text:clickedid);
	#endif
#endif