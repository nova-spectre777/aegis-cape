# Threat model

AEGIS assumes a transaction request, simulation infrastructure, or target contract may be malicious or inconsistent. It therefore treats simulations as evidence rather than authority.

Protected properties include asset-loss limits, minimum receives, approvals, owner/module changes, delegatecall use, and implementation drift.

Out of scope: seed recovery, key extraction, password cracking, signing without user authorization, transaction submission, wallet draining, and bypassing access controls.
