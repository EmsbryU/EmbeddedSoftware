module Excercise4 where
import ForSyDe.Shallow

system5 :: Signal Int -> (Signal Int, Signal Int)
system5 s_in = (s_out_1, s_out_2) where
    (s_out_1, s_out_2) = k_1 c_1 s_in
    c_1 = d_1 s_in
    
-- Kernel 'k_1'
k_1 :: Signal (Int, (Int, Int), [a] -> ([b], [c])) -> Signal a -> (Signal b, Signal c)
k_1 = kernel12SADF
-- Detector 'd_1'
-- - starts in state 0
-- - alternates between state 0 and 1
-- - ignores input data value
-- - executes scenario 0 in state 0
-- - executes scenario 1 in state 1
d_1 :: Signal a -> Signal (Int, (Int, Int), [Int] -> ([Int], [Int]))
d_1 = detector11SADF consume_rate next_state select_scenario initial_state where
    consume_rate = 1
    -- Next State Function 'next_state' ignores input value
    next_state 0 _ = 1
    next_state 1 _ = 0
    -- Definition of scenarios
    -- - Scenario 0: Send token
    k_1_scenario_0 = (1,(1, 0), \[x] -> ([x], []))
    -- - Scenario 1: Ignore token
    k_1_scenario_1 = (1,(0, 1), \[x] -> ([], [-x]))
    -- Function for Selection of scenarios
    select_scenario 0 = (1, [k_1_scenario_0])
    select_scenario 1 = (1, [k_1_scenario_1])
    -- Initial State
    initial_state = 0