module Main (main) where

import Lib
import Excercise2
import Excercise3
import Excercise4
import Excercise5
import Excercise8
import ForSyDe.Shallow
import SADF_Tutorial_Example

import Excercise4

-- 2b
-- main :: IO ()
-- main = print $ system (takeS 20 i_1) (takeS 5 i_2)

-- 2c
-- main :: IO()
-- main = print $ system2 i_1_finite i_2_finite

-- 3a
main :: IO()
main = print $ system5 $ signal [0..9]
