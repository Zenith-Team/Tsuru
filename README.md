# Tsuru

#### Let's build a platform for NSMBU custom code hacks
So basically this is just a massive compilation of code hacks for NSMBU made with scalability, accuracy, and integrity in mind. In addition to the code hacks, there is also a multitude of headers included, to minimize the amount of reverse-engineering required for modifying the game for others. Make sure to also grab the assets pack from the releases page when installing the hacks.
Project started on March 9 2021.

# What's here
Please note that a rewrite is currently in progress, so not everything listed here is available at the moment. **Items with an asterisk next to the name have not been added after the rewrite yet.**

## Custom Sprites:
All custom sprites which were not written by me have credits in customsprites.yaml. Also listed there are the sprite/profile IDs of each custom sprite.

* Actor Spawner
* Angry Sun *
* Beep Block
* Bomb Bro *
* Death Foo *
* Effect Spawner *
* Elemental Thwomp *
* Example World Map Actor
* Fake Actor
* Falling Chestnut
* Flipblock *
* Magic Platform *
* Mini-only door
* Model Loader *
* P-Acorn
* Para-Bones
* Poison Mushroom *
* Star Coin Shard
* Time Clock *
* Triple Block *
* Water Waves *
* Water Waves Platform *
* Wind generator

## Patches:
Miscellaneous hacks/patches are listed here. Most of the game-changing patches are toggleable in the config file located in /include/
* Add archive links for some unused actors to allow adding models *
* Cheat menu to activate cheats and debug settings
* Custom save data manager
* Customizable snow particle colors
* Customizable world map scripts *
* Debug collision viewer for levels and world map
* Disabled acorns falling on title screen
* Disabled Miiverse integration *
* Extra profile slots for up to 64812 new actors
* Fixed collision conditions for some sprites
* Indicator for hacks loaded via version string
* Infinite lives
* Infinite time
* Instant respawn
* NoClip
* Restored background offset settings functionality *
* Restored many of sead::PrimitiveRendererCafe's deleted functions
* Restored sound effect reverb settings
* RPL library loader
* SARC level loader
* Size modifier
* Space physics
* Titlescreen theme based on last world saved in
* Yoshi colors

# Building
This project is meant to be compiled with my fork of shibboleet's fork of the [CafeLoader Project Compiler](https://github.com/Luminyx1/CafeLoader-Compiler) script. A version of this source code that is ready for building will always be available on the [releases](https://github.com/Luminyx1/Tsuru/releases) page which includes additional files required for compiling. Keep in mind that currently this project targets version 1.3.0 of the standalone copy of New Super Mario Bros. U, but does maintain compatibility with the DLC as well. Support for the bundle will be coming soon but as of right now it is not our top priority.

# Credits
* [AboodXD](https://github.com/aboood40091) - [NSMBU-Haxx](https://github.com/aboood40091/NSMBU-haxx) code, headers, and build system
* [jhmaster2000](https://github.com/jhmaster2000) - General code and headers
* [Luminyx](https://github.com/Luminyx1) - Project leader, general code and headers
* [Newer Team](https://github.com/Newer-Team) - [Newer U](https://github.com/Newer-Team/NewerSMBU) code and headers
* [RicBent](https://github.com/RicBent) - [CodeDX](https://github.com/RicBent/codedx) code and headers
* [RoadrunnerWMC](https://github.com/RoadrunnerWMC) - Customizable [world map scripts](https://github.com/RoadrunnerWMC/Cobra)
* [shibboleet](https://github.com/shibbo) - General code, headers, and contribution to the build system
* [STUPID](https://github.com/stupidestmodder) - General code and headers
* Modified dynamic_libs headers based on original implementation by Dimok and [Maschell fork](https://github.com/Maschell/dynamic_libs)
* shiftjis.h from [Apollo PS3](https://github.com/bucanero/apollo-ps3/blob/master/include/shiftjis.h)

# Special Thanks
* Joey0980 for helping me set up CafeLoader when I first started
* STUPID for basically teaching me everything I know about code hacks
* Toms and Kinnay for giving me early access to the Newer U code
