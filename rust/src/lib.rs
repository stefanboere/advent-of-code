use std::fs;

pub fn ex01() -> (i32, i32) {
    let contents = fs::read_to_string("../input/01")
            .expect("File not found");

    let mut lns: Vec<i32> = contents.lines().map(|x| x.parse().unwrap()).collect();

    let a = ex01a_work(&lns);
    let b = ex01b_work(&mut lns);
    (a,b)
}

fn ex01a_work(xs: &[i32]) -> i32 {
    let mut cnt = 0;

    if xs.len() > 0 {
    let mut prev = xs[0];
        for x in &xs[1..] {
            if prev < *x {
                cnt = cnt + 1;
            }
            prev = *x;
        }
    }

    cnt
}

fn ex01b_work(xs: &mut [i32]) -> i32 {

    if xs.len() >= 3 {
        let mut prev0 = xs[0];
        let mut prev1 = xs[1];
        for x in &mut xs[2..] {
            let prev2 = *x;
            *x = prev0 + prev1 + prev2;
            prev0 = prev1;
            prev1 = prev2
        }
        ex01a_work(&xs[2..])
    }
    else {
        0
    }
}


#[cfg(test)]
mod tests {
    use super::*;
    static EX01_EXAMPLE: [i32;10] = [199, 200, 208, 210, 200, 207, 240, 269, 260, 263];

    #[test]
    fn ex01a_example() {
        let result = ex01a_work(&EX01_EXAMPLE);
        assert_eq!(result, 7);
    }

    #[test]
    fn ex01b_example() {
        let result = ex01b_work(&mut EX01_EXAMPLE.clone());
        assert_eq!(result, 5);
    }

    #[test]
    fn ex01test() {
        let result = ex01();
        assert_eq!(result, (1665, 1702));
    }
}
