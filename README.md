# Blaster
A multiplayer competitive shooter game made using UE5 and C++!
![HighresScreenshot00001](https://github.com/Th3RoadNotTaken/Blaster/assets/34506769/740e9da6-bebb-42bf-b75b-5a136d3f9bf5)

## About the project
I'm creating a competitive shooter which will consist of game modes such as team deathmatch and capture the flag.
* This game will consist of mechanics such as jumping, strafing, and leaning while shooting.
* There will be various types of weapons such as Assault Rifles, SMGs, Shotguns, Rocket Launchers, etc.
* There will also be several pickups throughout the map such as Ammo, Health, Speed & Jump Buffs, and Shield Bars.

## Technical Aspects
* UE5's enhanced input system to implement all player inputs.
* Aim Offsets for updating the character's upper body rotation while aiming at different angles.
* FABRIK - Forward and Backward Inverse Kinematics for adjusting the character's left hand correctly on any gun they hold.
* Implemented several multiplayer networking aspects such as Actor Replication, Rep Notifies, Remote Procedure Calls(RPCs), Conditional Replication, etc.
* Game mode class for defining the rules of the game such as when the player gets eliminated and how to respawn the player.
* Player state class for defining the rules to update player scores and defeats.
* Parameterized material instances for dissolving the character mesh once eliminated.
* HUD elements such as health bars, ammo count, match timers, player scores, etc. 

I'm currently working on creating different weapon types such as Rifles, SMGs, Rocket Launchers, Shotguns, Grenade Launchers, etc.
