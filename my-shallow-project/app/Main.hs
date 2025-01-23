module Main (main) where

import Lib
import SDF_Application
import Excercise3
import ForSyDe.Shallow

-- 2b
-- main :: IO ()
-- main = print $ system (takeS 20 i_1) (takeS 5 i_2)

-- 2c
-- main :: IO()
-- main = print $ system2 i_1_finite i_2_finite

-- 3a
main :: IO()
main = print $ system3 $ signal [0..9]
