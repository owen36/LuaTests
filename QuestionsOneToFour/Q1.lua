-- recived code: This is how it started.
local function releaseStorage(player)
    player:setStorageValue(1000, -1)
end
    
function onLogout(player)
    if player:getStorageValue(1000) == 1 then
    addEvent(releaseStorage, 1000, player)
    end
    return true
end

-- proposed improvements:
-- 1. Add comments to the code to make it easier to understand.
-- 2. Add error handling to the code to prevent potential issues.
-- 3. Use constants for storage ID and release delay to make the code more readable and maintainable.
-- 4. Improve the error messages for better debugging.
-- 5. Readability improvements.
local STORAGE_ID = 1000
local RELEASE_DELAY_MS = 1000

local function releaseStorage(player)
    -- Check if player parameter is valid
    if not player then
        print("Error: [releaseStorage] Invalid player")
        return
    end
    
    -- Release storage by setting storage value to -1
    local success = player:setStorageValue(STORAGE_ID, -1)
    if not success then
        print("Error: Failed to release storage for player: " .. player:getName())
    end
end

function onLogout(player)
    -- Check if player parameter is valid
    if not player then
        print("Error: [onLogout] Invalid player")
        return false
    end
    
    -- Check if player has the required storage value
    if player:getStorageValue(STORAGE_ID) == 1 then
        -- Schedule releaseStorage function to be called after a delay
        local success = addEvent(releaseStorage, RELEASE_DELAY_MS, player)
        if not success then
            print("Error: Failed to schedule releaseStorage event for player: " .. player:getName())
        end
    end
    return true
end