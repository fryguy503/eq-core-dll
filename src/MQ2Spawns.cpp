/*****************************************************************************
MQ2Main.dll: MacroQuest2's extension DLL for EverQuest
Copyright (C) 2002-2003 Plazmic, 2003-2005 Lax

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
******************************************************************************/
#if !defined(CINTERFACE)
//#error /DCINTERFACE
#endif

#define DBG_SPEW

//#define DEBUG_TRY 1
#include "MQ2Main.h"
#ifndef ISXEQ_LEGACY

extern std::map<int, int> g_PlayModesMap;

BOOL ProcessPending = false;

VOID SetNameSpriteTint(PSPAWNINFO pSpawn);

class EQPlayerHook
{
public:


    void EQPlayer_ExtraDetour(PSPAWNINFO pSpawn)
    {// note: we need to keep the original registers.
        __asm {push eax};
        __asm {push ebx};
        __asm {push ecx};
        __asm {push edx};
        __asm {push esi};
        __asm {push edi};
        OnAddSpawn(pSpawn);
        __asm {pop edi};
        __asm {pop esi};
        __asm {pop edx};
        __asm {pop ecx};
        __asm {pop ebx};
        __asm {pop eax};
    }
    /**/

    void EQPlayer_Trampoline(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
    void EQPlayer_Detour(DWORD p1, DWORD p2, DWORD p3, DWORD p4, DWORD p5, DWORD p6, DWORD p7)
    {
        PSPAWNINFO pSpawn;
        __asm {mov[pSpawn], ecx};

        EQPlayer_Trampoline(p1, p2, p3, p4, p5, p6, p7);
        EQPlayer_ExtraDetour(pSpawn);
        /**/
    }

    void dEQPlayer_Trampoline(void);
    void dEQPlayer_Detour(void)
    {
        void (EQPlayerHook:: * tmp)(void) = &EQPlayerHook::dEQPlayer_Trampoline;
        __asm {
            push ecx;
            push ecx;
            call OnRemoveSpawn;
            pop ecx;
            pop ecx;
            call[tmp];
        };
    }

    int SetNameSpriteState_Trampoline(bool Show);
    int SetNameSpriteState_Detour(bool Show)
    {
        if (gGameState != GAMESTATE_INGAME || !Show || !gMQCaptions)
            return SetNameSpriteState_Trampoline(Show);
        return 1;
    }

    bool SetNameSpriteTint_Trampoline(void);
    bool SetNameSpriteTint_Detour(void)
    {
        if (GetGameState() != GAMESTATE_INGAME || !gMQCaptions)
            return SetNameSpriteTint_Trampoline();
        return 1;
    }

    bool EQPlayerHook::IsTargetable(void);

};
FUNCTION_AT_ADDRESS(bool EQPlayerHook::IsTargetable(void), EQPlayer__IsTargetable);

class CActorEx
{
public:
    bool CanSetName(DWORD);
    void SetNameColor(DWORD& Color);
    void CActorEx::ChangeBoneStringSprite(int, int, char*);
};

FUNCTION_AT_VIRTUAL_ADDRESS(bool CActorEx::CanSetName(DWORD), 0x1a4);
FUNCTION_AT_VIRTUAL_ADDRESS(void CActorEx::SetNameColor(DWORD& Color), 0x190);
FUNCTION_AT_VIRTUAL_ADDRESS(void CActorEx::ChangeBoneStringSprite(int, int, char*), 0x18c);
#endif

typedef struct _CAPTIONCOLOR {
    PCHAR szName;
    PCHAR szDescription;
    BOOL Enabled;
    BOOL ToggleOnly;
    DWORD Color;
} CAPTIONCOLOR, PCAPTIONCOLOR;

#define CC_PC               0
#define CC_PCConColor       1
#define CC_PCPVPTeamColor   2
#define CC_PCRaidColor      3
#define CC_PCClassColor     4
#define CC_PCGroupColor     5
#define CC_PCTrader         6
#define CC_NPC              7
#define CC_NPCConColor      8
#define CC_NPCClassColor    9
#define CC_NPCMerchant      10
#define CC_NPCBanker        11
#define CC_NPCAssist        12 
#define CC_NPCMark          13 
#define CC_PetNPC           14
#define CC_PetPC            15
#define CC_PetConColor      16
#define CC_PetClassColor    17
#define CC_Corpse           18
#define CC_CorpseClassColor 19


CAPTIONCOLOR CaptionColors[] =
{
    {
        /*name*/"PC",
        /*desc*/"Default color for PCs",
        /* on */0,
        /*togl*/0,
        /*clr */0x00FF00FF,
            },
            {
                /*name*/"PCCon",
                /*desc*/"PCs by con color",
                /* on */0,
                /*togl*/1,
                /*clr */0,
                    },
                    {
                        /*name*/"PCPVPTeam",
                        /*desc*/"PCs by PVP team color",
                        /* on */0,
                        /*togl*/1,
                        /*clr */0,
                            },
                            {
                                /*name*/"PCRaid",
                                /*desc*/"Raid members",
                                /* on */0,
                                /*togl*/0,
                                /*clr */0x0000FF7F,
                                    },
                                    {
                                        /*name*/"PCClass",
                                        /*desc*/"PCs by class color(raid settings)",
                                        /* on */0,
                                        /*togl*/1,
                                        /*clr */0,
                                            },
                                            {
                                                /*name*/"PCGroup",
                                                /*desc*/"Group members",
                                                /* on */0,
                                                /*togl*/0,
                                                /*clr */0x00FFFF00,
                                                    },
                                                    {
                                                        /*name*/"PCTrader",
                                                        /*desc*/"Traders",
                                                        /* on */1,
                                                        /*togl*/0,
                                                        /*clr */0x00FF7F00,
                                                            },
                                                            {
                                                                /*name*/"NPC",
                                                                /*desc*/"NPC default color",
                                                                /* on */0,
                                                                /*togl*/0,
                                                                /*clr */0x00FF0000,
                                                                    },
                                                                    {
                                                                        /*name*/"NPCCon",
                                                                        /*desc*/"NPCs by con color",
                                                                        /* on */1,
                                                                        /*togl*/1,
                                                                        /*clr */0,
                                                                            },
                                                                            {
                                                                                /*name*/"NPCClass",
                                                                                /*desc*/"NPCs by class color (raid settings)",
                                                                                /* on */0,
                                                                                /*togl*/1,
                                                                                /*clr */0,
                                                                                    },
                                                                                    {
                                                                                        /*name*/"NPCMerchant",
                                                                                        /*desc*/"NPC Merchants",
                                                                                        /* on */1,
                                                                                        /*togl*/0,
                                                                                        /*clr */0x00FF7F00,
                                                                                            },
                                                                                            {
                                                                                                /*name*/"NPCBanker",
                                                                                                /*desc*/"NPC Bankers",
                                                                                                /* on */1,
                                                                                                /*togl*/0,
                                                                                                /*clr */0x00C800FF,
                                                                                                    },
                                                                                                    {
                                                                                                        /*name*/"NPCAssist",
                                                                                                        /*desc*/"NPCs from main assist",
                                                                                                        /* on */1,
                                                                                                        /*togl*/0,
                                                                                                        /*clr */0x00FFFF00,
                                                                                                            },
                                                                                                            {
                                                                                                                /*name*/"NPCMark",
                                                                                                                /*desc*/"Marked NPCs",
                                                                                                                /* on */1,
                                                                                                                /*togl*/0,
                                                                                                                /*clr */0x00FFFF00,
                                                                                                                    },
                                                                                                                    {
                                                                                                                        /*name*/"PetNPC",
                                                                                                                        /*desc*/"Pet with NPC owner",
                                                                                                                        /* on */0,
                                                                                                                        /*togl*/0,
                                                                                                                        /*clr */0x00FF0000,
                                                                                                                            },
                                                                                                                            {
                                                                                                                                /*name*/"PetPC",
                                                                                                                                /*desc*/"Pet with PC owner",
                                                                                                                                /* on */0,
                                                                                                                                /*togl*/0,
                                                                                                                                /*clr */0x00FFFF00,
                                                                                                                                    },
                                                                                                                                    {
                                                                                                                                        /*name*/"PetClass",
                                                                                                                                        /*desc*/"Pet by class color (raid settings)",
                                                                                                                                        /* on */0,
                                                                                                                                        /*togl*/0,
                                                                                                                                        /*clr */0x00FF0000,
                                                                                                                                            },
                                                                                                                                            {
                                                                                                                                                /*name*/"Corpse",
                                                                                                                                                /*desc*/"Corpses",
                                                                                                                                                /* on */0,
                                                                                                                                                /*togl*/0,
                                                                                                                                                /*clr */0x00FF0000,
                                                                                                                                                    },
                                                                                                                                                    {
                                                                                                                                                        /*name*/"CorpseClass",
                                                                                                                                                        /*desc*/"Corpse by class color (raid settings)",
                                                                                                                                                        /* on */0,
                                                                                                                                                        /*togl*/0,
                                                                                                                                                        /*clr */0x00FF0000,
                                                                                                                                                            },
                                                                                                                                                            {
                                                                                                                                                                /*name*/"",
                                                                                                                                                                /*desc*/"",
                                                                                                                                                                /* on */0,
                                                                                                                                                                /*togl*/0,
                                                                                                                                                                /*clr */0,
                                                                                                                                                                    },
};

// Color palette matching server side
namespace NameColorPalette {
    constexpr uint32_t None = 0;            // No color/skip - use trampoline
    constexpr uint32_t Default = 1;         // Default EQ player color - Blue
    constexpr uint32_t DedicatedTrader = 2; // Dedicated Trader - Purple
    constexpr uint32_t Seasonal = 3;        // Seasonal Character - Gold
    constexpr uint32_t Hardcore = 4;        // Hardcore mode - Blood Red

    static constexpr uint32_t Colors[5] = {
        0x00000000, // 0: None/Skip - Transparent/Default (use trampoline)
        0x003d6bdc, // 1: Default EQ blue
        0x00800080, // 2: Dedicated Trader - Purple
        0x00FFD700, // 3: Seasonal Character - Gold
        0x00A00000  // 4: Hardcore - Blood Red
    };
}

// Helper functions to create brightness variants
uint32_t MakeBrighter(uint32_t color, float factor = 1.5f) {
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;

    r = (uint8_t)min(255, (int)(r * factor));
    g = (uint8_t)min(255, (int)(g * factor));
    b = (uint8_t)min(255, (int)(b * factor));

    return (r << 16) | (g << 8) | b;
}

uint32_t MakeDarker(uint32_t color, float factor = 0.7f) {
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;

    r = (uint8_t)(r * factor);
    g = (uint8_t)(g * factor);
    b = (uint8_t)(b * factor);

    return (r << 16) | (g << 8) | b;
}

// Unpack 4 palette indices from uint32
void UnpackFourPaletteIndices(uint32_t packed, uint8_t& c1, uint8_t& c2, uint8_t& c3, uint8_t& c4) {
    c1 = (packed >> 24) & 0xFF;
    c2 = (packed >> 16) & 0xFF;
    c3 = (packed >> 8) & 0xFF;
    c4 = packed & 0xFF;
}

// Get color from palette index
uint32_t GetPaletteColor(uint8_t index) {
    if (index >= 5) return 0x00000000; // Invalid index
    return NameColorPalette::Colors[index];
}

// Interpolate between two colors
uint32_t InterpolateColors(uint32_t color1, uint32_t color2, float ratio) {
    if (ratio <= 0.0f) return color1;
    if (ratio >= 1.0f) return color2;

    // Extract RGB components
    uint8_t r1 = (color1 >> 16) & 0xFF;
    uint8_t g1 = (color1 >> 8) & 0xFF;
    uint8_t b1 = color1 & 0xFF;

    uint8_t r2 = (color2 >> 16) & 0xFF;
    uint8_t g2 = (color2 >> 8) & 0xFF;
    uint8_t b2 = color2 & 0xFF;

    // Interpolate
    uint8_t newR = (uint8_t)(r1 + (r2 - r1) * ratio);
    uint8_t newG = (uint8_t)(g1 + (g2 - g1) * ratio);
    uint8_t newB = (uint8_t)(b1 + (b2 - b1) * ratio);

    return (newR << 16) | (newG << 8) | newB;
}

// Timing configuration - adjust for 6 FPS update rate (every 1/10th second)
#define NAMEPLATE_UPDATE_FPS 6
#define TRANSITION_CYCLE_SECONDS 12.0f
#define TARGET_FLASH_SECONDS 1.0f
#define BASE_COLOR_LINGER_RATIO 0.6f

#define TRANSITION_CYCLE_TICKS ((int)(TRANSITION_CYCLE_SECONDS * NAMEPLATE_UPDATE_FPS))
#define TARGET_FLASH_TICKS ((int)(TARGET_FLASH_SECONDS * NAMEPLATE_UPDATE_FPS))

// Calculate transition color based on active colors and timing
// Always transition THROUGH the first color (index 0) when multiple colors are present
// Pattern: 0 -> 1 -> 0 -> 2 -> 0 -> 3 -> 0 -> 1 -> etc (with lingering on BASE color 0)
uint32_t CalculateTransitionColor(uint8_t colors[4], DWORD timer) {
    // Count active colors (non-zero indices)
    int activeColorCount = 0;
    uint32_t activeColors[4];

    for (int i = 0; i < 4; i++) {
        if (colors[i] > 0) {
            activeColors[activeColorCount] = GetPaletteColor(colors[i]);
            activeColorCount++;
        }
    }

    if (activeColorCount == 0) {
        return 0x00000000; // No colors, return default (no color applied)
    }

    if (activeColorCount == 1) {
        return activeColors[0]; // Single color, no transition
    }

    // Multiple colors: cycle through each color with base color between each
    // Total phases = (activeColorCount - 1) * 2  (to each color and back to base)
    const float cycleDuration = (float)TRANSITION_CYCLE_TICKS;
    const int totalPhases = (activeColorCount - 1) * 2; // Each non-base color gets "to" and "from" phases
    const float phaseDuration = cycleDuration / totalPhases;

    float cyclePosition = fmod((float)timer, cycleDuration);
    int phaseIndex = (int)(cyclePosition / phaseDuration);
    float phaseProgress = fmod(cyclePosition, phaseDuration) / phaseDuration;

    uint32_t baseColor = activeColors[0]; // Always cycle through this

    // Debug info
    static DWORD lastTimer = 0;
    if (timer != lastTimer) { // Only log when timer changes
        DebugSpew("Timer=%d, Phase=%d, Progress=%.2f, TotalPhases=%d",
            timer, phaseIndex, phaseProgress, totalPhases);
        lastTimer = timer;
    }

    if (phaseIndex % 2 == 0) {
        // Even phases: base color -> target color
        int targetIndex = (phaseIndex / 2) % (activeColorCount - 1) + 1; // +1 to skip base color
        uint32_t targetColor = activeColors[targetIndex];

        // Debug info
        static DWORD lastTimer2 = 0;
        if (timer != lastTimer2) { // Only log when timer changes
            DebugSpew("Phase %d: Base(0)=%x -> Target(%d)=%x, progress=%.2f",
                phaseIndex, baseColor, targetIndex, targetColor, phaseProgress);
            lastTimer2 = timer;
        }

        // Linger on BASE color for most of the phase
        if (phaseProgress < BASE_COLOR_LINGER_RATIO) {
            return baseColor; // Stay on base color
        }
        else {
            // Quick transition from base to target
            float adjustedProgress = (phaseProgress - BASE_COLOR_LINGER_RATIO) / (1.0f - BASE_COLOR_LINGER_RATIO);
            return InterpolateColors(baseColor, targetColor, adjustedProgress);
        }
    }
    else {
        // Odd phases: target color -> base color  
        int targetIndex = (phaseIndex / 2) % (activeColorCount - 1) + 1; // +1 to skip base color
        uint32_t targetColor = activeColors[targetIndex];

        // Debug info
        static DWORD lastTimer3 = 0;
        if (timer != lastTimer3) { // Only log when timer changes
            DebugSpew("Phase %d: Target(%d)=%x -> Base(0)=%x, progress=%.2f",
                phaseIndex, targetIndex, targetColor, baseColor, phaseProgress);
            lastTimer3 = timer;
        }

        // Quick transition from target back to base, then linger on BASE
        if (phaseProgress < (1.0f - BASE_COLOR_LINGER_RATIO)) {
            // Quick transition from target back to base
            float adjustedProgress = phaseProgress / (1.0f - BASE_COLOR_LINGER_RATIO);
            return InterpolateColors(targetColor, baseColor, adjustedProgress);
        }
        else {
            return baseColor; // Linger on BASE color
        }
    }
}

VOID SetNameSpriteTint(PSPAWNINFO pSpawn)
{
    if (!gMQCaptions) return;

    bool isTarget = (pSpawn == (PSPAWNINFO)pTarget);
    auto it = g_PlayModesMap.find(pSpawn->SpawnID);

    if (GetSpawnType(pSpawn) == PC && pSpawn && it != g_PlayModesMap.end()) {
        // Unpack the color indices from the server packet
        uint8_t c1, c2, c3, c4;
        UnpackFourPaletteIndices(it->second, c1, c2, c3, c4);
        uint8_t colors[4] = { c1, c2, c3, c4 };

        // Check if all colors are 0 (no play modes) - use default behavior
        if (c1 == 0 && c2 == 0 && c3 == 0 && c4 == 0) {
            ((EQPlayerHook*)pSpawn)->SetNameSpriteTint_Trampoline();
            return;
        }

        // Use spawn ID to create unique phase offset for each player (same rate, different phase)
        static DWORD globalTimer = 0;
        globalTimer++;
        DWORD phaseOffset = pSpawn->SpawnID * 37; // Phase offset based on spawn ID
        DWORD spawnTimer = globalTimer + phaseOffset; // Same rate, different starting point

        DWORD finalColor;

        if (isTarget) {
            // For targets: flash between bright grey and the transition color
            uint32_t transitionColor = CalculateTransitionColor(colors, spawnTimer);
            const uint32_t brightGrey = 0x00C0C0C0; // Bright grey

            // Flash based on configured timing
            bool showGrey = (spawnTimer % TARGET_FLASH_TICKS) < (TARGET_FLASH_TICKS / 2);
            finalColor = showGrey ? brightGrey : transitionColor;

            DebugSpew("Setting Target Nameplate flash to %x for %s (transition: %x) [Colors: %d=%x, %d=%x, %d=%x, %d=%x]",
                finalColor, pSpawn->Name, transitionColor,
                0, colors[0] ? GetPaletteColor(colors[0]) : 0,
                1, colors[1] ? GetPaletteColor(colors[1]) : 0,
                2, colors[2] ? GetPaletteColor(colors[2]) : 0,
                3, colors[3] ? GetPaletteColor(colors[3]) : 0);
        }
        else {
            // For non-targets: smooth transition between play mode colors
            finalColor = CalculateTransitionColor(colors, spawnTimer);

            DebugSpew("Setting Nameplate transition to %x for %s [Colors: %d=%x, %d=%x, %d=%x, %d=%x]",
                finalColor, pSpawn->Name,
                0, colors[0] ? GetPaletteColor(colors[0]) : 0,
                1, colors[1] ? GetPaletteColor(colors[1]) : 0,
                2, colors[2] ? GetPaletteColor(colors[2]) : 0,
                3, colors[3] ? GetPaletteColor(colors[3]) : 0);
        }

        DebugTry(((CActorEx*)pSpawn->pcactorex)->SetNameColor(finalColor));
        return;
    }

    // Use default EQ behavior for spawns without custom colors
}

BOOL SetNameSpriteState(PSPAWNINFO pSpawn, bool Show)
{
    //DebugSpew("SetNameSpriteState(%s) --race %d body %d)",pSpawn->Name,pSpawn->Race,GetBodyType(pSpawn));
    if (!Show)
    {
        ((EQPlayerHook*)pSpawn)->SetNameSpriteState_Trampoline(Show);
    }
    if (!gMQCaptions)
    {
        //DebugSpew("Returning default from SetNameSpriteState");
        return ((EQPlayerHook*)pSpawn)->SetNameSpriteState_Trampoline(Show);
    }
#define SetCaption(CaptionString) \
    {\
    if (CaptionString[0])\
    {\
    strcpy(NewCaption,CaptionString);\
    pNamingSpawn=pSpawn;\
    ParseMacroParameter(GetCharInfo()->pSpawn,NewCaption);\
    pNamingSpawn=0;\
    ((EQPlayer*)pSpawn)->ChangeBoneStringSprite(0,NewCaption);\
    return 1;\
    }\
    }
    CHAR NewCaption[MAX_STRING] = { 0 };
    //DebugSpew("Returning default from SetNameSpriteState");
    return ((EQPlayerHook*)pSpawn)->SetNameSpriteState_Trampoline(Show);
#undef SetCaption
}

VOID UpdateSpawnCaptions()
{
    //DebugSpew("UpdateSpawnCaptions()");
    DWORD N;
    DWORD Count = 0;
    for (N = 0; N < 120; N++)
    {
        if (PSPAWNINFO pSpawn = (PSPAWNINFO)EQP_DistArray[N].VarPtr.Ptr)
            if (pSpawn != (PSPAWNINFO)pTarget)
                if (EQP_DistArray[N].Value.Float <= 80.0f && gMQCaptions)
                {
                    if (SetNameSpriteState(pSpawn, true))
                    {
                        SetNameSpriteTint(pSpawn);
                        Count++;
                        if (Count >= gMaxSpawnCaptions)
                        {
                            return;
                        }
                    }
                }
                else
                {
                    return;
                }
    }
}

DETOUR_TRAMPOLINE_EMPTY(bool EQPlayerHook::SetNameSpriteTint_Trampoline(void));
DETOUR_TRAMPOLINE_EMPTY(int EQPlayerHook::SetNameSpriteState_Trampoline(bool Show));
DETOUR_TRAMPOLINE_EMPTY(VOID EQPlayerHook::dEQPlayer_Trampoline(VOID));
DETOUR_TRAMPOLINE_EMPTY(VOID EQPlayerHook::EQPlayer_Trampoline(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD));

VOID InitializeMQ2Spawns()
{
    DebugSpew("Initializing Spawn-related Hooks");
#ifndef GateBind
    ProcessGameEvents = 0;
#endif
    EzDetour(EQPlayer__EQPlayer, &EQPlayerHook::EQPlayer_Detour, &EQPlayerHook::EQPlayer_Trampoline);
    EzDetour(EQPlayer__dEQPlayer, &EQPlayerHook::dEQPlayer_Detour, &EQPlayerHook::dEQPlayer_Trampoline);
    EzDetour(EQPlayer__SetNameSpriteState, &EQPlayerHook::SetNameSpriteState_Detour, &EQPlayerHook::SetNameSpriteState_Trampoline);
    EzDetour(EQPlayer__SetNameSpriteTint, &EQPlayerHook::SetNameSpriteTint_Detour, &EQPlayerHook::SetNameSpriteTint_Trampoline);

    ProcessPending = true;
    ZeroMemory(&EQP_DistArray, sizeof(EQP_DistArray));
    gSpawnCount = 0;

    CHAR Temp[MAX_STRING] = { 0 };
    CHAR Name[MAX_STRING] = { 0 };
    // load custom spawn caption colors
    DWORD N;
    for (N = 0; CaptionColors[N].szName[0]; N++)
    {
        if (GetPrivateProfileString("Caption Colors", CaptionColors[N].szName, "", Temp, MAX_STRING, gszINIFilename))
        {
            if (!stricmp(Temp, "on") || !stricmp(Temp, "1"))
                CaptionColors[N].Enabled = 1;
            else
                CaptionColors[N].Enabled = 0;
        }
        sprintf(Name, "%s-Color", CaptionColors[N].szName);
        if (GetPrivateProfileString("Caption Colors", Name, "", Temp, MAX_STRING, gszINIFilename))
        {
            sscanf(Temp, "%x", &CaptionColors[N].Color);
        }
    }
    // write custom spawn caption colors
    for (N = 0; CaptionColors[N].szName[0]; N++)
    {
        WritePrivateProfileString("Caption Colors", CaptionColors[N].szName, CaptionColors[N].Enabled ? "ON" : "OFF", gszINIFilename);
        if (!CaptionColors[N].ToggleOnly)
        {
            sprintf(Temp, "%x", CaptionColors[N].Color);
            sprintf(Name, "%s-Color", CaptionColors[N].szName);
            WritePrivateProfileString("Caption Colors", Name, Temp, gszINIFilename);
        }
    }
}

VOID ShutdownMQ2Spawns()
{
    DebugSpew("Shutting Down Spawn-related Hooks");
    RemoveDetour(EQPlayer__EQPlayer);
    RemoveDetour(EQPlayer__dEQPlayer);
    RemoveDetour(EQPlayer__SetNameSpriteState);
    RemoveDetour(EQPlayer__SetNameSpriteTint);
    RemoveDetour(EQItemList__FreeItemList);
    RemoveDetour(EQItemList__add_item);
    RemoveDetour(EQItemList__delete_item);

    ProcessPending = false;

    ZeroMemory(EQP_DistArray, sizeof(EQP_DistArray));
    gSpawnCount = 0;
}

VOID UpdateMQ2SpawnSort()
{
    ZeroMemory(EQP_DistArray, sizeof(EQP_DistArray));
    gSpawnCount = 0;
    PSPAWNINFO pSpawn = (PSPAWNINFO)pSpawnList;
    while (pSpawn)
    {
        EQP_DistArray[gSpawnCount].VarPtr.Ptr = pSpawn;
        EQP_DistArray[gSpawnCount].Value.Float = GetDistance(pSpawn->X, pSpawn->Y);
        gSpawnCount++;
        pSpawn = pSpawn->pNext;
    }
    // quicksort!
    qsort(&EQP_DistArray[0], gSpawnCount, sizeof(MQRANK), MQRankFloatCompare);
    static unsigned long nCaptions = 100;
    static unsigned long LastTarget = 0;
    ++nCaptions;
    if (LastTarget)
    {
        if (PSPAWNINFO pSpawn = (PSPAWNINFO)GetSpawnByID(LastTarget))
        {
            if (pSpawn != (PSPAWNINFO)pTarget)
            {
                SetNameSpriteState(pSpawn, false);
            }
        }
        LastTarget = 0;
    }
    if (GetGameState() != -1 && GetGameState() == GAMESTATE_INGAME && nCaptions > 7)
    {
        nCaptions = 0;
        UpdateSpawnCaptions();
    }
    if (pTarget)
    {
        LastTarget = ((PSPAWNINFO)pTarget)->SpawnID;
        SetNameSpriteTint((PSPAWNINFO)pTarget);
        SetNameSpriteState((PSPAWNINFO)pTarget, true);
    }
}

#ifndef ISXEQ
VOID CaptionColorCmd(PSPAWNINFO pChar, PCHAR szLine)
{
    if (!szLine[0])
    {
        SyntaxError("Usage: /captioncolor <list|<name off|on|#>>");
        return;
    }
    CHAR Arg1[MAX_STRING] = { 0 };
    CHAR Arg2[MAX_STRING] = { 0 };
    GetArg(Arg1, szLine, 1);
    GetArg(Arg2, szLine, 2);

    if (!stricmp(Arg1, "list"))
    {
        WriteChatColor("Caption Color Settings");
        WriteChatColor("----------------------");
        for (DWORD N = 0; CaptionColors[N].szName[0]; N++)
        {
            if (!CaptionColors[N].Enabled || CaptionColors[N].ToggleOnly)
                WriteChatf("%s %s (%s)", CaptionColors[N].szName, CaptionColors[N].Enabled ? "ON" : "OFF", CaptionColors[N].szDescription);
            else
            {
                ARGBCOLOR Color;
                Color.ARGB = CaptionColors[N].Color;
                WriteChatf("%s ON Color: %d %d %d. (%s)", CaptionColors[N].szName, Color.R, Color.G, Color.B, CaptionColors[N].szDescription);
            }
        }
        return;
    }
    for (DWORD N = 0; CaptionColors[N].szName[0]; N++)
        if (!stricmp(Arg1, CaptionColors[N].szName))
        {
            if (Arg2[0])
            {
                if (!stricmp(Arg2, "on"))
                    CaptionColors[N].Enabled = 1;
                else if (!stricmp(Arg2, "off"))
                    CaptionColors[N].Enabled = 0;
                else if (CaptionColors[N].Enabled && !CaptionColors[N].ToggleOnly)
                {
                    ARGBCOLOR NewColor;
                    NewColor.A = 0;
                    NewColor.R = atoi(Arg2);
                    NewColor.G = atoi(GetArg(Arg2, szLine, 3));
                    NewColor.B = atoi(GetArg(Arg2, szLine, 4));
                    CaptionColors[N].Color = NewColor.ARGB;
                }
                else
                {
                    MacroError("Invalid option '%s' while '%s' is off.", Arg2, Arg1);
                    return;
                }
            }

            if (!CaptionColors[N].Enabled || CaptionColors[N].ToggleOnly)
                WriteChatf("%s %s (%s)", CaptionColors[N].szName, CaptionColors[N].Enabled ? "ON" : "OFF", CaptionColors[N].szDescription);
            else
            {
                ARGBCOLOR Color;
                Color.ARGB = CaptionColors[N].Color;
                WriteChatf("%s ON Color: %d %d %d. (%s)", CaptionColors[N].szName, Color.R, Color.G, Color.B, CaptionColors[N].szDescription);
            }
            WritePrivateProfileString("Caption Colors", CaptionColors[N].szName, CaptionColors[N].Enabled ? "ON" : "OFF", gszINIFilename);
            if (!CaptionColors[N].ToggleOnly)
            {
                sprintf(Arg2, "%x", CaptionColors[N].Color);
                sprintf(Arg1, "%s-Color", CaptionColors[N].szName);
                WritePrivateProfileString("Caption Colors", Arg1, Arg2, gszINIFilename);
            }
            return;
        }
}
#endif

BOOL IsTargetable(PSPAWNINFO pSpawn)
{
    return ((EQPlayerHook*)pSpawn)->IsTargetable();
}
