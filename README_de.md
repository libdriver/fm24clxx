[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver FM24CLXX
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/fm24clxx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

FM24CLXX ist ein von Cypress eingeführter ferroelektrischer Speicherchip des IIC-Busses. Im Gegensatz zum EEPROM unterstützt der ferroelektrische Speicherchip das Schreiben von Daten mit Busgeschwindigkeit ohne Wartezeit. Ferroelektrik hat eine geringere Schreibleistung als EEPROM. Ferroelectric unterstützt 10^14 Lese- und Schreibzeiten und die Datenspeicherzeit beträgt 151 Jahre.

LibDriver FM24CLXX ist der voll funktionsfähige Treiber von FM24CLXX, der von LibDriver gestartet wurde. FM24CLXX bietet Schreib- und Lesefunktionen. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver FM24CLXX-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver FM24CLXX IIC.

/test enthält den Testcode des LibDriver FM24CLXX-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver FM24CLXX-Beispielcode.

/doc enthält das LibDriver FM24CLXX-Offlinedokument.

/Datenblatt enthält FM24CLXX-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

#### example basic

```C
#include "driver_fm24clxx_basic.h"

uint8_t res;
uint8_t data;

res = fm24clxx_basic_init(FM24CL16B, FM24CLXX_ADDRESS_A000);
if (res != 0)
{
    return 1;
}

...

res = fm24clxx_basic_read(0x00, (uint8_t *)&data, 1);
if (res != 0)
{
    (void)fm24clxx_basic_deinit();

    return 1;
}
else
{
    fm24clxx_interface_debug_print("fm24clxx: 0x%02X.\n", data);
}

...

res = fm24clxx_basic_write(0x00, (uint8_t *)&data, 1);
if (res != 0)
{
    (void)fm24clxx_basic_deinit();

    return 1;
}
else
{
    fm24clxx_interface_debug_print("fm24clxx: 0x%02X.\n", data);
}

...

(void)fm24clxx_basic_deinit();

return 0;
```

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/fm24clxx/index.html](https://www.libdriver.com/docs/fm24clxx/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.