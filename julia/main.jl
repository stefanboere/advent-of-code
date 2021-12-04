using DelimitedFiles

ex01_example = [199, 200, 208, 210, 200, 207, 240, 269, 260, 263]
ex01_input = readdlm("../input/01", '\t', Int, '\n')[:]

ex01a_work(xs) = sum(xs[2:end] .> xs[1:end-1])
ex01b_work(xs) = sum(xs[4:end] .> xs[1:end-3])
ex01(xs) = (ex01a_work(xs), ex01b_work(xs))

