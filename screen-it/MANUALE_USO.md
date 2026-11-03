# NanoEls H5 — Manuale d'uso

Pannello Nextion NX8048P050 (5", 800×480) con interfaccia in italiano.
Riferimenti di questa edizione: TFT `h5_it.tft` (29/10/2026), firmware `h5-IT-20261028c.bin`.

Indice:

1. [Che cosa fa](#1-che-cosa-fa)
2. [Avvertenze di sicurezza](#2-avvertenze-di-sicurezza)
3. [Accensione](#3-accensione)
4. [Pagina 0: comandi di lavoro](#4-pagina-0-comandi-di-lavoro)
5. [Pagina 1: scelta della modalità](#5-pagina-1-scelta-della-modalità)
6. [Inserire i numeri](#6-inserire-i-numeri)
7. [Unità di misura](#7-unità-di-misura)
8. [PASSO, PRINCIPI, STEP](#8-passo-principi-step)
9. [Assi, finecorsa e jog](#9-assi-finecorsa-e-jog)
10. [Le modalità una per una](#10-le-modalità-una-per-una)
11. [Procedure passo-passo](#11-procedure-passo-passo)
12. [STOP, emergenze, reset](#12-stop-emergenze-reset)
13. [Messaggi della striscia in basso](#13-messaggi-della-striscia-in-basso)
14. [Problemi frequenti](#14-problemi-frequenti)
15. [File e backup](#15-file-e-backup)

---

## 1. Che cosa fa

È un ELS (Electronic Lead Screw): legge la rotazione del mandrino con un encoder e
comanda i motori passo-passo di carro (asse Z) e trasversale (asse X), più l'asse Y
se è installato.

In pratica:

* in **INGRANAGGI / X-INGRANAGGI** sostituisce la cascata di ingranaggi: il carro avanza
  di PASSO mm per ogni giro di mandrino;
* in **TORNITURA / SPIANATURA / FILETTATURA** esegue da solo una serie di passate con
  profondità crescente fra due finecorsa;
* nelle altre modalità fa cono, ellisse, troncatura, scanalatura, avanzamento
  asincrono, programmi G-code, joystick.

## 2. Avvertenze di sicurezza

Leggere prima di accendere l'ELS.

1. **Con ELS acceso il carro può muoversi appena giri il mandrino, anche a mano.**
   Con passo diverso da zero la posizione dell'asse è imposta dalla rotazione del
   mandrino: non appoggiare le mani fra carro e contropunta e non girare il mandrino
   per controllo se l'ELS è acceso.
2. **In alcune modalità OK accende e muove da solo.** Nelle modalità a passate (tornitura,
   spianatura, troncatura, filetto, ellisse, scanalatura) l'ultimo OK sposta il carro
   al punto di partenza con il mandrino fermo; la striscia in basso lo annuncia con
   `Vai Z… X…?`.
3. **Non cambiare PASSO o PRINCIPI mentre la macchina sta filettando.** La quota di
   riferimento viene riazzerata e il filetto risulta sbagliato. Fermare, cambiare,
   ripartire.
4. **Non disabilitare un asse mentre la macchina sta lavorando.** I passi continuano a
   essere contati ma il motore è diseccitato: la quota mostrata non corrisponde più a
   quella reale.
5. **STOP tenuto premuto per più di 3 secondi azzera quote, finecorsa e passo** (vedi §12).
6. Il finecorsa è una protezione software: non sostituisce i finecorsa meccanici.

## 3. Accensione

1. Inserire la SD con il file `h5_it.tft` rinominato **`h5.tft`** nella radice (FAT32) e
   accendere il pannello: il display carica il TFT e mostra pagina 0 con la striscia
   `Pronto - NanoEls`.
2. Il firmware è già installato; va ricaricato solo se si aggiorna.
3. Lo stato dell'ELS è scritto nel tasto in alto a sinistra:

| Scritta | Significato |
|---|---|
| `OFF` | ELS spento, gli assi non seguono il mandrino |
| `ON` | ELS acceso e in movimento sincronizzato |
| `SIN` | acceso, in attesa della fase corretta del mandrino prima di innestare |
| `ESTOP` | emergenza: serve spegnere e riaccendere |

Toccare il tasto `OFF/ON` commuta lo stato. A ELS acceso **lo stesso tasto funziona da
STOP** (vedi §12).

Il tasto blu in alto (`INGR.`, `TORN.`, …) mostra la modalità attiva: toccarlo apre la
pagina 1 con l'elenco delle modalità.

## 4. Pagina 0: comandi di lavoro

### Riga alta

| Zona | Cosa mostra | Cosa fa |
|---|---|---|
| `OFF` / `ON` (sinistra) | stato ELS | tocco: accende/spegne, a ELS acceso = STOP |
| `MODALITA` + sigla (blu) | modalità attiva | tocco: apre pagina 1 |
| `PRINCIPI` + numero | numero di avvii multipli | tocco: aumenta di 1 (dopo 3 s di pausa riparte da 1) |
| `PASSO` + valore | passo in mm/giro (o velocità) | tocco sul valore: inverte il segno (filetto sinistro) |
| `MISURA` + `MM`/`POL`/`TPI` (verde) | unità attiva | tocco: cambia unità |
| `+` rosso / `−` blu | — | aumentano/diminuiscono passo, passate o principi secondo la fase |

### Riga 2

| Zona | Significato |
|---|---|
| `STEP` | incremento di un tocco sulle frecce (1 → 0,1 → 0,01 mm; in pollici 0,1" → 0,01" → 0,001"). Tocco sul valore: passa al successivo |
| `GIRI/MIN` | giri del mandrino |
| `GIRI` | giri accumulati dall'ultimo azzeramento |
| `ANGOLO` | angolo del mandrino in gradi (0–360) |

Il tocco sui valori `GIRI` e `ANGOLO` equivale a STOP.

### Card assi X (rossa), Y (verde), Z (blu)

```
ASSE X                     ON
▲ MAX    1.234    5.678 ▼ MIN
         [ X ]  0.000
```

* **Numero grande** = posizione dell'asse rispetto allo zero. Tocco: azzera la posizione.
* **MAX / MIN** = i due finecorsa software. I numeri piccoli sotto le etichette sono le
  **distanze residue** dalla posizione attuale a quel finecorsa (vuoto = finecorsa non
  impostato), non la quota assoluta.
* **Fascia MAX/MIN**: tocco = imposta il finecorsa nella posizione attuale; un secondo
  tocco lo cancella. Se prima si digita un numero, il finecorsa viene messo a quella
  distanza dalla posizione attuale.
* **Pillola `ON`**: tocco sul quadrato dell'asse (X, Y, Z) = abilita/disabilita l'asse
  (motore eccitato o libero).
* Con un numero digitato, il tocco sul quadrato interpreta il numero come diametro e
  imposta lo zero X di conseguenza.

### Sei tasti freccia

`↑ X+` `↓ X−` `↗ Y+` `↘ Y−` `← Z−` `→ Z+`: jog manuale a pressione mantenuta.
Con STEP = 1 mm (o 0,1") il movimento è continuo finché si tiene premuto; con gli
incrementi piccoli è a scatti. Funzionano a ELS spento e nelle modalità semplici
(ingranaggi, asincrono, cono, asse Y, joystick); in una modalità a passate un tocco di
freccia **spegne l'ELS**.

### Tastierino

`0…9`, `STOP` (rosso), `CANC` (blu), `OK` (verde). Vedi §6.

## 5. Pagina 1: scelta della modalità

Dodici card e il chip `SCANALATURA`:

| Card | Modalità | Sigla in pagina 0 |
|---|---|---|
| INGRANAGGI | carro sincronizzato col mandrino | `INGR.` |
| X-INGRANAGGI | trasversale sincronizzata col mandrino | `X-ING` |
| TORNITURA | passate longitudinali | `TORN.` |
| SPIANATURA | passate radiali (sfacciatura) | `SPIAN.` |
| CONO | conicità X/Z | `CONO` |
| TRONCATURA | taglio radiale a passate | `TRONC.` |
| FILETTATURA | filettatura anche a più principi | `FILETT.` |
| ELLISSE | profilo ellittico | `ELLIS.` |
| G-CODE | esecuzione programmi | `G-CODE` |
| ASINCRONO | avanzamento a velocità costante | `ASINC.` |
| ASSE Y | asse Y sincronizzato | `ASSE Y` |
| JOYSTICK | comando con leva | `JOY` |
| SCANALATURA (chip in alto) | cave/scanalature | `SCAN.` |

Tocco su una card: la modalità viene impostata e si torna a pagina 0.
Cambiare modalità **spegne l'ELS** e azzera il procedimento in corso.
`‹ INDIETRO` riporta a pagina 0 senza cambiare nulla.

## 6. Inserire i numeri

1. Digitare le cifre: compaiono nella striscia in basso come anteprima `Usa 1.500?`.
2. `OK` conferma il valore. Se non c'è nulla da confermare, `OK` esegue il passo
   successivo della procedura o accende l'ELS.
3. `CANC` cancella l'ultima cifra. Attenzione: `CANC` seguito da `OK` conferma **0**,
   cioè azzera il valore in corso.
4. `+` / `−` con cifre digitate correggono il numero; senza cifre cambiano passo,
   passate o principi secondo la fase.
5. Massimo 8 cifre: alla nona il numero digitato si azzera e si riparte.

Il valore digitato viene interpretato secondo l'unità attiva:

| Unità | Cifre | Esempio |
|---|---|---|
| MM | millesimi di mm | `1500` = 1,5 mm — `100` = 0,1 mm |
| POL | millesimi di pollice | `100` = 0,100" |
| TPI | filetti per pollice (interi) | `8` = 8 filetti per pollice |
| rapporto cono (solo filetto conico) | cifre / 100000 | `50000` = 0,5 |

Non esiste il tasto decimale: il numero è sempre intero e l'unità decide la scala.

## 7. Unità di misura

Il tasto `MISURA` cicla **MM → POL → TPI**.

* MM: quote in millimetri, passo in mm/giro.
* POL: quote in pollici, passo in pollici/giro.
* TPI: passo espresso in filetti per pollice (per filettature in pollici).

Cambiare unità riporta STEP al valore di default dell'unità scelta.

## 8. PASSO, PRINCIPI, STEP

**PASSO** è il parametro più importante. Significato a seconda della modalità:

| Modalità | PASSO significa |
|---|---|
| INGRANAGGI, X-INGRANAGGI, TORNITURA, SPIANATURA, TRONCATURA, FILETTATURA | mm di avanzamento per giro di mandrino |
| CONO | avanzamento Z per giro (la X segue dal rapporto cono) |
| ASINCRONO, SCANALATURA, ASSE Y | velocità di avanzamento (mm/s), **non** legata al mandrino |
| ELLISSE | deve restare uguale a quello di avvio, altrimenti la modalità si spegne |

Segno del passo:

* positivo: passata da MIN verso MAX;
* negativo: passata da MAX verso MIN, e in troncatura significa lavorazione interna.

Si imposta digitando il valore e premendo `OK`; `+`/`−` lo incrementano/decrementano di
uno scalino.

**PRINCIPI** (numero sotto la scritta PRINCIPI) è il numero di avvii multipli.
Il movimento reale è **PASSO × PRINCIPI**, ma il display mostra solo il PASSO: con 3
principi e passo 2 il carro avanza 6 mm per giro mentre a video si legge `2`.
Si usa solo per filetti a più principi; in tutte le altre modalità deve restare 1.
Tocco sulla zona PRINCIPI: incrementa di 1; se si lascia passare più di 3 secondi e il
valore è maggiore di 1, il tocco successivo lo riporta a 1.
Nel filetto le passate totali diventano PASSATE × PRINCIPI.

**STEP** è la distanza percorsa da un tocco delle frecce, non la risoluzione della
macchina. Tre valori metrici (1 / 0,1 / 0,01 mm) e tre imperiali (0,1" / 0,01" / 0,001").
Con il valore grande il movimento è continuo finché si tiene premuto.

## 9. Assi, finecorsa e jog

### Impostare i finecorsa

I finecorsa definiscono il tratto di lavoro e, nelle modalità a passate, anche la
profondità.

1. Portare l'asse con le frecce (o a mano, se il motore è libero) nel punto voluto.
2. Toccare la fascia `MAX` oppure `MIN` della card: il finecorsa viene fissato lì.
3. Ripetere per l'altro finecorsa.
4. Per cancellarlo, toccare di nuovo la stessa fascia.

Se invece si digita un numero e poi si tocca la fascia, il finecorsa viene impostato a
quella distanza dalla posizione attuale (utile per quote precise).

Significato in lavorazione:

* **MIN** = inizio passata (con passo positivo), **MAX** = fine passata;
* sull'asse secondario (X in tornitura, Z in spianatura) uno dei due è la quota di
  partenza e l'altro la profondità finale.

### Distanze residue

I numeri piccoli sotto `MAX` e `MIN` dicono quanti mm mancano al finecorsa. Serve a
capire subito quanto spazio resta prima del fermo. Se sono vuoti, quel finecorsa non è
impostato.

### Jog

Le sei frecce muovono a pressione mantenuta. Il verso fisico dipende dal cablaggio e
dalla configurazione degli inversori: se `X+` va nella direzione sbagliata, il segno si
inverte in configurazione, non dal pannello.

A ELS spento il jog è sempre disponibile. A ELS acceso è disponibile solo nelle modalità
semplici; in quelle a passate un tocco di freccia spegne l'ELS (protezione contro i
movimenti accidentali durante una passata).

## 10. Le modalità una per una

| Modalità | Assi in movimento | Parametri richiesti | Note |
|---|---|---|---|
| INGRANAGGI | Z segue il mandrino | PASSO | la più semplice: sostituisce la cascata |
| X-INGRANAGGI | X segue il mandrino | PASSO | per lavorazioni radiali sincronizzate |
| ASINCRONO | Z a velocità costante | PASSO = mm/s | parte appena si dà ON, **senza mandrino** |
| CONO | Z + X sincronizzati | PASSO, diametro grande, diametro piccolo, corsa Z, esterno/interno | il rapporto si calcola dalle misure |
| TORNITURA | Z principale, X passate | PASSO, passate, finecorsa Z e X, esterno/interno | il classico cilindro in più passate |
| SPIANATURA | X principale, Z passa | come tornitura | sfacciatura; la 2ª fase chiede il verso |
| TRONCATURA | solo X | PASSO (segno), passate, finecorsa X | passo > 0 esterno, < 0 interno |
| FILETTATURA | Z principale, X passate | PASSO, principi, passate, finecorsa Z e X, esterno/interno, SENSO DX/SX, rapporto cono facoltativo | profondità a passate decrescenti |
| ELLISSE | Z principale, X profilo | PASSO costante, passate, 4 finecorsa | PASSO non modificabile in corsa |
| G-CODE | X, Y, Z | programma su memoria interna | solo con mandrino in moto |
| ASSE Y | Y | PASSO = velocità | richiede asse Y configurato |
| JOYSTICK | Z e X con la leva, Y regola passo | leva abilitata in configurazione | richiede joystick |
| SCANALATURA | Z avanzamento, X passi | PASSO = velocità Z, passate, 4 finecorsa | ogni passata è più corta per far uscire il truciolo |

Dettagli utili:

* **Card quotata**: a destra di ogni pagina di lavoro c'è il disegno della
  lavorazione con le misure in chiaro. Nel riquadro in alto compare il PASSO
  (`P`, `P X`, `P Y`, `AV.`), nella quota compare il finecorsa usato dalla
  modalità (`Z MAX`, `X MAX`, `Y MAX`); si aggiornano mentre si modificano i
  valori a sinistra. Sotto al disegno ci sono `STATO` (`OFF`, `ON`, `SIN`)
  e `MODALITÀ` con la sigla F1…F13 della pagina.
* **Riga calcolata (tutte le modalità)**: in fondo alla card di ogni pagina di lavoro
  compare un valore derivato dalle misure, in sola lettura: `AVANZ. mm/giro`
  (passo × principi) su INGRANAGGI, FILETTATURA, TORNITURA, SPIANATURA, TRONCATURA,
  ELLISSE, ASSE Y e X-INGRANAGGI; `VELOC. mm/min` su ASINCRONO; `VEL. MAX mm/min`
  su JOYSTICK; `RIDUZ. TOTALE mm` su SCANALATURA. Non si tocca: cambia da solo
  quando si modificano le quote. Sul CONO il valore derivato è il RAPPORTO.
* **CONO**: non si digita il rapporto. Si inseriscono Ø grande, Ø piccolo e corsa Z
  (che è il finecorsa Z MAX); il controller ricava la conicità
  `(Ø grande − Ø piccolo) / corsa Z` e la mostra come `1 : x`, dove
  `x = corsa Z / (Ø grande − Ø piccolo)`: è lo stesso valore delle tabelle dei coni
  (per un Morse 5, `1 : 19`). La X, che è radiale, si sposta di metà di quel valore
  per ogni mm di Z. Con misure mancanti o uguali la modalità non muove nulla.
* **TORNITURA / SPIANATURA / FILETTATURA**: la profondità scende a ogni passata (prima
  passata più profonda, poi via via più leggera); fra una passata e l'altra l'utensile
  rientra di 0,5 mm per non strisciare sul fondo. Nel filetto la prima passata è ancora
  più profonda e le successive molto più leggere.
* **TRONCATURA**: si muove solo la X, sincronizzata col mandrino.
* **FILETTATURA — senso**: destro o sinistro dipende dal segno del PASSO ed è acquisito
  quando si dà ON; modificarlo a ELS acceso non è possibile (va spento prima). La sola
  rotazione del mandrino non cambia il senso.
* **SCANALATURA**: Z avanza alla velocità del PASSO da un finecorsa all'altro, poi la X
  si sposta di un passo e ricomincia; ogni passata è leggermente più corta.
* **ASSE Y / JOYSTICK**: se l'hardware non è configurato la card non fa nulla e la
  striscia lo dice (`Joystick disattivato`, `Joystick non collegato`).

## 11. Procedure passo-passo

### A. Filettare (FILETTATURA)

1. Pagina 1 → `FILETTATURA` (si torna a pagina 0, ELS spento).
2. Unità: `MISURA` su `MM` (o `TPI` per filetti in pollici).
3. Digitare il passo e premere `OK`. Esempio filetto M8 passo 1,25: digitare `1250`.
   Il chip `SENSO DX/SX` nell'intestazione mostra il senso del filetto: `DX` = destro,
   `SX` = sinistro. Toccarlo commuta il senso (cambia il segno del PASSO); a ELS acceso
   la pressione è rifiutata con `SPEGNI PRIMA`. In alternativa si cambia segno toccando
   il valore `PASSO`.
4. PRINCIPI: lasciare 1 per un filetto normale.
5. Finecorsa Z: fissare `MIN` all'inizio del filetto e `MAX` alla fine (con passo
   positivo la passata va da MIN a MAX). Finecorsa X: `MIN` = diametro di partenza,
   `MAX` = profondità finale (per filetto esterno).
6. `OK` → `N passate?`: numero di passate, poi `OK`.
7. `OK` → `Esterno?` / `Interno?`: si commuta con le frecce `←` e `→`. In questa fase
   `+`/`−` regolano i PRINCIPI.
8. `OK` → `Rapporto cono …?`: mostra il valore di `CONO FILETTO`. Per filetto
   cilindrico lascialo a 0; per filetto conico impostalo nella pagina (o digita il
   nuovo valore, es. `5000` = 0,05) e `OK`.
9. `OK` → `Vai Z… X…?`: la striscia mostra quanto si sposterà il carro.
10. `OK` → ELS acceso: il carro va al punto di partenza, la X va alla prima profondità,
    compare `SIN` e la macchina attende la fase del mandrino.
11. Avviare il mandrino a giri bassi: l'ELS innesta e taglia la prima passata.
12. Ogni passata: taglio fino al finecorsa, rientro X di 0,5 mm, ritorno rapido al punto
    di partenza, nuova profondità. La striscia mostra `Passata i di n`.
13. A fine passate il carro torna al punto di partenza e l'ELS si spegne da solo con un
    segnale acustico.
14. Per anticipare la fine: `OK` durante una passata fa passare subito alla profondità
    successiva — attenzione, la X scende immediatamente.

### B. Tornire (TORNITURA)

1. Pagina 1 → `TORNITURA`.
2. Digitare l'avanzamento per giro (es. `100` = 0,1 mm/giro) e `OK`.
3. Finecorsa Z: `MIN` inizio passata, `MAX` fine passata.
4. Finecorsa X: per lavoro esterno `MIN` = diametro di partenza, `MAX` = profondità
   finale; per lavoro interno il contrario.
5. `OK` → `N passate?` → numero → `OK`.
6. `OK` → `Esterno?` / `Interno?` con le frecce `←`/`→` → `OK`.
7. `OK` → `Vai Z… X…?` → `OK`: il carro va all'angolo di partenza, attende `SIN`, esegue
   le passate.
8. A fine lavoro ritorno automatico e ELS spento.

### C. Spianare (SPIANATURA)

Come la tornitura, ma il PASSO è l'avanzamento **radiale** per giro e la fase 2 chiede
`Da destra a sinistra?` / `Da sinistra a destra?`; i finecorsa Z definiscono la larghezza
della faccia. La riga DIREZIONE mostra la scelta come `DX>SX` o `SX>DX`.

### D. Troncare (TRONCATURA)

1. `TRONCATURA`, passo con il segno giusto (positivo = esterno, negativo = interno).
   La riga LATO mostra il lato ricavato dal segno; toccarla (o `‹ ›`) inverte il
   segno del PASSO, con ELS spento.
2. Finecorsa X obbligatori: partenza e fondo taglio.
3. `OK` → `N passate?` → `OK` → fase 2 `Passo > 0, esterno` / `Passo < 0, interno` → `OK`.
4. `OK` su `Vai…` per partire.

### E. Cono (CONO)

1. Prima di attivare la modalità impostare i due diametri e la corsa Z (finecorsa Z MAX):
   nella pagina CONO del display o nella sezione **Cono** della UI web.
2. `CONO`, digitare il passo Z per giro e `OK`.
3. `Usa 1 : …?` mostra la conicità calcolata dalle misure, lo stesso valore delle
   tabelle dei coni (`1 : 19` per un Morse 5): `OK` per confermarlo.
   Il rapporto non si digita più.
4. `OK` → `Esterno?` / `Interno?` con le frecce → `OK` per partire.

### F. Scanalatura (SCANALATURA, chip in alto in pagina 1)

1. `SCANALATURA`, passo = velocità di avanzamento Z (mm/s).
2. Fissare i quattro finecorsa (corsa Z e posizioni X). Sulla riga del finecorsa
   Z, `−/+` corregge la metà toccata per ultima: `MAX` a sinistra, `MIN` a destra.
3. `OK` → `N passate?` → `OK` → esterno/interno → `OK` → `Vai…` → `OK`.

### G. Ingranaggi (INGRANAGGI / X-INGRANAGGI)

1. Pagina 1 → `INGRANAGGI`.
2. Digitare il PASSO (mm/giro) e `OK`.
3. `OK` accende l'ELS. Da quel momento il carro segue il mandrino: si lavora con
   l'avanzamento automatico come con la cascata meccanica.
4. `OFF` per fermare e togliere la sincronizzazione.

### H. Asincrono (ASINCRONO)

1. `ASINCRONO`, PASSO = velocità in mm/s (`1000` = 1 mm/s).
2. `OK` accende: il carro parte subito, **senza** bisogno di girare il mandrino.
3. `OFF` per fermare.

### I. G-code (G-CODE)

1. I programmi si caricano dalla sezione **GCode** della UI web: si incolla il
   testo oppure si usa **Sfoglia file .gcode**, poi `Salva` (i commenti vengono
   scartati se l'opzione è attiva).
2. `G-CODE`, `OK` → scelta del programma con `▲`/`▼` (`−` cancella il file selezionato).
3. `OK` → `Accendi il mandrino!`: avviare il mandrino a mano.
4. `OK` → il programma parte; la striscia mostra il comando in esecuzione.
5. Durante l'esecuzione sono attivi solo `STOP` e il tasto di emergenza.

### J. Joystick e asse Y

Richiedono l'hardware configurato. In `JOYSTICK` la leva muove Z e X, il potenziometro
regola il passo; la riga `INGRESSI ATTIVI` elenca gli assi abilitati nella
configurazione (`Z X Y` o solo quelli cablati). In `ASSE Y` l'asse Y ruota alla
velocità del PASSO.

## 12. STOP, emergenze, reset

**STOP** (`STOP` rosso, oppure il tasto `OFF/ON`, oppure tocco su `GIRI`/`ANGOLO`)
spegne l'ELS immediatamente: i passi pendenti vengono azzerati, il movimento si ferma
subito (non completa la rampa). Funziona sempre, anche durante la digitazione e in
G-code.

**STOP durante un jog** = emergenza: la macchina si blocca con il messaggio
`Spento in manuale`. Serve spegnere e riaccendere.

**STOP tenuto premuto più di 3 secondi e poi rilasciato** = reset generale:
finecorsa cancellati, passo a 0, posizioni e origini a zero, modalità INGRANAGGI,
unità MM, PRINCIPI 1, rapporto cono 0 (cilindrico). Usarlo solo quando si vuole ricominciare da zero.

**Emergenze** (`ESTOP` nella casella di stato, la macchina non risponde più ai comandi):

| Messaggio | Causa |
|---|---|
| `Posizione fuori macchina` | passi comandati oltre la corsa massima configurata |
| `Spento in manuale` | STOP premuto durante un movimento manuale |
| `Impossibile segnare origine` | errore interno di sincronizzazione |

In tutti i casi: spegnere il pannello, controllare la meccanica, riaccendere.

Il messaggio compare nella riga in basso come `ESTOP - <causa>`, la card `STATO`
del TFT passa a `ESTOP` e la casella di stato della UI web mostra `ESTOP` con la
stessa causa (dal firmware v52).

## 13. Messaggi della striscia in basso

| Messaggio | Significato / cosa fare |
|---|---|
| `Pronto - NanoEls` | riposo, nessuna operazione |
| `Usa 1.500?` | anteprima del numero digitato: `OK` conferma |
| `Imposta finecorsa` | manca un finecorsa Z: fissarlo prima di partire |
| `Imposta finecorsa X` | manca un finecorsa X (troncatura) |
| `N passata?` / `N passate?` | chiede il numero di passate |
| `Esterno?` / `Interno?` | chiede il lato di lavoro, si commuta con `←`/`→` |
| `Da destra a sinistra?` | spianatura: verso della passata |
| `Passo > 0, esterno` / `Passo < 0, interno` | troncatura: conferma del lato |
| `Rapporto cono 0.xxxxx?` | filetto: conferma il rapporto; 0 = cilindrico |
| `Usa 1 : x.xx?` | cono: conferma la conicità calcolata dalle misure (valore da catalogo) |
| `Rapporto 1 : x.xx` | cono in lavoro: conicità in uso (solo lettura) |
| `Vai Z… X…?` | sta per spostare il carro; `OK` per procedere |
| `Passata i di n` | passata in corso |
| `Imposta passo` | scanalatura/joystick accesi con passo 0 |
| `Accendi il mandrino!` | G-code: avviare il mandrino |
| `Mandrino ON. Vai?` | G-code pronto, `OK` per partire |
| `Diametro x.xx` | riposo: diametro in lavorazione (2× posizione X) |
| `Rapido …`, `Sincro …`, `Jog …` | direzione di movimento comandata dal joystick |
| `Joystick disattivato` / `non collegato` | hardware joystick assente o spento |
| `Passo +` / `Passo -` | passo regolato col joystick |

Molte condizioni di rifiuto danno solo un segnale acustico senza messaggio: avvio con
finecorsa mancanti, STEP uguale a zero, jog oltre il finecorsa.

## 14. Problemi frequenti

**Preme OK e non succede niente, solo un beep.**
Mancano i finecorsa obbligatori (`Imposta finecorsa`), oppure il passo è 0, oppure in
G-code non c'è un programma valido.

**Il carro non si muove col mandrino.**
Controllare: ELS acceso (`ON`), PASSO diverso da 0, asse abilitato (pillola `ON` sulla
card), finecorsa non già raggiunto.

**Il carro si muove appena sfioro il mandrino.**
È normale con ELS acceso: la posizione segue la rotazione. Se non serve, premere `OFF`.

**L'avanzamento è il doppio/triplo del previsto.**
Controllare PRINCIPI: moltiplica il passo e non è indicato nel campo PASSO.

**Il passo in TPI non torna.**
In TPI le cifre sono filetti per pollice interi (`8` = 8 TPI). Per passi metrici usare MM.

**Ho toccato il quadrato dell'asse e il motore si è liberato.**
Quel tocco abilita/disabilita l'asse: la pillola `ON` deve restare accesa durante il
lavoro. Riabilitarlo e rivedere la quota (i passi persi non vengono recuperati).

**Toccando una zona del pannello non succede nulla.**
Se un comando rapido (passo, STEP, posizione, MAX/MIN) non risponde, l'area sensibile va
corretta nel TFT: annotare quale zona e segnalarlo.

## 15. File e backup

| File | Uso |
|---|---|
| `h5_it.tft` | interfaccia per il pannello: copiarlo sulla SD come `h5.tft` (FAT32, radice) oppure caricarlo dalla Web UI (*Aggiorna display Nextion*) |
| `h5_it.HMI` | progetto Nextion modificabile, contiene gli sfondi |
| `h5-IT-20261103-v64.bin` | firmware italiano per ESP32-S3 (H5V64) |
| `lavorazione_tft_bg.png` | sfondo della pagina LAVORAZIONE (picture 59) |

Ordine di caricamento in caso di aggiornamento: prima il firmware, poi il TFT.
Per entrambi serve il controller **spento** (ELS OFF); il TFT richiede il display
alimentato dalla porta POWER, non da USB. Dopo il caricamento il pannello riparte
dal MENU.

## 16. Pagina LAVORAZIONE — lavorazione in corso

Quando si dà il via a una modalità di lavoro il pannello passa da solo alla
pagina **LAVORAZIONE**: dati della passata in alto, quote degli assi al centro,
statistiche e comando ON/OFF in basso.

**In alto** — `PASSO` (con `mm/giro`), `PRINCIPI`, `PASSATE`, `SENSO` (DX/SX o
ESTERNO/INTERNO) e `TIPO` (esterno/interno). La chip blu in alto a destra mostra
il nome della modalità in corso. Toccando PASSO, PRINCIPI o PASSATE si apre il
tastierino (solo a ELS spento).

**Card assi X, Y, Z** — la riga grande è la posizione attuale, `MAX` e `MIN` sono
i finecorsa. Sotto:

* `ZERO` → mette a zero la posizione dell'asse (non tocca i finecorsa);
* `MAX` / `MIN` → memorizzano la posizione attuale come finecorsa MAX o
  MIN. Funzionano solo a controller **spento**: se è acceso compare `SPEGNI
  PRIMA`. Se l'asse non è abilitato compare `ASSE NON USATO`.

**Statistiche** — `GIRI` (giri del mandrino dall'accensione), `GIRI/MIN`,
`ANGOLO` in gradi (0–360) e `PASSATA` (passata corrente / totale).

**STATO / AVVIA-STOP** — la riga `STATO` mostra `OFF` (spento), `ON` (acceso) o
`SIN` (acceso e in attesa della fase del mandrino). Dopo `ON` l'ELS esegue il
posizionamento iniziale e poi passa a `SIN`: appena il mandrino gira `SIN` torna
`ON` e parte la passata; se il mandrino resta fermo `SIN` rimane, è normale. Il
riquadro verde è il tasto: `AVVIA` accende in un solo tocco usando i dati già
impostati nella pagina modalità (i passi di conferma vengono accettati insieme),
`STOP` spegne. In G-CODE restano le conferme passo-passo di programma e mandrino.
Se mancano i finecorsa obbligatori il tasto fa solo beep e la riga in basso mostra
`Imposta finecorsa`.

**Jog** — `← Z−`, `Z+ →`, `↑ X+`, `↓ X−` muovono l'asse a pressione mantenuta;
al rilascio il movimento si ferma. A ELS acceso il jog è consentito solo nelle
modalità INGRANAGGI, X-INGRANAGGI, ASINCRONO, CONO, ASSE Y e JOYSTICK; in quelle a
passate un jog spegne l'ELS. La riga grande dell'asse si aggiorna durante il
movimento.

**`‹ MENU`** — torna al MENU senza spegnere nulla: la lavorazione continua e per
rivederla basta riaprire la modalità dal MENU.
