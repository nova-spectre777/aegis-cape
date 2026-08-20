# CAPE-Σ algorithm

CAPE-Σ evaluates a proposed wallet action against a set of independently produced or adversarially perturbed execution worlds.

1. Normalize the user's semantic policy into state-change invariants.
2. Generate or ingest simulation worlds.
3. Ignore worlds below an explicit credibility floor rather than silently averaging them in.
4. Convert each world into a wallet-centered post-state difference.
5. Test every credible world against every invariant.
6. If any credible world violates a critical invariant, block and return the lowest-perturbation counterexample.
7. Otherwise derive an observed post-state envelope and report disagreement entropy.
8. Bind policy/envelope metadata to a digest for later audit or smart-account integration.

A single credible catastrophic counterexample is sufficient to block. Probability is not used to average away catastrophic state changes.
