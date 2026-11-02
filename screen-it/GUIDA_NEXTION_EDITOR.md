# Guida clic-per-clic – ricostruzione TFT in Nextion Editor

Da usare insieme a [TABELLA_COMPONENTI.md](TABELLA_COMPONENTI.md): la tabella ha i
valori, questa guida dice **dove cliccare**. I nomi delle voci di menu possono
cambiare leggermente con la versione dell'Editor: se una voce non la trovi,
cercala tra le proprietà a destra (sono gli stessi attributi usati dal firmware).

---

## 0. Prima di toccare qualsiasi cosa

1. Copia `C:\Users\Admin\Desktop\h5\screen\h5.HMI` e il `h5.tft` di fabbrica in una
   cartella di backup (`backup-tft\`). Servono per tornare indietro.
2. Apri Nextion Editor → **File → Open** → `h5.HMI`.
3. **File → Save As** → `h5_it.HMI` nella cartella `screen-it`.
   Da qui in poi lavori solo sul file nuovo.

### Le tre regole che non si possono violare

1. **Non cancellare nessun componente.** Il firmware indirizza i tasti con un numero
   (l'ID) che dipende dall'ordine di creazione: cancellando, tutti gli ID successivi
   scalano di uno e i tasti rispondono sbagliato. Per "togliere" un componente si
   usa **visibile = No** (punto 4).
2. **I nuovi componenti si creano solo nell'ordine della tabella** (prima 51, poi 52,
   … 60; poi 28 … 41). L'ordine di creazione è l'ID.
3. **Non rinominare i componenti esistenti** (`tX`, `bMode`, `tPitch`, …): sono i nomi
   con cui il firmware scrive i valori.

---

## 1. I quattro font

Pannello in basso a sinistra → scheda **Font** → pulsante **Add** … quattro volte:

| Font | Famiglia | Stile | Dimensione | Encoding |
|---|---|---|---|---|
| `it16` | DejaVu Sans (o Arial) | Regular | 16 | iso-8859-1 |
| `it22` | DejaVu Sans | Regular | 22 | iso-8859-1 |
| `it30` | DejaVu Sans | Regular | 30 | iso-8859-1 |
| `it40` | DejaVu Sans | Regular | 40 | iso-8859-1 |

Nel dialogo del font seleziona **tutti i caratteri** (o almeno: cifre `0-9`,
lettere maiuscole/minuscole, `. , : - + / %`, spazio) e in più aggiungi a mano:

* `°` (serve: il firmware manda il byte `0xDF`, che nel font Nextion è il grado);
* per `it22` e `it16` anche `↑ ↓ ↗ ↘ ← → ‹` (frecce e INDIETRO);
* la `X` maiuscola è già compresa, ma verifica che ci sia.

Annota quale font l'Editor ha numerato come `font0`…`font3`: quando assegni il
font a un componente scegli quello giusto dall'elenco.

> Se le frecce appaiono come quadratini `□` nella simulazione, la famiglia scelta
> non le ha: usa le etichette ASCII `X+ X- Y+ Y- Z- Z+` come indicato nella tabella,
> senza cambiare posizioni.

---

## 2. Le due immagini di sfondo

Pannello in basso a sinistra → scheda **Picture** → **Add**:

1. `screen-it\page0_bg.png` → annota il numero che le viene assegnato: **P0**.
2. `screen-it\page1_bg.png` → annota il numero: **P1**.

Regole:

* Non aggiungere la stessa immagine due volte (spreca spazio e sposta gli ID).
* Se devi rimuoverne una, tutti i `pic` successivi scalano: ricontrolla i due `pic`
  delle pagine.
* Le immagini non hanno trasparenza: è normale, gli sfondi sono già piatti.

---

## 3. Pagina 0 – sfondo

1. Scheda **Page** (in basso a sinistra, accanto a Picture/Font) → clic su `page0`.
2. Pannello **Attribute** a destra:
   * `sta` → **Image**
   * `pic` → **P0**
   * `bco` → `0841`
   * `vscope` → Global

Da questo momento lo sfondo è il mockup e i vecchi tasti a immagine stonano: si
nascondono subito (punto 4).

---

## 4. Pagina 0 – nascondere i vecchi tasti a immagine

Componenti: **23, 24, 25, 44, 45, 46, 47, 48, 49** (STOP, CANC, invio, sei frecce).

Per ognuno:

1. Cliccalo sulla tela (sono ancora al loro posto, sopra lo sfondo nuovo).
2. Nel pannello Attribute cerca la voce **`vis`** (visibile):
   * se c'è → mettila a **0**;
   * se non c'è → seleziona la **pagina** `page0`, scheda **Event**,
     evento **Preinitialize**, e aggiungi una riga per ciascuno:
     ```
     t23.vis=0
     t24.vis=0
     t25.vis=0
     t44.vis=0
     ...
     t49.vis=0
     ```
     (usa il nome reale che vedi in `objname`, non l'ID).

Le scritte a immagine spariscono; gli ID restano e il firmware attuale continua a
funzionare.

---

## 5. Pagina 0 – componenti riusati

Per **ogni riga** delle sezioni 2.1, 2.2, 2.3 e 2.4 della tabella fai così:

1. Clic sul componente sulla tela.
2. Nel pannello Attribute digita i valori della riga, nell'ordine:
   **`x`, `y`, `w`, `h`** → poi **`bco`**, **`pco`**, **`font`**, **`txt`**,
   **`txt_maxl`**, **`isbr` = 0**, **`spax`** (allineamento orizzontale:
   0 = sinistra, 1 = centro, 2 = destra).
3. Se nella riga non c'è un valore, **non toccare** quell'attributo.

Attenzioni specifiche:

* **`sta` = Solid color** e **`pic` = 0**, **`picc` = 0**, **`picc2` = 0** su ogni
  componente riusato: altrimenti riappare l'arte di fabbrica sopra lo sfondo.
* **DualState 36, 37, 38, 39, 40, 41** (`dXMax` … `dZMin`): non hanno testo né font.
  Imposta solo `x, y, w, h`, `bco` = `10A3`, `bco2` = `10A3`, `val` = 0.
* **DualState 42, 43, 50** (`bPlus`, `bMinus`, `bStarts`): `bco` e `bco2` devono
  essere **esattamente** il colore del tasto disegnato sotto (`C0E5`, `1B7A`, `18A3`),
  altrimenti coprono il `+`, il `−` e la scritta `PRINCIPI`.
* **Tastierino 26…35** (`b0`…`b9`): `b0` è l'ID 26, `b9` è l'ID 35 — vanno spostati
  tutti alla stessa `y` (406) con passo 55-56 px, come da tabella.
* **`tPitch`, `tAngleVal`**: se dopo il caricamento il grado esce come `ß`,
  rimetti su quel componente il **font originale di fabbrica** (mostra il grado
  correttamente) e cambia solo posizione e colori.
* **`t3`** (striscia messaggi): `bco` = `1082`, `pco` = `A576`, `txt_maxl` ≥ 48.

---

## 6. Pagina 0 – nuovi componenti (ordine obbligatorio)

Toolbox a sinistra → per ogni riga della sezione 2.6:

1. Clic sulla categoria giusta: **Button** (per `bStop`, `bDel`, …) oppure
   **Text** (per `tStarts`).
2. Clic sulla tela dove va il componente: nasce con un nome tipo `bt0`/`t0`.
3. Subito, nell'Attribute:
   * `objname` → il nome esatto della tabella (`tStarts`, `bStop`, `bDel`, `bEnter`,
     `bXplus` … `bZplus`)
   * `x`, `y`, `w`, `h`
   * `sta` = Solid color, `pic`/`picc` = 0, `isbr` = 0
   * `bco`, `bco2` (premuto), `pco`, `font`, `txt`, `txt_maxl`, `spax`
4. Passa al successivo **solo dopo** aver finito questo.

L'ordine esatto è: **51** `tStarts`, **52** `bStop`, **53** `bDel`, **54** `bEnter`,
**55** `bXplus`, **56** `bXminus`, **57** `bYplus`, **58** `bYminus`,
**59** `bZminus`, **60** `bZplus`.

Controlli su questa fascia:

* i sei tasti freccia finiscono a `y+h = 356`, così il filetto colorato dello
  sfondo resta visibile sotto;
* `tStarts` sta **sopra** `bStarts` (creato dopo → ID più alto → disegnato sopra);
* `bDel` con `CANC` a 22 px deve stare in 56 px: se viene tagliato, usa `it16`.

---

## 7. Pagina 1 – sfondo e struttura

1. Scheda **Page** → `page1`.
2. Attribute: `sta` = **Image**, `pic` = **P1**, `bco` = `0841`.

### 7.1 DualState esistenti (12…25 e 27)

Solo geometria e colori (nessun testo): `x, y, w, h`, `bco` = `18A3`,
`bco2` = `18A3` (**obbligatorio uguale a `bco`**, altrimenti la card resta
"accesa" dopo il tocco), `val` = 0, `isbr` = 0.

Sono loro che coprono le diciture inglesi di fabbrica: se restano al loro posto e
dello stesso colore della card, il testo vecchio sparisce da solo.

### 7.2 Vecchie etichette da nascondere

ID **2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 22, 24, 26**: stesso metodo del punto 4
(`vis` = 0, oppure `Preinitialize` della pagina con `nome.vis=0`).
Vanno nascoste **dopo** aver sistemato i DualState, altrimenti rischi di cliccare
l'etichetta sbagliata.

### 7.3 Nuove etichette e ritorno (28…41)

Stessa ricetta del punto 6 (Text per 28…40, **Dual-state button** per 41),
nell'ordine: **28** `lGear` … **40** `lSlot`, **41** `bBack`.

* Testi: `bco` = `18A3`, `pco` = `F7BE`, font `it22`, `spax` come da tabella.
* `lSlot` è il chip `SCANALATURA`: `bco` = `18A3`, che è esattamente il `15161A`
  con cui è riempito il chip nello sfondo.
* `bBack`: `bco` = `bco2` = `2966`, nessun testo — la scritta `‹ INDIETRO` è nello
  sfondo.

---

## 8. Compilare

1. **File → TFT file output**.
2. Nel dialogo «TFT file output»:
   * nome file: `h5_it.tft`
   * cartella: `...\nanoels-h5\screen-it`
   * pulsante **Output**
3. Attendi qualche secondo: si apre Esplora file sulla cartella e `h5_it.tft`
   risulta appena scritto (dimensione ~3,8 MB).
4. Facoltativo ma consigliato: pulsante **Debug** (simulatore) → sfoglia le
   pagine, verifica che non ci siano rettangoli di colore diverso, testi tagliati
   o componenti sovrapposti.

> L'icona **Compile** nella toolbar, in questa build dell'Editor (v1.68.1
> portable), non produce nulla: non usarla. Il percorso valido è quello sopra
> (il pulsante **Upload** rilegge il file già su disco, non ricompila).

> Nel simulatore i valori dei numeri restano quelli scritti a mano: la verifica
> dei valori veri si fa sull'hardware.

---

## 9. Ordine di caricamento (importante)

**Prima il firmware, poi il TFT.**

1. **Firmware**: Web UI del controller (`http://<ip-del-controller>`) →
   *Aggiorna firmware ESP32* → `firmware-it\h5-IT-20261028c.bin`.
   Questo firmware funziona anche con il TFT vecchio (gli ID vecchi sono ancora
   mappati), quindi è sicuro caricarlo per primo.
2. **TFT** (due strade):
   * **Consigliata, dalla Web UI**: sezione *Aggiorna display Nextion* →
     `h5_it.tft`. Serve il controller **spento** (ELS OFF) e il display
     alimentato dalla porta **POWER**, non da USB. Durata ~6 minuti a 115200.
   * **Con la SD**: copia `h5_it.tft` su una SD **FAT32**, nella **radice**, e
     rinominalo `h5.tft`. Display spento → inserisci la SD → accendi. Parte da
     solo con `Update…`, poi `Update success`. Spegni, togli la SD, riaccendi.

Se preferisci la seriale: convertitore USB-TTL su `P0/P1` del display, pulsante
**Upload** dell'Editor, COM del convertitore, **115200** baud (un display ancora
di fabbrica vuole 9600 la prima volta).

---

## 10. Prova sull'hardware

1. Pagina 0: `OFF` bianco, `MODALITÀ` blu con `INGR.`, `PRINCIPI` con il numero,
   `PASSO` con il valore, `MISURA` verde, `+` rosso e `−` blu.
2. Assi: un valore sotto `▲ MAX`, uno a sinistra di `▼ MIN`, posizione grande bianca.
   Tocca la fascia sotto MAX/MIN: deve aprire il tastierino del finecorsa.
3. Frecce: `↑ X+` … `→ Z+` fanno muovere gli assi; il tasto si scurisce alla
   pressione e torna chiaro al rilascio.
4. Tastierino: `STOP` rosso ferma, le cifre compongono il numero, `CANC`
   cancella, `OK` conferma.
5. `MODALITÀ` → pagina 1: dodici card con titolo italiano, chip `SCANALATURA`,
   `‹ INDIETRO` torna a pagina 0. Scegliendo una card si torna comunque a pagina 0.
6. Grado: su `ANGOLO` deve leggere `0.00°` e non `0.00ß`.

---

## 11. Se qualcosa non torna

| Sintomo | Causa | Rimedio |
|---|---|---|
| Testo tagliato o con `…` | `txt_maxl` troppo piccolo o font grande | alza `txt_maxl`, riduci `w` del font |
| Rettangolo di colore diverso | `bco` ≠ colore sottostante | correggi `bco` |
| Tasto resta "acceso" | `bco2` ≠ `bco` su un DualState | eguaglia `bco2` a `bco` |
| Frecce/INDIETRO come `□` | font senza i glifi | usa etichette ASCII o altra famiglia |
| `ß` invece di `°` | font nuovo senza il grado Nextion (`0xDF`) | rimetti il font originale su `tAngleVal` |
| Tocco sbagliato / tasto morto | un ID è scalato (cancellazione o creazione fuori ordine) | non toccare altro: mandami il `.tft`, correggo la mappa |
| Pagina 1 ancora in inglese | etichette vecchie non nascoste | ripeti il punto 7.2 |
| Schermo bloccato all'avvio | non è il TFT: è il firmware (PSRAM) | usa solo il bin `h5-IT-20261028c.bin` |

**Prima di caricare il TFT sull'hardware**, se vuoi: mandami `h5_it.tft` e verifico
con lo script che gli ID dei nuovi componenti siano davvero 51…60 e 28…41 e che
i riquadri non escano dagli 800×480. Se un ID è diverso, aggiusto la tabella del
firmware in un minuto.
