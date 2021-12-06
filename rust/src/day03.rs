use std::fs;

pub fn ex03() -> (i32, i32) {
    let contents = fs::read_to_string("../input/03").expect("File not found");

    let lns: Vec<i32> = contents
        .lines()
        .map(|x| i32::from_str_radix(x, 2).unwrap())
        .collect();

    let a = ex03a_work(&lns, 12);
    let b = ex03b_work(&lns, 12);
    (a, b)
}

fn ex03a_work(xs: &[i32], sz: usize) -> i32 {
    let mut diffs: Vec<i32> = vec![];
    diffs.resize(sz, 0);

    for x in xs {
        for (i, d) in diffs.iter_mut().enumerate() {
            let xmask: i32 = x & (1 << i);
            if xmask == 0 {
                *d = *d - 1;
            } else {
                *d = *d + 1;
            }
        }
    }

    let mut gamma = 0;
    let mut epsilon = 0;
    for (i, d) in diffs.iter().enumerate() {
        if *d > 0 {
            gamma = gamma | 1 << i;
        } else {
            epsilon = epsilon | 1 << i;
        }
    }
    return gamma * epsilon;
}

fn ex03b_work(xs: &[i32], sz: i32) -> i32 {
    if let Some(oxygen) = ex03b_filter_crit(xs, true, sz - 1).first() {
        if let Some(co2) = ex03b_filter_crit(xs, false, sz - 1).first() {
            oxygen * co2
        } else {
            0
        }
    } else {
        0
    }
}

fn ex03b_filter_crit(xs: &[i32], keep: bool, column: i32) -> Vec<i32> {
    if xs.len() <= 1 || column < 0 {
        xs.to_vec()
    } else {
        let mut diff = 0;
        for x in xs {
            let xmask = x & (1 << column);
            diff = diff + if xmask == 0 { -1 } else { 1 };
        }

        let to_int = |x| {
            if x {
                1
            } else {
                0
            }
        };
        let tokeep = if diff >= 0 {
            to_int(keep)
        } else {
            to_int(!keep)
        };

        let xfiltered = xs
            .iter()
            .filter(|&&x| {
                let xcol = x >> column & 1;
                xcol == tokeep
            })
            .cloned()
            .collect::<Vec<i32>>();
        ex03b_filter_crit(&xfiltered, keep, column - 1)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    static EX03_EXAMPLE: [i32; 12] = [
        0b00100, 0b11110, 0b10110, 0b10111, 0b10101, 0b01111, 0b00111, 0b11100, 0b10000, 0b11001,
        0b00010, 0b01010,
    ];

    #[test]
    fn ex03a_example() {
        let result = ex03a_work(&EX03_EXAMPLE, 5);
        assert_eq!(result, 198);
    }

    #[test]
    fn ex02b_example() {
        let result = ex03b_work(&EX03_EXAMPLE, 5);
        assert_eq!(result, 230);
    }

    #[test]
    fn ex02test() {
        let result = ex03();
        assert_eq!(result, (3687446, 4406844));
    }
}
