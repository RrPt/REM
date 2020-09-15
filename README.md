# REM
Rainers Energy Measurement

*This project ist in german, to translate you can use a translator program like [here](https://translate.google.com/translate?hl=de&sl=auto&tl=en&u=https%3A%2F%2Fgithub.com%2FRrPt%2FREM)**

Das Projekt REM erlaubt es die exakte Leistung von vielen Verbrauchern gleichzeitig zu messen.
Die Komponenten werden normalerweise in der Hausverteilung installiert und können dann die Leistung von z.B. einzelnen Zimmern erfassen.

## Übersicht
Das System besteht aus mehreren Hutschinenkomponenten, die über den REM-Bus miteinander verbunden sind
![REM Übersicht](REM-Übersicht.jpg)

## REM-C 
Das REM-C Modul enthält den Controller. Dieser fragt alle Messwerte über den 
REM-Bus von den einzelnen REM-M Modulen ab und stellt diesen über den 
Ethernetanschluß zur Verfügung. Die geschieht per MQTT und einen Webserver.
Über den Webserver erfolgt auch die Kalibrierung.

An das REM-C Modul werden auch die drei Phasen der Spannungssignale angeschlossen,
diese werden galvanisch getrennt und über den REM-Bus den einzelnen REM-M Modulen
 zur Verfügung gestellt.

Es können bis zu 8 REM-M Module mit je 12 Kanälen angeschlossen werden, 
insgesamt also bis zu 96 Kanäle.

Für die Platine des REM-C Moduls stehen die KICAD Pläne, die 3D-Modelle der Gehäuse (SCAD) und die Controllersoftware (Arduino) zur Verfügung. 

## REM-M
### REM-MH
Das REM-M Modul beinhaltet zum einen ein Verteilermodul REM-MH, welches den REM-BUS auf die 2 REM-MM MOdule aufteilt.
Auf diesem wird auch per Jumper die Adresse des REM-M Moduls eingestellt.
### REM-MM
Jedes REM-M Modul beinhaltet 2 REM-MM Platinen, die für die eigentliche 
Messung zuständig sind.
An jede REM-MM Platine können 6 Stromsensoren angeschlossen werden, 
zusammen mit der über den REM-Bus gelieferten Spannung 
(Phase über Jumper für alle 6 Sensoren gleich einstellbar)
können so für alle 6 Kanäle die folgenden Energieparameter bestimmt werden:
 * Strom RMS
 * Leistung
 * Blindleistung
 
Pro REM-MM Platine:
 * Spannung RMS
 * Frequenz

Für die Platinen des REM-M Moduls stehen die KICAD Pläne und die 3D-Modelle der Gehäuse (SCAD) zur Verfügung. 
## Status
Das Projekt ist noch in der Entwicklung (Stand September 2020), 
allerdings sins sowohl Platinen als auch Gehäuse fertig.
In Entwicklung ist noch die Software und die Dokumentation.


## Bilder

![REM01](REM01.jpg)

![REM02](REM02.jpg)

## Stichwörter
 * ADE7816, Energy Metering IC
 * ESP32
 * TCA9548A
 * USR ES1
 * Leistungsmessung, Blindleistungsmessung, Spannungsmessung, Strommessung, RMS
 * Stromwandler, Current transformer, ZMPT107-1, CT1005
 