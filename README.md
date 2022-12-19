# ThreedoLib
3DO input library for Arduino

For Arduino Leonard/Pro Micro (5V 16MHz)

## Controller compatibility

It's been tested and confirmed to work with:

| Accessory      | Notes                                    |
|----------------|------------------------------------------|
| Digital Pad    |                                          |

Supports multiple daisy chained devices.

## How to use
3DO controllers works with 5V so I recommend to use a 5V Arduino.

This library requires [DigitalIO](https://github.com/greiman/DigitalIO).

I recommend the usage of [SukkoPera's fork of DigitalIO](https://github.com/SukkoPera/DigitalIO) as it supports a few more platforms.


### 3DO port pins (db9)


| 3DO  | Description | Notes    |
|------|-------------|----------|
| 1    | GROUND      |          |
| 2    | VCC/POWER   |          |
| 3    | AUDIO R     | Not used |
| 4    | AUDIO L     | Not used |
| 5    | VCC/POWER   |          |
| 6    | DATA OUT    |          |
| 7    | CLOCK       |          |
| 8    | GROUND      |          |
| 9    | DATA IN     |          |


## Credits

It uses the [DigitalIO](https://github.com/greiman/DigitalIO) from greiman.

I recommend the usage of [SukkoPera's fork of DigitalIO](https://github.com/SukkoPera/DigitalIO) as it supports a few more platforms.

Based on [documentation](https://hackaday.io/project/170365-blueretro/log/190948-3do-interface) from Darthcloud

And http://kaele.com/~kashima/games/3do.html


Special thanks to my friend Rafael for lending me the some controllers to test.


## Warning
Code and wiring directions are provided to you 'as is' and without any warranties. Use at your own risk.
