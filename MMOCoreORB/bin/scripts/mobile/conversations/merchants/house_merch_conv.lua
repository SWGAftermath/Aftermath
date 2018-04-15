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
  customDialogText = "Welcome to Aftermath's Luxury Homes Shop!",
  stopConversation = "false",
  options = {
  	{"Hi, what Luxury Homes do you have in stock?", "banter1"},
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
  customDialogText = "Thank you for the business you take care now!",
  stopConversation = "true",
  options = {
  }
}
housemerch_template:addScreen(housemerch_bye);


housemerch_nope = ConvoScreen:new {
  id = "nope",
  leftDialog = "",
  customDialogText = "Well then...",
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
  customDialogText = "Sorry. It's pretty busy around here lately... Nice to see another member of the Lokian gang for a change. What can I do for you?",
  stopConversation = "false",
  options = {
	{"Who? are you?", "banter2"},
	{"I need a new Luxury Home", "shop"}
  }
}
housemerch_template:addScreen(housemerch_banter1);


housemerch_banter2 = ConvoScreen:new {
  id = "banter2",
  leftDialog = "",
  customDialogText = "Looking for a Luxury Home on Aftermath? You've come to the right place!",
  stopConversation = "false",
  options = {
	{"Perfect! I've found the right spot", "banter3"}
  }
}
housemerch_template:addScreen(housemerch_banter2);


housemerch_banter3 = ConvoScreen:new {
  id = "banter3",
  leftDialog = "",
  customDialogText = "I guess that is what I am these days... Ah well, What can I do for yea ?. ",
  stopConversation = "false",
  options = {
	{"Want to join us on our next job?", "banter4"},
	{"Care to show me your inventory?", "shop"}
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