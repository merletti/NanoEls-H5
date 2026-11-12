# Schermate MENU + sottopagine — pagine, picture e hotspot

Data: 2026-10-30 (aggiornato a fine giornata). Progetto: `screen-it/h5_it.HMI`.
Display NX8048P050 800×480. Firmware: `firmware-it/h5.ino`.

**Struttura attuale**: all'accensione si apre il **MENU** (pagina 0); ogni voce del
MENU apre la **propria sottopagina** (13 modalità + COMANDO + GCODE + SETUP + WIFI
+ INFO); da ogni sottopagina il **pill MENU** in alto a destra riporta al MENU.
Le vecchie pagine *CONTROLLO* (page0) e *MODALITÀ* (page1) sono state **eliminate**.

Il MENU è una griglia **5 × 3** di card (F1…F13) più la riga servizi in basso.

Tutto il **disegno statico** (icone, titoli, valori, striscia in basso, pill MENU)
è dentro **l'immagine di sfondo** di ogni pagina: nell'HMI servono solo pagina +
sfondo + hotspot invisibili. I valori mostrati sono segnaposto statici finché non
arriva la fase 2 (componenti testo + mappa firmware).

## 1. Picture

| pic | file | contenuto |
|----|------|-----------|
| 0–4 | di fabbrica | risorse originali |
| 5 | `menu_bg.png` | vecchio MENU (non più usato) |
| 6–17 | vecchi sfondi | **non più usati**: avevano la chip "SCANALATURA" in tutte le pagine |
| 18 | `page0_merlino.png` | vecchia page0 con scritta Merlino (non usata) |
| 19 | `menu_merlino.png` | vecchio MENU 12 card (non più usato) |
| 20 | `mockup-tft/comando.png` | COMANDO |
| 21 | `mockup-tft/impostazioni.png` | SETUP / IMPOSTAZIONI |
| 22 | `mockup-tft/wifi.png` | WIFI |
| 23 | `mockup-tft/info.png` | INFO / STATO |
| 24 | `menu13_merlino.png` | **MENU attuale** (13 card + MERLINO) |
| 25 | `scanalatura_bg.png` | **SCANALATURA** (F13) |
| 26 | `ingranaggi_bg.png` | INGRANAGGI (chip corretta) |
| 27 | `filetto_bg.png` | FILETTATURA (chip piccola) |
| 28 | `tornitura_bg.png` | TORNITURA (chip corretta) |
| 29 | `spianatura_bg.png` | SPIANATURA (chip corretta) |
| 30 | `cono_bg.png` | CONO (chip corretta) |
| 31 | `joystick_bg.png` | JOYSTICK (chip corretta) |
| 32 | `troncatura_bg.png` | TRONCATURA (chip corretta) |
| 33 | `ellisse_bg.png` | ELLISSE (chip corretta) |
| 34 | `asincrono_bg.png` | ASINCRONO (chip corretta) |
| 35 | `assey_bg.png` | ASSE Y (chip corretta) |
| 36 | `xgear_bg.png` | X-INGRANAGGI (chip corretta) |
| 41 | `cono_bg5.png` | CONO a 5 righe (Ø grande, Ø piccolo, corsa Z, lato, fine corsa X) |
| 42 | `calc_labels.png` | striscia etichette 284×468 della riga calcolata: 18 righe da 26 px, una per indice pagina |
| 43 | `sprite_values_card.png` | copia della sprite 38 (800×52) con fondo opaco `#15161A` (card) invece di `#101114` |
| 44 | `card_strip_a.png` | card quotate 1–5 (288×1790): INGRANAGGI, FILETTATURA, TORNITURA, SPIANATURA, TRONCATURA |
| 45 | `card_strip_b.png` | card quotate 6–10 (288×1790): ELLISSE, ASINCRONO, ASSE Y, JOYSTICK, X-INGRANAGGI |
| 46 | `card_strip_c.png` | card quotata 11 (288×358): SCANALATURA |
| 47 | `lavorazione_tft_bg.png` (rev. 1) | LAVORAZIONE: sfondo **non più usato**, ancora presente con i vecchi tasti `MAX QUI`/`MIN QUI` |
| 48 | `import_card49/01_ingranaggi_bg.png` | INGRANAGGI con **card quotata v49 già dentro lo sfondo** |
| 49 | `import_card49/02_filetto_bg.png` | FILETTATURA con card v49 |
| 50 | `import_card49/03_tornitura_bg.png` | TORNITURA con card v49 |
| 51 | `import_card49/04_spianatura_bg.png` | SPIANATURA con card v49 |
| 52 | `import_card49/05_troncatura_bg.png` | TRONCATURA con card v49 |
| 53 | `import_card49/06_ellisse_bg.png` | ELLISSE con card v49 |
| 54 | `import_card49/07_asincrono_bg.png` | ASINCRONO con card v49 |
| 55 | `import_card49/08_assey_bg.png` | ASSE Y con card v49 |
| 56 | `import_card49/09_joystick_bg.png` | JOYSTICK con card v49 |
| 57 | `import_card49/10_xgear_bg.png` | X-INGRANAGGI con card v49 |
| 58 | `import_card49/11_scanalatura_bg.png` | SCANALATURA con card v49 |
| 59 | `lavorazione_tft_bg.png` (rev. 2) | **LAVORAZIONE** (pagina 21): tasti `MAX`/`MIN`, solo disegno statico, valori e tasti li scrive il firmware |
| 60 | `import_card49/01_ingranaggi_bg.png` | INGRANAGGI, sfondo v50 (etichette con spazio) |
| 61 | `import_card49/02_filetto_bg.png` | FILETTATURA, sfondo v50 |
| 62 | `import_card49/03_tornitura_bg.png` | TORNITURA, sfondo v50 |
| 63 | `import_card49/04_spianatura_bg.png` | SPIANATURA, sfondo v50 |
| 64 | `import_card49/05_troncatura_bg.png` | TRONCATURA, sfondo v50 |
| 65 | `import_card49/06_ellisse_bg.png` | ELLISSE, sfondo v50 |
| 66 | `import_card49/07_asincrono_bg.png` | ASINCRONO, sfondo v50 |
| 67 | `import_card49/08_assey_bg.png` | ASSE Y, sfondo v50 |
| 68 | `import_card49/09_joystick_bg.png` | JOYSTICK, sfondo v50 |
| 69 | `import_card49/10_xgear_bg.png` | X-INGRANAGGI, sfondo v50 |
| 70 | `import_card49/11_scanalatura_bg.png` | SCANALATURA, sfondo v50 |
| 71 | `cono_bg5.png` | CONO a 5 righe, sfondo v50 (data `IT 20261030`) |

> **Non rimuovere picture**: gli indici successivi scalano.
> Gli sfondi 26–36 sono stati importati in coda (l'editor non ha "Replace");
> l'ordine reale è stato verificato confrontando i byte `.is` con i PNG.
> Attenzione: 31 = JOYSTICK è stato importato prima di 32–36.

## 1b. Riga valore calcolato (tutte le modalità)

Come per il CONO (dove il RAPPORTO si ricava dalle due quote), ogni pagina di
lavoro mostra in fondo alla card un **valore derivato dalle misure**, in sola
lettura (non ha hotspot e non si tocca):

- **etichetta**: picture 42, riga `indice_pagina` (26 px), disegnata dal firmware
  con `xpic 502,393,284,26,0,<pagina*26>,42`;
- **valore**: allineato a destra a x=768, area da 610, sprite **43** (fondo card).

La riga cade sulla **riga di suggerimento** in fondo alla card quotata
(`Tocca un valore per digitarlo…`, y 400..412 a schermo): viene coperta.
Sul CONO, che non ha la card quotata, l'etichetta resta a y=345.

| pagina | etichetta | valore |
|--------|-----------|--------|
| 1,2,3,4,6,7,10,12 | AVANZ. mm/giro | passo × principi (mm per giro mandrino) |
| 8 ASINCRONO | VELOC. mm/min | passo × 60 (avanzamento a 1 giro/s) |
| 11 JOYSTICK | VEL. MAX mm/min | giri/s rapidi × passo vite Z × 60 |
| 17 SCANALATURA | RIDUZ. TOTALE mm | riduzione sinistra × (passate − 1) |
| 5 CONO | (già RAPPORTO a y=345) | rapporto calcolato dalle misure |

Le pagine 0, 9 e 13…16 non hanno la riga. La sprite 43 è usata anche per STATO
e per il RAPPORTO del CONO, così il numero non ha più il rettangolo scuro
`#101114` sopra la card.

## 1c. Card quotata (11 pagine di lavoro)

Le 11 pagine di lavoro (1,2,3,4,6,7,8,10,11,12,17) mostrano a destra un
**disegno quotato**: chip con il PASSO, quota con il finecorsa, riga STATO /
MODALITÀ e riga di suggerimento.

Dal 2026-11-02 il disegno è **dentro lo sfondo** di ogni pagina (picture 48–58,
una per pagina): il simulatore e il display la mostrano senza intervento del
firmware. Le vecchie strisce 44/45/46 e il relativo `xpic` di pagina
(`tftDrawCardBackdrop`) restano nel progetto e nel firmware ma sono
**pixel-identiche** alla card nuova: ridisegnano lo stesso disegno a
`xpic 500,74,288,358` e non cambiano nulla. La tabella qui sotto resta valida
per i valori vivi, scritti sopra la card.

| pagina | card | picture sfondo |
|--------|------|----------------|
| 1 | INGRANAGGI | 48 |
| 2 | FILETTATURA | 49 |
| 3 | TORNITURA | 50 |
| 4 | SPIANATURA | 51 |
| 6 | TRONCATURA | 52 |
| 7 | ELLISSE | 53 |
| 8 | ASINCRONO | 54 |
| 10 | ASSE Y | 55 |
| 11 | JOYSTICK | 56 |
| 12 | X-INGRANAGGI | 57 |
| 17 | SCANALATURA | 58 |

I valori vivi si scrivono dentro i rettangoli vuoti con la sprite 38 (fondo
`#101114`, uguale all'interno delle caselle), centrati nell'area:

| pagina | campo | destra | y | sinistra | casella (card locale) |
|--------|-------|--------|---|----------|------------------------|
| 1,2 | P | 714 | 155 | 569 | x69..214 y81 |
| 1,2 | Z MAX | 691 | 274 | 596 | x96..191 y200 |
| 3 | P | 712 | 155 | 567 | x67..212 y81 |
| 3 | Z MAX | 685 | 274 | 591 | x91..185 y200 |
| 4 | P | 683 | 276 | 538 | x38..183 y202 |
| 4 | X MAX | 745 | 186 | 651 | x151..245 y112 |
| 6 | P | 687 | 153 | 542 | x42..187 y79 |
| 6 | X MAX | 759 | 237 | 665 | x165..259 y163 |
| 7 | P | 714 | 155 | 569 | x69..214 y81 |
| 7 | Z MAX | 691 | 260 | 596 | x96..191 y186 |
| 8 | P | 714 | 155 | 569 | x69..214 y81 |
| 8 | Z MAX | 689 | 274 | 594 | x94..189 y200 |
| 10 | P Y | 765 | 149 | 620 | x120..265 y75 |
| 10 | Y MAX | 763 | 206 | 668 | x168..263 y132 |
| 12 | P X | 691 | 155 | 546 | x46..191 y81 |
| 12 | X MAX | 753 | 278 | 659 | x159..253 y204 |
| 17 | AV. | 714 | 155 | 569 | x69..214 y81 |
| 17 | Z MAX | 687 | 274 | 592 | x92..187 y200 |

La card locale si converte in schermo sommando (500, 74). Sulla SPIANATURA e
sulla X-INGRANAGGI la casella larga sta in basso e la chip stretta in alto,
quindi i due campi sono scambiati rispetto alle altre pagine.

STATO: label e valore di esempio sono nell'immagine; il firmware ridisegna il
valore (`OFF`/`ON`/`SIN`) a destra a x=768 con la sprite 43, y=341.
MODALITÀ (F1…F13) è **fissa nell'immagine** di ogni card e non viene ridisegnata.
JOYSTICK non ha valori vivi sul disegno: le velocità restano nella colonna
sinistra.

## 2. Pagine (ordine del pannello Page = indice usato negli eventi)

Il nome interno della pagina è quello storico (`page2`…`page18`) e **non** coincide
con l'indice: negli eventi si usa l'indice.

| indice | nome interno | pic | schermata |
|-------|------|-----|-----------|
| 0 | page2 | 24 | **MENU** (prima pagina all'accensione) |
| 1 | page3 | 60 | INGRANAGGI (F1) |
| 2 | page4 | 61 | FILETTATURA (F2) |
| 3 | page5 | 62 | TORNITURA (F3) |
| 4 | page6 | 63 | SPIANATURA (F4) |
| 5 | page7 | 71 | CONO (F5) — sfondo a 5 righe |
| 6 | page8 | 64 | TRONCATURA (F6) |
| 7 | page9 | 65 | ELLISSE (F7) |
| 8 | page10 | 66 | ASINCRONO (F8) |
| 9 | page11 | 13 | G-CODE (F9) |
| 10 | page12 | 67 | ASSE Y (F10) |
| 11 | page13 | 68 | JOYSTICK (F11) |
| 12 | page14 | 69 | X-INGRANAGGI (F12) |
| 13 | page15 | 20 | COMANDO |
| 14 | page16 | 21 | SETUP (IMPOSTAZIONI) |
| 15 | page17 | 22 | WIFI |
| 16 | page18 | 23 | INFO / STATO |
| 17 | page19 | 70 | **SCANALATURA (F13)** |
| 21 | page21 | 59 | **LAVORAZIONE** — pagina live aperta dal firmware all'avvio di una modalità |

Attributi pagina: `sta` = image, `pic` = numero della tabella, `bco` = `0841`.
In `Program.s` l'avvio è `page 0`.

## 3. Hotspot di navigazione (Hotspot invisibili, solo Touch Press Event)

### Pagina 0 — MENU (nome `page2`)

| id | zona | x | y | w | h | evento |
|----|------|---|---|---|---|--------|
| m0 | F1 INGRANAGGI | 12 | 64 | 148 | 100 | `page 1` |
| m1 | F2 FILETTATURA | 168 | 64 | 148 | 100 | `page 2` |
| m2 | F3 TORNITURA | 324 | 64 | 148 | 100 | `page 3` |
| m3 | F4 SPIANATURA | 480 | 64 | 148 | 100 | `page 4` |
| m4 | F5 CONO | 636 | 64 | 148 | 100 | `page 5` |
| m5 | F6 TRONCATURA | 12 | 172 | 148 | 100 | `page 6` |
| m6 | F7 ELLISSE | 168 | 172 | 148 | 100 | `page 7` |
| m7 | F8 ASINCRONO | 324 | 172 | 148 | 100 | `page 8` |
| m8 | F9 G-CODE | 480 | 172 | 148 | 100 | `page 9` |
| m9 | F10 ASSE Y | 636 | 172 | 148 | 100 | `page 10` |
| m10 | F11 JOYSTICK | 12 | 280 | 148 | 100 | `page 11` |
| m11 | F12 X-INGRANAGGI | 168 | 280 | 148 | 100 | `page 12` |
| m17 | F13 SCANALATURA | 324 | 280 | 148 | 100 | `page 17` |
| m12 | COMANDO | 12 | 388 | 149 | 54 | `page 13` |
| m13 | GCODE | 168 | 388 | 149 | 54 | `page 9` |
| m14 | SETUP | 325 | 388 | 148 | 54 | `page 14` |
| m15 | WIFI | 482 | 388 | 148 | 54 | `page 15` |
| m16 | INFO | 639 | 388 | 149 | 54 | `page 16` |

> GCODE e G-CODE portano alla **stessa** pagina (indice 9).
> L'hotspot della card F13 è stato creato per ultimo, quindi ha nome `m17`
> (id 18): non rinominarlo senza aggiornare questa tabella.

### Pagine 1…17 — pill MENU

Su **ogni** sottopagina c'è un hotspot `m0` identico:

| id | zona | x | y | w | h | evento |
|----|------|---|---|---|---|--------|
| m0 | pill `< MENU` | 684 | 6 | 104 | 58 | `page 0` |

> Verificato su **tutte** le 17 sottopagine (non solo su quelle testate prima).

## 4. Verifica fatta (simulatore, build 15:56)

- Avvio su MENU con MERLINO e 13 card (griglia 5 × 3).
- **Test automatico `gui/simtest.ps1`** con coordinate corrette
  (colonna destra a x≈955, non 875): per ognuna delle 18 voci del MENU
  (F1…F13 + COMANDO/GCODE/SETUP/WIFI/INFO) clic sulla voce, cattura della
  schermata, clic sul pill `< MENU`, cattura: tutte **18/18 PASS**
  (pagina aperta diversa dal MENU, ritorno identico pixel-per-pixel al MENU).
- **Chip di intestazione**: le 13 sottopagine hanno ora ciascuna la propria
  chip in alto a destra (prima erano tutte "SCANALATURA"). Verificato
  confrontando l'area della chip nei 13 screenshot: 13 impronte diverse.
- Compile: 0 errori / 0 warning, TFT **3.457.176** byte (`h5_it.tft`, 15:56).

### Card v49 nello sfondo (2026-11-02)

- Importate le picture **48–58** (sfondo completo 800×480 con la card quotata
  già composta) e ripuntato `pic` delle 11 pagine di lavoro (indici
  1,2,3,4,6,7,8,10,11,12,17).
- Simulatore: `page <id>` per le 13 pagine (11 di lavoro + CONO 5 + GCODE 9).
  Le 11 pagine mostrano la card v49 **senza** comandi `xpic` dal firmware;
  CONO (pic 41) e GCODE (pic 13) restano invariate.
- `h5_it.HMI` salvato (12.655.351 byte, 11:44); `h5_it.tft` ricompilato
  (**4.797.668** byte, 11:46, md5 `185e1d53279db272f1c499509ab301be`).
- Verifica pixel: la card v49 composta negli sfondi è **identica** allo slot
  0 della striscia 44 (`diff = 0`), quindi l'overlay `tftDrawCardBackdrop`
  del firmware resta innocuo.

> Nota: fino a questa build la pagina **X-INGRANAGGI (indice 12)** era l'unica
> sottopagina **senza** hotspot `m0` → da lì non si tornava al MENU. Aggiunto
> (684, 6, 104, 58) con Touch Press `page 0`.

### Sfondi v50 — etichette con spaziatura (2026-11-12)

- Corrette le etichette dei PNG di sfondo che perdevano lo spazio dopo
  `CORSA`/`VELOCITÀ` (es. `CORSAZ` → `CORSA Z`): ingranaggi, filetto, tornitura,
  spianatura, troncatura, ellisse, asincrono, asse Y, joystick, x-ingranaggi,
  scanalatura e cono. Bandiere di testo ricopiate dai render `mockup-tft/clean`.
- Corretta anche la data nel piè di pagina della pagina **CONO** (IT 20261030).
- Importate le picture **60–71** (sfondo 800×480 con la card quotata) e
  ripuntato `pic` delle 12 pagine: 1→60, 2→61, 3→62, 4→63, 5→71, 6→64, 7→65,
  8→66, 10→67, 11→68, 12→69, 17→70.
- `h5_it.HMI` salvato (14.201.774 byte, 10:43); `h5_it.tft` ricompilato con
  **0 errori** (**5.977.316** byte, 10:46, md5 `6cc5a211cad19ca406d63fa93416e48c`).
- Simulatore: verificate le 12 pagine con `page <id>`; tutte le etichette
  mostrano lo spazio corretto e il piè di pagina CONO riporta `IT 20261030`.

## 5. Fase 2 (mappa firmware)

Il firmware `firmware-it/h5.ino` va rimappato: usa ancora `page 0` come pagina di
controllo e `setText("t3", …)` sulla vecchia page0 (che non esiste più).

- Eventi delle card `0x65 <pagina> <id>` → `B_MODE_*` per gli id m0…m11 e m17.
- Pill MENU → `toScreen("page 2")` (nome interno della pagina 0).
- COMANDO → indice 13; GCODE → 9; SETUP → 14; WIFI → 15; INFO → 16;
  SCANALATURA → 17 (nuova, da agganciare a `B_MODE_SLOT`).
- Sostituire i valori statici delle sottopagine con `txt`/`xfloat` aggiornati
  dal firmware (PASSO, PRINCIPI, FINECORSA…).

## 6. Pagina 21 — LAVORAZIONE

Pagina live della lavorazione in corso (indice **21**, nome interno `page21`,
`sta` = image, `pic` = **59**). Non ha componenti: tutto il dinamico lo scrive il
firmware con la sprite 38 (fondo `#101114`) e la sprite 43 (fondo card
`#15161A`) dentro i rettangoli già presenti nello sfondo.

Apertura: il firmware la apre **subito dopo ATTIVA MODALITÀ** su una pagina di
lavoro (dal firmware v47) e, come prima, all'avvio della modalità con il tasto
ON (`tftAutoOpenWorkPage`) quando si parte dal MENU, da una pagina modalità o
dalla SCANALATURA. Il pill `‹ MENU` riporta al MENU (pagina 0).

Avvio (dal firmware v48): sulla pagina LAVORAZIONE `STATO/AVVIA` conferma in un
solo tocco i passi di setup usando i dati già impostati nella pagina modalità e
avvia; i finecorsa obbligatori restano controllati (in mancanza, solo beep e
messaggio `Imposta finecorsa` nella riga in basso). In G-CODE resta la conferma
passo-passo, perché il programma e il mandrino hanno controlli propri. Il
rapporto cono della FILETTATURA è un campo della pagina e non viene più azzerato
al passo di conferma.

Dal firmware v49: la riga in basso dipinta dal firmware usa lo sfondo `#101010`
su tutte le pagine tranne 19, 20 e 21 (che restano `#080808`); l'intestazione
`FILE SALVATI` della pagina 9 è dipinta sul colore card e il conteggio è
separato dall'etichetta. Il reset generale riporta il rapporto cono a 0
(cilindrico).

Dal firmware v50: la card CONO mostra la conicità da catalogo,
`1 : corsa Z / (Ø grande − Ø piccolo)` (per un Morse 5, `1 : 19`), non più il
doppio "per lato" (era `1 : 38`). Il movimento X/Z non cambia: la X si sposta
ancora di `coneRatio / 2` per unità di Z.

Dal firmware v51 (correzioni dal collaudo nel simulatore):

- **SPIANATURA**: la riga DIREZIONE mostra `DX>SX` / `SX>DX` (prima `EST`/`INT`,
  testo valido solo per le altre modalità).
- **TRONCATURA**: il lato segue il segno del passo (`EST` con passo > 0,
  `INT` con passo < 0); toccare LATO o `‹ ›` inverte il segno del PASSO e
  riallinea il campo. Con ELS acceso il tocco è rifiutato (`SPEGNI PRIMA`).
- **JOYSTICK**: `INGRESSI ATTIVI` non è più un testo fisso dello sfondo: il
  firmware scrive `Z X Y` (o il sottoinsieme) secondo `joystickZEnabled`,
  `joystickXEnabled`, `joystickYEnabled`. La riga non ha zona touch.
- **SCANALATURA**: `−/+` sul finecorsa Z agisce sulla metà toccata per ultima,
  MAX (sinistra) o MIN (destra), non più sempre su MAX. Il tastierino resta
  separato sulle due metà.

Dal firmware v52: il messaggio di emergenza non usa più i componenti della
vecchia HMI (`bMode`, `t3`, assenti nella HMI attuale). All'arresto di
emergenza il display dipinge `ESTOP` nella card STATO (pagina 21 e pagine
modalità) e `ESTOP - <causa>` nella riga in basso con la sprite; la UI web
riceve `UI.status=ESTOP` e `UI.message=<causa>`. Vale per `Spento in manuale`,
`Posizione fuori macchina`, `Impossibile segnare origine`, `Impossibile ON/OFF`.

Script a livello pagina (non ci sono Hotspot):

| evento | contenuto |
|--------|-----------|
| Preinitialize | vuoto |
| Postinitialize | `printh 68 15 10 5A FF FF FF` (pagina caricata) |
| Touch Press | zona `tch0`/`tch1` → `printh 68 15 <codice> 5A FF FF FF` |
| Touch Release | `printh 68 15 6F 5A FF FF FF` (rilascio jog) |

Codici (dispatch in `tftWorkEvent`, `firmware-it/h5/h5.ino`):

| codice | zona | x | y | w | h | azione |
|--------|------|---|---|---|---|--------|
| 0x31 | `‹ MENU` | 684 | 10 | 104 | 44 | torna al MENU |
| 0x8B | chip PASSO | 12 | 74 | 148 | 52 | tastierino passo |
| 0x8C | chip PRINCIPI | 168 | 74 | 148 | 52 | tastierino principi |
| 0x8D | chip PASSATE | 324 | 74 | 148 | 52 | tastierino passate |
| 0x70 | STATO / AVVIA-STOP | 552 | 356 | 224 | 34 | avvia (conferma i passi) / ferma |
| 0x75 | X ZERO | 24 | 268 | 58 | 28 | zero asse X |
| 0x85 | X MAX | 87 | 268 | 82 | 28 | finecorsa MAX X alla posizione |
| 0x86 | X MIN | 174 | 268 | 82 | 28 | finecorsa MIN X alla posizione |
| 0x76 | Y ZERO | 284 | 268 | 58 | 28 | zero asse Y |
| 0x87 | Y MAX | 347 | 268 | 82 | 28 | finecorsa MAX Y |
| 0x88 | Y MIN | 434 | 268 | 82 | 28 | finecorsa MIN Y |
| 0x77 | Z ZERO | 544 | 268 | 58 | 28 | zero asse Z |
| 0x89 | Z MAX | 607 | 268 | 82 | 28 | finecorsa MAX Z |
| 0x8A | Z MIN | 694 | 268 | 82 | 28 | finecorsa MIN Z |
| 0x65 | `← Z−` | 12 | 404 | 188 | 40 | jog Z negativo |
| 0x64 | `Z+ →` | 208 | 404 | 188 | 40 | jog Z positivo |
| 0x60 | `↑ X+` | 404 | 404 | 188 | 40 | jog X positivo |
| 0x61 | `↓ X−` | 600 | 404 | 188 | 40 | jog X negativo |
| 0x62/0x63 | (riservati Y±) | — | — | — | — | jog Y, solo con asse Y attivo |
| 0x6F | rilascio ovunque | — | — | — | — | ferma i jog tenuti premuti |

Nota: MAX / MIN memorizzano la posizione **attuale** come finecorsa, quindi
richiedono il controller **spento**; il firmware lo verifica e risponde con il
messaggio `SPEGNI PRIMA`.
