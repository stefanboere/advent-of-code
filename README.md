# Advent of code 2021

## Languages

Only the first few days have solutions in all languages; see below.
`a` means 'only part a'.

| Day | c++ | haskell | j | julia | lisp | perl | python | prolog | rust |
|-----|-----|---------|---|-------|------|------|--------|--------|------|
| 01  | x   | x       | x | x     | x    | x    | x      | x      | x    |
| 02  | x   | x       | x | x     | x    | x    | x      |        | x    |
| 03  | x   |         | a |       |      |      |        |        | x    |
| 04  | x   |         |   |       |      |      |        |        |      |
| 05  | x   |         |   |       |      |      |        |        |      |
| 06  | x   |         |   |       |      |      |        |        |      |
| 07  | x   |         |   |       |      |      |        |        |      |
| 08  | x   |         |   |       |      |      |        |        |      |
| 09  | x   |         |   |       |      |      |        |        |      |
| 10  | x   |         |   |       |      |      |        |        |      |
| 11  | x   |         |   |       |      |      |        |        |      |
| 12  | x   |         |   |       |      |      |        |        |      |
| 13  | x   |         |   |       |      |      |        |        |      |
| 14  | x   |         |   |       |      |      |        |        |      |
| 15  | x   |         |   |       |      |      |        |        |      |
| 16  | x   |         |   |       |      |      |        |        |      |
| 17  | x   |         |   |       |      |      |        |        |      |
| 18  | x   |         |   |       |      |      |        |        |      |
| 19  | x   |         |   |       |      |      |        |        |      |
| 20  | x   |         |   |       |      |      |        |        |      |
| 21  | x   |         |   |       |      |      |        |        |      |
| 22  | x   |         |   |       |      |      |        |        |      |
| 23  | x   |         |   |       |      |      |        |        |      |
| 24  | x   |         |   |       |      |      |        |        |      |
| 25  | x   |         |   |       |      |      |        |        |      |

## Running

If you use `nix` you can run `nix develop` (or use direnv)
to get a shell with all the required dependencies.
Then `cd` to the specific language folder
and run the following commands to execute the code.

| Language | Command |
|----------|---------|
| c++      | `cmake --build . && ./main` |
| haskell  | `cabal test` |
| j        | `jconsole main.ijs`, then type e.g. `ex01` |
| julia    | `julia`, type `include("main.jl")` and e.g. `ex01(ex01_input)` |
| lisp     | Send the entire Emacs buffer to SLIME |
| perl     | `./main.perl` |
| python   | `phython main.py` |
| prolog   | `swipl main.pl`, and type `ex01(A, B).` |
| rust     | `cargo check` |

