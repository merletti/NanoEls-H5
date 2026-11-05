import { truncateText } from './generatedlathecode.ts';

const OPENROUTER_RESPONSE_EXCERPT_LENGTH = 800;

export type OpenRouterResponse = {
  choices?: OpenRouterChoice[],
  error?: {
    message?: string,
  },
};

export type OpenRouterChoice = {
  finish_reason?: string | null,
  native_finish_reason?: string | null,
  message?: {
    content?: unknown,
    reasoning?: unknown,
    reasoning_details?: unknown,
    refusal?: unknown,
  },
};

export function extractAssistantText(content: unknown): string {
  if (typeof content === 'string') return content;
  if (!Array.isArray(content)) return '';
  return content.map(part => {
    if (typeof part === 'string') return part;
    if (part && typeof part === 'object' && 'text' in part && typeof part.text === 'string') return part.text;
    return '';
  }).join('');
}

export function formatNoOpenRouterContentError(choice: OpenRouterChoice | undefined): string {
  if (!choice) return 'OpenRouter non ha restituito scelte';
  const finishReason = choice.finish_reason ?? choice.native_finish_reason ?? '';
  const fields = ['OpenRouter non ha restituito contenuto lathecode.'];
  if (finishReason) fields.push(`Motivo di completamento: ${finishReason}.`);
  if (hasOpenRouterReasoning(choice.message)) {
    fields.push('Il provider ha restituito testo di ragionamento, ma message.content era vuoto, quindi non c\'era lathecode da elaborare.');
  }
  if (finishReason === 'length') {
    fields.push('La risposta ha raggiunto il limite di token di completamento prima di produrre il lathecode finale. Riprova o scegli un modello/impostazioni che producano il testo finale con meno ragionamento.');
  }
  const refusal = extractRefusalText(choice.message?.refusal);
  if (refusal) fields.push(`Rifiuto: ${truncateText(refusal, 240)}`);

  const excerpt = extractOpenRouterChoiceExcerpt(choice);
  if (excerpt) fields.push('', 'Estratto della risposta del modello:', truncateText(excerpt, OPENROUTER_RESPONSE_EXCERPT_LENGTH));
  return fields.join('\n');
}

function hasOpenRouterReasoning(message: OpenRouterChoice['message']): boolean {
  const reasoning = message?.reasoning;
  const reasoningDetails = message?.reasoning_details;
  return (typeof reasoning === 'string' && reasoning.trim().length > 0)
    || (Array.isArray(reasoningDetails) && reasoningDetails.length > 0);
}

function extractRefusalText(refusal: unknown): string {
  if (typeof refusal === 'string') return refusal.trim();
  if (!refusal || typeof refusal !== 'object') return '';
  if ('reason' in refusal && typeof refusal.reason === 'string') return refusal.reason.trim();
  if ('message' in refusal && typeof refusal.message === 'string') return refusal.message.trim();
  return '';
}

function extractOpenRouterChoiceExcerpt(choice: OpenRouterChoice): string {
  const message = choice.message;
  const parts = [
    extractAssistantText(message?.content),
    extractUnknownText(message?.reasoning),
    extractUnknownText(message?.reasoning_details),
    extractUnknownText(message?.refusal),
  ];
  return normalizeExcerptText(parts.filter(Boolean).join('\n'));
}

function extractUnknownText(value: unknown): string {
  if (typeof value === 'string') return value;
  if (Array.isArray(value)) return value.map(extractUnknownText).filter(Boolean).join('\n');
  if (!value || typeof value !== 'object') return '';
  if ('text' in value && typeof value.text === 'string') return value.text;
  if ('content' in value && typeof value.content === 'string') return value.content;
  if ('message' in value && typeof value.message === 'string') return value.message;
  if ('reason' in value && typeof value.reason === 'string') return value.reason;
  try {
    return JSON.stringify(value);
  } catch {
    return '';
  }
}

function normalizeExcerptText(text: string): string {
  return text.replace(/\s+/g, ' ').trim();
}
