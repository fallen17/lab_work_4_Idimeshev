use std::collections::HashMap;
use std::io::{self, Write};

fn bord_method(n: usize, k: usize, names: &[String], votes: &[Vec<usize>]) {
    let mut scores = vec![0; n];

    for i in 0..k {
        for j in 0..n {
            let candidate_idx = votes[i][j];
            scores[candidate_idx] += n - 1 - j;
        }
    }

    println!("--- Bord method ---");
    let mut max_score = 0;
    for i in 0..n {
        println!("{}: {} Points", names[i], scores[i]);
        if scores[i] > max_score {
            max_score = scores[i];
        }
    }

    print!("Bord's winner: ");
    for i in 0..n {
        if scores[i] == max_score {
            print!("{} ", names[i]);
        }
    }
    println!("\n");
}

fn kondorce_method(n: usize, k: usize, names: &[String], votes: &[Vec<usize>]) {
    let mut wins = vec![vec![0; n]; n];

    for v in 0..k {
        for i in 0..n {
            for j in (i + 1)..n {
                let sup = votes[v][i];
                let inf = votes[v][j];
                wins[sup][inf] += 1;
            }
        }
    }

    println!("--- Kondorce method ---");
    let mut winner_idx: Option<usize> = None;

    for i in 0..n {
        let mut is_kondorce_winner = true;
        for j in 0..n {
            if i == j {
                continue;
            }
            if wins[i][j] <= wins[j][i] {
                is_kondorce_winner = false;
                break;
            }
        }
        if is_kondorce_winner {
            winner_idx = Some(i);
            break;
        }
    }

    match winner_idx {
        Some(idx) => println!("Kondorce's winner: {}", names[idx]),
        None => println!("There's no Kondorce's winner..."),
    }
}

fn main() {
    let read_input = || -> String {
        let mut input = String::new();
        io::stdin().read_line(&mut input).expect("Failed to read line");
        input.trim().to_string()
    };

    print!("Type in amount of candidates... : ");
    io::stdout().flush().unwrap();
    let n: usize = read_input().parse().expect("Please type a number");

    let mut names = Vec::with_capacity(n);
    let mut name_to_index = HashMap::new();

    println!("Write candidates' names (in space):");
    let names_line = read_input();
    for (i, name) in names_line.split_whitespace().enumerate().take(n) {
        let name_str = name.to_string();
        name_to_index.insert(name_str.clone(), i);
        names.push(name_str);
    }

    print!("Type in amount of voters: ");
    io::stdout().flush().unwrap();
    let k: usize = read_input().parse().expect("Please type a number");

    let mut votes = vec![vec![0; n]; k];

    println!("Type in voter priority (name-chain):");
    for i in 0..k {
        print!("Voter {}: ", i + 1);
        io::stdout().flush().unwrap();
        let vote_line = read_input();
        let voter_prefs: Vec<&str> = vote_line.split_whitespace().collect();
        
        for j in 0..n {
            let name = voter_prefs[j];
            votes[i][j] = *name_to_index.get(name).expect("Candidate name not found");
        }
    }

    println!();
    bord_method(n, k, &names, &votes);
    kondorce_method(n, k, &names, &votes);

}