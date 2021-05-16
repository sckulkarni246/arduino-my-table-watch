# arduino-my-table-watch

## Arduino Nano << -- >> 4-digit segment display connections

Below is the mapping of the IO lines of the Arduino Nano to the various segments and the anodes. Please note, this is a common anode display. If you are using a common cathode display, the implementation would be mostly similar except the functions that turn the segments on and off.

```c
#define DIG1        5
#define DIG2        4
#define DIG3        3
#define DIG4        2
#define SEGA        8
#define SEGB        9
#define SEGC        11
#define SEGD        10
#define SEGE        12
#define SEGF        7
#define SEGG        6
```

## Changes needed for using a common cathode display

If you are using a common cathode display instead of a common anode display, you will need to modify the below functions.

1. **seg_on** -> change the level to **HIGH** instead of **LOW**
2. **seg_off** -> change the level to **LOW** instead of **HIGH**
3. **select_digit** -> change the level to **HIGH** instead of **LOW**
4. **deselect_digit** -> change the level to **LOW** instead of **HIGH**