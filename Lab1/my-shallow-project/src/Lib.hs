module Lib
    ( aProcess
    ) where

import ForSyDe.Shallow

aProcess :: Signal Integer -> Signal Integer
aProcess = mapSY (+1)

