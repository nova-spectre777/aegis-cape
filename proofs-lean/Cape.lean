structure Outcome where
  ethDelta : Int
  usdcDelta : Int

def Safe (o : Outcome) : Prop := o.ethDelta >= -101 ∧ o.usdcDelta >= 330000

theorem safe_example : Safe { ethDelta := -100, usdcDelta := 340000 } := by
  constructor <;> decide
