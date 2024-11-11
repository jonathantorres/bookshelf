## Controlling access to objects

#### Answer #1
Option a) since `name` is not a method, is a getter for the `name` property.
***

#### Answer #2
The closure will allow us to access the private `_weapon` constant.
***

#### Answer #3
- `daimyo.clan === "Takasu"` passes
- `proxy.clan === "Tokugawa"` passes
- `daimyo.clan === "Takasu"` will not pass (this is the second call)
- `proxy.clan === "Tokugawa"` passes
***

#### Answer #4
- `daimyo.armySize === 1000` passes
- `proxy.armySize === 1000` passes
- `daimyo.armySize === "large"` will not pass
- `daimyo.armySize === "large"` will pass (since we updated the object directly)
***


