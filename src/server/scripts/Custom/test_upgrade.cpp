#include "ScriptMgr.h"
#include "RBAC.h"
#include "Item.h"
#include "Chat.h"

class test_upgrade_class : public CommandScript
{
    public: 
        test_upgrade_class() : CommandScript("test_upgrade") { }

    std::vector<ChatCommand> GetCommands() const
	{
        std::vector<ChatCommand> commandtbl = {
            {"titem1", rbac::RBAC_PERM_COMMAND_GM, true, test_upgrade_class::&tItemEnchant1Handler, ""},
            {"titem2", rbac::RBAC_PERM_COMMAND_GM, true, test_upgrade_class::&tItemEnchant2Handler, ""}
        }
        return commandtbl;
    }

    void tItemEnchant1Handler(ChatHandler * handler, const char * args) {
        Player* player = handler->GetSession()->GetPlayer();
        Item* mainhand = player->GetItemByPos(255, EQUIPMENT_SLOT_MAINHAND);
        uint32 val = GetUInt32Value(ITEM_FIELD_ENCHANTMENT_1_1);
        TC_LOG_INFO("misc", "Mainhand enchant 1_1: %d", val);
    }

    void tItemEnchant2Handler(ChatHandler * handler, const char * args) {
        Player* player = handler->GetSession()->GetPlayer();
        Item* mainhand = player->GetItemByPos(255, EQUIPMENT_SLOT_MAINHAND);
        uint32 val = GetUInt32Value(ITEM_FIELD_ENCHANTMENT_1_3);
        TC_LOG_INFO("misc", "Mainhand enchant 1_3: %d", val);
    }

};

void AddSC_test_upgrade() {
    new test_upgrade_class();
}