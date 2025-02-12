module Test where

import ForSyDe.Shallow

f x = x + 1;

g = (+)

p_2 :: Signal (Vector Integer) -> Signal Integer
p_2 = mapSY (reduceV g . mapV f)

p_2' :: Signal (Vector Integer) -> Signal Integer
p_2' = mapSY (reduceV g) . zipxSY . mapV (mapSY (reduceV g)) . mapV (mapSY (mapV f)) . unzipxSY . mapSY (groupV 4)