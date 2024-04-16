// recived code: This is how it started.
void Game::addItemToPlayer(const std::string& recipient, uint16_t itemId)
{
Player* player = g_game.getPlayerByName(recipient);
if (!player) {
player = new Player(nullptr);
if (!IOLoginData::loadPlayerByName(player, recipient)) {
return;
}
}

Item* item = Item::CreateItem(itemId);
if (!item) {
return;
}

g_game.internalAddItem(player->getInbox(), item, INDEX_WHEREEVER, FLAG_NOLIMIT);

if (player->isOffline()) {
IOLoginData::savePlayer(player);
}
}

// proposed improvements:
// 1. cleanup the player object if it was newly created
void Game::addItemToPlayer(const std::string& recipient, uint16_t itemId)
{
    Player* player = g_game.getPlayerByName(recipient);

    // If player doesn't exist, try loading it
    if (!player) {
        player = new Player(nullptr);
        if (!IOLoginData::loadPlayerByName(player, recipient)) {
            delete player; // Cleanup if loading failed
            return;
        }
    }

    // Create the item
    Item* item = Item::CreateItem(itemId);
    if (!item) {
        // Cleanup and return if item creation failed
        if (!g_game.getPlayerByName(recipient)) {
            delete player;
        }
        return;
    }

    // Add the item to the player's inbox
    g_game.internalAddItem(player->getInbox(), item, INDEX_WHEREEVER, FLAG_NOLIMIT);

    // Save player data if offline
    if (player->isOffline()) {
        IOLoginData::savePlayer(player);
    }

    // Cleanup if player was newly created
    if (!g_game.getPlayerByName(recipient)) {
        delete player;
    }
}
