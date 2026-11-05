# lathecode

Formato testuale per pezzi torniti e altri oggetti a simmetria circolare. Definisce le dimensioni del grezzo e le asportazioni da eseguire da destra verso sinistra, come avviene su un tornio tradizionale. Permette di specificare utensili, profondità di passata e velocità. Supporta la conversione in GCode e STL.

**[Provalo nell'editor online.](https://kachurovskiy.com/lathecode)**

La forma dell'oggetto è definita in segmenti. Ogni segmento può essere dritto, inclinato, circolare o una B-spline, e la sua posizione è relativa al segmento precedente. Per esempio, in lathecode un semplice cilindro si definisce con un solo segmento. Un cilindro lungo 7 mm e con diametro 6 mm si descrive così:

```
L7 D6
```
<img width="1222" alt="L7 D6" src="https://github.com/kachurovskiy/lathecode/assets/122809499/f3feb30f-e1c1-4a81-a50c-1ae85a3fd259">

Un cilindro con uno spallamento si descrive con due segmenti, praticamente due cilindri uno dopo l'altro. Per esempio:

```
L2 D4
L7 D6
```
Questa descrizione rappresenta un oggetto con diametro esterno di 6 mm, lunghezza totale 2 + 7 = 9 mm e uno spallamento sul lato destro largo 2 mm e profondo 1 mm.

<img width="1551" alt="L2 D4 L7 D6" src="https://github.com/kachurovskiy/lathecode/assets/122809499/79b6ff26-613e-4489-8d78-1d7e0e6f6661">

## Grezzo

La dimensione del grezzo va specificata nella prima riga tramite raggio o diametro: ad esempio `STOCK D10` e `STOCK R5` dichiarano entrambi un grezzo con diametro 10 mm. Quando il grezzo non è specificato, si usa come diametro del grezzo il diametro massimo del pezzo.

Il grezzo può anche specificare un foro passante interno già esistente con `ID` o `IR`. Ad esempio, `STOCK D10 ID4` e `STOCK R5 IR2` dichiarano entrambi un grezzo da 10 mm con un foro interno da 4 mm.

## Coni

Invece di specificare il diametro con `D`, indica il diametro iniziale con `DS` e quello finale con `DE`, oppure usa i raggi `RS` e `RE`.
Per un cono con un angolo di conicità noto rispetto all'asse, fornisci la dimensione iniziale o finale più `A<gradi>`. Gli angoli positivi aumentano il raggio dall'inizio alla fine del segmento; quelli negativi lo diminuiscono. I coni definiti con l'angolo possono terminare sull'asse, ma non possono attraversarlo.

```
; specifica diametro o raggio iniziale e finale
; il codolo da MT2 a B16 si può scrivere così
DEPTH CUT1
L80 DS14.9 DE17.78
L2 DS17.78 DE15.733; distanziale
L24 DS15.733 DE14.5

; coni equivalenti usando l'angolo rispetto all'asse
L80 DE17.78 A1.031
L2 DS17.78 DE15.733; distanziale
L24 DS15.733 A-1.471
```

![image](https://github.com/kachurovskiy/lathecode/assets/517919/b9e57828-3540-491a-b26c-f3c4e6b78e6f)

## Sfere

```
; sfera con diametro 10 mm
L5 DS0 DE10 CONV
L5 DS10 DE0 CONV
```

![image](https://github.com/kachurovskiy/lathecode/assets/517919/3b43998a-8419-4e48-947c-fe7a2c475fa0)

## Ellissi

```
; trottola
L1 DS0 DE2 CONV
L14 DS2 DE20 CONC
L0.5 DS20 DE21 CONV
L0.5 DS21 DE20 CONV
L8 DS20 DE2 CONC
L3.1 D2
```

![image](https://github.com/kachurovskiy/lathecode/assets/517919/11b07d65-7ecc-411c-843d-ebd269759ca6)

## B-spline

Usa `BSPLINE` quando il profilo richiede una curva libera morbida invece di una conicità dritta o di un segmento circolare `CONV` / `CONC`. Una riga spline ha comunque una lunghezza orizzontale `L` fissa, un raggio o diametro iniziale e un raggio o diametro finale. I valori di controllo intermedi seguono `BSPLINE` e tirano la curva tra gli estremi:

```
; profilo esterno libero e morbido
L3 D10
L24 DS10 DE22 BSPLINE D14 D26 D18 D28
L4 D28 CH0.5
```

I valori di controllo possono essere diametri (`D`) o raggi (`R`). La curva parte da `DS` / `RS`, termina su `DE` / `RE` e non passa necessariamente per i controlli intermedi. Lathecode campiona la spline in brevi corde del profilo per l'anteprima e la pianificazione, poi il pianificatore genera normali movimenti GCode lineari.

Smussi e raccordi al momento non sono supportati per i segmenti `BSPLINE`.

## Raccordi e smussi

Uno smusso o un raccordo può essere aggiunto a entrambe le estremità di un segmento dritto o conico. Ogni segmento possiede le proprie caratteristiche di estremità e usa i segmenti vicini solo per stabilire se la caratteristica sale o scende.

```
; bullone M10
L20 D10 FI0.5 ; raccordo sull'estremità libera e alla radice dello spallamento
L6 D19.6 CH0.5 ; smusso su entrambi i bordi della testa
```

Le caratteristiche di estremità si possono specificare anche separatamente dopo `DS` e `DE`, oppure dopo `RS` e `RE`:

```
; bullone M10
L20 DS10 FI0.5 DE10 CH1 ; raccordo sull'estremità del bullone, smusso in salita tra bullone e testa
L6 DS19.6 CH0 DE19.6 CH0.5 ; nessuno smusso dove la testa tocca il gambo, piccolo smusso sulla sommità della testa
```

`CH0` e `FI0` indicano nessuna caratteristica. Le dimensioni di smussi e raccordi si misurano lungo la distanza orizzontale `L` del segmento. Le caratteristiche iniziale e finale insieme devono stare nella lunghezza del segmento. Ogni caratteristica deve anche stare nello spallamento radiale adiacente o nel segmento dritto/conico vicino, in corrispondenza di un angolo continuo.

Smussi e raccordi al momento non sono supportati per i segmenti `CONV` o `CONC`.

## Utensili

Si presume che l'utensile sia azzerato sull'asse e che tocchi il grezzo da destra.

Per usare un utensile da taglio standard, ad esempio MGMN200, specifica `TOOL RECT R0.2 L2`, dove R è il raggio dello spigolo e L definisce la larghezza dell'utensile.

Se usi una placchetta rotonda come RPMT10, definiscila con `TOOL ROUND R5`, dove R è il raggio dello spigolo.

Per usare un utensile con angolo punta, ad esempio [DCGT 070202](https://www.google.com/search?tbm=isch&q=DCGT+070202), specifica raggio utensile, lunghezza del tagliente, rotazione e angolo punta così:

```
TOOL ANG R0.2 L7.75 A30 NA55
```

Il pulsante Utensile dell'editor online può compilare queste righe `TOOL` standard partendo da placchette preimpostate e mostrare la stessa forma dell'utensile usata dal pianificatore.

## Profondità di passata e passata di finitura

La profondità di passata predefinita è 0,5 mm e si può cambiare, ad esempio a 1 mm. La passata di finitura predefinita è 0,1 mm.

```
DEPTH CUT1 FINISH0.2
```

## Avanzamenti e velocità

La velocità di taglio predefinita è 50 mm/min, quella di troncatura 10 mm/min, quella di spostamento 200 mm/min. Si possono regolare con una riga FEED:

```
FEED MOVE200 PASS50 PART10 ; velocità in mm/min
```

## Lavorazione in serie

Puoi definire e tagliare più di un pezzo:

```
STOCK D20

L5 R5
L3 R9
L3

L5 R5
L3 R9
L3

L5 R5
L3 R9
L3
```

![image](https://github.com/kachurovskiy/lathecode/assets/517919/103f353a-4fa6-4354-9539-c0a814f7df25)

## Direzione degli assi

Per impostazione predefinita Z aumenta verso sinistra e X aumenta verso l'alto (in avanti). Questo rispetta la convenzione NanoEls, ma molte macchine industriali usano esattamente l'opposto. Per rendere il GCode generato compatibile con quelle macchine, usa la direttiva `AXES`:

```
STOCK D4
AXES RIGHT DOWN
L3 D3
```

## Tornitura e sfacciatura

Se preferisci asportare materiale per tornitura invece che per sfacciatura, usa la direttiva `MODE TURN`:

```
STOCK D4
MODE TURN
AXES RIGHT DOWN
L3 D3
```

## Per gli sviluppatori

Se vuoi modificare il codice dell'editor online, usa `npm run dev` per l'esecuzione locale, `npm test` per i test e `npm run build` per generare `docs/index.html`, la pagina web autonoma dell'editor.
