# Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
	Custom/Transmogrification.h
	Custom/Transmogrification.cpp
	Custom/Transmogrifier.cpp
	Custom/autolearn.cpp
	Custom/chat.cpp
	Custom/Reforging.cpp
	Custom/custom_Fast_Arena_Start.cpp
	Custom/challenge_command.cpp
	Custom/Arena_Gobject.cpp
	Custom/npc_1v1arena.cpp
	Custom/npc_1v1arena.h
	Custom/beastmastery.cpp
	Custom/TemplateNPC.cpp
	Custom/TemplateNPC.h
	Custom/npc_solo3v3.cpp
	Custom/npc_solo3v3.h
)

message("  -> Prepared: Custom")
