#include "ScriptPCH.h"
#include "Group.h"

class skirmish_commandscript : public CommandScript
{
public:
    skirmish_commandscript() : CommandScript("skirmish_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand skirmishCommandTable[] =
        {
            { "2x2",            rbac::RBAC_PERM_COMMAND_2X2      false, &HandleSkirmish2x2Command,       "", NULL },
            { "3x3",            rbac::RBAC_PERM_COMMAND_3X3,      false, &HandleSkirmish3x3Command,       "", NULL },
            { "5x5",            rbac::RBAC_PERM_COMMAND_5X5,      false, &HandleSkirmish5x5Command,       "", NULL },
            { NULL,             0,                  false, NULL,                            "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "challenge",       rbac::RBAC_PERM_COMMAND_CHALLENGE,      false, NULL,                     "", skirmishCommandTable },
            { NULL,             0,                  false, NULL,                     "",                 NULL }
        };
        return commandTable;
    }

    static bool CreateSkirmish(ChatHandler* handler, char* args, uint8 type)
    {
        char* pParam1 = strtok(args, " ");
        if (!pParam1)
            return false;

        char* pParam2 = strtok(NULL, " ");
        if (!pParam2)
            return false;

        Player *player1, *player2;
        if (!handler->extractPlayerTarget(pParam1, &player1))
            return false;

        if (!handler->extractPlayerTarget(pParam2, &player2))
            return false;

        Group *gr1 = player1->GetGroup();
        Group *gr2 = player2->GetGroup();

        if (!gr1)
        {
            handler->PSendSysMessage("First player haven`t group.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!gr2)
        {
            handler->PSendSysMessage("Second player haven`t group.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!gr1->IsLeader(player1->GetGUID()))
        {
            handler->PSendSysMessage("First player isn`t leader.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!gr2->IsLeader(player2->GetGUID()))
        {
            handler->PSendSysMessage("Second player isn`t leader.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        WorldPacket data1(CMSG_BATTLEMASTER_JOIN_ARENA, 8+1+1+1);
        data1 << uint64(0);
        data1 << uint8(type);
        data1 << uint8(1);
        data1 << uint8(0);

        WorldPacket data2(CMSG_BATTLEMASTER_JOIN_ARENA, 8+1+1+1);
        data2 << uint64(0);
        data2 << uint8(type);
        data2 << uint8(1);
        data2 << uint8(0);

        ArenaType aType;

        switch (type)
        {
            case 0:
                aType = ARENA_TYPE_2v2;
                break;
            case 1:
                aType = ARENA_TYPE_3v3;
                break;
            case 2:
                aType = ARENA_TYPE_5v5;
                break;
            default:
                //sLog->outError("Unknown arena slot %u at CreateSkirmish", type);
                return false;
        }

        player1->setSkirmishStatus(aType, SKIRMISH_PREPEAR);
        player2->setSkirmishStatus(aType, SKIRMISH_PREPEAR);
        player1->GetSession()->HandleBattlemasterJoinArena(data1);
        player2->GetSession()->HandleBattlemasterJoinArena(data2);

        if (player1->getSkirmishStatus(aType) != SKIRMISH_JOINED)
        {
            player1->setSkirmishStatus(aType, SKIRMISH_NONE);
            handler->PSendSysMessage("There are some problems when try to join first team.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player2->getSkirmishStatus(aType) != SKIRMISH_JOINED)
        {
            player2->setSkirmishStatus(aType, SKIRMISH_NONE);
            handler->PSendSysMessage("There are some problems when try to join second team.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        return true;
    }

    static bool HandleSkirmish2x2Command(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        return CreateSkirmish(handler, (char*)args, 0);
    }

    static bool HandleSkirmish3x3Command(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        return CreateSkirmish(handler, (char*)args, 1);
    }

    static bool HandleSkirmish5x5Command(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        return CreateSkirmish(handler, (char*)args, 2);
    }

};

void AddSC_skirmish_commandscript()
{
    new skirmish_commandscript();
}