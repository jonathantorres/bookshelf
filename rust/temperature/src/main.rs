fn main() {
    let fahr:f32 = 85.0;
    let cel2:f32 = 53.0;
    let cel:f32 = to_cel(fahr);
    let fahr2:f32 = to_fahr(cel2);

    println!("F:{} = C:{}", fahr, cel);
    println!("C:{} = F:{}", cel2, fahr2);
}

fn to_cel(fahr:f32) -> f32 {
    (5.0/9.0) * (fahr-32.0)
}

fn to_fahr(cel:f32) -> f32 {
    cel * (9.0/5.0) + 32.0
}
