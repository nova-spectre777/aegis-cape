<div align="center">

# AEGIS
### CAPE-Σ · Counterfactual Adversarial Post-State Envelope

**A defensive crypto-wallet transaction firewall that asks what a transaction could do across credible hostile execution worlds before the user signs it.**

</div>

AEGIS is an experimental, non-custodial wallet-security research platform. CAPE-Σ does not treat one successful simulation as proof of safety. It evaluates wallet-centered post-state changes across multiple credible worlds, searches for policy-breaking counterexamples, and blocks when one credible catastrophic outcome survives.

> **v0.1 status:** research foundation, not audited wallet infrastructure. It does not store keys, sign transactions, submit transactions, recover seeds, or attempt to bypass wallet access controls.

## Core idea

```text
User intent / semantic policy
            |
            v
      proposed action
            |
   +--------+---------+
   |        |         |
   v        v         v
world A   world B   world C ...
current   oracle    proxy/ordering/etc.
   |        |         |
   +--------+---------+
            v
   wallet post-state diffs
            |
            v
        CAPE-Σ
            |
   +--------+---------+
   |                  |
 no violation     counterexample
   |                  |
   v                  v
 ALLOW               BLOCK
```

## What CAPE-Σ checks in v0.1

- maximum asset loss
- minimum expected asset receive
- unlimited token approvals
- wallet owner changes
- module installation
- delegatecall use
- optional implementation/code-hash drift
- simulator/world disagreement
- minimum credible-world threshold

A credible catastrophic counterexample is **not averaged away** by hundreds of safe simulations.

## Verified implementation

| Layer | Language | Purpose |
|---|---|---|
| `engine-cpp/` | C++23 | reference solver, envelopes, entropy, minimal counterexample |
| `coordinator-go/` | Go | simulator quorum, policy digest, HTTP API |
| `adversary-python/` | Python | hostile-world generator and deterministic lab |
| `wallet-ts/` | TypeScript | wallet/browser policy SDK |

Research-only source tracks are included for Solidity, Rust, Zig, and Lean 4 because those toolchains were unavailable in the release environment.

## Example policy

```text
ETH loss       <= 1.01 ETH
USDC receive   >= 3300 USDC
unlimited approvals = forbidden
owner changes       = forbidden
module installs     = forbidden
delegatecall         = forbidden
```

One generated world may still look like:

```text
world: router-upgrade
ETH:  -1.0
USDC:  0
approval: USDC -> unknown spender = unlimited
```

CAPE-Σ returns `BLOCK` plus that counterexample instead of a generic risk percentage.

## Quick verification

```bash
./scripts/check_all.sh
```

Run the C++ demo:

```bash
cmake -S engine-cpp -B engine-cpp/build
cmake --build engine-cpp/build
./engine-cpp/build/aegis-cape
```

Run the adversarial lab:

```bash
PYTHONPATH=adversary-python python3 -m aegis_lab.cli benchmark --seed 7 --count 64
```

## Defensive boundary

AEGIS intentionally contains **no seed-phrase handling, private-key extraction, password cracking, unauthorized signing, drainer logic, or transaction broadcasting**. It reasons about state changes before authorization.

See `docs/ALGORITHM.md`, `docs/THREAT_MODEL.md`, and `docs/ROADMAP.md`.
