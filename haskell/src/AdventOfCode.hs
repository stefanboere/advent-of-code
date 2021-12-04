{-# LANGUAGE DerivingStrategies #-}
module AdventOfCode
  ( module AdventOfCode
  ) where

import           Data.Char                      ( toUpper )
import           Data.Foldable                  ( foldl' )

ex01 :: IO (Int, Int)
ex01 = do
  ls <- map read . lines <$> readFile "../input/01"
  pure (ex01a_work ls, ex01b_work ls)

ex01_example :: [Int]
ex01_example = [199, 200, 208, 210, 200, 207, 240, 269, 260, 263]

ex01a_work :: [Int] -> Int
ex01a_work [] = 0
ex01a_work xs = length $ filter (uncurry (<)) $ zip xs (tail xs)

ex01b_work :: [Int] -> Int
ex01b_work []  = 0
ex01b_work [_] = 0
ex01b_work xs =
  let windowed = zipWith3 (\x y z -> x + y + z) xs (tail xs) (tail (tail xs))
  in  ex01a_work windowed

data Direction = Forward | Up | Down deriving stock (Show, Read)

ex02 :: IO (Int, Int)
ex02 = do
  ls <- map readln . lines <$> readFile "../input/02"
  pure (ex02a_work ls, ex02b_work ls)
 where
  readln ln = case words ln of
    [x : xs, y] -> (read (toUpper x : xs), read y)
    _           -> error "Parse error"

ex02_example :: [(Direction, Int)]
ex02_example =
  [(Forward, 5), (Down, 5), (Forward, 8), (Up, 3), (Down, 8), (Forward, 2)]

ex02a_work :: [(Direction, Int)] -> Int
ex02a_work lns = let (d, h) = foldr go (0, 0) lns in d * h
 where
  go (Forward, x) (d, h) = (d, h + x)
  go (Up     , x) (d, h) = (d - x, h)
  go (Down   , x) (d, h) = (d + x, h)

ex02b_work :: [(Direction, Int)] -> Int
ex02b_work lns = let (d, h, _) = foldl' go (0, 0, 0) lns in d * h
 where
  go (d, h, a) (Forward, x) = (d + x * a, h + x, a)
  go (d, h, a) (Up     , x) = (d, h, a - x)
  go (d, h, a) (Down   , x) = (d, h, a + x)
