dreamKoala = getCharacter("dreamKoala")

count = 0

function dreamKoala_touch()
    cocos2d.CCLuaLog("I'm touched!!!")
    cocos2d.CCLuaLog(count)
    count = count + 1
    dreamKoala:say("I love you " .. count .. " times!")    
    return 0
end