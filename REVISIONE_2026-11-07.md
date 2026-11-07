# Revisione NanoEls-H5 — 7 novembre 2026

**Repository**: `merletti/NanoEls-H5` (clone locale, branch `main`)
**Commit**: `f103a9d` — *Aggiunge alla checklist le prove di interfaccia a banco*
**Tag**: `v0.1.0` (indietro di 2 commit)
**Ambito**: tutto il contenuto pubblicato — 769 file, ~46 MB.

**Metodo**: lettura integrale di `firmware-it/h5/h5.ino` (12.646 righe) e dei
documenti, revisione dei sorgenti TypeScript dell'editor, esame degli script `gui/`.
Controlli automatici su link relativi, percorsi locali, segreti, duplicati esatti,
hash e dimensioni dei binari.

**Nessun file del repository è stato modificato durante la revisione.** Questo
rapporto è l'unico file aggiunto.

> **Stato alla pubblicazione.** Il rapporto fotografa il repository al commit
> `f103a9d`. I cinque difetti ALTA (XSS nell'elenco G-code, CSRF sulle POST,
> manuale d'uso, istruzioni di pubblicazione, nomi dei binari) sono stati
> corretti nel commit `5188270`; gli altri punti restano da valutare.

---

## Esito in breve

Il repository è completo, coerente nell'impianto e pubblicabile come vetrina: **non
contiene segreti, percorsi personali, link rotti o asset mancanti**. Le licenze
(MIT, con attribuzione ai progetti originali) sono corrette e l'hardware descritto
nel README corrisponde ai valori nel firmware.

Restano **2 problemi di sicurezza** (XSS memorizzato e POST senza controllo
dell'origine) e un problema documentale serio: **il manuale d'uso descrive
ancora l'interfaccia a due pagine precedente**, non il MENU a 13 card
attualmente nel TFT. A questi si aggiungono difetti circoscritti: test
dell'editor che non possono passare, lista G-code del TFT che esce dai limiti
oltre 32 file, copie offline della UI obsolete e nomi di binari che non esistono.

Le voci "Da completare prima della pubblicazione" (`README.md:140`) sono ormai
storiche: il repository è pubblico dal 6 novembre.

| Priorità | Area | Voce |
|---|---|---|
| 1 | Firmware | XSS memorizzato nella lista G-code (1.1) |
| 2 | Firmware | POST distruttive senza token né controllo Origin (1.2) |
| 3 | Manuale | Descrizione dell'interfaccia a 2 pagine, superata (4.1) |
| 4 | Editor | I test cercano testo inglese, l'output è italiano (3.1) |
| 5 | Doc | Binari firmware citati che non esistono (4.3) |
| 6 | Firmware | Lista G-code TFT oltre 32 file: indici fuori dai limiti (1.4) |

---

## 1. Firmware e sicurezza

### 1.1 [ALTA] XSS memorizzato nella lista dei G-code
`firmware-it/h5/h5.ino:4044`

```js
row.innerHTML = `
  <span class="gcode-item" data-name="${gcode}">${gcode}</span>
  ...
```

Il nome del file viene interpolato nell'HTML senza escaping. I nomi arrivano da
`/gcode/list` (`h5.ino:5731`) e vengono accettati in scrittura con il solo vincolo
di lunghezza (`h5.ino:5652-5657`, controllo a `5653`), senza whitelist
(`h5.ino:5714`).

**Impatto**: chiunque sulla LAN può creare un file con nome
`<img src=x onerror="...">`; quando l'operatore apre la sezione *Registro*, lo
script gira nel suo browser e può usare il WebSocket (comandi `@codice`, jog) e le
POST del controller. È il difetto più grave perché unisce persistenza e comandi
di movimento.

**Correzione**: costruire le righe con `textContent`/`createElement` e validare il
nome con `^[A-Za-z0-9._-]{2,32}$` in `saveGcode`, `removeGcodeByName` e
`readGcodeProgram`. La stessa whitelist va applicata anche lato server, non solo
nella UI.

### 1.2 [ALTA] POST distruttive senza token né controllo dell'origine
`firmware-it/h5/h5.ino:6321-6330`, `h5.ino:6460`

Il README documenta correttamente che la UI web non ha login (`README.md:151`),
ma non che le POST non verificano `Origin`/`Host` né richiedono un token:
`/gcode/remove`, `/config/reset`, `/wifi/reset`, `/reboot` possono essere invocate
da una pagina web qualsiasi aperta nello stesso browser (CSRF), senza leggere la
risposta.

**Correzione**: token di sessione generato all'avvio e incluso nelle POST, oppure
controllo `Origin`/`Host` più header personalizzato; rifiutare le richieste
`application/x-www-form-urlencoded` provenienti da origini diverse.

### 1.3 [MEDIA] Buffer WebSocket: 1024 byte contro costanti da 100.000
`firmware-it/h5/h5.ino:83-84`, `6408-6409`, `5619`, `8473`

Le costanti `INCOMING_BUFFER_SIZE`/`OUTGOING_BUFFER_SIZE` valgono 100.000 e **non
sono usate**; i buffer sono allocati con 1024. Il risultato di `writeBuffer` in
`handleWebSocketEvent` (`:5619`) non è controllato e il buffer in ingresso
alimenta `taskGcode` (`:8473`): un comando o un programma inviato via WebSocket
oltre 1024 byte viene troncato in silenzio.

**Correzione**: allocare con le costanti (o eliminare le costanti inutilizzate) e
verificare il valore di ritorno, rispondendo con un errore esplicito.

### 1.4 [MEDIA] Lista G-code del TFT: oltre 32 file indicizza fuori dai limiti
`firmware-it/h5/h5.ino:10233-10248`, `10300`, `10263-10318`

`tftGcodeList` scrive solo i primi `max` elementi ma restituisce il **totale**
(`count++` fuori dal blocco `if (count < max)`). Con più di
`TFT_GCODE_MAX` (32, `h5.ino:10218`) file, `tftGcodeCount` supera la dimensione
degli array `tftGcodeNames`/`tftGcodeSizes` e `tftDrawGcodeAll`/`tftGcodeDetails`
leggono `String` oltre il fondo dell'array: nomi corrotti o crash del task
display.

**Correzione**: restituire `min(count, max)` oppure gestire esplicitamente
l'eccedenza ("…altri N file") senza indicizzare oltre il limite.

### 1.5 [MEDIA] Emergenza: mutex non rilasciati e attese non interrompibili
`firmware-it/h5/h5.ino:6459-6465`, `7293-7303`, `8001`, `8079`, `8134`

`setEmergencyStop` prende i tre mutex con timeout di 10 tick e non li rilascia
mai. I cicli `waitForPendingPosNear0`/`waitForPendingPos0` non controllano
`emergencyStop`, quindi i task di movimento possono restare in attesa e non
raggiungere la riga che disabilita i driver.

**Impatto pratico**: limitato, perché il manuale prevede spegnimento e riavvio
dopo un'emergenza (`screen-it/MANUALE_USO.md:75`); resta però un rischio latente
(motori ancora abilitati) se in futuro l'emergenza diventasse ripristinabile.

**Correzione**: usare un flag atomico senza mutex e far uscire le attese su
`emergencyStop != ESTOP_NONE`; disabilitare i driver dentro `setEmergencyStop`.

### 1.6 [MEDIA] `isOn` letto da task diversi senza `volatile`
`firmware-it/h5/h5.ino:4198`

`bool isOn = false;` è scritto da `taskGcode`/`taskDisplay` e letto dal task WiFi
e da `loop()`. Senza `volatile` o sezione critica il compilatore può mantenere il
valore in registro e servire uno stato vecchio alla UI.

### 1.7 [MEDIA] Confronti su `micros()` non sicuri sull'overflow
`firmware-it/h5/h5.ino:7160`, `10652`

`micros() > spindleEncTime + 100000` e `micros() <= spindleEncTime + 100000`
falliscono al wrap di `micros()` (circa ogni 71 minuti): per un istante lo stato
"mandrino fermo" risulta invertito e il G-code può essere rifiutato o accettato a
sproposito.

**Correzione**: `(uint32_t)(micros() - spindleEncTime) > 100000`.

### 1.8 [MEDIA] Riavvio per nuova configurazione solo se il WiFi è attivo
`firmware-it/h5/h5.ino:6433`, `12599`

`configRestartPending` è servito solo dentro `taskWiFi`, creato solo se
`WIFI_ENABLED`. Con WiFi disabilitato, le modifiche che richiedono riavvio (per
esempio l'asse Y) non vengono mai applicate.

### 1.9 [MEDIA] Timer asincrono calcolato sempre sull'asse Z
`firmware-it/h5/h5.ino:7858-7863`

`getTimerLimit()` usa `z.motorSteps` e `z.screwPitch` anche in `MODE_Y`, dove il
timer pilota `y`. Con parametri diversi fra gli assi la velocità è sbagliata.
Usare `getAsyncAxis()`.

### 1.10 [BASSA] Nomi dei file G-code senza sanificazione del percorso
`firmware-it/h5/h5.ino:5657`, `5678`

Il nome è concatenato a `/` e `.gcode` senza vietare `/`, `..` o caratteri di
controllo. L'impatto è limitato a LittleFS e alla LAN, ma va chiuso con la stessa
whitelist del punto 1.1.

### 1.11 [BASSA] Piccoli difetti nella UI dei G-code
`firmware-it/h5/h5.ino:4048-4062`, `4101`

- Il click sulla `×` esegue anche il click della riga: il file viene prima
  caricato nell'editor e poi rimosso.
- Il click sull'area della dimensione chiama `loadGcode(event.target.dataset.name)`
  con `dataset.name` assente → `name=undefined`.
- `fetchFreeSpace()` usa `.find(...).substr` senza controllo: se `/status` non
  contiene `LittleFS.freeSpace=` la funzione lancia un'eccezione.

### 1.12 [NOTA] Gestione credenziali
La password WiFi non è mai restituita dalla UI (`h5.ino:5547`) e i campi sono
mascherati; la password dell'access point è fissa e documentata
(`h5.ino:81-82`) ma viene anche stampata su Serial (`h5.ino:6396`). Accettabile
per un access point di configurazione, da togliere se il monitor seriale finisce
in log condivisi.

---

## 2. Copie offline della UI web

### 2.1 [MEDIA] `preview/` e `gui/index_now.html` sono build superate
`preview/webui-preview.html:1360`, `gui/index_now.html`

Il file servito da `preview/serve.pl` si presenta come **`NanoEls v-test`** e non
contiene l'upload G-code da file, il riavvio del controller e il backup
configurazione presenti nell'HTML incorporato nel firmware. `gui/index_now.html`
è ancora più vecchio. Nessuno dei due è citato nel README.

**Impatto**: chi apre la "preview" crede di vedere la UI attuale e non trova
funzioni documentate.

**Correzione**: rigenerarle dall'HTML del firmware (unica fonte di verità) e
aggiungere un marcatore `<!-- build: data/versione -->`, oppure rimuoverle.

### 2.2 [MEDIA] Percorso del binario non coerente con `arduino-cli`
`README.md:93`

Il README indica `firmware-it/h5/build/h5.ino.bin`, ma `arduino-cli compile`
senza `--build-path`/`--output-dir` salva gli artefatti nella cartella temporanea
del sistema. Aggiungere il parametro al comando documentato:

```sh
arduino-cli compile --build-path firmware-it/h5/build ... firmware-it/h5
```

---

## 3. Editor lathecode

### 3.1 [MEDIA] I test non possono passare
`lathecode-italiano/sorgenti/test/planner-fixtures/fixtures.test.ts:127`
`lathecode-italiano/sorgenti/test/sample-toolpaths/sample-toolpaths.test.ts:432`

Le asserzioni cercano la stringa inglese `G91 ; relative positioning`, mentre il
generatore scrive `G91 ; posizionamento relativo`
(`sorgenti/src/gcode/gcodeutils.ts:46`). La suite è rossa per costruzione.

**Correzione**: verificare `startsWith('G91')` oppure aggiornare l'asserzione.

### 3.2 [MEDIA] I test sovrascrivono i file di riferimento
`.../fixtures.test.ts:56`, `:128`; `.../sample-toolpaths.test.ts:140`, `:435`

`saveGCode()` riscrive i `.gcode.txt` di riferimento e l'unica verifica è un
`toContain`. I file versionati contengono ancora intestazioni inglesi obsolete
(per esempio `test/planner-fixtures/sphere.gcode.txt:8`): il test non protegge da
regressioni e maschera le differenze.

**Correzione**: confronto con golden file in sola lettura, rigenerazione solo con
un flag esplicito.

### 3.3 [MEDIA] G-code non valido con profilo vuoto o durata zero
`sorgenti/src/gcode/gcodeutils.ts:22`, `:44`, `:64`

- `moves[0]!` lancia `TypeError` se non ci sono movimenti.
- `cutDuration * 100 / duration` produce `NaN%` quando la durata è 0.
- La prima riga `X${first.yStartMm}` non è formattata come le altre.

**Correzione**: guardia su `moves.length` e durata, formattazione con
`toFixed(3)`.

### 3.4 [MEDIA] `THREE` usato senza import: probabile errore di compilazione
`sorgenti/src/stl.ts:4`

`THREE.Object3D` non è importato (il file importa solo `resetRotation` e
`STLExporter`) e `tsconfig.json` è `strict` senza tipi globali. Con
`npm run build` (`tsc && vite build`) il controllo dei tipi dovrebbe fallire.
**Da confermare compilando**: qui `node`/`npm` non sono nel PATH.

**Correzione**: `import type * as THREE from 'three';`.

### 3.5 [MEDIA] `index.html` non è verificabile
`lathecode-italiano/index.html:1` (1,6 MB)

Artefatto Vite single-file senza versione, data o commit. Non è possibile sapere
se corrisponde ai sorgenti pubblicati. Aggiungere un commento di build e
marcarlo `linguist-generated` in `.gitattributes`.

### 3.6 [MEDIA] Profilo più grande del grezzo accettato in silenzio
`sorgenti/src/planner/rasterizer.ts:111-127`

`fillPolygon` ritaglia ai bordi del bitmap: un profilo esterno al grezzo viene
tagliato senza errore. **Correzione**: rifiutare il piano quando il raggio del
profilo supera quello del grezzo e indicare la riga.

### 3.7 [MEDIA] Utensili con parametri mancanti accettati
`sorgenti/src/common/lathecode.ts:258-260`

`TOOL RECT L0` diventa 3 mm (`length || 3`) e `TOOL ROUND` senza `R` produce un
utensile 0×0, senza errore. **Correzione**: rendere `R`/`L` obbligatori e
rifiutare i valori ≤ 0.

### 3.8 [BASSA] Valori espliciti 0 mascherati dai default
`sorgenti/src/common/lathecode.ts:273-281`

`|| 200`, `|| 0.5`, `|| 0.1` trasformano uno zero esplicito nel default, senza
avviso. Usare `??` e validare il campo.

### 3.9 [BASSA] Errore generico che perde riga e colonna
`sorgenti/src/common/latheparser.ts:568`

`throw new Error('Il cono attraversa l'asse')` non è un
`LatheCodeSyntaxError` e sfugge alla gestione che riporta posizione nel testo.

### 3.10 [BASSA] README dell'editor
`lathecode-italiano/README.md:37`, `:60`

La struttura indica la cartella `lathecode-italiano-pubblicazione/`, ma nel repo
si chiama `lathecode-italiano/`. Il comando suggerito `npx vitest run src`
esclude i test in `test/`, mentre `npm test` li include (richiedono Chrome).

---

## 4. Documentazione

I documenti sono dettagliati e in gran parte utili, ma diversi sono scritti per
l'interfaccia precedente o per firmware con altri nomi, e ora contraddicono il
repository. È l'area con le incongruenze più ampie.

### 4.1 [ALTA] Il manuale d'uso descrive l'interfaccia a due pagine precedente
`screen-it/MANUALE_USO.md:4`, `:11-12`, `:64-90`, `:139-161`

Il manuale è ancora impostato sul vecchio HMI:

- l'intestazione cita TFT del **29/10/2026** e firmware `h5-IT-20261028c.bin`;
- §3 descrive pagina 0 con la striscia `Pronto - NanoEls` (stringa **assente**
  dal firmware);
- §4 "Pagina 0: comandi di lavoro" mette `OFF`/`ON` in alto a sinistra, il tasto
  blu `MODALITA` e le frecce jog sulla stessa pagina;
- §5 "Pagina 1: scelta della modalità" parla di **dodici card** più il chip
  `SCANALATURA`.

Nell'HMI attuale pagina 0 è il **MENU a 13 card** (F1–F13 + MERLINO), `ELS`/`AVVIA`
stanno in alto a destra (firmware `tftDrawMenuState`, riquadro 684,18,106,38),
pagina 1 è INGRANAGGI e ogni modalità ha la propria sottopagina; la pagina live è
la 21 (`h5.ino:9700-9708`).

**Correzione**: riscrivere §3–§5 e le procedure sulla base delle schermate
attuali. È il difetto documentale più serio: è il manuale operativo di una
macchina che muove gli assi.

### 4.2 [ALTA] Istruzioni di pubblicazione non più vere
`ISTRUZIONI.md:3-5`, `PUBBLICAZIONE.md:26`

`ISTRUZIONI.md` dice "copia del progetto al **4 novembre**", "niente cartelle di
build, backup o screenshot di prova" e "**Non è stato pubblicato nulla online**".
`PUBBLICAZIONE.md:26` chiede di verificare un "repository senza remote".

Il repository è pubblico su `github.com/merletti/NanoEls-H5`, branch `main`
allineato a `origin`, ultimo commit del 6 novembre; in `gui/` sono tracciati
screenshot delle pagine, `contact_sheet.jpg`, `ev_long_backup/` e `build2.log`.

**Correzione**: aggiornare data e stato ("pubblicato il 6/11/2026"), e ripulire
gli artefatti oppure togliere l'affermazione che non ci sono.

### 4.3 [ALTA] Nomi di binari firmware inesistenti (3 occorrenze)
`screen-it/MANUALE_USO.md:4`, `:512`;
`screen-it/GUIDA_NEXTION_EDITOR.md:232`, `:276`

I documenti citano `h5-IT-20261028c.bin` e `h5-IT-20261104-v65.bin`. Nel repo
esiste solo `firmware-it/h5-IT-20261105-v65.bin`, l'unico citato correttamente in
`ISTRUZIONI.md:74`. Chi segue il manuale cerca un file che non c'è.

### 4.4 [MEDIA] Conteggio pagine incoerente e tabella incompleta
`README.md:26`, `:133`; `MONTAGGIO_TORNIO.md:154`; `PUBBLICAZIONE.md:44`;
`screen-it/TABELLA_PAGINE_MENU.md:157-182`, `:293`

I documenti dicono **21 pagine**; l'HMI contiene `page0`…`page21` (**22**).
La tabella delle pagine ne elenca **19** (indici 0-17 e 21) e omette 18
(tastierino), 19 (pannello impostazioni) e 20 (tastiera), pur citandole più sotto
(`TABELLA_PAGINE_MENU.md:293`). Le tre pagine sono usate dal firmware
(`h5.ino:9724`, `10389`, `10700`).

**Correzione**: decidere cosa si conta (tastierino escluso?), completare la
tabella con 18-20 e allineare il numero nei quattro documenti.

### 4.5 [MEDIA] Tabella pagine: mappatura superata e percorso errato
`screen-it/TABELLA_PAGINE_MENU.md:4`, `:259-267`

- Il percorso del firmware è scritto `firmware-it/h5.ino` (corretto:
  `firmware-it/h5/h5.ino`) in **due** punti; altrove è giusto
  (`README.md:56`, `PUBBLICAZIONE.md:73`).
- §5 è un piano di lavoro mai aggiornato: dice che il firmware "usa ancora
  `page 0` come pagina di controllo e `setText("t3", …)"`". Nel firmware non
  esiste alcuna `setText`; le costanti sono `TFT_MENU_PAGE 0` e
  `TFT_WORK_PAGE 21` (`h5.ino:9700-9708`).
- Gli eventi card sono descritti come `0x65 <pagina> <id>`; nel firmware `0x65`
  è l'ultimo codice jog (`h5.ino:11216`) e le card usano `0x71`…`0x7C`
  (`h5.ino:11004`).
- I nomi interni sono indicati `page2…page18`, ma nell'HMI sono
  `page0…page21`.

### 4.6 [MEDIA] Manuale: tastierino diverso dal firmware
`screen-it/MANUALE_USO.md:172`, `:183`

Il manuale dice "Non esiste il tasto decimale" e "Massimo 8 cifre"; la pagina 18
invia il punto decimale `0x5E` e il limite è `TFT_KEYPAD_MAXLEN 12`
(`h5.ino:10702`, `10710`, `10900`).

### 4.7 [MEDIA] Manuale: il reset non è qualsiasi STOP
`screen-it/MANUALE_USO.md:59`, `:433-435`

Il testo lascia intendere che uno STOP tenuto 3 secondi resetti. Il reset scatta
solo al **rilascio del tasto fisico OFF** dopo oltre 3000 ms
(`h5.ino:8946-8951`); lo STOP da TFT (`0x70`, `h5.ino:11002`) non resetta.
Allineare alla prova 3 del collaudo.

### 4.8 [MEDIA] Checklist: il MAC non è nella pagina INFO
`collaudo/checklist_sicurezza.html:350-352`

Il controllo A.9 chiede "Versione H5V65, indirizzo IP e **MAC**"; la pagina INFO
mostra versione, data, IP, uptime, heap libero ed errori, **non il MAC**
(`h5.ino:9977-9996`). Correggere il controllo o aggiungere il MAC alla pagina.

### 4.9 [MEDIA] Tabelle componenti e guida Nextion descrivono l'HMI legacy
`screen-it/TABELLA_COMPONENTI.md:3-4`, `:280-281`;
`screen-it/GUIDA_NEXTION_EDITOR.md:210`, `:213`, `:259`

Descrivono la ricostruzione dell'HMI a due pagine con 12 card e ID 1-60; la guida
presuppone file `h5.HMI`/`h5.tft` (nel repo ci sono `h5_it.HMI`/`h5_it.tft`) e
indica "~3,8 MB" contro i 4,9 MB reali. Va marcato come legacy o riscritto.

### 4.10 [MEDIA] README: immagine del MENU vecchio
`README.md:44`

La tabella immagini usa `screen-it/menu_bg.png`, che la tabella picture dichiara
"vecchio MENU (non più usato)" (`TABELLA_PAGINE_MENU.md:23`). Il MENU attuale è
`menu13_merlino.png` (picture 24).

### 4.11 [BASSA] Altre incoerenze puntuali
- `README.md:52-53` non cita il driver Y opzionale presente nel firmware
  (Y ENA 1 / DIR 2 / STEP 17).
- `README.md:66` chiama "sfondi 800×480" anche sprite 800×52, card 288×358 e
  tastierino 1600×104.
- `README.md:59-76` non cita `preview/`, `screen-it/import_clean/`,
  `screen-it/import_card49/`, `targhetta/precedenti/`.
- `MANUALE_USO.md:539` "GIRI dall'accensione" contraddice `:101`;
  `:129-133` omette X-INGRANAGGI fra le modalità con jog manuale.
- `MONTAGGIO_TORNIO.md:61` riporta un MAC hardcoded (`7c:e8:b1:b0:93:5c`);
  `:66` indica backlash encoder 0 contro `DEFAULT_ENCODER_BACKLASH 3`.
- `GUIDA_NEXTION_EDITOR.md:210` contiene un percorso locale
  (`...\nanoels-h5\screen-it`).
- `TABELLA_PAGINE_MENU.md:176` cita la picture 37 assente dalla tabella;
  `:45` parla di "18 righe, una per indice pagina" su 22 pagine.
- `PUBBLICAZIONE.md:43` dice "tutti i default ripristinati": `reset()` azzera
  stop, posizioni, origini, passo, principi, modo, unità e rapporto cono, non
  tutti i parametri (`h5.ino:8807-8844`).
- `collaudo/checklist_sicurezza.html:217-238` intitola "Le 13 modalità" un
  elenco di 9 modalità più varianti di filettatura; A.3 (`:314-316`) attribuisce
  a FILETTATURA i campi "SENSO/PRINCIPI/PASSATE", mentre la pagina 2 ha
  PITCH/STARTS/RATIO/ZMAX/HAND/FEED.
- `screen-it/TABELLA_PAGINE_MENU.md:237` e `:247-248` riportano dimensioni e md5
  superati: TFT reale **4.928.740 byte** md5 `84c996fc…`, HMI **13.716.534 byte**
  md5 `25159fe8…`. Vanno datati come storici o aggiornati.

---

## 5. Igiene del repository

### 5.1 [MEDIA] `.gitignore` in contraddizione con i file tracciati
`.gitignore:19-23`

Le regole ignorano `gui/*.log`, `gui/*.txt`, `gui/*.json` e `gui/*.png`, ma nel
repo risultano **17 file tracciati che corrispondono a quelle regole**
(`gui/acts*.txt`, `gui/build2.log`, `gui/tft_upload_curl.log`,
`gui/r13c.txt`, `gui/fw_upload_result.txt`…). In totale `gui/` contiene 105 file
`.txt/.log/.json`.

**Decidere**: o sono artefatti (allora `git rm --cached` e restano esclusi), o
servono (allora vanno tolti i pattern e documentati).

### 5.2 [MEDIA] Pattern `.gitignore` non valido
`.gitignore:17`

```
mockup-tft${id}.png
```

`${id}` è un residuo di script: il pattern corrisponde solo a un file chiamato
letteralmente `mockup-tft${id}.png`. Va sostituito con il pattern reale (per
esempio `mockup-tft/_*.png`).

### 5.3 [MEDIA] `gui/` pubblicata senza guida
`gui/` — 270 file (149 di primo livello), di cui 123 script PowerShell, 9 Perl,
7 HTML, un `.hmi` vuoto

Nessun `README` e nessuna intestazione di scopo: `gui/diag.ps1:1` inizia con
`param(...)`. Alcuni script **scrivono negli asset pubblicati** con percorsi
relativi alla cartella corrente (`gui/make_menu_merlino.ps1:2-3`,
`gui/make_merlino.ps1:2`, `gui/rename_thread.ps1:37-40`), quindi vanno lanciati
da una posizione precisa. `gui/links_patch.pl:4` modifica `h5_it.HMI` con offset
in byte cablati: funziona solo su quella build.

**Correzione**: un `gui/LEGGIMI.md` con scopo, prerequisiti (Windows, Chrome,
Perl, Nextion Editor), ordine di esecuzione; oppure escludere `gui/` dalla
pubblicazione e tenerla in un repository separato.

### 5.4 [MEDIA] Asset duplicati
- 18 coppie `mockup-tft/*.png` = `screen-it/*_bg.png` (identiche byte per byte:
  `cono`, `ellisse`, `tornitura`, `spianatura`, `xgear`…).
- `gui/label.svg` = `targhetta/targhetta_h5.svg` (245 KB).
- `gui/ev_long_backup/` = copia quasi completa di `gui/ev/` (27 file).
- `chip_ingr.png` = `chip_m_ingr.png` in radice.

**Correzione**: scegliere una fonte e rimuovere le copie (i mockup possono
diventare riferimenti nel README, ma non duplicati).

### 5.5 [BASSA] File morti
- `chip_ingr.png`, `chip_m_ingr.png`, `chip_scan.png` in radice: non citati da
  nessun documento o script.
- `gui/snap.hmi`: 0 byte.
- `gui/pages/page19.png` = `gui/pages/page20.png` (sospetto errore di cattura).

### 5.6 [BASSA] Varianti superate lasciate nel repo
`screen-it/` conserva `*_preFILETTATURA.png`, `page0_bg2..bg7.png`,
`card_strip*`. La tabella picture dichiara "non più usati" i picture 5-19, ma
restano nell'HMI e nel TFT (4,9 MB). Un riordino ridurrebbe peso e confusione.

### 5.7 [BASSA] `preview/serve.pl` serve qualsiasi percorso
`preview/serve.pl:20-24`

Toglie la `/` iniziale e apre il file relativo alla cartella corrente, quindi
anche `../…`. Ascolta solo su `127.0.0.1`, quindi il rischio è locale; va comunque
limitato alla cartella `preview/`.

### 5.8 [BASSA] Tag e release
Il tag `v0.1.0` punta a `3340068`, due commit prima di `main`: non include la
checklist di collaudo sicurezza. Non esistono release GitHub collegate.

---

## 6. Cosa è a posto (verificato)

- **Nessun segreto** nel repository: nessuna chiave, token o chiave privata. La
  chiave OpenRouter dell'editor è inserita dall'utente e resta nel browser.
- **Nessun percorso locale assoluto** in documenti, script, firmware o HTML.
- **Nessun link relativo rotto** nei `.md` né riferimenti a immagini mancanti
  negli HTML di `collaudo/`, `cablaggio/`, `preview/`.
- **Licenze**: MIT con copyright originale di Maxim Kachurovskiy e nota per i
  contributori; l'editor conserva la licenza del progetto lathecode.
- **README coerente col firmware**: encoder GPIO 13/14 (`h5.ino:15-16`), 1200
  impulsi/giro (`h5.ino:7`), Nextion 115200/primo upload 9600 (`h5.ino:542-543`),
  AP `NanoEls-H5-Setup` / `nanoels-h5` (`h5.ino:81-82`), `192.168.4.1`.
- **Pin e cablaggio**: i pin di `MONTAGGIO_TORNIO.md:32-40` e di
  `cablaggio/schema_cablaggio.html` coincidono con i `#define` del firmware
  (Z 41/42/35, X 16/15/7, Y 1/2/17, impulsi 8/18-21/47, encoder A13/B14,
  joystick 38/6/5/4, tastiera 36/37, UART 44/43).
- **Password WiFi** mai restituita dalla UI web; soli campi mascherati e vuoti.
- **Emergenza**: manuale (`MANUALE_USO.md:75`) e firmware coincidono (spegnimento
  e riaccensione); il reset generale cancella i finecorsa come dichiarato
  (`MANUALE_USO.md:433`, `h5.ino:8807`).
- **Binari validi**: PDF con header corretto, SVG ben formati, HMI/TFT integri;
  il firmware `h5-IT-20261105-v65.bin` corrisponde a `SOFTWARE_VERSION 65`.
- **Tagli di linea** coerenti con `.gitattributes` (`.ino`/`.md` LF, `.ps1` CRLF).

---

## 7. Verifiche non eseguite

Non sono stati eseguiti, perché gli strumenti non sono nel PATH di questa
macchina:

- compilazione del firmware (`arduino-cli` assente);
- build e test dell'editor (`node`/`npm` assenti);
- caricamento su Nextion (serve il display).

I giudizi su questi punti sono basati sulla lettura del codice e sono indicati
come "da confermare" dove serve.

---

## 8. Ordine di intervento consigliato

1. **Sicurezza UI** (1.1, 1.2, 1.10): escaping, whitelist dei nomi e token sulle
   POST. Una sola patch in `h5.ino`.
2. **Manuale d'uso** (4.1, 4.6, 4.7): riscrivere §3–§5 e le procedure
   sull'interfaccia a 13 card. È il documento che si legge davanti alla macchina.
3. **Test dell'editor** (3.1, 3.2): riallineare l'asserzione e smettere di
   riscrivere i golden; poi `npm run build` per confermare 3.4.
4. **Affidabilità firmware** (1.3, 1.4, 1.6-1.9): buffer, limite 32 file,
   `volatile`, overflow di `micros()`, timer asse Y.
5. **Copie UI, binari e nomi file** (2.1, 2.2, 4.2, 4.3): rigenerare o rimuovere
   `preview/` e `gui/index_now.html`; correggere il comando di build e i nomi dei
   binari; aggiornare le istruzioni di pubblicazione.
6. **Resto della documentazione e igiene** (4.4, 4.5, 4.8-4.11, 5.x): conteggio
   pagine, tabella componente/guida legacy, hash, `.gitignore`, `gui/LEGGIMI.md`,
   duplicati.

---

### Appendice — occorrenze ripetute da correggere insieme

| Testo | Occorrenze |
|---|---|
| `firmware-it/h5.ino` (percorso errato) | `TABELLA_PAGINE_MENU.md:4`, `:259` |
| binari `h5-IT-20261028c` / `h5-IT-20261104-v65` | `MANUALE_USO.md:4`, `:512`; `GUIDA_NEXTION_EDITOR.md:232`, `:276` (reale: `h5-IT-20261105-v65.bin`) |
| "prima della pubblicazione" | `README.md:19`, `:140` |
| "non pubblicato" / "senza remote" | `ISTRUZIONI.md:3-5`; `PUBBLICAZIONE.md:26` |
| "21 pagine" | `README.md:26`, `:133`; `MONTAGGIO_TORNIO.md:154`; `PUBBLICAZIONE.md:44` |
| descrizione interfaccia a 2 pagine | `MANUALE_USO.md:11-12`, `:64-90`, `:139-161`; `TABELLA_COMPONENTI.md:3-4`; `GUIDA_NEXTION_EDITOR.md:259` |
| dimensioni/hash HMI e TFT | `TABELLA_PAGINE_MENU.md:237`, `:247-248` |
| UI web in più copie | `preview/webui-preview.html`, `gui/index_now.html`, `h5.ino` (fonte) |
| asset duplicati | 18 coppie `mockup-tft`/`screen-it`, `gui/label.svg`/`targhetta`, `gui/ev_long_backup`/`gui/ev` |
