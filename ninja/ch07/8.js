function Warrior(weapon) {
    this.weapon = weapon;
}

Warrior.prototype.wield = function() {
    return 'Wielding ' + this.weapon;
}

Warrior.duel = function (warrior1, warrior2) {
    return warrior1.wield() + ' ' + warrior2.wield();
}

let w1 = new Warrior('Sword');
let w2 = new Warrior('Knife');

console.log(w1.wield());
console.log(Warrior.duel(w1, w2));
