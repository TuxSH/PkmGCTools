#include <LibPkmGC/Core/PokemonInfo.h>
#include <LibPkmGC/Core/Detail/StructMacros.h>

namespace LibPkmGC{

void VersionInfo::load(u8 * data) {
	LD_FIELD_E(u8, game, 0, GameIndex);
	LD_FIELD_E(u8, currentRegion, 1, RegionIndex);
	LD_FIELD_E(u8, originalRegion, 2, RegionIndex);
	LD_FIELD_E(u8, language, 3, LanguageIndex);
}

void VersionInfo::save(u8 * data) {
	SV_FIELD_E(u8, game, 0, GameIndex);
	SV_FIELD_E(u8, currentRegion, 1, RegionIndex);
	SV_FIELD_E(u8, originalRegion, 2, RegionIndex);
	SV_FIELD_E(u8, language, 3, LanguageIndex);
}

bool VersionInfo::isIncomplete(void) const {
	return (game == NoGame) || (currentRegion == NoRegion) || (originalRegion == NoRegion) || (language == NoLanguage);
}

void PokemonMove::load(u8 * data) {
	LD_FIELD_E(u16, moveIndex, 0, PokemonMoveIndex);
	LD_FIELD(u8, currentPPs, 2);
	LD_FIELD(u8, nbPPUpsUsed, 3);
}

void PokemonMove::save(u8 * data) {
	SV_FIELD_E(u16, moveIndex, 0, PokemonMoveIndex);
	SV_FIELD(u8, currentPPs, 2);
	SV_FIELD(u8, nbPPUpsUsed, 3);
}

u8 PokemonMove::calculateMaxPP(void) const {
	u32 baseMaxPP = (moveIndex > PsychoBoost) ? 0 : (u32)getBaseMoveMaxPPs(moveIndex);
	return (u8)(baseMaxPP*(100 + (u32)nbPPUpsUsed * 20) / 100);
}

void PokemonMarkings::load(u8 m) {
	circle = (m & 1) != 0;
	square = (m & 2) != 0;
	triangle = (m & 4) != 0;
	heart = (m & 8) != 0;
}

u8 PokemonMarkings::save(void) const {
	u8 m = (u8)(((heart) ? 1 : 0) << 3) | (((triangle) ? 1 : 0) << 2);
	m |= (u8)(((square) ? 1 : 0) << 1) | ((circle) ? 1 : 0);
	return m;
}

u16 getPokedexIndexOf(PokemonSpeciesIndex speciesIndex) {
	static const u16 remaining[] = { 
	290, 291, 292, 276, 277, 285, 286, 327, 278, 279, 283, 284, 320, 321, 300, 301, 352, 343, 344, 299, 324,
	302, 339, 340, 370, 341, 342, 349, 350, 318, 319, 328, 329, 330, 296, 297, 309, 310, 322, 323, 363, 364, 365, 331, 332, 361, 362,
	337, 338, 298, 325, 326, 311, 312, 303, 307, 308, 333, 334, 360, 355, 356, 315, 287, 288, 289, 316, 317, 357, 293, 294, 295, 366,
	367, 368, 359, 353, 354, 336, 335, 369, 304, 305, 306, 351, 313, 314, 345, 346, 347, 348, 280, 281, 282, 371, 372, 373, 374, 375,
	376, 377, 378, 379, 382, 383, 384, 380, 381, 385, 386, 358};

	u16 result = (u16)speciesIndex;
	if (speciesIndex == Bonsly) return 438;
	if (speciesIndex <= Celebi) return result;
	if (speciesIndex < Treecko) return 0;
	if (speciesIndex <= Shiftry) return (result - 25);
	if (speciesIndex <= Chimecho) return remaining[result - 301];
	else return 0;
	
}

PokemonSpeciesIndex getSpeciesIndexOf(u16 pokedexIndex) {
	static const PokemonSpeciesIndex speciesIndexFromPkdxIndexTable[388] = {
		NoSpecies,
		Bulbasaur,
		Ivysaur,
		Venusaur,
		Charmander,
		Charmeleon,
		Charizard,
		Squirtle,
		Wartortle,
		Blastoise,
		Caterpie,
		Metapod,
		Butterfree,
		Weedle,
		Kakuna,
		Beedrill,
		Pidgey,
		Pidgeotto,
		Pidgeot,
		Rattata,
		Raticate,
		Spearow,
		Fearow,
		Ekans,
		Arbok,
		Pikachu,
		Raichu,
		Sandshrew,
		Sandslash,
		NidoranF,
		Nidorina,
		Nidoqueen,
		NidoranM,
		Nidorino,
		Nidoking,
		Clefairy,
		Clefable,
		Vulpix,
		Ninetales,
		Jigglypuff,
		Wigglytuff,
		Zubat,
		Golbat,
		Oddish,
		Gloom,
		Vileplume,
		Paras,
		Parasect,
		Venonat,
		Venomoth,
		Diglett,
		Dugtrio,
		Meowth,
		Persian,
		Psyduck,
		Golduck,
		Mankey,
		Primeape,
		Growlithe,
		Arcanine,
		Poliwag,
		Poliwhirl,
		Poliwrath,
		Abra,
		Kadabra,
		Alakazam,
		Machop,
		Machoke,
		Machamp,
		Bellsprout,
		Weepinbell,
		Victreebel,
		Tentacool,
		Tentacruel,
		Geodude,
		Graveler,
		Golem,
		Ponyta,
		Rapidash,
		Slowpoke,
		Slowbro,
		Magnemite,
		Magneton,
		Farfetch_d,
		Doduo,
		Dodrio,
		Seel,
		Dewgong,
		Grimer,
		Muk,
		Shellder,
		Cloyster,
		Gastly,
		Haunter,
		Gengar,
		Onix,
		Drowzee,
		Hypno,
		Krabby,
		Kingler,
		Voltorb,
		Electrode,
		Exeggcute,
		Exeggutor,
		Cubone,
		Marowak,
		Hitmonlee,
		Hitmonchan,
		Lickitung,
		Koffing,
		Weezing,
		Rhyhorn,
		Rhydon,
		Chansey,
		Tangela,
		Kangaskhan,
		Horsea,
		Seadra,
		Goldeen,
		Seaking,
		Staryu,
		Starmie,
		MrMime,
		Scyther,
		Jynx,
		Electabuzz,
		Magmar,
		Pinsir,
		Tauros,
		Magikarp,
		Gyarados,
		Lapras,
		Ditto,
		Eevee,
		Vaporeon,
		Jolteon,
		Flareon,
		Porygon,
		Omanyte,
		Omastar,
		Kabuto,
		Kabutops,
		Aerodactyl,
		Snorlax,
		Articuno,
		Zapdos,
		Moltres,
		Dratini,
		Dragonair,
		Dragonite,
		Mewtwo,
		Mew,
		Chikorita,
		Bayleef,
		Meganium,
		Cyndaquil,
		Quilava,
		Typhlosion,
		Totodile,
		Croconaw,
		Feraligatr,
		Sentret,
		Furret,
		Hoothoot,
		Noctowl,
		Ledyba,
		Ledian,
		Spinarak,
		Ariados,
		Crobat,
		Chinchou,
		Lanturn,
		Pichu,
		Cleffa,
		Igglybuff,
		Togepi,
		Togetic,
		Natu,
		Xatu,
		Mareep,
		Flaaffy,
		Ampharos,
		Bellossom,
		Marill,
		Azumarill,
		Sudowoodo,
		Politoed,
		Hoppip,
		Skiploom,
		Jumpluff,
		Aipom,
		Sunkern,
		Sunflora,
		Yanma,
		Wooper,
		Quagsire,
		Espeon,
		Umbreon,
		Murkrow,
		Slowking,
		Misdreavus,
		Unown,
		Wobbuffet,
		Girafarig,
		Pineco,
		Forretress,
		Dunsparce,
		Gligar,
		Steelix,
		Snubbull,
		Granbull,
		Qwilfish,
		Scizor,
		Shuckle,
		Heracross,
		Sneasel,
		Teddiursa,
		Ursaring,
		Slugma,
		Magcargo,
		Swinub,
		Piloswine,
		Corsola,
		Remoraid,
		Octillery,
		Delibird,
		Mantine,
		Skarmory,
		Houndour,
		Houndoom,
		Kingdra,
		Phanpy,
		Donphan,
		Porygon2,
		Stantler,
		Smeargle,
		Tyrogue,
		Hitmontop,
		Smoochum,
		Elekid,
		Magby,
		Miltank,
		Blissey,
		Raikou,
		Entei,
		Suicune,
		Larvitar,
		Pupitar,
		Tyranitar,
		Lugia,
		HoOh,
		Celebi,
		Treecko,
		Grovyle,
		Sceptile,
		Torchic,
		Combusken,
		Blaziken,
		Mudkip,
		Marshtomp,
		Swampert,
		Poochyena,
		Mightyena,
		Zigzagoon,
		Linoone,
		Wurmple,
		Silcoon,
		Beautifly,
		Cascoon,
		Dustox,
		Lotad,
		Lombre,
		Ludicolo,
		Seedot,
		Nuzleaf,
		Shiftry,
		Taillow,
		Swellow,
		Wingull,
		Pelipper,
		Ralts,
		Kirlia,
		Gardevoir,
		Surskit,
		Masquerain,
		Shroomish,
		Breloom,
		Slakoth,
		Vigoroth,
		Slaking,
		Nincada,
		Ninjask,
		Shedinja,
		Whismur,
		Loudred,
		Exploud,
		Makuhita,
		Hariyama,
		Azurill,
		Nosepass,
		Skitty,
		Delcatty,
		Sableye,
		Mawile,
		Aron,
		Lairon,
		Aggron,
		Meditite,
		Medicham,
		Electrike,
		Manectric,
		Plusle,
		Minun,
		Volbeat,
		Illumise,
		Roselia,
		Gulpin,
		Swalot,
		Carvanha,
		Sharpedo,
		Wailmer,
		Wailord,
		Numel,
		Camerupt,
		Torkoal,
		Spoink,
		Grumpig,
		Spinda,
		Trapinch,
		Vibrava,
		Flygon,
		Cacnea,
		Cacturne,
		Swablu,
		Altaria,
		Zangoose,
		Seviper,
		Lunatone,
		Solrock,
		Barboach,
		Whiscash,
		Corphish,
		Crawdaunt,
		Baltoy,
		Claydol,
		Lileep,
		Cradily,
		Anorith,
		Armaldo,
		Feebas,
		Milotic,
		Castform,
		Kecleon,
		Shuppet,
		Banette,
		Duskull,
		Dusclops,
		Tropius,
		Chimecho,
		Absol,
		Wynaut,
		Snorunt,
		Glalie,
		Spheal,
		Sealeo,
		Walrein,
		Clamperl,
		Huntail,
		Gorebyss,
		Relicanth,
		Luvdisc,
		Bagon,
		Shelgon,
		Salamence,
		Beldum,
		Metang,
		Metagross,
		Regirock,
		Regice,
		Registeel,
		Latias,
		Latios,
		Kyogre,
		Groudon,
		Rayquaza,
		Jirachi,
		Deoxys,
	};
	if (pokedexIndex == 438) return Bonsly;
	if (pokedexIndex > 387) return NoSpecies;
	return speciesIndexFromPkdxIndexTable[(size_t)pokedexIndex];
}


const u8 baseMoveMaxPPs[355] = {
	0,
	35,
	25,
	10,
	15,
	20,
	20,
	15,
	15,
	15,
	35,
	30,
	5,
	10,
	30,
	30,
	35,
	35,
	20,
	15,
	20,
	20,
	10,
	20,
	30,
	5,
	25,
	15,
	15,
	15,
	25,
	20,
	5,
	35,
	15,
	20,
	20,
	20,
	15,
	30,
	35,
	20,
	20,
	30,
	25,
	40,
	20,
	15,
	20,
	20,
	20,
	30,
	25,
	15,
	30,
	25,
	5,
	15,
	10,
	5,
	20,
	20,
	20,
	5,
	35,
	20,
	25,
	20,
	20,
	20,
	15,
	20,
	10,
	10,
	40,
	25,
	10,
	35,
	30,
	15,
	20,
	40,
	10,
	15,
	30,
	15,
	20,
	10,
	15,
	10,
	5,
	10,
	10,
	25,
	10,
	20,
	40,
	30,
	30,
	20,
	20,
	15,
	10,
	40,
	15,
	20,
	30,
	20,
	20,
	10,
	40,
	40,
	30,
	30,
	30,
	20,
	30,
	10,
	10,
	20,
	5,
	10,
	30,
	20,
	20,
	20,
	5,
	15,
	10,
	20,
	15,
	15,
	35,
	20,
	15,
	10,
	20,
	30,
	15,
	40,
	20,
	15,
	10,
	5,
	10,
	30,
	10,
	15,
	20,
	15,
	40,
	40,
	10,
	5,
	15,
	10,
	10,
	10,
	15,
	30,
	30,
	10,
	10,
	20,
	10,
	1,
	1,
	10,
	10,
	10,
	5,
	15,
	25,
	15,
	10,
	15,
	30,
	5,
	40,
	15,
	10,
	25,
	10,
	30,
	10,
	20,
	10,
	10,
	10,
	10,
	10,
	20,
	5,
	40,
	5,
	5,
	15,
	5,
	10,
	5,
	15,
	10,
	5,
	10,
	20,
	20,
	40,
	15,
	10,
	20,
	20,
	25,
	5,
	15,
	10,
	5,
	20,
	15,
	20,
	25,
	20,
	5,
	30,
	5,
	10,
	20,
	40,
	5,
	20,
	40,
	20,
	15,
	35,
	10,
	5,
	5,
	5,
	15,
	5,
	20,
	5,
	5,
	15,
	20,
	10,
	5,
	5,
	15,
	15,
	15,
	15,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	15,
	15,
	15,
	10,
	20,
	20,
	10,
	20,
	20,
	20,
	20,
	20,
	10,
	10,
	10,
	20,
	20,
	5,
	15,
	10,
	10,
	15,
	10,
	20,
	5,
	5,
	10,
	10,
	20,
	5,
	10,
	20,
	10,
	20,
	20,
	20,
	5,
	5,
	15,
	20,
	10,
	15,
	20,
	15,
	10,
	10,
	15,
	10,
	5,
	5,
	10,
	15,
	10,
	5,
	20,
	25,
	5,
	40,
	10,
	5,
	40,
	15,
	20,
	20,
	5,
	15,
	20,
	30,
	15,
	15,
	5,
	10,
	30,
	20,
	30,
	15,
	5,
	40,
	15,
	5,
	20,
	5,
	15,
	25,
	40,
	15,
	20,
	15,
	20,
	15,
	20,
	10,
	20,
	20,
	5,
	5
};

LIBPKMGC_DECL const  u32 expTables[6][101] = {
	{
		0,
		1,
		8,
		27,
		64,
		125,
		216,
		343,
		512,
		729,
		1000,
		1331,
		1728,
		2197,
		2744,
		3375,
		4096,
		4913,
		5832,
		6859,
		8000,
		9261,
		10648,
		12167,
		13824,
		15625,
		17576,
		19683,
		21952,
		24389,
		27000,
		29791,
		32768,
		35937,
		39304,
		42875,
		46656,
		50653,
		54872,
		59319,
		64000,
		68921,
		74088,
		79507,
		85184,
		91125,
		97336,
		103823,
		110592,
		117649,
		125000,
		132651,
		140608,
		148877,
		157464,
		166375,
		175616,
		185193,
		195112,
		205379,
		216000,
		226981,
		238328,
		250047,
		262144,
		274625,
		287496,
		300763,
		314432,
		328509,
		343000,
		357911,
		373248,
		389017,
		405224,
		421875,
		438976,
		456533,
		474552,
		493039,
		512000,
		531441,
		551368,
		571787,
		592704,
		614125,
		636056,
		658503,
		681472,
		704969,
		729000,
		753571,
		778688,
		804357,
		830584,
		857375,
		884736,
		912673,
		941192,
		970299,
		1000000,
	},
	{
		0,
		1,
		15,
		52,
		122,
		237,
		406,
		637,
		942,
		1326,
		1800,
		2369,
		3041,
		3822,
		4719,
		5737,
		6881,
		8155,
		9564,
		11111,
		12800,
		14632,
		16610,
		18737,
		21012,
		23437,
		26012,
		28737,
		31610,
		34632,
		37800,
		41111,
		44564,
		48155,
		51881,
		55737,
		59719,
		63822,
		68041,
		72369,
		76800,
		81326,
		85942,
		90637,
		95406,
		100237,
		105122,
		110052,
		115015,
		120001,
		125000,
		131324,
		137795,
		144410,
		151165,
		158056,
		165079,
		172229,
		179503,
		186894,
		194400,
		202013,
		209728,
		217540,
		225443,
		233431,
		241496,
		249633,
		257834,
		267406,
		276458,
		286328,
		296358,
		305767,
		316074,
		326531,
		336255,
		346965,
		357812,
		367807,
		378880,
		390077,
		400293,
		411686,
		423190,
		433572,
		445239,
		457001,
		467489,
		479378,
		491346,
		501878,
		513934,
		526049,
		536557,
		548720,
		560922,
		571333,
		583539,
		591882,
		600000,
	},
	{
		0,
		1,
		4,
		13,
		32,
		65,
		112,
		178,
		276,
		393,
		540,
		745,
		967,
		1230,
		1591,
		1957,
		2457,
		3046,
		3732,
		4526,
		5440,
		6482,
		7666,
		9003,
		10506,
		12187,
		14060,
		16140,
		18439,
		20974,
		23760,
		26811,
		30146,
		33780,
		37731,
		42017,
		46656,
		50653,
		55969,
		60505,
		66560,
		71677,
		78533,
		84277,
		91998,
		98415,
		107069,
		114205,
		123863,
		131766,
		142500,
		151222,
		163105,
		172697,
		185807,
		196322,
		210739,
		222231,
		238036,
		250562,
		267840,
		281456,
		300293,
		315059,
		335544,
		351520,
		373744,
		390991,
		415050,
		433631,
		459620,
		479600,
		507617,
		529063,
		559209,
		582187,
		614566,
		639146,
		673863,
		700115,
		737280,
		765275,
		804997,
		834809,
		877201,
		908905,
		954084,
		987754,
		1035837,
		1071552,
		1122660,
		1160499,
		1214753,
		1254796,
		1312322,
		1354652,
		1415577,
		1460276,
		1524731,
		1571884,
		1640000,
	},
	{
		0,
		1,
		9,
		57,
		96,
		135,
		179,
		236,
		314,
		419,
		560,
		742,
		973,
		1261,
		1612,
		2035,
		2535,
		3120,
		3798,
		4575,
		5460,
		6458,
		7577,
		8825,
		10208,
		11735,
		13411,
		15244,
		17242,
		19411,
		21760,
		24294,
		27021,
		29949,
		33084,
		36435,
		40007,
		43808,
		47846,
		52127,
		56660,
		61450,
		66505,
		71833,
		77440,
		83335,
		89523,
		96012,
		102810,
		109923,
		117360,
		125126,
		133229,
		141677,
		150476,
		159635,
		169159,
		179056,
		189334,
		199999,
		211060,
		222522,
		234393,
		246681,
		259392,
		272535,
		286115,
		300140,
		314618,
		329555,
		344960,
		360838,
		377197,
		394045,
		411388,
		429235,
		447591,
		466464,
		485862,
		505791,
		526260,
		547274,
		568841,
		590969,
		613664,
		636935,
		660787,
		685228,
		710266,
		735907,
		762160,
		789030,
		816525,
		844653,
		873420,
		902835,
		932903,
		963632,
		995030,
		1027103,
		1059860,
	},
	{
		0,
		1,
		6,
		21,
		51,
		100,
		172,
		274,
		409,
		583,
		800,
		1064,
		1382,
		1757,
		2195,
		2700,
		3276,
		3930,
		4665,
		5487,
		6400,
		7408,
		8518,
		9733,
		11059,
		12500,
		14060,
		15746,
		17561,
		19511,
		21600,
		23832,
		26214,
		28749,
		31443,
		34300,
		37324,
		40522,
		43897,
		47455,
		51200,
		55136,
		59270,
		63605,
		68147,
		72900,
		77868,
		83058,
		88473,
		94119,
		100000,
		106120,
		112486,
		119101,
		125971,
		133100,
		140492,
		148154,
		156089,
		164303,
		172800,
		181584,
		190662,
		200037,
		209715,
		219700,
		229996,
		240610,
		251545,
		262807,
		274400,
		286328,
		298598,
		311213,
		324179,
		337500,
		351180,
		365226,
		379641,
		394431,
		409600,
		425152,
		441094,
		457429,
		474163,
		491300,
		508844,
		526802,
		545177,
		563975,
		583200,
		602856,
		622950,
		643485,
		664467,
		685900,
		707788,
		730138,
		752953,
		776239,
		800000,
	},
	{
		0,
		1,
		10,
		33,
		80,
		156,
		270,
		428,
		640,
		911,
		1250,
		1663,
		2160,
		2746,
		3430,
		4218,
		5120,
		6141,
		7290,
		8573,
		10000,
		11576,
		13310,
		15208,
		17280,
		19531,
		21970,
		24603,
		27440,
		30486,
		33750,
		37238,
		40960,
		44921,
		49130,
		53593,
		58320,
		63316,
		68590,
		74148,
		80000,
		86151,
		92610,
		99383,
		106480,
		113906,
		121670,
		129778,
		138240,
		147061,
		156250,
		165813,
		175760,
		186096,
		196830,
		207968,
		219520,
		231491,
		243890,
		256723,
		270000,
		283726,
		297910,
		312558,
		327680,
		343281,
		359370,
		375953,
		393040,
		410636,
		428750,
		447388,
		466560,
		486271,
		506530,
		527343,
		548720,
		570666,
		593190,
		616298,
		640000,
		664301,
		689210,
		714733,
		740880,
		767656,
		795070,
		823128,
		851840,
		881211,
		911250,
		941963,
		973360,
		1005446,
		1038230,
		1071718,
		1105920,
		1140841,
		1176490,
		1212873,
		1250000,
	},
};

const PokemonNatureAffinity natureStatAffinities[25][5] = {
	{Neutral, Neutral, Neutral, Neutral, Neutral},
	{Beneficial, Detrimental, Neutral, Neutral, Neutral},
	{Beneficial, Neutral, Neutral, Neutral, Detrimental},
	{Beneficial, Neutral, Detrimental, Neutral, Neutral},
	{Beneficial, Neutral, Neutral, Detrimental, Neutral},
	{Detrimental, Beneficial, Neutral, Neutral, Neutral},
	{Neutral, Neutral, Neutral, Neutral, Neutral},
	{Neutral, Beneficial, Neutral, Neutral, Detrimental},
	{Neutral, Beneficial, Detrimental, Neutral, Neutral},
	{Neutral, Beneficial, Neutral, Detrimental, Neutral},
	{Detrimental, Neutral, Neutral, Neutral, Beneficial},
	{Neutral, Detrimental, Neutral, Neutral, Beneficial},
	{Neutral, Neutral, Neutral, Neutral, Neutral},
	{Neutral, Neutral, Detrimental, Neutral, Beneficial},
	{Neutral, Neutral, Neutral, Detrimental, Beneficial},
	{Detrimental, Neutral, Beneficial, Neutral, Neutral},
	{Neutral, Detrimental, Beneficial, Neutral, Neutral},
	{Neutral, Neutral, Beneficial, Neutral, Detrimental},
	{Neutral, Neutral, Neutral, Neutral, Neutral},
	{Neutral, Neutral, Beneficial, Detrimental, Neutral},
	{Detrimental, Neutral, Neutral, Beneficial, Neutral},
	{Neutral, Detrimental, Neutral, Beneficial, Neutral},
	{Neutral, Neutral, Neutral, Beneficial, Detrimental},
	{Neutral, Neutral, Detrimental, Beneficial, Neutral},
	{Neutral, Neutral, Neutral, Neutral, Neutral},
};

LIBPKMGC_DECL const PokemonSpeciesData speciesData[0x19f]= {
	{
		// NoAbility
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		// Bulbasaur
		true,
		MediumSlow,
		M7F1,
		70,
		{Overgrow, NoAbility},
		{45, 49, 49, 65, 65, 45},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Ivysaur
		true,
		MediumSlow,
		M7F1,
		70,
		{Overgrow, NoAbility},
		{60, 62, 63, 80, 80, 60},
		{0, 0, 0, 1, 1, 0}
	},
	{
		// Venusaur
		true,
		MediumSlow,
		M7F1,
		70,
		{Overgrow, NoAbility},
		{80, 82, 83, 100, 100, 80},
		{0, 0, 0, 2, 1, 0}
	},
	{
		// Charmander
		true,
		MediumSlow,
		M7F1,
		70,
		{Blaze, NoAbility},
		{39, 52, 43, 60, 50, 65},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Charmeleon
		true,
		MediumSlow,
		M7F1,
		70,
		{Blaze, NoAbility},
		{58, 64, 58, 80, 65, 80},
		{0, 0, 0, 1, 0, 1}
	},
	{
		// Charizard
		true,
		MediumSlow,
		M7F1,
		70,
		{Blaze, NoAbility},
		{78, 84, 78, 109, 85, 100},
		{0, 0, 0, 3, 0, 0}
	},
	{
		// Squirtle
		true,
		MediumSlow,
		M7F1,
		70,
		{Torrent, NoAbility},
		{44, 48, 65, 50, 64, 43},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Wartortle
		true,
		MediumSlow,
		M7F1,
		70,
		{Torrent, NoAbility},
		{59, 63, 80, 65, 80, 58},
		{0, 0, 1, 0, 1, 0}
	},
	{
		// Blastoise
		true,
		MediumSlow,
		M7F1,
		70,
		{Torrent, NoAbility},
		{79, 83, 100, 85, 105, 78},
		{0, 0, 0, 0, 3, 0}
	},
	{
		// Caterpie
		true,
		MediumFast,
		M1F1,
		70,
		{ShieldDust, NoAbility},
		{45, 30, 35, 20, 20, 45},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Metapod
		true,
		MediumFast,
		M1F1,
		70,
		{ShedSkin, NoAbility},
		{50, 20, 55, 25, 25, 30},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Butterfree
		true,
		MediumFast,
		M1F1,
		70,
		{Compoundeyes, NoAbility},
		{60, 45, 50, 80, 80, 70},
		{0, 0, 0, 2, 1, 0}
	},
	{
		// Weedle
		true,
		MediumFast,
		M1F1,
		70,
		{ShieldDust, NoAbility},
		{40, 35, 30, 20, 20, 50},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Kakuna
		true,
		MediumFast,
		M1F1,
		70,
		{ShedSkin, NoAbility},
		{45, 25, 50, 25, 25, 35},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Beedrill
		true,
		MediumFast,
		M1F1,
		70,
		{Swarm, NoAbility},
		{65, 80, 40, 45, 80, 75},
		{0, 2, 0, 0, 1, 0}
	},
	{
		// Pidgey
		true,
		MediumSlow,
		M1F1,
		70,
		{KeenEye, NoAbility},
		{40, 45, 40, 35, 35, 56},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Pidgeotto
		true,
		MediumSlow,
		M1F1,
		70,
		{KeenEye, NoAbility},
		{63, 60, 55, 50, 50, 71},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Pidgeot
		true,
		MediumSlow,
		M1F1,
		70,
		{KeenEye, NoAbility},
		{83, 80, 75, 70, 70, 91},
		{0, 0, 0, 0, 0, 3}
	},
	{
		// Rattata
		true,
		MediumFast,
		M1F1,
		70,
		{RunAway, Guts},
		{30, 56, 35, 25, 35, 72},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Raticate
		true,
		MediumFast,
		M1F1,
		70,
		{RunAway, Guts},
		{55, 81, 60, 50, 70, 97},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Spearow
		true,
		MediumFast,
		M1F1,
		70,
		{KeenEye, NoAbility},
		{40, 60, 30, 31, 31, 70},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Fearow
		true,
		MediumFast,
		M1F1,
		70,
		{KeenEye, NoAbility},
		{65, 90, 65, 61, 61, 100},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Ekans
		true,
		MediumFast,
		M1F1,
		70,
		{Intimidate, ShedSkin},
		{35, 60, 44, 40, 54, 55},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Arbok
		true,
		MediumFast,
		M1F1,
		70,
		{Intimidate, ShedSkin},
		{60, 85, 69, 65, 79, 80},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Pikachu
		true,
		MediumFast,
		M1F1,
		70,
		{Static, NoAbility},
		{35, 55, 30, 50, 40, 90},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Raichu
		true,
		MediumFast,
		M1F1,
		70,
		{Static, NoAbility},
		{60, 90, 55, 90, 80, 100},
		{0, 0, 0, 0, 0, 3}
	},
	{
		// Sandshrew
		true,
		MediumFast,
		M1F1,
		70,
		{SandVeil, NoAbility},
		{50, 75, 85, 20, 30, 40},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Sandslash
		true,
		MediumFast,
		M1F1,
		70,
		{SandVeil, NoAbility},
		{75, 100, 110, 45, 55, 65},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Nidoran (F)
		true,
		MediumSlow,
		FemaleOnly,
		70,
		{PoisonPoint, NoAbility},
		{55, 47, 52, 40, 40, 41},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Nidorina
		true,
		MediumSlow,
		FemaleOnly,
		70,
		{PoisonPoint, NoAbility},
		{70, 62, 67, 55, 55, 56},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Nidoqueen
		true,
		MediumSlow,
		FemaleOnly,
		70,
		{PoisonPoint, NoAbility},
		{90, 82, 87, 75, 85, 76},
		{3, 0, 0, 0, 0, 0}
	},
	{
		// Nidoran (M)
		true,
		MediumSlow,
		MaleOnly,
		70,
		{PoisonPoint, NoAbility},
		{46, 57, 40, 40, 40, 50},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Nidorino
		true,
		MediumSlow,
		MaleOnly,
		70,
		{PoisonPoint, NoAbility},
		{61, 72, 57, 55, 55, 65},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Nidoking
		true,
		MediumSlow,
		MaleOnly,
		70,
		{PoisonPoint, NoAbility},
		{81, 92, 77, 85, 75, 85},
		{0, 3, 0, 0, 0, 0}
	},
	{
		// Clefairy
		true,
		Fast,
		M3F1,
		140,
		{CuteCharm, NoAbility},
		{70, 45, 48, 60, 65, 35},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Clefable
		true,
		Fast,
		M3F1,
		140,
		{CuteCharm, NoAbility},
		{95, 70, 73, 85, 90, 60},
		{3, 0, 0, 0, 0, 0}
	},
	{
		// Vulpix
		true,
		MediumFast,
		M3F1,
		70,
		{FlashFire, NoAbility},
		{38, 41, 40, 50, 65, 65},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Ninetails
		true,
		MediumFast,
		M3F1,
		70,
		{FlashFire, NoAbility},
		{73, 76, 75, 81, 100, 100},
		{0, 0, 0, 0, 1, 1}
	},
	{
		// Jigglypuff
		true,
		Fast,
		M3F1,
		70,
		{CuteCharm, NoAbility},
		{115, 45, 20, 45, 25, 20},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Wigglytuff
		true,
		Fast,
		M3F1,
		70,
		{CuteCharm, NoAbility},
		{140, 70, 45, 75, 50, 45},
		{3, 0, 0, 0, 0, 0}
	},
	{
		// Zubat
		true,
		MediumFast,
		M1F1,
		70,
		{InnerFocus, NoAbility},
		{40, 45, 35, 30, 40, 55},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Golbat
		true,
		MediumFast,
		M1F1,
		70,
		{InnerFocus, NoAbility},
		{75, 80, 70, 65, 75, 90},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Oddish
		true,
		MediumSlow,
		M1F1,
		70,
		{Chlorophyll, NoAbility},
		{45, 50, 55, 75, 65, 30},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Gloom
		true,
		MediumSlow,
		M1F1,
		70,
		{Chlorophyll, NoAbility},
		{60, 65, 70, 85, 75, 40},
		{0, 0, 0, 2, 0, 0}
	},
	{
		// Vileplume
		true,
		MediumSlow,
		M1F1,
		70,
		{Chlorophyll, NoAbility},
		{75, 80, 85, 100, 90, 50},
		{0, 0, 0, 3, 0, 0}
	},
	{
		// Paras
		true,
		MediumFast,
		M1F1,
		70,
		{EffectSpore, NoAbility},
		{35, 70, 55, 45, 55, 25},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Parasect
		true,
		MediumFast,
		M1F1,
		70,
		{EffectSpore, NoAbility},
		{60, 95, 80, 60, 80, 30},
		{0, 2, 1, 0, 0, 0}
	},
	{
		// Venonat
		true,
		MediumFast,
		M1F1,
		70,
		{Compoundeyes, NoAbility},
		{60, 55, 50, 40, 55, 45},
		{0, 0, 0, 0, 1, 0}
	},
	{
		// Venomoth
		true,
		MediumFast,
		M1F1,
		70,
		{ShieldDust, NoAbility},
		{70, 65, 60, 90, 75, 90},
		{0, 0, 0, 1, 0, 1}
	},
	{
		// Diglett
		true,
		MediumFast,
		M1F1,
		70,
		{SandVeil, ArenaTrap},
		{10, 55, 25, 35, 45, 95},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Dugtrio
		true,
		MediumFast,
		M1F1,
		70,
		{SandVeil, ArenaTrap},
		{35, 80, 50, 50, 70, 120},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Meowth
		true,
		MediumFast,
		M1F1,
		70,
		{Pickup, NoAbility},
		{40, 45, 35, 40, 40, 90},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Persian
		true,
		MediumFast,
		M1F1,
		70,
		{Limber, NoAbility},
		{65, 70, 60, 65, 65, 115},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Psyduck
		true,
		MediumFast,
		M1F1,
		70,
		{Damp, CloudNine},
		{50, 52, 48, 65, 50, 55},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Golduck
		true,
		MediumFast,
		M1F1,
		70,
		{Damp, CloudNine},
		{80, 82, 78, 95, 80, 85},
		{0, 0, 0, 2, 0, 0}
	},
	{
		// Mankey
		true,
		MediumFast,
		M1F1,
		70,
		{VitalSpirit, NoAbility},
		{40, 80, 35, 35, 45, 70},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Primeape
		true,
		MediumFast,
		M1F1,
		70,
		{VitalSpirit, NoAbility},
		{65, 105, 60, 60, 70, 95},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Growlithe
		true,
		Slow,
		M1F3,
		70,
		{Intimidate, FlashFire},
		{55, 70, 45, 70, 50, 60},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Arcanine
		true,
		Slow,
		M1F3,
		70,
		{Intimidate, FlashFire},
		{90, 110, 80, 100, 80, 95},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Poliwag
		true,
		MediumSlow,
		M1F1,
		70,
		{WaterAbsorb, Damp},
		{40, 50, 40, 40, 40, 90},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Poliwhirl
		true,
		MediumSlow,
		M1F1,
		70,
		{WaterAbsorb, Damp},
		{65, 65, 65, 50, 50, 90},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Poliwrath
		true,
		MediumSlow,
		M1F1,
		70,
		{WaterAbsorb, Damp},
		{90, 85, 95, 70, 90, 70},
		{0, 0, 3, 0, 0, 0}
	},
	{
		// Abra
		true,
		MediumSlow,
		M1F3,
		70,
		{Synchronize, InnerFocus},
		{25, 20, 15, 105, 55, 90},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Kadabra
		true,
		MediumSlow,
		M1F3,
		70,
		{Synchronize, InnerFocus},
		{40, 35, 30, 120, 70, 105},
		{0, 0, 0, 2, 0, 0}
	},
	{
		// Alakazam
		true,
		MediumSlow,
		M1F3,
		70,
		{Synchronize, InnerFocus},
		{55, 50, 45, 135, 85, 120},
		{0, 0, 0, 3, 0, 0}
	},
	{
		// Machop
		true,
		MediumSlow,
		M1F3,
		70,
		{Guts, NoAbility},
		{70, 80, 50, 35, 35, 35},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Machoke
		true,
		MediumSlow,
		M1F3,
		70,
		{Guts, NoAbility},
		{80, 100, 70, 50, 60, 45},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Machamp
		true,
		MediumSlow,
		M1F3,
		70,
		{Guts, NoAbility},
		{90, 130, 80, 65, 85, 55},
		{0, 3, 0, 0, 0, 0}
	},
	{
		// Bellsprout
		true,
		MediumSlow,
		M1F1,
		70,
		{Chlorophyll, NoAbility},
		{50, 75, 35, 70, 30, 40},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Weepinbell
		true,
		MediumSlow,
		M1F1,
		70,
		{Chlorophyll, NoAbility},
		{65, 90, 50, 85, 45, 55},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Victreebell
		true,
		MediumSlow,
		M1F1,
		70,
		{Chlorophyll, NoAbility},
		{80, 105, 65, 100, 60, 70},
		{0, 3, 0, 0, 0, 0}
	},
	{
		// Tentacool
		true,
		Slow,
		M1F1,
		70,
		{ClearBody, LiquidOoze},
		{40, 40, 35, 50, 100, 70},
		{0, 0, 0, 0, 1, 0}
	},
	{
		// Tentacruel
		true,
		Slow,
		M1F1,
		70,
		{ClearBody, LiquidOoze},
		{80, 70, 65, 80, 120, 100},
		{0, 0, 0, 0, 2, 0}
	},
	{
		// Geodude
		true,
		MediumSlow,
		M1F1,
		70,
		{RockHead, Sturdy},
		{40, 80, 100, 30, 30, 20},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Graveler
		true,
		MediumSlow,
		M1F1,
		70,
		{RockHead, Sturdy},
		{55, 95, 115, 45, 45, 35},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Golem
		true,
		MediumSlow,
		M1F1,
		70,
		{RockHead, Sturdy},
		{80, 110, 130, 55, 65, 45},
		{0, 0, 3, 0, 0, 0}
	},
	{
		// Ponyta
		true,
		MediumFast,
		M1F1,
		70,
		{RunAway, FlashFire},
		{50, 85, 55, 65, 65, 90},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Rapidash
		true,
		MediumFast,
		M1F1,
		70,
		{RunAway, FlashFire},
		{65, 100, 70, 80, 80, 105},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Slowpoke
		true,
		MediumFast,
		M1F1,
		70,
		{Oblivious, OwnTempo},
		{90, 65, 65, 40, 40, 15},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Slowbro
		true,
		MediumFast,
		M1F1,
		70,
		{Oblivious, OwnTempo},
		{95, 75, 110, 100, 80, 30},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Magnemite
		true,
		MediumFast,
		GenderlessOnly,
		70,
		{MagnetPull, Sturdy},
		{25, 35, 70, 95, 55, 45},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Magneton
		true,
		MediumFast,
		GenderlessOnly,
		70,
		{MagnetPull, Sturdy},
		{50, 60, 95, 120, 70, 70},
		{0, 0, 0, 2, 0, 0}
	},
	{
		// Farfetch'd
		true,
		MediumFast,
		M1F1,
		70,
		{KeenEye, InnerFocus},
		{52, 65, 55, 58, 62, 60},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Doduo
		true,
		MediumFast,
		M1F1,
		70,
		{RunAway, EarlyBird},
		{35, 85, 45, 35, 35, 75},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Dodrio
		true,
		MediumFast,
		M1F1,
		70,
		{RunAway, EarlyBird},
		{60, 110, 70, 60, 60, 100},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Seel
		true,
		MediumFast,
		M1F1,
		70,
		{ThickFat, NoAbility},
		{65, 45, 55, 45, 70, 45},
		{0, 0, 0, 0, 1, 0}
	},
	{
		// Dewgong
		true,
		MediumFast,
		M1F1,
		70,
		{ThickFat, NoAbility},
		{90, 70, 80, 70, 95, 70},
		{0, 0, 0, 0, 2, 0}
	},
	{
		// Grimer
		true,
		MediumFast,
		M1F1,
		70,
		{Stench, StickyHold},
		{80, 80, 50, 40, 50, 25},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Muk
		true,
		MediumFast,
		M1F1,
		70,
		{Stench, StickyHold},
		{105, 105, 75, 65, 100, 50},
		{1, 1, 0, 0, 0, 0}
	},
	{
		// Shellder
		true,
		Slow,
		M1F1,
		70,
		{ShellArmor, NoAbility},
		{30, 65, 100, 45, 25, 40},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Cloyster
		true,
		Slow,
		M1F1,
		70,
		{ShellArmor, NoAbility},
		{50, 95, 180, 85, 45, 70},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Gastly
		true,
		MediumSlow,
		M1F1,
		70,
		{Levitate, NoAbility},
		{30, 35, 30, 100, 35, 80},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Haunter
		true,
		MediumSlow,
		M1F1,
		70,
		{Levitate, NoAbility},
		{45, 50, 45, 115, 55, 95},
		{0, 0, 0, 2, 0, 0}
	},
	{
		// Gengar
		true,
		MediumSlow,
		M1F1,
		70,
		{Levitate, NoAbility},
		{60, 65, 60, 130, 75, 110},
		{0, 0, 0, 3, 0, 0}
	},
	{
		// Onix
		true,
		MediumFast,
		M1F1,
		70,
		{RockHead, Sturdy},
		{35, 45, 160, 30, 45, 70},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Drowzee
		true,
		MediumFast,
		M1F1,
		70,
		{Insomnia, NoAbility},
		{60, 48, 45, 43, 90, 42},
		{0, 0, 0, 0, 1, 0}
	},
	{
		// Hypno
		true,
		MediumFast,
		M1F1,
		70,
		{Insomnia, NoAbility},
		{85, 73, 70, 73, 115, 67},
		{0, 0, 0, 0, 2, 0}
	},
	{
		// Krabby
		true,
		MediumFast,
		M1F1,
		70,
		{HyperCutter, ShellArmor},
		{30, 105, 90, 25, 25, 50},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Kingler
		true,
		MediumFast,
		M1F1,
		70,
		{HyperCutter, ShellArmor},
		{55, 130, 115, 50, 50, 75},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Voltorb
		true,
		MediumFast,
		GenderlessOnly,
		70,
		{Soundproof, Static},
		{40, 30, 50, 55, 55, 100},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Electrode
		true,
		MediumFast,
		GenderlessOnly,
		70,
		{Soundproof, Static},
		{60, 50, 70, 80, 80, 140},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Exeggcute
		true,
		Slow,
		M1F1,
		70,
		{Chlorophyll, NoAbility},
		{60, 40, 80, 60, 45, 40},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Exeggcutor
		true,
		Slow,
		M1F1,
		70,
		{Chlorophyll, NoAbility},
		{95, 95, 85, 125, 65, 55},
		{0, 0, 0, 2, 0, 0}
	},
	{
		// Cubone
		true,
		MediumFast,
		M1F1,
		70,
		{RockHead, Lightningrod},
		{50, 50, 95, 40, 50, 35},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Marowak
		true,
		MediumFast,
		M1F1,
		70,
		{RockHead, Lightningrod},
		{60, 80, 110, 50, 80, 45},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Hitmonlee
		true,
		MediumFast,
		MaleOnly,
		70,
		{Limber, NoAbility},
		{50, 120, 53, 35, 110, 87},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Hitmonchan
		true,
		MediumFast,
		MaleOnly,
		70,
		{KeenEye, NoAbility},
		{50, 105, 79, 35, 110, 76},
		{0, 0, 0, 0, 2, 0}
	},
	{
		// Lickitung
		true,
		MediumFast,
		M1F1,
		70,
		{OwnTempo, Oblivious},
		{90, 55, 75, 60, 75, 30},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Koffing
		true,
		MediumFast,
		M1F1,
		70,
		{Levitate, NoAbility},
		{40, 65, 95, 60, 45, 35},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Weezing
		true,
		MediumFast,
		M1F1,
		70,
		{Levitate, NoAbility},
		{65, 90, 120, 85, 70, 60},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Rhyhorn
		true,
		Slow,
		M1F1,
		70,
		{Lightningrod, RockHead},
		{80, 85, 95, 30, 30, 25},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Rhydon
		true,
		Slow,
		M1F1,
		70,
		{Lightningrod, RockHead},
		{105, 130, 120, 45, 45, 40},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Chansey
		true,
		Fast,
		FemaleOnly,
		140,
		{NaturalCure, SereneGrace},
		{250, 5, 5, 35, 105, 50},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Tangela
		true,
		MediumFast,
		M1F1,
		70,
		{Chlorophyll, NoAbility},
		{65, 55, 115, 100, 40, 60},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Kangaskhan
		true,
		MediumFast,
		FemaleOnly,
		70,
		{EarlyBird, NoAbility},
		{105, 95, 80, 40, 80, 90},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Horsea
		true,
		MediumFast,
		M1F1,
		70,
		{SwiftSwim, NoAbility},
		{30, 40, 70, 70, 25, 60},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Seadra
		true,
		MediumFast,
		M1F1,
		70,
		{PoisonPoint, NoAbility},
		{55, 65, 95, 95, 45, 85},
		{0, 0, 1, 1, 0, 0}
	},
	{
		// Goldeen
		true,
		MediumFast,
		M1F1,
		70,
		{SwiftSwim, WaterVeil},
		{45, 67, 60, 35, 50, 63},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Seaking
		true,
		MediumFast,
		M1F1,
		70,
		{SwiftSwim, WaterVeil},
		{80, 92, 65, 65, 80, 68},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Staryu
		true,
		Slow,
		GenderlessOnly,
		70,
		{Illuminate, NaturalCure},
		{30, 45, 55, 70, 55, 85},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Starmie
		true,
		Slow,
		GenderlessOnly,
		70,
		{Illuminate, NaturalCure},
		{60, 75, 85, 100, 85, 115},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Mr.Mime
		true,
		MediumFast,
		M1F1,
		70,
		{Soundproof, NoAbility},
		{40, 45, 65, 100, 120, 90},
		{0, 0, 0, 0, 2, 0}
	},
	{
		// Scyther
		true,
		MediumFast,
		M1F1,
		70,
		{Swarm, NoAbility},
		{70, 110, 80, 55, 80, 105},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Jynx
		true,
		MediumFast,
		FemaleOnly,
		70,
		{Oblivious, NoAbility},
		{65, 50, 35, 115, 95, 95},
		{0, 0, 0, 2, 0, 0}
	},
	{
		// Electabuzz
		true,
		MediumFast,
		M1F3,
		70,
		{Static, NoAbility},
		{65, 83, 57, 95, 85, 105},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Magmar
		true,
		MediumFast,
		M1F3,
		70,
		{FlameBody, NoAbility},
		{65, 95, 57, 100, 85, 93},
		{0, 0, 0, 2, 0, 0}
	},
	{
		// Pinsir
		true,
		Slow,
		M1F1,
		70,
		{HyperCutter, NoAbility},
		{65, 125, 100, 55, 70, 85},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Tauros
		true,
		Slow,
		MaleOnly,
		70,
		{Intimidate, NoAbility},
		{75, 100, 95, 40, 70, 110},
		{0, 1, 0, 0, 0, 1}
	},
	{
		// Magikarp
		true,
		Slow,
		M1F1,
		70,
		{SwiftSwim, NoAbility},
		{20, 10, 55, 15, 20, 80},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Gyarados
		true,
		Slow,
		M1F1,
		70,
		{Intimidate, NoAbility},
		{95, 125, 79, 60, 100, 81},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Lapras
		true,
		Slow,
		M1F1,
		70,
		{WaterAbsorb, ShellArmor},
		{130, 85, 80, 85, 95, 60},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Ditto
		true,
		MediumFast,
		GenderlessOnly,
		70,
		{Limber, NoAbility},
		{48, 48, 48, 48, 48, 48},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Eevee
		true,
		MediumFast,
		M7F1,
		70,
		{RunAway, NoAbility},
		{55, 55, 50, 45, 65, 55},
		{0, 0, 0, 0, 1, 0}
	},
	{
		// Vaporeon
		true,
		MediumFast,
		M7F1,
		70,
		{WaterAbsorb, NoAbility},
		{130, 65, 60, 110, 95, 65},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Jolteon
		true,
		MediumFast,
		M7F1,
		70,
		{VoltAbsorb, NoAbility},
		{65, 65, 60, 110, 95, 130},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Flareon
		true,
		MediumFast,
		M7F1,
		70,
		{FlashFire, NoAbility},
		{65, 130, 60, 95, 110, 65},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Porygon
		true,
		MediumFast,
		GenderlessOnly,
		70,
		{Trace, NoAbility},
		{65, 60, 70, 85, 75, 40},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Omanyte
		true,
		MediumFast,
		M7F1,
		70,
		{SwiftSwim, ShellArmor},
		{35, 40, 100, 90, 55, 35},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Omastar
		true,
		MediumFast,
		M7F1,
		70,
		{SwiftSwim, ShellArmor},
		{70, 60, 125, 115, 70, 55},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Kabuto
		true,
		MediumFast,
		M7F1,
		70,
		{SwiftSwim, BattleArmor},
		{30, 80, 90, 55, 45, 55},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Kabutops
		true,
		MediumFast,
		M7F1,
		70,
		{SwiftSwim, BattleArmor},
		{60, 115, 105, 65, 70, 80},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Aerodactyl
		true,
		Slow,
		M7F1,
		70,
		{RockHead, Pressure},
		{80, 105, 65, 60, 75, 130},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Snorlax
		true,
		Slow,
		M7F1,
		70,
		{Immunity, ThickFat},
		{160, 110, 65, 65, 110, 30},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Articunno
		true,
		Slow,
		GenderlessOnly,
		35,
		{Pressure, NoAbility},
		{90, 85, 100, 95, 125, 85},
		{0, 0, 0, 0, 3, 0}
	},
	{
		// Zapdos
		true,
		Slow,
		GenderlessOnly,
		35,
		{Pressure, NoAbility},
		{90, 90, 85, 125, 90, 100},
		{0, 0, 0, 3, 0, 0}
	},
	{
		// Moltres
		true,
		Slow,
		GenderlessOnly,
		35,
		{Pressure, NoAbility},
		{90, 100, 90, 125, 85, 90},
		{0, 0, 0, 3, 0, 0}
	},
	{
		// Dratini
		true,
		Slow,
		M1F1,
		35,
		{ShedSkin, NoAbility},
		{41, 64, 45, 50, 50, 50},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Dragonair
		true,
		Slow,
		M1F1,
		35,
		{ShedSkin, NoAbility},
		{61, 84, 65, 70, 70, 70},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Dragonite
		true,
		Slow,
		M1F1,
		35,
		{InnerFocus, NoAbility},
		{91, 134, 95, 100, 100, 80},
		{0, 3, 0, 0, 0, 0}
	},
	{
		// Mewtwo
		true,
		Slow,
		GenderlessOnly,
		0,
		{Pressure, NoAbility},
		{106, 110, 90, 154, 90, 130},
		{0, 0, 0, 3, 0, 0}
	},
	{
		// Mew
		true,
		MediumSlow,
		GenderlessOnly,
		100,
		{Synchronize, NoAbility},
		{100, 100, 100, 100, 100, 100},
		{3, 0, 0, 0, 0, 0}
	},
	{
		// Chikorita
		true,
		MediumSlow,
		M7F1,
		70,
		{Overgrow, NoAbility},
		{45, 49, 65, 49, 65, 45},
		{0, 0, 0, 0, 1, 0}
	},
	{
		// Bayleef
		true,
		MediumSlow,
		M7F1,
		70,
		{Overgrow, NoAbility},
		{60, 62, 80, 63, 80, 60},
		{0, 0, 1, 0, 1, 0}
	},
	{
		// Meganium
		true,
		MediumSlow,
		M7F1,
		70,
		{Overgrow, NoAbility},
		{80, 82, 100, 83, 100, 80},
		{0, 0, 1, 0, 2, 0}
	},
	{
		// Cyndaquil
		true,
		MediumSlow,
		M7F1,
		70,
		{Blaze, NoAbility},
		{39, 52, 43, 60, 50, 65},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Quilava
		true,
		MediumSlow,
		M7F1,
		70,
		{Blaze, NoAbility},
		{58, 64, 58, 80, 65, 80},
		{0, 0, 0, 1, 0, 1}
	},
	{
		// Typhlosion
		true,
		MediumSlow,
		M7F1,
		70,
		{Blaze, NoAbility},
		{78, 84, 78, 109, 85, 100},
		{0, 0, 0, 3, 0, 0}
	},
	{
		// Totodile
		true,
		MediumSlow,
		M7F1,
		70,
		{Torrent, NoAbility},
		{50, 65, 64, 44, 48, 43},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Croconaw
		true,
		MediumSlow,
		M7F1,
		70,
		{Torrent, NoAbility},
		{65, 80, 80, 59, 63, 58},
		{0, 1, 1, 0, 0, 0}
	},
	{
		// Feraligatr
		true,
		MediumSlow,
		M7F1,
		70,
		{Torrent, NoAbility},
		{85, 105, 100, 79, 83, 78},
		{0, 2, 1, 0, 0, 0}
	},
	{
		// Sentret
		true,
		MediumFast,
		M1F1,
		70,
		{RunAway, KeenEye},
		{35, 46, 34, 35, 45, 20},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Furret
		true,
		MediumFast,
		M1F1,
		70,
		{RunAway, KeenEye},
		{85, 76, 64, 45, 55, 90},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Hoothoot
		true,
		MediumFast,
		M1F1,
		70,
		{Insomnia, KeenEye},
		{60, 30, 30, 36, 56, 50},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Noctowl
		true,
		MediumFast,
		M1F1,
		70,
		{Insomnia, KeenEye},
		{100, 50, 50, 76, 96, 70},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Ledyba
		true,
		Fast,
		M1F1,
		70,
		{Swarm, EarlyBird},
		{40, 20, 30, 40, 80, 55},
		{0, 0, 0, 0, 1, 0}
	},
	{
		// Ledian
		true,
		Fast,
		M1F1,
		70,
		{Swarm, EarlyBird},
		{55, 35, 50, 55, 110, 85},
		{0, 0, 0, 0, 2, 0}
	},
	{
		// Spinarak
		true,
		Fast,
		M1F1,
		70,
		{Swarm, Insomnia},
		{40, 60, 40, 40, 40, 30},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Ariados
		true,
		Fast,
		M1F1,
		70,
		{Swarm, Insomnia},
		{70, 90, 70, 60, 60, 40},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Crobat
		true,
		MediumFast,
		M1F1,
		70,
		{InnerFocus, NoAbility},
		{85, 90, 80, 70, 80, 130},
		{0, 0, 0, 0, 0, 3}
	},
	{
		// Chinchou
		true,
		Slow,
		M1F1,
		70,
		{VoltAbsorb, Illuminate},
		{75, 38, 38, 56, 56, 67},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Lanturn
		true,
		Slow,
		M1F1,
		70,
		{VoltAbsorb, Illuminate},
		{125, 58, 58, 76, 76, 67},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Pichu
		true,
		MediumFast,
		M1F1,
		70,
		{Static, NoAbility},
		{20, 40, 15, 35, 35, 60},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Cleffa
		true,
		Fast,
		M3F1,
		140,
		{CuteCharm, NoAbility},
		{50, 25, 28, 45, 55, 15},
		{0, 0, 0, 0, 1, 0}
	},
	{
		// Igglybuff
		true,
		Fast,
		M3F1,
		70,
		{CuteCharm, NoAbility},
		{90, 30, 15, 40, 20, 15},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Togepi
		true,
		Fast,
		M7F1,
		70,
		{Hustle, SereneGrace},
		{35, 20, 65, 40, 65, 20},
		{0, 0, 0, 0, 1, 0}
	},
	{
		// Togetic
		true,
		Fast,
		M7F1,
		70,
		{Hustle, SereneGrace},
		{55, 40, 85, 80, 105, 40},
		{0, 0, 0, 0, 2, 0}
	},
	{
		// Natu
		true,
		MediumFast,
		M1F1,
		70,
		{Synchronize, EarlyBird},
		{40, 50, 45, 70, 45, 70},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Xatu
		true,
		MediumFast,
		M1F1,
		70,
		{Synchronize, EarlyBird},
		{65, 75, 70, 95, 70, 95},
		{0, 0, 0, 1, 0, 1}
	},
	{
		// Mareep
		true,
		MediumSlow,
		M1F1,
		70,
		{Static, NoAbility},
		{55, 40, 40, 65, 45, 35},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Flaaffy
		true,
		MediumSlow,
		M1F1,
		70,
		{Static, NoAbility},
		{70, 55, 55, 80, 60, 45},
		{0, 0, 0, 2, 0, 0}
	},
	{
		// Ampharos
		true,
		MediumSlow,
		M1F1,
		70,
		{Static, NoAbility},
		{90, 75, 75, 115, 90, 55},
		{0, 0, 0, 3, 0, 0}
	},
	{
		// Bellossom
		true,
		MediumSlow,
		M1F1,
		70,
		{Chlorophyll, NoAbility},
		{75, 80, 85, 90, 100, 50},
		{0, 0, 0, 0, 3, 0}
	},
	{
		// Marill
		true,
		Fast,
		M1F1,
		70,
		{ThickFat, HugePower},
		{70, 20, 50, 20, 50, 40},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Azumarill
		true,
		Fast,
		M1F1,
		70,
		{ThickFat, HugePower},
		{100, 50, 80, 50, 80, 50},
		{3, 0, 0, 0, 0, 0}
	},
	{
		// Sudowoodo
		true,
		MediumFast,
		M1F1,
		70,
		{Sturdy, RockHead},
		{70, 100, 115, 30, 65, 30},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Politoed
		true,
		MediumSlow,
		M1F1,
		70,
		{WaterAbsorb, Damp},
		{90, 75, 75, 90, 100, 70},
		{0, 0, 0, 0, 3, 0}
	},
	{
		// Hoppip
		true,
		MediumSlow,
		M1F1,
		70,
		{Chlorophyll, NoAbility},
		{35, 35, 40, 35, 55, 50},
		{0, 0, 0, 0, 1, 0}
	},
	{
		// Skiploom
		true,
		MediumSlow,
		M1F1,
		70,
		{Chlorophyll, NoAbility},
		{55, 45, 50, 45, 65, 80},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Jumpluff
		true,
		MediumSlow,
		M1F1,
		70,
		{Chlorophyll, NoAbility},
		{75, 55, 70, 55, 85, 110},
		{0, 0, 0, 0, 0, 3}
	},
	{
		// Aipom
		true,
		Fast,
		M1F1,
		70,
		{RunAway, Pickup},
		{55, 70, 55, 40, 55, 85},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Sunkern
		true,
		MediumSlow,
		M1F1,
		70,
		{Chlorophyll, NoAbility},
		{30, 30, 30, 30, 30, 30},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Sunflora
		true,
		MediumSlow,
		M1F1,
		70,
		{Chlorophyll, NoAbility},
		{75, 75, 55, 105, 85, 30},
		{0, 0, 0, 2, 0, 0}
	},
	{
		// Yanma
		true,
		MediumFast,
		M1F1,
		70,
		{SpeedBoost, Compoundeyes},
		{65, 65, 45, 75, 45, 95},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Wooper
		true,
		MediumFast,
		M1F1,
		70,
		{Damp, WaterAbsorb},
		{55, 45, 45, 25, 25, 15},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Quagsire
		true,
		MediumFast,
		M1F1,
		70,
		{Damp, WaterAbsorb},
		{95, 85, 85, 65, 65, 35},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Espeon
		true,
		MediumFast,
		M7F1,
		70,
		{Synchronize, NoAbility},
		{65, 65, 60, 130, 95, 110},
		{0, 0, 0, 2, 0, 0}
	},
	{
		// Umbreon
		true,
		MediumFast,
		M7F1,
		35,
		{Synchronize, NoAbility},
		{95, 65, 110, 60, 130, 65},
		{0, 0, 0, 0, 2, 0}
	},
	{
		// Murkrow
		true,
		MediumSlow,
		M1F1,
		35,
		{Insomnia, NoAbility},
		{60, 85, 42, 85, 42, 91},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Slowking
		true,
		MediumFast,
		M1F1,
		70,
		{Oblivious, OwnTempo},
		{95, 75, 80, 100, 110, 30},
		{0, 0, 0, 0, 3, 0}
	},
	{
		// Misdreavus
		true,
		Fast,
		M1F1,
		35,
		{Levitate, NoAbility},
		{60, 60, 60, 85, 85, 85},
		{0, 0, 0, 1, 1, 0}
	},
	{
		// Unown
		true,
		MediumFast,
		GenderlessOnly,
		70,
		{Levitate, NoAbility},
		{48, 72, 48, 72, 48, 48},
		{0, 1, 0, 1, 0, 0}
	},
	{
		// Wobbuffet
		true,
		MediumFast,
		M1F1,
		70,
		{ShadowTag, NoAbility},
		{190, 33, 58, 33, 58, 33},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Girafarig
		true,
		MediumFast,
		M1F1,
		70,
		{InnerFocus, EarlyBird},
		{70, 80, 65, 90, 65, 85},
		{0, 0, 0, 2, 0, 0}
	},
	{
		// Pineco
		true,
		MediumFast,
		M1F1,
		70,
		{Sturdy, NoAbility},
		{50, 65, 90, 35, 35, 15},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Forretress
		true,
		MediumFast,
		M1F1,
		70,
		{Sturdy, NoAbility},
		{75, 90, 140, 60, 60, 40},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Dunsparce
		true,
		MediumFast,
		M1F1,
		70,
		{SereneGrace, RunAway},
		{100, 70, 70, 65, 65, 45},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Gligar
		true,
		MediumSlow,
		M1F1,
		70,
		{HyperCutter, SandVeil},
		{65, 75, 105, 35, 65, 85},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Steelix
		true,
		MediumFast,
		M1F1,
		70,
		{RockHead, Sturdy},
		{75, 85, 200, 55, 65, 30},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Snubbull
		true,
		Fast,
		M3F1,
		70,
		{Intimidate, RunAway},
		{60, 80, 50, 40, 40, 30},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Granbull
		true,
		Fast,
		M3F1,
		70,
		{Intimidate, Intimidate},
		{90, 120, 75, 60, 60, 45},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Qwilfish
		true,
		MediumFast,
		M1F1,
		70,
		{PoisonPoint, SwiftSwim},
		{65, 95, 75, 55, 55, 85},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Scizor
		true,
		MediumFast,
		M1F1,
		70,
		{Swarm, NoAbility},
		{70, 130, 100, 55, 80, 65},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Shuckle
		true,
		MediumSlow,
		M1F1,
		70,
		{Sturdy, NoAbility},
		{20, 10, 230, 10, 230, 5},
		{0, 0, 1, 0, 1, 0}
	},
	{
		// Heracross
		true,
		Slow,
		M1F1,
		70,
		{Swarm, Guts},
		{80, 125, 75, 40, 95, 85},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Sneasel
		true,
		MediumSlow,
		M1F1,
		35,
		{InnerFocus, KeenEye},
		{55, 95, 55, 35, 75, 115},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Teddiursa
		true,
		MediumFast,
		M1F1,
		70,
		{Pickup, NoAbility},
		{60, 80, 50, 50, 50, 40},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Ursaring
		true,
		MediumFast,
		M1F1,
		70,
		{Guts, NoAbility},
		{90, 130, 75, 75, 75, 55},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Slugma
		true,
		MediumFast,
		M1F1,
		70,
		{MagmaArmor, FlameBody},
		{40, 40, 40, 70, 40, 20},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Magcargo
		true,
		MediumFast,
		M1F1,
		70,
		{MagmaArmor, FlameBody},
		{50, 50, 120, 80, 80, 30},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Swinub
		true,
		Slow,
		M1F1,
		70,
		{Oblivious, NoAbility},
		{50, 50, 40, 30, 30, 50},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Piloswine
		true,
		Slow,
		M1F1,
		70,
		{Oblivious, NoAbility},
		{100, 100, 80, 60, 60, 50},
		{1, 1, 0, 0, 0, 0}
	},
	{
		// Corsola
		true,
		Fast,
		M3F1,
		70,
		{Hustle, NaturalCure},
		{55, 55, 85, 65, 85, 35},
		{0, 0, 1, 0, 1, 0}
	},
	{
		// Remoraid
		true,
		MediumFast,
		M1F1,
		70,
		{Hustle, NoAbility},
		{35, 65, 35, 65, 35, 65},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Octillery
		true,
		MediumFast,
		M1F1,
		70,
		{SuctionCups, NoAbility},
		{75, 105, 75, 105, 75, 45},
		{0, 1, 0, 1, 0, 0}
	},
	{
		// Delibird
		true,
		Fast,
		M1F1,
		70,
		{VitalSpirit, Hustle},
		{45, 55, 45, 65, 45, 75},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Mantine
		true,
		Slow,
		M1F1,
		70,
		{SwiftSwim, WaterAbsorb},
		{65, 40, 70, 80, 140, 70},
		{0, 0, 0, 0, 2, 0}
	},
	{
		// Skarmory
		true,
		Slow,
		M1F1,
		70,
		{KeenEye, Sturdy},
		{65, 80, 140, 40, 70, 70},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Houndour
		true,
		Slow,
		M1F1,
		35,
		{EarlyBird, FlashFire},
		{45, 60, 30, 80, 50, 65},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Houndoom
		true,
		Slow,
		M1F1,
		35,
		{EarlyBird, FlashFire},
		{75, 90, 50, 110, 80, 95},
		{0, 0, 0, 2, 0, 0}
	},
	{
		// Kingdra
		true,
		MediumFast,
		M1F1,
		70,
		{SwiftSwim, NoAbility},
		{75, 95, 95, 95, 95, 85},
		{0, 1, 0, 1, 1, 0}
	},
	{
		// Phanpy
		true,
		MediumFast,
		M1F1,
		70,
		{Pickup, NoAbility},
		{90, 60, 60, 40, 40, 40},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Donphan
		true,
		MediumFast,
		M1F1,
		70,
		{Sturdy, NoAbility},
		{90, 120, 120, 60, 60, 50},
		{0, 1, 1, 0, 0, 0}
	},
	{
		// Porygon2
		true,
		MediumFast,
		GenderlessOnly,
		70,
		{Trace, NoAbility},
		{85, 80, 90, 105, 95, 60},
		{0, 0, 0, 2, 0, 0}
	},
	{
		// Stantler
		true,
		Slow,
		M1F1,
		70,
		{Intimidate, NoAbility},
		{73, 95, 62, 85, 65, 85},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Smeargle
		true,
		Fast,
		M1F1,
		70,
		{OwnTempo, NoAbility},
		{55, 20, 35, 20, 45, 75},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Tyrogue
		true,
		MediumFast,
		MaleOnly,
		70,
		{Guts, NoAbility},
		{35, 35, 35, 35, 35, 35},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Hitmontop
		true,
		MediumFast,
		MaleOnly,
		70,
		{Intimidate, NoAbility},
		{50, 95, 95, 35, 110, 70},
		{0, 0, 0, 0, 2, 0}
	},
	{
		// Smoochum
		true,
		MediumFast,
		FemaleOnly,
		70,
		{Oblivious, NoAbility},
		{45, 30, 15, 85, 65, 65},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Elekid
		true,
		MediumFast,
		M1F3,
		70,
		{Static, NoAbility},
		{45, 63, 37, 65, 55, 95},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Magby
		true,
		MediumFast,
		M1F3,
		70,
		{FlameBody, NoAbility},
		{45, 75, 37, 70, 55, 83},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Miltank
		true,
		Slow,
		FemaleOnly,
		70,
		{ThickFat, NoAbility},
		{95, 80, 105, 40, 70, 100},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Blissey
		true,
		Fast,
		FemaleOnly,
		140,
		{NaturalCure, SereneGrace},
		{255, 10, 10, 75, 135, 55},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Raikou
		true,
		Slow,
		GenderlessOnly,
		35,
		{Pressure, NoAbility},
		{90, 85, 75, 115, 100, 115},
		{0, 0, 0, 1, 0, 2}
	},
	{
		// Entei
		true,
		Slow,
		GenderlessOnly,
		35,
		{Pressure, NoAbility},
		{115, 115, 85, 90, 75, 100},
		{1, 2, 0, 0, 0, 0}
	},
	{
		// Suicune
		true,
		Slow,
		GenderlessOnly,
		35,
		{Pressure, NoAbility},
		{100, 75, 115, 90, 115, 85},
		{0, 0, 1, 0, 2, 0}
	},
	{
		// Larvitar
		true,
		Slow,
		M1F1,
		35,
		{Guts, NoAbility},
		{50, 64, 50, 45, 50, 41},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Pupitar
		true,
		Slow,
		M1F1,
		35,
		{ShedSkin, NoAbility},
		{70, 84, 70, 65, 70, 51},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Tyranitar
		true,
		Slow,
		M1F1,
		35,
		{SandStream, NoAbility},
		{100, 134, 110, 95, 100, 61},
		{0, 3, 0, 0, 0, 0}
	},
	{
		// Lugia
		true,
		Slow,
		GenderlessOnly,
		0,
		{Pressure, NoAbility},
		{106, 90, 130, 90, 154, 110},
		{0, 0, 0, 0, 3, 0}
	},
	{
		// Ho-oh
		true,
		Slow,
		GenderlessOnly,
		0,
		{Pressure, NoAbility},
		{106, 130, 90, 110, 154, 90},
		{0, 0, 0, 0, 3, 0}
	},
	{
		// Celebi
		true,
		MediumSlow,
		GenderlessOnly,
		100,
		{NaturalCure, NoAbility},
		{100, 100, 100, 100, 100, 100},
		{3, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		// Treecko
		true,
		MediumSlow,
		M7F1,
		70,
		{Overgrow, NoAbility},
		{40, 45, 35, 65, 55, 70},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Grovyle
		true,
		MediumSlow,
		M7F1,
		70,
		{Overgrow, NoAbility},
		{50, 65, 45, 85, 65, 95},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Sceptile
		true,
		MediumSlow,
		M7F1,
		70,
		{Overgrow, NoAbility},
		{70, 85, 65, 105, 85, 120},
		{0, 0, 0, 0, 0, 3}
	},
	{
		// Torchic
		true,
		MediumSlow,
		M7F1,
		70,
		{Blaze, NoAbility},
		{45, 60, 40, 70, 50, 45},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Combusken
		true,
		MediumSlow,
		M7F1,
		70,
		{Blaze, NoAbility},
		{60, 85, 60, 85, 60, 55},
		{0, 1, 0, 1, 0, 0}
	},
	{
		// Blaziken
		true,
		MediumSlow,
		M7F1,
		70,
		{Blaze, NoAbility},
		{80, 120, 70, 110, 70, 80},
		{0, 3, 0, 0, 0, 0}
	},
	{
		// Mudkip
		true,
		MediumSlow,
		M7F1,
		70,
		{Torrent, NoAbility},
		{50, 70, 50, 50, 50, 40},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Marshtomp
		true,
		MediumSlow,
		M7F1,
		70,
		{Torrent, NoAbility},
		{70, 85, 70, 60, 70, 50},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Swampert
		true,
		MediumSlow,
		M7F1,
		70,
		{Torrent, NoAbility},
		{100, 110, 90, 85, 90, 60},
		{0, 3, 0, 0, 0, 0}
	},
	{
		// Poochyena
		true,
		MediumFast,
		M1F1,
		70,
		{RunAway, NoAbility},
		{35, 55, 35, 30, 30, 35},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Mightyena
		true,
		MediumFast,
		M1F1,
		70,
		{Intimidate, NoAbility},
		{70, 90, 70, 60, 60, 70},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Zigzagoon
		true,
		MediumFast,
		M1F1,
		70,
		{Pickup, NoAbility},
		{38, 30, 41, 30, 41, 60},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Linoone
		true,
		MediumFast,
		M1F1,
		70,
		{Pickup, NoAbility},
		{78, 70, 61, 50, 61, 100},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Wurmple
		true,
		MediumFast,
		M1F1,
		70,
		{ShieldDust, NoAbility},
		{45, 45, 35, 20, 30, 20},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Silcoon
		true,
		MediumFast,
		M1F1,
		70,
		{ShedSkin, NoAbility},
		{50, 35, 55, 25, 25, 15},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Beautifly
		true,
		MediumFast,
		M1F1,
		70,
		{Swarm, NoAbility},
		{60, 70, 50, 90, 50, 65},
		{0, 0, 0, 3, 0, 0}
	},
	{
		// Cascoon
		true,
		MediumFast,
		M1F1,
		70,
		{ShedSkin, NoAbility},
		{50, 35, 55, 25, 25, 15},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Dustox
		true,
		MediumFast,
		M1F1,
		70,
		{ShieldDust, NoAbility},
		{60, 50, 70, 50, 90, 65},
		{0, 0, 0, 0, 3, 0}
	},
	{
		// Lotad
		true,
		MediumSlow,
		M1F1,
		70,
		{SwiftSwim, RainDish},
		{40, 30, 30, 40, 50, 30},
		{0, 0, 0, 0, 1, 0}
	},
	{
		// Lombre
		true,
		MediumSlow,
		M1F1,
		70,
		{SwiftSwim, RainDish},
		{60, 50, 50, 60, 70, 50},
		{0, 0, 0, 0, 2, 0}
	},
	{
		// Ludicolo
		true,
		MediumSlow,
		M1F1,
		70,
		{SwiftSwim, RainDish},
		{80, 70, 70, 90, 100, 70},
		{0, 0, 0, 0, 3, 0}
	},
	{
		// Seedot
		true,
		MediumSlow,
		M1F1,
		70,
		{Chlorophyll, EarlyBird},
		{40, 40, 50, 30, 30, 30},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Nuzleaf
		true,
		MediumSlow,
		M1F1,
		70,
		{Chlorophyll, EarlyBird},
		{70, 70, 40, 60, 40, 60},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Shiftry
		true,
		MediumSlow,
		M1F1,
		70,
		{Chlorophyll, EarlyBird},
		{90, 100, 60, 90, 60, 80},
		{0, 3, 0, 0, 0, 0}
	},
	{
		// Nincada
		true,
		Erratic,
		M1F1,
		70,
		{Compoundeyes, NoAbility},
		{31, 45, 90, 30, 30, 40},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Ninjask
		true,
		Erratic,
		M1F1,
		70,
		{SpeedBoost, NoAbility},
		{61, 90, 45, 50, 50, 160},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Shedinja
		true,
		Erratic,
		GenderlessOnly,
		70,
		{WonderGuard, NoAbility},
		{1, 90, 45, 30, 30, 40},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Taillow
		true,
		MediumSlow,
		M1F1,
		70,
		{Guts, NoAbility},
		{40, 55, 30, 30, 30, 85},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Swellow
		true,
		MediumSlow,
		M1F1,
		70,
		{Guts, NoAbility},
		{60, 85, 60, 50, 50, 125},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Shroomish
		true,
		Fluctuating,
		M1F1,
		70,
		{EffectSpore, NoAbility},
		{60, 40, 60, 40, 60, 35},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Breloom
		true,
		Fluctuating,
		M1F1,
		70,
		{EffectSpore, NoAbility},
		{60, 130, 80, 60, 60, 70},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Spinda
		true,
		Fast,
		M1F1,
		70,
		{OwnTempo, NoAbility},
		{60, 60, 60, 60, 60, 60},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Wingull
		true,
		MediumFast,
		M1F1,
		70,
		{KeenEye, NoAbility},
		{40, 30, 30, 55, 30, 85},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Pelipper
		true,
		MediumFast,
		M1F1,
		70,
		{KeenEye, NoAbility},
		{60, 50, 100, 85, 70, 65},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Surskit
		true,
		MediumFast,
		M1F1,
		70,
		{SwiftSwim, NoAbility},
		{40, 30, 32, 50, 52, 65},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Masquerain
		true,
		MediumFast,
		M1F1,
		70,
		{Intimidate, NoAbility},
		{70, 60, 62, 80, 82, 60},
		{0, 0, 0, 1, 1, 0}
	},
	{
		// Wailmer
		true,
		Fluctuating,
		M1F1,
		70,
		{WaterVeil, Oblivious},
		{130, 70, 35, 70, 35, 60},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Wailord
		true,
		Fluctuating,
		M1F1,
		70,
		{WaterVeil, Oblivious},
		{170, 90, 45, 90, 45, 60},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Skitty
		true,
		Fast,
		M3F1,
		70,
		{CuteCharm, NoAbility},
		{50, 45, 45, 35, 35, 50},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Delcatty
		true,
		Fast,
		M3F1,
		70,
		{CuteCharm, NoAbility},
		{70, 65, 65, 55, 55, 70},
		{1, 0, 0, 0, 0, 1}
	},
	{
		// Kecleon
		true,
		MediumSlow,
		M1F1,
		70,
		{ColorChange, NoAbility},
		{60, 90, 70, 60, 120, 40},
		{0, 0, 0, 0, 1, 0}
	},
	{
		// Baltoy
		true,
		MediumFast,
		GenderlessOnly,
		70,
		{Levitate, NoAbility},
		{40, 40, 55, 40, 70, 55},
		{0, 0, 0, 0, 1, 0}
	},
	{
		// Claydol
		true,
		MediumFast,
		GenderlessOnly,
		70,
		{Levitate, NoAbility},
		{60, 70, 105, 70, 120, 75},
		{0, 0, 0, 0, 2, 0}
	},
	{
		// Nosepass
		true,
		MediumFast,
		M1F1,
		70,
		{Sturdy, MagnetPull},
		{30, 45, 135, 45, 90, 30},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Torkoal
		true,
		MediumFast,
		M1F1,
		70,
		{WhiteSmoke, NoAbility},
		{70, 85, 140, 85, 70, 20},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Sableye
		true,
		MediumSlow,
		M1F1,
		35,
		{KeenEye, NoAbility},
		{50, 75, 75, 65, 65, 50},
		{0, 1, 1, 0, 0, 0}
	},
	{
		// Barboach
		true,
		MediumFast,
		M1F1,
		70,
		{Oblivious, NoAbility},
		{50, 48, 43, 46, 41, 60},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Whiscash
		true,
		MediumFast,
		M1F1,
		70,
		{Oblivious, NoAbility},
		{110, 78, 73, 76, 71, 60},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Luvdisc
		true,
		Fast,
		M3F1,
		70,
		{SwiftSwim, NoAbility},
		{43, 30, 55, 40, 65, 97},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Corphish
		true,
		Fluctuating,
		M1F1,
		70,
		{HyperCutter, ShellArmor},
		{43, 80, 65, 50, 35, 35},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Crawdaunt
		true,
		Fluctuating,
		M1F1,
		70,
		{HyperCutter, ShellArmor},
		{63, 120, 85, 90, 55, 55},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Feebas
		true,
		Erratic,
		M1F1,
		70,
		{SwiftSwim, NoAbility},
		{20, 15, 20, 10, 55, 80},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Milotic
		true,
		Erratic,
		M1F1,
		70,
		{MarvelScale, NoAbility},
		{95, 60, 79, 100, 125, 81},
		{0, 0, 0, 0, 2, 0}
	},
	{
		// Carvanha
		true,
		Slow,
		M1F1,
		35,
		{RoughSkin, NoAbility},
		{45, 90, 20, 65, 20, 65},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Sharpedo
		true,
		Slow,
		M1F1,
		35,
		{RoughSkin, NoAbility},
		{70, 120, 40, 95, 40, 95},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Trapinch
		true,
		MediumSlow,
		M1F1,
		70,
		{HyperCutter, ArenaTrap},
		{45, 100, 45, 45, 45, 10},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Vibrava
		true,
		MediumSlow,
		M1F1,
		70,
		{Levitate, Levitate},
		{50, 70, 50, 50, 50, 70},
		{0, 1, 0, 0, 0, 1}
	},
	{
		// Flygon
		true,
		MediumSlow,
		M1F1,
		70,
		{Levitate, Levitate},
		{80, 100, 80, 80, 80, 100},
		{0, 1, 0, 0, 0, 2}
	},
	{
		// Makuhita
		true,
		Fluctuating,
		M1F3,
		70,
		{ThickFat, Guts},
		{72, 60, 30, 20, 30, 25},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Hariyama
		true,
		Fluctuating,
		M1F3,
		70,
		{ThickFat, Guts},
		{144, 120, 60, 40, 60, 50},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Electrike
		true,
		Slow,
		M1F1,
		70,
		{Static, Lightningrod},
		{40, 45, 40, 65, 40, 65},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Manectric
		true,
		Slow,
		M1F1,
		70,
		{Static, Lightningrod},
		{70, 75, 60, 105, 60, 105},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Numel
		true,
		MediumFast,
		M1F1,
		70,
		{Oblivious, NoAbility},
		{60, 60, 40, 65, 45, 35},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Camerupt
		true,
		MediumFast,
		M1F1,
		70,
		{MagmaArmor, NoAbility},
		{70, 100, 70, 105, 75, 40},
		{0, 1, 0, 1, 0, 0}
	},
	{
		// Spheal
		true,
		MediumSlow,
		M1F1,
		70,
		{ThickFat, NoAbility},
		{70, 40, 50, 55, 50, 25},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Sealeo
		true,
		MediumSlow,
		M1F1,
		70,
		{ThickFat, NoAbility},
		{90, 60, 70, 75, 70, 45},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Walrein
		true,
		MediumSlow,
		M1F1,
		70,
		{ThickFat, NoAbility},
		{110, 80, 90, 95, 90, 65},
		{3, 0, 0, 0, 0, 0}
	},
	{
		// Cacnea
		true,
		MediumSlow,
		M1F1,
		35,
		{SandVeil, NoAbility},
		{50, 85, 40, 85, 40, 35},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Cacturne
		true,
		MediumSlow,
		M1F1,
		35,
		{SandVeil, NoAbility},
		{70, 115, 60, 115, 60, 55},
		{0, 1, 0, 1, 0, 0}
	},
	{
		// Snorunt
		true,
		MediumFast,
		M1F1,
		70,
		{InnerFocus, NoAbility},
		{50, 50, 50, 50, 50, 50},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Glalie
		true,
		MediumFast,
		M1F1,
		70,
		{InnerFocus, NoAbility},
		{80, 80, 80, 80, 80, 80},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Lunatone
		true,
		Fast,
		GenderlessOnly,
		70,
		{Levitate, NoAbility},
		{70, 55, 65, 95, 85, 70},
		{0, 0, 0, 2, 0, 0}
	},
	{
		// Solrock
		true,
		Fast,
		GenderlessOnly,
		70,
		{Levitate, NoAbility},
		{70, 95, 85, 55, 65, 70},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Azuril
		true,
		Fast,
		M3F1,
		70,
		{ThickFat, HugePower},
		{50, 20, 40, 20, 40, 20},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Spoink
		true,
		Fast,
		M1F1,
		70,
		{ThickFat, OwnTempo},
		{60, 25, 35, 70, 80, 60},
		{0, 0, 0, 0, 1, 0}
	},
	{
		// Grumpig
		true,
		Fast,
		M1F1,
		70,
		{ThickFat, OwnTempo},
		{80, 45, 65, 90, 110, 80},
		{0, 0, 0, 0, 2, 0}
	},
	{
		// Plusle
		true,
		MediumFast,
		M1F1,
		70,
		{Plus, NoAbility},
		{60, 50, 40, 85, 75, 95},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Minun
		true,
		MediumFast,
		M1F1,
		70,
		{Minus, NoAbility},
		{60, 40, 50, 75, 85, 95},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Mawile
		true,
		Fast,
		M1F1,
		70,
		{HyperCutter, Intimidate},
		{50, 85, 85, 55, 55, 50},
		{0, 1, 1, 0, 0, 0}
	},
	{
		// Meditite
		true,
		MediumFast,
		M1F1,
		70,
		{PurePower, NoAbility},
		{30, 40, 55, 40, 55, 60},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Medicham
		true,
		MediumFast,
		M1F1,
		70,
		{PurePower, NoAbility},
		{60, 60, 75, 60, 75, 80},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Swablu
		true,
		Erratic,
		M1F1,
		70,
		{NaturalCure, NoAbility},
		{45, 40, 60, 40, 75, 50},
		{0, 0, 0, 0, 1, 0}
	},
	{
		// Altaria
		true,
		Erratic,
		M1F1,
		70,
		{NaturalCure, NoAbility},
		{75, 70, 90, 70, 105, 80},
		{0, 0, 0, 0, 2, 0}
	},
	{
		// Wynaut
		true,
		MediumFast,
		M1F1,
		70,
		{ShadowTag, NoAbility},
		{95, 23, 48, 23, 48, 23},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Duskull
		true,
		Fast,
		M1F1,
		35,
		{Levitate, NoAbility},
		{20, 40, 90, 30, 90, 25},
		{0, 0, 1, 0, 1, 0}
	},
	{
		// Dusclops
		true,
		Fast,
		M1F1,
		35,
		{Pressure, NoAbility},
		{40, 70, 130, 60, 130, 25},
		{0, 0, 1, 0, 2, 0}
	},
	{
		// Roselia
		true,
		MediumSlow,
		M1F1,
		70,
		{NaturalCure, PoisonPoint},
		{50, 60, 45, 100, 80, 65},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Slakoth
		true,
		Slow,
		M1F1,
		70,
		{Truant, NoAbility},
		{60, 60, 60, 35, 35, 30},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Vigoroth
		true,
		Slow,
		M1F1,
		70,
		{VitalSpirit, NoAbility},
		{80, 80, 80, 55, 55, 90},
		{0, 0, 0, 0, 0, 2}
	},
	{
		// Slaking
		true,
		Slow,
		M1F1,
		70,
		{Truant, NoAbility},
		{150, 160, 100, 95, 65, 100},
		{3, 0, 0, 0, 0, 0}
	},
	{
		// Gulpin
		true,
		Fluctuating,
		M1F1,
		70,
		{LiquidOoze, StickyHold},
		{70, 43, 53, 43, 53, 40},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Swalot
		true,
		Fluctuating,
		M1F1,
		70,
		{LiquidOoze, StickyHold},
		{100, 73, 83, 73, 83, 55},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Tropius
		true,
		Slow,
		M1F1,
		70,
		{Chlorophyll, NoAbility},
		{99, 68, 83, 72, 87, 51},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Whismur
		true,
		MediumSlow,
		M1F1,
		70,
		{Soundproof, NoAbility},
		{64, 51, 23, 51, 23, 28},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Loudred
		true,
		MediumSlow,
		M1F1,
		70,
		{Soundproof, NoAbility},
		{84, 71, 43, 71, 43, 48},
		{2, 0, 0, 0, 0, 0}
	},
	{
		// Exploud
		true,
		MediumSlow,
		M1F1,
		70,
		{Soundproof, NoAbility},
		{104, 91, 63, 91, 63, 68},
		{3, 0, 0, 0, 0, 0}
	},
	{
		// Clamperl
		true,
		Erratic,
		M1F1,
		70,
		{ShellArmor, NoAbility},
		{35, 64, 85, 74, 55, 32},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Huntail
		true,
		Erratic,
		M1F1,
		70,
		{SwiftSwim, NoAbility},
		{55, 104, 105, 94, 75, 52},
		{0, 1, 1, 0, 0, 0}
	},
	{
		// Gorebyss
		true,
		Erratic,
		M1F1,
		70,
		{SwiftSwim, NoAbility},
		{55, 84, 105, 114, 75, 52},
		{0, 0, 0, 2, 0, 0}
	},
	{
		// Absol
		true,
		MediumSlow,
		M1F1,
		35,
		{Pressure, NoAbility},
		{65, 130, 60, 75, 60, 75},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Shuppet
		true,
		Fast,
		M1F1,
		35,
		{Insomnia, NoAbility},
		{44, 75, 35, 63, 33, 45},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Banette
		true,
		Fast,
		M1F1,
		35,
		{Insomnia, NoAbility},
		{64, 115, 65, 83, 63, 65},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Seviper
		true,
		Fluctuating,
		M1F1,
		70,
		{ShedSkin, NoAbility},
		{73, 100, 60, 100, 60, 65},
		{0, 1, 0, 1, 0, 0}
	},
	{
		// Zangoose
		true,
		Erratic,
		M1F1,
		70,
		{Immunity, NoAbility},
		{73, 115, 60, 60, 60, 90},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Relicanth
		true,
		Slow,
		M7F1,
		70,
		{SwiftSwim, RockHead},
		{100, 90, 130, 45, 65, 55},
		{1, 0, 1, 0, 0, 0}
	},
	{
		// Aron
		true,
		Slow,
		M1F1,
		35,
		{Sturdy, RockHead},
		{50, 70, 100, 40, 40, 30},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Lairon
		true,
		Slow,
		M1F1,
		35,
		{Sturdy, RockHead},
		{60, 90, 140, 50, 50, 40},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Aggron
		true,
		Slow,
		M1F1,
		35,
		{Sturdy, RockHead},
		{70, 110, 180, 60, 60, 50},
		{0, 0, 3, 0, 0, 0}
	},
	{
		// Castform
		true,
		MediumFast,
		M1F1,
		70,
		{Forecast, NoAbility},
		{70, 70, 70, 70, 70, 70},
		{1, 0, 0, 0, 0, 0}
	},
	{
		// Volbeat
		true,
		Erratic,
		MaleOnly,
		70,
		{Illuminate, Swarm},
		{65, 73, 55, 47, 75, 85},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Illumise
		true,
		Fluctuating,
		FemaleOnly,
		70,
		{Oblivious, NoAbility},
		{65, 47, 55, 73, 75, 85},
		{0, 0, 0, 0, 0, 1}
	},
	{
		// Lileep
		true,
		Erratic,
		M7F1,
		70,
		{SuctionCups, NoAbility},
		{66, 41, 77, 61, 87, 23},
		{0, 0, 0, 0, 1, 0}
	},
	{
		// Cradily
		true,
		Erratic,
		M7F1,
		70,
		{SuctionCups, NoAbility},
		{86, 81, 97, 81, 107, 43},
		{0, 0, 0, 0, 2, 0}
	},
	{
		// Anorith
		true,
		Erratic,
		M7F1,
		70,
		{BattleArmor, NoAbility},
		{45, 95, 50, 40, 50, 75},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Armaldo
		true,
		Erratic,
		M7F1,
		70,
		{BattleArmor, NoAbility},
		{75, 125, 100, 70, 80, 45},
		{0, 2, 0, 0, 0, 0}
	},
	{
		// Ralts
		true,
		Slow,
		M1F1,
		35,
		{Synchronize, Trace},
		{28, 25, 25, 45, 35, 40},
		{0, 0, 0, 1, 0, 0}
	},
	{
		// Kirlia
		true,
		Slow,
		M1F1,
		35,
		{Synchronize, Trace},
		{38, 35, 35, 65, 55, 50},
		{0, 0, 0, 2, 0, 0}
	},
	{
		// Gardevoir
		true,
		Slow,
		M1F1,
		35,
		{Synchronize, Trace},
		{68, 65, 65, 125, 115, 80},
		{0, 0, 0, 3, 0, 0}
	},
	{
		// Bagon
		true,
		Slow,
		M1F1,
		35,
		{RockHead, NoAbility},
		{45, 75, 60, 40, 30, 50},
		{0, 1, 0, 0, 0, 0}
	},
	{
		// Shellgon
		true,
		Slow,
		M1F1,
		35,
		{RockHead, NoAbility},
		{65, 95, 100, 60, 50, 50},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Salamence
		true,
		Slow,
		M1F1,
		35,
		{Intimidate, NoAbility},
		{95, 135, 80, 110, 80, 100},
		{0, 3, 0, 0, 0, 0}
	},
	{
		// Beldum
		true,
		Slow,
		GenderlessOnly,
		35,
		{ClearBody, NoAbility},
		{40, 55, 80, 35, 60, 30},
		{0, 0, 1, 0, 0, 0}
	},
	{
		// Metang
		true,
		Slow,
		GenderlessOnly,
		35,
		{ClearBody, NoAbility},
		{60, 75, 100, 55, 80, 50},
		{0, 0, 2, 0, 0, 0}
	},
	{
		// Metagross
		true,
		Slow,
		GenderlessOnly,
		35,
		{ClearBody, NoAbility},
		{80, 135, 130, 95, 90, 70},
		{0, 0, 3, 0, 0, 0}
	},
	{
		// Regirock
		true,
		Slow,
		GenderlessOnly,
		35,
		{ClearBody, NoAbility},
		{80, 100, 200, 50, 100, 50},
		{0, 0, 3, 0, 0, 0}
	},
	{
		// Regice
		true,
		Slow,
		GenderlessOnly,
		35,
		{ClearBody, NoAbility},
		{80, 50, 100, 100, 200, 50},
		{0, 0, 0, 0, 3, 0}
	},
	{
		// Registeel
		true,
		Slow,
		GenderlessOnly,
		35,
		{ClearBody, NoAbility},
		{80, 75, 150, 75, 150, 50},
		{0, 0, 2, 0, 1, 0}
	},
	{
		// Kyogre
		true,
		Slow,
		GenderlessOnly,
		0,
		{Drizzle, NoAbility},
		{100, 100, 90, 150, 140, 90},
		{0, 0, 0, 3, 0, 0}
	},
	{
		// Groudon
		true,
		Slow,
		GenderlessOnly,
		0,
		{Drought, NoAbility},
		{100, 150, 140, 100, 90, 90},
		{0, 3, 0, 0, 0, 0}
	},
	{
		// Rayquaza
		true,
		Slow,
		GenderlessOnly,
		0,
		{AirLock, NoAbility},
		{105, 150, 90, 150, 90, 95},
		{0, 2, 0, 1, 0, 0}
	},
	{
		// Latias
		true,
		Slow,
		FemaleOnly,
		90,
		{Levitate, NoAbility},
		{80, 80, 90, 110, 130, 110},
		{0, 0, 0, 0, 3, 0}
	},
	{
		// Latios
		true,
		Slow,
		MaleOnly,
		90,
		{Levitate, NoAbility},
		{80, 90, 80, 130, 110, 110},
		{0, 0, 0, 3, 0, 0}
	},
	{
		// Jirachi
		true,
		Slow,
		GenderlessOnly,
		100,
		{SereneGrace, NoAbility},
		{100, 100, 100, 100, 100, 100},
		{3, 0, 0, 0, 0, 0}
	},
	{
		// Deoxys
		true,
		Slow,
		GenderlessOnly,
		0,
		{Pressure, NoAbility},
		{50, 150, 50, 150, 50, 150},
		{0, 1, 0, 1, 0, 1}
	},
	{
		// Chimecho
		true,
		Fast,
		M1F1,
		70,
		{Levitate, NoAbility},
		{65, 50, 70, 95, 80, 65},
		{0, 0, 0, 1, 1, 0}
	},
	{
		false,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		// Bonsly
		true,
		MediumFast,
		M1F1,
		70,
		{Sturdy, RockHead},
		{42, 40, 92, 12, 52, 18},
		{0, 0, 0, 0, 0, 0}
	},
	{
		// Munchlax
		true,
		MediumFast,
		MaleOnly,
		0,
		{NoAbility, NoAbility},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
};


PokemonSpeciesData getSpeciesData(PokemonSpeciesIndex index) {
	if (index > Munchlax) {
		PokemonSpeciesData ret = {};
		return ret;
	}
	return speciesData[(size_t)index];
}

const u32* getSpeciesExpTable(PokemonSpeciesIndex index) {
	if (index > Munchlax) return NULL;
	return expTables[(size_t)getSpeciesData(index).expGrowthType];
}

PokemonNatureAffinity getNatureStatAffinity(PokemonNatureIndex nature, size_t stat) {
	if (stat == 0 || nature > Quirky) return Neutral; // HP
	return natureStatAffinities[(size_t)nature][(size_t)stat - 1];
}

u8 getBaseMoveMaxPPs(PokemonMoveIndex move) {
	if (move > PsychoBoost) return 0;
	return baseMoveMaxPPs[(size_t)move];
}

}