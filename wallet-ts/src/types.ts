export type AssetRule={asset:string;minimumDelta?:number;maximumLoss?:number};
export type WalletPolicy={assetRules:AssetRule[];denyUnlimitedApprovals:boolean;denyOwnerChange:boolean;denyModuleInstall:boolean;denyDelegatecall:boolean;minimumCredibleWorld:number};
export type World={id:string;credibility:number;perturbationCost:number;assetDeltas:{asset:string;delta:number}[];approvals:{token:string;spender:string;unlimited:boolean}[];ownerChanged:boolean;moduleInstalled:boolean;delegatecallUsed:boolean};
export type Violation={code:string;world:string};
