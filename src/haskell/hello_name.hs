# 0 "/home/adam/proj/github/lang-comparision/src/hello_name/haskell.hs"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "/home/adam/proj/github/lang-comparision/src/hello_name/haskell.hs"
-- |This program takes in user input and says hello
-- Compile with: ghc --make haskell.hs

import System.IO
main = do
    putStr "Enter your name: "
    hFlush stdout
    name <- getLine
    putStrLn ("Hello " ++ name ++ "!\n")
