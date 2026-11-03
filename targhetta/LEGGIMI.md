# Targhetta posteriore NanoEls H5

Targhetta da incollare sul retro del case, con la disposizione dei connettori.
Riprodotta dal PDF originale del progetto NanoEls H5 (`h5/case/h5.pdf`, disegno Figma).

## File

| File | Uso |
|---|---|
| `targhetta_h5_A4.pdf` | foglio A4 pronto (inglese): **2 copie** a grandezza reale, segni di taglio e righello di controllo 50 mm |
| `targhetta_h5.pdf` | solo targhetta (inglese), pagina da **53,6 × 33,5 mm** (scala 100%) |
| `targhetta_h5.svg` | versione vettoriale (inglese), per stampe o ridimensionamenti |
| `targhetta_h5.png` | anteprima 1600 × 1000 px (inglese) |
| `targhetta_h5_IT_A4.pdf` | foglio A4 pronto in **italiano**, stessa impostazione (2 copie, segni di taglio, righello 50 mm) |
| `targhetta_h5_IT.pdf` | solo targhetta in **italiano**, pagina da 53,6 × 33,5 mm |
| `targhetta_h5_IT.svg` | versione vettoriale in **italiano** |
| `targhetta_h5_IT.png` | anteprima 1600 × 1000 px (italiano) |
| `targhetta_h5_originale.pdf` | PDF originale del progetto (se lo stampi, va al **19%**) |
| `h5.fig` | sorgente Figma, modificabile su figma.com |
| `precedenti/targhetta_h5_IT_serigrafia.*` | edizione italiana con i nomi della serigrafia (`ZPULSE`, `ZSCALE`, ...) |

L'edizione italiana ha **tutti i nomi tradotti**: connettori e piedini (`IMPULSI Z`, `SCALA Z`,
`SEGN. JOY`, `TASTIERA`, `ALIM. 5V`, `VARIE`, `ABIL.`, `SENSO`, `PASSO`, `MASSA`, `DATI`).
Se preferisci i nomi uguali alla serigrafia della scheda, usa
`precedenti/targhetta_h5_IT_serigrafia.pdf` (o il relativo foglio A4).

## Stampa

Consigliato il foglio A4: `targhetta_h5_A4.pdf` (inglese) oppure `targhetta_h5_IT_A4.pdf`
(italiano). Entrambi contengono due copie e i segni di taglio. I PDF singoli
`targhetta_h5.pdf` / `targhetta_h5_IT.pdf` servono invece per stampa diretta su etichetta
adesiva o per chi vuole una pagina già della misura finale.

1. Aprire il foglio A4 scelto e stampare su A4 **al 100%**
   (Actual size / Nessun adattamento, senza "Adatta alla pagina").
2. Controllare il righello in fondo al foglio: deve misurare esattamente **50 mm**.
   Se misura diverso, la stampante sta scalando: disattivare l'adattamento.
3. Ritagliare lungo i segni agli angoli e incollare sul retro del case
   con nastro biadesivo.

La targhetta misura **53,6 × 33,5 mm**, cioè il 19% del disegno originale
(800 × 500 pt). Il foglio A4 contiene già la scala corretta: non serve ridurre nulla.

## Legenda connettori

Sulla targhetta italiana:

- **Z / X / Y** (assi): `5V ABIL. SENSO PASSO` (driver passo-passo)
- **IMPULSI / SCALE / ENCODER**: `5V MASSA B A`
- **SEGN. JOY** (joystick): `JB JY JX JZ`
- **TASTIERA**: `5V MASSA CLK DATI`
- **ALIM. 5V / ALIM. JOY**: `5V 5V MASSA MASSA`
- **VARIE**: `5V MASSA IO10 IO11`

Griglia: `Z X Y SEGN. JOY TASTIERA`, `IMPULSI Z IMPULSI X IMPULSI Y ALIM. JOY ENCODER`,
`SCALA Z SCALA X SCALA Y ALIM. 5V VARIE`.

Questi ordini sono quelli che si leggono **dal retro del case**, da sinistra a destra:
corrispondono ai piedi **1 → 4**, perché il **piede 1 è il +5V** (il lato della scritta `5V`).
Quindi per l'ENCODER guardando il retro il +5V (piede 1) è all'estremità **sinistra** e
A (piede 4) all'estremità **destra**. Le tabelle del foglio di cablaggio usano la stessa
convenzione: piede 1 = +5V, piede 4 = segnale più lontano (PASSO per gli assi, A per gli ingressi).

Sulla serigrafia della scheda gli stessi segnali si chiamano `ZPULSE`, `ZSCALE`, `JSIGNAL`,
`JPOWER`, `KEYBOARD`, `POWER`, `MISC`, `ENA/DIR/STEP`, `GND`: per un confronto diretto usa
l'edizione in `precedenti/` o il foglio di cablaggio.

## Schema di cablaggio

Per la corrispondenza completa connettore → pin → GPIO c'è il foglio A4 dedicato
(`../cablaggio/schema_cablaggio_A4.pdf`): una pagina da stampare al 100%, con tutte le
tabelle di piedinatura in italiano, una nota che riporta i nomi serigrafati sulla scheda
(`ZPULSE` = IMPULSI Z, `JSIGNAL` = SEGN. JOY, `GND` = MASSA, ...) e le note di collegamento.
