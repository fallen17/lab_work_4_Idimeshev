fn f(x: f64) -> f64 {
    x * (x + 1.0).ln() - 1.0
}

fn df(x: f64) -> f64 {
    (x + 1.0).ln() + x / (x + 1.0)
}

fn phi(x: f64) -> f64 {
    1.0 / (x + 1.0).ln()
}

fn bisection(mut a: f64, mut b: f64, eps: f64) {
    println!("\n--- BISECTION METHOD ---");
    println!("{:>5} {:>15} {:>15} {:>15}", "N", "an", "bn", "bn - an");
    println!("{}", "-".repeat(60));

    let mut n = 0;
    while (b - a) > eps {
        n += 1;
        let c = (a + b) / 2.0;
        println!("{:5} {:15.6} {:15.6} {:15.6}", n, a, b, b - a);

        if f(a) * f(c) < 0.0 {
            b = c;
        } else {
            a = c;
        }
    }
    println!("Result: Root = {:.6} | Iterations = {}", (a + b) / 2.0, n);
}

fn newton(x0: f64, eps: f64) {
    println!("\n--- NEWTON'S METHOD ---");
    println!("{:>5} {:>15} {:>15} {:>15}", "N", "Xn", "Xn+1", "|Xn+1 - Xn|");
    println!("{}", "-".repeat(60));

    let mut xn = x0;
    let mut n = 0;

    loop {
        n += 1;
        let x_next = xn - f(xn) / df(xn);
        let diff = (x_next - xn).abs();
        
        println!("{:5} {:15.6} {:15.6} {:15.6}", n, xn, x_next, diff);
        
        if diff < eps {
            println!("Result: Root = {:.6} | Iterations = {}", x_next, n);
            break;
        }
        xn = x_next;
    }
}

fn simple_iteration(x0: f64, eps: f64) {
    println!("\n--- SIMPLE ITERATION METHOD ---");
    println!("{:>5} {:>15} {:>15} {:>15}", "N", "Xn", "Xn+1", "|Xn+1 - Xn|");
    println!("{}", "-".repeat(60));

    let mut xn = x0;
    let mut n = 0;

    loop {
        n += 1;
        let x_next = phi(xn);
        let diff = (x_next - xn).abs();
        
        println!("{:5} {:15.6} {:15.6} {:15.6}", n, xn, x_next, diff);
        
        if diff < eps {
            println!("Result: Root = {:.6} | Iterations = {}", x_next, n);
            break;
        }
        xn = x_next;
    }
}

fn main() {
    let a = 1.0;
    let b = 2.0;
    let eps = 1e-4;

    bisection(a, b, eps);
    newton(b, eps);
    simple_iteration(1.5, eps);
}