import {createHash} from 'node:crypto';
import type {WalletPolicy,World,Violation} from './types.js';
export function canonicalPolicy(policy:WalletPolicy):string{
 const normalized={...policy,assetRules:[...policy.assetRules].sort((a,b)=>a.asset.localeCompare(b.asset))};
 return JSON.stringify(normalized);
}
export function policyDigest(policy:WalletPolicy):string{return createHash('sha256').update(canonicalPolicy(policy)).digest('hex')}
export function assess(worlds:World[],policy:WalletPolicy){
 const violations:Violation[]=[];
 for(const w of worlds){if(w.credibility<policy.minimumCredibleWorld)continue;
  for(const r of policy.assetRules){const d=w.assetDeltas.find(x=>x.asset===r.asset)?.delta??0;if(r.minimumDelta!==undefined&&d<r.minimumDelta)violations.push({code:`MINIMUM_DELTA:${r.asset}`,world:w.id});if(r.maximumLoss!==undefined&&d < -r.maximumLoss)violations.push({code:`MAXIMUM_LOSS:${r.asset}`,world:w.id});}
  if(policy.denyUnlimitedApprovals&&w.approvals.some(a=>a.unlimited))violations.push({code:'UNLIMITED_APPROVAL',world:w.id});
  if(policy.denyOwnerChange&&w.ownerChanged)violations.push({code:'OWNER_CHANGE',world:w.id});
  if(policy.denyModuleInstall&&w.moduleInstalled)violations.push({code:'MODULE_INSTALL',world:w.id});
  if(policy.denyDelegatecall&&w.delegatecallUsed)violations.push({code:'DELEGATECALL',world:w.id});
 }
 const counterexample=[...violations].sort((a,b)=>(worlds.find(w=>w.id===a.world)?.perturbationCost??99)-(worlds.find(w=>w.id===b.world)?.perturbationCost??99))[0];
 return {decision:violations.length?'BLOCK':worlds.length?'ALLOW':'UNKNOWN',policyDigest:policyDigest(policy),counterexample:counterexample?.world,violations};
}
