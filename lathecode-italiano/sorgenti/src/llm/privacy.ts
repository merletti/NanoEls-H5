const OPENROUTER_PROVIDER_PRIVACY =
  'Le richieste OpenRouter richiedono endpoint del fornitore con raccolta dati disattivata e conservazione dati zero.';

export const OPENROUTER_API_KEY_PRIVACY =
  `La tua chiave API OpenRouter è memorizzata localmente in questo browser e inviata solo a OpenRouter quando usi un'azione LLM. ${OPENROUTER_PROVIDER_PRIVACY}`;

export function openRouterActionPrivacyText(sentDataDescription: string): string {
  return `${sentDataDescription} Nessun server lathecode la memorizza. ${OPENROUTER_PROVIDER_PRIVACY}`;
}

export function createPrivacyDisclosure(text: string): HTMLParagraphElement {
  const disclosure = document.createElement('p');
  disclosure.className = 'privacyDisclosure';
  disclosure.textContent = text;
  return disclosure;
}
