## Functions for the Journeyman

#### Answer #1
See program in `1.js`, run it by doing: `node 1.js`.
***

#### Answer #2
`samurai = "Toyotomi"` and `ninja = "Fuma"`.
***

#### Answer #3
Only the second assertion will pass. `whoAmI2() === window`.
***

#### Answer #4
- `assert(ninja1.whoAmI() === ninja1, "ninja1?");` This assertion will pass.
- `assert(ninja2.whoAmI() === ninja1, "ninja1 again?");` This assertion will NOT pass.
- `assert(identify() === ninja1, "ninja1 again?");` This assertion will NOT pass.
- `assert(ninja1.whoAmI.call(ninja2) === ninja2, "ninja2 here?");` This assertion will pass.
***

#### Answer #5
Only the first assertion will pass. `ninja1.whoAmI() === ninja1`.
***

#### Answer #6
Only the first assertion will pass. `ninja1.whoAmI() === ninja1`.
***
