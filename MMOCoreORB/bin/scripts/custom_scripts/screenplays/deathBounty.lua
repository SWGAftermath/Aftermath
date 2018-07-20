--True here tells the server to load this screenplay at server load. False tells it to wait until explicitly started.

deathBounty = ScreenPlay:new {
	screenplayName = deathBounty,
}

registerScreenPlay("deathBounty", true)