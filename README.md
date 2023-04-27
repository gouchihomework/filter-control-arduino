# filter-control-arduino

Edits and improvements will be made sporadically. No guarantees it'll work.

04-26-2023: The state machine should work fine - so should the outputs. Can't test it. No idea how the specifics of the MAF work (I'd need the thing and its manual in front of me, alongside a multimeter to poke at it). From what I can gather, it isn't as simple as the code makes it out to be - the MAF ISN'T intended to determine whether air is blowing, or how fast it's blowing. It's intended to show the MASS, and by extension DENSITY, of the air flowing, hence the concern with temperature (lower temperatures = higher density = more air). Since I don't know how it works, I've left the temperature control be for now.