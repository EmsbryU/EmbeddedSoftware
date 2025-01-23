module Main (main) where

import Lib
import ForSyDe.Shallow

main :: IO ()
main = print $ aProcess (signal [1..10])
