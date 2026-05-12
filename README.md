# Custom OpenGL Glut Engine - with Bowling Scene

## About

Custom 3D engine in OpenGL with the implementation of a lighting model and basic physics for Sphere and OBB collisions.
The engine is highly parameterizable and allows for the easy addition of new scenes. The `BowlingScene` scene is implemented, which contains 4 fully playable bowling lanes. The game consists of 3 rounds and has video animations for strike, spare, split, and miss.

---

## Requirements
### Windows
* `pgr.dll` [How To Download](https://cent.felk.cvut.cz/courses/PGR/framework.html)
* `freeglut.dll`
* `glew32.dll`
* `assimp.dll`

### Linux
The Linux executable is configured with an `RPATH` of `$ORIGIN`, meaning it will automatically load these libraries from its own directory before checking your system. 
* `libpgr.so` [How To Link](https://cent.felk.cvut.cz/courses/PGR/framework.html)
* `libassimp.so`
* `libglut.so`
* `libGLEW.so`
* `libglfw.so`

---

## How to Play

1. Turn on the given lane using the **F5, F6, F7**, or **F8** key.
2. Go to the blue / red bowling ball, aim at it, and press **E**.
3. Stand on the lane and look in the direction you want to throw.
4. By holding **ENTER**, charge the throw strength (0 seconds = min, 5 seconds = max strength). (enter has inertia).
5. Press **E** again to throw the ball.
6. Repeat from step 2 until you finish all the rounds.

Good luck (and have fun) :D

---

## Controls
**Movement and interaction:**

* **W, A, S, D**: Player movement.
* **Mouse**: Camera rotation.
* **E**: Pick up the bowling ball / throw the ball (in player mode) / camera up (in freecam mode).
* **Q**: Camera down (freecam mode only).
* **ENTER (hold)**: Charge throw strength.
* **Shift**: Speed up movement (+50 %).
* **Spacebar**: Jumping (player mode only).

**Cameras and scene:**
* **F1**: Player mode (with collisions).
* **F2**: Free camera mode (freecam).
* **F3, F4**: Static views.
* **F5, F6, F7, F8**: Open bowling lanes.
* **F9**: Shift time of day by +1 hour.
* **F10**: Toggle light mode (on / off / disco).
* **F11**: Fullscreen.
* **ESC**: Exit game.

**Mouse and display:**

* **LMB (Left button)**: Model selection for the in-game editor.
* **RMB (Right button)**: Menu.
* **Mouse wheel (scrolling)**: Zoom in / zoom out (zoom in freecam mode).
* **Mouse wheel (hold)**: Camera drag.
* **8**: Shows all models and collision shapes.
* **9**: Shows models only.
* **0**: Shows collision shapes only.

**In-game Editor:**

* **R / T / Y**: Select modification mode - rotation/translation/scaling.
* **1 / 2 / 3**: Select modification axis (X/Y/Z).
* **Mouse wheel**: Changes the value of the selected parameter.
* **Shift**: Increases step precision.
* **Alt**: Super Extra fine step.
* **Ctrl**: Uniform axis modification.
* **U**: Undo.
