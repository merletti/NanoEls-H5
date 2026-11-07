# Istruzioni per la pubblicazione — NanoEls H5

Questa cartella contiene il progetto NanoEls H5 (firmware **H5V65**), pubblicato su
GitHub il **6 novembre 2026**:

<https://github.com/merletti/NanoEls-H5>

Il repository è pubblico, il branch di lavoro è `main` e il remote `origin` è già
configurato. In `gui/` sono versionati anche materiali di lavoro e schermate del
pannello; build e backup locali sono esclusi da `.gitignore`.

File principali: [README.md](README.md) (presentazione), [LICENSE](LICENSE)
(MIT), [PUBBLICAZIONE.md](PUBBLICAZIONE.md) (checklist dettagliata),
[collaudo/](collaudo/) (procedure di collaudo sicurezza).

## A. Prima di ogni aggiornamento pubblico

1. **Completare i test sul tornio** elencati in PUBBLICAZIONE.md, sezione 3.
2. **Link del progetto originale e donazioni**: il link al progetto originale è
   in [README.md](README.md), sezione *Progetto originale*
   ([kachurovskiy/nanoels — h5](https://github.com/kachurovskiy/nanoels/tree/main/h5));
   il link «offri un caffè» (PayPal) è nella sezione *Sostieni il progetto*.
   Per cambiarlo basta modificare quell'indirizzo e fare un commit.
3. **Licenza**: la licenza riporta `NanoEls H5 contributors`; se si vuole nome e
   cognome, modificare [LICENSE](LICENSE).

## B. Pubblicare una modifica (GitHub Desktop)

1. Aprire GitHub Desktop e scegliere il repository `NanoEls-H5` (se non c'è,
   **File → Add local repository** su questa cartella).
2. Scrivere il messaggio di commit, premere **Commit to main**, poi **Push origin**.

## C. Pubblicare una modifica (Git Bash)

Aprire Git Bash nella cartella e digitare:

```sh
git add -A
git commit -m "Descrizione della modifica"
git push
```

Se viene chiesta la password, GitHub richiede un **token**: impostazioni account →
*Developer settings* → *Personal access tokens* → *Fine-grained token* con permesso
di lettura/scrittura sui contenuti del repository. Il token si incolla al posto
della password. Se compare la finestra **Git Credential Manager**, non chiuderla:
completare l'accesso.

## D. Se il repository va ricreato da zero

Solo in caso di perdita del repository online:

1. Su github.com: **New repository**, nome `NanoEls-H5`, visibilità **Public**,
   senza aggiungere README, licenza o .gitignore (sono già nel progetto).
2. Aprire Git Bash nella cartella e digitare:

   ```sh
   git remote add origin https://github.com/merletti/NanoEls-H5.git
   git push -u origin main
   ```

3. Controllare che il branch remoto sia `main` e che i file siano tutti presenti.

## E. Prima release (file pronti all'uso)

Dal sito GitHub: repository → **Releases** → **Draft a new release**.

- Tag: `v0.1.0` — titolo: `NanoEls H5 v0.1.0`.
- Allegare i file già presenti nella cartella:
  - `firmware-it/h5-IT-20261105-v65.bin`
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
