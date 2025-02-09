module Excercise3b where

import ForSyDe.Shallow


system3b :: Signal Int -> (Signal Int, Signal Int)
system3b s_in = (s_out1, s_out2) where
    s_out1 = a_2 s_1
    s_out2 = a_3 s_2
    (s_1, s_2) = a_1 s_in

a_1 :: Signal Int -> (Signal  Int, Signal Int)
a_1 = actor12SDF 1 (1,1) f_1 where
        f_1 [x] = ([x], [x])

a_2 :: Signal Int -> Signal Int
a_2 = actor11SDF 2 1 f_2 where
    f_2 [x, y] = [x]

a_3 :: Signal Int -> Signal Int
a_3 = actor11SDF 2 1 f_3 where
    f_3 [x, y] = [-y]

--- >>> system3b (takeS 11 (infiniteS (+1) 0))
-- ({0,2,4,6,8},{-1,-3,-5,-7,-9})
