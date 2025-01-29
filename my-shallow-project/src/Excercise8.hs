module Excercise8 where
import ForSyDe.Shallow

smc :: Signal Int -> (Signal Int, Signal Int)
smc input = (x, y) where
    s_1 = p1 input x
    s_2 = p2 s_1
    s_3 = p3 s_2 s_4
    x =  delaySDF [0] s_3
    (y, s_4) =  p4 input

p1 :: Signal Int -> Signal Int -> Signal Int
p1 = actor21SDF (1,1) 1 f_1 where
    f_1 [x] [y] = [x + y]

p2 :: Signal Int -> Signal Int
p2 = actor11SDF 1 1 f_2 where
    f_2 [x] = [2*x]

p3 :: Signal Int -> Signal Int -> Signal Int
p3 = actor21SDF (1,1) 1 f_1 where
    f_1 [x] [y] = [x + y]

p4 :: Signal Int -> (Signal Int, Signal Int)
p4 = actor12SDF 1 (1,1) f_2 where
    f_2 [x] = ([x + 1], [x + 1])