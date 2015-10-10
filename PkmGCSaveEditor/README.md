#PkmGCSaveEditor
PkmGCSaveEditor is a cross-platform, open source (GPLv3) Pokémon Colosseum and Pokémon XD **save file editor**. It comes with its backend library, LibPkmGC (LPGLv3) (not documented yet).

##Current features:
* You can edit all of your Pokémon, import and export them. You can NOT edit the information specific to Shadow Pokémon, though.
	* You can import/export Pokémon from/to Base64 strings
	* GBA Pokémon are **fully** supported as well.
	* As a consequence conversion between Colosseum, XD and GBA Pokémon is **fully** supported. 
		* It is done (almost) exactly like it is in Colosseum/XD during a GC<->GBA trade (meaning, for example, that the data specific to shadow Pokémon is lost).
		* Please note that A-Save discards all party-related information (e.g status alteration). The Devil is in the detail...
* You can edit your game configuration. In particular, you can change your save language.
* You can edit your trainer info (name, IDs, gender (yes, you can edit it even though it will have no graphical effect :p), money and Pokécoupons), your bag and your Party.
* You can edit your PC (both Pokémon and items).
* You can edit your Daycare.
* You can edit your Strategy Memo.
* You can edit the description of some ribbons
* On XD, you can edit your Purifier.

###Additional features not in PkmGCSaveEditor, but *partially* supported by the backend library **only**: 
Editing your Mailbox and your Battle Mode data.

##Supported languages:
* Interface: English, French, German
* Dumped names (thanks [Tiddlywinks](http://projectpokemon.org/forums/showthread.php?46253-Stars-Pokemon-colosseum-and-XD-hacking-tutorial-part-2-Text-editing&p=205271&viewfull=1#post205271)!): English, French, German, Spanish, Italian, Japanese

##Special thanks to:
peterpansexuall (German translation), Yago (testing), Ralf (for his "offset tables"), StarsMMD, Tiddlywinks.

_Tips_: The most recent versions of Dolphin (e.g. 5.0-rc) can directly read and write to GCI files, making testing your changes much easier.
You can dump/restore your physical memory card contents using Ctr-Gcs-DacoTaco-Edition.
