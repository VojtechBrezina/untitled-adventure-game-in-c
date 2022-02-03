# Untitled adventure game in c

Ukázka toho, co se dá zvládnout po dokončení kurzu BI-PA1.21 na FIT ČVUT.

## Kompilace a spuštění

Nejjednodušší je zkompilovat program skriptem `build.sh`. Ten
vytvoří spustitelný soubor `build/game`. Hru je potřeba spouštět vždy
ve stejném adresáři, ve kterém si vytvoří pracovní složku `.saves`.

Pokud váš systém nemá bash, nebo gcc, budete muset program zkompilovat
sami. V takovém případě je potřeba kompilátoru předat informaci o tom,
že direktiva `#include "soubor"` má hledat ve složce `src`. Pokud ani potom
program nepůjde zkompilovat, je to nejspíš tím že používá GNU rozšíření
standartní knihovny.

## Nové koncepty

Některé knihovní funkce potřebné pro realizaci podobného projektu bohužel
nejsou v kurzu PA1 popsány. Zde se proto pokusím o jejich shrnutí.

### Práce se souborem

Textová adventure hra by asi nebyla moc zábavná, pokud by neukládala váš
postup.
*...to be done...*
