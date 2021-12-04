use std::fs;

enum Direction {
    Forward,
    Up,
    Down
}

pub fn ex02() -> (i32, i32) {
    let contents = fs::read_to_string("../input/02")
            .expect("File not found");

    let lns: Vec<(Direction, i32)> = contents.lines().map(parseln).collect();

    let a = ex02a_work(&lns);
    let b = ex02b_work(&lns);
    (a, b)
}

fn parseln(ln: &str) -> (Direction, i32) {
    let (xstr, ystr) = ln.split_once(' ').unwrap();
    let x = match xstr {
        "forward" => Some(Direction::Forward),
        "up" => Some(Direction::Up),
        "down" => Some(Direction::Down),
        _ => None
    }.unwrap();

    let y = ystr.parse().unwrap();
    (x, y)
}

fn ex02a_work(xs: &[(Direction, i32)]) -> i32 {

    let mut depth = 0;
    let mut hor = 0;
    for (dir, x) in xs {
        match dir {
          Direction::Forward => hor = hor + x,
          Direction::Up     => depth = depth - x,
          Direction::Down   => depth = depth + x
        }
    }

    depth * hor
}


fn ex02b_work(xs: &[(Direction, i32)]) -> i32 {

    let mut depth = 0;
    let mut hor = 0;
    let mut aim = 0;
    for (dir, x) in xs {
        match dir {
          Direction::Forward => {
              depth = depth + x * aim;
              hor = hor + x
          },
          Direction::Up     => aim = aim - x,
          Direction::Down   => aim = aim + x
        }
    }

    depth * hor
}


#[cfg(test)]
mod tests {
    use super::*;
    static EX02_EXAMPLE: [(Direction,i32);6] = [
        (Direction::Forward, 5),
        (Direction::Down, 5),
        (Direction::Forward, 8),
        (Direction::Up, 3),
        (Direction::Down, 8),
        (Direction::Forward, 2)
    ];

    #[test]
    fn ex02a_example() {
        let result = ex02a_work(&EX02_EXAMPLE);
        assert_eq!(result, 150);
    }

    #[test]
    fn ex02b_example() {
        let result = ex02b_work(&EX02_EXAMPLE);
        assert_eq!(result, 900);
    }

    #[test]
    fn ex02test() {
        let result = ex02();
        assert_eq!(result, (1815044, 1739283308));
    }
}
