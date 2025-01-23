{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use camelCase" #-}
module SDF_Application where

import ForSyDe.Shallow

system :: Signal Int -> Signal Int -> Signal Int
system s_in1 s_in2 = s_out where
  s_1 = actor_a s_in1
  s_2 = actor_b s_in2
  s_3 = actor_c s_1 s_4_delayed
  (s_4, s_out) = actor_d s_2 s_3
  s_4_delayed = delaySDF [0] s_4

-- 2c
system2 :: Signal Int -> Signal Int -> (Signal Int, Signal Int, Signal Int, Signal Int, Signal Int, Signal Int)
system2 s_in1 s_in2 = (s_out,s_1,s_2,s_3,s_4, s_4_delayed) where
  s_1 = actor_a s_in1
  s_2 = actor_b s_in2
  s_3 = actor_c s_1 s_4_delayed
  (s_4, s_out) = actor_d s_2 s_3
  s_4_delayed = delaySDF [0] s_4

actor_a :: Signal Int -> Signal Int
actor_a = actor11SDF 2 1 f_1 where
  f_1 [x, y] = [x + y]

actor_b :: Signal Int -> Signal Int
actor_b = actor11SDF 1 2 f_2 where
  f_2 [x] = [x, x+1]

actor_c :: Signal Int -> Signal Int -> Signal Int
actor_c = actor21SDF (2,1) 1 f_3 where
  f_3 [x, y] [z] = [x + y + z]

actor_d :: Signal Int -> Signal Int -> (Signal Int, Signal Int)
actor_d = actor22SDF (2,1) (1,2) f_4 where
  f_4 [x, y] [z] = ([x + y + z], [x + y, x + y + z])

-- 2b
i_1:: Signal Int
i_1 = infiniteS (+1) 0

i_2 :: Signal Int
i_2 = infiniteS (+10) 0

-- 2c
i_1_finite :: Signal Int
i_1_finite = signal [0..9]
i_2_finite :: Signal Int
i_2_finite = signal [0,10..90]
