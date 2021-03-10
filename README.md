

GRLB-Scara для MEGA2560 ramps v1.4 основаная на GRLB 0.9j. Основной проект:

https://www.thingiverse.com/thing:3096135.

Серво-привод управляется командой "M3 Sx" (x задает угол, изменяется: 0-1000) и "M5".

Схема подключения.

[![Подключение](https://github.com/akv47/DrawBot-ramps/blob/main/pic/connect.jpg)

Добавлена возможность калибровки DrawBot командой "$M". Калибровка производиться из положения плеча под углом 45 градусов, при этом высчитываются и сохраняются параметры theta ($30) и psi ($31).

[![](https://github.com/akv47/DrawBot-ramps/blob/main/pic/ramps.png)](https://youtu.be/nXxYWECz4rc)
