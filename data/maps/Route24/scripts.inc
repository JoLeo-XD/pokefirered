Route24_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION,Route24_EventScript_OnTransition
	.byte 0

Route24_EventScript_OnTransition::
	call_if_unset FLAG_BATTLED_NUGGET_ROCKET, Route24_EventScript_RocketChangeSpriteToMan
	call_if_set FLAG_BATTLED_NUGGET_ROCKET, Route24_EventScript_RocketChangeSpriteToGrunt
	end

Route24_EventScript_RocketChangeSpriteToMan::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_MAN
	return

Route24_EventScript_RocketChangeSpriteToGrunt::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_ROCKET_M
	return

Route24_EventScript_Rocket::
	lock
	faceplayer
	setvar VAR_TEMP_1, 2
	goto_if_eq VAR_MAP_SCENE_ROUTE24, 1, Route24_EventScript_RocketPostBattle
	goto_if_set FLAG_BATTLED_NUGGET_ROCKET, Route24_EventScript_BattleRocketGotNugget
	msgbox Route24_Text_JustEarnedFabulousPrize
	checkitemspace ITEM_NUGGET
	goto_if_eq VAR_RESULT, FALSE, Route24_EventScript_NoRoomForNugget
	call Route24_EventScript_BattleRocket
	release
	end

Route24_EventScript_NoRoomForNugget::
	msgbox Route24_Text_YouDontHaveAnyRoom
	release
	end

Route24_EventScript_RocketPostBattle::
	msgbox Route24_Text_YoudBecomeTopRocketLeader
	release
	end

Route24_EventScript_RocketTriggerLeft::
	lockall
	setvar VAR_TEMP_1, 0
	goto Route24_EventScript_RocketTrigger
	end

Route24_EventScript_RocketTriggerRight::
	lockall
	setvar VAR_TEMP_1, 1
	goto Route24_EventScript_RocketTrigger
	end

Route24_EventScript_RocketTrigger::
	textcolor NPC_TEXT_COLOR_MALE
	call_if_eq VAR_TEMP_1, 0, Route24_EventScript_RocketApproachPlayer
	call_if_eq VAR_TEMP_1, 1, Route24_EventScript_RocketMotionToPlayer
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	goto_if_set FLAG_BATTLED_NUGGET_ROCKET, Route24_EventScript_BattleRocketGotNugget
	msgbox Route24_Text_JustEarnedFabulousPrize
	checkitemspace ITEM_NUGGET
	goto_if_eq VAR_RESULT, FALSE, Route24_EventScript_NoRoomForNuggetTrigger
	call Route24_EventScript_BattleRocket
	releaseall
	end

Route24_EventScript_BattleRocket::
	setflag FLAG_BATTLED_NUGGET_ROCKET
	giveitem_msg Route24_Text_ReceivedNuggetFromMysteryTrainer, ITEM_NUGGET
	msgbox Route24_Text_JoinTeamRocket, MSGBOX_NPC
	setvar VAR_0x8004, LOCALID_ROUTE24_ROCKET
	setvar VAR_0x8005, OBJ_EVENT_GFX_ROCKET_M
	call_if_lt VAR_TEMP_1, 2, Route24_EventScript_RocketSpinLookLeft
	call_if_eq VAR_TEMP_1, 2, Route24_EventScript_RocketSpinLookDown
	message Route24_Text_MakeAnOfferYouCantRefuse
	waitmessage
	playbgm MUS_ENCOUNTER_ROCKET, 0
	waitbuttonpress
	setvar VAR_LAST_TALKED, LOCALID_ROUTE24_ROCKET
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_6, Route24_Text_RocketDefeat
	msgbox Route24_Text_YoudBecomeTopRocketLeader
	setvar VAR_MAP_SCENE_ROUTE24, 1
	return

Route24_EventScript_BattleRocketGotNugget::
	lockall
	message Route24_Text_DoYouNeedFurtherConvincing
	waitmessage
	playbgm MUS_ENCOUNTER_ROCKET, 0
	waitbuttonpress
	setvar VAR_LAST_TALKED, LOCALID_ROUTE24_ROCKET
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_6, Route24_Text_RocketDefeat
	msgbox Route24_Text_YoudBecomeTopRocketLeader
	setvar VAR_MAP_SCENE_ROUTE24, 1
	releaseall
	end

Route24_EventScript_RocketApproachPlayer::
	applymovement LOCALID_ROUTE24_ROCKET, Route24_Movement_RocketApproachPlayer
	waitmovement 0
	return

Route24_EventScript_RocketMotionToPlayer::
	applymovement LOCALID_ROUTE24_ROCKET, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

Route24_EventScript_RocketSpinLookLeft::
	applymovement LOCALID_ROUTE24_ROCKET, Route24_Movement_RocketSpinLookLeft
	waitmovement 0
	special SetLocalIdSprite
	applymovement LOCALID_ROUTE24_ROCKET, Route24_Movement_RocketSpinLookLeft
	waitmovement 0
	return

Route24_EventScript_RocketSpinLookDown::
	applymovement LOCALID_ROUTE24_ROCKET, Route24_Movement_RocketSpinLookDown
	waitmovement 0
	special SetLocalIdSprite
	applymovement LOCALID_ROUTE24_ROCKET, Route24_Movement_RocketSpinLookDown
	waitmovement 0
	return

Route24_EventScript_NoRoomForNuggetTrigger::
	msgbox Route24_Text_YouDontHaveAnyRoom
	closemessage
	applymovement LOCALID_PLAYER, Route24_Movement_WalkDown
	waitmovement 0
	call_if_eq VAR_TEMP_1, 0, Route24_EventScript_RocketWalkBackToPos
	release
	end

Route24_EventScript_RocketWalkBackToPos::
	applymovement LOCALID_ROUTE24_ROCKET, Route24_Movement_RocketWalkBackToPos
	waitmovement 0
	return

Route24_Movement_RocketApproachPlayer::
	walk_left
	step_end

Route24_Movement_RocketWalkBackToPos::
	walk_right
	walk_in_place_faster_left
	step_end

Route24_Movement_WalkDown::
	walk_down
	step_end

Route24_Movement_RocketSpinLookLeft::
	walk_in_place_faster_down
	delay_2
	walk_in_place_faster_right
	delay_2
	walk_in_place_faster_up
	delay_2
	walk_in_place_faster_left
	delay_2
	step_end

Route24_Movement_RocketSpinLookDown::
	walk_in_place_faster_right
	delay_2
	walk_in_place_faster_up
	delay_2
	walk_in_place_faster_left
	delay_2
	walk_in_place_faster_down
	delay_2
	step_end
