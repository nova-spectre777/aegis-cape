from .worlds import generate

def evaluate(seed=7,count=64,min_usdc=3300,max_eth_loss=1.01):
    worlds=generate(seed,count)
    blocked=[]
    for w in worlds:
        reasons=[]
        if w.usdc_delta < min_usdc: reasons.append("minimum_usdc")
        if w.eth_delta < -max_eth_loss: reasons.append("maximum_eth_loss")
        if w.unlimited_approval: reasons.append("unlimited_approval")
        if w.owner_changed: reasons.append("owner_change")
        if w.delegatecall_used: reasons.append("delegatecall")
        if reasons: blocked.append((w,reasons))
    minimal=min(blocked,key=lambda x:x[0].perturbation_cost) if blocked else None
    return {"worlds":len(worlds),"blocked_worlds":len(blocked),"decision":"BLOCK" if blocked else "ALLOW","minimal_counterexample": minimal[0].id if minimal else None,"reasons":minimal[1] if minimal else []}
