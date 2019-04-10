# BatonGuerre #

BatonGuerre is a strategy game with fully customisable campaign.

### How to play ###

BatonGuerre is strongly inspired from the [StickWar](http://www.stickpage.com/stickwargameplay.shtml) game (hence the name).
Basically you need to get ressources, hire soldiers/miners and crush your opponent by destroying his base before he destroys yours.

### Controls

* Send units by clicking on the icons at the top left
* Control a specific group of unit by clicking on the icon while pressing Ctrl then drop the flag where you want all the units of this category to go
* Command all units to attack using the right arrow.
* Command all units to retreat behind your base using the left arrow.

### Installing ###

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

### Customising campaign ###

* Batonguerre is fully customisable by editing the .json files in the confs directory.

You can change your army configuration in the `base/army.json` file.
You can change the ennemy armies in each level by editing `levels/{level name}/army.json`.

You can change the map configuration in each level by editing `configuration.json`.

To see the details of these files see below.

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

## Attributes of  



* Repo owner or admin
* Other community or team contact
