{-# OPTIONS_GHC -Wno-incomplete-patterns #-}
module Excercise3 where

import ForSyDe.Shallow

system3 :: Signal Int -> (Signal Int, Signal Int)
system3 s_in = (s_out1, s_out2) where
    s_out1 = a_2 (half s_1)
    s_out2 = a_3 (half (0:-s_2))
    (s_1, s_2) = a_1 s_in

a_1 :: Signal Int -> (Signal  Int, Signal Int)
a_1 = actor12SDF 1 (1,1) f_1 where
        f_1 [x] = ([x], [x])

a_2 :: Signal Int -> Signal Int
a_2 = actor11SDF 1 1 f_2 where
    f_2 [x] = [x]

a_3 :: Signal Int -> Signal Int
a_3 = actor11SDF 1 1 f_3 where
    f_3 [x] = [-x]



half :: Signal Int -> Signal Int
half NullS = NullS
half (x:-xs) = x :- half (dropS 1 xs)
