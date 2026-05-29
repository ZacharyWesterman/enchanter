# Enchanter
Enchanter videogame project. This is **VERY MUCH** a WIP, so don't expect everything to work!
If you *do* want to take a look, see the following for how to get up and running.

# Dependencies
First install any missing dependencies.
If on Ubuntu, run `./install_deps.sh`.
If you're on some other distro or OS, I'm so sorry.

# Building

**WARNING**: If you change value of the `TARGET=` or `DEBUG=` flags, make sure to run `make clean` first,
otherwise you are pretty much guaranteed to get compilation errors!

- If building for linux, just run `make` or `make TARGET=linux_amd64` and then you can run `./bin/enchanter`.
- If building for web, run `./webenv.sh` and then
  - If you want a debug html page, run `make TARGET=webassembly DEBUG=true`, and then run `emrun bin/enchanter.html`.
  - If you don't need the debug page, run `make TARGET=webassembly`.

# Cleanup (optional)
To clean up built application files, run `make clean`.
To return to a pristine state without any libs or anything, run `make pristine`.
