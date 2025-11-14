# ctrash

CLI trash management done right - light, fast, feature-full. Written in C++.

## This repo is a very rough WIP!

Definitely not ready to even test just yet :P But! If you'd like to contribute, well...I'll announce when they're open.

## Aims
We're looking to create a lightweight program that allows quick and easy management of trash, including automation of it, and possibly hooks to various events as well. But we're also looking to generate a library behind it, `libtrash`, that will be extensible, scalable, and designed for easy use by other C++ devs, who wish to have a library for trash management that's easy, clean, thread-safe, fast and well-documented. The aim for this library is to replace the current gap in existing libraries, rather that one for this stuff doesn't really exist. It should be extended to handle all operating systems, from Windows, macOS, to all UNIX and Linux distros, and more. I wish to provide the ability to parallel-process large clusters of files, as well as remain fast when perusing a large trash space. As such, this will require various levels of filesystem monitoring, whether by maintaining a local db or by running a filesystem lookup each time (which could be costly if not done through some monitoring socket). 

## TODO

- Trash management and functions, in line with freedesktop.org trash specs
- Compatibility with UNIX rm-flags, with additions
- Nice, pretty listing of trash contents
    - the aim is to provide most of the necessary support for UNIX ls/eza flags
    - BUT the output should be a prettified table, with customisable column-row sizes, wrapping, terminal
      width-detection, and paging
    - Respect PAGER env-var for paging mode, but allow manual setting within config/within cli options
- Fast, fast, fast! Nothing but the cleanest fastest lightest C++ we can write!
- Completions - fish, bash, zsh, what else?
- Support for alerts and/or actions when trash hits user-set thresholds - will generate config format first
- Write up a contribution and code style-guideline list
- Write up feature request and bug report templates
- Generate workflows.
- Automate packaging and publishing on various distros

Not sure if I'm missing anything, but I shall update it here if so :]

### Possible extra features?

- Tray management? systemd and cron timer support?
- macOS support? Or even...*shudder* Windows support?
- Feel free to submit feature requests :]
