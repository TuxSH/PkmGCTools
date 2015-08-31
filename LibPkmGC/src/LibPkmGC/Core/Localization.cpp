/*
* Copyright (C) TuxSH 2015
* This file is part of LibPkmGC.
*
* LibPkmGC is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* LibPkmGC is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with LibPkmGC.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <LibPkmGC/Core/Localization.h>

namespace LibPkmGC {

namespace Localization {

size_t itemIndexToNameIndex(ItemIndex index, bool isXD) {
	size_t i = (size_t)index;
	if ((index >= NoItem) && (index <= GreenShard)) return i;
	i -= 11;
	if ((index >= HPUp) && (index <= PPMax)) return i;
	--i;
	if ((index >= GuardSpec) && (index <= FluffyTail)) return i;
	--i;
	if ((index >= SuperRepel) && (index <= Repel)) return i;
	i -= 6;
	if ((index >= SunStone) && (index <= LeafStone)) return i;
	i -= 4;
	if ((index == TinyMushroom) || (index == BigMushroom)) return i;
	--i;
	if ((index >= Pearl) && (index <= HeartScale)) return i;
	i -= 9;
	if ((index >= OrangeMail) && (index <= EnigmaBerry)) return i;
	i -= 3;
	if ((index >= BrightPowder) && (index <= Stick)) return i;
	i -= 28;
	if ((index >= RedScarf) && (index <= YellowScarf)) return i;
	i -= 30;
	if ((index >= TM01) && (index <= TM50)) return i;
	i -= 161;
	if (isXD) {
		if (index < SafeKey || index > BattleCD60) return 0;
		return i;
	}
	else{
		if (index < SafeKey || index > EinFileF) return 0;
		return i;
	}
	return 0;
}

ItemIndex nameIndexToItemIndex(size_t index, bool isXD) {
	static const ItemIndex commonItems[] = {
		NoItem,
		MasterBall,
		UltraBall,
		GreatBall,
		PokeBall,
		SafariBall,
		NetBall,
		DiveBall,
		NestBall,
		RepeatBall,
		TimerBall,
		LuxuryBall,
		PremierBall,
		Potion,
		Antidote,
		BurnHeal,
		IceHeal,
		Awakening,
		ParlyzHeal,
		FullRestore,
		MaxPotion,
		HyperPotion,
		SuperPotion,
		FullHeal,
		Revive,
		MaxRevive,
		FreshWater,
		SodaPop,
		Lemonade,
		MoomooMilk,
		EnergyPowder,
		EnergyRoot,
		HealPowder,
		RevivalHerb,
		Ether,
		MaxEther,
		Elixir,
		MaxElixir,
		LavaCookie,
		BlueFlute,
		YellowFlute,
		RedFlute,
		BlackFlute,
		WhiteFlute,
		BerryJuice,
		SacredAsh,
		ShoalSalt,
		ShoalShell,
		RedShard,
		BlueShard,
		YellowShard,
		GreenShard,


		HPUp,
		Protein,
		Iron,
		Carbos,
		Calcium,
		RareCandy,
		PPUp,
		Zinc,
		PPMax,


		GuardSpec,
		DireHit,
		XAttack,
		XDefend,
		XSpeed,
		XAccuracy,
		XSpecial,
		Pokedoll,
		FluffyTail,

		SuperRepel,
		MaxRepel,
		EscapeRope,
		Repel,

		SunStone,
		MoonStone,
		FireStone,
		ThunderStone,
		WaterStone,
		LeafStone,

		TinyMushroom,
		BigMushroom,

		Pearl,
		BigPearl,
		Stardust,
		StarPiece,
		Nugget,
		HeartScale,

		OrangeMail,
		HarborMail,
		GlitterMail,
		MechMail,
		WoodMail,
		WaveMail,
		BeadMail,
		ShadowMail,
		TropicMail,
		DreamMail,
		FabMail,
		RetroMail,

		CheriBerry,
		ChestoBerry,
		PechaBerry,
		RawstBerry,
		AspearBerry,
		LeppaBerry,
		OranBerry,
		PersimBerry,
		LumBerry,
		SitrusBerry,
		FigyBerry,
		WikiBerry,
		MagoBerry,
		AguavBerry,
		IapapaBerry,
		RazzBerry,
		BlukBerry,
		NanabBerry,
		WepearBerry,
		PinapBerry,
		PomegBerry,
		KelpsyBerry,
		QualotBerry,
		HondewBerry,
		GrepaBerry,
		TamatoBerry,
		CornnBerry,
		MagostBerry,
		RabutaBerry,
		NomelBerry,
		SpelonBerry,
		PamtreBerry,
		WatmelBerry,
		DurinBerry,
		BelueBerry,
		LiechiBerry,
		GanlonBerry,
		SalacBerry,
		PetayaBerry,
		ApicotBerry,
		LansatBerry,
		StarfBerry,
		EnigmaBerry,

		BrightPowder,
		WhiteHerb,
		MachoBrace,
		ExpShare,
		QuickClaw,
		SootheBell,
		MentalHerb,
		ChoiceBand,
		KingsRock,
		SilverPowder,
		AmuletCoin,
		CleanseTag,
		SoulDew,
		DeepSeaTooth,
		DeepSeaScale,
		SmokeBall,
		Everstone,
		FocusBand,
		LuckyEgg,
		ScopeLens,
		MetalCoat,
		Leftovers,
		DragonScale,
		LightBall,
		SoftSand,
		HardStone,
		MiracleSeed,
		BlackGlasses,
		BlackBelt,
		Magnet,
		MysticWater,
		SharpBeak,
		PoisonBarb,
		NeverMeltIce,
		SpellTag,
		TwistedSpoon,
		Charcoal,
		DragonFang,
		SilkScarf,
		UpGrade,
		ShellBell,
		SeaIncense,
		LaxIncense,
		LuckyPunch,
		MetalPowder,
		ThickClub,
		Stick,


		RedScarf,
		BlueScarf,
		PinkScarf,
		GreenScarf,
		YellowScarf,

		TM01,
		TM02,
		TM03,
		TM04,
		TM05,
		TM06,
		TM07,
		TM08,
		TM09,
		TM10,
		TM11,
		TM12,
		TM13,
		TM14,
		TM15,
		TM16,
		TM17,
		TM18,
		TM19,
		TM20,
		TM21,
		TM22,
		TM23,
		TM24,
		TM25,
		TM26,
		TM27,
		TM28,
		TM29,
		TM30,
		TM31,
		TM32,
		TM33,
		TM34,
		TM35,
		TM36,
		TM37,
		TM38,
		TM39,
		TM40,
		TM41,
		TM42,
		TM43,
		TM44,
		TM45,
		TM46,
		TM47,
		TM48,
		TM49,
		TM50
	};
	static const ItemIndex colosseumItems[] = {
		JailKey,
		ElevatorKey,

		SmallTablet,
		FDisk,
		RDisk,
		LDisk,
		DDisk,
		UDisk,
		SubwayKey,
		MaingateKey,
		CardKey,
		DownStKey,
		DNASample,
		DNASample1,
		DNASample2,
		DNASample3,
		DNASample4,
		DNASample5,
		DNASample6,
		DNASample7,
		DNASample8,
		DNASample9,
		DNASample10,
		DNASample11,
		DNASample12,
		DNASample13,
		DNASample14,
		DNASample15,
		DNASample16,
		DNASample17,
		DataROM_C,
		SteelTeeth,
		Gear,
		RedIDBadge,
		GrnIDBadge,
		BluIDBadge,
		YlwIDBadge,
		TimeFlute,
		EinFileS,
		EinFileH,
		EinFileC,
		EinFileP,
		CologneCase_C,
		JoyScent_C,
		ExciteScent_C,
		VividScent_C,
		PowerupPart,
		EinFileF,
	};
	static const ItemIndex XDItems[] = {
		SafeKey,
		ElevatorKey,
		BonslyCard,
		MachinePart,
		GonzapsKey,
		DataROM_XD,
		IDCard,
		MusicDisc,
		SystemLever,
		MayorsNote,
		MirorRadar,
		PokeSnack,
		CologneCase_XD,
		JoyScent_XD,
		ExciteScent_XD,
		VividScent_XD,
		SunShard,
		MoonShard,
		BonslyPhoto,
		CryAnalyzer,


		KraneMemo1,
		KraneMemo2,
		KraneMemo3,
		KraneMemo4,
		KraneMemo5,
		VoiceCase1,
		VoiceCase2,
		VoiceCase3,
		VoiceCase4,
		VoiceCase5,
		DiscCase,
		BattleCD01,
		BattleCD02,
		BattleCD03,
		BattleCD04,
		BattleCD05,
		BattleCD06,
		BattleCD07,
		BattleCD08,
		BattleCD09,
		BattleCD10,
		BattleCD11,
		BattleCD12,
		BattleCD13,
		BattleCD14,
		BattleCD15,
		BattleCD16,
		BattleCD17,
		BattleCD18,
		BattleCD19,
		BattleCD20,
		BattleCD21,
		BattleCD22,
		BattleCD23,
		BattleCD24,
		BattleCD25,
		BattleCD26,
		BattleCD27,
		BattleCD28,
		BattleCD29,
		BattleCD30,
		BattleCD31,
		BattleCD32,
		BattleCD33,
		BattleCD34,
		BattleCD35,
		BattleCD36,
		BattleCD37,
		BattleCD38,
		BattleCD39,
		BattleCD40,
		BattleCD41,
		BattleCD42,
		BattleCD43,
		BattleCD44,
		BattleCD45,
		BattleCD46,
		BattleCD47,
		BattleCD48,
		BattleCD49,
		BattleCD50,
		BattleCD51,
		BattleCD52,
		BattleCD53,
		BattleCD54,
		BattleCD55,
		BattleCD56,
		BattleCD57,
		BattleCD58,
		BattleCD59,
		BattleCD60,
	};
	
	if (index < 245) return commonItems[index];
	index -= 245;

	if (isXD) {
		if (index < 91) return XDItems[index];
	}
	else {
		if (index < 48) return colosseumItems[index];
	}
	return NoItem;
}

size_t pkmSpeciesIndexToNameIndex(PokemonSpeciesIndex index) {
	if (index == Bonsly) return 387;
	return (size_t) getPokedexIndexOf(index);
}
PokemonSpeciesIndex nameIndexToPkmSpeciesIndex(size_t index) {
	if (index == 387) return Bonsly;
	return getSpeciesIndexOf((u16)index);
}

#define LIBPKMGC_CHECK_LANG_INDEX(lang) lang = ((lang == NoLanguage) || (lang > Spanish)) ? English : lang;
#define LIBPKMGC_GET_LOCALIZED_NAME_LIST(lang) const char **lst = (names[(size_t)lang] == NULL) ? names[2] : names[(size_t)lang];
#define LIBPKMGC_GET_LOCALIZED_NAME(lang, id, maxval) LIBPKMGC_CHECK_LANG_INDEX(lang); LIBPKMGC_GET_LOCALIZED_NAME_LIST(lang);\
return (id > maxval) ? lst[0] : lst[(size_t)id];

const char* getPokemonSpeciesName(LanguageIndex language, PokemonSpeciesIndex index) {
	using namespace Detail::Species;
	size_t id = pkmSpeciesIndexToNameIndex(index);
	LIBPKMGC_GET_LOCALIZED_NAME(language, id, 387);
}

const char* getPokemonSpeciesNameByPkdxIndex(LanguageIndex language, u16 pkdexIndex) {
	using namespace Detail::Species;
	size_t id = (pkdexIndex == 438) ? 387 : pkdexIndex;
	LIBPKMGC_GET_LOCALIZED_NAME(language, id, 387);

}

const char* getPokemonNatureName(LanguageIndex language, PokemonNatureIndex index) {
	using namespace Detail::Natures;
	LIBPKMGC_GET_LOCALIZED_NAME(language, index, Quirky);
}

const char* getPokemonMoveName(LanguageIndex language, PokemonMoveIndex index) {
	using namespace Detail::Moves;
	LIBPKMGC_GET_LOCALIZED_NAME(language, index, PsychoBoost);
}
const char* getPokemonAbilityName(LanguageIndex language, PokemonAbilityIndex index) {
	using namespace Detail::Abilities;
	LIBPKMGC_GET_LOCALIZED_NAME(language, index, AirLock);
}

const char* getItemName(LanguageIndex language, ItemIndex index, bool isXD) {
	LIBPKMGC_CHECK_LANG_INDEX(language);
	size_t id = itemIndexToNameIndex(index, isXD);

	if (id < 245) {
		using namespace Detail::GivableItems;
		LIBPKMGC_GET_LOCALIZED_NAME_LIST(language);
		return lst[id];
	}

	if (isXD) {
		using namespace Detail::XDExclusiveItems;
		LIBPKMGC_GET_LOCALIZED_NAME_LIST(language);
		return lst[namesByIndex[id - 245]];
	}
	else {
		using namespace Detail::ColosseumExclusiveItems;
		LIBPKMGC_GET_LOCALIZED_NAME_LIST(language);
		return lst[id - 245];
	}
	return 0;
}


}
}
