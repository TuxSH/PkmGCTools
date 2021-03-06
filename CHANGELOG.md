###PkmGCTools v1.2.3:
Fixing a problem with japanese characters.

###PkmGCTools v1.2.2:
Few changes this week:
* The PID of a Pokémon can now be displayed either in hexadecimal or in decimal (default: hexadecimal).
* When editing the moves of a Pokémon, Hidden Power's type and base power are now displayed.

I made a guide on how to make legal Pokémon as well. You can find it in the wiki.

###PkmGCTools v1.2.1:
Mostly ergonomic changes:
	* Move names are now displayed next to CTs.
	* Added autocompletion for Pokémon, item, and move combo boxes.
	* Added the following buttons to the Strategy Memo editor: 'Fill memo' (for both Colosseum and XD) and 'Fill memo (all shiny)' (for Colosseum only) buttons .
	* Stats boosted (resp. hindered) by the different natures are now displayed in red (resp. blue).

###PkmGCTools v1.2:
* The interface can now be displayed in **German** (thanks [peterpansexuell](http://www.smogon.com/forums/members/peterpansexuell.158307/) !)
* Updates can now be automatically checked for at startup (this is the default)
* **New features**:
	* Ribbon descriptions can now be modified (7 ribbons are concerned)
	* Pokémon can now be imported/exported from/to Base64 strings
	* On Colosseum, you can now change Rui's name
* Minor changes and bugfixes

###PkmGCTools v1.1.2:
Fixed a bug in XD: the map+script data was being wiped out.
Some refactoring in LibPkmGC.

###PkmGCTools v1.1.1:
Fixed a lot of critical bugs (affecting IVs, etc...). Pokedollars and PokéCoupons are now limited to 9,999,999. Bag items are limited to 99 again in Pokémon Colosseum Fixed a lot of critical bugs (affecting IVs, etc...)
(use the PC storage system to fix bag entries with more than 99 items).

To users of previous versions:
* If and **only** if you have modified a **Colosseum** save file with that previous version, please load this save file again, 
and click "Bugs affecting Pokémon..."(in "Options", "Bug fixes"). **Do it only once and only once** (for each concerned save file).
* If you have imported or exported a Pokémon in the GBA format, please check its status alteration, its EVs, and its game of origin. 

###PkmGCTools v1.1:
* GBA Pokémon are now **fully** supported.
* As a consequence conversion between Colosseum, XD and GBA Pokémon is now **fully** supported. 
	* It is done (almost) exactly like it is in Colosseum/XD during a GC<->GBA trade (meaning, for example, that the data specific to shadow Pokémon is lost).
	* Please note that A-Save discards all party-related information (e.g status alteration). The Devil is in the detail...
* The maximum number for items has been raised to 999.
* Some bug fixes (Strategy Memo edition now working properly etc...).
* PkmGCSaveEditor now has an icon!