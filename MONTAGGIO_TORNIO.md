# NanoEls H5 — Montaggio sul tornio

Checklist per passare dal banco alla macchina. Riferimenti: firmware **H5V65**,
[schema di cablaggio](cablaggio/schema_cablaggio.html) rev. 6,
[manuale d'uso](screen-it/MANUALE_USO.md), prove obbligatorie in
[PUBBLICAZIONE.md](PUBBLICAZIONE.md) §3.

Regola generale: **si sale di un gradino solo se il precedente è passato.**
Se un controllo non torna, fermarsi e correggere il cablaggio o il parametro;
non provare ad aggiustare in corsa.

---

## A. Prima di iniziare

- [ ] Tornio spento, spina staccata, mandrino libero e senza pezzo.
- [ ] Attrezzi: chiavi, cacciavite, tester, comparatore con base magnetica,
      calibro, metri di nastro per i cavi.
- [ ] Driver passo-passo con datasheet (corrente per fase, microstep).
- [ ] Alimentatore 5 V per la scheda e alimentatore motori (VMOT) separati o
      adeguati alla corrente totale.
- [ ] Fungo di emergenza che toglie alimentazione a driver e mandrino: lo STOP
      del pannello è una protezione software, **non** un dispositivo di
      sicurezza certificato.
- [ ] Foto dello stato attuale del tornio (per rimontare tutto com'era).

## B. Cablaggio e alimentazione

Pin di riferimento (dettaglio e serigrafie in schema rev. 6). **Piede 1 = +5V**
sul lato della scritta 5V.

| Collegamento | Piedi | Segnali |
|---|---|---|
| Driver Z | 1→4 | +5V · ABIL. (GPIO 41) · SENSO (42) · PASSO (35) |
| Driver X | 1→4 | +5V · ABIL. (GPIO 16) · SENSO (15) · PASSO (7) |
| Encoder mandrino | 1→4 | +5V · MASSA · B (14) · A (13) |
| Volantino Z (opz.) | 1→4 | +5V · MASSA · B (8) · A (18) |
| Volantino X (opz.) | 1→4 | +5V · MASSA · B (21) · A (47) |
| UART display | 1→4 | +5V · MASSA · RX (44) · TX (43) |
| Alim. 5V | 1→4 | +5V · +5V · MASSA · MASSA |

- [ ] Driver Z e X alimentati a **VMOT** dai morsetti del driver; la tensione
      motore **non** entra nei connettori della scheda.
- [ ] Ingressi PASSO/SENSO/ABIL. dei driver **optoisolati** (la scheda esce a 5 V).
- [ ] Microstep e corrente dei driver impostati *prima* di collegare i motori:
      corrente dal datasheet del motore, microstep coerente con il parametro
      **Passi motore per giro** (200 passi × microstep × eventuale riduzione).
- [ ] Masse comuni: alimentatore 5 V, driver e scheda su un unico punto di massa.
- [ ] Encoder mandrino montato **1:1** col mandrino (cinghia o giunto), cinghia
      tesa, ruota solidale e senza giochi; 1200 impulsi/giro di default.
- [ ] Volantini montati solo se si usano; altrimenti connettori liberi.
- [ ] Controller fissato lontano da trucioli e refrigerante, cavi in passacavi,
      schermatura o twist per encoder e segnali di passo.
- [ ] Fungo di emergenza installato e provato **a tornio spento** (continuità).
- [ ] Verifica col tester prima di dare tensione: nessun corto tra +5V e MASSA
      sui connettori, piede 1 giusto su ogni connettore.

## C. Configurazione nella UI web

Aprire `http://<IP del controller>/` (l'IP è DHCP: se non risponde, cercare il
MAC `7c:e8:b1:b0:93:5c` con `arp -a`). Salvare dopo ogni sezione.

Mandrino:

- [ ] **PPR encoder** = 1200 (o il valore reale dell'encoder montato).
- [ ] **Gioco encoder** = 0 (aumentare solo se l'angolo oscilla dopo un'inversione).

Asse Z (carro):

- [ ] **Passo vite madre**: passo reale della vite (per viti in pollici, 25,4 / TPI).
- [ ] **Passi motore per giro**: 200 × microstep × riduzione.
- [ ] **Corsa massima**: poco sopra la corsa fisica sicura del carro.
- [ ] **Velocità manuale**: partire bassi e salire dopo le prove.
- [ ] **Gioco**: misurato col comparatore, 0 se non misurabile.
- [ ] **Inverti direzione**: da attivare solo dopo la prova dei versi (§D).

Asse X (slitta trasversale):

- [ ] Stessi campi di Z, con il passo della vite trasversale.
- [ ] **Corsa massima** riferita alla slitta, non al diametro.

Altro:

- [ ] **Cono**: Diametro grande, Diametro piccolo (la corsa Z è il finecorsa MAX
      impostato nella pagina CONO).
- [ ] **Joystick**: lasciarlo disattivato se non collegato.
- [ ] **Backup configurazione**: in *Impostazioni*, dopo aver verificato i
      parametri, premere **Scarica backup** e conservare il file JSON. Serve per
      ripristinare la macchina dopo una modifica o per configurarne una seconda.
- [ ] Annotare i valori scelti qui sotto, servono per il collaudo.

| Parametro | Z | X |
|---|---|---|
| Passo vite (mm/giro) | | |
| Passi motore/giro | | |
| Corsa massima (mm) | | |
| Gioco (mm) | | |
| Inverti direzione | sì / no | sì / no |

## D. Prima accensione e verifiche a vuoto

Senza pezzo, con l'utensile lontano dal mandrino e la mano sul fungo.

1. [ ] Accensione: display su MENU, UI web raggiungibile, versione H5V65.
2. [ ] **ELS OFF**. Jog Z+ e Z− con tocchi brevi: verso corretto sullo schermo,
       distanza pari a STEP misurata col comparatore. Se il verso è sbagliato:
       spegnere, attivare **Inverti direzione** in UI web e riprovare.
3. [ ] Jog X+ e X− con lo stesso controllo.
4. [ ] 10 jog da 1 mm e ritorno: la quota torna a 0 (nessun passo perso).
5. [ ] Mandrino a mano: un giro → **GIRI** +1 e **ANGOLO** torna a ~0; **GIRI/MIN**
       plausibile. Se GIRI scende col verso di lavoro, spegnere e invertire A/B
       sul connettore encoder.
6. [ ] Finecorsa software: impostare **MAX** e **MIN** su Z e X (fascia nella card
       o pulsanti nella pagina LAVORAZIONE), lasciando margine dai fermi fisici.
7. [ ] Jog oltre il finecorsa: si ferma (solo beep), la quota non prosegue.
8. [ ] **STOP durante un jog**: compare `Spento in manuale`, serve spegnere e
       riaccendere. (Prova 2 del collaudo sicurezza.)
9. [ ] **STOP tenuto 3 s**: reset generale, finecorsa cancellati, passo 0,
       modalità INGRANAGGI. (Prova 3 del collaudo sicurezza.)
10. [ ] Riavviare: i parametri NVS sono conservati e il WiFi si riconnette.

## E. Prime prove con l'ELS acceso

A vuoto o con un pezzo di prova morbido, giri bassi, mano sul fungo.

1. [ ] **INGRANAGGI**, passo piccolo (es. 0,1 mm/giro): dieci giri a mano →
       il carro avanza di 1 mm misurato col comparatore (passo × giri).
2. [ ] **X-INGRANAGGI** con lo stesso criterio sulla trasversale.
3. [ ] **ASINCRONO**: parte senza mandrino; OFF lo ferma subito.
4. [ ] Raggiungimento del finecorsa software in movimento: si ferma senza
       oltrepassare il limite.
5. [ ] Cambio modalità a ELS acceso: l'ELS si spegne e il procedimento si azzera.
6. [ ] **Posizione fuori macchina**: forzare un comando oltre la corsa massima e
       verificare l'emergenza (prova controllata, a vuoto).

## F. Prove di lavorazione (obbligatorie prima della pubblicazione)

Elenco completo in [PUBBLICAZIONE.md](PUBBLICAZIONE.md) §3. Qui l'ordine consigliato.

- [ ] **Sincronizzazione Z/X** su pezzo di prova senza utensile: quota live
      coerente con i giri del mandrino.
- [ ] **TORNITURA**: cilindro in più passate, profondità decrescenti.
- [ ] **SPIANATURA**: sfacciatura, verso destro e sinistro.
- [ ] **TRONCATURA**: passo positivo (esterno) e negativo (interno).
- [ ] **CONO**: Morse 5 con le sue quote; il display deve mostrare `1 : 19`.
- [ ] **FILETTATURA**: DX e SX, più principi, filetto cilindrico e conico;
      controllo col contapassi o con la madrevite.
- [ ] **ELLISSE**, **SCANALATURA**, **ASSE Y** se l'asse è installato.
- [ ] **G-CODE**: programma caricato dalla UI web (anche da file `.gcode`),
      esecuzione, pausa con mandrino fermo.
- [ ] Valori live durante la lavorazione: GIRI/MIN, ANGOLO, posizioni, passata i di n.
- [ ] Emergenze: `Posizione fuori macchina` e `Spento in manuale` con la causa
      scritta su TFT e UI web.
- [ ] **21 pagine TFT**, tastierino numerico e tastiera PS/2 (se collegata).
- [ ] **OTA**: aggiornamento firmware e TFT dalla UI web (ELS OFF; display
      alimentato da POWER, non da USB). Dopo il TFT non togliere tensione per
      2–3 minuti.
- [ ] UI web da telefono: quote, finecorsa, WiFi, parametri assi.

## G. Se qualcosa non torna

| Sintomo | Controllo |
|---|---|
| Asse nel verso sbagliato | **Inverti direzione** in UI web (a ELS spento) |
| Passo doppio o metà | **Passi motore per giro** / **Passo vite madre** |
| Quota che deriva | gioco, slittamento motore, microstep o corrente driver |
| GIRI negativo o sbagliato | A/B encoder invertiti o PPR errata |
| `ESTOP - Posizione fuori macchina` | **Corsa massima** troppo stretta o finecorsa non impostati |
| Motore libero | pillola asse su OFF o **Inverti abilitazione** del driver |
| L'ELS non parte | finecorsa mancanti, PASSO 0, mandrino fermo in G-CODE |

Dopo la correzione, ripetere la prova dal gradino precedente.

## H. Chiusura

- [ ] Foto del controller montato e dell'encoder (servono al README).
- [ ] Aggiornare *Stato del progetto* nel [README](README.md) con le prove passate.
- [ ] Annotare qui i problemi trovati e le soluzioni.
- [ ] Riallineare il pacchetto di pubblicazione su Desktop se la documentazione cambia.
