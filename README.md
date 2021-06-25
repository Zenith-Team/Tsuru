# SuperHacks
#### New Super Mario Bros. U Custom Code and ASM
So basically this is just a massive compilation of code hacks for NSMBU, inspired by NewerSMBW, made with extensibility in mind. A lot of stuff here was made by me as I learned how to write hacks, and some of it may not be fully up-to-par, but I tried my test to clean everything up as much as possible. Make sure to also grab the assets pack form the releases page when installing the hacks.
Project started on March 9 2021.

# What's here
## Headers:
I have included as many headers as I could, to minimize the amount of reverse-engineering required for modifying the game for others, and for completeness. There are much too many headers to keep track of, so here is a list of extra actor and actor base headers that are included here, plus some other special ones.
### Actors
* bobomb.h (unfinished)
* boss.h (unfinished)
* bowser.h (unfinished)
* bowserfireball.h
* brosbase.h
* enemy.h (semi-unfinished)
* icicle.h (unfinished)
* itembase.h (todo)
* liquid.h (unfinished)
* player.h (unfinished)
* playerbase.h (unfinished)
* rockywrench.h (unfinished)
* spinningstar.h (unfinished)
* thwomp.h
* windgeneratorbase.h (unfinished)
* yoshi.h (unfinished)
### Special
* dynamic_libs/h264_functions.h
* dynamic_libs/h264_types.h
* terrain.h (unfinished)
* taskmgr.h
## Custom Sprites:
All custom sprites which were not written by me have credits in customsprites.yaml. Also listed there are the sprite/profile IDs of each custom sprite.
* Actor Spawner
* Angry Sun (unfinished)
* Bomb Bro (unfinished)
* Death Foo (very buggy)
* Effect Spawner
* Fake Checkpoint
* Fake Star Coin
* Falling Chestnut (unfinished)
* Fire Thwomp (unfinished)
* Flipblock
* Fly bones
* Magic Platform
* Model loader
* Poison Mushroom (unfinished)
* Time Clock
* Triple Block (unfinished, broken)
* Water Waves (unfinished)
* Water Waves Platform (unfinished, broken)
* Wind generator (unfinished)
## Patches:
Miscellaneous hacks/patches are listed here
* Add archive links for some unused actors to allow adding models
* Customizable snow particle colors
* Customizable world map scripts
* Debug collision viewer
* Disabled acorns falling on title screen
* Disabled Miiverse related popups/menus (unfinished)
* Disabled music speedup at 100 seconds
* Disabled FXAA in-game
* Fixed collision conditions for some sprites
* Restored background offset settings functionality
* Restored drawCircle16Impl and drawCircle32Impl in sead::PrimitiveRendererCafe
* Restored sound effect reverb settings
* RPL library loader
* Sarc level loader
* Size modifier
* Space Physics
* Yoshi colors
* ZLib loader

# Credits
* [AboodXD](https://github.com/aboood40091) - [NSMBU-Haxx](https://github.com/aboood40091/NSMBU-haxx) code and headers
* [Newer Team](https://github.com/Newer-Team) - [Newer U](https://github.com/Newer-Team/NewerSMBU) code and headers
* [RicBent](https://github.com/RicBent) - [CodeDX](https://github.com/RicBent/codedx) code and headers
* [RoadrunnerWMC](https://github.com/RoadrunnerWMC) - Customizable world map scripts
* [STUPID](https://github.com/stupidestmodder) - General code and headers
* Modified dynamic_libs based on original implementation by dimok and [Maschell fork](https://github.com/Maschell/dynamic_libs)
* shiftjis.h from [Apollo PS3](https://github.com/bucanero/apollo-ps3/blob/master/include/shiftjis.h)

# Special Thanks
* JHMaster for helping create tools to assist in reverse engineering
* Joey for helping me set up NSMBU-Haxx when I first started
* STUPID for basically teaching me everything I know about custom code hacks, thank you! <3
* Toms and Kinnay for giving me early access to the Newer U code
