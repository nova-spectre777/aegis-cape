import test from 'node:test';import assert from 'node:assert/strict';import {assess,policyDigest,type WalletPolicy,type World} from '../src/index.js';
const p:WalletPolicy={assetRules:[{asset:'ETH',maximumLoss:1.01},{asset:'USDC',minimumDelta:3300}],denyUnlimitedApprovals:true,denyOwnerChange:true,denyModuleInstall:true,denyDelegatecall:true,minimumCredibleWorld:.5};
const ok:World={id:'ok',credibility:1,perturbationCost:0,assetDeltas:[{asset:'ETH',delta:-1},{asset:'USDC',delta:3400}],approvals:[],ownerChanged:false,moduleInstalled:false,delegatecallUsed:false};
test('allows safe worlds',()=>assert.equal(assess([ok],p).decision,'ALLOW'));
test('blocks adversarial approval',()=>{const evil={...ok,id:'evil',perturbationCost:.01,approvals:[{token:'USDC',spender:'x',unlimited:true}]};assert.equal(assess([ok,evil],p).decision,'BLOCK')});
test('stable digest',()=>assert.equal(policyDigest(p).length,64));
