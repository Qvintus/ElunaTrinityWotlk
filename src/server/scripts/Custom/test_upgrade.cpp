#include "ScriptMgr.h"
#include "RBAC.h"
#include "Item.h"
#include "Chat.h"
#include "WorldSession.h"
#include "Object.h"
#include "Log.h"

class test_upgrade_class : public CommandScript
{
    public: 
        test_upgrade_class() : CommandScript("test_upgrade") { }

    std::vector<ChatCommand> GetCommands() const
	{
        std::vector<ChatCommand> commandtbl = {
            {"titem1", rbac::RBAC_PERM_COMMAND_GM, true, &tItemEnchant1Handler, ""}
        };
        return commandtbl;
    }

    static bool tItemEnchant1Handler(ChatHandler* chatHandler, char const* argsStr) {
        Player* player = chatHandler->GetSession()->GetPlayer();
        Item* mainhand = player->GetItemByPos(255, EQUIPMENT_SLOT_MAINHAND);
        uint64 guid = mainhand->GetGUID();

        TC_LOG_ERROR("misc", "GUID: %d", guid);
        return true;
    }
};

void AddSC_test_upgrade() {
    new test_upgrade_class();
}