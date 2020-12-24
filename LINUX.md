# Compiling for Linux
from..
* [Ubuntu/Debian](#for-the-lucky),
* [Some other *nix](#for-the-foolish),
* or even [Microsoft Windows](#for-the-rest-of-you).
[Appendix A: Dedicated Server]

## For the lucky
On Debian, Ubuntu, or derivitives, installing the Steam Runtime should be easy.
I havn't done it, but Valve provides [pre-built packages][prebuilt]
and [source].

(the source isn't portable because it uses `dpkg`)

## For the foolish
Linux users not using DPKG can build using [jimbly's SteamRT containers][jimbly].

**NOTE:** All of the following commands assume ofd is in `~/proj/ofd`,
with the source code in `~/proj/ofd/Open-Fortress-Source/`,
the game is in `~/proj/ofd/game/open_fortress`, and your username is `magnus`.

First, install the 32bit SteamRT toolchain.
```sh
# ensure your user has permissions to use docker (optional)
$ sudo usermod -aG docker magnus
$ docker pull jimbly/steamrt-i386-gcc
```

Place the following in `~/proj/ofd/build.sh`.
```bash
#!/bin/bash
export STEAM_RUNTIME_PATH=/usr
#export MAKE_VERBOSE=1

pushd Open-Fortress-Source

# Generate project files
./vpc_game_linux

# the whole `if` and `for` is just to let
# you pass in a series of targets, and have
# them all built one by one (ex: `build.sh mathlib client_ofd`)
if [ -z "$@" ]; then
  # this command builds `all-targets`
  make -f game_linux.mak
else
 for target in "$@"; do
  make -f game_linux.mak "$target"
 done
fi

popd
```


Here is the command I use to run a build, with the Ccache mounted.
If you don't care about caching build artefacts, remove the second `-v`.
```sh
#explanation of args:
# "-it" for interactive-mode, and to allocate a virtual TTY.
# "-v source:destination" mounts folder source at destionation inside the container
# "-w /ofd" sets the working directory for the command to /ofd
$ docker run -it -v ~/proj/ofd:/ofd -v ~/proj/ofd/ccache:/root/.ccache -w /ofd jimbly/steamrt-i386-gcc ./build.sh
```

## For the rest of you
On Windows, linux builds can be made with 'Docker Machines'..
Again, I havn't done it, but [jimbly's containers][jimbly] were actually purpose-built for this.

# Appendix A: Dedicated Server
### this section is quite WIP
Basically, you've gotta: Install Linux, SteamCMD, Git, and Git LFS.
Then, using SteamCMD, install appids 440 (TF2) and 244310 (SSDK2013 DS)
and then launch the game, making sure to put TF2 where it is expected (next to srcds_linux, in a folder called `tf`)
ReddKing was having problems with SRCDS not installing TF2 files, but worked around it by transferring TF2 to the server over FTP.

## Any problems?
Contact me! I'm `Nopey Nope#5837` on Discord, and `imjustagan@gmail.com` is my email.



[jimbly]: https://github.com/Jimbly/steam-runtime-docker
[prebuilt]: https://repo.steampowered.com/steamrt-images-scout/snapshots/
[source]: https://github.com/ValveSoftware/steam-runtime
