#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cmake -S "$ROOT/engine-cpp" -B "$ROOT/engine-cpp/build" >/dev/null
cmake --build "$ROOT/engine-cpp/build" >/dev/null
"$ROOT/engine-cpp/build/aegis-cape"
PYTHONPATH="$ROOT/adversary-python" python3 -m aegis_lab.cli benchmark --seed 7 --count 64
