# Untitled adventure game in c

Ukázka toho, co se dá zvládnout po dokončení kurzu BI-PA1.21 na FIT ČVUT.

Předem upozorňuji, že můj styl programování v jazyce C se mírně liší od
toho oficiálně prezentovaného v PA1. Kromě toho je použit překladač gcc
místo překladače g++ používaného ProgTestem, takže například přetypování
návratové hodonty funkce `malloc()` odpadá.

## Kompilace a spuštění

Nejjednodušší je zkompilovat program skriptem `build.sh`. Ten
vytvoří spustitelný soubor `build/game`. Hru je potřeba spouštět vždy
ve stejném adresáři, ve kterém si vytvoří pracovní složku `.saves`.

Pokud váš systém nemá bash, nebo gcc, budete muset program zkompilovat
sami. V takovém případě je potřeba kompilátoru předat informaci o tom,
že direktiva `#include "soubor"` má hledat ve složce `src` a následně
zkompilovat všechny `.c` soubory v tomto adresáři. Pokud ani potom
program nepůjde zkompilovat, je to nejspíš tím že používá GNU rozšíření
standartní knihovny (především ta, která popisuje předmět PA1, jako
`getline()`, nebo `strdup()`).

## Nové koncepty

Některé knihovní funkce a koncepty jazyka C potřebné pro realizaci podobného
projektu bohužel nejsou v kurzu PA1 popsány. Zde se proto pokusím o jejich
shrnutí.

### Rozdělení projektu do více souborů

Projekt je poněkud příliš rozsáhlý na to, aby se *pohodlně* vešel do jednoho
souboru. Rozdělení programu do více souborů je část jazyka C, kterou sám
neovládám úplně dokonale a tak se radši nebudu snažit nic vysvětlovat.
[Zde](https://gcc.gnu.org/onlinedocs/cpp/Header-Files.html) oficiální gcc
dokumentace na téma hlavičkových souborů. Jinak předpokládám, že v předmětu
PA2 bude vše objasněno.

### Nuance práce s makrem `assert`

Některé kontroly pomocí makra `assert` by zásadně zpomalovaly běh programu.
Proto knihovna `assert.h` umožňuje toto makro deaktivovat pomocí definice
symbolické konstandy `NDEBUG`. Toho se dá dosáhnout takto:

```c
#define NDEBUG
// Knihovnu je potreba vlozit po definici:
#include <assert.h>
```

V tomto projektu je ale potřeba řídit tuto funkci externě, aby bylo možné
automaticky vytvořit build s asserty, nebo bez nich. Překladač `gcc` použitý
ve skriptu `build.sh` podporuje definici simbolických konstant pomocí přepínače `-D`, který funguje následovně:

```bash
# Jednoduché přepínače
gcc -D__PROGTEST__ soubor.c
gcc -DNDEBUG soubor.c

# Konstanty s hodnotou
gcc -DCOUNT_OF_SOMETHING=5 soubor.c
gcc -DMY_NAME=\"Jmeno Prijmeni\"
```

### Práce se souborem

Textová adventure hra by asi nebyla moc zábavná, pokud by neukládala váš
postup.
*...to be done...*
