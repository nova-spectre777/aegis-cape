declare module 'node:crypto' {
  export function createHash(name:string): { update(data:string): { digest(encoding:'hex'): string } };
}
declare module 'node:test' {
  const test: (name:string, fn:()=>void|Promise<void>) => void;
  export default test;
}
declare module 'node:assert/strict' {
  const assert: { equal(actual:unknown, expected:unknown): void; ok(value:unknown): void };
  export default assert;
}
