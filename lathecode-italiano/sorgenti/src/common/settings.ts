export const PX_PER_MM_OPTIONS = [10, 50, 100, 250, 500, 750, 1000] as const;
export const PX_PER_MM_STORAGE_KEY = 'pxPerMm';
export const PLANNER_ENGINE_OPTIONS = ['pixel', 'vector'] as const;
export const DEFAULT_OPENROUTER_MODEL = 'deepseek/deepseek-v4-pro';
export const DEFAULT_OPENROUTER_VISION_MODEL = 'google/gemini-3.1-flash-lite-preview';

export type PlannerEngine = typeof PLANNER_ENGINE_OPTIONS[number];

export type AppSettings = {
  pxPerMm: number,
  plannerEngine: PlannerEngine,
  cuttingEdgeThicknessPx: number,
  pixelRoughStairToleranceMm: number,
  optimizeEpsilonDegrees: number,
  smoothingEpsilonPx: number,
  plannerCanvasSizePx: number,
  plannerPreviewSourcePixelLimit: number,
  moveTimeoutMs: number,
  stlDebugCanvasSizePx: number,
  partRevolutionDegrees: number,
  vectorComparisonToleranceMm: number,
  vectorContactClearanceMm: number,
  vectorToolpathGougeToleranceAreaMm2: number,
  vectorFinalLeftoverMinToleranceAreaMm2: number,
  vectorGeometryLinearToleranceMm: number,
  vectorMinimumCutDepthMm: number,
  vectorMinimumRoughChipAreaMm2: number,
  vectorMinimumUsefulCutMm: number,
  vectorPassInsetMm: number,
  vectorCandidateMarginMm: number,
  vectorCandidateMinimumStepMm: number,
  vectorFaceCreepBoundaryRangeMm: number,
  vectorFaceCreepMinimumStepMm: number,
  vectorBoundaryCleanupMinAreaMm2: number,
  vectorRadialBoundaryToleranceMm: number,
  vectorFinishChordMinMm: number,
  vectorFinishChordMaxMm: number,
  vectorSpanSampleOffsetMaxMm: number,
  vectorBinarySearchIterations: number,
  polygonEpsilonMm: number,
  polygonClipperScale: number,
  toolGeometryCircleSteps: number,
  toolGeometryOvertravelScanSteps: number,
  toolGeometryOvertravelBinarySearchIterations: number,
  toolGeometryBoundaryToleranceMm: number,
  stlProjectionScale: number,
  stlCutPlaneToleranceMm: number,
  stlProjectionMinimumAreaPx2: number,
  stlConstantRadiusTolerancePx: number,
  stlSizeMatchTolerance: number,
  showNanoElsH4Controls: boolean,
  openRouterApiKey: string,
  openRouterModel: string,
  openRouterVisionModel: string,
};

export type AppSettingKey = keyof AppSettings;

type BaseAppSettingDefinition = {
  key: AppSettingKey,
  label: string,
  storageKey: string,
  guidance: string,
};

export type NumericAppSettingDefinition = BaseAppSettingDefinition & {
  type: 'number',
  defaultValue: number,
  min: number,
  max: number,
  step: number,
  unit: string,
  reasonableValues: string,
  integer?: boolean,
};

export type SelectAppSettingDefinition = BaseAppSettingDefinition & {
  type: 'select',
  defaultValue: PlannerEngine,
  options: readonly {
    value: PlannerEngine,
    label: string,
  }[],
};

export type BooleanAppSettingDefinition = BaseAppSettingDefinition & {
  type: 'boolean',
  defaultValue: boolean,
};

export type TextAppSettingDefinition = BaseAppSettingDefinition & {
  type: 'text',
  defaultValue: string,
  inputType?: 'text' | 'password',
  placeholder?: string,
  allowEmpty?: boolean,
};

export type AppSettingDefinition =
  NumericAppSettingDefinition
  | SelectAppSettingDefinition
  | BooleanAppSettingDefinition
  | TextAppSettingDefinition;

export type AppSettingSectionDefinition = {
  id: string,
  label: string,
  guidance: string,
  plannerEngines?: readonly PlannerEngine[],
  definitions: readonly AppSettingDefinition[],
};

export const DEFAULT_APP_SETTINGS: AppSettings = {
  pxPerMm: 100,
  plannerEngine: 'pixel',
  cuttingEdgeThicknessPx: 2,
  pixelRoughStairToleranceMm: 0.025,
  optimizeEpsilonDegrees: 0.05,
  smoothingEpsilonPx: 0.9,
  plannerCanvasSizePx: 500,
  plannerPreviewSourcePixelLimit: 1000000000,
  moveTimeoutMs: 50,
  stlDebugCanvasSizePx: 500,
  partRevolutionDegrees: 360,
  vectorComparisonToleranceMm: 1e-6,
  vectorContactClearanceMm: 1e-4,
  vectorToolpathGougeToleranceAreaMm2: 1e-4,
  vectorFinalLeftoverMinToleranceAreaMm2: 0.5,
  vectorGeometryLinearToleranceMm: 0.001,
  vectorMinimumCutDepthMm: 0.001,
  vectorMinimumRoughChipAreaMm2: 0.001,
  vectorMinimumUsefulCutMm: 0.001,
  vectorPassInsetMm: 0.001,
  vectorCandidateMarginMm: 0.001,
  vectorCandidateMinimumStepMm: 0.05,
  vectorFaceCreepBoundaryRangeMm: 0.5,
  vectorFaceCreepMinimumStepMm: 0.025,
  vectorBoundaryCleanupMinAreaMm2: 1e-5,
  vectorRadialBoundaryToleranceMm: 0.001,
  vectorFinishChordMinMm: 0.05,
  vectorFinishChordMaxMm: 0.1,
  vectorSpanSampleOffsetMaxMm: 1e-5,
  vectorBinarySearchIterations: 20,
  polygonEpsilonMm: 1e-9,
  polygonClipperScale: 100000,
  toolGeometryCircleSteps: 48,
  toolGeometryOvertravelScanSteps: 100,
  toolGeometryOvertravelBinarySearchIterations: 24,
  toolGeometryBoundaryToleranceMm: 1e-6,
  stlProjectionScale: 100000,
  stlCutPlaneToleranceMm: 1e-6,
  stlProjectionMinimumAreaPx2: 0.001,
  stlConstantRadiusTolerancePx: 1,
  stlSizeMatchTolerance: 0.2,
  showNanoElsH4Controls: false,
  openRouterApiKey: '',
  openRouterModel: DEFAULT_OPENROUTER_MODEL,
  openRouterVisionModel: DEFAULT_OPENROUTER_VISION_MODEL,
};

export const DEFAULT_PX_PER_MM = DEFAULT_APP_SETTINGS.pxPerMm;
export const DEFAULT_PLANNER_ENGINE = DEFAULT_APP_SETTINGS.plannerEngine;
export const CUTTING_EDGE_THICKNESS_PX = DEFAULT_APP_SETTINGS.cuttingEdgeThicknessPx;
export const OPTIMIZE_EPSILON_DEGREES = DEFAULT_APP_SETTINGS.optimizeEpsilonDegrees;
export const SMOOTHING_EPSILON_PX = DEFAULT_APP_SETTINGS.smoothingEpsilonPx;
export const PLANNER_CANVAS_SIZE_PX = DEFAULT_APP_SETTINGS.plannerCanvasSizePx;
export const DEFAULT_MOVE_TIMEOUT_MS = DEFAULT_APP_SETTINGS.moveTimeoutMs;
export const STL_DEBUG_CANVAS_SIZE_PX = DEFAULT_APP_SETTINGS.stlDebugCanvasSizePx;

export const APP_SETTING_SECTIONS: readonly AppSettingSectionDefinition[] = [
  {
    id: 'planning',
    label: 'Pianificazione',
    guidance: 'Scelta del pianificatore principale e della risoluzione condivisa da pianificazione e importazione STL.',
    definitions: [
      {
        key: 'pxPerMm',
        type: 'number',
        label: 'Pixel per mm',
        storageKey: PX_PER_MM_STORAGE_KEY,
        defaultValue: DEFAULT_APP_SETTINGS.pxPerMm,
        min: 10,
        max: 1000,
        step: 1,
        unit: 'px/mm',
        reasonableValues: PX_PER_MM_OPTIONS.join(', '),
        guidance: 'Risoluzione raster per la pianificazione e l\'importazione STL. Valori più alti conservano più dettagli ma rendono la pianificazione più lenta e dispendiosa in memoria.',
        integer: true,
      },
      {
        key: 'plannerEngine',
        type: 'select',
        label: 'Motore del pianificatore',
        storageKey: 'plannerEngine',
        defaultValue: DEFAULT_APP_SETTINGS.plannerEngine,
        options: [
          {value: 'pixel', label: 'Pixel (stabile)'},
          {value: 'vector', label: 'Vettoriale (sperimentale)'},
        ],
        guidance: 'Scegli il pianificatore a pixel stabile o quello vettoriale sperimentale. Pixel resta il predefinito perché al momento è più affidabile.',
      },
    ],
  },
  {
    id: 'pixelPlanner',
    label: 'Pianificatore a pixel',
    guidance: 'Controlli del pianificatore raster che influenzano taglio a pixel, unione delle movimentazioni e GCode generato.',
    plannerEngines: ['pixel'],
    definitions: [
      {
        key: 'cuttingEdgeThicknessPx',
        type: 'number',
        label: 'Spessore del tagliente',
        storageKey: 'cuttingEdgeThicknessPx',
        defaultValue: DEFAULT_APP_SETTINGS.cuttingEdgeThicknessPx,
        min: 1,
        max: 10,
        step: 1,
        unit: 'px',
        reasonableValues: '1 a 5',
        guidance: 'Numero di pixel del colore utensile considerati tagliente attivo. Aumenta solo se i contorni dell\'utensile sono troppo sottili o frammentati.',
        integer: true,
      },
      {
        key: 'pixelRoughStairToleranceMm',
        type: 'number',
        label: 'Tolleranza gradini di sgrossatura',
        storageKey: 'pixelRoughStairToleranceMm',
        defaultValue: DEFAULT_APP_SETTINGS.pixelRoughStairToleranceMm,
        min: 0,
        max: 0.1,
        step: 0.001,
        unit: 'mm',
        reasonableValues: '0.01 a 0.03',
        guidance: 'Deviazione geometrica massima consentita semplificando piccoli gradini di sgrossatura in movimenti rettilinei. Il pianificatore la limita anche a un quarto del sovrametallo di finitura.',
      },
      {
        key: 'optimizeEpsilonDegrees',
        type: 'number',
        label: 'Tolleranza angolare ottimizzazione coni',
        storageKey: 'optimizeEpsilonDegrees',
        defaultValue: DEFAULT_APP_SETTINGS.optimizeEpsilonDegrees,
        min: 0,
        max: 1,
        step: 0.01,
        unit: 'gradi',
        reasonableValues: '0.01 a 0.2',
        guidance: 'Differenza angolare massima per unire sequenze ripetute di movimenti simili a coni. Valori più alti riducono i movimenti ma possono alterare la geometria.',
      },
      {
        key: 'smoothingEpsilonPx',
        type: 'number',
        label: 'Tolleranza di addolcimento movimenti',
        storageKey: 'smoothingEpsilonPx',
        defaultValue: DEFAULT_APP_SETTINGS.smoothingEpsilonPx,
        min: 0,
        max: 5,
        step: 0.05,
        unit: 'px',
        reasonableValues: '0.2 a 1.5',
        guidance: 'Deviazione massima in pixel consentita addolcendo movimenti adiacenti. Valori più alti producono GCode più corto con meno fedeltà al livello del pixel.',
      },
    ],
  },
  {
    id: 'vectorPlanner',
    label: 'Pianificatore vettoriale avanzato',
    guidance: 'Tolleranze geometriche per il pianificatore vettoriale sperimentale. I valori predefiniti corrispondono al comportamento del pianificatore integrato.',
    plannerEngines: ['vector'],
    definitions: [
      {
        key: 'vectorComparisonToleranceMm',
        type: 'number',
        label: 'Tolleranza di confronto',
        storageKey: 'vectorComparisonToleranceMm',
        defaultValue: DEFAULT_APP_SETTINGS.vectorComparisonToleranceMm,
        min: 0,
        max: 0.001,
        step: 0.000001,
        unit: 'mm',
        reasonableValues: '0.000001 a 0.00001',
        guidance: 'Tolleranza minima sulle coordinate usata per uguaglianze e controllo dell\'avanzamento dei cicli. Aumentala solo in caso di instabilità numerica.',
      },
      {
        key: 'vectorContactClearanceMm',
        type: 'number',
        label: 'Distanza di contatto finitura',
        storageKey: 'vectorContactClearanceMm',
        defaultValue: DEFAULT_APP_SETTINGS.vectorContactClearanceMm,
        min: 0,
        max: 0.01,
        step: 0.0001,
        unit: 'mm',
        reasonableValues: '0 a 0.001',
        guidance: 'Piccolo scostamento tra il contatto preferito di finitura e il contatto esatto dell\'utensile. Valori più bassi tagliano più vicino ma possono toccare i confini protetti.',
      },
      {
        key: 'vectorToolpathGougeToleranceAreaMm2',
        type: 'number',
        label: 'Area di tolleranza per scavature',
        storageKey: 'vectorToolpathGougeToleranceAreaMm2',
        defaultValue: DEFAULT_APP_SETTINGS.vectorToolpathGougeToleranceAreaMm2,
        min: 0,
        max: 0.1,
        step: 0.0001,
        unit: 'mm²',
        reasonableValues: '0.00001 a 0.001',
        guidance: 'Sovrapposizione consentita con le aree protette nei controlli dell\'utensile in movimento. Mantienila piccola: valori alti possono nascondere scavature reali.',
      },
      {
        key: 'vectorFinalLeftoverMinToleranceAreaMm2',
        type: 'number',
        label: 'Soglia segnalazione materiale residuo',
        storageKey: 'vectorFinalLeftoverMinToleranceAreaMm2',
        defaultValue: DEFAULT_APP_SETTINGS.vectorFinalLeftoverMinToleranceAreaMm2,
        min: 0,
        max: 10,
        step: 0.01,
        unit: 'mm²',
        reasonableValues: '0.1 a 1',
        guidance: 'Area minima di materiale residuo prima che la verifica finale vettoriale segnali materiale non asportato.',
      },
      {
        key: 'vectorGeometryLinearToleranceMm',
        type: 'number',
        label: 'Tolleranza lineare geometria',
        storageKey: 'vectorGeometryLinearToleranceMm',
        defaultValue: DEFAULT_APP_SETTINGS.vectorGeometryLinearToleranceMm,
        min: 0,
        max: 0.1,
        step: 0.0001,
        unit: 'mm',
        reasonableValues: '0.0005 a 0.005',
        guidance: 'Tolleranza lineare usata scalando le tolleranze dell\'area di verifica per poligoni e approssimazione con corde.',
      },
      {
        key: 'vectorMinimumCutDepthMm',
        type: 'number',
        label: 'Profondità minima di taglio',
        storageKey: 'vectorMinimumCutDepthMm',
        defaultValue: DEFAULT_APP_SETTINGS.vectorMinimumCutDepthMm,
        min: 0.000001,
        max: 0.1,
        step: 0.0001,
        unit: 'mm',
        reasonableValues: '0.0005 a 0.005',
        guidance: 'Limite inferiore per larghezze di taglio e finitura usate dalla pianificazione delle passate vettoriali.',
      },
      {
        key: 'vectorMinimumRoughChipAreaMm2',
        type: 'number',
        label: 'Area minima truciolo di sgrossatura',
        storageKey: 'vectorMinimumRoughChipAreaMm2',
        defaultValue: DEFAULT_APP_SETTINGS.vectorMinimumRoughChipAreaMm2,
        min: 0,
        max: 1,
        step: 0.0001,
        unit: 'mm²',
        reasonableValues: '0.0005 a 0.01',
        guidance: 'Area minima di truciolo di sgrossatura che vale la pena pianificare. Aumentarla riduce minuscoli movimenti di sgrossatura e lascia più lavoro alla finitura.',
      },
      {
        key: 'vectorMinimumUsefulCutMm',
        type: 'number',
        label: 'Lunghezza minima di taglio utile',
        storageKey: 'vectorMinimumUsefulCutMm',
        defaultValue: DEFAULT_APP_SETTINGS.vectorMinimumUsefulCutMm,
        min: 0,
        max: 0.1,
        step: 0.0001,
        unit: 'mm',
        reasonableValues: '0.0005 a 0.005',
        guidance: 'Profondità minima di materiale o lunghezza sicura minima prima che un taglio vettoriale sia considerato utile.',
      },
      {
        key: 'vectorPassInsetMm',
        type: 'number',
        label: 'Rientro bordo passata',
        storageKey: 'vectorPassInsetMm',
        defaultValue: DEFAULT_APP_SETTINGS.vectorPassInsetMm,
        min: 0,
        max: 0.05,
        step: 0.0001,
        unit: 'mm',
        reasonableValues: '0.0005 a 0.005',
        guidance: 'Piccolo rientro usato per campionare dentro una fascia di sgrossatura invece che esattamente su un bordo del poligono.',
      },
      {
        key: 'vectorCandidateMarginMm',
        type: 'number',
        label: 'Margine bordo candidato',
        storageKey: 'vectorCandidateMarginMm',
        defaultValue: DEFAULT_APP_SETTINGS.vectorCandidateMarginMm,
        min: 0,
        max: 0.05,
        step: 0.0001,
        unit: 'mm',
        reasonableValues: '0.0005 a 0.005',
        guidance: 'Margine dai bordi dell\'intervallo quando si scelgono i punti di affondo e di inizio tornitura candidati.',
      },
      {
        key: 'vectorCandidateMinimumStepMm',
        type: 'number',
        label: 'Passo minimo candidato',
        storageKey: 'vectorCandidateMinimumStepMm',
        defaultValue: DEFAULT_APP_SETTINGS.vectorCandidateMinimumStepMm,
        min: 0.001,
        max: 1,
        step: 0.001,
        unit: 'mm',
        reasonableValues: '0.02 a 0.1',
        guidance: 'Spaziatura minima tra le posizioni candidate di sgrossatura campionate. Valori più bassi cercano più posizioni e possono rallentare la pianificazione.',
      },
      {
        key: 'vectorFaceCreepBoundaryRangeMm',
        type: 'number',
        label: 'Intervallo creep di faccia',
        storageKey: 'vectorFaceCreepBoundaryRangeMm',
        defaultValue: DEFAULT_APP_SETTINGS.vectorFaceCreepBoundaryRangeMm,
        min: 0,
        max: 5,
        step: 0.01,
        unit: 'mm',
        reasonableValues: '0.1 a 1',
        guidance: 'Distanza dal confine radiale entro cui la sgrossatura della faccia può aggiungere movimenti laterali di pulizia.',
      },
      {
        key: 'vectorFaceCreepMinimumStepMm',
        type: 'number',
        label: 'Passo minimo creep di faccia',
        storageKey: 'vectorFaceCreepMinimumStepMm',
        defaultValue: DEFAULT_APP_SETTINGS.vectorFaceCreepMinimumStepMm,
        min: 0.001,
        max: 0.5,
        step: 0.001,
        unit: 'mm',
        reasonableValues: '0.01 a 0.05',
        guidance: 'Passo minimo per la pulizia laterale della faccia. Valori più bassi sono più fini ma più lenti.',
      },
      {
        key: 'vectorBoundaryCleanupMinAreaMm2',
        type: 'number',
        label: 'Area minima pulizia bordo',
        storageKey: 'vectorBoundaryCleanupMinAreaMm2',
        defaultValue: DEFAULT_APP_SETTINGS.vectorBoundaryCleanupMinAreaMm2,
        min: 0,
        max: 0.01,
        step: 0.00001,
        unit: 'mm²',
        reasonableValues: '0.00001 a 0.0001',
        guidance: 'Materiale asportato in più minimo necessario perché venga mantenuto il superamento del confine radiale non terminale.',
      },
      {
        key: 'vectorRadialBoundaryToleranceMm',
        type: 'number',
        label: 'Tolleranza confine radiale',
        storageKey: 'vectorRadialBoundaryToleranceMm',
        defaultValue: DEFAULT_APP_SETTINGS.vectorRadialBoundaryToleranceMm,
        min: 0,
        max: 0.05,
        step: 0.0001,
        unit: 'mm',
        reasonableValues: '0.0005 a 0.005',
        guidance: 'Tolleranza per riconoscere i punti di pulizia sul confine radiale di mezzeria, foro o diametro esterno.',
      },
      {
        key: 'vectorFinishChordMinMm',
        type: 'number',
        label: 'Corda minima finitura',
        storageKey: 'vectorFinishChordMinMm',
        defaultValue: DEFAULT_APP_SETTINGS.vectorFinishChordMinMm,
        min: 0.001,
        max: 1,
        step: 0.001,
        unit: 'mm',
        reasonableValues: '0.02 a 0.1',
        guidance: 'Limite inferiore della lunghezza della corda delle curve nell\'approssimazione del profilo vettoriale. Valori più bassi conservano più dettagli e possono rallentare il ritaglio.',
      },
      {
        key: 'vectorFinishChordMaxMm',
        type: 'number',
        label: 'Corda massima finitura',
        storageKey: 'vectorFinishChordMaxMm',
        defaultValue: DEFAULT_APP_SETTINGS.vectorFinishChordMaxMm,
        min: 0.001,
        max: 2,
        step: 0.001,
        unit: 'mm',
        reasonableValues: '0.05 a 0.2',
        guidance: 'Limite superiore della lunghezza della corda delle curve nell\'approssimazione del profilo vettoriale. Valori più alti sono più veloci ma meno precisi sulle curve.',
      },
      {
        key: 'vectorSpanSampleOffsetMaxMm',
        type: 'number',
        label: 'Scostamento massimo campione intervallo',
        storageKey: 'vectorSpanSampleOffsetMaxMm',
        defaultValue: DEFAULT_APP_SETTINGS.vectorSpanSampleOffsetMaxMm,
        min: 0,
        max: 0.001,
        step: 0.000001,
        unit: 'mm',
        reasonableValues: '0.000001 a 0.00005',
        guidance: 'Piccolo scostamento massimo usato per campionare intervalli accanto ai bordi del poligono.',
      },
      {
        key: 'vectorBinarySearchIterations',
        type: 'number',
        label: 'Iterazioni ricerca prefisso sicuro',
        storageKey: 'vectorBinarySearchIterations',
        defaultValue: DEFAULT_APP_SETTINGS.vectorBinarySearchIterations,
        min: 1,
        max: 60,
        step: 1,
        unit: 'iterazioni',
        reasonableValues: '12 a 30',
        guidance: 'Iterazioni usate nella ricerca binaria del prefisso sicuro più lungo di un movimento vettoriale candidato.',
        integer: true,
      },
    ],
  },
  {
    id: 'geometry',
    label: 'Geometria avanzata',
    guidance: 'Tolleranze condivise per poligoni e impronta utensile usate dalla pianificazione vettoriale e dal ritaglio geometrico.',
    plannerEngines: ['vector'],
    definitions: [
      {
        key: 'polygonEpsilonMm',
        type: 'number',
        label: 'Epsilon poligono',
        storageKey: 'polygonEpsilonMm',
        defaultValue: DEFAULT_APP_SETTINGS.polygonEpsilonMm,
        min: 0,
        max: 0.000001,
        step: 0.000000001,
        unit: 'mm',
        reasonableValues: '0.000000001 a 0.00000001',
        guidance: 'Tolleranza minima per punti duplicati dei poligoni, unione di intervalli e filtri di area prima del ritaglio a virgola fissa.',
      },
      {
        key: 'polygonClipperScale',
        type: 'number',
        label: 'Scala a virgola fissa poligoni',
        storageKey: 'polygonClipperScale',
        defaultValue: DEFAULT_APP_SETTINGS.polygonClipperScale,
        min: 1000,
        max: 10000000,
        step: 1000,
        unit: 'unità/mm',
        reasonableValues: '100000 a 1000000',
        guidance: 'Fattore di scala per convertire la geometria vettoriale in coordinate intere per le operazioni Clipper. Valori più alti conservano più precisione ma riducono l\'intervallo sicuro delle coordinate.',
        integer: true,
      },
      {
        key: 'toolGeometryCircleSteps',
        type: 'number',
        label: 'Segmenti del cerchio utensile',
        storageKey: 'toolGeometryCircleSteps',
        defaultValue: DEFAULT_APP_SETTINGS.toolGeometryCircleSteps,
        min: 8,
        max: 360,
        step: 1,
        unit: 'segmenti',
        reasonableValues: '32 a 96',
        guidance: 'Numero di segmenti usati per approssimare punte tonde e raccordi circolari dell\'utensile. Valori più alti sono più morbidi e più lenti.',
        integer: true,
      },
      {
        key: 'toolGeometryOvertravelScanSteps',
        type: 'number',
        label: 'Passi di scansione superamento bordo',
        storageKey: 'toolGeometryOvertravelScanSteps',
        defaultValue: DEFAULT_APP_SETTINGS.toolGeometryOvertravelScanSteps,
        min: 10,
        max: 1000,
        step: 1,
        unit: 'passi',
        reasonableValues: '50 a 200',
        guidance: 'Passi di scansione grossolana per trovare il superamento utile del confine radiale dall\'impronta dell\'utensile.',
        integer: true,
      },
      {
        key: 'toolGeometryOvertravelBinarySearchIterations',
        type: 'number',
        label: 'Iterazioni rifinitura superamento bordo',
        storageKey: 'toolGeometryOvertravelBinarySearchIterations',
        defaultValue: DEFAULT_APP_SETTINGS.toolGeometryOvertravelBinarySearchIterations,
        min: 1,
        max: 60,
        step: 1,
        unit: 'iterazioni',
        reasonableValues: '16 a 32',
        guidance: 'Iterazioni di ricerca binaria per rifinire il superamento del confine radiale dopo che la scansione grossolana ha trovato un attraversamento.',
        integer: true,
      },
      {
        key: 'toolGeometryBoundaryToleranceMm',
        type: 'number',
        label: 'Tolleranza confine utensile',
        storageKey: 'toolGeometryBoundaryToleranceMm',
        defaultValue: DEFAULT_APP_SETTINGS.toolGeometryBoundaryToleranceMm,
        min: 0,
        max: 0.001,
        step: 0.000001,
        unit: 'mm',
        reasonableValues: '0.000001 a 0.00001',
        guidance: 'Tolleranza per stabilire se un intervallo dell\'impronta utensile copre l\'intera larghezza dell\'utensile in un campione di confine.',
      },
    ],
  },
  {
    id: 'stlImport',
    label: 'Importazione STL avanzata',
    guidance: 'Tolleranze numeriche usate proiettando o sezionando mesh STL in profili torniti.',
    definitions: [
      {
        key: 'stlProjectionScale',
        type: 'number',
        label: 'Scala proiezione STL',
        storageKey: 'stlProjectionScale',
        defaultValue: DEFAULT_APP_SETTINGS.stlProjectionScale,
        min: 1000,
        max: 1000000,
        step: 1000,
        unit: 'unità/mm',
        reasonableValues: '100000 a 200000',
        guidance: 'Scala usata per arrotondare le coordinate dei triangoli proiettati prima dell\'unione dei poligoni. Valori più alti conservano i dettagli ma possono rendere il ritaglio più rumoroso.',
        integer: true,
      },
      {
        key: 'stlCutPlaneToleranceMm',
        type: 'number',
        label: 'Tolleranza piano di taglio STL',
        storageKey: 'stlCutPlaneToleranceMm',
        defaultValue: DEFAULT_APP_SETTINGS.stlCutPlaneToleranceMm,
        min: 0.000000001,
        max: 0.001,
        step: 0.000001,
        unit: 'mm',
        reasonableValues: '0.000001 a 0.00001',
        guidance: 'Tolleranza di distanza per classificare vertici e facce STL come giacenti su un piano di sezione.',
      },
      {
        key: 'stlProjectionMinimumAreaPx2',
        type: 'number',
        label: 'Area minima proiezione STL',
        storageKey: 'stlProjectionMinimumAreaPx2',
        defaultValue: DEFAULT_APP_SETTINGS.stlProjectionMinimumAreaPx2,
        min: 0,
        max: 10,
        step: 0.001,
        unit: 'px²',
        reasonableValues: '0.001 a 0.1',
        guidance: 'Area minima del poligono proiettato mantenuta dopo la pulizia della sezione STL.',
      },
      {
        key: 'stlConstantRadiusTolerancePx',
        type: 'number',
        label: 'Tolleranza raggio costante STL',
        storageKey: 'stlConstantRadiusTolerancePx',
        defaultValue: DEFAULT_APP_SETTINGS.stlConstantRadiusTolerancePx,
        min: 0,
        max: 20,
        step: 0.1,
        unit: 'px',
        reasonableValues: '0.5 a 2',
        guidance: 'Tolleranza in pixel per riconoscere un profilo interno importato come raggio del foro del materiale costante.',
      },
      {
        key: 'stlSizeMatchTolerance',
        type: 'number',
        label: 'Tolleranza corrispondenza dimensioni STL',
        storageKey: 'stlSizeMatchTolerance',
        defaultValue: DEFAULT_APP_SETTINGS.stlSizeMatchTolerance,
        min: 0,
        max: 2,
        step: 0.01,
        unit: 'rapporto',
        reasonableValues: '0.1 a 0.4',
        guidance: 'Scostamento relativo del volume di contenimento consentito classificando le proiezioni STL candidate rispetto alle dimensioni della mesh originale.',
      },
    ],
  },
  {
    id: 'preview',
    label: 'Anteprima e diagnostica',
    guidance: 'Impostazioni solo di visualizzazione per anteprime e canvas diagnostici.',
    definitions: [
      {
        key: 'partRevolutionDegrees',
        type: 'number',
        label: 'Rivoluzione pezzo 3D',
        storageKey: 'partRevolutionDegrees',
        defaultValue: DEFAULT_APP_SETTINGS.partRevolutionDegrees,
        min: 45,
        max: 360,
        step: 1,
        unit: 'gradi',
        reasonableValues: '180 a 360',
        guidance: 'Ampiezza angolare usata ruotando il pezzo nell\'anteprima 3D. Usa 360 per un solido completo o 270 per una vista in sezione.',
        integer: true,
      },
      {
        key: 'plannerCanvasSizePx',
        type: 'number',
        label: 'Dimensione anteprima pianificatore',
        storageKey: 'plannerCanvasSizePx',
        defaultValue: DEFAULT_APP_SETTINGS.plannerCanvasSizePx,
        min: 100,
        max: 2000,
        step: 50,
        unit: 'px',
        reasonableValues: '300 a 1000',
        guidance: 'Dimensione di destinazione per anteprime del pianificatore e del percorso utensile. Influisce sulla dimensione di visualizzazione, non sulle coordinate macchina generate.',
        integer: true,
      },
      {
        key: 'plannerPreviewSourcePixelLimit',
        type: 'number',
        label: 'Limite pixel sorgente anteprima pianificatore',
        storageKey: 'plannerPreviewSourcePixelLimit',
        defaultValue: DEFAULT_APP_SETTINGS.plannerPreviewSourcePixelLimit,
        min: 0,
        max: 10000000000,
        step: 1000000,
        unit: 'px',
        reasonableValues: '10000000 a 1000000000',
        guidance: 'Bitmap sorgente più grande del pianificatore a pixel ammessa per generare l\'anteprima delle aree non tagliate. Riducila per evitare tempi di scansione extra su lavori enormi ad alta risoluzione; imposta 0 per disattivare queste anteprime.',
        integer: true,
      },
      {
        key: 'moveTimeoutMs',
        type: 'number',
        label: 'Ritardo disegno percorso utensile',
        storageKey: 'moveTimeoutMs',
        defaultValue: DEFAULT_APP_SETTINGS.moveTimeoutMs,
        min: 0,
        max: 1000,
        step: 1,
        unit: 'ms',
        reasonableValues: '0 a 100',
        guidance: 'Ritardo tra i movimenti disegnati del percorso utensile. Usa 0 per il rendering immediato; il parametro URL moveTimeout ha comunque la precedenza.',
        integer: true,
      },
      {
        key: 'stlDebugCanvasSizePx',
        type: 'number',
        label: 'Dimensione anteprima diagnostica STL',
        storageKey: 'stlDebugCanvasSizePx',
        defaultValue: DEFAULT_APP_SETTINGS.stlDebugCanvasSizePx,
        min: 100,
        max: 2000,
        step: 50,
        unit: 'px',
        reasonableValues: '300 a 1000',
        guidance: 'Dimensione del canvas per le viste diagnostiche delle proiezioni STL. Influisce solo sulla visualizzazione diagnostica.',
        integer: true,
      },
    ],
  },
  {
    id: 'gcodeOutput',
    label: 'Uscita GCode',
    guidance: 'Controlli per le azioni di output del G-code generato e le integrazioni con l\'invio.',
    definitions: [
      {
        key: 'showNanoElsH4Controls',
        type: 'boolean',
        label: 'Mostra controlli NanoEls H4',
        storageKey: 'showNanoElsH4Controls',
        defaultValue: DEFAULT_APP_SETTINGS.showNanoElsH4Controls,
        guidance: 'Mostra i pulsanti Serial API del browser per eseguire o salvare il G-code generato su NanoEls H4. Lascia disattivato se di solito copi il G-code o usi un altro controller.',
      },
    ],
  },
  {
    id: 'llm',
    label: 'LLM',
    guidance: 'Impostazioni OpenRouter usate da prompt, disegno e modifiche dall\'editor. Le azioni LLM inviano solo i dati necessari per quell\'azione da questo browser a OpenRouter.',
    definitions: [
      {
        key: 'openRouterApiKey',
        type: 'text',
        label: 'Chiave API OpenRouter',
        storageKey: 'openRouterApiKey',
        defaultValue: DEFAULT_APP_SETTINGS.openRouterApiKey,
        inputType: 'password',
        placeholder: 'sk-or-...',
        allowEmpty: true,
        guidance: 'Memorizzata localmente in questo browser. Le richieste LLM usano filtri dei provider OpenRouter che rifiutano endpoint che raccolgono dati e non ZDR.',
      },
      {
        key: 'openRouterModel',
        type: 'text',
        label: 'Modello testuale OpenRouter',
        storageKey: 'openRouterModel',
        defaultValue: DEFAULT_APP_SETTINGS.openRouterModel,
        placeholder: DEFAULT_OPENROUTER_MODEL,
        guidance: 'Modello usato per prompt testuali e modifiche dall\'editor.',
      },
      {
        key: 'openRouterVisionModel',
        type: 'text',
        label: 'Modello visione OpenRouter',
        storageKey: 'openRouterVisionModel',
        defaultValue: DEFAULT_APP_SETTINGS.openRouterVisionModel,
        placeholder: DEFAULT_OPENROUTER_VISION_MODEL,
        guidance: 'Modello usato per il caricamento delle immagini dei disegni tecnici. DeepSeek V3.2 su OpenRouter è solo testuale, quindi l\'input di immagini richiede un modello con visione.',
      },
    ],
  },
];

export const APP_SETTING_DEFINITIONS: readonly AppSettingDefinition[] = APP_SETTING_SECTIONS.flatMap(section => section.definitions);

type RawAppSettingValue = number | string | boolean | null | undefined;
type AppSettingValue = number | PlannerEngine | boolean | string;

export function parsePxPerMm(value: number | string | null | undefined): number {
  return parseNumericAppSetting(getNumericAppSettingDefinition('pxPerMm'), value);
}

export function normalizeAppSettings(values: Partial<Record<AppSettingKey, RawAppSettingValue>> = {}): AppSettings {
  const settings = {...DEFAULT_APP_SETTINGS} as Record<AppSettingKey, AppSettingValue>;
  for (const definition of APP_SETTING_DEFINITIONS) {
    settings[definition.key] = parseAppSetting(definition, values[definition.key]);
  }
  return settings as AppSettings;
}

export function loadAppSettings(storage: Storage = localStorage): AppSettings {
  const values: Partial<Record<AppSettingKey, string | null>> = {};
  for (const definition of APP_SETTING_DEFINITIONS) {
    values[definition.key] = storage.getItem(definition.storageKey);
  }
  return normalizeAppSettings(values);
}

export function saveAppSettings(settings: Partial<AppSettings>, storage: Storage = localStorage): AppSettings {
  const normalized = normalizeAppSettings(settings);
  for (const definition of APP_SETTING_DEFINITIONS) {
    storage.setItem(definition.storageKey, String(normalized[definition.key]));
  }
  return normalized;
}

function parseAppSetting(definition: AppSettingDefinition, value: RawAppSettingValue): AppSettingValue {
  if (definition.type === 'select') return parseSelectAppSetting(definition, value);
  if (definition.type === 'boolean') return parseBooleanAppSetting(definition, value);
  if (definition.type === 'text') return parseTextAppSetting(definition, value);
  return parseNumericAppSetting(definition, value);
}

function parseSelectAppSetting(definition: SelectAppSettingDefinition, value: RawAppSettingValue): PlannerEngine {
  if (typeof value !== 'string') return definition.defaultValue;
  return definition.options.some(option => option.value === value) ? value as PlannerEngine : definition.defaultValue;
}

function parseNumericAppSetting(definition: NumericAppSettingDefinition, value: RawAppSettingValue): number {
  if (value === null || value === undefined || value === '') return definition.defaultValue;
  if (typeof value === 'boolean') return definition.defaultValue;
  const numberValue = Number(value);
  if (!Number.isFinite(numberValue)) return definition.defaultValue;
  const rounded = definition.integer ? Math.round(numberValue) : numberValue;
  return Math.min(definition.max, Math.max(definition.min, rounded));
}

function parseBooleanAppSetting(definition: BooleanAppSettingDefinition, value: RawAppSettingValue): boolean {
  if (typeof value === 'boolean') return value;
  if (typeof value !== 'string') return definition.defaultValue;
  if (value === 'true' || value === '1') return true;
  if (value === 'false' || value === '0') return false;
  return definition.defaultValue;
}

function parseTextAppSetting(definition: TextAppSettingDefinition, value: RawAppSettingValue): string {
  if (value === null || value === undefined) return definition.defaultValue;
  if (typeof value === 'boolean') return definition.defaultValue;
  const textValue = String(value).trim();
  if (!textValue && !definition.allowEmpty) return definition.defaultValue;
  return textValue;
}

function getNumericAppSettingDefinition(key: AppSettingKey): NumericAppSettingDefinition {
  const definition = APP_SETTING_DEFINITIONS.find((d): d is NumericAppSettingDefinition => d.key === key && d.type === 'number');
  if (!definition) throw new Error(`Impostazione numerica sconosciuta: ${key}`);
  return definition;
}
