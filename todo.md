# TODO
refac :
	read conf
	json read int/char/etc...
	ent pointer -> brigade
	team list brigade ent->brigade stop
	upd and evt in state
	game ->battle
	type -> behaviour
	view create with pointer to config ?
mnu :
	state menu
	load
	save
gme :
	armor
	lif bar  when hit
	nnja jmp fix when wrong side stop.
	retrear base
	multiple plyrs:
		plyrs have sides (int)
after :
	comments
	memory leak maybe
	
	
##Toconf
	rename json read elem and put it in utils
	team init with read,
	team contains gld, gps, pop.
	create base in team -> add later to list.
	
	
##Final conf
should look like that :
conf/
    lvls/
        mrmy
        btl/
            rmy
            ent
            btlcnf
    saves/
        btl/
            rmy
            ent
            btlcnf
        rmy
        stts
    bscs/
        ents/
