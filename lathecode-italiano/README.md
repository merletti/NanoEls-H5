# lathecode — versione italiana

Editor web per descrivere pezzi torniti con il linguaggio **lathecode**, vederne
l'anteprima 2D/3D e generare **G-code** o **STL**. Questa è la traduzione italiana
dell'app originale di Maxim Kachurovskiy.

- `index.html`: applicazione pronta all'uso, già compilata in un unico file.
- `sorgenti/`: codice TypeScript completo per ricompilarla.

## Avvio rapido

Apri `index.html` con un browser recente (Chrome, Edge, Firefox). Non serve un
server: l'app è un singolo file HTML e funziona anche senza connessione.

Le funzioni basate su OpenRouter (prompt testuale, disegno tecnico, modifica
assistita) richiedono internet e una chiave API OpenRouter, che resta salvata solo
nella memoria locale del browser.

## Funzioni principali

- Campioni pronti: forme base, fori, coni, archi, spline, coni Morse, bulloni,
  alberi, pulegge e pezzi decorativi.
- Disegno del profilo dalle quote, con strumenti retta, convesso, concavo, spline
  e mano libera; smussi e raccordi modificabili.
- Importazione STL e conversione in lathecode.
- Anteprima 2D e 3D, sezione trasversale con quote.
- Pianificatore a pixel stabile o vettoriale sperimentale, con impostazioni
  avanzate.
- Generazione G-code per controller NanoEls H4/H5, copia, download STL, salvataggio
  locale e backup/ripristino delle impostazioni.
- Interfaccia interamente in italiano; restano in inglese solo parole chiave del
  linguaggio lathecode e del G-code, che devono essere interpretate così come sono.

## Struttura del pacchetto

```
lathecode-italiano-pubblicazione/
  index.html      app compilata, pronta da aprire
  README.md       questo file
  LICENSE         licenza MIT originale
  sorgenti/       progetto completo (TypeScript, Vite, test)
```

## Ricompilare dai sorgenti

Requisiti: Node.js 22 e npm.

```bash
cd sorgenti
npm ci
npm run build
```

La build produce `docs/index.html`. Per aggiornare la copia pronta, sostituisci
`index.html` nella cartella principale con quel file.

Test unitari:

```bash
npx vitest run src
```

I test in `test/` usano Puppeteer e richiedono Chrome installato; i test unitari
in `src/` non ne hanno bisogno.

## Licenza e attribuzione

Codice originale: [lathecode](https://github.com/kachurovskiy/lathecode) di Maxim
Kachurovskiy, licenza MIT (vedi `LICENSE`). Questa versione mantiene la stessa
licenza e aggiunge la traduzione italiana dell'interfaccia, dei messaggi e della
documentazione.

Le modifiche riguardano solo i testi visibili: struttura, algoritmo del
pianificatore, formato lathecode e output G-code restano quelli del progetto
originale.
