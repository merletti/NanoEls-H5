# NanoEls H5 — Manuale d'uso

Pannello Nextion NX8048P050 (5", 800×480) con interfaccia in italiano.
Riferimenti di questa edizione: TFT `h5_it.tft` (interfaccia IT 20261030) e firmware `h5-IT-20261105-v65.bin`.

Indice:

1. [Che cosa fa](#1-che-cosa-fa)
2. [Avvertenze di sicurezza](#2-avvertenze-di-sicurezza)
3. [Accensione e MENU](#3-accensione-e-menu)
4. [Le pagine delle modalità](#4-le-pagine-delle-modalità)
5. [LAVORAZIONE: lavorazione in corso](#5-lavorazione-lavorazione-in-corso)
6. [Inserire i valori](#6-inserire-i-valori)
7. [Unità di misura](#7-unità-di-misura)
8. [PASSO, PRINCIPI, PASSATE](#8-passo-principi-passate)
9. [Assi, finecorsa e jog](#9-assi-finecorsa-e-jog)
10. [Le modalità una per una](#10-le-modalità-una-per-una)
11. [Procedure passo-passo](#11-procedure-passo-passo)
12. [STOP, emergenze, ripristino](#12-stop-emergenze-ripristino)
13. [Messaggi del display](#13-messaggi-del-display)
14. [Problemi frequenti](#14-problemi-frequenti)
15. [Pagine di servizio](#15-pagine-di-servizio)
16. [File, aggiornamenti e backup](#16-file-aggiornamenti-e-backup)

---

## 1. Che cosa fa

È un ELS (Electronic Lead Screw): legge la rotazione del mandrino con un encoder e
comanda i motori passo-passo di carro (asse Z) e trasversale (asse X), più l'asse Y
se è installato.

In pratica:

* in **INGRANAGGI / X-INGRANAGGI** sostituisce la cascata di ingranaggi: l'asse avanza
  di PASSO mm per ogni giro di mandrino;
* in **TORNITURA / SPIANATURA / FILETTATURA / TRONCATURA / ELLISSE / SCANALATURA**
  esegue da solo una serie di passate con profondità crescente fra due finecorsa;
* nelle altre modalità fa cono, avanzamento asincrono, programmi G-code, joystick,
  asse Y.

Il pannello è organizzato in tre livelli: **MENU** (scelta della modalità o del
servizio), **pagina della modalità** (impostazione dei valori) e **LAVORAZIONE**
(comandi e quote durante il lavoro).

## 2. Avvertenze di sicurezza

Leggere prima di accendere l'ELS.

1. **Con ELS acceso il carro può muoversi appena giri il mandrino, anche a mano.**
   Con passo diverso da zero la posizione dell'asse è imposta dalla rotazione del
   mandrino: non appoggiare le mani fra carro e contropunta e non girare il mandrino
   per controllo se l'ELS è acceso.
2. **AVVIA accetta in un solo tocco tutte le conferme e fa partire la macchina.**
   Nella pagina LAVORAZIONE il tasto verde avvia subito con i valori già impostati
   nella pagina modalità: controllare PASSO, PASSATE, LATO e FINECORSA prima di
   premerlo. La sola apertura della pagina modalità o di LAVORAZIONE non fa partire
   nulla.
3. **Non cambiare PASSO o PRINCIPI mentre la macchina sta filettando.** La quota di
   riferimento viene riazzerata e il filetto risulta sbagliato. Fermare, cambiare,
   ripartire.
4. **Non disabilitare un asse mentre la macchina sta lavorando.** I passi continuano a
   essere contati ma il motore è diseccitato: la quota mostrata non corrisponde più a
   quella reale.
5. **MAX QUI e MIN QUI funzionano solo a ELS spento.** A ELS acceso il pannello
   risponde `SPEGNI PRIMA`.
6. Il finecorsa è una **protezione software**: non sostituisce i finecorsa meccanici.
7. In emergenza (`ESTOP`) la macchina non risponde più ai comandi: spegnere e
   riaccendere il controller dopo aver controllato la meccanica.

## 3. Accensione e MENU

1. Accendere controller e display. Il pannello mostra il **MENU**.
2. Il firmware è già installato; il TFT va ricaricato solo quando si aggiorna
   l'interfaccia (vedi §16).
3. In alto a destra c'è lo stato dell'ELS:

| Scritta | Significato |
|---|---|
| `ELS OFF` | ELS spento, gli assi non seguono il mandrino |
| `ELS ON` | ELS acceso e in movimento sincronizzato |
| `ELS SIN` | acceso, in attesa della fase corretta del mandrino prima di innestare |

Toccare il riquadro `ELS` commuta lo stato; a ELS acceso lo stesso tocco lo spegne.

### Le tredici modalità

| Card | Modalità | Sottotitolo |
|---|---|---|
| F1 | INGRANAGGI | Gearbox |
| F2 | FILETTATURA | Threading |
| F3 | TORNITURA | Turning |
| F4 | SPIANATURA | Facing |
| F5 | CONO | Cone |
| F6 | TRONCATURA | Parting |
| F7 | ELLISSE | Ellipse |
| F8 | ASINCRONO | Async |
| F9 | G-CODE | G-code |
| F10 | ASSE Y | Y axis |
| F11 | JOYSTICK | Joy |
| F12 | X-INGRANAGGI | X gearbox |
| F13 | SCANALATURA | Grooving |

Toccando una card si apre la pagina della modalità: la modalità viene già selezionata
(e l'ELS si spegne se era acceso), ma la macchina non parte.

### La riga di servizio

In basso ci sono cinque voci:

| Voce | Apre |
|---|---|
| `COMANDO` | il controllo manuale degli assi e il tastierino (§15) |
| `GCODE` | l'elenco dei programmi G-code salvati (§15) |
| `SETUP` | le impostazioni della macchina (§15) |
| `WIFI` | nome rete, password e stato della connessione (§15) |
| `INFO` | firmware, versione TFT, indirizzo IP, memoria libera (§15) |

La striscia in basso mostra un suggerimento o lo stato corrente, ad esempio
`MENU OFF`; a destra compare la data dell'interfaccia (`IT 20261030`).

## 4. Le pagine delle modalità

Tutte le pagine F1–F13 hanno la stessa struttura.

**In alto** il nome della modalità e il sottotitolo `Modalità Fn · English`.
Su FILETTATURA, a sinistra del nome, compare il riquadro del senso del filetto
(`SENSO DX` o `SENSO SX`).

**A sinistra** i campi della modalità. Ogni campo ha:

* il **riquadro del valore**: toccandolo si apre il tastierino numerico (§6);
* i due tasti **`−`** e **`+`**: correggono il valore di uno scalino
  (PASSO: 0,01 mm o 0,001"; in TPI 1 filetto; PRINCIPI e PASSATE: 1).

Alcuni campi non si digitano ma si commutano toccandoli o con `‹` `›`:

* `LATO` — ESTERNO / INTERNO (tornitura, cono, troncatura, ellisse);
* `DIREZIONE` — DX → SX / SX → DX (spianatura), AVANTI / DIETRO (scanalatura);
* `SENSO` — `+` / `−` (asincrono, asse Y);
* `SENSO DX/SX` — senso del filetto; a ELS acceso la pressione è rifiutata con
  `SPEGNI PRIMA`.

**A destra** la card riassuntiva: il disegno della lavorazione con le misure, la riga
`STATO` (OFF, ON, SIN, ESTOP), la sigla `MODALITÀ Fn` e in fondo il valore derivato
dalle misure (`AVANZ.`, `VELOC.`, `RAPPORTO`, `RIDUZ. TOTALE`). I valori derivati
sono in sola lettura: cambiano da soli quando si modificano le quote.

**In basso** due tasti:

* **`ATTIVA MODALITÀ`** (verde): applica la modalità con i valori correnti e apre la
  pagina LAVORAZIONE. Non fa partire il moto.
* **`ANNULLA`** (grigio): torna al MENU. La modalità resta quella selezionata.

I finecorsa non presenti come campo (per esempio i finecorsa X in FILETTATURA) si
impostano in LAVORAZIONE con `MAX QUI` / `MIN QUI` (§9), oppure in
`SETUP → LIMITI E FINECORSA`.

## 5. LAVORAZIONE: lavorazione in corso

Dopo `ATTIVA MODALITÀ` il pannello apre la pagina **LAVORAZIONE**. È la pagina da cui
si comanda il lavoro.

**In alto** — `PASSO` (mm/giro), `PRINCIPI`, `PASSATE`, `SENSO` (DX/SX), `TIPO`
(ESTERNO/INTERNO) e il riquadro blu con il nome della modalità. Toccando `PASSO`,
`PRINCIPI` o `PASSATE` si apre il tastierino; a ELS acceso compare `SPEGNI PRIMA`.
Il tasto `‹ MENU` in alto a destra torna al MENU senza fermare il lavoro.

**Card assi X (rosso), Y (verde), Z (blu)** — la riga grande è la posizione attuale in
mm (o pollici), `MAX` e `MIN` sono i due finecorsa. Sotto:

* `ZERO` — azzera la posizione dell'asse (non tocca i finecorsa); conferma `ZERO X`,
  `ZERO Y` o `ZERO Z`;
* `MAX QUI` — memorizza la posizione attuale come finecorsa MAX;
* `MIN QUI` — memorizza la posizione attuale come finecorsa MIN.

`MAX QUI` e `MIN QUI` funzionano solo a ELS spento; a ELS acceso rispondono
`SPEGNI PRIMA`. Se l'asse non è abilitato rispondono `ASSE NON USATO`. Se il nuovo
MAX finisce sotto il MIN (o viceversa) il valore è rifiutato con `MAX SOTTO IL MIN` o
`MIN SOPRA IL MAX`.

**Statistiche** — `GIRI` (giri del mandrino dall'accensione), `GIRI/MIN`, `ANGOLO` in
gradi e `PASSATA` (passata corrente / totale).

**STATO e AVVIA/STOP** — la riga `STATO` mostra `OFF`, `ON` o `SIN`; in emergenza
mostra `ESTOP`. Il riquadro verde è il tasto:

* `AVVIA` — accende e avvia in un solo tocco, accettando insieme tutte le conferme
  della modalità con i valori già impostati (passate, lato, rapporto, posizionamento).
  È il comportamento normale per tutte le modalità tranne G-CODE.
* `STOP` — spegne subito e ferma il movimento.
* In **G-CODE** le conferme restano separate: un tocco conferma il programma, un
  altro conferma il mandrino e avvia.

Se mancano i finecorsa obbligatori il tasto fa solo beep e la striscia mostra
`Imposta finecorsa` (Z) oppure `Imposta finecorsa X`. In FILETTATURA, se il mandrino
non sta girando, dopo `AVVIA` lo stato passa a `SIN` ed è normale: appena il mandrino
gira la macchina innesta e parte.

**Jog** — `← Z−`, `Z+ →`, `↑ X+`, `↓ X−` muovono l'asse a pressione mantenuta; al
rilascio il movimento si ferma. A ELS acceso il jog è consentito solo in INGRANAGGI,
X-INGRANAGGI, ASINCRONO, CONO, ASSE Y e JOYSTICK; nelle modalità a passate e in
G-CODE un jog spegne l'ELS. Il pannello rilascia da solo il jog dopo 15 secondi di
pressione continua.

## 6. Inserire i valori

Toccando il riquadro di un valore si apre il **tastierino numerico**:

```
1 2 3        OK
4 5 6
7 8 9     ANNULLA
. 0 ←
```

* cifre `1…9`, `0`, **`.`** (punto decimale), **`←`** (cancella l'ultima cifra),
  **`OK`** (conferma), **`ANNULLA`** (esce senza modificare);
* si possono digitare fino a **12 caratteri**;
* il punto decimale è uno solo; se si digita per primo, il pannello antepone `0`;
* la prima cifra digitata **sostituisce** il valore precedente;
* un valore assente o vuoto (per esempio un finecorsa non impostato) si può digitare
  direttamente.

Il valore digitato è interpretato nell'unità attiva:

| Unità | Esempio | Significato |
|---|---|---|
| MM | `1.25` | 1,25 mm |
| POL | `0.125` | 0,125 pollici |
| TPI | `8` | 8 filetti per pollice |
| PASSATE / PRINCIPI | `4` | numero intero |
| CONO FILETTO | `0.05` | rapporto conico (0 = cilindrico) |

Nella pagina **COMANDO** esiste anche una riga numerica diretta (`STOP` e `1…9`, `0`,
`CANC`, `OK`) senza punto decimale: in millimetri le cifre sono millesimi
(`1500` = 1,5 mm), in pollici millesimi di pollice (`100` = 0,100"), in TPI filetti per
pollice. Il pannello ne mostra l'anteprima come `Usa 1.500?`.

## 7. Unità di misura

Il tasto `MISURA` (pagina COMANDO) e la riga `MISURA` in
`SETUP → UNITÀ E FORMATO` ciclano **MM → POL → TPI**.

* MM: quote in millimetri, passo in mm/giro.
* POL: quote in pollici, passo in pollici/giro.
* TPI: passo espresso in filetti per pollice (filettature in pollici).

Cambiare unità cambia la scala con cui sono mostrati e digitati i valori; la posizione
meccanica non si sposta. In TPI il PASSO è un numero di filetti per pollice: per un
passo metrico usare MM.

## 8. PASSO, PRINCIPI, PASSATE

**PASSO** è il parametro più importante. Significato a seconda della modalità:

| Modalità | PASSO significa |
|---|---|
| INGRANAGGI, X-INGRANAGGI, TORNITURA, SPIANATURA, TRONCATURA, FILETTATURA, ELLISSE | mm di avanzamento per giro di mandrino |
| CONO | avanzamento Z per giro; la X segue dal rapporto cono |
| ASINCRONO, SCANALATURA, ASSE Y | velocità di avanzamento indipendente dal mandrino (mm/s, o °/s con asse Y rotativo) |

Segno del PASSO:

* positivo: passata da MIN verso MAX;
* negativo: passata da MAX verso MIN;
* in FILETTATURA il segno è il senso del filetto: positivo `DX` (destro),
  negativo `SX` (sinistro);
* in TRONCATURA il segno è il lato: positivo esterno, negativo interno.

Si imposta digitando il valore e premendo `OK`, oppure con `−`/`+` (0,01 mm per
tocco; 0,001" in pollici; 1 TPI in TPI).

**PRINCIPI** è il numero di avvii multipli. Il movimento effettivo è
**PASSO × PRINCIPI**, ma il display mostra solo il PASSO: con 3 principi e passo 2
l'asse avanza 6 mm per giro mentre a video si legge `2`. Si usa nei filetti a più
principi e nelle modalità di ingranaggi; nelle altre modalità va lasciato a 1.

**PASSATE** è il numero di passate delle modalità a passate. In FILETTATURA le passate
totali diventano **PASSATE × PRINCIPI**: ogni principio viene tagliato per ogni
profondità.

Nella card laterale il valore `AVANZ.` (o `VELOC.`, `RAPPORTO`, `RIDUZ. TOTALE`)
mostra il risultato del calcolo ed è in sola lettura.

## 9. Assi, finecorsa e jog

### Impostare i finecorsa

I finecorsa definiscono il tratto di lavoro e, nelle modalità a passate, la
profondità. Il modo normale è dalla pagina LAVORAZIONE:

1. Portare l'asse nella posizione voluta con il jog (o a mano, se il motore è libero).
2. Toccare `MAX QUI` oppure `MIN QUI`: il finecorsa viene fissato lì.
3. Ripetere per l'altro finecorsa.

In alternativa, nella pagina modalità si possono digitare i finecorsa presenti come
campo (per esempio `FINE CORSA Z MAX`), e in `SETUP → LIMITI E FINECORSA` si possono
leggere e modificare `FINECORSA Z MAX/MIN` e `X MAX/MIN`.

### Quali finecorsa servono

| Modalità | Finecorsa richiesti |
|---|---|
| TORNITURA, SPIANATURA, FILETTATURA, ELLISSE | Z MIN e MAX, X MIN e MAX |
| TRONCATURA | X MIN e MAX |
| SCANALATURA | Z MIN e MAX, X MIN e MAX |
| INGRANAGGI, X-INGRANAGGI, ASINCRONO, ASSE Y, CONO, JOYSTICK | quelli usati dalla modalità |

Se manca un finecorsa obbligatorio, `AVVIA` fa solo beep e la striscia lo segnala.

### Significato in lavorazione

* **MIN** = inizio passata (con passo positivo), **MAX** = fine passata;
* sull'asse secondario (X in tornitura, Z in spianatura) i due finecorsa sono la quota
  di partenza e la profondità finale.

### Jog

Le sei frecce della pagina COMANDO (`↑ X+`, `↓ X−`, `↗ Y+`, `↘ Y−`, `← Z−`, `→ Z+`) e
le quattro di LAVORAZIONE (`← Z−`, `Z+ →`, `↑ X+`, `↓ X−`) muovono a pressione
mantenuta. Il verso fisico dipende dal cablaggio e dagli inversori configurati: se
`X+` va nella direzione sbagliata si corregge in configurazione, non dal pannello.

Non esiste un incremento "a scatti": la velocità è quella configurata in
`SETUP → VELOCITÀ E RAMPE` (`VEL. MANUALE Z/X/Y`). A ELS spento il jog è sempre
disponibile; a ELS acceso vale la regola del §5.

## 10. Le modalità una per una

| Card | Campi della pagina | Cosa comanda | Note |
|---|---|---|---|
| F1 INGRANAGGI | PASSO, PRINCIPI, FINECORSA Z MAX/MIN | Z sincronizzata col mandrino | la più semplice: sostituisce la cascata |
| F2 FILETTATURA | PASSO, PRINCIPI, CONO FILETTO, FINECORSA Z MAX; chip SENSO DX/SX | Z principale, X passate | profondità a passate decrescenti; X finecorsa da LAVORAZIONE |
| F3 TORNITURA | PASSO, PASSATE, LATO, FINECORSA Z MAX | Z principale, X passate | il classico cilindro in più passate |
| F4 SPIANATURA | PASSO, PASSATE, DIREZIONE, FINECORSA X MAX | X principale, Z passate | sfacciatura; la direzione è DX→SX o SX→DX |
| F5 CONO | ∅ GRANDE, ∅ PICCOLO, CORSA Z, LATO, FINECORSA X MAX | Z + X sincronizzati | il rapporto si calcola dalle misure |
| F6 TRONCATURA | PASSO, PASSATE, LATO, FINECORSA X MAX | solo X | il lato segue il segno del PASSO |
| F7 ELLISSE | PASSO, PASSATE, LATO, FINECORSA Z MAX | Z principale, X profilo | PASSO non modificabile in corsa |
| F8 ASINCRONO | PASSO, PRINCIPI, SENSO, FINECORSA Z MAX | Z a velocità costante | parte senza mandrino |
| F9 G-CODE | elenco programmi | X, Y, Z | richiede il mandrino in moto |
| F10 ASSE Y | PASSO Y, PRINCIPI, SENSO, FINECORSA Y MAX | Y | richiede asse Y configurato |
| F11 JOYSTICK | VELOCITÀ NORMALE, VELOCITÀ RAPIDA, ZONA MORTA, INGRESSI ATTIVI | Z e X con la leva, passo con potenziometro | richiede joystick |
| F12 X-INGRANAGGI | PASSO X, PRINCIPI, FINECORSA X MAX/MIN | X sincronizzata col mandrino | ingranaggi sull'asse trasversale |
| F13 SCANALATURA | PASSATE, RIDUZIONE SINISTRA, AVANZAMENTO, DIREZIONE, FINECORSA Z MAX/MIN | Z avanzamento, X passi | ogni passata è più corta per far uscire il truciolo |

Dettagli utili:

* **Card quotata**: a destra di ogni pagina c'è il disegno della lavorazione con le
  misure in chiaro. Nel riquadro in alto compare il PASSO (`P`, `P X`, `P Y`, `AV.`),
  nella quota il finecorsa usato dalla modalità (`Z MAX`, `X MAX`, `Y MAX`). Sotto al
  disegno ci sono `STATO` e la sigla `MODALITÀ F1…F13`.
* **Riga calcolata**: in fondo alla card compare un valore derivato dalle misure, in
  sola lettura: `AVANZ. mm/giro` (passo × principi) su INGRANAGGI, FILETTATURA,
  TORNITURA, SPIANATURA, TRONCATURA, ELLISSE, ASSE Y e X-INGRANAGGI; `VELOC. mm/min`
  su ASINCRONO; `VEL. MAX mm/min` su JOYSTICK; `RIDUZ. TOTALE mm` su SCANALATURA; sul
  CONO il valore derivato è il RAPPORTO.
* **CONO**: non si digita il rapporto. Si inseriscono ∅ grande, ∅ piccolo e corsa Z
  (che è il finecorsa Z MAX); il controller ricava la conicità
  `(Ø grande − Ø piccolo) / corsa Z` e la mostra come `1 : x`, dove
  `x = corsa Z / (Ø grande − Ø piccolo)`: è lo stesso valore delle tabelle dei coni
  (per un Morse 5, `1 : 19`). La X, che è radiale, si sposta di metà di quel valore
  per ogni mm di Z. Con misure mancanti o uguali la modalità non muove nulla.
* **TORNITURA / SPIANATURA / FILETTATURA**: la profondità scende a ogni passata
  (prima passata più profonda, poi via via più leggera); fra una passata e l'altra
  l'utensile rientra di 0,5 mm per non strisciare sul fondo. Nel filetto la prima
  passata è ancora più profonda e le successive molto più leggere.
* **TRONCATURA**: si muove solo la X, sincronizzata col mandrino. Il segno del PASSO
  decide il lato (positivo esterno, negativo interno) e il verso della passata.
* **FILETTATURA — senso**: destro o sinistro è il segno del PASSO, acquisito quando si
  dà ON (il chip `SENSO DX/SX` lo mostra). Modificarlo a ELS acceso non è possibile:
  il pannello risponde `SPEGNI PRIMA`. La sola rotazione del mandrino non cambia il
  senso.
* **FILETTATURA — esterno/interno**: la pagina non ha il campo `LATO`. Il tipo usato è
  quello memorizzato dall'ultima scelta fatta in un'altra modalità (per esempio
  `LATO` in TORNITURA o ELLISSE). Per un filetto interno impostarlo prima da una di
  quelle pagine, poi passare a FILETTATURA.
* **SCANALATURA**: Z avanza alla velocità di AVANZAMENTO da un finecorsa all'altro,
  poi la X si sposta del passo e ricomincia; ogni passata è più corta di RIDUZIONE
  SINISTRA.
* **JOYSTICK**: la riga `INGRESSI ATTIVI` elenca gli assi abilitati nella
  configurazione (`Z X Y` o solo quelli cablati). Se l'hardware non è configurato la
  card non fa nulla e la striscia lo dice (`Joystick disattivato`,
  `Joystick non collegato`).

## 11. Procedure passo-passo

### A. Filettare (FILETTATURA)

1. MENU → `FILETTATURA`.
2. Unità: `MISURA` su `MM` (o `TPI` per filetti in pollici) dalla pagina COMANDO.
3. Toccare `PASSO` e digitare il passo (esempio M8 passo 1,25: `1.25`), poi `OK`.
4. `PRINCIPI`: lasciare 1 per un filetto normale.
5. `CONO FILETTO`: `0` per filetto cilindrico; altrimenti il rapporto conico.
6. `FINE CORSA Z MAX`: fine del filetto (con passo positivo la passata va da MIN a
   MAX).
7. Chip `SENSO DX/SX`: `DX` per filetto destro, `SX` per sinistro.
8. `ATTIVA MODALITÀ`: si apre LAVORAZIONE.
9. A ELS spento impostare i finecorsa mancanti sulla X: posizionare l'utensile,
   `MAX QUI` / `MIN QUI`. Per filetto esterno `MIN` è la quota di partenza e `MAX` la
   profondità finale; per interno il contrario.
10. `AVVIA`: la macchina va al punto di partenza, la X scende alla prima profondità e
    lo stato passa a `SIN`.
11. Avviare il mandrino a giri bassi: l'ELS innesta e taglia la prima passata.
12. Ogni passata: taglio fino al finecorsa, rientro X di 0,5 mm, ritorno rapido al
    punto di partenza, nuova profondità. La striscia mostra `Passata i di n`.
13. A fine passate il carro torna al punto di partenza e l'ELS si spegne da solo con un
    segnale acustico.
14. Per anticipare la fine: in TORNITURA/SPIANATURA/FILETTATURA, con ELS acceso,
    premere di nuovo `AVVIA` per passare subito alla profondità successiva.
    Attenzione: la X scende immediatamente.

### B. Tornire (TORNITURA)

1. MENU → `TORNITURA`.
2. Digitare l'avanzamento per giro (esempio `0.1`) e `OK`.
3. `PASSATE`: numero di passate.
4. `LATO`: `ESTERNO` o `INTERNO`.
5. `FINE CORSA Z MAX`: fine della passata; il MIN si imposta da LAVORAZIONE.
6. `ATTIVA MODALITÀ`, poi completare i finecorsa X e Z in LAVORAZIONE.
7. `AVVIA`: il carro va all'angolo di partenza, attende la fase (`SIN`) ed esegue le
   passate.
8. A fine lavoro ritorno automatico e ELS spento.

### C. Spianare (SPIANATURA)

Come la tornitura, ma il PASSO è l'avanzamento **radiale** per giro e la pagina chiede
`DIREZIONE` (`DX → SX` o `SX → DX`); il finecorsa Z definisce la larghezza della
faccia e il finecorsa X la profondità.

### D. Troncare (TRONCATURA)

1. MENU → `TRONCATURA`.
2. PASSO con il segno giusto: positivo esterno, negativo interno. `LATO` mostra il
   lato ricavato dal segno; toccarlo inverte il segno del PASSO (solo a ELS spento).
3. `PASSATE`, `FINE CORSA X MAX`.
4. `ATTIVA MODALITÀ`; in LAVORAZIONE impostare il finecorsa X mancante.
5. `AVVIA` per partire.

### E. Cono (CONO)

1. MENU → `CONO`.
2. Digitare `∅ GRANDE`, `∅ PICCOLO` e `CORSA Z`; il `RAPPORTO` in fondo alla card si
   aggiorna da solo (`1 : 19` per un Morse 5).
3. `LATO`, `FINE CORSA X MAX`.
4. `ATTIVA MODALITÀ`, poi `AVVIA`: la macchina conferma il rapporto calcolato e parte
   con il lato scelto.

### F. Scanalatura (SCANALATURA, F13)

1. MENU → `SCANALATURA`.
2. `PASSATE`, `RIDUZIONE SINISTRA` (accorciamento di ogni passata),
   `AVANZAMENTO` (mm/giro), `DIREZIONE`.
3. `FINECORSA Z`: toccare MAX o MIN e digitare il valore; `−`/`+` correggono l'ultima
   metà toccata.
4. `ATTIVA MODALITÀ`; completare gli altri finecorsa in LAVORAZIONE, poi `AVVIA`.

### G. Ingranaggi (INGRANAGGI / X-INGRANAGGI)

1. MENU → `INGRANAGGI` (o `X-INGRANAGGI`).
2. Digitare il PASSO (mm/giro) e `OK`; PRINCIPI a 1.
3. `ATTIVA MODALITÀ` → `AVVIA`: l'asse segue il mandrino come con la cascata
   meccanica.
4. `STOP` per fermare e togliere la sincronizzazione.

### H. Asincrono (ASINCRONO)

1. MENU → `ASINCRONO`.
2. `PASSO` = velocità in mm/s (`0.25` = 0,25 mm/s).
3. `ATTIVA MODALITÀ` → `AVVIA`: il carro parte subito, **senza** bisogno di girare il
   mandrino.
4. `STOP` per fermare.

### I. G-code (G-CODE)

1. Caricare i programmi dalla sezione **GCode** della UI web: si incolla il testo
   oppure si usa **Sfoglia file .gcode**, poi `Salva`. I nomi ammessi sono 2–32
   caratteri fra lettere, numeri, punto, trattino e underscore.
2. Dal MENU aprire `G-CODE` (card F9 o voce della riga di servizio): a sinistra
   l'elenco dei file salvati, a destra `DETTAGLI` con dimensione, righe e data.
3. Selezionare il programma, poi `ESEGUI`: il primo tocco chiede conferma
   (`TOCCA DI NUOVO PER ESEGUIRE`), il secondo entro 3 secondi avvia.
4. Se il mandrino sta già girando il programma parte; altrimenti compare
   `ACCENDI IL MANDRINO`: avviarlo e premere `AVVIA` in LAVORAZIONE.
5. Durante l'esecuzione sono attivi solo `STOP` e l'emergenza.
6. `ELIMINA` richiede due tocchi entro 3 secondi; `RICARICA ELENCO` rilegge la
   memoria.

### J. Joystick e asse Y

Richiedono l'hardware configurato. In `JOYSTICK` la leva muove Z e X, il potenziometro
regola il passo; `VELOCITÀ NORMALE` e `VELOCITÀ RAPIDA` sono in giri/s, `ZONA MORTA` in
unità ADC. In `ASSE Y` l'asse ruota alla velocità del PASSO Y.

## 12. STOP, emergenze, ripristino

**STOP** (`AVVIA/STOP` in LAVORAZIONE, `STOP` rosso in COMANDO, oppure il riquadro
`ELS` del MENU) spegne l'ELS immediatamente: il movimento si ferma subito, senza
completare la rampa. Funziona anche durante la digitazione e in G-code.

**STOP durante un jog** = emergenza: la macchina si blocca con `ESTOP - Spento in
manuale`. Serve spegnere e riaccendere.

**Cambiare modalità** spegne l'ELS e azzera il procedimento in corso.

**Emergenze** (`ESTOP` al posto di OFF/ON, la macchina non risponde più ai comandi):

| Messaggio | Causa |
|---|---|
| `ESTOP - Posizione fuori macchina` | passi comandati oltre la corsa massima configurata |
| `ESTOP - Spento in manuale` | STOP premuto durante un movimento manuale |
| `ESTOP - Impossibile segnare origine` | errore interno di sincronizzazione |
| `ESTOP - Impossibile ON/OFF` | errore interno durante l'accensione |

In tutti i casi: spegnere il pannello, controllare la meccanica, riaccendere.

**Ripristino** — `SETUP → RIPRISTINA`:

* `RIPRISTINA MACCHINA`: valori di fabbrica della macchina (passi, corse, backlash,
  finecorsa, velocità, unità, asse Y). Due tocchi entro 3 secondi; il controller si
  riavvia.
* `RIPRISTINA WIFI`: cancella rete e password. Due tocchi entro 3 secondi; il
  controller si riavvia.

Non è previsto un reset tenendo premuto STOP: il ripristino si fa da questa pagina.

## 13. Messaggi del display

La striscia in basso mostra per pochi secondi il messaggio dell'ultima azione, poi
torna allo stato della pagina (`MENU OFF`, `FILETTATURA OFF`, `COMANDO OFF`, …).

### Messaggi di stato (maiuscoli)

| Messaggio | Significato / cosa fare |
|---|---|
| `SPEGNI PRIMA` | operazione consentita solo a ELS spento |
| `ASSE NON USATO` | asse non abilitato: abilitarlo in configurazione |
| `MAX IMPOSTATO` / `MIN IMPOSTATO` | finecorsa memorizzato |
| `MAX SOTTO IL MIN` / `MIN SOPRA IL MAX` | finecorsa incoerente: rifiutato |
| `ZERO X` / `ZERO Y` / `ZERO Z` | posizione azzerata |
| `TOCCA DI NUOVO PER CONFERMARE` | azione distruttiva: secondo tocco entro 3 s |
| `TOCCA DI NUOVO PER ESEGUIRE` | avvio G-code: secondo tocco entro 3 s |
| `TOCCA DI NUOVO PER ELIMINARE` | eliminazione G-code: secondo tocco entro 3 s |
| `TOCCA DI NUOVO PER DIMENTICARE` | cancellazione WiFi: secondo tocco entro 3 s |
| `NESSUN PROGRAMMA` | non ci sono programmi G-code da eseguire |
| `PROGRAMMA NON VALIDO` | il file G-code è vuoto o illeggibile |
| `ACCENDI IL MANDRINO` | G-code pronto: avviare il mandrino |
| `G-CODE IN CORSO` | programma in esecuzione |
| `ELENCO AGGIORNATO` | elenco G-code riletto |
| `SALVATO, RIAVVIO...` / `RIAVVIO PER APPLICARE` | impostazioni salvate, riavvio |
| `RIPRISTINO, RIAVVIO...` | valori di fabbrica ripristinati |
| `WIFI CANCELLATO, RIAVVIO...` | rete WiFi cancellata |
| `IMPOSTA IL NOME RETE` | manca la SSID: aprirla e digitarla |
| `ESTOP - <causa>` | emergenza: spegnere e riaccendere |

### Messaggi della striscia nelle modalità

| Messaggio | Significato / cosa fare |
|---|---|
| `Usa 1.500?` | anteprima del numero digitato: `OK` conferma |
| `Imposta finecorsa` | manca un finecorsa Z: fissarlo prima di partire |
| `Imposta finecorsa X` | manca un finecorsa X (troncatura o modalità a passate) |
| `N passata?` / `N passate?` | numero di passate |
| `Esterno?` / `Interno?` | lato di lavoro (impostato con LATO) |
| `Da destra a sinistra?` / `Da sinistra a destra?` | spianatura: verso della passata |
| `Passo > 0, esterno` / `Passo < 0, interno` | troncatura: conferma del lato |
| `Rapporto cono 0.xxxxx?` | filetto: rapporto conico; 0 = cilindrico |
| `Vai Z… X…?` | il carro sta per spostarsi al punto di partenza |
| `Passata i di n` | passata in corso |
| `Nessun programma` / nome programma | G-code: scelta del programma |
| `Accendi il mandrino!` / `Mandrino ON. Vai?` | G-code: avvio del mandrino |
| `Imposta passo` | scanalatura o joystick accesi con passo 0 |
| `Diametro x.xx` | riposo: diametro in lavorazione (2× posizione X) |
| `Jog …`, `Sincro …`, `Rapido …` | direzione comandata dal joystick |
| `Avanzamento …` / `Avanzamento off` / `Avanzamento fermo` | stato joystick |
| `Joystick disattivato` / `Joystick non collegato` | hardware joystick assente o spento |
| `Passo +` / `Passo -` | passo regolato col joystick |

Molte condizioni di rifiuto danno solo un segnale acustico: avvio con finecorsa
mancanti, jog oltre il finecorsa, tasto non attivo.

## 14. Problemi frequenti

**AVVIA fa solo un beep.**
Mancano i finecorsa obbligatori (`Imposta finecorsa` / `Imposta finecorsa X`), il
passo è 0, oppure in G-code non c'è un programma valido.

**Il carro non si muove col mandrino.**
Controllare: ELS acceso (`ON`), PASSO diverso da 0, asse abilitato, finecorsa non già
raggiunto, stato non `SIN` con mandrino fermo.

**Il carro si muove appena sfioro il mandrino.**
È normale con ELS acceso: la posizione segue la rotazione. Se non serve, premere
`STOP` o `ELS OFF`.

**L'avanzamento è il doppio/triplo del previsto.**
Controllare PRINCIPI: moltiplica il passo e non è indicato nel campo PASSO.

**Il passo in TPI non torna.**
In TPI il PASSO è il numero di filetti per pollice (`8` = 8 TPI). Per passi metrici
usare MM.

**Ho toccato il quadrato dell'asse e il motore si è liberato.**
Quel tocco abilita/disabilita l'asse: deve restare abilitato durante il lavoro.
Riabilitarlo e rivedere la quota (i passi persi non vengono recuperati).

**MAX QUI / MIN QUI rispondono SPEGNI PRIMA.**
I finecorsa si impostano solo a ELS spento: premere `STOP`, posizionare l'asse,
toccare di nuovo il tasto.

**Il filetto esce interno invece che esterno (o viceversa).**
La pagina FILETTATURA non ha LATO: aprire TORNITURA (o ELLISSE), impostare `LATO` come
serve, poi tornare a FILETTATURA.

**Toccando una zona del pannello non succede nulla.**
Se un comando non risponde, l'area sensibile va corretta nel TFT: annotare quale zona
e segnalarlo.

## 15. Pagine di servizio

### COMANDO

Controllo manuale e tastierino rapido: stato ELS (`OFF`/`ON`), modalità attiva
(toccandola si torna al MENU), `PRINCIPI`, `PASSO`, `MISURA`, posizione X/Y/Z
(toccando il numero grande si azzera), le sei frecce di jog, `STOP` e la riga
numerica con `CANC`/`OK`. Non avvia cicli di lavorazione: serve per posizionare e
regolare.

### GCODE

Elenco dei programmi nella memoria del controller, con dimensione in kB. A destra
`DETTAGLI` (nome, dimensione, righe, data), `ESEGUI`, `ELIMINA`, `RICARICA ELENCO`.
La striscia mostra il numero di programmi e la memoria libera. I file si caricano
dalla UI web (§16).

### SETUP (IMPOSTAZIONI)

Sei sezioni, ognuna su pagine di 7 righe con `PREC`/`SUCC`:

| Sezione | Voci principali |
|---|---|
| PASSI ASSI | impulsi encoder, gioco encoder, passi motore Z/X/Y, vite Z/X mm/giro |
| LIMITI E FINECORSA | corsa max Z/X/Y, backlash Z/X/Y, distanza di sicurezza, finecorsa Z/X MAX/MIN |
| VELOCITÀ E RAMPE | velocità di avvio, accelerazione e velocità manuale per asse, ritardo e pausa step |
| UNITÀ E FORMATO | MISURA, mostra tachimetro, mostra angolo, passo manuale, asse Y attivo/rotativo |
| LINGUA E DISPLAY | lingua (ITALIANO), display (NX8048P050), firmware, servizio — sola lettura |
| RIPRISTINA | ripristina macchina, ripristina WiFi |

Toccare una riga apre il tastierino; `−`/`+` correggono di uno scalino; le voci
`SI/NO` e `MISURA` si commutano toccandole. Le modifiche si applicano al riavvio del
controller.

### WIFI

Mostra rete e password (sempre mascherata `********`), `CONNETTI`, `DIMENTICA`, stato
(`DISATTIVATO`, `CONNESSIONE`, `CONNESSO`, `AP SETUP`) e indirizzo IP. Toccando nome
rete o password si apre la tastiera; `CONNETTI` salva e riavvia; `DIMENTICA` richiede
due tocchi. Impostare la rete a controller spento: la striscia lo ricorda.

### INFO / STATO

Firmware, versione TFT (`IT 20261030`), indirizzo IP, tempo acceso, memoria libera ed
errori. È la pagina da guardare per trovare l'indirizzo della UI web.

## 16. File, aggiornamenti e backup

| File | Uso |
|---|---|
| `screen-it/h5_it.tft` | interfaccia per il pannello: copiarlo sulla SD come `h5.tft` (FAT32, radice) oppure caricarlo dalla UI web (*Aggiorna TFT Nextion*) |
| `screen-it/h5_it.HMI` | progetto Nextion modificabile, contiene gli sfondi |
| `firmware-it/h5-IT-20261105-v65.bin` | firmware italiano per ESP32-S3 (H5V65) |
| `screen-it/lavorazione_tft_bg.png` | sfondo della pagina LAVORAZIONE (picture 59) |

**Ordine di caricamento**: prima il firmware, poi il TFT.

* Firmware: dalla UI web (*Aggiorna firmware*) oppure con Arduino IDE; a ELS spento.
* TFT: dalla UI web (*Aggiorna TFT Nextion*) o da SD; il display deve essere
  alimentato dalla porta **POWER**, non da USB; durata ~6 minuti a 115200.
* Dopo il caricamento il pannello riparte dal MENU.
* I programmi G-code si caricano dalla sezione **GCode** della UI web (testo incollato
  o file `.gcode`).
* La configurazione della macchina, della tastiera e del WiFi si può scaricare e
  ricaricare dalla UI web per il backup; la password WiFi non viene mai mostrata.
* L'indirizzo della UI web è quello indicato in `INFO / STATO`.
