# AEGIS v0.1 Verification

Verified locally on the release environment.

## Verified toolchains
- C++23: GCC 14.2.0 / CMake
- Go: 1.23.2
- Python: 3.13.5
- TypeScript: 5.8.3 / Node 22.16.0

## Passing checks
- C++ CAPE-Σ solver: 1/1 CTest passed
- Go coordinator/quorum/API tests: passed
- Python adversarial lab: 3/3 tests passed
- TypeScript wallet SDK: 3/3 tests passed

## Demo result
The bundled C++ fixture returns `BLOCK`, disagreement entropy `0.996246`, and identifies `router-upgrade` as a counterexample with a minimum-output violation plus unlimited approval.

The deterministic Python lab generates 64 worlds, finds 2 policy-breaking worlds, and selects `world-41` as the minimum-perturbation counterexample in that fixture.

## Not verified in this environment
The repository includes source-only research tracks for Rust, Zig, Lean 4 and Solidity. Their compilers/toolchains were unavailable, so this release does not claim those paths compile or pass tests.

## Security boundary
No release component handles seed phrases, private keys, password recovery, unauthorized signing, transaction broadcasting, or wallet-draining logic.
