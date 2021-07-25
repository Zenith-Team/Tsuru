# SuperHacks (working title)
#### New Super Mario Bros. U Extension and Hack Framework
So basically this is just a massive compilation of code hacks for NSMBU made with scalability, accuracy, and integrity in mind. Besides the code hacks, there is also a multitude of headers included, to minimize the amount of reverse-engineering required for modifying the game for others. Make sure to also grab the assets pack form the releases page when installing the hacks.
Project started on March 9 2021.

# What's here
Please note that a rewrite is currently in progress, so not everything listed here is available at the moment.
## Headers:
I have included as many headers as I could, to minimize the amount of reverse-engineering required for modifying the game for others, and for completeness. There are much too many headers to keep track of, so here is a list of extra actor and actor base headers that are included here, plus some other special ones.
### Actors
* bobomb.h
* boss.h
* bowser.h
* bowserfireball.h
* brosbase.h
* enemy.h
* icicle.h
* itembase.h
* liquid.h
* player.h
* playerbase.h
* pokey.h
* rockywrench.h
* spinningstar.h
* thwomp.h
* windgeneratorbase.h (unfinished)
* yoshi.h (unfinished)
### Special
* dynlibs/h264/functions.h
* dynlibs/h264/types.h
* terrain.h
* taskmgr.h
## Custom Sprites:
All custom sprites which were not written by me have credits in customsprites.yaml. Also listed there are the sprite/profile IDs of each custom sprite.
* Actor Spawner
* Angry Sun
* Bomb Bro
* Death Foo
* Effect Spawner
* Fake Checkpoint
* Fake Star Coin
* Falling Chestnut
* Fire Thwomp
* Flipblock
* Fly bones
* Magic Platform
* Model loader
* Poison Mushroom
* Time Clock
* Triple Block
* Water Waves
* Water Waves Platform
* Wind generator
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
* Fireproof pokey
* Fixed collision conditions for some sprites
* Infinite lives
* Infinite time
* Restored background offset settings functionality
* Restored drawCircle16Impl and drawCircle32Impl in sead::PrimitiveRendererCafe
* Restored sound effect reverb settings
* RPL library loader
* SARC level loader
* Size modifier
* Space Physics
* Stationary pokey
* Yoshi colors
* ZLib loader

# Credits
* [AboodXD](https://github.com/aboood40091) - [NSMBU-Haxx](https://github.com/aboood40091/NSMBU-haxx) code, headers, and build system
* [Newer Team](https://github.com/Newer-Team) - [Newer U](https://github.com/Newer-Team/NewerSMBU) code and headers
* [RicBent](https://github.com/RicBent) - [CodeDX](https://github.com/RicBent/codedx) code and headers
* [RoadrunnerWMC](https://github.com/RoadrunnerWMC) - Customizable world map scripts
* [Shibboleet](https://github.com/shibbo) - General code, headers, and contribution to the build system
* [STUPID](https://github.com/stupidestmodder) - General code and headers
* Modified dynamic_libs headers based on original implementation by Dimok and [Maschell fork](https://github.com/Maschell/dynamic_libs)
* shiftjis.h from [Apollo PS3](https://github.com/bucanero/apollo-ps3/blob/master/include/shiftjis.h)

# Special Thanks
* Joey0980 for helping me set up NSMBU-Haxx when I first started
* STUPID for basically teaching me everything I know about code hacks
* Toms and Kinnay for giving me early access to the Newer U code
