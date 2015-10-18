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

#include <LibPkmGC/Core/Detail/TypeNames.h>

namespace LibPkmGC {
namespace Localization {
namespace Detail {

namespace Types {

const char **names[7] = { NULL, japaneseNames, englishNames, germanNames, frenchNames, italianNames, spanishNames };

const char* englishNames[18] = {
	"NORMAL",
	"FIRE",
	"WATER",
	"ELECTR",
	"GRASS",
	"ICE",
	"FIGHT",
	"POISON",
	"GROUND",
	"FLYING",
	"PSYCHC",
	"BUG",
	"ROCK",
	"GHOST",
	"DRAGON",
	"DARK",
	"STEEL",
	"?",
};

const char* frenchNames[18] = {
	"NORMAL",
	"FEU",
	"EAU",
	"ELECTR",
	"PLANTE",
	"GLACE",
	"COMBAT",
	"POISON",
	"SOL",
	"VOL",
	"PSY",
	"INSECT",
	"ROCHE",
	"SPECTR",
	"DRAGON",
	"TENEBR",
	"ACIER",
	"?",
};

const char* germanNames[18] = {
	"NORMAL",
	"FEUER",
	"WASSER",
	"ELEK.",
	"PFLAN.",
	"EIS",
	"KAMPF",
	"GIFT",
	"BODEN",
	"FLUG",
	"PSYCHO",
	"K\xC3\x84""FER",
	"GEST.",
	"GEIST",
	"DRACH.",
	"UNL.",
	"STAHL",
	"?",
};

const char* italianNames[18] = {
	"NORMALE",
	"FUOCO",
	"ACQUA",
	"ELETTRO",
	"ERBA",
	"GHIACCIO",
	"LOTTA",
	"VELENO",
	"TERRA",
	"VOLANTE",
	"PSICO",
	"COLEOTT.",
	"ROCCIA",
	"SPETTRO",
	"DRAGO",
	"BUIO",
	"ACCIAIO",
	"?",
};

const char* spanishNames[18] = {
	"NORMAL",
	"FUEGO",
	"AGUA",
	"EL\xC3\x89""CT.",
	"PLANTA",
	"HIELO",
	"LUCHA",
	"VENENO",
	"TIERRA",
	"VOLAD.",
	"PS\xC3\x8DQ.",
	"BICHO",
	"ROCA",
	"FANT.",
	"DRAG\xC3\x93N",
	"SINIE.",
	"ACERO",
	"(?)",
};

const char* japaneseNames[18] = {
	"\xe3\x83\x8e\xe3\x83\xbc\xe3\x83\x9e\xe3\x83\xab",
	"\xe3\x81\xbb\xe3\x81\xae\xe3\x81\x8a",
	"\xe3\x81\xbf\xe3\x81\x9a",
	"\xe3\x81\xa7\xe3\x82\x93\xe3\x81\x8d",
	"\xe3\x81\x8f\xe3\x81\x95",
	"\xe3\x81\x93\xe3\x81\x8a\xe3\x82\x8a",
	"\xe3\x81\x8b\xe3\x81\x8f\xe3\x81\xa8\xe3\x81\x86",
	"\xe3\x81\xa9\xe3\x81\x8f",
	"\xe3\x81\x98\xe3\x82\x81\xe3\x82\x93",
	"\xe3\x81\xb2\xe3\x81\x93\xe3\x81\x86",
	"\xe3\x82\xa8\xe3\x82\xb9\xe3\x83\x91\xe3\x83\xbc",
	"\xe3\x82\x80\xe3\x81\x97",
	"\xe3\x81\x84\xe3\x82\x8f",
	"\xe3\x82\xb4\xe3\x83\xbc\xe3\x82\xb9\xe3\x83\x88",
	"\xe3\x83\x89\xe3\x83\xa9\xe3\x82\xb4\xe3\x83\xb3",
	"\xe3\x81\x82\xe3\x81\x8f",
	"\xe3\x81\xaf\xe3\x81\x8c\xe3\x81\xad",
	"\xef\xbc\x9f",
};

}
}
}
}