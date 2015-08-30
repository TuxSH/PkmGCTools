#ifndef _LIBPKMGC_ITEM_INFO_H
#define _LIBPKMGC_ITEM_INFO_H

#include <LibPkmGC/Core/IntegerTypes.h>

namespace LibPkmGC {

enum ItemIndex {
	NoItem = 0x0000,
	MasterBall = 0x0001,
	UltraBall = 0x0002,
	GreatBall = 0x0003,
	PokeBall = 0x0004,
	SafariBall = 0x0005,
	NetBall = 0x0006,
	DiveBall = 0x0007,
	NestBall = 0x0008,
	RepeatBall = 0x0009,
	TimerBall = 0x000A,
	LuxuryBall = 0x000B,
	PremierBall = 0x000C,
	Potion = 0x000D,
	Antidote = 0x000E,
	BurnHeal = 0x000F,
	IceHeal = 0x0010,
	Awakening = 0x0011,
	ParlyzHeal = 0x0012,
	FullRestore = 0x0013,
	MaxPotion = 0x0014,
	HyperPotion = 0x0015,
	SuperPotion = 0x0016,
	FullHeal = 0x0017,
	Revive = 0x0018,
	MaxRevive = 0x0019,
	FreshWater = 0x001A,
	SodaPop = 0x001B,
	Lemonade = 0x001C,
	MoomooMilk = 0x001D,
	EnergyPowder = 0x001E,
	EnergyRoot = 0x001F,
	HealPowder = 0x0020,
	RevivalHerb = 0x0021,
	Ether = 0x0022,
	MaxEther = 0x0023,
	Elixir = 0x0024,
	MaxElixir = 0x0025,
	LavaCookie = 0x0026,
	BlueFlute = 0x0027,
	YellowFlute = 0x0028,
	RedFlute = 0x0029,
	BlackFlute = 0x002A,
	WhiteFlute = 0x002B,
	BerryJuice = 0x002C,
	SacredAsh = 0x002D,
	ShoalSalt = 0x002E,
	ShoalShell = 0x002F,
	RedShard = 0x0030,
	BlueShard = 0x0031,
	YellowShard = 0x0032,
	GreenShard = 0x0033,


	HPUp = 0x003F,
	Protein = 0x0040,
	Iron = 0x0041,
	Carbos = 0x0042,
	Calcium = 0x0043,
	RareCandy = 0x0044,
	PPUp = 0x0045,
	Zinc = 0x0046,
	PPMax = 0x0047,


	GuardSpec = 0x0049,
	DireHit = 0x004A,
	XAttack = 0x004B,
	XDefend = 0x004C,
	XSpeed = 0x004D,
	XAccuracy = 0x004E,
	XSpecial = 0x004F,
	Pokedoll = 0x0050,
	FluffyTail = 0x0051,

	SuperRepel = 0x0053,
	MaxRepel = 0x0054,
	EscapeRope = 0x0055,
	Repel = 0x0056,

	SunStone = 0x005D,
	MoonStone = 0x005E,
	FireStone = 0x005F,
	ThunderStone = 0x0060,
	WaterStone = 0x0061,
	LeafStone = 0x0062,

	TinyMushroom = 0x0067,
	BigMushroom = 0x0068,

	Pearl = 0x006A,
	BigPearl = 0x006B,
	Stardust = 0x006C,
	StarPiece = 0x006D,
	Nugget = 0x006E,
	HeartScale = 0x006F,

	OrangeMail = 0x0079,
	HarborMail = 0x007A,
	GlitterMail = 0x007B,
	MechMail = 0x007C,
	WoodMail = 0x007D,
	WaveMail = 0x007E,
	BeadMail = 0x007F,
	ShadowMail = 0x0080,
	TropicMail = 0x0081,
	DreamMail = 0x0082,
	FabMail = 0x0083,
	RetroMail = 0x0084,

	CheriBerry = 0x0085,
	ChestoBerry = 0x0086,
	PechaBerry = 0x0087,
	RawstBerry = 0x0088,
	AspearBerry = 0x0089,
	LeppaBerry = 0x008A,
	OranBerry = 0x008B,
	PersimBerry = 0x008C,
	LumBerry = 0x008D,
	SitrusBerry = 0x008E,
	FigyBerry = 0x008F,
	WikiBerry = 0x0090,
	MagoBerry = 0x0091,
	AguavBerry = 0x0092,
	IapapaBerry = 0x0093,
	RazzBerry = 0x0094,
	BlukBerry = 0x0095,
	NanabBerry = 0x0096,
	WepearBerry = 0x0097,
	PinapBerry = 0x0098,
	PomegBerry = 0x0099,
	KelpsyBerry = 0x009A,
	QualotBerry = 0x009B,
	HondewBerry = 0x009C,
	GrepaBerry = 0x009D,
	TamatoBerry = 0x009E,
	CornnBerry = 0x009F,
	MagostBerry = 0x00A0,
	RabutaBerry = 0x00A1,
	NomelBerry = 0x00A2,
	SpelonBerry = 0x00A3,
	PamtreBerry = 0x00A4,
	WatmelBerry = 0x00A5,
	DurinBerry = 0x00A6,
	BelueBerry = 0x00A7,
	LiechiBerry = 0x00A8,
	GanlonBerry = 0x00A9,
	SalacBerry = 0x00AA,
	PetayaBerry = 0x00AB,
	ApicotBerry = 0x00AC,
	LansatBerry = 0x00AD,
	StarfBerry = 0x00AE,
	EnigmaBerry = 0x00AF,

	BrightPowder = 0x00B3,
	WhiteHerb = 0x00B4,
	MachoBrace = 0x00B5,
	ExpShare = 0x00B6,
	QuickClaw = 0x00B7,
	SootheBell = 0x00B8,
	MentalHerb = 0x00B9,
	ChoiceBand = 0x00BA,
	KingsRock = 0x00BB,
	SilverPowder = 0x00BC,
	AmuletCoin = 0x00BD,
	CleanseTag = 0x00BE,
	SoulDew = 0x00BF,
	DeepSeaTooth = 0x00C0,
	DeepSeaScale = 0x00C1,
	SmokeBall = 0x00C2,
	Everstone = 0x00C3,
	FocusBand = 0x00C4,
	LuckyEgg = 0x00C5,
	ScopeLens = 0x00C6,
	MetalCoat = 0x00C7,
	Leftovers = 0x00C8,
	DragonScale = 0x00C9,
	LightBall = 0x00CA,
	SoftSand = 0x00CB,
	HardStone = 0x00CC,
	MiracleSeed = 0x00CD,
	BlackGlasses = 0x00CE,
	BlackBelt = 0x00CF,
	Magnet = 0x00D0,
	MysticWater = 0x00D1,
	SharpBeak = 0x00D2,
	PoisonBarb = 0x00D3,
	NeverMeltIce = 0x00D4,
	SpellTag = 0x00D5,
	TwistedSpoon = 0x00D6,
	Charcoal = 0x00D7,
	DragonFang = 0x00D8,
	SilkScarf = 0x00D9,
	UpGrade = 0x00DA,
	ShellBell = 0x00DB,
	SeaIncense = 0x00DC,
	LaxIncense = 0x00DD,
	LuckyPunch = 0x00DE,
	MetalPowder = 0x00DF,
	ThickClub = 0x00E0,
	Stick = 0x00E1,


	RedScarf = 0x00FE,
	BlueScarf = 0x00FF,
	PinkScarf = 0x0100,
	GreenScarf = 0x0101,
	YellowScarf = 0x0102,

	TM01 = 0x0121,
	TM02 = 0x0122,
	TM03 = 0x0123,
	TM04 = 0x0124,
	TM05 = 0x0125,
	TM06 = 0x0126,
	TM07 = 0x0127,
	TM08 = 0x0128,
	TM09 = 0x0129,
	TM10 = 0x012A,
	TM11 = 0x012B,
	TM12 = 0x012C,
	TM13 = 0x012D,
	TM14 = 0x012E,
	TM15 = 0x012F,
	TM16 = 0x0130,
	TM17 = 0x0131,
	TM18 = 0x0132,
	TM19 = 0x0133,
	TM20 = 0x0134,
	TM21 = 0x0135,
	TM22 = 0x0136,
	TM23 = 0x0137,
	TM24 = 0x0138,
	TM25 = 0x0139,
	TM26 = 0x013A,
	TM27 = 0x013B,
	TM28 = 0x013C,
	TM29 = 0x013D,
	TM30 = 0x013E,
	TM31 = 0x013F,
	TM32 = 0x0140,
	TM33 = 0x0141,
	TM34 = 0x0142,
	TM35 = 0x0143,
	TM36 = 0x0144,
	TM37 = 0x0145,
	TM38 = 0x0146,
	TM39 = 0x0147,
	TM40 = 0x0148,
	TM41 = 0x0149,
	TM42 = 0x014A,
	TM43 = 0x014B,
	TM44 = 0x014C,
	TM45 = 0x014D,
	TM46 = 0x014E,
	TM47 = 0x014F,
	TM48 = 0x0150,
	TM49 = 0x0151,
	TM50 = 0x0152,

	/* Colosseum-only items (mostly key items) */

	JailKey = 0x01F4,
	ElevatorKey = 0x01F5, // common to colo and XD

	SmallTablet = 0x01F6,
	FDisk = 0x01F7,
	RDisk = 0x01F8,
	LDisk = 0x01F9,
	DDisk = 0x01FA,
	UDisk = 0x01FB,
	SubwayKey = 0x01FC,
	MaingateKey = 0x01FD,
	CardKey = 0x01FE,
	DownStKey = 0x01FF,
	DNASample = 0x0200,
	DNASample1 = 0x0201,
	DNASample2 = 0x0202,
	DNASample3 = 0x0203,
	DNASample4 = 0x0204,
	DNASample5 = 0x0205,
	DNASample6 = 0x0206,
	DNASample7 = 0x0207,
	DNASample8 = 0x0208,
	DNASample9 = 0x0209,
	DNASample10 = 0x020A,
	DNASample11 = 0x020B,
	DNASample12 = 0x020C,
	DNASample13 = 0x020D,
	DNASample14 = 0x020E,
	DNASample15 = 0x020F,
	DNASample16 = 0x0210,
	DNASample17 = 0x0211,
	DataROM_C = 0x0212,
	SteelTeeth = 0x0213,
	Gear = 0x0214,
	RedIDBadge = 0x0215,
	GrnIDBadge = 0x0216,
	BluIDBadge = 0x0217,
	YlwIDBadge = 0x0218,
	TimeFlute = 0x0219,
	EinFileS = 0x021A,
	EinFileH = 0x021B,
	EinFileC = 0x021C,
	EinFileP = 0x021D,
	CologneCase_C = 0x021E,
	JoyScent_C = 0x021F,
	ExciteScent_C = 0x0220,
	VividScent_C = 0x0221,
	PowerupPart = 0x0222,
	EinFileF = 0x0223,


	/* XD-only items. On the debugger, they will probably be hidden by the Colosseum-only items */
	SafeKey = 0x01F4,

	BonslyCard = 0x01F6,
	MachinePart = 0x01F7,
	GonzapsKey = 0x01F8,
	DataROM_XD = 0x01F9,
	IDCard = 0x01FA,
	MusicDisc = 0x01FB,
	SystemLever = 0x01FC,
	MayorsNote = 0x01FD,
	MirorRadar = 0x01FE,
	PokeSnack = 0x01FF,
	CologneCase_XD = 0x200,
	JoyScent_XD = 0x0201,
	ExciteScent_XD = 0x0202,
	VividScent_XD = 0x0203,
	SunShard = 0x0204,
	MoonShard = 0x0205,
	BonslyPhoto = 0x0206,
	CryAnalyzer = 0x0207,


	KraneMemo1 = 0x020B,
	KraneMemo2 = 0x020C,
	KraneMemo3 = 0x020D,
	KraneMemo4 = 0x020E,
	KraneMemo5 = 0x020F,
	VoiceCase1 = 0x0210,
	VoiceCase2 = 0x0211,
	VoiceCase3 = 0x0212,
	VoiceCase4 = 0x0213,
	VoiceCase5 = 0x0214,
	DiscCase = 0x0215,
	BattleCD01 = 0x0216,
	BattleCD02 = 0x0217,
	BattleCD03 = 0x0218,
	BattleCD04 = 0x0219,
	BattleCD05 = 0x021A,
	BattleCD06 = 0x021B,
	BattleCD07 = 0x021C,
	BattleCD08 = 0x021D,
	BattleCD09 = 0x021E,
	BattleCD10 = 0x021F,
	BattleCD11 = 0x0220,
	BattleCD12 = 0x0221,
	BattleCD13 = 0x0222,
	BattleCD14 = 0x0223,
	BattleCD15 = 0x0224,
	BattleCD16 = 0x0225,
	BattleCD17 = 0x0226,
	BattleCD18 = 0x0227,
	BattleCD19 = 0x0228,
	BattleCD20 = 0x0229,
	BattleCD21 = 0x022A,
	BattleCD22 = 0x022B,
	BattleCD23 = 0x022C,
	BattleCD24 = 0x022D,
	BattleCD25 = 0x022E,
	BattleCD26 = 0x022F,
	BattleCD27 = 0x0230,
	BattleCD28 = 0x0231,
	BattleCD29 = 0x0232,
	BattleCD30 = 0x0233,
	BattleCD31 = 0x0234,
	BattleCD32 = 0x0235,
	BattleCD33 = 0x0236,
	BattleCD34 = 0x0237,
	BattleCD35 = 0x0238,
	BattleCD36 = 0x0239,
	BattleCD37 = 0x023A,
	BattleCD38 = 0x023B,
	BattleCD39 = 0x023C,
	BattleCD40 = 0x023D,
	BattleCD41 = 0x023E,
	BattleCD42 = 0x023F,
	BattleCD43 = 0x0240,
	BattleCD44 = 0x0241,
	BattleCD45 = 0x0242,
	BattleCD46 = 0x0243,
	BattleCD47 = 0x0244,
	BattleCD48 = 0x0245,
	BattleCD49 = 0x0246,
	BattleCD50 = 0x0247,
	BattleCD51 = 0x0248,
	BattleCD52 = 0x0249,
	BattleCD53 = 0x024A,
	BattleCD54 = 0x024B,
	BattleCD55 = 0x024C,
	BattleCD56 = 0x024D,
	BattleCD57 = 0x024E,
	BattleCD58 = 0x024F,
	BattleCD59 = 0x0250,
	BattleCD60 = 0x0251,
};

struct LIBPKMGC_DECL Item {
	ItemIndex index;
	u16 quantity;

	void load(u8* data);
	void save(u8* data);
};

enum ItemCategoryIndex {
	NoItemCategory = 0,
	PokeballsCategory = 1,
	RegularItemsCategory = 2,
	BerriesCategory = 3,
	TMsCategory = 4,
	KeyItemsCategory = 5,
	ColognesCategory = 6,
	BattleCDsCategory = 7
};

LIBPKMGC_DECL ItemCategoryIndex getItemCategory(ItemIndex index, bool isXD = false);

}

#endif