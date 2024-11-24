# TFTtag-GDEM1085Z51-for-OpenEpaperLink

Uses a GDEM1085Z51 1360x480 10.85inch Black,White,Red e-paper display + a WAVESHARE ESP32-S3-ETH ESP32 board as an OpenEpaperLink Tag 

Display connects to ESP32 via adapter board DESPI-C1085

Display: https://www.good-display.com/product/529.html

Adapter Board: https://www.good-display.com/product/573.html

ESP32 Board: https://www.waveshare.com/wiki/ESP32-S3-ETH

Connections adapter board to ESP32:

| DESPI-C1085 | ESP32-S3-ETH |
|-------------|--------------|
| BUSY        |  IO0         |
| RES         |  IO16        |
| CS2         |  IO17        |
| CS          |  IO21        |
| SCLK        |  IO18        | 
| SDI         |  IO15        |
| GND         |  GND         |
| 3.3V        |  3.3V        |

Based on https://github.com/nlimper/TFTtag-for-OpenEpaperLink

Also see https://github.com/OpenEPaperLink/OpenEPaperLink
