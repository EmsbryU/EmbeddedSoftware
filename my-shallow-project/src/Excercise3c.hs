-- module Excercise3b where

-- import ForSyDe.Shallow


-- system3b :: Signal Int -> (Signal Int, Signal Int)
-- system3b s_in = (s_out1, s_out2) where
--     s_out1 = a_3 s_1
--     s_out2 = a_4 s_2
--     (s_1,c_1) = a_1 s_in (delaySDF[0] c_2)
--     (s_2, c_2) = a_2 s_in c_1

-- a_1 = actor22SDF (1,1) (1,1) f_1 where
--     f_1 [x] [y] = ([x], [y])

-- a_2 = actor22SDF (1,1) (1,1) f_1 where
--     f_1 [x] [y] = ([x], [y])

-- a_3 = actor11SDF 1 1 (\[x] -> [x])
-- a_4 = actor11SDF 1 1 (\[x] -> [-x])

module Excercise3c where

import ForSyDe.Shallow



system3b s_in = s_out1 where
    (s_out1, state) = a_3 s_in (delaySDF[0] state)

a_3 :: Signal Int -> Signal Int -> (Signal Int, Signal Int)
a_3 = actor22SDF (1,1) (1,1) f where
    f [x] [0] = ([x], [1])
    f [x] [1] = ([-x], [0])


-- >>> system3b (takeS 10 (infiniteS (+1) 0))
-- {0,-1,2,-3,4,-5,6,-7,8,-9}


--- >>> system3b (takeS 11 (infiniteS (+1) 0))
-- ({0,1,2,3,4,5,6,7,8,9,10},{0,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10})
