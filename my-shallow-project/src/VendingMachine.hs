module VendingMachine (vendingMachine) where

import ForSyDe.Shallow

vendingMachine :: Signal Bool -- Signal of 5 SEK coins
               -> Signal Bool -- Signal of 10 SEK coins
               -> Signal (Bool, Bool) -- Signal of (Bottle, Return)
vendingMachine fiveCoin tenCoin = res where
    lastFive = delaySDF [False] fiveCoin
    lastBottle = delaySDF [False] bottle
    (bottle, change) = allMightyVendingMachineOracle lastBottle lastFive fiveCoin tenCoin
    res = zipSY bottle change
allMightyVendingMachineOracle :: Signal Bool -> Signal Bool -> Signal Bool -> Signal Bool -> (Signal Bool, Signal Bool)
allMightyVendingMachineOracle = actor42SDF (1,1,1,1) (1,1) f where
    --10 coin inserted
    f [False] [True] [False] [True] = ([True], [True])
    f [False] [False] [False] [True] = ([True], [False])
    f [True] [False] [False] [True] = ([True], [False])
    f [True] [True] [False] [True] = ([True], [False])
    --5 coin inserted
    f [False] [True] [True] [False] = ([True], [False])
    f [False] [False] [True] [False] = ([False], [False])
    f [True] [False] [True] [False] = ([False], [False])
    f [True] [True] [True] [False] = ([False], [False])
    --nothing inserted
    f [False] [True] [False] [False] = ([False], [True])
    f _ _ _ _ = ([False], [False])

s_coin5 :: Signal Bool
s_coin5 =  signal [False, True, True, True, False, False]
s_coin10 :: Signal Bool
s_coin10 = signal [True, False, False, False, True, False]


-- >>> vendingMachine s_coin5 s_coin10

-- >>> unzipSY $ vendingMachine s_coin5 s_coin10
-- ({True,False,True,False,True,False},{False,False,False,False,True,False})


