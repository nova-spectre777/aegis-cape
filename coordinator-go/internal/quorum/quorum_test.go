package quorum
import("testing";"github.com/nova-spectre777/aegis/coordinator-go/internal/model")
func TestBlocksLowestPerturbationCounterexample(t *testing.T){
 p:=model.Policy{MinimumDelta:map[string]float64{"USDC":3300},MaximumLoss:map[string]float64{"ETH":1.01},DenyUnlimitedApprovals:true,MinimumCredibleWorld:0.5}
 req:=model.AssessmentRequest{TransactionID:"tx",Policy:p,Worlds:[]model.World{
  {ID:"ok",Credibility:1,AssetDeltas:[]model.AssetDelta{{"ETH",-1},{"USDC",3400}}},
  {ID:"bad-expensive",Credibility:.9,PerturbationCost:.4,AssetDeltas:[]model.AssetDelta{{"ETH",-1},{"USDC",0}}},
  {ID:"bad-minimal",Credibility:.9,PerturbationCost:.02,Approvals:[]model.ApprovalChange{{Token:"USDC",Spender:"x",Unlimited:true}}},
 }}
 r:=Assess(req); if r.Decision!="BLOCK"||r.Counterexample!="bad-minimal"{t.Fatalf("unexpected %#v",r)}
 if len(r.PolicyDigest)!=64{t.Fatal("bad digest")}
}
func TestAllowsSafe(t *testing.T){p:=model.Policy{MinimumCredibleWorld:.5}; r:=Assess(model.AssessmentRequest{Policy:p,Worlds:[]model.World{{ID:"ok",Credibility:1}}}); if r.Decision!="ALLOW"{t.Fatal(r.Decision)}}
func TestUnknownWithoutCredibleWorlds(t *testing.T){p:=model.Policy{MinimumCredibleWorld:.8}; r:=Assess(model.AssessmentRequest{Policy:p,Worlds:[]model.World{{ID:"low",Credibility:.1}}}); if r.Decision!="UNKNOWN"{t.Fatal(r.Decision)}}
