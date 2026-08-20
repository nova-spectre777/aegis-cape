#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
echo "[C++]"
cmake -S "$ROOT/engine-cpp" -B "$ROOT/engine-cpp/build" >/dev/null
cmake --build "$ROOT/engine-cpp/build" >/dev/null
ctest --test-dir "$ROOT/engine-cpp/build" --output-on-failure

echo "[Go]"
(cd "$ROOT/coordinator-go" && go test ./...)

echo "[Python]"
PYTHONPATH="$ROOT/adversary-python" python3 -m unittest discover -s "$ROOT/adversary-python/tests" -v

echo "[TypeScript]"
(cd "$ROOT/wallet-ts" && rm -rf dist && tsc -p tsconfig.json && node --test dist/test/*.js)

echo "[Research toolchains]"
for tool in rustc zig lake solc forge; do if command -v "$tool" >/dev/null 2>&1; then echo "$tool: available"; else echo "$tool: not installed (source track not verified)"; fi; done
