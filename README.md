# BatonGuerre #

BatonGuerre is a strategy game with fully customisable campaign.

## How to play ##

BatonGuerre is strongly inspired from the [StickWar](http://www.stickpage.com/stickwargameplay.shtml) game (hence the name).
Basically you need to get ressources, hire soldiers/miners and crush your opponent by destroying his base before he destroys yours.

## Controls

* Send units by clicking on the icons at the top left
* Control a specific group of unit by clicking on the icon while pressing Ctrl then drop the flag where you want all the units of this category to go
* Command all units to attack using the right arrow.
* Command all units to retreat behind your base using the left arrow.

## Installing ##

To install BatonGuerre you need the following :

* Make
* SFML
* CSFML
* gcc

On linux run 
```
sudo apt install libsml-dev libcsfml-dev build-essential && ./release
```
It will produce an executable named battle and launch it.

## Customising campaign ##

* Batonguerre is fully customisable by editing the .json files in the confs directory.

You can change your army configuration in the `base/army.json` file.
You can change the ennemy armies in each level by editing `levels/{level name}/army.json`.

You can change the map configuration in each level by editing `configuration.json`.

To see the details of these files see below.

### Configuration files ###

Every level comes with a `configuration.json` file.

This file describe the general battle configuration, it must contain the following keys : 


| Key | Description | Domain |
| --- | ----------- | ------ |
| map_size | the distance from the ally to the ennemy base | Positive integers |
| ground_pos | The position of the ground on which the units walks | Positive integers |
| player_team | The side of the player's base | 0 or 1 |
| nb_teams | The number of teams | 2 |
| teams | A size 2 list of the teams basic configurations | A list of 2 teams (see below) |
| entities | A list of ennemy entities present on the battlefield at the begining of the game | A list of entities (see below) |
| gold_heaps | The positions of the gold heaps on the map | A list of float |
| gold_heaps_size | The quantity of gold contained in every gold heap | Natural numbers |


The `teams` and `entities` objects must have the following keys 

#### Teams objects

| Key | Description | Domain |
| --- | ----------- | ------ |
| pop | the position of the base | Positive integers |
| gold_start | the available amount of gold at the beginin of the game | Positive integers |
| gold_per_sec | the amount of gold gained every second of the game | Positive integers |
| ai | the name of the ai who controls the army (plyer for the player, dumb for the ennemy) | plyer/dumb |

#### Entities objects

| Key | Description | Domain |
| --- | ----------- | ------ |
| brigade_id | the id of the brigade to which the units belong (index of the brigade in the corresponding `army.json` file | Natural numbers |
| number | the number of units | Positive integers |
| gold_per_sec | the amount of gold gained every second of the game | Positive integers |
| ai | the name of the ai who controls the army (plyer for the player, dumb for the ennemy) | plyer/dumb |


### Army files ###

An army is described by a json containing one object `"brigade"` referencing a list of brigades. Brigades define the units you will be able to hire in the game.

A brigade is described by the following characteristics :

| Key | Description | Domain |
| --- | ----------- | ------ |
| type | the type of unit in this brigade (see below) | mineworker/kicker/ninja/archer |
| cooldown | how much time you have to weit before hiring a second unit of this brigade | Any positive integer |
| cost | how much gold it costs to hire an unit of this brigade | Any positive integer |
| base_life | How much hp does an unit of this brigade have | Any positive integer (zero being possible but useless |
| base_speed | The speed of the units of this brigade | Any natural number |
| random_speed | Adds a random number inferior to this to the speed of every unit in this brigade | Natural numbers |
| base_size | The rendering size of the unit as a coefficient | Positive floats |
| base_armor | The base armor of the units in the brigade, armor is directly substracted from damages taken | Natural numbers |
| range | The range of the basic attacks of the units (for units with multiple ranges see the `archers` below) | Positive integer |
| Additional attributes | Every type of unit has more attributes to configure, see below for the specific attributes | see below |

## Unit types

### Mineworkers

Mineworkers are the only unit capable of harvesting gold. They do so by going to the next gold heap on the map and start filling their bag. When their bag is full they go back to the base to make it available.
It is important to know : 
* Mineworkers cannot attack
* When commanded to attack, mineworkers will just walk to the next gold heap and start mining from it
* When a mineworker reach the base it automaticaly empty its bag, giving you all of its gold even if it was not full. This can be usefull to rapidly earn a lot of gold.

Here are the specific attributes of mineworker that you need to specify in the `army.json` files :

| Key | Description | Domain |
| --- | ----------- | ------ |
| gold harvested | how much gold is harvested from a heap at every movement | Positive integer |
| max_gold | The maximum capacity of the bag | Positive integer |
| harvesting_speed | How much time it takes to make a movement | Positive integers |


### Archers

Mineworkers are the only ranged units, they behave like other attack-based units and will attack on command with the following attacks. 
* Basic ranged attack, the archer shoots an arrow, the arrow will damage the first ennemy it encounters or fall on the ground after a certain time.
* Critical strike, the archer makes a stylish move with the arrow before shooting making it more damaging
* When on low range attack, archer will attack with their arrow, gaining significant speed.

Here are the specific attributes of archers that you need to specify in the `army.json` files :

| Key | Description | Domain |
| --- | ----------- | ------ |
| range_short | the range of short attacks | Positive integer |
| short_range_damage | the damages of the short range hits | Positive integer |
| normal_damage | the damages of the arrows | Positive integer |
| critical_chance | the probability of critical strike (1/n => lower is better) | Positive integer |
| critical_damage | the damages of the critical strikes | Positive integers |
| number_of_arrows | the number of arrows thrown at the same time | Positive integers |
| arrow_speed | the movement speed of the arrows | Positive integers |
| arrow_size | the rendered size of the arrows | Positive floats |
| basic_attack_speed | the time between two attacks (affects both shooting and hitting) | Positive integers |


### Kickers

Mineworkers are the basic fighting unit, they behave like other attack-based units and will attack on command with the following attacks. 
* A quick punch.
* A slower but more powerfull kick

Here are the specific attributes of kickers that you need to specify in the `army.json` files :

| Key | Description | Domain |
| --- | ----------- | ------ |
| punch_damage | the damage dealt by a punch | Positive integer |
| punch_chance | the probability of punching an opponent (higher = less kicks) | Positive integer |
| kick_damage | the damages of the kicks | Positive integer |
| base_attack_speed | the speed of kicks (higher is better) | Positive integer |
| punch_attack_speed | the speed of punch (higher is better) | Positive integers |


### Ninjas

Ninjas are the most deadly fighting unit, they behave like other attack-based units and will attack on command with the following attacks. 
* Hiting with their sword
* Preparing a more precise movement and slashing the enemy.
* When at a medium distance, they will sometimes jump strait on the opponent, closing the distance between them and dealing massive damages on the landing.

Here are the specific attributes of ninjas that you need to specify in the `army.json` files :

| Key | Description | Domain |
| --- | ----------- | ------ |
| hit_chance | the probability of hitting an opponent with a simple hit (higher = less precise hits) | Positive integer |
| hit_damage | the damage dealt by a simple hit | Positive integer |
| slash_damage | the damage of the slashing attacks | Positive integer |
| jump_damage | the damage of a jump attack | Positive integer |
| jump_chance | the probability of jumping on an ennemy (percentage) | Any number between 0 and 100 |
| jump_range | the range of the jump attacks | Any number between 0 and 100 |
| basic_attack_speed | the attack speed of the normal attacks (higher is better) | Any number between 0 and 100 |


## Contributors 

* Graphics & animations : Roland Bertin-Johannet
* Code : Me
