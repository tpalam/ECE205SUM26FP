My game will be a recreating of Geometry Dash. It is a simple platformer where a box travels through a map full of player-created obstacles. In fact, the entire map is player created.

So far, inheritance has been implemented using base class Obstacle, to create Spike and various types of Sawblade.

The game also uses game states for the player, defined in Game.h. This is also regarded as a Singleton design pattern since player game state and behavior are managed based on player input (playing the game, paused, and die) rather than implementing them as distinct functions for each state.

Inheritance was also used in the creation of base class PowerUp.

Factory was also used to create the various objects defined in a json file.


In future updates, I plan to create a main menu. From there, there will be a button to open the level editor, and a level selector screen. This will make the game feel much more full.

Challenges faced:
Hand creating the level through the json file. This required me to keep tabs on x and y locations on the coordinate system, balance the obstacles apart so it was not impossible (ex instant death to spike after a inevitable drop from platform, etc.). Since the game levels are all custom, I decided to use a level editor.