using DelimitedFiles

ex01_example = [199, 200, 208, 210, 200, 207, 240, 269, 260, 263]
ex01_input = readdlm("../input/01", '\t', Int, '\n')[:]

ex01a_work(xs) = sum(xs[2:end] .> xs[1:end-1])
ex01b_work(xs) = sum(xs[4:end] .> xs[1:end-3])
ex01(xs) = (ex01a_work(xs), ex01b_work(xs))


@enum Direction forward up down
ex02_example =
  [(forward, 5), (down, 5), (forward, 8), (up, 3), (down, 8), (forward, 2)]
ex02_input_raw = readdlm("../input/02", ' ')
parseDirection(x) = eval(Symbol(x))
ex02_input = tuple.(parseDirection.(ex02_input_raw[:,1]), ex02_input_raw[:,2])

function ex02a_diff(dir, x)
  if dir == forward
    [0, x]
  elseif dir == up
    [-x, 0]
  else
    [x, 0]
  end
end

ex02a_diff(x) = ex02a_diff(x...)
ex02a(xs) = prod(sum(ex02a_diff.(xs)))

function ex02b_diff((d,h,a), x)
  ah = ex02a_diff(x)
  (d + ah[2] * a, h + ah[2], a +ah[1])
end
ex02b(xs) = prod(foldl(ex02b_diff, xs, init=(0,0,0))[1:2])
ex02(xs) = (ex02a(xs), ex02b(xs))
