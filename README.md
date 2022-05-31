# <img src="https://media.discordapp.net/attachments/804348227482419230/901215136302395535/tsuru3_small.png" width="64"> Tsuru

#### Let's build a platform for NSMBU custom code hacks

# Our goal
The goal of this project is to provide a platform for New Super Mario Bros. U custom code for modders with the same toolset that Nintendo developers had when writing the game. We also have provided a ton of code examples and premade patches for new modders to learn from and for people who would just like to use them in their own personal mods.
Project started on March 9 2021.

# What's here
Please note that a rewrite is currently in progress, so not everything listed here is available at the moment. **Items with an asterisk next to the name have not been added after the rewrite yet.**

## Custom Sprites:
* Actor Spawner
* Angry Sun/Moon
* Beep Block
* Bomb Bro *
* Cataquack
* Custom Door
* Death Foo
* Debug Helper
* Effect Spawner
* Example World Map Actor
* Fake Actor Collection
* Falling Chestnut
* Flipblock *
* Giant Skewer
* Kamiya
* Liquid Collision Overlay
* Magic Platform *
* Military Cheep
* Model Loader
* P-Acorn (as an in-game actor)
* Para-Bones
* Physics Modifier
* Poison Mushroom *
* RGB Light Source
* Scuttlebug
* Star Coin Shard
* String Bank
* Task Changer
* Time Clock
* Triple Block *
* Universal Boss Controller
* Water Waves
* Wind Generator

## Patches:
Miscellaneous hacks/patches are listed here. Most of the game-changing patches are toggleable in the savefile by hex editing or disabling them in project.yaml
* Add archive links for some unused actors to allow adding models
* ATLYS custom world map system (early alpha)
* Cheat menu to activate cheats and debug settings
* Custom cutscene player
* Custom powerup slots
* Custom save data manager API with an example
* Customizable snow particle colors
* Customizable world map scripts *
* Debug collision viewer for levels and world map
* Disabled acorns falling on title screen
* Disabled Miiverse integration *
* Extra profile slots for up to 64812 new actors
* Fireproof Bowser
* Fixed collision conditions for some sprites
* Fixed framebuffer clearing issue
* Handle some exceptions/errors
* Indicator for hacks loaded via version string *
* Infinite lives
* Infinite time
* Instant respawn
* Integrated crash fix graphics pack
* Load resources for actor spawner automatically
* NoClip
* No powerup from checkpoint
* Projection settings for World Map and Level
* Restored background offset settings functionality
* Restored sound effect reverb settings
* RPL library loader
* SARC level loader
* Size modifier *
* Space physics
* Titlescreen theme based on last world saved in
* World-based titlescreen level theme
* Wrong VF handling
* Yoshi colors

# Contributing
Just create a new Pull Request on the designated page. We will review the PR and accept if we feel that it meets our quality standard and design philosophy. If you have discovered an issue or bug, make an issue on the Issue Tracker. Suggestions can also go there.

# Building
This project is meant to be compiled with a custom version of the CafeLoader Project Compiler script. A version of this source code that is ready for building will always be available on the [releases](https://github.com/Luminyx1/Tsuru/releases) page which includes additional files required for compiling. Keep in mind that currently this project targets version 1.3.0 of the standalone copy of New Super Mario Bros. U, but does maintain compatibility with the DLC as well. Support for the bundle will be coming soon but as of right now it is not our top priority.

# Usage
If you would like to use the hacks from the Tsuru project in your own mods, all you need to do is to include a link to this repository somewhere in the credits of the mod.
If you would like to fork the repo and build upon it, just provide a link to this repository and include the Credits section below in the readme.

# Help
If you require any assistance for anything related to Tsuru, feel free to join our [Discord server](https://discord.gg/PXM34tKQNj) and ask for help in there.

# Credits
* [AboodXD](https://github.com/aboood40091) - [NSMBU-Haxx](https://github.com/aboood40091/NSMBU-haxx) code, headers, and build system
* [Flizl](https://twitter.com/fliizzl) - Graphics
* [iHarv](https://github.com/iHarv) - Quality Assurance
* [jhmaster2000](https://github.com/jhmaster2000) - General code and headers
* [Luminyx](https://github.com/Luminyx1) - Project lead, general code and headers
* [Newer Team](https://github.com/Newer-Team) - [Newer U](https://github.com/Newer-Team/NewerSMBU) code and headers
* [RicBent](https://github.com/RicBent) - [CodeDX](https://github.com/RicBent/codedx) code and headers
* [RoadrunnerWMC](https://github.com/RoadrunnerWMC) - Customizable [world map scripts](https://github.com/RoadrunnerWMC/Cobra)
* [shibboleet](https://github.com/shibbo) - General code, headers, and contribution to the build system
* [STUPID](https://github.com/stupidestmodder) - General code and headers
* [Techmuse](https://twitter.com/techmuse8) - Quality Assurance
* [WillyMaker](https://www.youtube.com/channel/UCBDaY5sapkDhqlBBNJnW-Og) - Sprite data and images
* Modified dynamic_libs headers based on original implementation by [Dimok](https://github.com/dimok789) and [Maschell fork](https://github.com/Maschell/dynamic_libs)
* shiftjis.h from [Apollo PS3](https://github.com/bucanero/apollo-ps3/blob/master/include/shiftjis.h)

# Special Thanks
* Joey for helping me set up CafeLoader when I first started
* Abood and STUPID for basically teaching me everything I know about custom code
* Toms and Kinnay for giving me early access to the Newer U source code
