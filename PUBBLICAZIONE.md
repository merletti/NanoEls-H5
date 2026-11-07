# Pubblicazione del progetto

Il repository è pubblico dal 6 novembre 2026 su
`https://github.com/merletti/NanoEls-H5` (branch `main`, remote `origin` già
configurato). Questa checklist serve ora per le modifiche successive e per la
prima release: non va rifatta la creazione del repository se non in caso di
ricreazione da zero (sezione 4).

## 1. Contenuti da completare

- [x] **Link del progetto originale**: in [README.md](README.md), sezione
      *Progetto originale*, rimanda a `kachurovskiy/nanoels/h5`.
- [x] **Link «offri un caffè»**: sezione *Sostieni il progetto* di
      [README.md](README.md), con il profilo PayPal
      `paypal.com/biz/profile/officinamerletti`. Le donazioni restano
      facoltative.
- [ ] **Nome autore**: in [LICENSE](LICENSE) c'è `NanoEls H5 contributors`;
      se vuoi comparire con nome e cognome, aggiornalo (e la config git del repo).
- [ ] **Screenshot reali**: le immagini del README sono gli sfondi 800×480 del
      TFT; se possibile aggiungere una foto del controller montato sul tornio.
- [ ] **Video breve** (opzionale): 20–30 secondi di una lavorazione reale.

## 2. Controlli prima di ogni push

- [ ] Nessun segreto nel repo: la password WiFi dell'utente sta solo in NVS e il
      backup NVS non è versionato. L'AP di setup (`nanoels-h5`) è una password
      pubblica prevista dal firmware, non un segreto.
- [ ] Nessun file personale o percorso locale nei documenti.
- [ ] `git status` pulito e remote `origin` puntato a
      `github.com/merletti/NanoEls-H5` (controllo: `git remote -v`).
- [ ] Licenza: il progetto deriva da NanoEls (MIT). La nota di copyright originale
      deve restare in [LICENSE](LICENSE).
- [x] Avvertenza di responsabilità presente in [README.md](README.md) (sezione
      *Responsabilità*).
- [ ] I binari in `firmware-it/` corrispondono al firmware compilato (versione in
      `SOFTWARE_VERSION`).

## 3. Test obbligatori prima di una release

Firmware e interfaccia:

- [ ] tutte le 13 modalità: ON/OFF, partenza, finecorsa, STOP;
- [ ] filettatura DX e SX, più principi, filetto conico;
- [ ] cono con quote Morse 5: il rapporto mostrato deve essere `1 : 19`;
- [ ] G-code: caricamento da UI web, esecuzione, pausa con mandrino fermo;
- [ ] emergenze: `Posizione fuori macchina`, `Spento in manuale`;
- [ ] ripristino da `SETUP → RIPRISTINA` → `RIPRISTINA MACCHINA` (doppio tocco
      entro 3 s): tutti i default ripristinati e riavvio automatico;
- [ ] 22 pagine TFT, tastierino numerico e tastiera testuale sul pannello;
- [ ] aggiornamento OTA di firmware e display;
- [ ] UI web da telefono: quote, finecorsa, WiFi, parametri assi;
- [ ] riavvio: le impostazioni NVS sono conservate; il WiFi si riconnette.

Meccanica:

- [ ] sincronizzazione Z/X su un pezzo di prova, senza utensile;
- [ ] controllo dei valori live durante la lavorazione;
- [ ] prova su una seconda configurazione hardware, se disponibile.

## 4. Repository pubblico (già creato)

Il repository esiste: `https://github.com/merletti/NanoEls-H5`, visibilità
**Public**, branch `main`, con *Issues* attive. Descrizione e argomenti (`lathe`,
`els`, `esp32-s3`, `nextion`, `arduino`) si modificano dalla pagina principale
del repository con l'ingranaggio accanto a *About*, nella colonna di destra.

Solo se il repository va ricreato da zero:

1. Su GitHub creare un repository vuoto `NanoEls-H5`, senza README né licenza
   (sono già nel progetto), visibilità **Public**.
2. Collegare e caricare:

   ```sh
   git remote add origin https://github.com/merletti/NanoEls-H5.git
   git branch -M main
   git push -u origin main
   ```

## 5. Prima release

1. Aggiornare la versione in `firmware-it/h5/h5.ino` (`SOFTWARE_VERSION`) e
   ricompilare.
2. Creare il tag e caricare la release con i file pronti all'uso:

   ```sh
   git tag -a v0.1.0 -m "NanoEls H5 v0.1.0"
   git push origin v0.1.0
   ```

   Allegati consigliati: `firmware-it/h5-IT-<data>-v<versione>.bin`,
   `screen-it/h5_it.tft`, `screen-it/MANUALE_USO.md` (o PDF) e, se presenti,
   foto/video.
3. Nel testo della release: novità, istruzioni di aggiornamento (prima firmware,
   poi TFT) e avvertenza sulla sicurezza (motori, utensile, STOP).

## 6. Dopo la pubblicazione

- [ ] Aggiungere il badge della release al README, se utile.
- [ ] Tenere aggiornato lo stato dei test nella sezione *Stato del progetto*.
- [ ] Rispondere alle issue citando la versione (`H5V65`) mostrata dalla UI web.
- [ ] Le donazioni restano facoltative: nessuna funzione va messa a pagamento.
