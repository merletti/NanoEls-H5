# Tabella componenti – H5 (Nextion 5" 800×480)

Riferimento per ricostruire le due pagine in Nextion Editor sugli sfondi nuovi
`screen-it/page0_bg.png` e `screen-it/page1_bg.png`.
I passi operativi, clic per clic, sono in
[GUIDA_NEXTION_EDITOR.md](GUIDA_NEXTION_EDITOR.md).

Gli **ID non si toccano** (tranne quelli nuovi in fondo): il firmware li usa per i tasti.
I nomi in tabella sono quelli che il firmware usa per scrivere i valori (`tX`, `bMode`, …):
**non rinominarli**.

---

## 0. Regole valide per tutti i componenti

1. **Immagini**: apri l'immagine di sfondo con *Picture → Add* (una per pagina) e poi
   seleziona la pagina e imposta **sta = image**, **pic =** numero dell'immagine.
2. **Stacca tutte le immagini dai componenti**: per ogni componente
   `pic = 0`, `pic2 = 0`, `picc = 0`, `picc2 = 0`.
   (le immagini factory non si possono estrarre, quindi tutto è ridisegnato a colori piatti)
3. **`bco` non è trasparente**: va sempre messo *uguale al colore che c'è sotto*,
   altrimenti si vede un rettangolo. Per questo i componenti sono sempre rientrati
   di qualche pixel dentro i riquadri dello sfondo.
4. **`isbr = 0`** (nessun bordo) su tutti.
5. **DualState**: `bco2 = bco` (se diverso, il tasto resta "acceso" dopo il tocco).
6. **Button**: `bco2` = colore premuto (tabella colori al punto 6).
7. **Allineamento testo** (in Nextion si imposta con `spax`/`spay` oppure con i pulsanti
   di allineamento nelle proprietà): le colonne "Allin." della tabella dicono
   sinistra / centro.
8. **Font**: crea 4 font nuovi (Fonts → Add, famiglia *DejaVu Sans* o *Arial*):
   `it16` (16 px), `it22` (22 px), `it30` (30 px), `it40` (40 px).
   DejaVu Sans serve per i glifi `↑ ↓ ↗ ↘ ← → ‹` usati nelle frecce e in INDIETRO.
   Includi anche il byte `0xDF` (il grado Nextion): il firmware lo manda per `°`
   in `tAngleVal` e nei messaggi. Se un font non lo ha, si vedrà `ß`.
9. Ordine di disegno = ordine nell'albero: i componenti **nuovi** stanno sopra a quelli
   vecchi (ID più alto), ed è voluto.

---

## 1. Colori

| Uso | HEX | RGB565 (valore da digitare nell'Editor) |
|---|---|---|
| sfondo pagina | #0A0A0C | `0841` |
| card scura (riga alta, riga 2, tasti numerici, card pagina 1) | #15161A | `18A3` |
| card assi X/Y/Z | #141519 | `10A3` |
| striscia messaggi | #101114 | `1082` |
| blu | #1A6DD6 | `1B7A` |
| rosso | #C81E2B | `C0E5` |
| verde | #16A34A | `1D09` |
| bianco testo | #F2F2F2 | `EF9D` |
| bianco testo 2 | #F5F5F7 | `F7BE` |
| bianco pieno | #FFFFFF | `FFFF` |
| grigio secondario | #9AA0A8 | `9D14` |
| grigio messaggi | #A8ADB4 | `A576` |
| pillola INDIETRO | #2B2D33 | `2966` |
| tasto freccia | #E9E9EE | `E75D` |
| premuto chiaro | #D0D0D6 | `CE7A` |
| premuto scuro | #24252C | `2125` |
| premuto rosso | #A81724 | `A0C4` |
| premuto blu | #1558AF | `1AD5` |
| premuto verde | #12853D | `1427` |

---

## 2. PAGINA 0 – componenti esistenti (da spostare/ridimensionare)

Colonne: **ID · Nome · Tipo · X · Y · W · H · bco · pco · Font · Allin. · Testo**

### 2.1 Riga alta (y 7…68)

| ID | Nome | Tipo | X | Y | W | H | bco | pco | Font | Allin. | Testo |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 3 | `bStatus` | Button | 11 | 12 | 90 | 52 | `EF9D` | `0841` | it30 | centro | `OFF` |
| 4 | `bMode` | Button | 116 | 12 | 160 | 52 | `1B7A` | `FFFF` | it30 | centro | `INGR.` |
| 5 | `tPitch` | Text | 400 | 28 | 193 | 32 | `18A3` | `EF9D` | it30 | centro | `1.500` |
| 6 | `bMeasure` | Button | 620 | 30 | 56 | 28 | `1D09` | `FFFF` | it22 | centro | `MM` |
| 42 | `bPlus` | DualState | 689 | 11 | 44 | 54 | `C0E5`/`C0E5` | — | — | — | — |
| 43 | `bMinus` | DualState | 746 | 11 | 44 | 54 | `1B7A`/`1B7A` | — | — | — | — |
| 50 | `bStarts` | DualState | 289 | 31 | 86 | 30 | `18A3`/`18A3` | — | — | — | — |

Note riga alta:

* `bPlus` / `bMinus` / `bStarts` sono **invisibili**: hanno lo stesso colore del tasto
  rosso/blu/pillola sotto, quindi non coprono il `+`, il `−` e la scritta `PRINCIPI`
  che sono disegnati nello sfondo.
* `bStarts` (ID 50) è l'area che tocca gli avvii multipli; il **numero** lo scrive il
  componente nuovo `tStarts` (ID 51) che sta sopra a `bStarts`.

### 2.2 Riga 2 – STEP / GIRI-MIN / GIRI / ANGOLO (y 74…125)

| ID | Nome | Tipo | X | Y | W | H | bco | pco | Font | Allin. | Testo |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 7 | `tStepVal` | Text | 40 | 91 | 150 | 33 | `18A3` | `EF9D` | it30 | sinistra | `1` |
| 8 | `tRPMVal` | Text | 236 | 91 | 155 | 33 | `18A3` | `EF9D` | it30 | sinistra | `0` |
| 9 | `tTurnsVal` | Text | 436 | 91 | 150 | 33 | `18A3` | `EF9D` | it30 | sinistra | `0.00` |
| 10 | `tAngleVal` | Text | 634 | 91 | 152 | 33 | `18A3` | `EF9D` | it30 | sinistra | `0.00°` |

### 2.3 Card assi (y 132…278)

| ID | Nome | Tipo | X | Y | W | H | bco | pco | Font | Allin. | Testo |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 36 | `dXMax` | DualState | 10 | 178 | 120 | 36 | `10A3`/`10A3` | — | — | — | — |
| 37 | `dXMin` | DualState | 136 | 178 | 118 | 36 | `10A3`/`10A3` | — | — | — | — |
| 13 | `tXUp` | Text | 55 | 152 | 76 | 22 | `10A3` | `9D14` | it16 | centro | `0.00` |
| 14 | `tXDown` | Text | 134 | 152 | 59 | 22 | `10A3` | `9D14` | it16 | centro | `0.00` |
| 11 | `bX` | Button | 18 | 219 | 54 | 50 | `C0E5` | `FFFF` | it30 | centro | `X` |
| 12 | `tX` | Text | 78 | 231 | 182 | 40 | `10A3` | `FFFF` | it30 | sinistra | `0.000` |
| 38 | `dYMax` | DualState | 275 | 178 | 120 | 36 | `10A3`/`10A3` | — | — | — | — |
| 39 | `dYMin` | DualState | 401 | 178 | 118 | 36 | `10A3`/`10A3` | — | — | — | — |
| 16 | `tYUp` | Text | 320 | 152 | 76 | 22 | `10A3` | `9D14` | it16 | centro | `0.00` |
| 18 | `tYDown` | Text | 399 | 152 | 59 | 22 | `10A3` | `9D14` | it16 | centro | `0.00` |
| 15 | `bY` | Button | 283 | 219 | 54 | 50 | `1D09` | `FFFF` | it30 | centro | `Y` |
| 17 | `tY` | Text | 344 | 231 | 182 | 40 | `10A3` | `FFFF` | it30 | sinistra | `0.000` |
| 40 | `dZMax` | DualState | 540 | 178 | 120 | 36 | `10A3`/`10A3` | — | — | — | — |
| 41 | `dZMin` | DualState | 666 | 178 | 118 | 36 | `10A3`/`10A3` | — | — | — | — |
| 20 | `tZLeft` | Text | 584 | 152 | 76 | 22 | `10A3` | `9D14` | it16 | centro | `0.00` |
| 22 | `tZRight` | Text | 663 | 152 | 59 | 22 | `10A3` | `9D14` | it16 | centro | `0.00` |
| 19 | `bZ` | Button | 547 | 219 | 54 | 50 | `1B7A` | `FFFF` | it30 | centro | `Z` |

Note assi:

* Le etichette `▲ MAX` / `▼ MIN` e `POSIZIONE` sono **nello sfondo**.
  I due valori stanno in linea: MAX a destra dell'etichetta, MIN subito a sinistra
  della sua etichetta (`0.00        0.00 ▼ MIN`).
* `dXMax`…`dZMin` (ID 36…41) sono le aree toccabili per impostare i finecorsa:
  **invisibili** (stesso colore della card), messe nella fascia vuota sotto i valori.
  Toccando la fascia sotto il valore MAX/MIN si imposta quel finecorsa.
* `bX`/`bY`/`bZ` coprono il quadrato colorato; il quadrato è dello sfondo,
  il componente ridisegna solo la lettera.

### 2.4 Tastierino e striscia messaggi

| ID | Nome | Tipo | X | Y | W | H | bco | pco | Font | Allin. | Testo |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 2 | `t3` | Text | 14 | 369 | 776 | 29 | `1082` | `A576` | it16 | sinistra | `NanoEls IT 20261028` |
| 26 | `b0` | Button | 616 | 406 | 46 | 72 | `18A3` | `F7BE` | it40 | centro | `0` |
| 27 | `b1` | Button | 117 | 406 | 46 | 72 | `18A3` | `F7BE` | it40 | centro | `1` |
| 28 | `b2` | Button | 172 | 406 | 46 | 72 | `18A3` | `F7BE` | it40 | centro | `2` |
| 29 | `b3` | Button | 228 | 406 | 46 | 72 | `18A3` | `F7BE` | it40 | centro | `3` |
| 30 | `b4` | Button | 283 | 406 | 46 | 72 | `18A3` | `F7BE` | it40 | centro | `4` |
| 31 | `b5` | Button | 339 | 406 | 46 | 72 | `18A3` | `F7BE` | it40 | centro | `5` |
| 32 | `b6` | Button | 394 | 406 | 46 | 72 | `18A3` | `F7BE` | it40 | centro | `6` |
| 33 | `b7` | Button | 449 | 406 | 46 | 72 | `18A3` | `F7BE` | it40 | centro | `7` |
| 34 | `b8` | Button | 505 | 406 | 46 | 72 | `18A3` | `F7BE` | it40 | centro | `8` |
| 35 | `b9` | Button | 560 | 406 | 46 | 72 | `18A3` | `F7BE` | it40 | centro | `9` |
| 1 | `page0` | Page | 0 | 0 | 800 | 480 | `0841` | — | — | — | sta=image, pic=sffondo |

### 2.5 Pagina 0 – componenti da NASCONDERE (visibile = No)

Questi sono i vecchi pulsanti a immagine che non si possono ridisegnare
(un DualState non ha testo, quindi non può mostrare “STOP / CANC / OK / frecce”).
Restano nel progetto, nascosti, così **gli ID non cambiano**:

| ID | Vecchio uso |
|---|---|
| 23 | STOP |
| 24 | backspace |
| 25 | invio |
| 44 | freccia X+ |
| 45 | freccia X− |
| 46 | freccia Y+ |
| 47 | freccia Y− |
| 48 | freccia Z− |
| 49 | freccia Z+ |

### 2.6 Pagina 0 – componenti NUOVI (creare in questo ordine)

L'ordine di creazione determina l'ID (51, 52, …). **Creali nell'ordine indicato.**

| ID | Nome | Tipo | X | Y | W | H | bco | pco | Font | Allin. | Testo |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 51 | `tStarts` | Text | 299 | 30 | 66 | 30 | `18A3` | `EF9D` | it22 | centro | `1` |
| 52 | `bStop` | Button | 8 | 406 | 100 | 72 | `C0E5` | `FFFF` | it30 | centro | `STOP` |
| 53 | `bDel` | Button | 671 | 406 | 56 | 72 | `1B7A` | `FFFF` | it22 | centro | `CANC` |
| 54 | `bEnter` | Button | 736 | 406 | 56 | 72 | `1D09` | `FFFF` | it30 | centro | `OK` |
| 55 | `bXplus` | Button | 10 | 288 | 115 | 68 | `E75D` | `0841` | it22 | centro | `↑ X+` |
| 56 | `bXminus` | Button | 140 | 288 | 114 | 68 | `E75D` | `0841` | it22 | centro | `↓ X−` |
| 57 | `bYplus` | Button | 277 | 288 | 115 | 68 | `E75D` | `0841` | it22 | centro | `↗ Y+` |
| 58 | `bYminus` | Button | 407 | 288 | 115 | 68 | `E75D` | `0841` | it22 | centro | `↘ Y−` |
| 59 | `bZminus` | Button | 545 | 288 | 114 | 68 | `E75D` | `0841` | it22 | centro | `← Z−` |
| 60 | `bZplus` | Button | 674 | 288 | 115 | 68 | `E75D` | `0841` | it22 | centro | `→ Z+` |

Note:

* `tStarts`: `txt_maxl = 8`. Mostra il numero di avvii multipli (lo scrive il firmware).
* `bStop` / `bDel` / `bEnter`: premuto = `A0C4` / `1AD5` / `1427`.
* Frecce: premuto = `CE7A`. Se il font non ha `↗ ↘`, sostituisci con
  `Y+` / `Y−` (oppure `↑ Y+` / `↓ Y−`) senza toccare le coordinate.
* La striscia colorata in fondo alle frecce (rosso/verde/blu) è nello sfondo e resta visibile
  perché il tasto finisce a y = 355.

---

## 3. PAGINA 1 – componenti esistenti

### 3.1 Card (DualState = aree toccabili + riempimento card)

| ID | Nome | Tipo | X | Y | W | H | bco | bco2 | Testo |
|---|---|---|---|---|---|---|---|---|---|
| 12 | `mGear` | DualState | 12 | 88 | 183 | 104 | `18A3` | `18A3` | — |
| 13 | `mTurn` | DualState | 211 | 88 | 183 | 104 | `18A3` | `18A3` | — |
| 14 | `mFace` | DualState | 410 | 88 | 183 | 104 | `18A3` | `18A3` | — |
| 15 | `mCone` | DualState | 609 | 88 | 183 | 104 | `18A3` | `18A3` | — |
| 16 | `mCut` | DualState | 12 | 227 | 183 | 104 | `18A3` | `18A3` | — |
| 17 | `mThread` | DualState | 211 | 227 | 183 | 104 | `18A3` | `18A3` | — |
| 18 | `mEllipse` | DualState | 410 | 227 | 183 | 104 | `18A3` | `18A3` | — |
| 19 | `mGcode` | DualState | 609 | 227 | 183 | 104 | `18A3` | `18A3` | — |
| 20 | `mAsync` | DualState | 12 | 367 | 183 | 104 | `18A3` | `18A3` | — |
| 21 | `mY` | DualState | 211 | 367 | 183 | 104 | `18A3` | `18A3` | — |
| 23 | `mXgear` | DualState | 410 | 367 | 183 | 104 | `18A3` | `18A3` | — |
| 25 | `mJoy` | DualState | 609 | 367 | 183 | 104 | `18A3` | `18A3` | — |
| 27 | `mSlot` | DualState | 303 | 14 | 190 | 30 | `18A3` | `18A3` | — |

I DualState riempiono la card dello stesso colore: restano invisibili e lasciano
vedere il badge `F1…F12` in alto (che è nello sfondo) e il bordo arrotondato.

### 3.2 Vecchie etichette: NASCONDERE (visibile = No)

ID **2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 22, 24, 26** — non si possono riusare perché
stanno *sotto* ai DualState (ID più basso) e verrebbero coperti.

### 3.3 Nuove etichette (creare in questo ordine: ID 28…41)

| ID | Nome | Tipo | X | Y | W | H | bco | pco | Font | Allin. | Testo |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 28 | `lGear` | Text | 21 | 108 | 165 | 34 | `18A3` | `F7BE` | it22 | sinistra | `INGRANAGGI` |
| 29 | `lTurn` | Text | 220 | 108 | 165 | 34 | `18A3` | `F7BE` | it22 | sinistra | `TORNITURA` |
| 30 | `lFace` | Text | 419 | 108 | 165 | 34 | `18A3` | `F7BE` | it22 | sinistra | `SPIANATURA` |
| 31 | `lCone` | Text | 618 | 108 | 165 | 34 | `18A3` | `F7BE` | it22 | sinistra | `CONO` |
| 32 | `lCut` | Text | 21 | 247 | 165 | 34 | `18A3` | `F7BE` | it22 | sinistra | `TRONCATURA` |
| 33 | `lThread` | Text | 220 | 247 | 165 | 34 | `18A3` | `F7BE` | it22 | sinistra | `FILETTATURA` |
| 34 | `lEllipse` | Text | 419 | 247 | 165 | 34 | `18A3` | `F7BE` | it22 | sinistra | `ELLISSE` |
| 35 | `lGcode` | Text | 618 | 247 | 165 | 34 | `18A3` | `F7BE` | it22 | sinistra | `G-CODE` |
| 36 | `lAsync` | Text | 21 | 387 | 165 | 34 | `18A3` | `F7BE` | it22 | sinistra | `ASINCRONO` |
| 37 | `lY` | Text | 220 | 387 | 165 | 34 | `18A3` | `F7BE` | it22 | sinistra | `ASSE Y` |
| 38 | `lXgear` | Text | 419 | 387 | 165 | 34 | `18A3` | `F7BE` | it22 | sinistra | `X-INGRANAGGI` |
| 39 | `lJoy` | Text | 618 | 387 | 165 | 34 | `18A3` | `F7BE` | it22 | sinistra | `JOYSTICK` |
| 40 | `lSlot` | Text | 309 | 17 | 178 | 24 | `18A3` | `F7BE` | it22 | centro | `SCANALATURA` |
| 41 | `bBack` | DualState | 692 | 17 | 98 | 32 | `2966` | `2966` | — | — | — |

Note pagina 1:

* `txt_maxl` di tutte le etichette ≥ 16.
* `bBack` (ID 41) è la pillola INDIETRO: il firmware la usa per tornare a pagina 0.
  La scritta `‹ INDIETRO` è nello sfondo e il componente la lascia scoperta
  (stesso colore della pillola).
* **Ordine modalità**: le card seguono l'ordine ID del firmware:
  12 INGRANAGGI, 13 TORNITURA, 14 SPIANATURA, 15 CONO,
  16 TRONCATURA, 17 FILETTATURA, 18 ELLISSE, 19 G-CODE,
  20 ASINCRONO, 21 ASSE Y, 23 X-INGRANAGGI, 25 JOYSTICK,
  27 SCANALATURA (chip in alto). Con questo ordine **non serve toccare il firmware**.
* Le diciture inglesi (GEARBOX, THREADING, …) restano coperte dai DualState:
  spariscono dalla vista.

---

## 4. Modifiche firmware abbinate

1. **`HEX_TO_KEYCODE`** – nuovi ID (le vecchie voci restano, così il TFT attuale
   continua a funzionare):
   `[52]=B_OFF, [53]=B_BACKSPACE, [54]=B_ON,
    [55]=B_UP, [56]=B_DOWN, [57]=B_FORWARD, [58]=B_BACK, [59]=B_LEFT, [60]=B_RIGHT`
2. **Pagina 1** – `case 41: toScreen("page 0");` (pulsante INDIETRO).
3. **Passo e avvii multipli** – il passo non porta più il suffisso ` x3`:
   `pitchText` senza `" x" + String(starts)` e nuovo `setText("tStarts", String(starts))`.

Nessuna rinomina: `tX`, `tY`, `tZ`, `tXUp`… restano gli stessi nomi di prima.

---

## 5. Controllo rapido dopo la compilazione

1. Pagina 0: `OFF` bianco, `MODALITÀ` blu con `INGR.`, `PRINCIPI` con il numero sotto,
   `PASSO` con il valore, `MISURA` verde, `+` rosso e `−` blu.
2. Assi: sotto `▲ MAX` c'è un valore, a sinistra di `▼ MIN` un altro; la posizione grande
   è bianca.
3. Frecce: 6 tasti chiari con `↑ X+` … `→ Z+`; il filetto colorato resta in basso.
4. Tastierino: STOP rosso, cifre, CANC blu, OK verde.
5. Pagina 1: 12 card con titolo italiano centrato in verticale + chip `SCANALATURA`
   e `‹ INDIETRO` funzionante.

Se un ID dei nuovi componenti non torna (l'Editor li numera in ordine di creazione),
dimmi cosa ha assegnato: correggo la tabella del firmware in un minuto.
