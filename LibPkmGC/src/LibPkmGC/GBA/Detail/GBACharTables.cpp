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

#include <LibPkmGC/GBA/Detail/GBACharTables.h>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap.hpp>

namespace LibPkmGC {

namespace Detail {

typedef boost::bimap< boost::bimaps::unordered_set_of<u8>, boost::bimaps::unordered_set_of<u32> > chartable_t;
typedef chartable_t::value_type charset_t;

inline chartable_t initEurCharTable(void) {
	// Some characters have no Unicode equivalents
	chartable_t tbl;
	tbl.insert(charset_t(0x00, 0x0020));
	tbl.insert(charset_t(0x01, 0x00C0));
	tbl.insert(charset_t(0x02, 0x00C1));
	tbl.insert(charset_t(0x03, 0x00C2));
	tbl.insert(charset_t(0x04, 0x00C7));
	tbl.insert(charset_t(0x05, 0x00C8));
	tbl.insert(charset_t(0x06, 0x00C9));
	tbl.insert(charset_t(0x07, 0x00CA));
	tbl.insert(charset_t(0x08, 0x00CB));
	tbl.insert(charset_t(0x09, 0x00CC));
	tbl.insert(charset_t(0x0B, 0x00CE));
	tbl.insert(charset_t(0x0C, 0x00CF));
	tbl.insert(charset_t(0x0D, 0x00D2));
	tbl.insert(charset_t(0x0E, 0x00D3));
	tbl.insert(charset_t(0x0F, 0x00D4));
	tbl.insert(charset_t(0x10, 0x0152));
	tbl.insert(charset_t(0x11, 0x00D9));
	tbl.insert(charset_t(0x12, 0x00DA));
	tbl.insert(charset_t(0x13, 0x00DB));
	tbl.insert(charset_t(0x14, 0x00D1));
	tbl.insert(charset_t(0x15, 0x00DF));
	tbl.insert(charset_t(0x16, 0x00E0));
	tbl.insert(charset_t(0x17, 0x00E1));
	tbl.insert(charset_t(0x19, 0x00E7));
	tbl.insert(charset_t(0x1A, 0x00E8));
	tbl.insert(charset_t(0x1B, 0x00E9));
	tbl.insert(charset_t(0x1C, 0x00EA));
	tbl.insert(charset_t(0x1D, 0x00EB));
	tbl.insert(charset_t(0x1E, 0x00EC));
	tbl.insert(charset_t(0x20, 0x00EE));
	tbl.insert(charset_t(0x21, 0x00EF));
	tbl.insert(charset_t(0x22, 0x00F2));
	tbl.insert(charset_t(0x23, 0x00F3));
	tbl.insert(charset_t(0x24, 0x00F4));
	tbl.insert(charset_t(0x25, 0x0153));
	tbl.insert(charset_t(0x26, 0x00F9));
	tbl.insert(charset_t(0x27, 0x00FA));
	tbl.insert(charset_t(0x28, 0x00FB));
	tbl.insert(charset_t(0x29, 0x00F1));
	tbl.insert(charset_t(0x2A, 0x00BA));
	tbl.insert(charset_t(0x2B, 0x01AA));
	tbl.insert(charset_t(0x2D, 0x0026));
	tbl.insert(charset_t(0x2E, 0x002B));
	tbl.insert(charset_t(0x35, 0x003D));
	tbl.insert(charset_t(0x36, 0x003B));
	tbl.insert(charset_t(0x50, 0x25AF));
	tbl.insert(charset_t(0x51, 0x00BF));
	tbl.insert(charset_t(0x52, 0x00A1));
	tbl.insert(charset_t(0x5A, 0x00CD));
	tbl.insert(charset_t(0x5B, 0x0025));
	tbl.insert(charset_t(0x5C, 0x0028));
	tbl.insert(charset_t(0x5D, 0x0029));
	tbl.insert(charset_t(0x68, 0x00E2));
	tbl.insert(charset_t(0x6F, 0x00ED));
	tbl.insert(charset_t(0x79, 0x2191));
	tbl.insert(charset_t(0x7A, 0x2193));
	tbl.insert(charset_t(0x7B, 0x2190));
	tbl.insert(charset_t(0x7C, 0x2192));
	tbl.insert(charset_t(0x85, 0x003C));
	tbl.insert(charset_t(0x86, 0x003E));
	tbl.insert(charset_t(0xA1, 0x0030));
	tbl.insert(charset_t(0xA2, 0x0031));
	tbl.insert(charset_t(0xA3, 0x0032));
	tbl.insert(charset_t(0xA4, 0x0033));
	tbl.insert(charset_t(0xA5, 0x0034));
	tbl.insert(charset_t(0xA6, 0x0035));
	tbl.insert(charset_t(0xA7, 0x0036));
	tbl.insert(charset_t(0xA8, 0x0037));
	tbl.insert(charset_t(0xA9, 0x0038));
	tbl.insert(charset_t(0xAA, 0x0039));
	tbl.insert(charset_t(0xAB, 0x0021));
	tbl.insert(charset_t(0xAC, 0x003F));
	tbl.insert(charset_t(0xAD, 0x002E));
	tbl.insert(charset_t(0xAE, 0x002D));
	tbl.insert(charset_t(0xAF, 0x00B7));
	tbl.insert(charset_t(0xB0, 0x2026));
	tbl.insert(charset_t(0xB1, 0x00AB));
	tbl.insert(charset_t(0xB2, 0x00BB));
	tbl.insert(charset_t(0xB3, 0x2018));
	tbl.insert(charset_t(0xB4, 0x2019));
	tbl.insert(charset_t(0xB5, 0x2642));
	tbl.insert(charset_t(0xB6, 0x2640));
	tbl.insert(charset_t(0xB7, 0x0024));
	tbl.insert(charset_t(0xB8, 0x002C));
	tbl.insert(charset_t(0xB9, 0x00D7));
	tbl.insert(charset_t(0xBA, 0x002F));
	tbl.insert(charset_t(0xBB, 0x0041));
	tbl.insert(charset_t(0xBC, 0x0042));
	tbl.insert(charset_t(0xBD, 0x0043));
	tbl.insert(charset_t(0xBE, 0x0044));
	tbl.insert(charset_t(0xBF, 0x0045));
	tbl.insert(charset_t(0xC0, 0x0046));
	tbl.insert(charset_t(0xC1, 0x0047));
	tbl.insert(charset_t(0xC2, 0x0048));
	tbl.insert(charset_t(0xC3, 0x0049));
	tbl.insert(charset_t(0xC4, 0x004A));
	tbl.insert(charset_t(0xC5, 0x004B));
	tbl.insert(charset_t(0xC6, 0x004C));
	tbl.insert(charset_t(0xC7, 0x004D));
	tbl.insert(charset_t(0xC8, 0x004E));
	tbl.insert(charset_t(0xC9, 0x004F));
	tbl.insert(charset_t(0xCA, 0x0050));
	tbl.insert(charset_t(0xCB, 0x0051));
	tbl.insert(charset_t(0xCC, 0x0052));
	tbl.insert(charset_t(0xCD, 0x0053));
	tbl.insert(charset_t(0xCE, 0x0054));
	tbl.insert(charset_t(0xCF, 0x0055));
	tbl.insert(charset_t(0xD0, 0x0056));
	tbl.insert(charset_t(0xD1, 0x0057));
	tbl.insert(charset_t(0xD2, 0x0058));
	tbl.insert(charset_t(0xD3, 0x0059));
	tbl.insert(charset_t(0xD4, 0x005A));
	tbl.insert(charset_t(0xD5, 0x0061));
	tbl.insert(charset_t(0xD6, 0x0062));
	tbl.insert(charset_t(0xD7, 0x0063));
	tbl.insert(charset_t(0xD8, 0x0064));
	tbl.insert(charset_t(0xD9, 0x0065));
	tbl.insert(charset_t(0xDA, 0x0066));
	tbl.insert(charset_t(0xDB, 0x0067));
	tbl.insert(charset_t(0xDC, 0x0068));
	tbl.insert(charset_t(0xDD, 0x0069));
	tbl.insert(charset_t(0xDE, 0x006A));
	tbl.insert(charset_t(0xDF, 0x006B));
	tbl.insert(charset_t(0xE0, 0x006C));
	tbl.insert(charset_t(0xE1, 0x006D));
	tbl.insert(charset_t(0xE2, 0x006E));
	tbl.insert(charset_t(0xE3, 0x006F));
	tbl.insert(charset_t(0xE4, 0x0070));
	tbl.insert(charset_t(0xE5, 0x0071));
	tbl.insert(charset_t(0xE6, 0x0072));
	tbl.insert(charset_t(0xE7, 0x0073));
	tbl.insert(charset_t(0xE8, 0x0074));
	tbl.insert(charset_t(0xE9, 0x0075));
	tbl.insert(charset_t(0xEA, 0x0076));
	tbl.insert(charset_t(0xEB, 0x0077));
	tbl.insert(charset_t(0xEC, 0x0078));
	tbl.insert(charset_t(0xED, 0x0079));
	tbl.insert(charset_t(0xEE, 0x007A));
	tbl.insert(charset_t(0xEF, 0x2023));
	tbl.insert(charset_t(0xF0, 0x003A));
	tbl.insert(charset_t(0xF1, 0x00C4));
	tbl.insert(charset_t(0xF2, 0x00D6));
	tbl.insert(charset_t(0xF3, 0x00DC));
	tbl.insert(charset_t(0xF4, 0x00E4));
	tbl.insert(charset_t(0xF5, 0x00F6));
	tbl.insert(charset_t(0xF6, 0x00FC));

	//F7 ... FF : commands

	return tbl;
}

inline chartable_t initJapCharTable(void) {
	chartable_t tbl;

	tbl.insert(charset_t(0x00, 0x3000));
	//----------------------------------------------------------
	//	Medium-sized hirgananas
	//----------------------------------------------------------
	tbl.insert(charset_t(0x01, 0x3042));
	tbl.insert(charset_t(0x02, 0x3044));
	tbl.insert(charset_t(0x03, 0x3046));
	tbl.insert(charset_t(0x04, 0x3048));
	tbl.insert(charset_t(0x05, 0x304A));
	tbl.insert(charset_t(0x06, 0x304B));
	tbl.insert(charset_t(0x07, 0x304D));
	tbl.insert(charset_t(0x08, 0x304F));
	tbl.insert(charset_t(0x09, 0x3051));
	tbl.insert(charset_t(0x0A, 0x3053));
	tbl.insert(charset_t(0x0B, 0x3055));
	tbl.insert(charset_t(0x0C, 0x3057));
	tbl.insert(charset_t(0x0D, 0x3059));
	tbl.insert(charset_t(0x0E, 0x305B));
	tbl.insert(charset_t(0x0F, 0x305D));
	tbl.insert(charset_t(0x10, 0x305F));
	tbl.insert(charset_t(0x11, 0x3061));
	tbl.insert(charset_t(0x12, 0x3064));
	tbl.insert(charset_t(0x13, 0x3066));
	tbl.insert(charset_t(0x14, 0x3068));
	tbl.insert(charset_t(0x15, 0x306A));
	tbl.insert(charset_t(0x16, 0x306B));
	tbl.insert(charset_t(0x17, 0x306C));
	tbl.insert(charset_t(0x18, 0x306D));
	tbl.insert(charset_t(0x19, 0x306E));
	tbl.insert(charset_t(0x1A, 0x307F));
	tbl.insert(charset_t(0x1B, 0x3072));
	tbl.insert(charset_t(0x1C, 0x3075));
	tbl.insert(charset_t(0x1D, 0x3078));
	tbl.insert(charset_t(0x1E, 0x307B));
	tbl.insert(charset_t(0x1F, 0x307E));
	tbl.insert(charset_t(0x20, 0x307F));
	tbl.insert(charset_t(0x21, 0x3080));
	tbl.insert(charset_t(0x22, 0x3081));
	tbl.insert(charset_t(0x23, 0x3082));
	tbl.insert(charset_t(0x24, 0x3084));
	tbl.insert(charset_t(0x25, 0x3086));
	tbl.insert(charset_t(0x26, 0x3088));
	tbl.insert(charset_t(0x27, 0x3089));
	tbl.insert(charset_t(0x28, 0x308A));
	tbl.insert(charset_t(0x29, 0x308B));
	tbl.insert(charset_t(0x2A, 0x308C));
	tbl.insert(charset_t(0x2B, 0x308D));
	tbl.insert(charset_t(0x2C, 0x308F));
	tbl.insert(charset_t(0x2D, 0x3092));
	tbl.insert(charset_t(0x2E, 0x3093));
	//--------------------------------------------------------
	//	Small-sized hiraganas
	//--------------------------------------------------------
	tbl.insert(charset_t(0x2F, 0x3041));
	tbl.insert(charset_t(0x30, 0x3043));
	tbl.insert(charset_t(0x31, 0x3045));
	tbl.insert(charset_t(0x32, 0x3047));
	tbl.insert(charset_t(0x33, 0x3049));
	tbl.insert(charset_t(0x34, 0x3083));
	tbl.insert(charset_t(0x35, 0x3085));
	tbl.insert(charset_t(0x36, 0x3087));
	//------------------------------------------------------------
	//	Medium-sized hiraganas with dakuten
	//------------------------------------------------------------
	tbl.insert(charset_t(0x37, 0x304C));
	tbl.insert(charset_t(0x38, 0x304E));
	tbl.insert(charset_t(0x39, 0x3050));
	tbl.insert(charset_t(0x3A, 0x3052));
	tbl.insert(charset_t(0x3B, 0x3054));
	tbl.insert(charset_t(0x3C, 0x3056));
	tbl.insert(charset_t(0x3D, 0x3058));
	tbl.insert(charset_t(0x3E, 0x305A));
	tbl.insert(charset_t(0x3F, 0x305C));
	tbl.insert(charset_t(0x40, 0x305E));
	tbl.insert(charset_t(0x41, 0x3060));
	tbl.insert(charset_t(0x42, 0x3062));
	tbl.insert(charset_t(0x43, 0x3065));
	tbl.insert(charset_t(0x44, 0x3067));
	tbl.insert(charset_t(0x45, 0x3069));
	tbl.insert(charset_t(0x46, 0x3070));
	tbl.insert(charset_t(0x47, 0x3073));
	tbl.insert(charset_t(0x48, 0x3076));
	tbl.insert(charset_t(0x49, 0x3079));
	tbl.insert(charset_t(0x4A, 0x307C));
	//----------------------------------------------------------
	//	Medium-sized hiraganas with handakuten
	//----------------------------------------------------------
	tbl.insert(charset_t(0x4B, 0x3071));
	tbl.insert(charset_t(0x4C, 0x3074));
	tbl.insert(charset_t(0x4D, 0x3077));
	tbl.insert(charset_t(0x4E, 0x307A));
	tbl.insert(charset_t(0x4F, 0x307D));
	//--------------------------------------------------------
	//	Small-sized hiragana
	//--------------------------------------------------------
		tbl.insert(charset_t(0x50, 0x3063));
	//----------------------------------------------------------
	//	Medium-sized katakanas
	//----------------------------------------------------------
	tbl.insert(charset_t(0x51, 0x30A2));
	tbl.insert(charset_t(0x52, 0x30A4));
	tbl.insert(charset_t(0x53, 0x30A6));
	tbl.insert(charset_t(0x54, 0x30A8));
	tbl.insert(charset_t(0x55, 0x30AA));
	tbl.insert(charset_t(0x56, 0x30AB));
	tbl.insert(charset_t(0x57, 0x30AD));
	tbl.insert(charset_t(0x58, 0x30AF));
	tbl.insert(charset_t(0x59, 0x30B1));
	tbl.insert(charset_t(0x5A, 0x30B3));
	tbl.insert(charset_t(0x5B, 0x30B5));
	tbl.insert(charset_t(0x5C, 0x30B7));
	tbl.insert(charset_t(0x5D, 0x30B9));
	tbl.insert(charset_t(0x5E, 0x30BB));
	tbl.insert(charset_t(0x5F, 0x30BD));
	tbl.insert(charset_t(0x60, 0x30BF));
	tbl.insert(charset_t(0x61, 0x30C1));
	tbl.insert(charset_t(0x62, 0x30C4));
	tbl.insert(charset_t(0x63, 0x30C6));
	tbl.insert(charset_t(0x64, 0x30C8));
	tbl.insert(charset_t(0x65, 0x30CA));
	tbl.insert(charset_t(0x66, 0x30CB));
	tbl.insert(charset_t(0x67, 0x30CC));
	tbl.insert(charset_t(0x68, 0x30CD));
	tbl.insert(charset_t(0x69, 0x30CE));
	tbl.insert(charset_t(0x6A, 0x30CF));
	tbl.insert(charset_t(0x6B, 0x30D2));
	tbl.insert(charset_t(0x6C, 0x30D5));
	tbl.insert(charset_t(0x6D, 0x30D8));
	tbl.insert(charset_t(0x6E, 0x30DB));
	tbl.insert(charset_t(0x6F, 0x30DE));
	tbl.insert(charset_t(0x70, 0x30DF));
	tbl.insert(charset_t(0x71, 0x30E0));
	tbl.insert(charset_t(0x72, 0x30E1));
	tbl.insert(charset_t(0x73, 0x30E2));
	tbl.insert(charset_t(0x74, 0x30E4));
	tbl.insert(charset_t(0x75, 0x30E6));
	tbl.insert(charset_t(0x76, 0x30E8));
	tbl.insert(charset_t(0x77, 0x30E9));
	tbl.insert(charset_t(0x78, 0x30EA));
	tbl.insert(charset_t(0x79, 0x30EB));
	tbl.insert(charset_t(0x7A, 0x30EC));
	tbl.insert(charset_t(0x7B, 0x30ED));
	tbl.insert(charset_t(0x7C, 0x30EF));
	tbl.insert(charset_t(0x7D, 0x30F2));
	tbl.insert(charset_t(0x7E, 0x30F3));
	//----------------------------------------------------------
	//	Small-sized katakanas
	//----------------------------------------------------------
	tbl.insert(charset_t(0x7F, 0x30A1));
	tbl.insert(charset_t(0x80, 0x30A3));
	tbl.insert(charset_t(0x81, 0x30A5));
	tbl.insert(charset_t(0x82, 0x30A7));
	tbl.insert(charset_t(0x83, 0x30A9));
	tbl.insert(charset_t(0x84, 0x30E3));
	tbl.insert(charset_t(0x85, 0x30E5));
	tbl.insert(charset_t(0x86, 0x30E7));
	//------------------------------------------------------------
	//	Medium-sized katakanas with dakuten
	//------------------------------------------------------------
	tbl.insert(charset_t(0x87, 0x30AC));
	tbl.insert(charset_t(0x88, 0x30AE));
	tbl.insert(charset_t(0x89, 0x30B0));
	tbl.insert(charset_t(0x8A, 0x30B2));
	tbl.insert(charset_t(0x8B, 0x30B4));
	tbl.insert(charset_t(0x8C, 0x30B6));
	tbl.insert(charset_t(0x8D, 0x30B8));
	tbl.insert(charset_t(0x8E, 0x30BA));
	tbl.insert(charset_t(0x8F, 0x30BC));
	tbl.insert(charset_t(0x90, 0x30BE));
	tbl.insert(charset_t(0x91, 0x30C0));
	tbl.insert(charset_t(0x92, 0x30C2));
	tbl.insert(charset_t(0x93, 0x30C5));
	tbl.insert(charset_t(0x94, 0x30C7));
	tbl.insert(charset_t(0x95, 0x30C9));
	tbl.insert(charset_t(0x96, 0x30D0));
	tbl.insert(charset_t(0x97, 0x30D3));
	tbl.insert(charset_t(0x98, 0x30D6));
	tbl.insert(charset_t(0x99, 0x30D9));
	tbl.insert(charset_t(0x9A, 0x30DC));
	//------------------------------------------------------------
	//	Medium-sized katakanas with handakuten
	//------------------------------------------------------------
	tbl.insert(charset_t(0x9B, 0x30D1));
	tbl.insert(charset_t(0x9C, 0x30D4));
	tbl.insert(charset_t(0x9D, 0x30D7));
	tbl.insert(charset_t(0x9E, 0x30DA));
	tbl.insert(charset_t(0x9F, 0x30DD));
	//------------------------------------------------------------
	//	Small-sized katakana
	//------------------------------------------------------------
	tbl.insert(charset_t(0xA0, 0x30C3));
	//--------------------------------------------------------------------------------------------------
	//	Full-width Roman characters (or equivalent), ideographic characters,
	//	and other common symbols
	//--------------------------------------------------------------------------------------------------
	tbl.insert(charset_t(0xA1, 0xFF10));
	tbl.insert(charset_t(0xA2, 0xFF11));
	tbl.insert(charset_t(0xA3, 0xFF12));
	tbl.insert(charset_t(0xA4, 0xFF13));
	tbl.insert(charset_t(0xA5, 0xFF14));
	tbl.insert(charset_t(0xA6, 0xFF15));
	tbl.insert(charset_t(0xA7, 0xFF16));
	tbl.insert(charset_t(0xA8, 0xFF17));
	tbl.insert(charset_t(0xA9, 0xFF18));
	tbl.insert(charset_t(0xAA, 0xFF19));
	tbl.insert(charset_t(0xAB, 0xFF01));
	tbl.insert(charset_t(0xAC, 0xFF1F));
	tbl.insert(charset_t(0xAD, 0x3002));
	tbl.insert(charset_t(0xAE, 0x30FC));
	tbl.insert(charset_t(0xAF, 0x30FB));
	tbl.insert(charset_t(0xB0, 0x2025));
	tbl.insert(charset_t(0xB1, 0x300E));
	tbl.insert(charset_t(0xB2, 0x300F));
	tbl.insert(charset_t(0xB3, 0x300C));
	tbl.insert(charset_t(0xB4, 0x300D));
	tbl.insert(charset_t(0xB5, 0x2642));
	tbl.insert(charset_t(0xB6, 0x2640));
	tbl.insert(charset_t(0xB7, 0x5186));
	tbl.insert(charset_t(0xB8, 0xFF0E));
	tbl.insert(charset_t(0xB9, 0x00D7));
	tbl.insert(charset_t(0xBA, 0xFF0F));
	tbl.insert(charset_t(0xBB, 0xFF21));
	tbl.insert(charset_t(0xBC, 0xFF22));
	tbl.insert(charset_t(0xBD, 0xFF23));
	tbl.insert(charset_t(0xBE, 0xFF24));
	tbl.insert(charset_t(0xBF, 0xFF25));
	tbl.insert(charset_t(0xC0, 0xFF26));
	tbl.insert(charset_t(0xC1, 0xFF27));
	tbl.insert(charset_t(0xC2, 0xFF28));
	tbl.insert(charset_t(0xC3, 0xFF29));
	tbl.insert(charset_t(0xC4, 0xFF2A));
	tbl.insert(charset_t(0xC5, 0xFF2B));
	tbl.insert(charset_t(0xC6, 0xFF2C));
	tbl.insert(charset_t(0xC7, 0xFF2D));
	tbl.insert(charset_t(0xC8, 0xFF2E));
	tbl.insert(charset_t(0xC9, 0xFF2F));
	tbl.insert(charset_t(0xCA, 0xFF30));
	tbl.insert(charset_t(0xCB, 0xFF31));
	tbl.insert(charset_t(0xCC, 0xFF32));
	tbl.insert(charset_t(0xCD, 0xFF33));
	tbl.insert(charset_t(0xCE, 0xFF34));
	tbl.insert(charset_t(0xCF, 0xFF35));
	tbl.insert(charset_t(0xD0, 0xFF36));
	tbl.insert(charset_t(0xD1, 0xFF37));
	tbl.insert(charset_t(0xD2, 0xFF38));
	tbl.insert(charset_t(0xD3, 0xFF39));
	tbl.insert(charset_t(0xD4, 0xFF3A));
	tbl.insert(charset_t(0xD5, 0xFF41));
	tbl.insert(charset_t(0xD6, 0xFF42));
	tbl.insert(charset_t(0xD7, 0xFF43));
	tbl.insert(charset_t(0xD8, 0xFF44));
	tbl.insert(charset_t(0xD9, 0xFF45));
	tbl.insert(charset_t(0xDA, 0xFF46));
	tbl.insert(charset_t(0xDB, 0xFF47));
	tbl.insert(charset_t(0xDC, 0xFF48));
	tbl.insert(charset_t(0xDD, 0xFF49));
	tbl.insert(charset_t(0xDE, 0xFF4A));
	tbl.insert(charset_t(0xDF, 0xFF4B));
	tbl.insert(charset_t(0xE0, 0xFF4C));
	tbl.insert(charset_t(0xE1, 0xFF4D));
	tbl.insert(charset_t(0xE2, 0xFF4E));
	tbl.insert(charset_t(0xE3, 0xFF4F));
	tbl.insert(charset_t(0xE4, 0xFF50));
	tbl.insert(charset_t(0xE5, 0xFF51));
	tbl.insert(charset_t(0xE6, 0xFF52));
	tbl.insert(charset_t(0xE7, 0xFF53));
	tbl.insert(charset_t(0xE8, 0xFF54));
	tbl.insert(charset_t(0xE9, 0xFF55));
	tbl.insert(charset_t(0xEA, 0xFF56));
	tbl.insert(charset_t(0xEB, 0xFF57));
	tbl.insert(charset_t(0xEC, 0xFF58));
	tbl.insert(charset_t(0xED, 0xFF59));
	tbl.insert(charset_t(0xEE, 0xFF5A));
	//--------------------------------------------------------------------------------------------------
	//Symbols and accentued (fullwidth in-game) roman characters
	//--------------------------------------------------------------------------------------------------
	tbl.insert(charset_t(0xEF, 0x25BA));
	tbl.insert(charset_t(0xF0, 0xFF1A));
	tbl.insert(charset_t(0xF1, 0x00C4));
	tbl.insert(charset_t(0xF2, 0x00D6));
	tbl.insert(charset_t(0xF3, 0x00DC));
	tbl.insert(charset_t(0xF4, 0x00E4));
	tbl.insert(charset_t(0xF5, 0x00F6));
	tbl.insert(charset_t(0xF6, 0x00FC));

	return tbl;
}

static const chartable_t eurCharTable = initEurCharTable(), japCharTable = initJapCharTable();

u32 GBAToUCS4(u8 val, bool jp, u32 deflt) {
	if (jp && deflt == '?') deflt = 0xff1f; // (fullwidth)
	chartable_t const& tbl = (jp) ? japCharTable : eurCharTable;
	chartable_t::left_const_iterator it = tbl.left.find(val);
	return (it == tbl.left.end()) ? deflt : it->get_right();
}

u8 UCS4ToGBA(u32 val, bool jp, u8 deflt) {
	chartable_t const& tbl = (jp) ? japCharTable : eurCharTable;
	chartable_t::right_const_iterator it = tbl.right.find(val);
	return (it == tbl.right.end()) ? deflt : it->get_left();
}

}
}