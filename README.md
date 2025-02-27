# C Template

This repo is designed to be forked/copied to a new repo as a base project for C Problem Sets. It includes some CMake setup, a git submodule for cmocka, and a buildable starter project that does... nothing useful. But, it shows the framework for CMake and cmocka setups and should be relatively easy to add challenges/problems for mentees to solve. 

It includes vscode tasks that automatically pull, configure, and build cmocka, and configure and build the challenge (including tests). This allows the mentee to "simply" click the play button either on top of source files or the play/debug butotn on the bottom task bar. There should be no "setup" required on their part (unless you added something that needs it). Write code and press play!

Add unit tests, implentation, and use the Todo Tree to add todos that the member may need to complete to satisfy the project.

There are existing TODOs for you, the challenge creator, as a reminder of what you may want to change to set up the project.

<!-- { } REQUIRED Edit the below for your specific challenge (and delete this and above): -->

# C Challenge Name

The C Challenge description, providing context and an overview of the challenge.

## KSAT List
This question is intended to evaluate the following topics:
- A####: ...

## Tasks
What exactly should the mentee do? What files do they need to edit/care about? Are there any important parts of the code they should look through?

A reminder for the TODOs you may have created would be helpful. A todo button has been added to the bottom status bar as another avenue of getting to them besides the side bar.

## Building and Testing
Depending on your environment, there are a couple ways you can build the challenge. The ideal methods are listed in preferred to not-as-preferred order for simplicities sake.

Ensure you have `cmake` installed via `apt`. Compiling this project via `gcc`/`clang` is not covered.

### VSCode + CMake + CMake Extension
This is the ideal method as it makes it very easy to run and debug the applications as the environment is currently set up.

Ensure you have installed the VSCode extensions `CMake` and `CMake Tools`. 

At this point, there should be a good amount of buttons in the bottom status bar. The most important ones are the bug and play icons followed by the name of the challenge in brackets (i.e. `[c_challenge]). The bug icon will debug your application, play button runs it, and the text in brackets will change whether you are debugging/running the challenge itself or the unit tests for the challenge (these are called "targets"). Clicking on the text will alllow you to select which target you are running/debugging.

*Note*: The "play" or "debug" icons in the top right of any C source files will run the currently active target; even if you have a C unit test source file open, and the active target is "c_challenge" (or equivalant challenge name, as long as it's without "_tests"), it won't run the tests, and vice versa if you have a "_tests" target set.

*Note*: There is a setting in `.vscode/settings.json` (workspace settings) that makes these icons appear. If the icons/text are/is not present, make sure the setting looks like:
```
"cmake.options.statusBarVisibility": "compact",
```
(This setting is in the UI version of settings as well)

### VSCode + CMake
In `.vscode/tasks.json` is a series of defined tasks that can be ran via pressing `ctrl+shift+p` (or open up the command pallet via the GUI) and typing/selecting `Task: Run Task`.

The most notable task is "Build Challenge". This will invoke CMake to build your project (both the application and the unit tests version). The other tasks are dependencies for this task to help pull in `cmocka` (C unit testing library) and build it.

Running the "Build Challenge" task will produce two binaries in `./build/bin/`, one that is your application and the other that runs the unit tests. These may be started from the command line in whatever fashion you'd like.

### CMake
You can also just use `cmake` on the command line. Everything above is just wrappers around these commands.

To configure the project (assuming you are at the workspace level directory, root of the project/repo):
```
cmake -S . -B build/ -DCMAKE_BUILD_TYPE=Debug
```
And to build the binaries:
```
cmake --build build
```
(If you change project configuration, the first command is required (add/remove files, create folders of source code, etc). Basically if the project structure changed and you had to edit `CMakeLists.txt` in the process.)

(If you just change source code in existing files, you only need the second command to recompile.)

That's it! Now the binaries exist and can be executed on the command line however you please.
