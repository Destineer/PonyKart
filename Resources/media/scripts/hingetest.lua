-- load up our types
luanet.load_assembly("Mogre")
luanet.load_assembly("BulletSharp")
Vector3 = luanet.import_type("Mogre.Vector3")
HingeConstraint = luanet.import_type("BulletSharp.HingeConstraint")

-- this is run when we create a HingeTest.thing
function hingetest(lthing)
	-- spawn our static box and our moving box
	thing1 = spawn("StaticTallThinBox", addVectors(lthing.SpawnPosition, Vector3(0, 5, 0)))
	thing2 = spawn("TallThinBox", addVectors(lthing.SpawnPosition, Vector3(5, 5, 0)))
	
	-- make a hinge
	hinge = HingeConstraint(thing1.Body, thing2.Body, Vector3(2.5, 5, 0), Vector3(-2.5, 5, 0), Vector3.UNIT_Y, Vector3.UNIT_Y)
	-- remember that methods use : and not .!
	hinge:SetLimit(-1.57, 1.57)
	-- properties still use . though
	hinge.BreakingImpulseThreshold = 800
	-- and then add our constraint to the world
	addConstraint(hinge, false)
end