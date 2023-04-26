
# POSIX (1.beadando) prím számok:
 A feladatban meghatározom a prímszámok számát 1 és egy felhasználó által meghatározott határ között, mind szekvenciálisan, mind párhuzamosan.
    Függvényt definiálok annak ellenőrzésére, hogy egy szám prím-e, valamint egy függvényt a prímszámok számának meghatározására egy adott tartományban a prímellenőrző függvény használatával.
 A párhuzamos megvalósítás bemeneti paraméterként megadott mennyiségű szálat használ a munkamegosztáshoz.
 A kód kiírja a megtalált prímszámok számát, mindkét megvalósítás esetén az eltelt időt, valamint az időmegtakarítást, amit a párhuzamosítás eredményezett.


# OPENMP (2.beadando) mátrix szorzás sor-oszlop, blokkokra bontott:
 A feladatban Mátrix-szorzást végzek egy a,b NxN-es mátrixra.
  Első lépésben feltölti a mátrixokat értékekkel fill_matrix() függvény segítségével, majd a szekvenciális számolást a matrix_mult_serial() függvény míg a párhuzamos számolásokat matrix_mult_parallel() függvény illetve a matrix_mult_block_parallel(). 
  Összehasonlítja a sor oszlop szorzás szekvenciális és párhuzamos megvalósításának futási idejét.  Az összehasonlításhoz a grafikont python plotolja ki, a c kód az adatokat egy szöveg fájlba menti.

#PYTHON (3.beadando) pi közelítés:
 A feladatban a Monte Carlo módszer segítségével közelítést ad a pi értékére. A calculate_pi függvény véletlenszerűen generál egy adott számú pontot, num_samples változó által meghatározott mennyiséget.
 A szekvenciális megoldás meghívja a calculate_pi függvényt, majd visszaadja az eltelt idő és kapott pi közelítést. 
A párhuzamos megoldás először létrehoz egy processzor poolt ahol egységesen elosztja a szálak között a num_sample-t.
 Majd ezután mindegyik szálra meghívja a calculate_pi függvényt és a visszakapott értékekből átlagot von. Majd végső lépésben diagrammként ábrázolja, hogy melyik módszer mennyi időt vett igénybe, a közelítés pontosságát is. 
