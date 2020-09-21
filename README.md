# Zork

This is a text based game about the adventures of Player Character, a slave gladiator in the roman period that aspires to be set free after a combat against Kroz.

## How to play

You can input commands and the player character will execute them.

**Commands**

- `help` - Shows this information.
- `examine [object]` - Examine something. If written with no arguments it examines the current room.
- `go <direction>` - Move towards a direction.
- `take <object>` - Picks up an item.
- `drop <object>` - Drops an item.
- `open <object>` - Uses a key in your inventory to open an object.
- `put <object> in <object>` - Puts an item inside an object.
- `hit <object> with <object>` - Hits something with the given object.

**Objects**

- Anything with a name counts as an object.
- Body parts and exits also count as objects.
- You have to be explicit when giving the name of an object or it won't be recognized.

**Directions**

- The only accepted directions are north, south, east and west.

**Combat**

- Different objects deal different amounts of damage.
- Remember you can choose body parts as a target.
- Body parts can be severed when hit, dropping to the floor.
- You can hit the body of a creature by attaking it directly.

**How to win**

<details>
<summary>Spoiler</summary>

1.  Go to the empty cell

    ```
    > go north
    > go north
    ```

2.  Take the board

    ```
    > take board
    ```

3.  Go to the office

    ```
    > go south
    > go east
    ```

4.  Sever Porcius' right arm / hand with the board

    ```
    > hit porcius right hand with board
    ```

5.  Kill Porcius

    ```
    > hit porcius with board
    > hit porcius with board
    > hit porcius with board
    ...
    ```

6.  Drop the board

    ```
    > drop board
    ```

7.  Take the desk key

    ```
    > take desk key
    ```

8.  Open the desk

    ```
    > open desk
    ```

9.  Drop the desk key

    ```
    > drop desk key
    ```

10. Take the armory key

    ```
    > take armory key
    ```

11. Go to the arena loby

    ```
    > go west
    > go west
    ```

12. Open the armory door

    ```
    > open armory door
    ```

13. Drop the armory key

    ```
    > drop armory key
    ```

14. Go to the armory

    ```
    > go south
    ```

15. Take two weapons

    ```
    > take sword
    > take spear
    ```

16. Go to the arena

    ```
    > go north
    > go north
    ```

17. Sever Kroz's right and left arm / hand with your sword

    ```
    > hit kroz right arm with sword
    > hit kroz left arm with sword
    ```

18. Kill kroz

    ```
    > hit kroz with sword
    > hit kroz with sword
    > hit kroz with sword
    ...
    ```

</details>

## Features

Implemented features:

- Seven connected rooms
- Items can be picked up
- Items can be dropped
- Items can be placed inside other items

Extra features:

- Keys that open items and doors
- Body parts that can be severed and picked up
- Combat with the NPCs
- Destructible environment (doors, items, etc.)

## Authors

_Jaime Bea Pérez-Zubizarreta_

## Github

https://github.com/JaimeBea/Zork

## License

[MIT](./LICENSE)
