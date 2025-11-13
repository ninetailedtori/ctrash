# ctrash
CLI trash management done right - light, fast, feature-full. Written in C.

## This repo is a very rough WIP!
Definitely not ready to even test just yet :P But! If you'd like to contribute, well...I'll announce when they're open.

## TODO
- Trash management and functions, in line with freedesktop.org trash specs
- Compatibility with UNIX rmflags, with additions
- Nice, pretty listing of trash contents
  - the aim is to provide most of the necessary support for UNIX ls/eza flags
  - BUT the output should be a prettified table, with customisable column-row sizes, wrapping, terminal width-detection, and paging
  - Respect PAGER env-var for paging mode, but allow manual setting within config/within cli options
- Fast, fast, fast! Nothing but the cleanest fastest lightest C we can write!

Not sure if I'm missing anything, but I shall update it here if so :]

### Possible extra features?
- Tray management? systemd or cron timer support?
- MacOS support? Or even...*shudder* Windows support?
- Feel free to submit feature requests :]
