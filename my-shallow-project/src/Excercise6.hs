module Excercise6 where
import ForSyDe.Shallow

bonusSystem :: Signal Int -> Signal Int
bonusSystem s_in = s_out where
    s_out = actor c1 s_in
    c1 = speedController (delaySADF [15] s_out)

actor = kernel11SADF

speedController :: Signal Int -> Signal (Int, Int, [Int] -> [Int])
speedController = detector11SADF consumeRate nextState selectScenario initialState where
    consumeRate = 1
    nextState state [lastres] 
        | lastres > 20 = 1
        | lastres < 10 = 0
        | otherwise = state 

    fastScenario_1 = (2, 1, \x -> [sum x])
    slowScenario_0 = (3, 1, \x -> [sum x])
    selectScenario 1 = (1, [fastScenario_1])
    selectScenario 0 = (1, [slowScenario_0])
    initialState = 0

-- >>> bonusSystem (signal [4,5,6,8,8,9,9,8,2,4,8,5,2])
-- {15,25,17,6,15}
