Route16_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Route16_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route16_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route16_OnWarp
	.byte 0

Route16_OnResume::
	call_if_set FLAG_SYS_SPECIAL_WILD_BATTLE, Route16_EventScript_RemoveSnorlax
	call_if_unset FLAG_SYS_NATIONAL_DEX, Route16_EventScript_HideRecurringSnorlax
	call_if_unset FLAG_HIDE_ROUTE_16_SNORLAX, Route16_EventScript_HideRecurringSnorlax
	end

Route16_EventScript_RemoveSnorlax::
	removeobject VAR_LAST_TALKED
	return

Route16_OnTransition::
	call_if_eq VAR_MAP_SCENE_ROUTE16, 1, Route16_OnTransitionCyclingRoad
	end

Route16_OnTransitionCyclingRoad::
	setflag FLAG_SYS_ON_CYCLING_ROAD
	return

Route16_OnWarp::
	map_script_2 VAR_MAP_SCENE_ROUTE16, 1, Route16_OnWarpCyclingRoad
	.2byte 0

Route16_OnWarpCyclingRoad::
	special ForcePlayerOntoBike
	end

Route16_EventScript_Snorlax::
	lock
	faceplayer
	goto_if_unset FLAG_GOT_POKE_FLUTE, Route16_EventScript_SnorlaxNoPokeFlute
	msgbox Text_WantToUsePokeFlute, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route16_EventScript_DontUsePokeFlute
	call EventScript_AwakenSnorlax
	waitse
	playmoncry SPECIES_SNORLAX, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	setflag FLAG_HIDE_ROUTE_16_SNORLAX
	setflag FLAG_SYS_SPECIAL_WILD_BATTLE
	setwildbattle SPECIES_SNORLAX, 30
	dowildbattle
	clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route16_EventScript_FoughtSnorlax
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route16_EventScript_FoughtSnorlax
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Route16_EventScript_FoughtSnorlax
	release
	end

Route16_EventScript_HideRecurringSnorlax::
    setflag FLAG_HIDE_ROUTE_16_RECURRING_SNORLAX
    end

Route16_EventScript_RecurringSnorlax::
	lock
	faceplayer
	goto_if_unset FLAG_GOT_POKE_FLUTE, Route16_EventScript_SnorlaxNoPokeFlute
	msgbox Text_AnotherSnorlaxHasAppeared, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route16_EventScript_DontUsePokeFlute
	setvar VAR_0x8004, FALSE
	setvar VAR_0x8005, 20
	specialvar VAR_0x8006, IsLeadMonAbilityCompoundEyes
	call_if_eq VAR_0x8006, TRUE, Route16_EventScript_SnorlaxIncreaseOdds
	random VAR_0x8005
	switch VAR_RESULT
	case 0, Route16_EventScript_SnorlaxSetGiveLeftoversTrue
Route16_EventScript_RecurringSnorlaxContinue::
	call EventScript_AwakenSnorlax
	waitse
	playmoncry SPECIES_SNORLAX, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	setflag FLAG_HIDE_ROUTE_16_RECURRING_SNORLAX
	setflag FLAG_SYS_SPECIAL_WILD_BATTLE
	call_if_eq VAR_0x8004, FALSE, Route16_EventScript_SnorlaxNoLeftovers
	call_if_eq VAR_0x8004, TRUE, Route16_EventScript_SnorlaxGiveLeftovers
	dowildbattle
	clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
	specialvar VAR_0x8007, GetBattleOutcome
	goto_if_eq VAR_0x8007, B_OUTCOME_WON, Route16_EventScript_FoughtSnorlax
	goto_if_eq VAR_0x8007, B_OUTCOME_RAN, Route16_EventScript_FoughtSnorlax
	goto_if_eq VAR_0x8007, B_OUTCOME_PLAYER_TELEPORTED, Route16_EventScript_FoughtSnorlax
	release
	end

Route16_EventScript_SnorlaxSetGiveLeftoversTrue::
	setvar VAR_0x8004, TRUE
	goto Route16_EventScript_RecurringSnorlaxContinue
	end

Route16_EventScript_SnorlaxNoLeftovers::
	setwildbattlerandomlevel SPECIES_SNORLAX, 45, 6
	return

Route16_EventScript_SnorlaxGiveLeftovers::
	setwildbattlerandomlevel SPECIES_SNORLAX, 45, 6, ITEM_LEFTOVERS
	return

Route16_EventScript_SnorlaxIncreaseOdds::
	setvar VAR_0x8005, 5
	return

Route16_EventScript_DontUsePokeFlute::
	release
	end

Route16_EventScript_FoughtSnorlax::
	msgbox Text_SnorlaxReturnedToMountains
	release
	end

Route16_EventScript_SnorlaxNoPokeFlute::
	msgbox Route16_Text_MonSprawledOutInSlumber
	release
	end

Route16_EventScript_CyclingRoadSign::
	msgbox Route16_Text_CyclingRoadSign, MSGBOX_SIGN
	end

Route16_EventScript_RouteSign::
	msgbox Route16_Text_RouteSign, MSGBOX_SIGN
	end
