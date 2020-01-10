VendorConvoTemplate = ConvoTemplate:new {
	initialScreen = "initial",
	templateType = "Lua",
	luaClassHandler = "VendorConvoHandler",
	screens = {}
}

initial = ConvoScreen:new {
	id = "initial",
	customDialogText = "",
	stopConversation = "false",
	options = {
	}
}
VendorConvoTemplate:addScreen(initial);

start_sale = ConvoScreen:new {
	id = "start_sale",
	customDialogText = "",
	stopConversation = "true",
	options = {}
}
VendorConvoTemplate:addScreen(start_sale);

information_first = ConvoScreen:new {
	id = "information_first",
	customDialogText = "",
	stopConversation = "false",
	options = {}
}
VendorConvoTemplate:addScreen(information_first);

information_second = ConvoScreen:new {
	id = "information_second",
	customDialogText = "",
	stopConversation = "false",
	options = {}
}
VendorConvoTemplate:addScreen(information_second);

factionRestriction = ConvoScreen:new {
	id = "factionRestriction",
	customDialogText = "I don't sell to outsiders.",
	stopConversation = "true",
	options = {}
}
VendorConvoTemplate:addScreen(factionRestriction);

addConversationTemplate("VendorConvoTemplate", VendorConvoTemplate);

eventVendorConvoTemplate = VendorConvoTemplate:new {
	luaClassHandler = "EventVendorConvoHandler"
}

addConversationTemplate("eventVendorConvoTemplate", eventVendorConvoTemplate);

houseVendorConvoTemplate = VendorConvoTemplate:new {
	luaClassHandler = "HouseVendorConvoHandler"
}

addConversationTemplate("houseVendorConvoTemplate", houseVendorConvoTemplate);

HalloweenEventVendorConvoTemplate = VendorConvoTemplate:new {
	luaClassHandler = "HalloweenEventVendorConvoHandler"
}

addConversationTemplate("HalloweenEventVendorConvoTemplate", HalloweenEventVendorConvoTemplate);
