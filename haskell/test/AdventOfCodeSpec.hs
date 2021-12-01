module AdventOfCodeSpec
  ( spec
  ) where

import           Test.Hspec

import           AdventOfCode

spec :: Spec
spec = do
  describe "01" $ do
    it "a_example" $ ex01a_work ex01_example `shouldBe` 7
    it "b_example" $ ex01b_work ex01_example `shouldBe` 5
    it "a,b" $ ex01 `shouldReturn` (1665, 1702)
