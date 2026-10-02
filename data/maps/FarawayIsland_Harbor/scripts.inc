FarawayIsland_Harbor_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, FarawayIsland_Harbor_OnLoad
	.byte 0

FarawayIsland_Harbor_OnLoad::
	call_if_unset FLAG_ARRIVED_ON_FARAWAY_ISLAND, FarawayIsland_Harbor_StopBGM
	end

FarawayIsland_Harbor_StopBGM::
	playbgm MUS_NONE, 1
	end

FarawayIsland_Harbor_EventScript_Sailor::
	goto_if_unset FLAG_ARRIVED_ON_FARAWAY_ISLAND, FarawayIsland_Harbor_EventScript_SailorLock
	lock
	faceplayer
	message Text_WhereDoYouWantToSail
	waitmessage
	setvar VAR_0x8004, SEAGALLOP_FARAWAY_ISLAND
	multichoice 20, 8, MULTICHOICE_SEAGALLOP_VERMILION, FALSE
	switch VAR_RESULT
	case 0, EventScript_SailToVermilionCity
	case 1, EventScript_CancelSail
	case 127, EventScript_CancelSail
	end

FarawayIsland_Harbor_EventScript_SailorLock::
	msgbox Text_ArentYouGoingToCheck, MSGBOX_NPC
	end

Text_ArentYouGoingToCheck::
    .string "Aren't you at least going to\n"
    .string "check it out?$"
