module Excercise5 where
import ForSyDe.Shallow
--5a
switch :: Signal Bool -> Signal Int -> (Signal Int, Signal Int)
switch control input = (t, f) where
    (t, f) = switchKernel (switchControl control) input 

switchKernel :: Signal (Int, (Int, Int), [a] -> ([b], [c])) -> Signal a -> (Signal b, Signal c)
switchKernel = kernel12SADF

switchControl :: Signal Bool -> Signal (Int, (Int, Int), [Int] -> ([Int], [Int]))
switchControl = detector11SADF consumeRate nextState selectScenario initialState where
    consumeRate = 1
    nextState _ [True] = 1
    nextState _ [False] = 0
    trueScenario_1 = (1,(1, 0), \[x] -> ([x], []))
    falseScenario_0 = (1,(0, 1), \[x] -> ([], [x]))
    selectScenario 1 = (1, [trueScenario_1])
    selectScenario 0 = (1, [falseScenario_0])
    initialState = 0

--5a
select control in1 in2 = out where
    out = selectKernel (selectControl control) in1 in2

selectKernel = kernel21SADF

selectControl = detector11SADF consumeRate nextState selectScenario initialState where
    consumeRate = 1
    nextState _ [True] = 1
    nextState _ [False] = 0
    fTrue [x] [] = [x]
    fFalse [] [x] = [x]
    trueScenario_1 = ((1, 0), 1, fTrue)
    falseScenario_0 = ((0, 1), 1, fFalse)
    selectScenario 1 = (1, [trueScenario_1])
    selectScenario 0 = (1, [falseScenario_0])
    initialState = 0

--5b
bdfGraph :: Signal Int -> Signal Bool -> Signal Int
bdfGraph s_a s_b = s_c where
    (switchOutTrue, switchOutFalse) = switch s_b s_a
    ident = actorC switchOutTrue
    neg = actorD switchOutFalse
    s_c = select s_b ident neg

actorC :: Signal Int -> Signal Int
actorC = actor11SDF 1 1 (\[x] -> [x])

actorD :: Signal Int -> Signal Int
actorD = actor11SDF 1 1 (\[x] -> [-x])