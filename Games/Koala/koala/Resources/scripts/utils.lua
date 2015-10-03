cocos2d.CCLuaLog("Hello LUA")

function getCharacter(name)
    cocos2d.CCLuaLog("getCharacter " .. name)
    director = ichigo.Director:getInstance()
    cocos2d.CCLuaLog(director:getName())
    agent = director:findByName(name)
    cocos2d.CCLuaLog(agent:getName())
    character = tolua.cast(agent,"ichigo::Character")   
    return character
end

