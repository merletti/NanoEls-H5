# Pubblicazione del progetto

Checklist per mettere online il repository in modo libero e gratuito, con la
possibilità di offrire un caffè. Da completare quando il progetto è testato.

## 1. Contenuti da completare

- [ ] **Link donazioni**: sostituire il segnaposto in [README.md](README.md)
      (sezione *Sostieni il progetto*) con il link Buy Me a Coffee / Ko-fi.
      Il link va creato prima: il progetto non ne contiene ancora uno.
- [ ] **Nome autore**: in [LICENSE](LICENSE) c'è `NanoEls H5 contributors`;
      se vuoi comparire con nome e cognome, aggiornalo (e la config git del repo).
- [ ] **Screenshot reali**: le immagini del README sono gli sfondi 800×480 del
      TFT; se possibile aggiungere una foto del controller montato sul tornio.
- [ ] **Video breve** (opzionale): 20–30 secondi di una lavorazione reale.

## 2. Controlli prima del push

- [ ] Nessun segreto nel repo: la password WiFi dell'utente sta solo in NVS e il
      backup NVS non è versionato. L'AP di setup (`nanoels-h5`) è una password
      pubblica prevista dal firmware, non un segreto.
- [ ] Nessun file personale o percorso locale nei documenti.
- [ ] `git status` pulito e repository senza remote.
- [ ] Licenza: il progetto deriva da NanoEls (MIT). La nota di copyright originale
      deve restare in [LICENSE](LICENSE).
- [ ] I binari in `firmware-it/` corrispondono al firmware compilato (versione in
      `SOFTWARE_VERSION`).

## 3. Test obbligatori prima della pubblicazione

Firmware e interfaccia:

- [ ] tutte le 13 modalità: ON/OFF, partenza, finecorsa, STOP;
- [ ] filettatura DX e SX, più principi, filetto conico;
- [ ] cono con quote Morse 5: il rapporto mostrato deve essere `1 : 19`;
- [ ] G-code: caricamento da UI web, esecuzione, pausa con mandrino fermo;
- [ ] emergenze: `Posizione fuori macchina`, `Spento in manuale`;
- [ ] reset generale (STOP tenuto 3 s): tutti i default ripristinati;
- [ ] 21 pagine TFT, tastierino numerico e tastiera testuale sul pannello;
- [ ] aggiornamento OTA di firmware e display;
- [ ] UI web da telefono: quote, finecorsa, WiFi, parametri assi;
- [ ] riavvio: le impostazioni NVS sono conservate; il WiFi si riconnette.

Meccanica:

- [ ] sincronizzazione Z/X su un pezzo di prova, senza utensile;
- [ ] controllo dei valori live durante la lavorazione;
- [ ] prova su una seconda configurazione hardware, se disponibile.

## 4. Creare il repository pubblico

1. Su GitHub creare un repository vuoto `nanoels-h5`, senza README né licenza
   (sono già nel progetto), visibilità **Public**.
2. Collegare e caricare:

   ```sh
   git remote add origin git@github.com:<utente>/nanoels-h5.git
   git branch -M main
   git push -u origin main
   ```

3. Impostare descrizione e argomenti del repo: `lathe`, `els`, `esp32-s3`,
   `nextion`, `arduino`.
4. Attivare *Issues* (e *Discussions* se vuoi raccogliere idee).

## 5. Prima release

1. Aggiornare la versione in `firmware-it/h5/h5.ino` (`SOFTWARE_VERSION`) e
   ricompilare.
2. Creare il tag e caricare la release con i file pronti all'uso:

   ```sh
   git tag -a v0.1.0 -m "NanoEls H5 v0.1.0"
   git push origin v0.1.0
   ```

   Allegati consigliati: `h5-IT-<data>-v<versione>.bin`, `h5_it.tft`,
   `MANUALE_USO.md` (o PDF) e, se presenti, foto/video.
3. Nel testo della release: novità, istruzioni di aggiornamento (prima firmware,
   poi TFT) e avvertenza sulla sicurezza (motori, utensile, STOP).

## 6. Dopo la pubblicazione

- [ ] Aggiungere il badge della release al README, se utile.
- [ ] Tenere aggiornato lo stato dei test nella sezione *Stato del progetto*.
- [ ] Rispondere alle issue citando la versione (`H5V64`) mostrata dalla UI web.
- [ ] Le donazioni restano facoltative: nessuna funzione va messa a pagamento.
