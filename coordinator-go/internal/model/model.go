package model

type AssetDelta struct { Asset string `json:"asset"`; Delta float64 `json:"delta"` }
type ApprovalChange struct { Token string `json:"token"`; Spender string `json:"spender"`; Unlimited bool `json:"unlimited"` }
type World struct {
 ID string `json:"id"`; Simulator string `json:"simulator"`; Credibility float64 `json:"credibility"`; PerturbationCost float64 `json:"perturbation_cost"`
 AssetDeltas []AssetDelta `json:"asset_deltas"`; Approvals []ApprovalChange `json:"approvals"`
 OwnerChanged bool `json:"owner_changed"`; ModuleInstalled bool `json:"module_installed"`; DelegatecallUsed bool `json:"delegatecall_used"`; CodehashChanged bool `json:"codehash_changed"`
}
type Policy struct { MinimumDelta map[string]float64 `json:"minimum_delta"`; MaximumLoss map[string]float64 `json:"maximum_loss"`; DenyUnlimitedApprovals bool `json:"deny_unlimited_approvals"`; DenyOwnerChange bool `json:"deny_owner_change"`; DenyModuleInstall bool `json:"deny_module_install"`; DenyDelegatecall bool `json:"deny_delegatecall"`; MinimumCredibleWorld float64 `json:"minimum_credible_world"` }
type AssessmentRequest struct { TransactionID string `json:"transaction_id"`; Worlds []World `json:"worlds"`; Policy Policy `json:"policy"` }
type AssessmentResponse struct { Decision string `json:"decision"`; Counterexample string `json:"counterexample,omitempty"`; Violations []string `json:"violations,omitempty"`; PolicyDigest string `json:"policy_digest"`; QuorumDivergence bool `json:"quorum_divergence"` }
