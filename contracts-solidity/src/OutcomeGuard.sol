// SPDX-License-Identifier: MIT
pragma solidity ^0.8.24;

/// @notice Research-only outcome commitment helper. It stores no keys and cannot move funds.
contract OutcomeGuard {
    struct Commitment { bytes32 policyHash; bytes32 envelopeRoot; uint64 validUntil; }
    mapping(bytes32 => Commitment) public commitments;
    event CommitmentRegistered(bytes32 indexed id, bytes32 policyHash, bytes32 envelopeRoot, uint64 validUntil);
    function register(bytes32 id, bytes32 policyHash, bytes32 envelopeRoot, uint64 validUntil) external {
        require(validUntil > block.timestamp, "expired");
        commitments[id] = Commitment(policyHash, envelopeRoot, validUntil);
        emit CommitmentRegistered(id, policyHash, envelopeRoot, validUntil);
    }
    function valid(bytes32 id, bytes32 policyHash, bytes32 envelopeRoot) external view returns (bool) {
        Commitment memory c=commitments[id];
        return c.validUntil >= block.timestamp && c.policyHash==policyHash && c.envelopeRoot==envelopeRoot;
    }
}
