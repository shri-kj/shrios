SerenityGarden_MapScripts::
	.byte 0

SerenityGarden_EventScript_Guide::
	lock
	faceplayer
	msgbox SerenityGarden_Text_Guide, MSGBOX_DEFAULT
	release
	end

SerenityGarden_EventScript_Wanderer::
	lock
	faceplayer
	msgbox SerenityGarden_Text_Wanderer, MSGBOX_DEFAULT
	release
	end

SerenityGarden_EventScript_Sign::
	msgbox SerenityGarden_Text_Sign, MSGBOX_SIGN
	end

SerenityGarden_Text_Guide:
	.string "Welcome to Serenity, a haven set apart\n"
	.string "for calm minds and curious souls.\p"
	.string "The light breeze here carries away\n"
	.string "every worry you brought with you.$"

SerenityGarden_Text_Wanderer:
	.string "The colors shift with the time of day,\n"
	.string "but the feeling never fades.\p"
	.string "I come here whenever I need to\n"
	.string "remember why I travel.$"

SerenityGarden_Text_Sign:
	.string "Serenity Garden\n"
	.string "Leave the noise behind.$"
