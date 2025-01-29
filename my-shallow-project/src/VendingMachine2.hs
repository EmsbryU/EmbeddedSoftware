module VendingMachine2 (vendingMachine) where

import ForSyDe.Shallow

data Coin = C5 | C10 deriving (Show, Eq, Ord)
data Bottle = B deriving (Show, Eq, Ord)
data Return = R deriving (Show, Eq, Ord)

type Coin_Event = AbstExt Coin
type Bottle_Event = AbstExt Bottle
type Return_Event = AbstExt Return

vendingMachine :: Signal Coin_Event -- Signal of Coins
               -> Signal (Bottle_Event, Return_Event) -- Signal of (Bottle, Return)

vendingMachine coin = res where
    lastFive = delaySDF [Abst] coin
    lastBottle = delaySDF [Abst] bottle
    (bottle, change) = allMightyVendingMachineOracle lastBottle lastFive coin
    res = zipSY bottle change

allMightyVendingMachineOracle :: Signal Bottle_Event -> Signal Coin_Event -> Signal Coin_Event -> (Signal Bottle_Event, Signal Return_Event)
allMightyVendingMachineOracle = actor32SDF (1,1,1) (1,1) f where
    f [Abst] [Prst C5] [Prst C10] = ([Prst B], [Prst R])
    f _ _ [Prst C10] = ([Prst B], [Abst])

    f [Abst] [Prst C5] [Prst C5] = ([Prst B], [Abst])
    f _ _ [Prst C5] = ([Abst], [Abst])

    f [Abst] [Prst C5] [Abst] = ([Abst], [Prst R])
    f _ _ _ = ([Abst], [Abst])

s_coin :: Signal (AbstExt Coin)
s_coin = signal [Prst C10, Prst C5, Prst C5, Prst C5, Prst C10, Abst]

-- >>> vendingMachine s_coin
-- {(B,_),(_,_),(B,_),(_,_),(B,R),(_,_)}

-- >>> unzipSY $ vendingMachine s_coin
-- ({B,_,B,_,B,_},{_,_,_,_,R,_})
