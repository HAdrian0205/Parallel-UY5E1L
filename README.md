# Parallel-UY5E1L

Féléves feladat: 

- C nyelven POSIX és OpenMP felhasználásával egy program, amely numerikus integrálást végez.
- A program előre meghatározott szabályok/módszerek mentén képes elvégezni numerikus integrálást.
- Kiválasztható, hogy mely szabály/módszer alapján szeretnénk elvégeztetni az integrálást.
- A választható numerikus integrálási szabályok:
  - Téglalap-szabály (1,2) szerinti
  - Trapéz-szabály szerinti
- Ezután megadhatjuk az x koordinátákat és a felvett értékeket.
- A program ezt követően elvégzi a numerikus integrálást.
- Az integrál közelítés menete például trapéz szabály szerint (párhuzamosítással):
  - 1. *Az integrál intervallumának felosztása részintervallumokra, amelyeket külön-külön dolgozhatunk fel a különböző szálakban.
  - 2. A részintervallumokhoz tartozó trapézok területének kiszámítása a trapézszabály használatával. (Fontos megjegyezeni, hogy ez nem tartozik a párhuzamosításhoz
       közvetlenül)
  - 3. *A részintervallumok területeinek összegzése a végső integrál értékének meghatározásához.

* jelentése: Párhuzamosítás alkalmazásával elkészülő lépés.
