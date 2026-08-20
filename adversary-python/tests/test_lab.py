import unittest
from aegis_lab.worlds import generate
from aegis_lab.benchmark import evaluate
class LabTest(unittest.TestCase):
 def test_deterministic(self): self.assertEqual(generate(5,10),generate(5,10))
 def test_counterexample_exists(self):
  r=evaluate(7,64);self.assertEqual(r["decision"],"BLOCK");self.assertGreater(r["blocked_worlds"],0)
 def test_wire_has_no_secrets(self):
  x=generate(1,2)[0].to_wire();self.assertNotIn("private_key",str(x));self.assertNotIn("seed_phrase",str(x))
if __name__=="__main__":unittest.main()
