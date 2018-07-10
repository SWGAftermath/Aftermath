-- Legend of Hondo Merchant System
-- By Tatwi www.tpot.ca 2015


housemerch_template = ConvoTemplate:new {
	initialScreen = "start",
	templateType = "Lua",
	luaClassHandler = "housemerch_convo_handler",
	screens = {}
}


housemerch_start = ConvoScreen:new {
  id = "start",
  leftDialog = "",
  customDialogText = "What's a guy gotta do ta get a drink around here? Oh, yeah? Whadda ya want? Wait a minute...you look like a smart individual. You interested in some top of the line housing? If you are, I got ya covered. Just don't ask where I got it from.",
  stopConversation = "false",
  options = {
  	{"Top of the line housing? I'm going to need more information.", "banter1"},
  }
}
housemerch_template:addScreen(housemerch_start);


housemerch_shop = ConvoScreen:new {
  id = "shop",
  leftDialog = "",
  customDialogText = "Here's what I got right now.",
  stopConversation = "false",
  options = { 
  }
}
housemerch_template:addScreen(housemerch_shop);


housemerch_confirm_purchase = ConvoScreen:new {
  id = "confirm_purchase",
  leftDialog = "",
  customDialogText = "Are you sure this is one ya want?",
  stopConversation = "false",
  options = { 
  }
}
housemerch_template:addScreen(housemerch_confirm_purchase);


housemerch_bye = ConvoScreen:new {
  id = "bye",
  leftDialog = "",
  customDialogText = "Yeah, Yeah. Ya know where I am if ya want more blueprints.",
  stopConversation = "true",
  options = {
  }
}
housemerch_template:addScreen(housemerch_bye);


housemerch_nope = ConvoScreen:new {
  id = "nope",
  leftDialog = "",
  customDialogText = "Pfft, stop wasting my time then.",
  stopConversation = "true",
  options = { 
  }
}
housemerch_template:addScreen(housemerch_nope);


housemerch_get_lost = ConvoScreen:new {
  id = "get_lost",
  leftDialog = "",
  customDialogText = "You've got some nerve showing your face around here!",
  stopConversation = "false",
  options = {
	{"At least mine is a pretty face!", "get_lost_reply"}
  }
}
housemerch_template:addScreen(housemerch_get_lost);

housemerch_get_lost_reply = ConvoScreen:new {
  id = "get_lost_reply",
  leftDialog = "",
  customDialogText = "Please don't make me contact the authorities.",
  stopConversation = "true",
  options = {
  }
}
housemerch_template:addScreen(housemerch_get_lost_reply);


housemerch_faction_too_low = ConvoScreen:new {
  id = "faction_too_low",
  leftDialog = "",
  customDialogText = "Sorry, but I don't trust you enough to do business with you.",
  stopConversation = "false",
  options = {
	{"I get that. I really do... Bye", "bye"}
  }
}
housemerch_template:addScreen(housemerch_faction_too_low);


housemerch_insufficient_funds = ConvoScreen:new {
  id = "insufficient_funds",
  leftDialog = "",
  customDialogText = "This ain't a charity. Get outta here until you have some cash!",
  stopConversation = "true",
  options = { 
  }
}
housemerch_template:addScreen(housemerch_insufficient_funds);


housemerch_banter1 = ConvoScreen:new {
  id = "banter1",
  leftDialog = "",
  customDialogText = "I'm talking housing that isn't available anywhere else...an underground bunker or a vehicle garage. you name it, I got it. This is top of the line stuff, so don't expect it to be cheap. No funny business either, I only take cash all up front.",
  stopConversation = "false",
  options = {
	{"Is there any more information you can give me before I look at your stock?", "banter2"},
	{"I'm interested, let me see what you have.", "shop"}
  }
}
housemerch_template:addScreen(housemerch_banter1);


housemerch_banter2 = ConvoScreen:new {
  id = "banter2",
  leftDialog = "",
  customDialogText = "What do I look like to ya, a book? Look, it's like I said before...these are top of the line housing blueprints not available on the public market yet.",
  stopConversation = "false",
  options = {
	{"What am I supposed to do with just the blueprints?", "banter3"}
  }
}
housemerch_template:addScreen(housemerch_banter2);


housemerch_banter3 = ConvoScreen:new {
  id = "banter3",
  leftDialog = "",
  customDialogText = "You'll have ta find yourself an Architect willing to make these houses. Any Architect worth his own will be all over these blueprints. This stuff is of the highest quality and never seen before.",
  stopConversation = "false",
  options = {
	{"Is there any way I can see these houses before I purchase them, so I know what I'm buying?", "banter4"}
  }
}
housemerch_template:addScreen(housemerch_banter3);


housemerch_banter4 = ConvoScreen:new {
  id = "banter4",
  leftDialog = "",
  customDialogText = "You sure like to ask a lot of questions don't ya? There's a small area on the planet Naboo north-east of Theed, me and my associate have put up some display versions for potential customers to check out. You can find it at -3832, 5125.",
  stopConversation = "false",
  options = {
	{"Thanks for the information, show me what you have.", "shop"}
  }
}
housemerch_template:addScreen(housemerch_banter4);


-- Template Footer
addConversationTemplate("housemerch_template", housemerch_template)