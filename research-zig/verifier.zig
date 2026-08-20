const std=@import("std");
pub fn withinMaximumLoss(delta:f64,max_loss:f64) bool { return delta >= -max_loss; }
test "loss bound" { try std.testing.expect(withinMaximumLoss(-1.0,1.01)); }
