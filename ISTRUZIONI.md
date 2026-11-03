# Istruzioni per la pubblicazione — NanoEls H5

Cartella: `C:\Users\Admin\Desktop\NanoEls-H5-pubblicazione`

Contiene una copia completa del progetto al **3 novembre 2026** (firmware
**H5V63**), già pronta come repository git con la sua cronologia: niente cartelle
di build, backup o screenshot di prova. **Non è stato pubblicato nulla online.**

File principali: [README.md](README.md) (presentazione), [LICENSE](LICENSE)
(MIT), [PUBBLICAZIONE.md](PUBBLICAZIONE.md) (checklist dettagliata),
[collaudo/](collaudo/) (procedure di collaudo sicurezza).

## A. Prima di pubblicare

1. **Completare i test sul tornio** elencati in PUBBLICAZIONE.md, sezione 3.
2. **Link "offrimi un caffè"**:
   - creare un account su buymeacoffee.com oppure ko-fi.com;
   - copiare il link del proprio profilo;
   - aprire [README.md](README.md), cercare la riga `_link donazioni in arrivo_`
     e sostituirla con `[Offrimi un caffè](IL_TUO_LINK)`;
   - salvare e fare un commit (comandi in sezione D).
3. **Firma**:
   - la licenza riporta `NanoEls H5 contributors`; se si vuole nome e cognome,
     modificare [LICENSE](LICENSE);
   - se si vuole che i commit risultino collegati al proprio account GitHub,
     comunicare l'email GitHub **prima** del primo push (dopo diventa più
     complicato correggerli).

Se nel frattempo il progetto cambia ancora, chiedere di riallineare questa
cartella prima di pubblicarla.

## B. Metodo semplice: GitHub Desktop

1. Installare **GitHub Desktop** (desktop.github.com) e accedere con il proprio
   account GitHub.
2. Menu **File → Add local repository**, scegliere
   `C:\Users\Admin\Desktop\NanoEls-H5-pubblicazione`.
3. In alto compare **Publish repository**: nome `nanoels-h5`, togliere la spunta
   **Keep this code private**, premere **Publish repository**.
4. Il repository è online; da quel momento le modifiche si pubblicano con
   **Commit to main** + **Push origin**.

## C. Metodo con i comandi (Git Bash)

1. Su github.com: **New repository**, nome `nanoels-h5`, visibilità **Public**,
   senza aggiungere README, licenza o .gitignore (sono già nel progetto).
2. Aprire Git Bash nella cartella e digitare:

   ```sh
   cd "/c/Users/Admin/Desktop/NanoEls-H5-pubblicazione"
   git remote add origin https://github.com/TUONOME/nanoels-h5.git
   git push -u origin main
   ```

3. Se viene chiesta la password, GitHub richiede un **token**: impostazioni
   account → *Developer settings* → *Personal access tokens* → *Fine-grained
   token* con permesso di lettura/scrittura sui contenuti del repository. Il token
   si incolla al posto della password.

## D. Aggiornare il progetto dopo la pubblicazione

Modificare i file nella cartella, poi:

```sh
cd "/c/Users/Admin/Desktop/NanoEls-H5-pubblicazione"
git add -A
git commit -m "Descrizione della modifica"
git push
```

Con GitHub Desktop: scrivere il messaggio, **Commit to main**, poi **Push origin**.

## E. Prima release (file pronti all'uso)

Dal sito GitHub: repository → **Releases** → **Draft a new release**.

- Tag: `v0.1.0` — titolo: `NanoEls H5 v0.1.0`.
- Allegare i file già presenti nella cartella:
  - `firmware-it/h5-IT-20261103-v63.bin`
  - `screen-it/h5_it.tft`
  - `screen-it/MANUALE_USO.md`
- Descrivere le novità e l'ordine di aggiornamento (**prima firmware, poi TFT**),
  poi **Publish release**.

## F. Regole da rispettare

- **Nessuna password personale** nel repository: la password WiFi dell'utente sta
  solo nella memoria del controller (NVS). `nanoels-h5` è la password pubblica
  dell'access point di setup, prevista dal firmware.
- Non aggiungere cartelle `build/`, backup o screenshot: sono già esclusi da
  `.gitignore`.
- Mantenere la nota di copyright originale di Maxim Kachurovskiy in
  [LICENSE](LICENSE).
- La UI web non ha login: va usata solo su rete locale (già scritto nel README).
- Le donazioni restano facoltative: nessuna funzione va messa a pagamento.
