from __future__ import annotations
from dataclasses import dataclass, asdict
from random import Random

@dataclass(frozen=True)
class World:
    id: str
    simulator: str
    credibility: float
    perturbation_cost: float
    eth_delta: float
    usdc_delta: float
    unlimited_approval: bool = False
    owner_changed: bool = False
    delegatecall_used: bool = False
    codehash_changed: bool = False

    def to_wire(self):
        approvals = []
        if self.unlimited_approval:
            approvals.append({"token":"USDC","spender":"0xDEADBEEF","unlimited":True})
        return {
            "id": self.id,
            "simulator": self.simulator,
            "credibility": self.credibility,
            "perturbation_cost": self.perturbation_cost,
            "asset_deltas": [{"asset":"ETH","delta":self.eth_delta},{"asset":"USDC","delta":self.usdc_delta}],
            "approvals": approvals,
            "owner_changed": self.owner_changed,
            "module_installed": False,
            "delegatecall_used": self.delegatecall_used,
            "codehash_changed": self.codehash_changed,
        }

def generate(seed: int = 7, count: int = 64) -> list[World]:
    r = Random(seed)
    worlds=[World("baseline","sim-a",1.0,0.0,-1.0,3420.0)]
    for i in range(count-1):
        price_shift=r.uniform(-0.025,0.02)
        usdc=3420.0*(1+price_shift)
        worlds.append(World(
            f"world-{i}", f"sim-{i%3}", r.uniform(.65,1.0), abs(price_shift), -1.0-r.uniform(0,.006), usdc,
            unlimited_approval=(i==17),
            codehash_changed=(i in {17,41}),
            delegatecall_used=(i==41),
        ))
    return worlds
