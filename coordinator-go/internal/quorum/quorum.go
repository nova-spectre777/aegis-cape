package quorum

import (
 "crypto/sha256"
 "encoding/hex"
 "encoding/json"
 "math"
 "sort"
 "github.com/nova-spectre777/aegis/coordinator-go/internal/model"
)

func PolicyDigest(p model.Policy) string {
 type kv struct{ K string `json:"k"`; V float64 `json:"v"` }
 type canon struct { Min []kv `json:"min"`; Max []kv `json:"max"`; DenyUnlimited bool `json:"deny_unlimited"`; DenyOwner bool `json:"deny_owner"`; DenyModule bool `json:"deny_module"`; DenyDelegate bool `json:"deny_delegate"`; MinCred float64 `json:"min_cred"` }
 c := canon{DenyUnlimited:p.DenyUnlimitedApprovals,DenyOwner:p.DenyOwnerChange,DenyModule:p.DenyModuleInstall,DenyDelegate:p.DenyDelegatecall,MinCred:p.MinimumCredibleWorld}
 for k,v := range p.MinimumDelta { c.Min=append(c.Min,kv{k,v}) }
 for k,v := range p.MaximumLoss { c.Max=append(c.Max,kv{k,v}) }
 sort.Slice(c.Min,func(i,j int)bool{return c.Min[i].K<c.Min[j].K}); sort.Slice(c.Max,func(i,j int)bool{return c.Max[i].K<c.Max[j].K})
 b,_:=json.Marshal(c); sum:=sha256.Sum256(b); return hex.EncodeToString(sum[:])
}

func violationsFor(w model.World,p model.Policy) []string {
 var violations []string
 for _,d:=range w.AssetDeltas {
   if min,ok:=p.MinimumDelta[d.Asset]; ok && d.Delta<min { violations=append(violations,"minimum_delta:"+d.Asset) }
   if max,ok:=p.MaximumLoss[d.Asset]; ok && d.Delta < -max { violations=append(violations,"maximum_loss:"+d.Asset) }
 }
 if p.DenyUnlimitedApprovals { for _,a:=range w.Approvals { if a.Unlimited { violations=append(violations,"unlimited_approval:"+a.Token) } } }
 if p.DenyOwnerChange && w.OwnerChanged { violations=append(violations,"owner_change") }
 if p.DenyModuleInstall && w.ModuleInstalled { violations=append(violations,"module_install") }
 if p.DenyDelegatecall && w.DelegatecallUsed { violations=append(violations,"delegatecall") }
 return violations
}

func Assess(req model.AssessmentRequest) model.AssessmentResponse {
 resp:=model.AssessmentResponse{Decision:"UNKNOWN",PolicyDigest:PolicyDigest(req.Policy)}
 signatures:=map[string]struct{}{}
 credible:=0
 bestCost:=math.Inf(1)
 for _,w:=range req.Worlds {
   if w.Credibility < req.Policy.MinimumCredibleWorld { continue }
   credible++
   sigb,_:=json.Marshal(struct{D []model.AssetDelta;A []model.ApprovalChange;O,M,G,C bool}{w.AssetDeltas,w.Approvals,w.OwnerChanged,w.ModuleInstalled,w.DelegatecallUsed,w.CodehashChanged})
   sum:=sha256.Sum256(sigb); signatures[hex.EncodeToString(sum[:])]=struct{}{}
   violations:=violationsFor(w,req.Policy)
   if len(violations)>0 && w.PerturbationCost<bestCost {
      bestCost=w.PerturbationCost
      resp.Counterexample=w.ID
      resp.Violations=violations
   }
 }
 resp.QuorumDivergence=len(signatures)>1
 if credible==0 { return resp }
 if resp.Counterexample!="" {resp.Decision="BLOCK"} else {resp.Decision="ALLOW"}
 return resp
}
