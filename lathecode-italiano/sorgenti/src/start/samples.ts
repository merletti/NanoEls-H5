export type SampleDefinition = {
  id: string;
  title: string;
  description: string;
  text: string;
};

export type SampleSection = {
  id: string;
  title: string;
  description: string;
  samples: readonly SampleDefinition[];
};

type MorseTaperSize = 1 | 2 | 3 | 4 | 5 | 6 | 7;

type MorseTaperExtensionRow = {
  outerMt: MorseTaperSize;
  innerMt: MorseTaperSize;
  bodyDiameterMm: number;
  taperDiameterMm: number;
  taperLengthMm: number;
  bodyLengthMm: number;
};

const TAPER_ANGLE_TABLE = {
  morse: {
    MT0: {taperPerFootIn: 0.6246, angleFromCenterlineDeg: 1.4908, includedAngleDeg: 2.9816},
    MT1: {taperPerFootIn: 0.5986, angleFromCenterlineDeg: 1.4287, includedAngleDeg: 2.8574},
    MT2: {taperPerFootIn: 0.5994, angleFromCenterlineDeg: 1.4307, includedAngleDeg: 2.8614},
    MT3: {taperPerFootIn: 0.6024, angleFromCenterlineDeg: 1.4377, includedAngleDeg: 2.8754},
    MT4: {taperPerFootIn: 0.6233, angleFromCenterlineDeg: 1.4876, includedAngleDeg: 2.9752},
    MT4_5: {taperPerFootIn: 0.6240, angleFromCenterlineDeg: 1.4894, includedAngleDeg: 2.9788},
    MT5: {taperPerFootIn: 0.6315, angleFromCenterlineDeg: 1.5073, includedAngleDeg: 3.0146},
    MT6: {taperPerFootIn: 0.6257, angleFromCenterlineDeg: 1.4933, includedAngleDeg: 2.9866},
    MT7: {taperPerFootIn: 0.6240, angleFromCenterlineDeg: 1.4894, includedAngleDeg: 2.9788},
  },
  jarno: {
    allSizes: {taperPerFootIn: 0.6000, angleFromCenterlineDeg: 1.4321, includedAngleDeg: 2.8642},
  },
  brownSharpe: {
    mostSizes: {taperPerFootIn: 0.5000, angleFromCenterlineDeg: 1.1935, includedAngleDeg: 2.3870},
    number10: {taperPerFootIn: 0.5161, angleFromCenterlineDeg: 1.2320, includedAngleDeg: 2.4640},
  },
  jacobs: {
    JT0: {taperPerFootIn: 0.5915, angleFromCenterlineDeg: 1.4117, includedAngleDeg: 2.8234},
    JT1: {taperPerFootIn: 0.9251, angleFromCenterlineDeg: 2.2074, includedAngleDeg: 4.4148},
    JT2: {taperPerFootIn: 0.9786, angleFromCenterlineDeg: 2.3350, includedAngleDeg: 4.6700},
    JT3: {taperPerFootIn: 0.6390, angleFromCenterlineDeg: 1.5251, includedAngleDeg: 3.0502},
    JT4: {taperPerFootIn: 0.6289, angleFromCenterlineDeg: 1.5009, includedAngleDeg: 3.0018},
    JT5: {taperPerFootIn: 0.6201, angleFromCenterlineDeg: 1.4801, includedAngleDeg: 2.9602},
    JT6: {taperPerFootIn: 0.6229, angleFromCenterlineDeg: 1.4868, includedAngleDeg: 2.9736},
    JT33: {taperPerFootIn: 0.7619, angleFromCenterlineDeg: 1.8184, includedAngleDeg: 3.6368},
  },
  steep724: {
    ansiNmtbCatBt: {taperPerFootIn: 3.5000, angleFromCenterlineDeg: 8.2971, includedAngleDeg: 16.5943},
  },
  r8: {
    standard: {taperPerFootIn: 3.5547, angleFromCenterlineDeg: 8.4250, includedAngleDeg: 16.8500},
  },
  spindleNose: {
    shortA1A2B1B2D1: {taperPerFootIn: 3.0000, angleFromCenterlineDeg: 7.1250, includedAngleDeg: 14.2500},
    longL: {taperPerFootIn: 3.5000, angleFromCenterlineDeg: 8.2972, includedAngleDeg: 16.5944},
  },
} as const;

const MORSE_TAPER_ANGLE_DEGREES: Record<MorseTaperSize, number> = {
  1: TAPER_ANGLE_TABLE.morse.MT1.angleFromCenterlineDeg,
  2: TAPER_ANGLE_TABLE.morse.MT2.angleFromCenterlineDeg,
  3: TAPER_ANGLE_TABLE.morse.MT3.angleFromCenterlineDeg,
  4: TAPER_ANGLE_TABLE.morse.MT4.angleFromCenterlineDeg,
  5: TAPER_ANGLE_TABLE.morse.MT5.angleFromCenterlineDeg,
  6: TAPER_ANGLE_TABLE.morse.MT6.angleFromCenterlineDeg,
  7: TAPER_ANGLE_TABLE.morse.MT7.angleFromCenterlineDeg,
};

const MORSE_TAPER_LARGE_DIAMETERS_MM: Record<MorseTaperSize, number> = {
  1: 12.065,
  2: 17.78,
  3: 23.825,
  4: 31.267,
  5: 44.399,
  6: 63.348,
  7: 83.058,
};

const MORSE_EXTENSION_THROUGH_BORE_DIAMETER_MM = 8.4;

const MORSE_TAPER_EXTENSION_ROWS: readonly MorseTaperExtensionRow[] = [
  {outerMt: 1, innerMt: 1, bodyDiameterMm: 20, taperDiameterMm: 12.065, taperLengthMm: 62, bodyLengthMm: 83},
  {outerMt: 1, innerMt: 2, bodyDiameterMm: 30, taperDiameterMm: 12.065, taperLengthMm: 62, bodyLengthMm: 98},
  {outerMt: 2, innerMt: 1, bodyDiameterMm: 20, taperDiameterMm: 17.78, taperLengthMm: 75, bodyLengthMm: 85},
  {outerMt: 2, innerMt: 2, bodyDiameterMm: 30, taperDiameterMm: 17.78, taperLengthMm: 75, bodyLengthMm: 100},
  {outerMt: 2, innerMt: 3, bodyDiameterMm: 36, taperDiameterMm: 17.78, taperLengthMm: 75, bodyLengthMm: 121},
  {outerMt: 2, innerMt: 4, bodyDiameterMm: 48, taperDiameterMm: 17.78, taperLengthMm: 75, bodyLengthMm: 140},
  {outerMt: 3, innerMt: 1, bodyDiameterMm: 20, taperDiameterMm: 23.825, taperLengthMm: 94, bodyLengthMm: 79},
  {outerMt: 3, innerMt: 2, bodyDiameterMm: 30, taperDiameterMm: 23.825, taperLengthMm: 94, bodyLengthMm: 100},
  {outerMt: 3, innerMt: 3, bodyDiameterMm: 36, taperDiameterMm: 23.825, taperLengthMm: 94, bodyLengthMm: 121},
  {outerMt: 3, innerMt: 4, bodyDiameterMm: 48, taperDiameterMm: 23.825, taperLengthMm: 94, bodyLengthMm: 146},
  {outerMt: 3, innerMt: 5, bodyDiameterMm: 63, taperDiameterMm: 23.825, taperLengthMm: 94, bodyLengthMm: 174},
  {outerMt: 4, innerMt: 1, bodyDiameterMm: 20, taperDiameterMm: 31.267, taperLengthMm: 117.5, bodyLengthMm: 82.5},
  {outerMt: 4, innerMt: 2, bodyDiameterMm: 30, taperDiameterMm: 31.267, taperLengthMm: 117.5, bodyLengthMm: 97.5},
  {outerMt: 4, innerMt: 3, bodyDiameterMm: 36, taperDiameterMm: 31.267, taperLengthMm: 117.5, bodyLengthMm: 122.5},
  {outerMt: 4, innerMt: 4, bodyDiameterMm: 48, taperDiameterMm: 31.267, taperLengthMm: 117.5, bodyLengthMm: 147.5},
  {outerMt: 4, innerMt: 5, bodyDiameterMm: 63, taperDiameterMm: 31.267, taperLengthMm: 117.5, bodyLengthMm: 182.5},
  {outerMt: 5, innerMt: 1, bodyDiameterMm: 20, taperDiameterMm: 44.399, taperLengthMm: 149.5, bodyLengthMm: 82.5},
  {outerMt: 5, innerMt: 2, bodyDiameterMm: 30, taperDiameterMm: 44.399, taperLengthMm: 149.5, bodyLengthMm: 97.5},
  {outerMt: 5, innerMt: 3, bodyDiameterMm: 36, taperDiameterMm: 44.399, taperLengthMm: 149.5, bodyLengthMm: 118.5},
  {outerMt: 5, innerMt: 4, bodyDiameterMm: 48, taperDiameterMm: 44.399, taperLengthMm: 149.5, bodyLengthMm: 150.5},
  {outerMt: 5, innerMt: 5, bodyDiameterMm: 63, taperDiameterMm: 44.399, taperLengthMm: 149.5, bodyLengthMm: 185.5},
  {outerMt: 5, innerMt: 6, bodyDiameterMm: 83, taperDiameterMm: 44.399, taperLengthMm: 149.5, bodyLengthMm: 247.5},
  {outerMt: 6, innerMt: 2, bodyDiameterMm: 30, taperDiameterMm: 63.348, taperLengthMm: 210, bodyLengthMm: 99},
  {outerMt: 6, innerMt: 3, bodyDiameterMm: 36, taperDiameterMm: 63.348, taperLengthMm: 210, bodyLengthMm: 120},
  {outerMt: 6, innerMt: 4, bodyDiameterMm: 48, taperDiameterMm: 63.348, taperLengthMm: 210, bodyLengthMm: 145},
  {outerMt: 6, innerMt: 5, bodyDiameterMm: 61, taperDiameterMm: 63.348, taperLengthMm: 210, bodyLengthMm: 180},
  {outerMt: 6, innerMt: 6, bodyDiameterMm: 83, taperDiameterMm: 63.348, taperLengthMm: 210, bodyLengthMm: 242},
  {outerMt: 6, innerMt: 7, bodyDiameterMm: 105, taperDiameterMm: 63.348, taperLengthMm: 210, bodyLengthMm: 328},
];

function createMorseTaperExtensionSample(row: MorseTaperExtensionRow): SampleDefinition {
  const title = `Estensione MT${row.outerMt} verso MT${row.innerMt}`;
  const maxDiameter = Math.max(row.bodyDiameterMm, row.taperDiameterMm);
  const stockDiameter = Math.ceil(maxDiameter + 4);
  const cutDepth = maxDiameter >= 80 ? 1 : maxDiameter >= 50 ? 0.75 : 0.5;
  const bodyOnChuckSide = row.bodyDiameterMm >= row.taperDiameterMm;
  const socketReliefLength = Math.min(8, Math.max(4, row.bodyLengthMm * 0.06));
  const socketLength = row.bodyLengthMm - socketReliefLength;
  const innerLargeDiameter = MORSE_TAPER_LARGE_DIAMETERS_MM[row.innerMt];
  const outsideProfile = bodyOnChuckSide
    ? [
      `L${formatSampleNumber(row.taperLengthMm)} DE${formatSampleNumber(row.taperDiameterMm)} A${formatSampleTaperAngle(getMorseTaperAngle(row.outerMt))}`,
      `L${formatSampleNumber(row.bodyLengthMm)} D${formatSampleNumber(row.bodyDiameterMm)}`,
    ]
    : [
      `L${formatSampleNumber(row.bodyLengthMm)} D${formatSampleNumber(row.bodyDiameterMm)}`,
      `L${formatSampleNumber(row.taperLengthMm)} DE${formatSampleNumber(row.taperDiameterMm)} A${formatSampleTaperAngle(getMorseTaperAngle(row.outerMt))}`,
    ];
  const insideProfile = bodyOnChuckSide
    ? [
      `L${formatSampleNumber(row.taperLengthMm)} D${formatSampleNumber(MORSE_EXTENSION_THROUGH_BORE_DIAMETER_MM)}`,
      `L${formatSampleNumber(socketReliefLength)} D${formatSampleNumber(MORSE_EXTENSION_THROUGH_BORE_DIAMETER_MM)}`,
      `L${formatSampleNumber(socketLength)} DE${formatSampleNumber(innerLargeDiameter)} A${formatSampleTaperAngle(getMorseTaperAngle(row.innerMt))}`,
    ]
    : [
      `L${formatSampleNumber(socketLength)} DS${formatSampleNumber(innerLargeDiameter)} A${formatSampleTaperAngle(-getMorseTaperAngle(row.innerMt))}`,
      `L${formatSampleNumber(socketReliefLength)} D${formatSampleNumber(MORSE_EXTENSION_THROUGH_BORE_DIAMETER_MM)}`,
      `L${formatSampleNumber(row.taperLengthMm)} D${formatSampleNumber(MORSE_EXTENSION_THROUGH_BORE_DIAMETER_MM)}`,
    ];

  return {
    id: `mt${row.outerMt}-to-mt${row.innerMt}-extension`,
    title,
    description: `Prolunga Morse con esterno MT${row.outerMt}, interno MT${row.innerMt}, tabella D${formatSampleNumber(row.bodyDiameterMm)}, D1 ${formatSampleNumber(row.taperDiameterMm)}, L ${formatSampleNumber(row.taperLengthMm)} e L1 ${formatSampleNumber(row.bodyLengthMm)}.`,
    text: `; ${title}

STOCK D${formatSampleNumber(stockDiameter)} ID8
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT${formatSampleNumber(cutDepth)} FINISH0.1
FEED MOVE190 PASS38 PART9

${outsideProfile.join('\n')}

INSIDE
${insideProfile.join('\n')}`,
  };
}

function getMorseTaperAngle(size: MorseTaperSize): number {
  return MORSE_TAPER_ANGLE_DEGREES[size];
}

function formatSampleNumber(value: number): string {
  const rounded = Math.round(value * 1000) / 1000;
  if (Number.isInteger(rounded)) return rounded.toFixed(0);
  return rounded.toFixed(3).replace(/0+$/, '').replace(/\.$/, '');
}

function formatSampleTaperAngle(value: number): string {
  return value.toFixed(4);
}

export const SAMPLE_SECTIONS: readonly SampleSection[] = [
  {
    id: 'start-here-tiny-wins',
    title: 'Inizia qui: piccoli successi',
    description: 'Piccoli pezzi iniziali che mostrano le forme base di lathecode senza dover prima decidere il setup.',
    samples: [
      {
        id: 'hello-cylinder',
        title: 'Cilindro di prova',
        description: 'Il pezzo più piccolo e utile: un cilindro smussato pulito con materiale, utensile, profondità e avanzamento prudenti.',
        text: `; Cilindro di prova

STOCK D16
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.5 FINISH0.1
FEED MOVE200 PASS45 PART10
MODE TURN

L24 D12 CH0.5`,
      },
      {
        id: 'two-step-shoulder',
        title: 'Spallamento a due gradini',
        description: 'Un primo pezzo a spallamento con naso sottile, fascia di appoggio raccordata e corpo più largo lato mandrino.',
        text: `; Spallamento a due gradini

STOCK D22
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.55 FINISH0.1
FEED MOVE200 PASS45 PART10
MODE TURN

L13 DS12 CH0.4 DE12 FI0.5
L2 D10 FI0.5
L7 D18 FI0.5
L4 D20 CH0.5`,
      },
      {
        id: 'taper',
        title: 'Perno conico',
        description: 'Un semplice profilo a cono/tronco con estremità piccola e robusto spallamento lato mandrino.',
        text: `; Perno conico

STOCK D24
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.6 FINISH0.1
FEED MOVE190 PASS42 PART10
MODE TURN

L3 DS7 CH0.5 DE7 CH0
L18 DS7 DE18
L6 D22 CH0.5`,
      },
      {
        id: 'ball-on-a-stick',
        title: 'Sfera su stelo',
        description: 'Perla rotonda più piccola su uno stelo sottile e lungo, con una base modesta lato mandrino per il supporto.',
        text: `; Sfera su stelo

STOCK D20
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9
MODE TURN

L1.5 D5
L4.5 DS5 DE14 CONV
L4.5 DS14 DE5 CONV
L12 DS5 CH0 DE5 CH3
L3 D15
L1.5 D17 CH0.5`,
      },
      {
        id: 'three-part-batch',
        title: 'Lotto di tre pezzi',
        description: 'Tre piccoli distanziali pieni in un solo setup, con spazi di troncatura e massa crescente verso il mandrino.',
        text: `; Lotto di tre pezzi

STOCK D22
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.45 FINISH0.1
FEED MOVE220 PASS50 PART12

L2 D12
L4 D14
L1.5
L2 D10
L5 D16
L1.5
L2 D12
L7 D18
L3 D20`,
      },
    ],
  },
  {
    id: 'spline-profiles',
    title: 'Profili spline',
    description: 'Profili B-spline morbidi per manici, tappi, pomelli, piedini e abbozzi di ugelli utili, dove gli archi circolari sarebbero troppo rigidi.',
    samples: [
      {
        id: 'b-spline-sampler',
        title: 'Campioni B-spline',
        description: 'Una forma di riferimento compatta controllata da valori guida dei diametri interni invece che da archi circolari.',
        text: `; Campioni B-spline

STOCK D32
TOOL ROUND R3
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9
MODE TURN

L3 D10
L24 DS10 DE22 BSPLINE D14 D26 D18 D28
L4 D28 CH0.5`,
      },
      {
        id: 'ergonomic-file-handle',
        title: 'Manico ergonomico per lima',
        description: 'Abbozzo di manico morbido con codolo stretto, rigonfiamento per il palmo e spallamento più largo lato mandrino.',
        text: `; Manico ergonomico per lima

STOCK D36
TOOL ROUND R3
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9
MODE TURN

L5 D12
L26 DS12 DE28 BSPLINE D18 D32 D24 D30
L5 D34 CH0.5`,
      },
      {
        id: 'bottle-stopper-spline',
        title: 'Tappo bottiglia a spline',
        description: 'Abbozzo di tappo utile con cono dolce di innesto e presa arrotondata liscia.',
        text: `; Tappo bottiglia a spline

STOCK D34
TOOL ROUND R2.5
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9
MODE TURN

L8 DS12 DE20 BSPLINE D13 D16 D18 D20
L10 DS20 DE30 BSPLINE D26 D32 D28
L4 D32 CH0.5`,
      },
      {
        id: 'soft-bumper-button-spline',
        title: 'Tampone morbido',
        description: 'Forma a cupola per tampone o piedino con piccolo collo di centraggio e ampia faccia di contatto arrotondata.',
        text: `; Tampone morbido

STOCK D32
TOOL ROUND R2.5
DEPTH CUT0.4 FINISH0.1
FEED MOVE180 PASS36 PART9
MODE TURN

L2 D8
L14 DS8 DE24 BSPLINE D16 D30 D22
L5 D28 CH0.5`,
      },
      {
        id: 'hantel-dumbbell-spline',
        title: 'Profilo manubrio',
        description: 'Pezzo tornito lungo simile a un manubrio con due masse terminali arrotondate, lunga presa a vita e pomello più pesante lato mandrino.',
        text: `; Profilo manubrio

STOCK D40
TOOL ROUND R3
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9
MODE TURN

L5 DS30 CH0.4 DE30 CH0
L10 DS30 DE16 BSPLINE D34 D28 D20
L18 DS16 DE18 BSPLINE D13 D12 D20 D14
L10 DS18 DE34 BSPLINE D22 D30 D36
L5 D36 CH0.5`,
      },
      {
        id: 'cucumber-spline',
        title: 'Cetriolo a spline',
        description: 'Cilindro lungo leggermente irregolare con estremità arrotondate, piccole variazioni organiche di diametro e calotta supportata lato mandrino.',
        text: `; Cetriolo a spline

STOCK D32
TOOL ROUND R2.5
DEPTH CUT0.4 FINISH0.1
FEED MOVE180 PASS36 PART9
MODE TURN

L5 DS8 DE22 BSPLINE D12 D18 D24
L20 DS22 DE25 BSPLINE D27 D23 D26 D24
L20 DS25 DE23 BSPLINE D22 D28 D24 D27
L8 DS23 DE28 BSPLINE D25 D30 D27
L4 D30 CH0.4`,
      },
      {
        id: 'pear-spline',
        title: 'Pera a spline',
        description: 'Sagoma lunga a forma di pera con collo piccolo, pancia inferiore ampia e piedino corto lato mandrino.',
        text: `; Pera a spline

STOCK D42
TOOL ROUND R3
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9
MODE TURN

L3 D8
L10 DS8 DE18 BSPLINE D9 D12 D16
L18 DS18 DE36 BSPLINE D24 D38 D40 D34
L8 DS36 DE30 BSPLINE D40 D34 D30
L5 D36 CH0.5`,
      },
      {
        id: 'torus-donut-ring-spline',
        title: 'Anello a ciambella',
        description: 'Anello corto forato con profilo esterno arrotondato a ciambella e foro passante dritto.',
        text: `; Anello a ciambella

STOCK D36 ID10
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L2 D20
L10 DS20 DE20 BSPLINE D28 D34 D28
L2 D22

INSIDE
L14 D12`,
      },
      {
        id: 'spline-nozzle-blank',
        title: 'Abbozzo ugello a spline',
        description: 'Campana esterna e passaggio interno sagomati con spline per un abbozzo compatto stile ugello.',
        text: `; Abbozzo ugello a spline

STOCK D34 ID8
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L4 D16
L18 DS16 DE28 BSPLINE D18 D24 D30 D26
L8 D30

INSIDE
L6 D12
L20 DS12 DE20 BSPLINE D14 D18 D22 D18
L4 D20`,
      },
      {
        id: 'bellmouth-bushing-spline',
        title: 'Boccola a imboccatura svasata',
        description: 'Boccola forata con imboccatura svasata liscia e flangia più spessa lato mandrino.',
        text: `; Boccola a imboccatura svasata

STOCK D36 ID10
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L6 D22
L18 DS22 DE30 BSPLINE D24 D34 D28 D32
L6 D34

INSIDE
L8 D20
L12 DS20 DE12 BSPLINE D18 D14 D12
L10 D12`,
      },
    ],
  },


  {
    id: 'curvy-showpieces',
    title: 'Pezzi decorativi curvi',
    description: 'Forme decorative a simmetria assiale per provare archi convessi, vitini concavi, dettagli a perle e gola e profili cavi da vetrina.',
    samples: [
      {
        id: 'classic-chess-pawn',
        title: 'Pedone classico',
        description: 'Elegante sagoma di pedone con testa a sfera piccola, collo sottile, collarino e piedino modesto lato mandrino.',
        text: `; Pedone classico

STOCK D28
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L1.5 D7
L4.5 DS7 DE16 CONV
L3.5 DS16 DE8 CONV
L5 D7
L2 D12
L2 D17
L4 DS17 DE24 CONV
L3 D24
L1.5 D26`,
      },
      {
        id: 'bishop-ish-finial',
        title: 'Pinnacolo tipo alfiere',
        description: 'Sagoma da scacchi con elementi curvi sovrapposti, volutamente senza intaglio fuori asse.',
        text: `; Pinnacolo tipo alfiere

STOCK D34
TOOL ROUND R1.5
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L2 D6
L4 DS6 DE18 CONV
L5 DS18 DE12 CONV
L5 DS12 DE24 CONV
L4 DS24 DE16 CONC
L4 D28
L3 D32`,
      },
      {
        id: 'hourglass-standoff',
        title: 'Distanziale a clessidra',
        description: 'Due collarini collegati da una vita concava per un corpo distanziale decorativo.',
        text: `; Distanziale a clessidra

STOCK D30
TOOL ROUND R1.5
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L4 D22
L5 DS22 DE12 CONC
L5 DS12 DE24 CONC
L4 D24
L3 D28`,
      },
      {
        id: 'onion-dome',
        title: 'Cupola a cipolla',
        description: 'Curve convesse sovrapposte che salgono da una punta piccola fino a una base più ampia a cupola di cipolla.',
        text: `; Cupola a cipolla

STOCK D34
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L2 D5
L4 DS5 DE14 CONV
L5 DS14 DE24 CONV
L5 DS24 DE18 CONV
L5 DS18 DE30 CONV
L3 D32`,
      },
      {
        id: 'goblet-profile',
        title: 'Profilo calice',
        description: 'Coppa cava, stelo sottile e piede, senza manici né dettagli fuori asse.',
        text: `; Profilo calice

STOCK D34 ID10
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L3 D22
L5 DS22 DE28 CONV
L5 DS28 DE16 CONV
L6 D12
L4 D20
L5 D32

INSIDE
L5 D20
L5 DS20 DE14
L13 D10`,
      },
      {
        id: 'mini-vase',
        title: 'Vasetto',
        description: 'Esterno cavo panciuto con bocca stretta e cavità interna a gradini.',
        text: `; Vasetto

STOCK D34 ID10
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L3 D16
L5 DS16 DE24 CONV
L6 DS24 DE30 CONV
L5 DS30 DE18 CONV
L5 D28
L3 D32

INSIDE
L4 D14
L6 DS14 DE18
L7 D14
L10 D10`,
      },
      {
        id: 'bead-stack',
        title: 'Serie di perle',
        description: 'Campione tornito decorativo a perle e gola con più perle arrotondate prima della base.',
        text: `; Serie di perle

STOCK D30
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.4 FINISH0.1
FEED MOVE180 PASS36 PART9

L2 D8
L3 DS8 DE18 CONV
L3 DS18 DE10 CONV
L3 DS10 DE20 CONV
L3 DS20 DE12 CONV
L3 DS12 DE22 CONV
L3 DS22 DE14 CONV
L5 D28`,
      },
      {
        id: 'spool-bobbin',
        title: 'Rocchetto',
        description: 'Due flange con valle concava per l\'avvolgimento in mezzo.',
        text: `; Rocchetto

STOCK D30
TOOL ROUND R1.5
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L4 D26
L4 DS26 DE14 CONC
L8 D14
L4 DS14 DE28 CONC
L4 D28
L2 D28`,
      },
      {
        id: 'trophy-without-handles',
        title: 'Trofeo senza manici',
        description: 'Coppa cava, stelo, base e bordo rilevato senza alcuna geometria a manici non da tornio.',
        text: `; Trofeo senza manici

STOCK D36 ID10
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L3 D24
L5 DS24 DE30 CONV
L5 DS30 DE18 CONV
L5 D14
L4 D18
L5 D32
L3 D34

INSIDE
L5 D22
L5 DS22 DE16
L8 D12
L12 D10`,
      },
    ],
  },
  {
    id: 'toys-desk-trinkets-funny-shapes',
    title: 'Giochi, ninnoli da scrivania e forme divertenti',
    description: 'Sagome giocose a simmetria assiale che mostrano comunque movimenti lathecode pratici: coni, perle, gole, cupole, anelli e forme arrotondate sovrapposte.',
    samples: [
      {
        id: 'spinning-top',
        title: 'Trottola',
        description: 'Punta appuntita, stelo sottile e corpo grosso con la massa maggiore verso il mandrino.',
        text: `; Trottola

STOCK D32
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L2 D4
L5 DS4 DE10
L5 D8
L6 DS8 DE28 CONV
L4 D30
L2 D30`,
      },
      {
        id: 'ufo-saucer',
        title: 'Disco volante',
        description: 'Bordo piatto con cupola sopra e sotto, espresso come tornitura simmetrica a forma di disco.',
        text: `; Disco volante

STOCK D34
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L3 D10
L4 DS10 DE24 CONV
L3 D30
L4 DS30 DE18 CONV
L4 D28
L3 D32`,
      },
      {
        id: 'tiny-rocket',
        title: 'Razzo piccolo',
        description: 'Naso a cono, corpo cilindrico, coda a ugello e spallamento di lancio lato mandrino.',
        text: `; Razzo piccolo

STOCK D28
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.5 FINISH0.1
FEED MOVE190 PASS40 PART10

L5 DS4 DE16
L9 D16
L3 D12
L4 D22
L2 D24`,
      },
      {
        id: 'snowman-totem',
        title: 'Totem pupazzo di neve',
        description: 'Tre forme arrotondate sovrapposte con un cappellino, crescenti verso la base lato mandrino.',
        text: `; Totem pupazzo di neve

STOCK D34
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L3 DS6 DE14 CONV
L3 DS14 DE8 CONV
L4 DS8 DE22 CONV
L4 DS22 DE12 CONV
L5 DS12 DE28 CONV
L5 DS28 DE18 CONV
L3 D30`,
      },
      {
        id: 'mushroom',
        title: 'Fungo',
        description: 'Stelo corto che porta a un cappello arrotondato, con il cappello verso il mandrino.',
        text: `; Fungo

STOCK D32
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L5 D10
L4 DS10 DE24 CONV
L4 DS24 DE30 CONV
L4 DS30 DE18 CONV
L3 D30`,
      },
      {
        id: 'acorn',
        title: 'Ghianda',
        description: 'Punta piccola, corpo a dado arrotondato e piccola fascia a calotta vicino al lato mandrino.',
        text: `; Ghianda

STOCK D30
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L2 D5
L5 DS5 DE20 CONV
L5 DS20 DE16 CONV
L4 D22
L3 D28
L2 D28`,
      },
      {
        id: 'lighthouse',
        title: 'Faro',
        description: 'Torre conica, fasce ad anello e lanterna a cupola su una base ampia.',
        text: `; Faro

STOCK D34
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L3 D8
L4 DS8 DE14 CONV
L10 DS14 DE22
L1.5 D26
L5 D22
L1.5 D28
L4 D32`,
      },
      {
        id: 'honey-dipper',
        title: 'Mestolo per miele',
        description: 'Manico più gole ad anello ripetute per una testa compatta a coste.',
        text: `; Mestolo per miele

STOCK D26
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.4 FINISH0.1
FEED MOVE210 PASS45 PART11

L10 D8
L1.5 D18
L1.5 D12
L1.5 D20
L1.5 D12
L1.5 D22
L1.5 D12
L5 D24`,
      },
      {
        id: 'saturn-bead',
        title: 'Perla Saturno',
        description: 'Perla arrotondata con anello equatoriale sporgente, mantenuta a simmetria assiale per l\'anteprima al tornio.',
        text: `; Perla Saturno

STOCK D34
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L3 D8
L5 DS8 DE24 CONV
L2 D32
L5 DS24 DE10 CONV
L4 D28
L2 D32`,
      },
      {
        id: 'cartoon-bomb',
        title: 'Bomba da fumetto',
        description: 'Corpo sferico con breve stelo tipo miccia, senza alcuna geometria della miccia fuori asse.',
        text: `; Bomba da fumetto

STOCK D34
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L4 D6
L6 DS6 DE28 CONV
L6 DS28 DE14 CONV
L4 D30
L2 D32`,
      },
      {
        id: 'tiny-traffic-cone',
        title: 'Cono stradale piccolo',
        description: 'Cono e base sovrapposti, con punta piccola e piede largo lato mandrino.',
        text: `; Cono stradale piccolo

STOCK D30
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.5 FINISH0.1
FEED MOVE190 PASS40 PART10

L2 D4
L12 DS4 DE20
L3 D22
L4 D28
L2 D28`,
      },
      {
        id: 'rubber-duck-silhouette-lathe-edition',
        title: 'Papera in gomma, edizione tornio',
        description: 'Corpo e testa arrotondati interpretati come un totem sovrapposto realizzabile al tornio.',
        text: `; Papera in gomma, edizione tornio

STOCK D34
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L3 D8
L4 DS8 DE18 CONV
L4 DS18 DE12 CONV
L3 D14
L6 DS14 DE28 CONV
L5 DS28 DE20 CONV
L3 D32`,
      },
    ],
  },


  {
    id: 'morse-taper-arbor-adapters',
    title: 'Boccole adattatrici cono Morse',
    description: 'Boccole riduttrici per punte che corrispondono al set di adattatori da MT1-MT2 a MT4-MT5, usando le dimensioni da tabella per lunghezza totale, diametro esterno e diametro interno del cono.',
    samples: [
      {
        id: 'mt1-mt2-adapter-sleeve',
        title: 'Boccola adattatrice MT1-MT2',
        description: 'Boccola riduttrice per punte con esterno misura MT2, foro misura MT1, L92, D17.78, d12.065.',
        text: `; Boccola adattatrice MT1-MT2

STOCK D22 ID5
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L8 D13.64
L84 DE17.78 A${formatSampleTaperAngle(getMorseTaperAngle(2))}

INSIDE
L8 D9.765
L84 DE12.065 A${formatSampleTaperAngle(getMorseTaperAngle(1))}`,
      },
      {
        id: 'mt1-mt3-adapter-sleeve',
        title: 'Boccola adattatrice MT1-MT3',
        description: 'Boccola riduttrice per punte con esterno misura MT3, foro misura MT1, L99, D23.825, d12.065.',
        text: `; Boccola adattatrice MT1-MT3

STOCK D28 ID5
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L8 D19.37
L91 DE23.825 A${formatSampleTaperAngle(getMorseTaperAngle(3))}

INSIDE
L8 D9.59
L91 DE12.065 A${formatSampleTaperAngle(getMorseTaperAngle(1))}`,
      },
      {
        id: 'mt1-mt4-adapter-sleeve',
        title: 'Boccola adattatrice MT1-MT4',
        description: 'Boccola riduttrice per punte con esterno misura MT4, foro misura MT1, L124, D31.267, d12.065.',
        text: `; Boccola adattatrice MT1-MT4

STOCK D36 ID5
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L10 D25.687
L114 DE31.267 A${formatSampleTaperAngle(getMorseTaperAngle(4))}

INSIDE
L10 D8.965
L114 DE12.065 A${formatSampleTaperAngle(getMorseTaperAngle(1))}`,
      },
      {
        id: 'mt2-mt3-adapter-sleeve',
        title: 'Boccola adattatrice MT2-MT3',
        description: 'Boccola riduttrice per punte con esterno misura MT3, foro misura MT2, L112, D23.825, d17.78.',
        text: `; Boccola adattatrice MT2-MT3

STOCK D28 ID5
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L9 D18.785
L103 DE23.825 A${formatSampleTaperAngle(getMorseTaperAngle(3))}

INSIDE
L9 D14.98
L103 DE17.78 A${formatSampleTaperAngle(getMorseTaperAngle(2))}`,
      },
      {
        id: 'mt2-mt4-adapter-sleeve',
        title: 'Boccola adattatrice MT2-MT4',
        description: 'Boccola riduttrice per punte con esterno misura MT4, foro misura MT2, L124, D31.267, d17.78.',
        text: `; Boccola adattatrice MT2-MT4

STOCK D36 ID5
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L10 D25.687
L114 DE31.267 A${formatSampleTaperAngle(getMorseTaperAngle(4))}

INSIDE
L10 D14.68
L114 DE17.78 A${formatSampleTaperAngle(getMorseTaperAngle(2))}`,
      },
      {
        id: 'mt2-mt5-adapter-sleeve',
        title: 'Boccola adattatrice MT2-MT5',
        description: 'Boccola riduttrice per punte con esterno misura MT5, foro misura MT2, L156, D44.399, d17.78.',
        text: `; Boccola adattatrice MT2-MT5

STOCK D50 ID5
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.6 FINISH0.1
FEED MOVE190 PASS38 PART9

L12 D37.379
L144 DE44.399 A${formatSampleTaperAngle(getMorseTaperAngle(5))}

INSIDE
L12 D13.88
L144 DE17.78 A${formatSampleTaperAngle(getMorseTaperAngle(2))}`,
      },
      {
        id: 'mt3-mt4-adapter-sleeve',
        title: 'Boccola adattatrice MT3-MT4',
        description: 'Boccola riduttrice per punte con esterno misura MT4, foro misura MT3, L140, D31.267, d23.825.',
        text: `; Boccola adattatrice MT3-MT4

STOCK D36 ID5
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L11 D24.967
L129 DE31.267 A${formatSampleTaperAngle(getMorseTaperAngle(4))}

INSIDE
L11 D20.325
L129 DE23.825 A${formatSampleTaperAngle(getMorseTaperAngle(3))}`,
      },
      {
        id: 'mt3-mt5-adapter-sleeve',
        title: 'Boccola adattatrice MT3-MT5',
        description: 'Boccola riduttrice per punte con esterno misura MT5, foro misura MT3, L156, D44.399, d23.825.',
        text: `; Boccola adattatrice MT3-MT5

STOCK D50 ID5
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.6 FINISH0.1
FEED MOVE190 PASS38 PART9

L12 D37.379
L144 DE44.399 A${formatSampleTaperAngle(getMorseTaperAngle(5))}

INSIDE
L12 D19.925
L144 DE23.825 A${formatSampleTaperAngle(getMorseTaperAngle(3))}`,
      },
      {
        id: 'mt4-mt5-adapter-sleeve',
        title: 'Boccola adattatrice MT4-MT5',
        description: 'Boccola riduttrice per punte con esterno misura MT5, foro misura MT4, L171, D44.399, d31.267.',
        text: `; Boccola adattatrice MT4-MT5

STOCK D50 ID5
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.6 FINISH0.1
FEED MOVE190 PASS38 PART9

L13 D36.704
L158 DE44.399 A${formatSampleTaperAngle(getMorseTaperAngle(5))}

INSIDE
L13 D26.992
L158 DE31.267 A${formatSampleTaperAngle(getMorseTaperAngle(4))}`,
      },
    ],
  },
  {
    id: 'morse-taper-extensions',
    title: 'Prolunghe cono Morse',
    description: 'Adattatori di prolunga cono Morse corrispondenti alle righe della tabella da MT1-MT1 a MT6-MT7, con diametro corpo, diametro esterno del cono, lunghezza cono e lunghezza corpo alloggio indicati.',
    samples: MORSE_TAPER_EXTENSION_ROWS.map(createMorseTaperExtensionSample),
  },
  {
    id: 'f1-boring-head-adapters',
    title: 'Adattatori per testa alesatrice F1',
    description: 'Abbozzi di adattatori per teste alesatrici per codoli comuni NT, BT, Morse, serie C e R8, con sporgenze lato F1 e fori per tirante.',
    samples: [
      {
        id: 'nt30-f1-m12-adapter',
        title: 'Adattatore NT30-F1-M12',
        description: 'Adattatore con codolo conico NT30, sporgenza F1 e foro tirante M12.',
        text: `; Adattatore NT30-F1-M12

STOCK D54 ID8
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.55 FINISH0.1
FEED MOVE190 PASS38 PART9

L10 D30
L24 DE44 A${formatSampleTaperAngle(TAPER_ANGLE_TABLE.steep724.ansiNmtbCatBt.angleFromCenterlineDeg)}
L8 D48
L12 D50
L20 D50

INSIDE
L74 D10`,
      },
      {
        id: 'bt30-f1-m12-adapter',
        title: 'Adattatore BT30-F1-M12',
        description: 'Abbozzo adattatore stile BT30 con gradino flangia corto, sporgenza F1 e foro tirante M12.',
        text: `; Adattatore BT30-F1-M12

STOCK D56 ID8
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.55 FINISH0.1
FEED MOVE190 PASS38 PART9

L10 D31
L22 DE42 A${formatSampleTaperAngle(TAPER_ANGLE_TABLE.steep724.ansiNmtbCatBt.angleFromCenterlineDeg)}
L6 D46
L10 D52
L8 D46
L18 D50

INSIDE
L74 D10`,
      },
      {
        id: 'mt2-f1-m10-adapter',
        title: 'Adattatore MT2-F1-M10',
        description: 'Adattatore con codolo MT2, testa F1 compatta e foro tirante M10.',
        text: `; Adattatore MT2-F1-M10

STOCK D44 ID8
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L8 D14.7
L56 DE17.78 A${formatSampleTaperAngle(getMorseTaperAngle(2))}
L8 D34
L14 D40

INSIDE
L86 D8.5`,
      },
      {
        id: 'mt3-f1-m12-adapter',
        title: 'Adattatore MT3-F1-M12',
        description: 'Adattatore con codolo conico MT3, testa F1 più grande e foro tirante M12.',
        text: `; Adattatore MT3-F1-M12

STOCK D50 ID8
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.5 FINISH0.1
FEED MOVE190 PASS38 PART9

L8 D19.8
L70 DE23.825 A${formatSampleTaperAngle(getMorseTaperAngle(3))}
L8 D38
L14 D46

INSIDE
L100 D10`,
      },
      {
        id: 'mt4-f1-m16-adapter',
        title: 'Adattatore MT4-F1-M16',
        description: 'Adattatore con codolo conico MT4, testa F1 robusta e foro tirante M16.',
        text: `; Adattatore MT4-F1-M16

STOCK D62 ID8
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.6 FINISH0.1
FEED MOVE190 PASS38 PART9

L10 D25.9
L88 DE31.267 A${formatSampleTaperAngle(getMorseTaperAngle(4))}
L8 D48
L16 D58

INSIDE
L122 D13`,
      },
      {
        id: 'c25-f1-adapter',
        title: 'Adattatore C25-F1',
        description: 'Adattatore con codolo dritto C25 e sporgenza a gradino per testa alesatrice F1.',
        text: `; Adattatore C25-F1

STOCK D48 ID8
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.5 FINISH0.1
FEED MOVE190 PASS38 PART9

L44 D25
L8 D36
L18 D44

INSIDE
L70 D10`,
      },
      {
        id: 'c20-f1-adapter',
        title: 'Adattatore C20-F1',
        description: 'Adattatore con codolo dritto C20 e sporgenza compatta per testa alesatrice F1.',
        text: `; Adattatore C20-F1

STOCK D44 ID8
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L40 D20
L8 D32
L18 D40

INSIDE
L66 D8.5`,
      },
      {
        id: 'nt40-f1-m16-adapter',
        title: 'Adattatore NT40-F1-M16',
        description: 'Adattatore con codolo conico NT40, sporgenza F1 larga e foro tirante M16.',
        text: `; Adattatore NT40-F1-M16

STOCK D66 ID8
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.65 FINISH0.1
FEED MOVE190 PASS38 PART9

L12 D38
L32 DE56 A${formatSampleTaperAngle(TAPER_ANGLE_TABLE.steep724.ansiNmtbCatBt.angleFromCenterlineDeg)}
L10 D60
L18 D62
L20 D58

INSIDE
L92 D13`,
      },
      {
        id: 'bt40-f1-m16-adapter',
        title: 'Adattatore BT40-F1-M16',
        description: 'Abbozzo adattatore stile BT40 con scarico flangia, sporgenza F1 e foro tirante M16.',
        text: `; Adattatore BT40-F1-M16

STOCK D68 ID8
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.65 FINISH0.1
FEED MOVE190 PASS38 PART9

L12 D39
L30 DE54 A${formatSampleTaperAngle(TAPER_ANGLE_TABLE.steep724.ansiNmtbCatBt.angleFromCenterlineDeg)}
L8 D60
L12 D64
L10 D58
L20 D60

INSIDE
L92 D13`,
      },
      {
        id: 'r8-f1-inch-7-16-adapter',
        title: 'Adattatore R8-F1 7/16',
        description: 'Adattatore con codolo R8, testa F1 e foro tirante approssimato da 7/16 di pollice.',
        text: `; Adattatore R8-F1 7/16

STOCK D46 ID8
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.5 FINISH0.1
FEED MOVE190 PASS38 PART9

L12 D18
L13.5 DE22 A${formatSampleTaperAngle(TAPER_ANGLE_TABLE.r8.standard.angleFromCenterlineDeg)}
L41.5 D22
L8 D32
L18 D42

INSIDE
L93 D8.5`,
      },
      {
        id: 'r8-f1-m12-adapter',
        title: 'Adattatore R8-F1-M12',
        description: 'Adattatore con codolo R8, stesso profilo esterno F1 e foro tirante M12.',
        text: `; Adattatore R8-F1-M12

STOCK D46 ID8
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.5 FINISH0.1
FEED MOVE190 PASS38 PART9

L12 D18
L13.5 DE22 A${formatSampleTaperAngle(TAPER_ANGLE_TABLE.r8.standard.angleFromCenterlineDeg)}
L41.5 D22
L8 D32
L18 D42

INSIDE
L93 D10`,
      },
    ],
  },
  {
    id: 'metric-hex-bolts-din-933',
    title: 'Bulloni esagonali metrici - DIN 933',
    description: 'Abbozzi di bulloni esagonali metrici con altezza testa k, dimensioni e (punta a punta) e s (chiave) DIN 933, con piccoli smussi sulla testa e cono di inizio filettatura.',
    samples: [
      {
        id: 'm3-x-12-hex-bolt',
        title: 'Bullone esagonale M3 x 12',
        description: 'Abbozzo bullone DIN 933 M3 con testa k2, e6.01, s5.5.',
        text: `; Bullone esagonale M3 x 12

STOCK D6.01
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.35 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L0.8 DS2.4 DE3
L10.7 D3
L0.5 D2.7
L2 D6.01 CH0.255`,
      },
      {
        id: 'm4-x-16-hex-bolt',
        title: 'Bullone esagonale M4 x 16',
        description: 'Abbozzo bullone DIN 933 M4 con testa k2.8, e7.66, s7.',
        text: `; Bullone esagonale M4 x 16

STOCK D7.66
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.4 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L1 DS3.2 DE4
L14.4 D4
L0.6 D3.6
L2.8 D7.66 CH0.33`,
      },
      {
        id: 'm5-x-20-hex-bolt',
        title: 'Bullone esagonale M5 x 20',
        description: 'Abbozzo bullone DIN 933 M5 con testa k3.5, e8.79, s8.',
        text: `; Bullone esagonale M5 x 20

STOCK D8.79
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.4 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L1.2 DS4 DE5
L18.1 D5
L0.7 D4.5
L3.5 D8.79 CH0.395`,
      },
      {
        id: 'm6-x-25-hex-bolt',
        title: 'Bullone esagonale M6 x 25',
        description: 'Abbozzo bullone DIN 933 M6 con testa k4, e11.05, s10.',
        text: `; Bullone esagonale M6 x 25

STOCK D11.05
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L1.5 DS4.8 DE6
L22.7 D6
L0.8 D5.4
L4 D11.05 CH0.525`,
      },
      {
        id: 'm8-x-40-hex-bolt',
        title: 'Bullone esagonale M8 x 40',
        description: 'Abbozzo bullone DIN 933 M8 con testa k5.3, e14.38, s13.',
        text: `; Bullone esagonale M8 x 40

STOCK D14.38
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.5 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L2 DS6.4 DE8
L36.8 D8
L1.2 D7.2
L5.3 D14.38 CH0.69`,
      },
      {
        id: 'm10-x-50-hex-bolt',
        title: 'Bullone esagonale M10 x 50',
        description: 'Abbozzo bullone DIN 933 M10 con testa k6.4, e18.9, s17.',
        text: `; Bullone esagonale M10 x 50

STOCK D18.9
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.55 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L2.5 DS8 DE10
L46 D10
L1.5 D9
L6.4 D18.9 CH0.95`,
      },
      {
        id: 'm12-x-60-hex-bolt',
        title: 'Bullone esagonale M12 x 60',
        description: 'Abbozzo bullone DIN 933 M12 con testa k7.5, e21.1, s19.',
        text: `; Bullone esagonale M12 x 60

STOCK D21.1
TOOL ANG R0.4 L12 A32.5 NA55
DEPTH CUT0.6 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L3 DS9.6 DE12
L55.2 D12
L1.8 D10.8
L7.5 D21.1 CH1.05`,
      },
      {
        id: 'm14-x-70-hex-bolt',
        title: 'Bullone esagonale M14 x 70',
        description: 'Abbozzo bullone DIN 933 M14 con testa k8.8, e24.49, s22.',
        text: `; Bullone esagonale M14 x 70

STOCK D24.49
TOOL ANG R0.4 L12 A32.5 NA55
DEPTH CUT0.65 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L3.5 DS11.2 DE14
L64.4 D14
L2.1 D12.6
L8.8 D24.49 CH1.245`,
      },
      {
        id: 'm16-x-80-hex-bolt',
        title: 'Bullone esagonale M16 x 80',
        description: 'Abbozzo bullone DIN 933 M16 con testa k10, e26.75, s24.',
        text: `; Bullone esagonale M16 x 80

STOCK D26.75
TOOL ANG R0.4 L12 A32.5 NA55
DEPTH CUT0.7 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L4 DS12.8 DE16
L73.6 D16
L2.4 D14.4
L10 D26.75 CH1.375`,
      },
      {
        id: 'm18-x-90-hex-bolt',
        title: 'Bullone esagonale M18 x 90',
        description: 'Abbozzo bullone DIN 933 M18 con testa k11.5, e30.14, s27.',
        text: `; Bullone esagonale M18 x 90

STOCK D30.14
TOOL ANG R0.4 L12 A32.5 NA55
DEPTH CUT0.75 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L4.5 DS14.4 DE18
L82.8 D18
L2.7 D16.2
L11.5 D30.14 CH1.57`,
      },
      {
        id: 'm20-x-100-hex-bolt',
        title: 'Bullone esagonale M20 x 100',
        description: 'Abbozzo bullone DIN 933 M20 con testa k12.5, e33.53, s30.',
        text: `; Bullone esagonale M20 x 100

STOCK D33.53
TOOL ANG R0.4 L12 A32.5 NA55
DEPTH CUT0.8 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L5 DS16 DE20
L92 D20
L3 D18
L12.5 D33.53 CH1.765`,
      },
      {
        id: 'm22-x-110-hex-bolt',
        title: 'Bullone esagonale M22 x 110',
        description: 'Abbozzo bullone DIN 933 M22 con testa k14, e35.72, s32.',
        text: `; Bullone esagonale M22 x 110

STOCK D35.72
TOOL ANG R0.4 L12 A32.5 NA55
DEPTH CUT0.85 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L5.5 DS17.6 DE22
L101.2 D22
L3.3 D19.8
L14 D35.72 CH1.86`,
      },
      {
        id: 'm24-x-120-hex-bolt',
        title: 'Bullone esagonale M24 x 120',
        description: 'Abbozzo bullone DIN 933 M24 con testa k15, e39.98, s36.',
        text: `; Bullone esagonale M24 x 120

STOCK D39.98
TOOL ANG R0.4 L12 A32.5 NA55
DEPTH CUT0.9 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L6 DS19.2 DE24
L110.4 D24
L3.6 D21.6
L15 D39.98 CH1.99`,
      },
      {
        id: 'm27-x-140-hex-bolt',
        title: 'Bullone esagonale M27 x 140',
        description: 'Abbozzo bullone DIN 933 M27 con testa k17, e45.2, s41.',
        text: `; Bullone esagonale M27 x 140

STOCK D45.2
TOOL ANG R0.4 L12 A32.5 NA55
DEPTH CUT1 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L6.8 DS21.6 DE27
L129.1 D27
L4.1 D24.3
L17 D45.2 CH2.1`,
      },
      {
        id: 'm30-x-150-hex-bolt',
        title: 'Bullone esagonale M30 x 150',
        description: 'Abbozzo bullone DIN 933 M30 con testa k18.7, e50.85, s46.',
        text: `; Bullone esagonale M30 x 150

STOCK D50.85
TOOL ANG R0.4 L12 A32.5 NA55
DEPTH CUT1.1 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L7.5 DS24 DE30
L138 D30
L4.5 D27
L18.7 D50.85 CH2.425`,
      },
      {
        id: 'm33-x-160-hex-bolt',
        title: 'Bullone esagonale M33 x 160',
        description: 'Abbozzo bullone DIN 933 M33 con testa k21, e55.37, s50.',
        text: `; Bullone esagonale M33 x 160

STOCK D55.37
TOOL ANG R0.4 L12 A32.5 NA55
DEPTH CUT1.2 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L8.3 DS26.4 DE33
L146.7 D33
L5 D29.7
L21 D55.37 CH2.685`,
      },
      {
        id: 'm36-x-180-hex-bolt',
        title: 'Bullone esagonale M36 x 180',
        description: 'Abbozzo bullone DIN 933 M36 con testa k22.5, e60.79, s55.',
        text: `; Bullone esagonale M36 x 180

STOCK D60.79
TOOL ANG R0.4 L12 A32.5 NA55
DEPTH CUT1.3 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L9 DS28.8 DE36
L165.6 D36
L5.4 D32.4
L22.5 D60.79 CH2.895`,
      },
      {
        id: 'm42-x-200-hex-bolt',
        title: 'Bullone esagonale M42 x 200',
        description: 'Abbozzo bullone DIN 933 M42 con testa k26, e71.3, s65.',
        text: `; Bullone esagonale M42 x 200

STOCK D71.3
TOOL ANG R0.4 L12 A32.5 NA55
DEPTH CUT1.5 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L10.5 DS33.6 DE42
L183.2 D42
L6.3 D37.8
L26 D71.3 CH3.15`,
      },
      {
        id: 'm48-x-240-hex-bolt',
        title: 'Bullone esagonale M48 x 240',
        description: 'Abbozzo bullone DIN 933 M48 con testa k30, e82.6, s75.',
        text: `; Bullone esagonale M48 x 240

STOCK D82.6
TOOL ANG R0.4 L12 A32.5 NA55
DEPTH CUT1.7 FINISH0.1
FEED MOVE190 PASS40 PART10
MODE TURN

L12 DS38.4 DE48
L220.8 D48
L7.2 D43.2
L30 D82.6 CH3.8`,
      },
    ],
  },
  {
    id: 'imperial-hex-bolts',
    title: 'Bulloni esagonali in pollici',
    description: 'Abbozzi di bulloni esagonali UNC in pollici con dimensioni ASME B18.2.1 T-6 per corpo, chiave, punta a punta e altezza testa, con piccoli smussi su entrambi i lati della testa.',
    samples: [
      {
        id: 'half-13-x-2-hex-bolt',
        title: 'Bullone esagonale 1/2-13 x 2 in',
        description: 'Abbozzo ASME B18.2.1 T-6 1/2-13 con Hmax 0.323, Gmax 0.866, Fmax 0.750 e Dmax 0.499.',
        text: `; Bullone esagonale 1/2-13 x 2 in

UNITS IN
STOCK D0.866
TOOL ANG R0.008 L0.31 A32.5 NA55
DEPTH CUT0.025 FINISH0.004
FEED MOVE8 PASS2 PART0.4
MODE TURN

L0.1 DS0.4 DE0.499
L1.83 D0.499
L0.07 D0.459
L0.323 D0.866 CH0.058`,
      },
      {
        id: 'nine-sixteenths-12-x-2-25-hex-bolt',
        title: 'Bullone esagonale 9/16-12 x 2.25 in',
        description: 'Abbozzo ASME B18.2.1 T-6 9/16-12 con Hmax 0.371, Gmax 0.938, Fmax 0.812 e Dmax 0.561.',
        text: `; Bullone esagonale 9/16-12 x 2.25 in

UNITS IN
STOCK D0.938
TOOL ANG R0.008 L0.31 A32.5 NA55
DEPTH CUT0.025 FINISH0.004
FEED MOVE8 PASS2 PART0.4
MODE TURN

L0.11 DS0.45 DE0.561
L2.06 D0.561
L0.08 D0.516
L0.371 D0.938 CH0.063`,
      },
      {
        id: 'five-eighths-11-x-2-5-hex-bolt',
        title: 'Bullone esagonale 5/8-11 x 2.5 in',
        description: 'Abbozzo ASME B18.2.1 T-6 5/8-11 con Hmax 0.403, Gmax 1.083, Fmax 0.938 e Dmax 0.623.',
        text: `; Bullone esagonale 5/8-11 x 2.5 in

UNITS IN
STOCK D1.083
TOOL ANG R0.008 L0.31 A32.5 NA55
DEPTH CUT0.03 FINISH0.004
FEED MOVE8 PASS2 PART0.4
MODE TURN

L0.13 DS0.5 DE0.623
L2.28 D0.623
L0.09 D0.573
L0.403 D1.083 CH0.0725`,
      },
      {
        id: 'three-quarters-10-x-3-hex-bolt',
        title: 'Bullone esagonale 3/4-10 x 3 in',
        description: 'Abbozzo ASME B18.2.1 T-6 3/4-10 con Hmax 0.483, Gmax 1.299, Fmax 1.125 e Dmax 0.748.',
        text: `; Bullone esagonale 3/4-10 x 3 in

UNITS IN
STOCK D1.299
TOOL ANG R0.008 L0.31 A32.5 NA55
DEPTH CUT0.035 FINISH0.004
FEED MOVE8 PASS2 PART0.4
MODE TURN

L0.15 DS0.6 DE0.748
L2.74 D0.748
L0.11 D0.688
L0.483 D1.299 CH0.087`,
      },
      {
        id: 'seven-eighths-9-x-3-5-hex-bolt',
        title: 'Bullone esagonale 7/8-9 x 3.5 in',
        description: 'Abbozzo ASME B18.2.1 T-6 7/8-9 con Hmax 0.563, Gmax 1.516, Fmax 1.312 e Dmax 0.873.',
        text: `; Bullone esagonale 7/8-9 x 3.5 in

UNITS IN
STOCK D1.516
TOOL ANG R0.008 L0.31 A32.5 NA55
DEPTH CUT0.04 FINISH0.004
FEED MOVE8 PASS2 PART0.4
MODE TURN

L0.18 DS0.7 DE0.873
L3.2 D0.873
L0.12 D0.803
L0.563 D1.516 CH0.102`,
      },
      {
        id: 'one-8-x-4-hex-bolt',
        title: 'Bullone esagonale 1-8 x 4 in',
        description: 'Abbozzo ASME B18.2.1 T-6 1-8 con Hmax 0.627, Gmax 1.732, Fmax 1.500 e Dmax 0.998.',
        text: `; Bullone esagonale 1-8 x 4 in

UNITS IN
STOCK D1.732
TOOL ANG R0.016 L0.47 A32.5 NA55
DEPTH CUT0.045 FINISH0.004
FEED MOVE8 PASS2 PART0.4
MODE TURN

L0.2 DS0.8 DE0.998
L3.66 D0.998
L0.14 D0.918
L0.627 D1.732 CH0.116`,
      },
      {
        id: 'one-and-one-eighth-8-x-4-5-hex-bolt',
        title: 'Bullone esagonale 1-1/8-8 x 4.5 in',
        description: 'Abbozzo ASME B18.2.1 T-6 1-1/8-8 con Hmax 0.718, Gmax 1.949, Fmax 1.688 e Dmax 1.123.',
        text: `; Bullone esagonale 1-1/8-8 x 4.5 in

UNITS IN
STOCK D1.949
TOOL ANG R0.016 L0.47 A32.5 NA55
DEPTH CUT0.05 FINISH0.004
FEED MOVE8 PASS2 PART0.4
MODE TURN

L0.23 DS0.9 DE1.123
L4.11 D1.123
L0.16 D1.033
L0.718 D1.949 CH0.1305`,
      },
      {
        id: 'one-and-one-quarter-8-x-5-hex-bolt',
        title: 'Bullone esagonale 1-1/4-8 x 5 in',
        description: 'Abbozzo ASME B18.2.1 T-6 1-1/4-8 con Hmax 0.813, Gmax 2.165, Fmax 1.875 e Dmax 1.248.',
        text: `; Bullone esagonale 1-1/4-8 x 5 in

UNITS IN
STOCK D2.165
TOOL ANG R0.016 L0.47 A32.5 NA55
DEPTH CUT0.055 FINISH0.004
FEED MOVE8 PASS2 PART0.4
MODE TURN

L0.25 DS1 DE1.248
L4.57 D1.248
L0.18 D1.148
L0.813 D2.165 CH0.145`,
      },
      {
        id: 'one-and-three-eighths-8-x-5-5-hex-bolt',
        title: 'Bullone esagonale 1-3/8-8 x 5.5 in',
        description: 'Abbozzo ASME B18.2.1 T-6 1-3/8-8 con Hmax 0.878, Gmax 2.382, Fmax 2.062 e Dmax 1.373.',
        text: `; Bullone esagonale 1-3/8-8 x 5.5 in

UNITS IN
STOCK D2.382
TOOL ANG R0.016 L0.47 A32.5 NA55
DEPTH CUT0.06 FINISH0.004
FEED MOVE8 PASS2 PART0.4
MODE TURN

L0.28 DS1.1 DE1.373
L5.03 D1.373
L0.19 D1.263
L0.878 D2.382 CH0.16`,
      },
      {
        id: 'one-and-one-half-8-x-6-hex-bolt',
        title: 'Bullone esagonale 1-1/2-8 x 6 in',
        description: 'Abbozzo ASME B18.2.1 T-6 1-1/2-8 con Hmax 0.974, Gmax 2.598, Fmax 2.250 e Dmax 1.498.',
        text: `; Bullone esagonale 1-1/2-8 x 6 in

UNITS IN
STOCK D2.598
TOOL ANG R0.016 L0.47 A32.5 NA55
DEPTH CUT0.065 FINISH0.004
FEED MOVE8 PASS2 PART0.4
MODE TURN

L0.3 DS1.2 DE1.498
L5.49 D1.498
L0.21 D1.378
L0.974 D2.598 CH0.174`,
      },
      {
        id: 'one-and-five-eighths-8-x-6-5-hex-bolt',
        title: 'Bullone esagonale 1-5/8-8 x 6.5 in',
        description: 'Abbozzo ASME B18.2.1 T-6 1-5/8-8 con Hmax 1.038, Gmax 2.815, Fmax 2.438 e Dmax 1.623.',
        text: `; Bullone esagonale 1-5/8-8 x 6.5 in

UNITS IN
STOCK D2.815
TOOL ANG R0.016 L0.47 A32.5 NA55
DEPTH CUT0.07 FINISH0.004
FEED MOVE8 PASS2 PART0.4
MODE TURN

L0.33 DS1.3 DE1.623
L5.94 D1.623
L0.23 D1.493
L1.038 D2.815 CH0.1885`,
      },
      {
        id: 'one-and-three-quarters-8-x-7-hex-bolt',
        title: 'Bullone esagonale 1-3/4-8 x 7 in',
        description: 'Abbozzo ASME B18.2.1 T-6 1-3/4-8 con Hmax 1.134, Gmax 3.031, Fmax 2.625 e Dmax 1.748.',
        text: `; Bullone esagonale 1-3/4-8 x 7 in

UNITS IN
STOCK D3.031
TOOL ANG R0.016 L0.47 A32.5 NA55
DEPTH CUT0.075 FINISH0.004
FEED MOVE8 PASS2 PART0.4
MODE TURN

L0.35 DS1.4 DE1.748
L6.4 D1.748
L0.25 D1.608
L1.134 D3.031 CH0.203`,
      },
      {
        id: 'one-and-seven-eighths-8-x-7-5-hex-bolt',
        title: 'Bullone esagonale 1-7/8-8 x 7.5 in',
        description: 'Abbozzo ASME B18.2.1 T-6 1-7/8-8 con Hmax 1.198, Gmax 3.248, Fmax 2.812 e Dmax 1.873.',
        text: `; Bullone esagonale 1-7/8-8 x 7.5 in

UNITS IN
STOCK D3.248
TOOL ANG R0.016 L0.47 A32.5 NA55
DEPTH CUT0.08 FINISH0.004
FEED MOVE8 PASS2 PART0.4
MODE TURN

L0.38 DS1.5 DE1.873
L6.86 D1.873
L0.26 D1.723
L1.198 D3.248 CH0.218`,
      },
      {
        id: 'two-8-x-8-hex-bolt',
        title: 'Bullone esagonale 2-8 x 8 in',
        description: 'Abbozzo ASME B18.2.1 T-6 2-8 con Hmax 1.263, Gmax 3.464, Fmax 3.000 e Dmax 1.998.',
        text: `; Bullone esagonale 2-8 x 8 in

UNITS IN
STOCK D3.464
TOOL ANG R0.016 L0.47 A32.5 NA55
DEPTH CUT0.085 FINISH0.004
FEED MOVE8 PASS2 PART0.4
MODE TURN

L0.4 DS1.6 DE1.998
L7.32 D1.998
L0.28 D1.838
L1.263 D3.464 CH0.232`,
      },
      {
        id: 'two-and-one-quarter-8-x-9-hex-bolt',
        title: 'Bullone esagonale 2-1/4-8 x 9 in',
        description: 'Abbozzo ASME B18.2.1 T-6 2-1/4-8 con Hmax 1.423, Gmax 3.897, Fmax 3.375 e Dmax 2.248.',
        text: `; Bullone esagonale 2-1/4-8 x 9 in

UNITS IN
STOCK D3.897
TOOL ANG R0.016 L0.47 A32.5 NA55
DEPTH CUT0.09 FINISH0.004
FEED MOVE8 PASS2 PART0.4
MODE TURN

L0.45 DS1.8 DE2.248
L8.23 D2.248
L0.32 D2.068
L1.423 D3.897 CH0.261`,
      },
      {
        id: 'two-and-one-half-8-x-10-hex-bolt',
        title: 'Bullone esagonale 2-1/2-8 x 10 in',
        description: 'Abbozzo ASME B18.2.1 T-6 2-1/2-8 con Hmax 1.583, Gmax 4.330, Fmax 3.750 e Dmax 2.498.',
        text: `; Bullone esagonale 2-1/2-8 x 10 in

UNITS IN
STOCK D4.33
TOOL ANG R0.016 L0.47 A32.5 NA55
DEPTH CUT0.095 FINISH0.004
FEED MOVE8 PASS2 PART0.4
MODE TURN

L0.5 DS2 DE2.498
L9.15 D2.498
L0.35 D2.298
L1.583 D4.33 CH0.29`,
      },
      {
        id: 'two-and-three-quarters-8-x-11-hex-bolt',
        title: 'Bullone esagonale 2-3/4-8 x 11 in',
        description: 'Abbozzo ASME B18.2.1 T-6 2-3/4-8 con Hmax 1.744, Gmax 4.763, Fmax 4.125 e Dmax 2.748.',
        text: `; Bullone esagonale 2-3/4-8 x 11 in

UNITS IN
STOCK D4.763
TOOL ANG R0.016 L0.47 A32.5 NA55
DEPTH CUT0.1 FINISH0.004
FEED MOVE8 PASS2 PART0.4
MODE TURN

L0.55 DS2.2 DE2.748
L10.06 D2.748
L0.39 D2.528
L1.744 D4.763 CH0.319`,
      },
      {
        id: 'three-8-x-12-hex-bolt',
        title: 'Bullone esagonale 3-8 x 12 in',
        description: 'Abbozzo ASME B18.2.1 T-6 3-8 con Hmax 1.935, Gmax 5.196, Fmax 4.500 e Dmax 2.997.',
        text: `; Bullone esagonale 3-8 x 12 in

UNITS IN
STOCK D5.196
TOOL ANG R0.016 L0.47 A32.5 NA55
DEPTH CUT0.11 FINISH0.004
FEED MOVE8 PASS2 PART0.4
MODE TURN

L0.6 DS2.4 DE2.997
L10.98 D2.997
L0.42 D2.757
L1.935 D5.196 CH0.348`,
      },
    ],
  },
  {
    id: 'screw-fastener-blanks',
    title: 'Abbozzi di viti e fissaggi',
    description: 'Sagome di teste di vite, prigionieri, spine, rivetti, dadi e filettature simulate dimensionate per la geometria raggiungibile dall\'utensile.',
    samples: [
      {
        id: 'shoulder-bolt-blank',
        title: 'Abbozzo vite a spallamento',
        description: 'Filetto più piccolo, spallamento di precisione più grande e testa rotonda ampia lato mandrino.',
        text: `; Abbozzo vite a spallamento

STOCK D30
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.45 FINISH0.1
FEED MOVE220 PASS50 PART12
MODE TURN

L7 D8
L12 D16
L2 D14
L6 D26
L3 D28`,
      },
      {
        id: 'fully-threaded-rod-blank',
        title: 'Abbozzo barra interamente filettata',
        description: 'Cilindro dritto con gole anulari ripetute raggiungibili che simulano il passo della filettatura.',
        text: `; Abbozzo barra interamente filettata

STOCK D22
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.4 FINISH0.1
FEED MOVE220 PASS50 PART12
MODE TURN

L3 D10
L1.5 D13
L1.5 D10
L1.5 D13
L1.5 D10
L1.5 D13
L1.5 D10
L8 D14
L4 D20`,
      },
      {
        id: 'pan-head-screw-blank',
        title: 'Abbozzo vite a testa bombata',
        description: 'Testa bombata e fascia dritta della vite, tagliate con utensile a punta tonda per il raggio della testa.',
        text: `; Abbozzo vite a testa bombata

STOCK D24
TOOL ROUND R1.5
DEPTH CUT0.4 FINISH0.1
FEED MOVE180 PASS36 PART9

L8 D7
L5 D10
L3 DS10 DE20 CONV
L4 D22
L3 D22`,
      },
      {
        id: 'countersunk-screw-blank',
        title: 'Abbozzo vite a testa svasata',
        description: 'Testa conica e gambo stretto, con la testa più grande rivolta verso il mandrino.',
        text: `; Abbozzo vite a testa svasata

STOCK D26
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS40 PART10

L9 D7
L3 D10
L7 DS10 DE24
L3 D24`,
      },
      {
        id: 'thumb-screw-blank',
        title: 'Abbozzo vite a testa zigrinata',
        description: 'Testa grande arrotondata tipo pomello con gambo sottile, pronta per la zigrinatura fuori da lathecode.',
        text: `; Abbozzo vite a testa zigrinata

STOCK D32
TOOL ROUND R1.5
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L10 D8
L5 D12
L5 DS12 DE28 CONV
L4 D30`,
      },
      {
        id: 'threaded-spacer-stud',
        title: 'Prigioniero distanziale filettato',
        description: 'Prigioniero cavo tipo distanziale con foro passante e spallamento più grande lato mandrino.',
        text: `; Prigioniero distanziale filettato

STOCK D28 ID8
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L8 D14
L10 D18
L5 D24

INSIDE
L23 D10`,
      },
      {
        id: 'fake-thread-pitch-sampler',
        title: 'Campioni passo filettatura simulato',
        description: 'Diverse barre scanalate in un unico setup di materiale, con gruppi visivi di passo differenti.',
        text: `; Campioni passo filettatura simulato

STOCK D24
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.4 FINISH0.1
FEED MOVE220 PASS50 PART12

L2 D10
L1.5 D14
L1.5 D10
L1.5 D14
L1.5
L3 D12
L1.5 D16
L3 D12
L1.5
L4 D14
L1.5 D18
L4 D14
L4 D22`,
      },
      {
        id: 'solid-rivet-blank',
        title: 'Abbozzo rivetto pieno',
        description: 'Testa a cupola e gambo dritto, usando un utensile tondo per il raggio della testa.',
        text: `; Abbozzo rivetto pieno

STOCK D24
TOOL ROUND R1.5
DEPTH CUT0.4 FINISH0.1
FEED MOVE180 PASS36 PART9

L10 D8
L4 D10
L4 DS10 DE22 CONV
L3 D22`,
      },
      {
        id: 'grooved-pin-blank',
        title: 'Abbozzo spina scanalata',
        description: 'Spina con gola raggiungibile per anello di tenuta e bottone più grande lato mandrino.',
        text: `; Abbozzo spina scanalata

STOCK D24
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.4 FINISH0.1
FEED MOVE220 PASS50 PART12
MODE TURN

L8 D10
L1.5 D8
L8 D12
L4 D18
L3 D22`,
      },
      {
        id: 'round-nut-blank',
        title: 'Abbozzo dado tondo',
        description: 'Corpo cilindrico di dado tondo con foro passante in materiale tubolare.',
        text: `; Abbozzo dado tondo

STOCK D28 ID10
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L6 D22
L6 D24

INSIDE
L12 D14`,
      },
      {
        id: 'acorn-nut-blank',
        title: 'Abbozzo dado cieco',
        description: 'Corpo di dado a cupola chiuso con foro interno e calotta esterna arrotondata.',
        text: `; Abbozzo dado cieco

STOCK D32 ID10
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L3 D16
L5 DS16 DE26 CONV
L5 D30

INSIDE
L8 D14
L5 D12`,
      },
      {
        id: 'decorative-screw-cap',
        title: 'Calotta decorativa per vite',
        description: 'Calotta bassa a cupola con incavo interno rappresentato da un breve profilo di foro.',
        text: `; Calotta decorativa per vite

STOCK D30 ID10
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.4 FINISH0.1
FEED MOVE180 PASS36 PART9

L3 D20
L5 DS20 DE26 CONV
L3 D28

INSIDE
L4 D18
L7 D12`,
      },
    ],
  },
  {
    id: 'shafts-axles-journals',
    title: 'Alberi, assi e perni',
    description: 'Alberi dritti, perni a gradini, assi, sedi cuscinetto, gole ed estremità arrotondate con scarichi pari alla larghezza utensile e supporto lato mandrino.',
    samples: [
      {
        id: 'straight-shaft-blank',
        title: 'Abbozzo albero dritto',
        description: 'Cilindro lungo semplice per controllare scala, rettilineità e finitura di base.',
        text: `; Abbozzo albero dritto

STOCK D18
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.4 FINISH0.1
FEED MOVE220 PASS50 PART12
MODE TURN

L36 D12
L4 D16`,
      },
      {
        id: 'shaft-with-center-relief',
        title: 'Albero con scarico centrale',
        description: 'Due fasce cuscinetto più grandi separate da un tratto centrale ridotto.',
        text: `; Albero con scarico centrale

STOCK D26
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.45 FINISH0.1
FEED MOVE220 PASS50 PART12
MODE TURN

L8 D18
L12 D12
L10 D20
L4 D24`,
      },
      {
        id: 'shaft-with-parting-grooves',
        title: 'Albero con gole di troncatura',
        description: 'Albero dritto con gole raggiungibili a ogni estremità per troncatura o elementi di tenuta.',
        text: `; Albero con gole di troncatura

STOCK D24
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.4 FINISH0.1
FEED MOVE220 PASS50 PART12
MODE TURN

L5 D12
L1.5 D9
L18 D14
L1.5 D10
L6 D18
L4 D22`,
      },
      {
        id: 'two-diameter-motor-shaft',
        title: 'Albero motore a due diametri',
        description: 'Estremità di uscita piccola, albero principale più grande e spallamento posteriore robusto.',
        text: `; Albero motore a due diametri

STOCK D26
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.45 FINISH0.1
FEED MOVE220 PASS50 PART12
MODE TURN

L14 D8
L18 D16
L5 D24`,
      },
      {
        id: 'eccentric-free-cam-blank',
        title: 'Abbozzo camma senza eccentricità',
        description: 'Sagoma lobata rotonda tipo camma, a simmetria assiale, senza alcun vero scostamento eccentrico.',
        text: `; Abbozzo camma senza eccentricità

STOCK D32
TOOL ROUND R1.5
DEPTH CUT0.4 FINISH0.1
FEED MOVE180 PASS36 PART9

L5 D12
L5 DS12 DE24 CONV
L6 D28
L5 DS28 DE18 CONV
L4 D30`,
      },
      {
        id: 'toy-wheel-axle',
        title: 'Asse per ruote giocattolo',
        description: 'Assicino piccolo con bottoni arrotondati alle estremità per ruote giocattolo, sempre a simmetria assiale.',
        text: `; Asse per ruote giocattolo

STOCK D24
TOOL ROUND R1.5
DEPTH CUT0.4 FINISH0.1
FEED MOVE180 PASS36 PART9
MODE TURN

L3 DS8 DE16 CONV
L18 D10
L4 D18
L3 D22`,
      },
      {
        id: 'miniature-train-axle-blank',
        title: 'Abbozzo asse trenino',
        description: 'Albero centrale con due sedi ruota e spallamento di presa lato mandrino.',
        text: `; Abbozzo asse trenino

STOCK D28
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.45 FINISH0.1
FEED MOVE220 PASS50 PART12
MODE TURN

L6 D10
L5 D18
L12 D12
L5 D20
L4 D26`,
      },
      {
        id: 'dual-bearing-seat',
        title: 'Doppia sede cuscinetto',
        description: 'Due fasce cuscinetto rilevate separate da uno scarico centrale raggiungibile.',
        text: `; Doppia sede cuscinetto

STOCK D30
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.45 FINISH0.1
FEED MOVE220 PASS50 PART12
MODE TURN

L7 D18
L8 D12
L8 D20
L5 D26
L3 D28`,
      },
      {
        id: 'retaining-ring-groove-shaft',
        title: 'Albero con gole anello elastico',
        description: 'Albero con più gole tipo anello elastico abbastanza larghe per l\'utensile.',
        text: `; Albero con gole anello elastico

STOCK D26
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.4 FINISH0.1
FEED MOVE220 PASS50 PART12
MODE TURN

L6 D12
L1.5 D9
L8 D14
L1.5 D10
L8 D18
L4 D24`,
      },
      {
        id: 'end-capped-journal',
        title: 'Perno con testata',
        description: 'Perno con estremità arrotondata, calotta liscia e fascia posteriore più grande per un\'estremità dall\'aspetto finito.',
        text: `; Perno con testata

STOCK D28
TOOL ROUND R1.5
DEPTH CUT0.4 FINISH0.1
FEED MOVE180 PASS36 PART9

L4 DS8 DE14 CONV
L14 D14
L5 D22
L4 D26`,
      },
    ],
  },




  {
    id: 'v-belt-pulley-groove-standards',
    title: 'Standard gole pulegge a cinghia trapezoidale',
    description: 'Campioni di pulegge a una e più gole con diametro esterno, apertura gola, diametro di fondo, passo e distanza bordo ricavati da tabella per cinghie metriche, classiche e a profilo stretto in pollici.',
    samples: [
      {
        id: 'spz-80-single-v-pulley',
        title: 'Puleggia V singola SPZ 80 mm',
        description: 'Gola metrica SPZ a PD 80 mm: OD 84, gola 34 gradi, apertura 9.7 mm e larghezza fascia 16 mm.',
        text: `; Puleggia V singola SPZ 80 mm
; PD80 OD84 alpha34 W9.7 D11 X2 E8

STOCK D88 ID16
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.6 FINISH0.1
FEED MOVE200 PASS42 PART10

L3.15 D84
L3.36 DS84 DE62
L2.97 D62
L3.36 DS62 DE84
L3.15 D84

INSIDE
L15.99 D20`,
      },
      {
        id: 'spz-160-triple-v-pulley',
        title: 'Puleggia V tripla SPZ 160 mm',
        description: 'Tre gole SPZ a PD 160 mm con fianchi a 38 gradi, passo gola 12 mm e distanza bordo da tabella.',
        text: `; Puleggia V tripla SPZ 160 mm
; PD160 OD164 alpha38 W9.7 D11 X2 S12 E8

STOCK D168 ID28
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.8 FINISH0.1
FEED MOVE220 PASS45 PART12

L3.15 D164
L3.79 DS164 DE142
L2.12 D142
L3.79 DS142 DE164
L2.3 D164
L3.79 DS164 DE142
L2.12 D142
L3.79 DS142 DE164
L2.3 D164
L3.79 DS164 DE142
L2.12 D142
L3.79 DS142 DE164
L3.15 D164

INSIDE
L39.99 D40`,
      },
      {
        id: 'spa-118-double-v-pulley',
        title: 'Puleggia V doppia SPA 118 mm',
        description: 'Due gole SPA nel campo del diametro primitivo a 34 gradi con passo 15 mm e distanza bordo 10 mm.',
        text: `; Puleggia V doppia SPA 118 mm
; PD118 OD123.5 alpha34 W12.7 D13.8 X2.75 S15 E10

STOCK D128 ID24
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.7 FINISH0.1
FEED MOVE210 PASS44 PART11

L3.65 D123.5
L4.22 DS123.5 DE95.9
L4.26 D95.9
L4.22 DS95.9 DE123.5
L2.3 D123.5
L4.22 DS123.5 DE95.9
L4.26 D95.9
L4.22 DS95.9 DE123.5
L3.65 D123.5

INSIDE
L34.99 D32`,
      },
      {
        id: 'spb-224-double-v-pulley',
        title: 'Puleggia V doppia SPB 224 mm',
        description: 'Due gole SPB sopra il punto di rottura di 190 mm: gola 38 gradi, apertura 16.2 mm e passo 17 mm.',
        text: `; Puleggia V doppia SPB 224 mm
; PD224 OD231 alpha38 W16.2 D17.5 X3.5 S17 E12.5

STOCK D236 ID42
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.9 FINISH0.1
FEED MOVE220 PASS46 PART12

L4.4 D231
L6.03 DS231 DE196
L4.15 D196
L6.03 DS196 DE231
L0.8 D231
L6.03 DS231 DE196
L4.15 D196
L6.03 DS196 DE231
L4.4 D231

INSIDE
L42.02 D55`,
      },
      {
        id: 'spc-355-single-v-pulley',
        title: 'Puleggia V singola SPC 355 mm',
        description: 'Gola singola SPC grande con OD 364.6 mm, fianchi a 38 gradi, apertura 22 mm e fascia 34 mm.',
        text: `; Puleggia V singola SPC 355 mm
; PD355 OD364.6 alpha38 W22 D23.8 X4.8 E17

STOCK D372 ID70
TOOL RECT R0.15 L1.5 H4
DEPTH CUT1.2 FINISH0.1
FEED MOVE240 PASS50 PART14

L6 D364.6
L8.19 DS364.6 DE317
L5.61 D317
L8.19 DS317 DE364.6
L6 D364.6

INSIDE
L33.99 D90`,
      },
      {
        id: 'ab-6in-double-v-pulley',
        title: 'Puleggia V doppia A/B 6 in',
        description: 'Sezione classica A/B a PD 6 in, convertita in mm con gole a 34 gradi e passo 19.05 mm.',
        text: `; Puleggia V doppia A/B 6 in
; PD152.4 OD161.3 alpha34 W15.54 D15.88 X4.45 S19.05 E12.7

STOCK D166 ID30
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.8 FINISH0.1
FEED MOVE220 PASS45 PART12

L4.93 D161.3
L4.86 DS161.3 DE129.54
L5.83 D129.54
L4.86 DS129.54 DE161.3
L3.51 D161.3
L4.86 DS161.3 DE129.54
L5.83 D129.54
L4.86 DS129.54 DE161.3
L4.93 D161.3

INSIDE
L44.47 D42`,
      },
      {
        id: 'c-10in-single-v-pulley',
        title: 'Puleggia V singola C 10 in',
        description: 'Sezione classica C nel campo 8-12 in, con gola a 36 gradi e dimensioni convertite in mm.',
        text: `; Puleggia V singola C 10 in
; PD254 OD264.16 alpha36 W22.53 D19.81 X5.08 E17.48

STOCK D270 ID50
TOOL RECT R0.15 L1.5 H4
DEPTH CUT1 FINISH0.1
FEED MOVE230 PASS48 PART13

L6.21 D264.16
L6.44 DS264.16 DE224.54
L9.66 D224.54
L6.44 DS224.54 DE264.16
L6.21 D264.16

INSIDE
L34.96 D64`,
      },
      {
        id: 'd-14in-double-v-pulley',
        title: 'Puleggia V doppia D 14 in',
        description: 'Sezione classica D nel campo 13-17 in, con gole a 36 gradi e fascia ampia a due gole.',
        text: `; Puleggia V doppia D 14 in
; PD355.6 OD370.84 alpha36 W32.28 D26.67 X7.62 S36.53 E22.23

STOCK D378 ID70
TOOL RECT R0.15 L1.5 H4
DEPTH CUT1.2 FINISH0.1
FEED MOVE240 PASS50 PART14

L6.09 D370.84
L8.67 DS370.84 DE317.5
L14.95 D317.5
L8.67 DS317.5 DE370.84
L4.25 D370.84
L8.67 DS370.84 DE317.5
L14.95 D317.5
L8.67 DS317.5 DE370.84
L6.09 D370.84

INSIDE
L81.01 D90`,
      },
      {
        id: 'e-24in-single-v-pulley',
        title: 'Puleggia V singola E 24 in',
        description: 'Sezione classica E grande a PD 24 in, con gola a 36 gradi e dimensioni convertite in mm.',
        text: `; Puleggia V singola E 24 in
; PD609.6 OD629.92 alpha36 W38.79 D33.02 X10.16 E31.24

STOCK D640 ID100
TOOL RECT R0.15 L1.5 H4
DEPTH CUT1.6 FINISH0.1
FEED MOVE250 PASS54 PART15

L11.84 D629.92
L10.73 DS629.92 DE563.88
L17.33 D563.88
L10.73 DS563.88 DE629.92
L11.84 D629.92

INSIDE
L62.47 D125`,
      },
      {
        id: '3v-7in-triple-v-pulley',
        title: 'Puleggia V tripla 3V 7 in',
        description: 'Puleggia tripla a profilo stretto 3V nel campo 40 gradi, con passo 10.34 mm e distanza bordo 8.74 mm.',
        text: `; Puleggia V tripla 3V 7 in
; PD177.8 OD179.08 alpha40 W8.89 D8.89 X0.64 S10.34 E8.74

STOCK D184 ID30
TOOL RECT R0.15 L1.5 H4
DEPTH CUT0.6 FINISH0.1
FEED MOVE220 PASS45 PART12

L4.29 D179.08
L3.24 DS179.08 DE161.3
L2.42 D161.3
L3.24 DS161.3 DE179.08
L1.45 D179.08
L3.24 DS179.08 DE161.3
L2.42 D161.3
L3.24 DS161.3 DE179.08
L1.45 D179.08
L3.24 DS179.08 DE161.3
L2.42 D161.3
L3.24 DS161.3 DE179.08
L4.29 D179.08

INSIDE
L38.15 D40`,
      },
      {
        id: '5v-12in-double-v-pulley',
        title: 'Puleggia V doppia 5V 12 in',
        description: 'Puleggia doppia a profilo stretto 5V nel campo 10-16 in, modellata con angolo gola incluso di 40 gradi.',
        text: `; Puleggia V doppia 5V 12 in
; PD304.8 OD307.34 alpha40 W15.24 D15.24 X1.27 S17.48 E12.7

STOCK D314 ID50
TOOL RECT R0.15 L1.5 H4
DEPTH CUT1 FINISH0.1
FEED MOVE230 PASS48 PART13

L5.08 D307.34
L5.55 DS307.34 DE276.86
L4.15 D276.86
L5.55 DS276.86 DE307.34
L2.24 D307.34
L5.55 DS307.34 DE276.86
L4.15 D276.86
L5.55 DS276.86 DE307.34
L5.08 D307.34

INSIDE
L42.88 D70`,
      },
      {
        id: '8v-18in-single-v-pulley',
        title: 'Puleggia V singola 8V 18 in',
        description: 'Puleggia grande a profilo stretto 8V a PD 18 in con gola a 40 gradi, apertura 25.4 mm e fascia 38.1 mm.',
        text: `; Puleggia V singola 8V 18 in
; PD457.2 OD462.28 alpha40 W25.4 D25.4 X2.54 E19.05

STOCK D472 ID80
TOOL RECT R0.15 L1.5 H4
DEPTH CUT1.4 FINISH0.1
FEED MOVE240 PASS52 PART14

L6.35 D462.28
L9.24 DS462.28 DE411.48
L6.91 D411.48
L9.24 DS411.48 DE462.28
L6.35 D462.28

INSIDE
L38.09 D105`,
      },
    ],
  },
  {
    id: 'pulleys-wheels-rotating-blanks',
    title: 'Pulegge, ruote e abbozzi rotanti',
    description: 'Abbozzi di pulegge, ruote, rulli, rocchetti e bobine con fori, flange, corone, coni e larghezze gola realistici e adatti all\'utensile selezionato.',
    samples: [
      {
        id: 'flat-belt-pulley-blank',
        title: 'Abbozzo puleggia a cinghia piatta',
        description: 'Faccia di appoggio con corona e foro passante centrale e fascia di presa più grande lato mandrino.',
        text: `; Abbozzo puleggia a cinghia piatta

STOCK D38 ID12
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L4 D28
L6 DS28 DE34 CONV
L6 DS34 DE30 CONV
L4 D36

INSIDE
L20 D16`,
      },
      {
        id: 'v-belt-pulley-blank',
        title: 'Abbozzo puleggia a cinghia trapezoidale',
        description: 'Abbozzo puleggia con gola larga inclinata e flange rilevate.',
        text: `; Abbozzo puleggia a cinghia trapezoidale

STOCK D40 ID12
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L4 D34
L5 DS34 DE22
L4 D22
L5 DS22 DE34
L4 D36

INSIDE
L22 D16`,
      },
      {
        id: 'round-belt-pulley',
        title: 'Puleggia a cinghia tonda',
        description: 'Gola arrotondata per cinghia, tagliata con piccolo utensile a punta tonda e foro passante.',
        text: `; Puleggia a cinghia tonda

STOCK D40 ID12
TOOL ROUND R1.5
DEPTH CUT0.4 FINISH0.1
FEED MOVE180 PASS36 PART9

L4 D34
L6 DS34 DE22 CONC
L4 D22
L6 DS22 DE34 CONC
L4 D36

INSIDE
L24 D16`,
      },
      {
        id: 'multi-groove-belt-pulley',
        title: 'Puleggia a più gole',
        description: 'Abbozzo puleggia singola con tre gole a V, fasce rilevate e mozzo più pesante lato mandrino.',
        text: `; Puleggia a più gole

STOCK D42
TOOL ANG R0.2 L7.8 A32.5 NA55
DEPTH CUT0.5 FINISH0.1
FEED MOVE190 PASS40 PART10

L3 D34
L2 DS34 DE28
L2 DS28 DE34
L2 D34
L2 DS34 DE28
L2 DS28 DE34
L2 D34
L2 DS34 DE28
L2 DS28 DE34
L3 D36
L3 D40`,
      },
      {
        id: 'toy-wheel-blank',
        title: 'Abbozzo ruota giocattolo',
        description: 'Profilo esterno arrotondato tipo pneumatico con semplice foro mozzo.',
        text: `; Abbozzo ruota giocattolo

STOCK D38 ID10
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.4 FINISH0.1
FEED MOVE180 PASS36 PART9

L3 D24
L5 DS24 DE34 CONV
L5 DS34 DE26 CONV
L4 D36

INSIDE
L17 D14`,
      },
      {
        id: 'model-train-wheel-blank',
        title: 'Abbozzo ruota trenino',
        description: 'Flangia tipo ruota ferroviaria, battistrada conico, mozzo e foro in un abbozzo solo tondo.',
        text: `; Abbozzo ruota trenino

STOCK D38 ID10
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L3 D32
L8 DS30 DE24
L4 D26
L4 D36

INSIDE
L19 D14`,
      },
      {
        id: 'flywheel-blank',
        title: 'Abbozzo volano',
        description: 'Cerchio pesante, impressione di raggiera più sottile, mozzo centrale e foro passante.',
        text: `; Abbozzo volano

STOCK D38 ID10
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L4 D34
L8 D22
L4 D28
L4 D36

INSIDE
L20 D14`,
      },
      {
        id: 'handwheel-blank-round-only',
        title: 'Abbozzo volantino, solo tondo',
        description: 'Contorno rotondo di volantino con cerchio e mozzo rilevati ma senza razze.',
        text: `; Abbozzo volantino, solo tondo

STOCK D40 ID12
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L4 D34
L8 D24
L4 D30
L4 D38

INSIDE
L20 D16`,
      },
      {
        id: 'wire-spool',
        title: 'Rocchetto per filo',
        description: 'Abbozzo rocchetto a due flange per filo con vita centrale stretta e foro.',
        text: `; Rocchetto per filo

STOCK D38 ID10
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L4 D34
L14 D22
L4 D36
L3 D36

INSIDE
L25 D14`,
      },
      {
        id: 'cable-drum',
        title: 'Tamburo per cavo',
        description: 'Tamburo grande flangiato con valle di avvolgimento arrotondata e foro centrale.',
        text: `; Tamburo per cavo

STOCK D44 ID12
TOOL ROUND R1.5
DEPTH CUT0.45 FINISH0.1
FEED MOVE180 PASS36 PART9

L5 D40
L6 DS40 DE26 CONC
L6 D26
L6 DS26 DE40 CONC
L5 D42

INSIDE
L28 D16`,
      },
      {
        id: 'fishing-reel-spool-blank',
        title: 'Abbozzo bobina mulinello',
        description: 'Corpo bobina conico tra flange con foro centrale pulito.',
        text: `; Abbozzo bobina mulinello

STOCK D42 ID12
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.45 FINISH0.1
FEED MOVE190 PASS38 PART9

L4 D36
L6 DS36 DE24
L8 D24
L6 DS24 DE38
L4 D40

INSIDE
L28 D16`,
      },
      {
        id: 'miniature-winch-drum',
        title: 'Tamburo argano in miniatura',
        description: 'Tamburo argano scanalato con flange, foro passante e gole di avvolgimento larghe quanto l\'utensile.',
        text: `; Tamburo argano in miniatura

STOCK D38 ID10
TOOL ANG R0.15 L2.2 A120 NA55
DEPTH CUT0.4 FINISH0.1
FEED MOVE190 PASS38 PART9

L4 D34
L5 D24
L2.2 D20
L5 D24
L2.2 D20
L5 D24
L4 D36

INSIDE
L27.4 D14`,
      },
    ],
  },

] as const;

export const START_SAMPLE_DEFINITIONS: readonly SampleDefinition[] = SAMPLE_SECTIONS.flatMap(section => section.samples);

export function getStartSampleSections(): readonly SampleSection[] {
  return SAMPLE_SECTIONS;
}

export function getStartSampleDefinitions(): SampleDefinition[] {
  return START_SAMPLE_DEFINITIONS.slice();
}
