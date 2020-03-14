#include "ScriptMgr.h"
#include "RBAC.h"
#include "Item.h"
#include "Chat.h"
#include "WorldSession.h"
#include "WorldPacket.h"
#include "Object.h"
#include "Log.h"
#include "QueryPackets.h"
#include "Opcodes.h"

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
        ItemTemplate const* temp = mainhand->GetTemplate();
        
        WorldPackets::Query::QueryItemSingleResponse response;

        std::string locName = "Test Success";
        std::string locDescription = temp->Description;
        response.ItemID = temp->ItemId;
        response.Allow = true;

        response.Stats.Class = temp->Class;
        response.Stats.SubClass = temp->SubClass;
        response.Stats.SoundOverrideSubclass = temp->SoundOverrideSubclass;
        response.Stats.Name = locName;
        response.Stats.DisplayInfoID = temp->DisplayInfoID;
        response.Stats.Quality = temp->Quality;
        response.Stats.Flags = temp->Flags;
        response.Stats.Flags2 = temp->Flags2;
        response.Stats.BuyPrice = temp->BuyPrice;
        response.Stats.SellPrice = temp->SellPrice;
        response.Stats.InventoryType = temp->InventoryType;
        response.Stats.AllowableClass = temp->AllowableClass;
        response.Stats.AllowableRace = temp->AllowableRace;
        response.Stats.ItemLevel = temp->ItemLevel;
        response.Stats.RequiredLevel = temp->RequiredLevel;
        response.Stats.RequiredSkill = temp->RequiredSkill;
        response.Stats.RequiredSkillRank = temp->RequiredSkillRank;
        response.Stats.RequiredSpell = temp->RequiredSpell;
        response.Stats.RequiredHonorRank = temp->RequiredHonorRank;
        response.Stats.RequiredCityRank = temp->RequiredCityRank;
        response.Stats.RequiredReputationFaction = temp->RequiredReputationFaction;
        response.Stats.RequiredReputationRank = temp->RequiredReputationRank;
        response.Stats.MaxCount = temp->MaxCount;
        response.Stats.Stackable = temp->Stackable;
        response.Stats.ContainerSlots = temp->ContainerSlots;
        response.Stats.StatsCount = temp->StatsCount;
        for (uint32 i = 0; i < temp->StatsCount; ++i)
        {
            response.Stats.ItemStat[i].ItemStatType = temp->ItemStat[i].ItemStatType;
            response.Stats.ItemStat[i].ItemStatValue = temp->ItemStat[i].ItemStatValue; //Visual update
        }

        response.Stats.ScalingStatDistribution = temp->ScalingStatDistribution;
        response.Stats.ScalingStatValue = temp->ScalingStatValue;

        for (uint8 i = 0; i < MAX_ITEM_PROTO_DAMAGES; ++i)
        {
            response.Stats.Damage[i].DamageMin = temp->Damage[i].DamageMin;
            response.Stats.Damage[i].DamageMax = temp->Damage[i].DamageMax;
            response.Stats.Damage[i].DamageType = temp->Damage[i].DamageType;
        }

        response.Stats.Resistance[SPELL_SCHOOL_NORMAL] = temp->Armor;
        response.Stats.Resistance[SPELL_SCHOOL_HOLY] = temp->HolyRes;
        response.Stats.Resistance[SPELL_SCHOOL_FIRE] = temp->FireRes;
        response.Stats.Resistance[SPELL_SCHOOL_NATURE] = temp->NatureRes;
        response.Stats.Resistance[SPELL_SCHOOL_FROST] = temp->FrostRes;
        response.Stats.Resistance[SPELL_SCHOOL_SHADOW] = temp->ShadowRes;
        response.Stats.Resistance[SPELL_SCHOOL_ARCANE] = temp->ArcaneRes;

        response.Stats.Delay = temp->Delay;
        response.Stats.AmmoType = temp->AmmoType;
        response.Stats.RangedModRange = temp->RangedModRange;

        for (uint8 s = 0; s < MAX_ITEM_PROTO_SPELLS; ++s)
        {
            response.Stats.Spells[s].SpellId = temp->Spells[s].SpellId;
            response.Stats.Spells[s].SpellTrigger = temp->Spells[s].SpellTrigger;
            response.Stats.Spells[s].SpellCharges = temp->Spells[s].SpellCharges;
            response.Stats.Spells[s].SpellCooldown = temp->Spells[s].SpellCooldown;
            response.Stats.Spells[s].SpellCategory = temp->Spells[s].SpellCategory;
            response.Stats.Spells[s].SpellCategoryCooldown = temp->Spells[s].SpellCategoryCooldown;
        }

        response.Stats.Bonding = temp->Bonding;
        response.Stats.Description = locDescription;
        response.Stats.PageText = temp->PageText;
        response.Stats.LanguageID = temp->LanguageID;
        response.Stats.PageMaterial = temp->PageMaterial;
        response.Stats.StartQuest = temp->StartQuest;
        response.Stats.LockID = temp->LockID;
        response.Stats.Material = temp->Material;
        response.Stats.Sheath = temp->Sheath;
        response.Stats.RandomProperty = temp->RandomProperty;
        response.Stats.RandomSuffix = temp->RandomSuffix;
        response.Stats.Block = temp->Block;
        response.Stats.ItemSet = temp->ItemSet;
        response.Stats.MaxDurability = temp->MaxDurability;
        response.Stats.Area = temp->Area;
        response.Stats.Map = temp->Map;
        response.Stats.BagFamily = temp->BagFamily;
        response.Stats.TotemCategory = temp->TotemCategory;

        for (uint8 s = 0; s < MAX_ITEM_PROTO_SOCKETS; ++s)
        {
            response.Stats.Socket[s].Color = temp->Socket[s].Color;
            response.Stats.Socket[s].Content = temp->Socket[s].Content;
        }

        response.Stats.SocketBonus = temp->socketBonus;
        response.Stats.GemProperties = temp->GemProperties;
        response.Stats.RequiredDisenchantSkill = temp->RequiredDisenchantSkill;
        response.Stats.ArmorDamageModifier = temp->ArmorDamageModifier;
        response.Stats.Duration = temp->Duration;
        response.Stats.ItemLimitCategory = temp->ItemLimitCategory;
        response.Stats.HolidayId = temp->HolidayId;

        SendPacket(response.Write());

        return true;
    }
};

void AddSC_test_upgrade() {
    new test_upgrade_class();
}