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
            {"titem1", rbac::RBAC_PERM_COMMAND_GM, true, &tItemEnchant1Handler, ""},
            {"titem2", rbac::RBAC_PERM_COMMAND_GM, true, &tItemEnchant2Handler, ""}
        };
        return commandtbl;
    }

    static bool tItemEnchant1Handler(ChatHandler* chatHandler, char const* argsStr) {
        Player* player = chatHandler->GetSession()->GetPlayer();
        Item* mainhand = player->GetItemByPos(255, EQUIPMENT_SLOT_MAINHAND);
        uint32 val = mainhand->GetUInt32Value(ITEM_FIELD_ENCHANTMENT_1_1);
        TC_LOG_INFO("misc", "Mainhand enchant 1_1: %d", val);

        return true;
    }

    static bool tItemEnchant2Handler(ChatHandler* chatHandler, char const* argsStr) {
        Player* player = chatHandler->GetSession()->GetPlayer();
        Item* mainhand = player->GetItemByPos(255, EQUIPMENT_SLOT_MAINHAND);
        uint32 val = mainhand->GetUInt32Value(ITEM_FIELD_ENCHANTMENT_1_3);
        TC_LOG_INFO("misc", "Mainhand enchant 1_3: %d", val);

        return true;
    }

};

void AddSC_test_upgrade() {
    new test_upgrade_class();
}