import argparse,json
from .benchmark import evaluate
from .worlds import generate

def main():
 p=argparse.ArgumentParser();sub=p.add_subparsers(dest="cmd",required=True)
 b=sub.add_parser("benchmark");b.add_argument("--seed",type=int,default=7);b.add_argument("--count",type=int,default=64)
 e=sub.add_parser("worlds");e.add_argument("--seed",type=int,default=7);e.add_argument("--count",type=int,default=8)
 a=p.parse_args()
 if a.cmd=="benchmark": print(json.dumps(evaluate(a.seed,a.count),indent=2))
 else: print(json.dumps([w.to_wire() for w in generate(a.seed,a.count)],indent=2))
if __name__=="__main__":main()
