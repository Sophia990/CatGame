### Escape the Wild

In Escape the Wild, you are a stray cat, struggling to survive in the forest. You must constantly hunt chickens and avoid dogs just to stay alive. You want to break free of this lifestyle, but how?

Download and play game: https://sophia990.itch.io/escape-the-wild

Requirements to open project: Unreal Engine 5.6, Git LFS

In this game, I have purposefully left the player with very little information, in order to encourage them to enjoy exploring and figuring out the mechanics of the game themselves. The controls give some hints, and the fullness bar is left unexplained but visible; otherwise, you must discover the world yourself. However, if you would like a summary of the mechanics, please read the section below.

**Mechanics and Gameplay**

As a cat, you are at constant risk of starving when your fullness bar reaches zero, and of being chased by dogs who will bite you and take one of your three lives.

You can explore the forest and village as much as you would like, but you need to continuously catch and eat chickens to keep your fullness from dropping too low. Don’t leave it too long to eat either, as you will expend more energy, causing your fullness to drop more quickly, when sprinting to hunt or explore.

Chickens are more than just a food source, however. The villagers are friendly and will appreciate a chicken as a gift, or attention from a cat. The more you interact with, or gift chickens to, an individual villager, the more their affection for you increases.

This is your escape from the wild: when a villager’s affection increases, they will occasionally gift you food, and will eventually adopt you, meaning you win the game.

**Implementation**

I wanted to challenge myself to use Unreal Engine 5 for Escape the Wild, so I could gain proficiency in multiple game engines. I was able to apply the prior experience I have in Unity to Unreal Engine, as well as learning skills specific to Unreal.

As I only had a small amount of prior experience with C++, and none with Blueprints, I split my implementation of the game between them in order to better understand both of them through the development of Escape the Wild. I generally added basic properties to C++ classes, and wrote functions either in C++, exposing them to Blueprints for input binding, or fully in Blueprints.

For example, the player has a vitals component purely in C++, keeping track of fullness, including draining fullness over time, adding fullness again when the player eats, and broadcasting if the player starves.

The logic to keep track of the player’s lives, lose a life, gain temporary invulnerability and drop any prey in the player’s mouth when bitten by a dog, and broadcast that the player is out of lives, is also all in a C++ class.

On the other hand, the player’s movement, such as looking around, walking, sprinting and jumping, and responses to inputs, such as eating, interacting with villagers and meowing, are all in a Blueprint class called BP_Cat.

In addition to this, the player, dogs and chickens all have Animation Blueprints and Blend Spaces.

Some hybrid C++ and Blueprint features are the chickens and steak. Chickens have notice and catch collision components, can be caught and released, run away from the player, and have their physics disabled while being carried. They also have a food value when eaten, and repeatedly snap to the ground to allow chickens to walk over the terrain after sculpting the Landscape, without disappearing into a hill or flying over dips in the ground.

The Blueprint class for steak actually inherits from the same C++ class as chickens, but has the notice collision component disabled, and lacks movement logic, which is in the chickens’ Blueprint class. The C++ functions to be caught, released, and snap to the ground are all relevant to the steak; snap-to-ground is called when it spawns.

The only logic on villagers relates to their affection component, and is also a mix of C++ and Blueprints. Logic to check affection, change affection, and keep track of affection thresholds lives in a C++ component, whereas what to do when affection changes or a threshold is reached is part of the Blueprint class.

Dogs are also created from a mix of C++ and Blueprints, but, in addition to this, they are AI enemies with AI Perception, a Behaviour Tree and a Blackboard to control their patrolling and chasing behaviours. They will also give up after a while when the player is unreachable.

This was quite new to me, and took some learning and time spent debugging to understand how to implement the dogs’ Behaviour Tree. Additionally, I learnt how to create a Nav Mesh in Unreal Engine and how to modify this to exclude certain areas, namely the tops of wooden crates.

**Process**

When creating Escape the Wild, I began by making the player character, attaching animations to the cat, and adding movement. I then added the vitals component, with fullness and a fullness bar. Following this, I made one of each type of character in the game, first creating a single chicken, then a single dog, then a single villager with affection, who would gift steak.

When I had done this, I was able to use the Unreal Engine Landscape tool to sculpt and paint textures on the terrain, then added props and placed villagers and dogs. Finally, I made a chicken spawner class to spawn chickens randomly at appropriate locations at the beginning of the game.

When the game itself was done, I added a menu screen, and linked up the win and lose conditions to win and lose screens. I have experience creating menus and UI in Unity, but I was able to adapt these skills to learn how to do this in Unreal Engine too. Furthermore, I added a text variable on the Game Instance that stored the lose reason - if the player starved or was killed by a dog - so that I could display this on the lose screen.

Although I am pleased with the game overall, if I had more time to spend on refining Escape the Wild, I would improve a number of features. For example, I would create more appealing UI screens and in-game UI, with a way to quit the game while playing. Additionally, I would like to make the environment cleaner, and more detailed and interesting, and give a visual indication of villagers’ affection increasing. One more area for improvement would be the dogs’ AI, especially making the gap between the player’s bite invulnerability ending and a dog noticing them again smoother.

**Credits**

Birdsong Ambience - hoshisato (https://freesound.org/people/hoshisato/sounds/853112/)

Cat Meow - Sonniss GDC Game Audio Bundle 2020 (https://sonniss.com/gameaudiogdc/)

Dog Bark - jorickhoofd (https://freesound.org/people/jorickhoofd/sounds/160093/)

Eating Crunch - User391915396 (https://freesound.org/people/User391915396/sounds/570336/)

Villager Interaction Sound - JavierZumer (https://freesound.org/people/JavierZumer/sounds/257227/)

Animal Assets - ithappy studios (https://ithappystudios.com/free/animals-free/)

Steak Asset - Marcel Plagmann (https://plaggy.sellfy.store/p/cc0-steaks-3d/)

Villager Asset - Winged Boots Studio (https://www.fab.com/listings/d49af8e0-b16c-4f1f-849f-48b30bd59740?lang=en)

Environment Assets - Yevheniia Yaremko (https://www.fab.com/listings/d7408876-2301-468a-a2e9-6eea38ddc10d?lang=en)
