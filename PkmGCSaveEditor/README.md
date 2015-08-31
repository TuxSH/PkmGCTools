#PkmGCSaveEditor
PkmGCSaveEditor is a cross-platform, open source (GPLv3) Pokémon Colosseum and Pokémon XD **save file editor**. It comes with its backend library, LibPkmGC (LPGLv3) (not documented yet).

##Current features:
* You can edit all of your Pokémon. You can import and export them as well, including from Colosseum to XD and vice-versa. You can edit the information specific to Shadow Pokémon, though.
* You can edit your game configuration. In particular, you can change your save language.
* You can edit your trainer info (name, IDs, gender (!), money and Pokécoupons), your bag and your Party.
* You can edit your PC (both Pokémon and items).
* You can edit your Daycare.
* You can edit your Strategy Memo.
* On XD, you can edit your Purifier.

###Additional features *partially* supported by the backend library **only**: 
Editing your Mailbox and your Battle Mode data.

##Supported languages:
* Interface: English, French
* Dumped names (thanks [Tiddlywinks](http://projectpokemon.org/forums/showthread.php?46253-Stars-Pokemon-colosseum-and-XD-hacking-tutorial-part-2-Text-editing&p=205271&viewfull=1#post205271)!): English, French, German, Spanish, Italian, Japanese

##Special thanks to:
Ralf (for his "offset tables"), StarsMMD, Tiddlywinks.

_Tips_: The most recent versions of Dolphin (e.g. 5.0-rc) can directly read and write to GCI files, making testing your changes much easier.
You can dump/restore your physical memory card contents using Ctr-Gcs-DacoTaco-Edition.
