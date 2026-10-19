EventScript_ItemfinderDigUpUnderfootItem::
	lockall
	textcolor NPC_TEXT_COLOR_NEUTRAL
	waitse
	call EventScript_TryPickUpHiddenItem
	goto_if_eq VAR_0x8007, TRUE, EventScript_DigUpItemPutInPocket
	goto_if_eq VAR_0x8007, FALSE, EventScript_DigUpItemBagIsFull
	end

EventScript_DigUpItemPutInPocket::
	buffergenderstringsingle STR_VAR_1, VAR_0x8005
	message Text_DugUpItemFromGround
	waitfanfare
	waitmessage
	delay 60
	buffergenderstring STR_VAR_1, VAR_0x8005, VAR_0x8006
	msgbox Text_PutItemAway
	special SetHiddenItemFlag
	releaseall
	end

EventScript_DigUpItemBagIsFull::
	buffergenderstringsingle STR_VAR_1, VAR_0x8005
	msgbox Text_DugUpItemFromGround
	msgbox Text_TooBadBagFull
	setvar VAR_RESULT, 0
	releaseall
	end
