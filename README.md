# ReplaySorcery
## An open-source, instant-replay solution for Linux.
Back when I used to use windows I used AMD ReLive alot. It, and the nVidia version ShadowPlay Instant Replay, will constantly record the screen without using too much computer resources and at the press of a keycombo will save the last 30 seconds.

I wanted something like this for Linux...

I got tired waiting for someone else to do it.

# Documentation
## Installing
### Arch
There is an official AUR package that gets updated from the CI (thanks to [Bennett Hardwick](https://github.com/bennetthardwick)): [replay-sorcery](https://aur.archlinux.org/packages/replay-sorcery).

[Sergey A.](https://github.com/murlakatamenka) has also setup a `-git` AUR package: [replay-sorcery-git](https://aur.archlinux.org/packages/replay-sorcery-git).

## Building from Source
```
$ git submodule update --init
$ cmake -B bin -DCMAKE_BUILD_TYPE=Release
$ make -C bin
$ sudo make -C bin install
```

### Required dependencies
- CMake
- FFmpeg
- X11

### Optional dependencies
- PulseAudio (for audio recording)

## Running
It can be enabled as a user systemd service:
```
$ systemctl --user enable --now replay-sorcery
```

Once it is running, just press Ctrl+Super+R to save the last 30 seconds.

You can also use systemd to look at the output:
```
$ journalctl --user -fu replay-sorcery
```

## Configuration
The config file location and options has completely changed since version 0.3.x

The config file is located at `@CMAKE_INSTALL_PREFIX@/etc/replay-sorcery.conf` (`/usr/local/etc/replay-sorcery.conf` by default). See `sys/replay-sorcery.conf` for the default values along with documentation.

# TODO
- Document code better
- Cross-platform support
  - Doubt there is any demand though
  - Maybe for Intel devices if they are fast enough?
