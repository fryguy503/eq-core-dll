// MQ2Labels.cpp : Defines the entry point for the DLL application.
//

#include "MQ2Main.h"
#include "EQClasses.h"
#include <sstream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <windows.h>
#include <intrin.h>  
#include <unordered_map>


typedef enum eStatEntry
{
	eStatClassesBitmask = 1,
	eStatCurHP,
	eStatCurMana,
	eStatCurEndur,
	eStatMaxHP,
	eStatMaxMana,
	eStatMaxEndur,
	eStatMitigation,
	eStatEvasion,
	eStatSTR,
	eStatSTA,
	eStatDEX,
	eStatAGI,
	eStatINT,
	eStatWIS,
	eStatCHA,
	eStatMR,
	eStatFR,
	eStatCR,
	eStatDR,
	eStatPR,
	eStatHPRegen,
	eStatManaRegen,
	eStatEndurRegen,
	eStatATK,
	eStatHaste,
	eStatKickTimer,
	eStatBashTimer,
	eStatBackstabTimer,
	eStatFrenzyTimer,
	eStatStrikeTimer,
	eStatDummyValue,
	eStatCAuth,
	eStatMax
};

typedef enum EQLabelTypes {
	Name = 1,
	Level = 2,
	Class = 3,
	Deity = 4,
	Strength = 5,
	Stamina = 6,
	Dexterity = 7,
	Agility = 8,
	Wisdom = 9,
	Intelligence = 10,
	Charisma = 11,
	SavevsPoison = 12,
	SavevsDisease = 13,
	SavevsFire = 14,
	SavevsCold = 15,
	SavevsMagic = 16,
	CurrentHitPoints = 17,
	MaximumHitPoints = 18,
	HitPointPercentage = 19,
	ManaPercentage = 20,
	StaminaEndurancePercentage = 21,
	CurrentMitigation = 22,
	CurrentOffense = 23,
	Weight = 24,
	MaximumWeight = 25,
	ExperiencePercentage = 26,
	AlternateExperiencePercentage = 27,
	TargetName = 28,
	TargetHitPointPercentage = 29,
	GroupMember1Name = 30,
	GroupMember2Name = 31,
	GroupMember3Name = 32,
	GroupMember4Name = 33,
	GroupMember5Name = 34,
	GroupMember1HealthPercentage = 35,
	GroupMember2HealthPercentage = 36,
	GroupMember3HealthPercentage = 37,
	GroupMember4HealthPercentage = 38,
	GroupMember5HealthPercentage = 39,
	GroupPet1HealthPercentage = 40,
	GroupPet2HealthPercentage = 41,
	GroupPet3HealthPercentage = 42,
	GroupPet4HealthPercentage = 43,
	GroupPet5HealthPercentage = 44,
	Buff0 = 45,
	Buff1 = 46,
	Buff2 = 47,
	Buff3 = 48,
	Buff4 = 49,
	Buff5 = 50,
	Buff6 = 51,
	Buff7 = 52,
	Buff8 = 53,
	Buff9 = 54,
	Buff10 = 55,
	Buff11 = 56,
	Buff12 = 57,
	Buff13 = 58,
	Buff14 = 59,
	Spell1 = 60,
	Spell2 = 61,
	Spell3 = 62,
	Spell4 = 63,
	Spell5 = 64,
	Spell6 = 65,
	Spell7 = 66,
	Spell8 = 67,
	PlayersPetName = 68,
	PlayersPetHPPercent = 69,
	PlayersCurrentHP = 70,
	CurrentAlternateAdvancementPointsAvailabletoSpend = 71,
	CurrentExperiencePercentageAssignedtoAlternateAdvancement = 72,
	CharacterLastName = 73,
	CharacterTitle = 74,
	CurrentMP3SongName = 75,
	CurrentMP3SongDurationMinutesValue = 76,
	CurrentMP3SongDurationSecondsValue = 77,
	CurrentMP3SongPositionMinutesValue = 78,
	CurrentMP3SongPositionSecondsValue = 79,
	Song1 = 80,
	Song2 = 81,
	Song3 = 82,
	Song4 = 83,
	Song5 = 84,
	Song6 = 85,
	PetBuff1 = 86,
	PetBuff2 = 87,
	PetBuff3 = 88,
	PetBuff4 = 89,
	PetBuff5 = 90,
	PetBuff6 = 91,
	PetBuff7 = 92,
	PetBuff8 = 93,
	PetBuff9 = 94,
	PetBuff10 = 95,
	PetBuff11 = 96,
	PetBuff12 = 97,
	PetBuff13 = 98,
	PetBuff14 = 99,
	PetBuff15 = 100,
	PetBuff16 = 101,
	PetBuff17 = 102,
	PetBuff18 = 103,
	PetBuff19 = 104,
	PetBuff20 = 105,
	PetBuff21 = 106,
	PetBuff22 = 107,
	PetBuff23 = 108,
	PetBuff24 = 109,
	PetBuff25 = 110,
	PetBuff26 = 111,
	PetBuff27 = 112,
	PetBuff28 = 113,
	PetBuff29 = 114,
	PetBuff30 = 115,
	PersonalTributeTimer = 116,
	CurrentAmountofTributePoints = 117,
	TotalCareerTribute = 118,
	TributeCostPer10Mins = 119,
	TargetofTargetPercentage = 120,
	GuildTributeTimer = 121,
	GuildTributePool = 122,
	GuildTributePayment = 123,
	ManaNumber = 124,
	ManaNumberMax = 125,
	EnduranceNumber = 126,
	EnduranceNumberMax = 127,
	ManaMaxMana = 128,
	EnduranceMaxEndurance = 129,
	None130 = 130,
	None131 = 131,
	TaskSystemDurationTimer = 132,
	Spell9 = 133,
	CastingSpellName = 134,
	TargetofTargetName = 135,
	CorruptionResist = 136,
	PlayerCombatTimerLabel = 137,
	Spell10 = 138,
	GroupMember1ManaPercentage = 139,
	GroupMember2ManaPercentage = 140,
	GroupMember3ManaPercentage = 141,
	GroupMember4ManaPercentage = 142,
	GroupMember5ManaPercentage = 143,
	GroupMember1EndurancePercentage = 144,
	GroupMember2EndurancePercentage = 145,
	GroupMember3EndurancePercentage = 146,
	GroupMember4EndurancePercentage = 147,
	GroupMember5EndurancePercentage = 148,
	Spell11 = 149,
	Spell12 = 150,
	HPPercentageExtendedTargetWindow0 = 151,
	HPPercentageExtendedTargetWindow1 = 152,
	HPPercentageExtendedTargetWindow2 = 153,
	HPPercentageExtendedTargetWindow3 = 154,
	HPPercentageExtendedTargetWindow4 = 155,
	HPPercentageExtendedTargetWindow5 = 156,
	HPPercentageExtendedTargetWindow6 = 157,
	HPPercentageExtendedTargetWindow7 = 158,
	HPPercentageExtendedTargetWindow8 = 159,
	HPPercentageExtendedTargetWindow9 = 160,
	HPPercentageExtendedTargetWindow10 = 161,
	HPPercentageExtendedTargetWindow11 = 162,
	HPPercentageExtendedTargetWindow12 = 163,
	HPPercentageExtendedTargetWindow13 = 164,
	HPPercentageExtendedTargetWindow14 = 165,
	HPPercentageExtendedTargetWindow15 = 166,
	HPPercentageExtendedTargetWindow16 = 167,
	HPPercentageExtendedTargetWindow17 = 168,
	HPPercentageExtendedTargetWindow18 = 169,
	HPPercentageExtendedTargetWindow19 = 170,
	ManaPercentageExtendedTargetWindow0 = 171,
	ManaPercentageExtendedTargetWindow1 = 172,
	ManaPercentageExtendedTargetWindow2 = 173,
	ManaPercentageExtendedTargetWindow3 = 174,
	ManaPercentageExtendedTargetWindow4 = 175,
	ManaPercentageExtendedTargetWindow5 = 176,
	ManaPercentageExtendedTargetWindow6 = 177,
	ManaPercentageExtendedTargetWindow7 = 178,
	ManaPercentageExtendedTargetWindow8 = 179,
	ManaPercentageExtendedTargetWindow9 = 180,
	ManaPercentageExtendedTargetWindow10 = 181,
	ManaPercentageExtendedTargetWindow11 = 182,
	ManaPercentageExtendedTargetWindow12 = 183,
	ManaPercentageExtendedTargetWindow13 = 184,
	ManaPercentageExtendedTargetWindow14 = 185,
	ManaPercentageExtendedTargetWindow15 = 186,
	ManaPercentageExtendedTargetWindow16 = 187,
	ManaPercentageExtendedTargetWindow17 = 188,
	ManaPercentageExtendedTargetWindow18 = 189,
	ManaPercentageExtendedTargetWindow19 = 190,
	EndurancePercentageExtendedTargetWindow0 = 191,
	EndurancePercentageExtendedTargetWindow1 = 192,
	EndurancePercentageExtendedTargetWindow2 = 193,
	EndurancePercentageExtendedTargetWindow3 = 194,
	EndurancePercentageExtendedTargetWindow4 = 195,
	EndurancePercentageExtendedTargetWindow5 = 196,
	EndurancePercentageExtendedTargetWindow6 = 197,
	EndurancePercentageExtendedTargetWindow7 = 198,
	EndurancePercentageExtendedTargetWindow8 = 199,
	EndurancePercentageExtendedTargetWindow9 = 200,
	EndurancePercentageExtendedTargetWindow10 = 201,
	EndurancePercentageExtendedTargetWindow11 = 202,
	EndurancePercentageExtendedTargetWindow12 = 203,
	EndurancePercentageExtendedTargetWindow13 = 204,
	EndurancePercentageExtendedTargetWindow14 = 205,
	EndurancePercentageExtendedTargetWindow15 = 206,
	EndurancePercentageExtendedTargetWindow16 = 207,
	EndurancePercentageExtendedTargetWindow17 = 208,
	EndurancePercentageExtendedTargetWindow18 = 209,
	EndurancePercentageExtendedTargetWindow19 = 210,
	Haste = 211,
	HitPointRegeneration = 212,
	ManaRegeneration = 213,
	EnduranceRegeneration = 214,
	SpellShield = 215,
	CombatEffects = 216,
	Shielding = 217,
	DamageShielding = 218,
	DamageOverTimeShielding = 219,
	DamageShieldMitigation = 220,
	Avoidance = 221,
	Accuracy = 222,
	StunResist = 223,
	StrikeThrough = 224,
	HealAmount = 225,
	SpellDamage = 226,
	Clairvoyance = 227,
	SkillDamageBash = 228,
	SkillDamageBackstab = 229,
	SkillDamageDragonpunch = 230,
	SkillDamageEaglestrike = 231,
	SkillDamageFlyingkick = 232,
	SkillDamageKick = 233,
	SkillDamageRoundkick = 234,
	SkillDamageTigerclaw = 235,
	SkillDamageFrenzy = 236,
	WeightMaxWeight = 237,
	BaseStrength = 238,
	BaseStamina = 239,
	BaseDexterity = 240,
	BaseAgility = 241,
	BaseWisdom = 242,
	BaseIntelligence = 243,
	BaseCharisma = 244,
	BaseSavevsPoison = 245,
	BaseSavevsDisease = 246,
	BaseSavevsFire = 247,
	BaseSavevsCold = 248,
	BaseSavevsMagic = 249,
	BaseSavevsCorruption = 250,
	HeroicStrength = 251,
	HeroicStamina = 252,
	HeroicDexterity = 253,
	HeroicAgility = 254,
	HeroicWisdom = 255,
	HeroicIntelligence = 256,
	HeroicCharisma = 257,
	HeroicSavevsPoison = 258,
	HeroicSavevsDisease = 259,
	HeroicSavevsFire = 260,
	HeroicSavevsCold = 261,
	HeroicSavevsMagic = 262,
	HeroicSavevsCorruption = 263,
	CapStrength = 264,
	CapStamina = 265,
	CapDexterity = 266,
	CapAgility = 267,
	CapWisdom = 268,
	CapIntelligence = 269,
	CapCharisma = 270,
	CapSavevsPoison = 271,
	CapSavevsDisease = 272,
	CapSavevsFire = 273,
	CapSavevsCold = 274,
	CapSavevsMagic = 275,
	CapSavevsCorruption = 276,
	CapSpellShield = 277,
	CapCombatEffects = 278,
	CapShielding = 279,
	CapDamageShielding = 280,
	CapDamageOverTimeShielding = 281,
	CapDamageShieldMitigation = 282,
	CapAvoidance = 283,
	CapAccuracy = 284,
	CapStunResist = 285,
	CapStrikeThrough = 286,
	CapSkillDamageBash = 287,
	CapSkillDamageBackstab = 288,
	CapSkillDamageDragonpunch = 289,
	CapSkillDamageEaglestrike = 290,
	CapSkillDamageFlyingkick = 291,
	CapSkillDamageKick = 292,
	CapSkillDamageRoundkick = 293,
	CapSkillDamageTigerclaw = 294,
	CapSkillDamageFrenzy = 295,
	LoyaltyTokenCount = 296,
	TributeTrophyTimer = 297,
	TributeTrophyCost = 298,
	GuildTributeTrophyTimer = 299,
	GuildTributeTrophyCost = 300,
	TargetofPetHP = 301,
	AggroTargetName = 302,
	AggroMostHatedName = 303,
	AggroMostHatedNameNoLock = 304,
	AggroMyHatePercent = 305,
	AggroMyHatePercentNoLock = 306,
	AggroMostHatedHatePercent = 307,
	AggroMostHatedHatePercentNoLock = 308,
	AggroGroup1HatePercent = 309,
	AggroGroup2HatePercent = 310,
	AggroGroup3HatePercent = 311,
	AggroGroup4HatePercent = 312,
	AggroGroup5HatePercent = 313,
	AggroExtendedTarget1HatePercent = 314,
	AggroExtendedTarget2HatePercent = 315,
	AggroExtendedTarget3HatePercent = 316,
	AggroExtendedTarget4HatePercent = 317,
	AggroExtendedTarget5HatePercent = 318,
	AggroExtendedTarget6HatePercent = 319,
	AggroExtendedTarget7HatePercent = 320,
	AggroExtendedTarget8HatePercent = 321,
	AggroExtendedTarget9HatePercent = 322,
	AggroExtendedTarget10HatePercent = 323,
	AggroExtendedTarget11HatePercent = 324,
	AggroExtendedTarget12HatePercent = 325,
	AggroExtendedTarget13HatePercent = 326,
	AggroExtendedTarget14HatePercent = 327,
	AggroExtendedTarget15HatePercent = 328,
	AggroExtendedTarget16HatePercent = 329,
	AggroExtendedTarget17HatePercent = 330,
	AggroExtendedTarget18HatePercent = 331,
	AggroExtendedTarget19HatePercent = 332,
	AggroExtendedTarget20HatePercent = 333,
	NA334 = 334,
	MercenaryAAExperiencePercentLabel = 335,
	MercenaryAAExperiencePointsLabel = 336,
	MercenaryAAExperiencePointsSpentLabel = 337,
	MercenaryHP = 338,
	MercenaryMaxHP = 339,
	MercenaryMana = 340,
	MercenaryMaxMana = 341,
	MercenaryEndurance = 342,
	MercenaryMaxEndurance = 343,
	MercenaryArmorClass = 344,
	MercenaryAttack = 345,
	MercenaryHastePercent = 346,
	MercenaryStrength = 347,
	MercenaryStamina = 348,
	MercenaryIntelligence = 349,
	MercenaryWisdom = 350,
	MercenaryAgility = 351,
	MercenaryDexterity = 352,
	MercenaryCharisma = 353,
	MercenaryCombatHPRegeneration = 354,
	MercenaryCombatManaRegeneration = 355,
	MercenaryCombatEnduranceRegeneration = 356,
	MercenaryHealAmount = 357,
	MercenarySpellDamage = 358,
	NA359 = 359,
	PowerSourcePercentageRemaining = 360,
	NA361 = 361,
	Velocity = 401,
	AccuracyAgain = 402,
	Evasion = 403,
	NA404 = 404,
	Spell13 = 414,
	Spell14 = 415,
	NA416 = 416,
	ExtraBuff0 = 500,
	ExtraBuff1 = 501,
	ExtraBuff2 = 502,
	ExtraBuff3 = 503,
	ExtraBuff4 = 504,
	ExtraBuff5 = 505,
	ExtraBuff6 = 506,
	ExtraBuff7 = 507,
	ExtraBuff8 = 508,
	ExtraBuff9 = 509,
	ExtraBuff10 = 510,
	ExtraBuff11 = 511,
	ExtraBuff12 = 512,
	ExtraBuff13 = 513,
	ExtraBuff14 = 514,
	ExtraBuff15 = 515,
	ExtraBuff16 = 516,
	ExtraBuff17 = 517,
	ExtraBuff18 = 518,
	ExtraBuff19 = 519,
	ExtraBuff20 = 520,
	ExtraBuff21 = 521,
	ExtraBuff22 = 522,
	ExtraBuff23 = 523,
	ExtraBuff24 = 524,
	ExtraBuff25 = 525,
	ExtraBuff26 = 526,
	ExtraBuff27 = 527,
	ExtraBuff28 = 528,
	ExtraBuff29 = 529,
	ExtraBuff30 = 530,
	ExtraBuff31 = 531,
	ExtraBuff32 = 532,
	ExtraBuff33 = 533,
	ExtraBuff34 = 534,
	ExtraBuff35 = 535,
	ExtraBuff36 = 536,
	ExtraBuff37 = 537,
	ExtraBuff38 = 538,
	ExtraBuff39 = 539,
	ExtraBuff40 = 540,
	ExtraBuff41 = 541,
	NA549 = 549,
	BlockedBuff0 = 550,
	BlockedBuff1 = 551,
	BlockedBuff2 = 552,
	BlockedBuff3 = 553,
	BlockedBuff4 = 554,
	BlockedBuff5 = 555,
	BlockedBuff6 = 556,
	BlockedBuff7 = 557,
	BlockedBuff8 = 558,
	BlockedBuff9 = 559,
	BlockedBuff10 = 560,
	BlockedBuff11 = 561,
	BlockedBuff12 = 562,
	BlockedBuff13 = 563,
	BlockedBuff14 = 564,
	BlockedBuff15 = 565,
	BlockedBuff16 = 566,
	BlockedBuff17 = 567,
	BlockedBuff18 = 568,
	BlockedBuff19 = 569,
	BlockedBuff20 = 570,
	BlockedBuff21 = 571,
	BlockedBuff22 = 572,
	BlockedBuff23 = 573,
	BlockedBuff24 = 574,
	BlockedBuff25 = 575,
	BlockedBuff26 = 576,
	BlockedBuff27 = 577,
	BlockedBuff28 = 578,
	BlockedBuff29 = 579,
	NA580 = 580,
	SongBuff0 = 600,
	SongBuff1 = 601,
	SongBuff2 = 602,
	SongBuff3 = 603,
	SongBuff4 = 604,
	SongBuff5 = 605,
	SongBuff6 = 606,
	SongBuff7 = 607,
	SongBuff8 = 608,
	SongBuff9 = 609,
	SongBuff10 = 610,
	SongBuff11 = 611,
	SongBuff12 = 612,
	SongBuff13 = 613,
	SongBuff14 = 614,
	SongBuff15 = 615,
	SongBuff16 = 616,
	SongBuff17 = 617,
	SongBuff18 = 618,
	SongBuff19 = 619,
	SongBuff20 = 620,
	SongBuff21 = 621,
	SongBuff22 = 622,
	SongBuff23 = 623,
	SongBuff24 = 624,
	SongBuff25 = 625,
	SongBuff26 = 626,
	SongBuff27 = 627,
	SongBuff28 = 628,
	SongBuff29 = 629,
	NA630 = 630,
	PetBlockedBuff0 = 650,
	PetBlockedBuff1 = 651,
	PetBlockedBuff2 = 652,
	PetBlockedBuff3 = 653,
	PetBlockedBuff4 = 654,
	PetBlockedBuff5 = 655,
	PetBlockedBuff6 = 656,
	PetBlockedBuff7 = 657,
	PetBlockedBuff8 = 658,
	PetBlockedBuff9 = 659,
	PetBlockedBuff10 = 660,
	PetBlockedBuff11 = 661,
	PetBlockedBuff12 = 662,
	PetBlockedBuff13 = 663,
	PetBlockedBuff14 = 664,
	PetBlockedBuff15 = 665,
	PetBlockedBuff16 = 666,
	PetBlockedBuff17 = 667,
	PetBlockedBuff18 = 668,
	PetBlockedBuff19 = 669,
	PetBlockedBuff20 = 670,
	PetBlockedBuff21 = 671,
	PetBlockedBuff22 = 672,
	PetBlockedBuff23 = 673,
	PetBlockedBuff24 = 674,
	PetBlockedBuff25 = 675,
	PetBlockedBuff26 = 676,
	PetBlockedBuff27 = 677,
	PetBlockedBuff28 = 678,
	PetBlockedBuff29 = 679,
	ClassAbbrList = 6666,
	TrueEvasion = 6667,
	TrueMitigation = 6668,
	EchoOfMemory = 6669,
	EQLabelTypesMax,
};

typedef enum SkillID {
	SKILL_BACKSTAB = 8,
	SKILL_BASH = 10,
	SKILL_KICK = 30,
	SKILL_ROUND_KICK = 38,
	SKILL_FLYING_KICK = 26,
	SKILL_DRAGON_PUNCH = 21,
	SKILL_EAGLE_STRIKE = 23,
	SKILL_TIGER_CLAW = 52,
	SKILL_FRENZY = 74
};

typedef string(*pEqTypesFunc)(EQLabelTypes LabelID);

typedef struct ClassInfo {
	std::vector<std::string> levelTitles;
};

std::map<int, std::vector<std::string>> BuildClassInfoMap() {
	std::map<int, std::vector<std::string>> classInfoMap;

	classInfoMap[1] = { {"Warrior", "Champion", "Myrmidon", "Warlord", "Overlord", "Vanquisher", "Imperator"} };
	classInfoMap[2] = { {"Cleric", "Vicar", "Templar", "High Priest", "Archon", "Prelate", "Exemplar"} };
	classInfoMap[3] = { {"Paladin", "Cavalier", "Knight", "Crusader", "Lord Protector", "Lord", "Holy Defender"} };
	classInfoMap[4] = { {"Ranger", "Pathfinder", "Outrider", "Warder", "Forest Stalker", "Plainswalker", "Huntmaster"} };
	classInfoMap[5] = { {"Shadow Knight", "Reaver", "Revenant", "Grave Lord", "Dread Lord", "Scourge Knight", "Bloodreaver"} };
	classInfoMap[6] = { {"Druid", "Wanderer", "Preserver", "Hierophant", "Storm Warden", "Natureguard", "Stormcaller"} };
	classInfoMap[7] = { {"Monk", "Disciple", "Master", "Grandmaster", "Transcendent", "Stone Fist", "Ashenhand"} };
	classInfoMap[8] = { {"Bard", "Minstrel", "Troubadour", "Virtuoso", "Maestro", "Herald", "Lyricist"} };
	classInfoMap[9] = { {"Rogue", "Rake", "Blackguard", "Assassin", "Deceiver", "Nemesis", "Shadowblade"} };
	classInfoMap[10] = { {"Shaman", "Mystic", "Luminary", "Oracle", "Prophet", "Soothsayer", "Spiritwatcher"} };
	classInfoMap[11] = { {"Necromancer", "Heretic", "Defiler", "Warlock", "Arch Lich", "Wraith", "Deathcaller"} };
	classInfoMap[12] = { {"Wizard", "Channeler", "Evoker", "Sorceror", "Arcanist", "Grand Arcanist", "Arch Arcanist"} };
	classInfoMap[13] = { {"Magician", "Elementalist", "Conjurer", "Arch Mage", "Arch Convoker", "Arch Magus", "Grand Summoner"} };
	classInfoMap[14] = { {"Enchanter", "Illusionist", "Beguiler", "Phantasmist", "Coercer", "Bedazzler", "Entrancer"} };
	classInfoMap[15] = { {"Beastlord", "Primalist", "Animist", "Savage Lord", "Feral Lord", "Wildblood", "Arch Animist"} };
	classInfoMap[16] = { {"Berserker", "Brawler", "Vehement", "Rager", "Fury", "Ravager", "Juggernaut"} };

	return classInfoMap;
}

std::map<EQLabelTypes, pEqTypesFunc> eqTypesMap = std::map<EQLabelTypes, pEqTypesFunc>();
std::map<EQLabelTypes, eStatEntry> statLabelMappings = std::map<EQLabelTypes, eStatEntry>();
std::map<eStatEntry, int64_t> statEntries;
std::map<int, std::vector<std::string>> classNames;
std::unordered_map<unsigned int, unsigned int> skillCooldowns;

int char_sel_data_cache = 0;

int statArray[6] = { 0 };


std::string GetSpeedFloatRepresentationOfStat(eStatEntry statType)
{
	auto statItr = statEntries.find(statType);

	if (statItr != statEntries.end())
	{
		std::stringstream strStream(stringstream::in || stringstream::out);
		strStream.precision(3);
		strStream << (float)((statItr)->second / 100000.f);
		return strStream.str();
	}

	return string(" ");
}

std::string GetStringWeightFloatRepresentationOfStat(eStatEntry statType)
{
	auto statItr = statEntries.find(statType);

	if (statEntries.find(statType) != statEntries.end())
	{
		double num_val = (statItr)->second / 10.0;

		std::stringstream strStream(stringstream::in | stringstream::out);
		strStream << num_val;
		return strStream.str();
	}

	return string(" ");
}

std::string GetStringRepresentationOfStat(eStatEntry statType)
{
	auto statItr = statEntries.find(statType);

	if (statEntries.find(statType) != statEntries.end())
	{
		std::stringstream strStream(stringstream::in | stringstream::out);
		strStream << (statItr)->second;
		return strStream.str();
	}

	return string(" ");
}

std::string EQLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return string(" ");

	auto iter = statLabelMappings.find(EQLabelTypes(LabelID));
	if (iter == statLabelMappings.end())
		return string(" ");

	return GetStringRepresentationOfStat(iter->second);
}

std::string GetStringRepresentationOfClass(int class_id, int level) {
	auto it = classNames.find(class_id);
	if (it != classNames.end()) {
		const std::vector<std::string>& titles = it->second;

		// Determine the index based on level
		int index = 0;
		if (level >= 1 && level <= 50) {
			index = 0;  // Level 1 to 50
		}
		else if (level <= 54) {
			index = 1;  // Level 51 to 54
		}
		else if (level <= 59) {
			index = 2;  // Level 55 to 59
		}
		else if (level <= 64) {
			index = 3;  // Level 60 to 64
		}
		else if (level <= 69) {
			index = 4;  // Level 65 to 69
		}
		else if (level <= 74) {
			index = 5;  // Level 70 to 74
		}
		else {
			index = 6; // Level 75+
		}

		// Check if the index is within the range of available titles
		if (index < titles.size()) {
			return string(titles[index]);
		}
	}

	return "Unknown Class";
}

std::string EQClassFunction(EQLabelTypes LabelID) {
	if (statEntries.find(eStatClassesBitmask) != statEntries.end()) {
		int classesBitmask = statEntries[eStatClassesBitmask];
		std::string result;

		for (int i = 1; i <= 16; i++) {
			if (classesBitmask & (1 << (i - 1))) {  // Check if the ith bit is set
				if (!result.empty()) {
					result += "\n";  // Add newline to separate class names
				}
				result += GetStringRepresentationOfClass(i, (int)pLocalPlayer->Data.pSpawn->Level);  // Append class name
			}
		}

		return result.empty() ? "DoodooHead" : result;
	}
	else {
		return "ERROR";
	}
}

std::string EQClassAbbrFunction(EQLabelTypes LabelID) {
	if (statEntries.find(eStatClassesBitmask) != statEntries.end()) {

		// Define the array for class ID to abbreviation
		static const std::string classAbbreviations[17] = {
			"",  // Index 0 will not be used
			"WAR",
			"CLR",
			"PAL",
			"RNG",
			"SHD",
			"DRU",
			"MNK",
			"BRD",
			"ROG",
			"SHM",
			"NEC",
			"WIZ",
			"MAG",
			"ENC",
			"BST",
			"BER"
		};

		int classesBitmask = statEntries[eStatClassesBitmask];
		std::string result;

		for (int i = 1; i <= 16; i++) {
			if (classesBitmask & (1 << (i - 1))) {  // Check if the ith bit is set
				if (!result.empty()) {
					result += "\n";  // Add newline to separate class names
				}
				result += classAbbreviations[i];
			}
		}

		return result.empty() ? "DoodooHead" : result;
	}
	else {
		return "ERROR";
	}
}

std::string EQDualManaLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return string(" ");

	return GetStringRepresentationOfStat(eStatCurMana) + " / " + GetStringRepresentationOfStat(eStatMaxMana);
}

std::string EQSpeedLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return string(" ");

	auto iter = statLabelMappings.find(EQLabelTypes(LabelID));
	if (iter == statLabelMappings.end())
		return string(" ");

	return GetSpeedFloatRepresentationOfStat(iter->second);
}

std::string EQDualHPLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return string(" ");

	return GetStringRepresentationOfStat(eStatCurHP) + " / " + GetStringRepresentationOfStat(eStatMaxHP);
}

std::string EQHPPercentageLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return "100";

	auto statItrCur = statEntries.find(eStatCurHP);

	auto statItrMax = statEntries.find(eStatMaxHP);

	if (statItrCur == statEntries.end() || statItrMax == statEntries.end())
	{
		return "100";
	}

	auto statCur = statItrCur->second;
	auto statMax = statItrMax->second;

	auto outVal = (int)((double)statCur / (double)statMax * 100.0);
	std::stringstream strStream(stringstream::in | stringstream::out);
	strStream << outVal;
	return strStream.str();
}

std::string EQManaPercentageLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return "100";

	auto statItrCur = statEntries.find(eStatCurMana);

	auto statItrMax = statEntries.find(eStatMaxMana);

	if (statItrCur == statEntries.end() || statItrMax == statEntries.end())
	{
		return "100";
	}

	auto statCur = statItrCur->second;
	auto statMax = statItrMax->second;

	auto outVal = (int)((double)statCur / (double)statMax * 100.0);
	std::stringstream strStream(stringstream::in | stringstream::out);
	strStream << outVal;
	return strStream.str();
}

std::string EQEndurPercentageLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return "100";

	auto statItrCur = statEntries.find(eStatCurEndur);

	auto statItrMax = statEntries.find(eStatMaxEndur);

	if (statItrCur == statEntries.end() || statItrMax == statEntries.end())
	{
		return "100";
	}

	auto statCur = statItrCur->second;
	auto statMax = statItrMax->second;

	auto outVal = (int)((double)statCur / (double)statMax * 100.0);
	std::stringstream strStream(stringstream::in | stringstream::out);
	strStream << outVal;
	return strStream.str();
}

std::string EQGaugeLabelFunction(eStatEntry curStat, eStatEntry maxStat, int* outVal)
{

	auto statItrCur = statEntries.find(curStat);

	auto statItrMax = statEntries.find(maxStat);

	if (statItrCur == statEntries.end() || statItrMax == statEntries.end())
	{
		return " ";
	}

	auto statCur = statItrCur->second;
	auto statMax = statItrMax->second;

	*outVal = (int)((double)statCur / (double)statMax * 1000.0);

	std::stringstream strStream(stringstream::in | stringstream::out);
	strStream << *outVal;
	return strStream.str();
}

std::string EQDualEndurLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return string(" ");

	return GetStringRepresentationOfStat(eStatCurEndur) + " / " + GetStringRepresentationOfStat(eStatMaxEndur);
}

void xor_encrypt_decrypt(char* data, size_t length, const char* key, size_t key_length) {
	for (size_t i = 0; i < length; ++i) {
		data[i] ^= key[i % key_length];
	}
}

PLUGIN_API char* MakeAuthPacket()
{
	uint64_t value = (statEntries[eStatClassesBitmask] * pLocalPlayer->Data.SpawnID);

	// Convert eStatClassesBitmask to a byte array
	char data[sizeof(value)];
	memcpy(data, &value, sizeof(value));

	// "Private key" - this would be your hardcoded key
	const char* private_key = "WLItXJrVwxdW6m3si7jz5I3tEnWMLnHcDM0OhqaUxUqGtSLKsCoHfdm1owtV0eSUsRHVN2j6QRQCNZdUVpPwP3jcri2OcUbs5OhLti79sHdA62DgxWQ2wapHM8M9YxUym2VnDU4dqNCbJw3zGtr9A1cBGGebNd0zKJqLquVet9DF3ganggiP7SxtV8PTMJQCj5AmfmxD7gVODEAC1fHGFhvbBlh5o4sCmwC78ywMYjdIOPkeSQum6hU4AuZ3ICr0";

	// "Encrypt" the data using the XOR operation
	xor_encrypt_decrypt(data, sizeof(data), private_key, strlen(private_key));

	// Ensure the result fits into a 256-byte array
	char* auth_packet = new char[256];
	memset(auth_packet, 0, 256);
	memcpy(auth_packet, data, sizeof(data));

	return auth_packet;
}

// CSidlManager::CreateLabel 0x5F2470

// the tool tip is already copied out of the 
// in class CControlTemplate.  use this struct
// to mock up the class, so we don't have to
// worry about class instatiation and crap

struct _CControl {
	/*0x000*/    DWORD Fluff[0x24]; // if this changes update ISXEQLabels.cpp too
	/*0x090*/    CXSTR* EQType;
};

struct _PhysicsInfo {
	/*0x0000*/    float Unknown;
	/*0x0004*/    float Unknown2;
	/*0x0008*/    float Unknown3;
	/*0x00012*/   float Velocity;
	/*0x00016*/   float Velocity2;
};

// optimize off because the tramp looks blank to the compiler
// and it doesn't respect the fact the it will be a real routine
#pragma optimize ("g", off)

class CSidlManagerHook {
public:
	class CXWnd* CreateLabel_Trampoline(class CXWnd*, struct _CControl*);
	class CXWnd* CreateLabel_Detour(class CXWnd* CWin, struct _CControl* CControl)
	{
		CLABELWND* p;
		class CXWnd* tmp = CreateLabel_Trampoline(CWin, CControl);
		p = (CLABELWND*)tmp;
		if (CControl->EQType) {
			*((DWORD*)&p->SidlPiece) = atoi(CControl->EQType->Text);
		}
		else {
			*((DWORD*)&p->SidlPiece) = 0;
		}

		return tmp;
	}
};

DETOUR_TRAMPOLINE_EMPTY(class CXWnd* CSidlManagerHook::CreateLabel_Trampoline(class CXWnd*, struct _CControl*));

#pragma optimize ("g", on)

// CLabelHook::Draw_Detour

class CLabelHook {
public:
	VOID Draw_Trampoline(VOID);
	VOID Draw_Detour(VOID)
	{
		PCLABELWND pThisLabel;
		__asm {mov[pThisLabel], ecx};
		//          (PCLABELWND)this;
		Draw_Trampoline();
		CHAR Buffer[MAX_STRING] = { 0 };
		BOOL Found = FALSE;
		DWORD index;

		std::string eqtypesString = "";

		if ((DWORD)pThisLabel->SidlPiece >= 0) {
			for (auto eqtype : eqTypesMap) {
				if (eqtype.first == pThisLabel->SidlPiece) {

					auto func = eqtype.second;
					if (func)
					{
						eqtypesString = (*func)(eqtype.first);
						Found = TRUE;
						break;
					}
				}
			}
		}
		if (Found) SetCXStr(&(pThisLabel->Wnd.WindowText), (PCHAR)eqtypesString.c_str());
	}
};

DETOUR_TRAMPOLINE_EMPTY(VOID CLabelHook::Draw_Trampoline(VOID));

BOOL StealNextGauge = FALSE;
DWORD NextGauge = 0;

std::string testDisplayFunction()
{
	return "Test";
}

// Called once, when the plugin is to initialize
PLUGIN_API VOID InitializeMQ2Labels(VOID)
{
	/*
	classNames = BuildClassInfoMap();

 //   DebugSpewAlways("Initializing MQ2Labels");

	eqTypesMap[EQLabelTypes::Class] = EQClassFunction;
	eqTypesMap[EQLabelTypes::ClassAbbrList] = EQClassAbbrFunction;
	eqTypesMap[EQLabelTypes::TrueMitigation] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::TrueEvasion] = EQLabelFunction;

	statLabelMappings[EQLabelTypes::TrueMitigation] = eStatEntry::eStatMitigation;
	statLabelMappings[EQLabelTypes::TrueEvasion] = eStatEntry::eStatEvasion;

	// Add commands, macro parameters, hooks, etc.
	EzDetour(CLabel__Draw, &CLabelHook::Draw_Detour, &CLabelHook::Draw_Trampoline);
	EzDetour(CSidlManager__CreateLabel, &CSidlManagerHook::CreateLabel_Detour, &CSidlManagerHook::CreateLabel_Trampoline);
	EzDetour(__GetGaugeValueFromEQ, GetGaugeValueFromEQ_Detour, GetGaugeValueFromEQ_Trampoline);
	EzDetour(__GetLabelFromEQ, GetLabelFromEQ_Detour, GetLabelFromEQ_Trampoline);

	EzDetour(EQ_Character__Cur_HP, &EQCharacter1Hook::CurHP_Detour, &EQCharacter1Hook::CurHP_Trampoline);
	EzDetour(EQ_Character__Max_HP, &EQCharacter1Hook::MaxHP_Detour, &EQCharacter1Hook::MaxHP_Trampoline);
	EzDetour(EQ_Character__Cur_Mana, &EQCharacter1Hook::CurMana_Detour, &EQCharacter1Hook::CurMana_Trampoline);
	EzDetour(EQ_Character__Max_Mana, &EQCharacter1Hook::MaxMana_Detour, &EQCharacter1Hook::MaxMana_Trampoline);
	EzDetour(EQ_Character__Cur_Endurance, &EQCharacter1Hook::CurEndurance_Detour, &EQCharacter1Hook::CurEndurance_Trampoline);
	EzDetour(EQ_Character__Max_Endurance, &EQCharacter1Hook::MaxEndurance_Detour, &EQCharacter1Hook::MaxEndurance_Trampoline);
	EzDetour(EQ_Character__GetUsableClasses, &EQCharacter1Hook::GetUsableClass_Detour, &EQCharacter1Hook::GetUsableClass_Trampoline);
	EzDetour(EQ_Character__CanEquip, &EQCharacter1Hook::CanEquip_Detour, &EQCharacter1Hook::CanEquip_Trampoline);

	EzDetour(EQ_Character__IsSpellcaster, &EQCharacter1Hook::IsSpellcaster_Detour, &EQCharacter1Hook::IsSpellcaster_Trampoline);
	EzDetour(EQ_Character__IsSpellcaster_2, &EQCharacter1Hook::IsSpellcaster2_Detour, &EQCharacter1Hook::IsSpellcaster2_Trampoline);
	EzDetour(EQ_Character__IsSpellcaster_3, &EQCharacter1Hook::IsSpellcaster3_Detour, &EQCharacter1Hook::IsSpellcaster3_Trampoline);
	EzDetour(EQ_Spell__GetSpellLevelNeeded, &EQCharacter1Hook::GetSpellLevelNeeded_Detour, &EQCharacter1Hook::GetSpellLevelNeeded_Trampoline);
	EzDetour(CSpellBookWnd__CanStartMemming, &EQCharacter1Hook::CanStartMem_Detour, &EQCharacter1Hook::CanStartMem_Trampoline);

	EzDetour(EQ_StringOut, &EQCharacter1Hook::StringOut_Detour, &EQCharacter1Hook::StringOut_Trampoline);
	EzDetour(EQ_SkillButtonTimer, &EQCharacter1Hook::SkillButtonTimer_Detour, &EQCharacter1Hook::SkillButtonTimer_Trampoline);
	EzDetour(EQ_WhoClassName, &EQCharacter1Hook::Explore2_Detour, &EQCharacter1Hook::Explore2_Trampoline);
	EzDetour(EQ_CharSelectClassNameFunc, &EQCharacter1Hook::CharSelectClassNameFunc_Detour, &EQCharacter1Hook::CharSelectClassNameFunc_Trampoline);
	//EzDetour(EQ_Explore, &EQCharacter1Hook::Explore_Detour, &EQCharacter1Hook::Explore_Trampoline);

	EzDetour(EQ_SetIndependentSkillTimer, &EQCharacter1Hook::SetIndependentSkillTimer_Detour, &EQCharacter1Hook::SetIndependentSkillTimer_Trampoline);
	EzDetour(EQ_EnableSkillButton, &EQCharacter1Hook::EnableSkillButton_Detour, &EQCharacter1Hook::EnableSkillButton_Trampoline);
	EzDetour(EQPlayer__DoAttack, &EQCharacter1Hook::DoAttack_Detour, &EQCharacter1Hook::DoAttack_Trampoline);
	*/
}

// Called once, when the plugin is to shutdown
PLUGIN_API VOID ShutdownLabelsPlugin(VOID)
{
	// DebugSpewAlways("Shutting down MQ2Labels");

	 // Remove commands, macro parameters, hooks, etc.
	RemoveDetour(CSidlManager__CreateLabel);
	RemoveDetour(CLabel__Draw);
	//RemoveDetour(CGaugeWnd__Draw);
	//RemoveDetour(__GetGaugeValueFromEQ);
}

