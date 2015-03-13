# Overview #
## Pinout ##
| Usage   | Name | Pin | Pin | Name | Usage   |
|:--------|:-----|:----|:----|:-----|:--------|
| 3,3V    | VCC  |   1 |  20 | VSS  | GND     |
| A0      | P1.0 |   2 |  19 | XIN  | Quarz   |
| A1      | P1.1 |   3 |  18 | XOUT | Quarz   |
| OUT1    | P1.2 |   4 |  17 | TEST |  |
| OUT2    | P1.3 |   5 |  16 | RST  |  |
| KBRD 0  | P1.4 |   6 |  15 | P1.7 | KBRD 3  |
| KBRD 1  | P1.5 |   7 |  14 | P1.6 | KBRD 2  |
| DISP RS | P2.0 |   8 |  13 | P2.5 | DISP D7 |
| DISP RW | P2.1 |   9 |  12 | P2.4 | DISP D6 |
| DISP D4 | P2.2 |  10 |  11 | P2.3 | DISP D5 |

## Helping Links ##

### Display control ###
http://cacheattack.blogspot.de/2011/06/quick-overview-on-interfacing-msp430.html

### Crystal ###
[adding a 32kHz crystal](http://www.msp430launchpad.com/2012/03/using-aclk-and-32khz-crystal.html)

### Toolchain ###
[debugging msp430](http://wiki.ubuntuusers.de/MSP430-Toolchain)

### Chips ###
You need at least 14 GPIO Pins and an ADC with 2 Channels.

[MSP430g2232](http://www.ti.com/lit/gpn/msp430g2232) or [MS430g2553](http://www.ti.com/lit/gpn/msp430g2553) in DIP Package

### Documentation ###
[MSP430x2xx User Guide](http://www.ti.com/lit/ug/slau144j/slau144j.pdf)