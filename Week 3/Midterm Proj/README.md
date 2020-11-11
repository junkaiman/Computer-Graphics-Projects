# Midterm project proposal

Junkai Man

MEDIART-206

Prof. Benjamin Bacon

-----

In the midterm project, I plan to design an interactive game that triggers the player to take in-depth thinking around the philosophy of making mistakes. 

Inspired by the film *Triangle*, I plan to use a mechanism that will be different from most 2d adventure games. After the player dies, instead of clearing everything and restart the level, in this game, the player will respawn with their previous bodies that replay their previous operations. The “current self” can see and interact with its “previous selves” just like there are multiple players playing at the same time. 

After the research, I found a mobile game *Sometimes You Die* that conveys a similar idea. In that game, the player dies with their body left on the screen. Sometimes the player has to pass the level with the help of their dead bodies. But my idea is slightly different, I intend to present the interaction between “previous selves”, “current self”, and even “future selves”. That is to say, those “previous selves” will not be static dead bodies or like recordings on the screen, but can have interactions with “current selves” (i.e. Block the way of current selves, have collisions with current selves). 

![image-20201111082940886](D:\STUDY\THIS_TERM\MEDIART206\jm687_MEDIART206\Week 3\image-20201111082940886.png)

I intend to use the “previous selves” as a metaphor for our failures because we made mistakes at a certain moment and hence died in the game. And the “current self” represents “I” at this moment. We are influenced by our previous decisions, and the previous mistakes do have a series of consequences on ourselves for now and in the future, no matter how. So the co-existence of previous and current selves manifest this “influence” across time. 

However, I don’t want to repetitively deliver the cliché that “Failure is not the opposite of success, it’s part of success”. I want to reflect the failure in a truthful and realistic way. Yes indeed, failure can be part of success. We gain experience from our failures, and we learn lessons from the failure. These lessons build up the basis of our later success. But on the other hand, most of our previous failures will become barriers on the road to success. Some small errors will accumulate to huge deviation, and some failures directly ruin everything. Or, sometimes we dwell too much in the sadness of failure and stop moving forward. 

Therefore, in the game, the “previous selves” may block the way of the “current self”, preventing the player from going forward. But sometimes they may perform as a stair for the current self to climb to a higher altitude. The player will need specific strategies to die “properly”, and take advantage of “previous failures” to complete the level.

Another question is how exactly should we deal with these failures? Should we erase the influence of bad “previous self”? Or keep those failures in memories regardless of how “painful” they were? In the game, the player is designed to have a weapon that shoots bullet to the surroundings. When the bullet touches the player’s “previous self”, the “previous life” will be terminated and the body will be erased from the screen until the next spawning. However, the player has to pay the price for exerting this ability to erase a “previous failure” because the bullet they shoot to the air might at a certain time kill the “current self” and leads to death. So, there exists a situation that your “future self” will be killed by bullets that are shoot by your previous or current self, which conveys the philosophy that “We may create a new failure when dealing with our previous failures.”

![image-20201111083028529](D:\STUDY\THIS_TERM\MEDIART206\jm687_MEDIART206\Week 3\image-20201111083028529.png)

To clarify the design and programming of this project, the following list will help to understand.



**Objects:**

- player
  - current_self: The object that player can control, using ‘a’, ‘d’, ‘space’. Inherent of player object.
  - previous_selves[]: A vector that contains many player objects. After the death of current_self, the particular current_self is pushed into the vector.

- start block: The block where the player is spawned

- wall block: The object that blocks the movement of player object

- death block: The block which triggers the death of current_self

- end block: When current_self touches the end block, the level completes

- bullet: The object that triggers the death of current_self and triggers the elimination of previous_self

**Environment:**

- gravity: A glm::vec2 that applies on every player object

**Data:**

- Player’s operations on each current_self will be recorded into a xml file, and the data will be used to replay the operations

- when, which key is pressed down

- when, which key is released

**Animation:**

- color change of every spawned player object

- the change of background color

- death animation of player object

- elimination animation of player object that is hit by bullet 