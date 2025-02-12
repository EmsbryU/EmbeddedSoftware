module Test where

import ForSyDe.Shallow
import GHC.Real (reduce)

f x = x + 1;

g = (+)

p_2 :: Signal (Vector Integer) -> Signal Integer
p_2 = mapSY (reduceV g . mapV f)

p_2' :: Signal (Vector Integer) -> Signal Integer
p_2' = mapSY (reduceV g) . zipxSY . mapV (mapSY (reduceV g)) . mapV (mapSY (mapV f)) . unzipxSY . mapSY (groupV 4)

mapMatrix     = mapV . mapV
reduceMatrix f = reduceV f . mapV (reduceV f)


grayscale = mapMatrix (convert . fromVector) . mapV (groupV 3)
  where
    convert [r,g,b] = fromIntegral r * 0.3125
                    + fromIntegral g * 0.5625
                    + fromIntegral b * 0.125
    convert _ = error "X length is not a multiple of 3"