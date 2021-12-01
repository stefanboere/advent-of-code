module AdventOfCode
  ( module AdventOfCode
  ) where

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
