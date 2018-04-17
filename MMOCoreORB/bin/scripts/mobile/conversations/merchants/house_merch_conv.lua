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
  customDialogText = "What's a guy gotta do to get a drink around here? Oh, yeah? What do ya want? Wait a minute...you look like a smart individual. You interested in some top of the line housing? If you are, I got ya covered. Just don't ask where I got it from.",
  stopConversation = "false",
  options = {
  	{"Top of the line housing? I'm going to need more information.", "banter1"},
  }
}
housemerch_template:addScreen(housemerch_start);


housemerch_shop = ConvoScreen:new {
  id = "shop",
  leftDialog = "",
  customDialogText = "Here's what I have in stock at the moment.",
  stopConversation = "false",
  options = { 
  }
}
housemerch_template:addScreen(housemerch_shop);


housemerch_confirm_purchase = ConvoScreen:new {
  id = "confirm_purchase",
  leftDialog = "",
  customDialogText = "Are you sure you would like to make this purchase?",
  stopConversation = "false",
  options = { 
  }
}
housemerch_template:addScreen(housemerch_confirm_purchase);


housemerch_bye = ConvoScreen:new {
  id = "bye",
  leftDialog = "",
  customDialogText = "Yeah, Yeah. You know where I am if you want more blueprints.",
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
  customDialogText = "Sorry, but you do not have enough credits on hand to make this purchase.",
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
  customDialogText = "What do I look like to you, a book? Look, it's like I said before...these are top of the line housing blueprints not available on the public market yet.",
  stopConversation = "false",
  options = {
	{"What am I supposed to do with just the blueprints?", "banter3"}
  }
}
housemerch_template:addScreen(housemerch_banter2);


housemerch_banter3 = ConvoScreen:new {
  id = "banter3",
  leftDialog = "",
  customDialogText = "You'll have ta find yourself an Architect willing to make these houses. Any Architect worth his own will be all over these blueprints. This stuff is top quality and never seen before.",
  stopConversation = "false",
  options = {
	{"Thanks for the information, show me what you have.", "shop"}
  }
}
housemerch_template:addScreen(housemerch_banter3);


housemerch_banter4 = ConvoScreen:new {
  id = "banter4",
  leftDialog = "",
  customDialogText = "I dunno... since we left Nym's and started our own thing here, you guys have done great with the pirating without me. I'm happy enough selling deed's for Luxury Homes",
  stopConversation = "false",
  options = {
	{"Alright, old man. Let's see what you've got then.", "shop"}
  }
}
housemerch_template:addScreen(housemerch_banter4);


-- Template Footer
addConversationTemplate("housemerch_template", housemerch_template)