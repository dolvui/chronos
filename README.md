# chronos

chronos will be a langague where each instruction modify the currents state and some keyword can reverse the state. This is a control flow langague.

## USAGE

stack:
- gcc or g++
- flex
- bison


```bash
git clone https://github.com/dolvui/chronos.git
cd chonos
mkdir build
cd build

# on nixos you can:
nix-shell ..

cmake .. && make
./chronos ../test.ch

```
___


## grammar:

### types `<TYPES>` :

#### `name` : `regex exp`

`VAR`  : [a-zA-Z_][a-zA-Z0-9-_]*

___

`BOOL`  : ("True"|"False")|(1|0)
`INT`   : [0-9]+
`FLOAT` : [0-9]*\.[0-9]+
`LIST`  : \[\] | [<TYPES_1> , ... ]

### Usage

`create` <VAR> = <BOOL> | <INT> | <FLOAT> | <LIST> [,<BOOL> : save state];


#### INT

create <VAR> = <INT>;

permitted operation:

<VAR> += <INT>;
<VAR> -= <INT>;
<VAR> *= <INT>;
<VAR> /= <INT>;
<VAR> ^= <INT>;

<VAR> += <VAR>;
<VAR> -= <VAR>;
<VAR> *= <VAR>;
<VAR> /= <VAR>;
<VAR> ^= <VAR>;

#### FLOAT

same as int

#### BOOL

create <VAR> = 0;
create <VAR> = 1;

create <VAR> = True;
create <VAR> = False;

#### LIST

not for now.

## STATE LOGIC

State are checkpoints on the flow of the program that can be influence by specific keyword.

- `save`
- `choose`
- `retro`
- `undo`
- `jmp`

### create a state

save <VAR>;

create a state named <VAR> and store it for future use.
also you can :

save <VAR> [<EXP>,...];

create a state named <VAR> and store it for future use, note that a lists of expression is passed with a list.
thoses expression are apply virtualy to the current state, then store.

### travel on state

suppose we saved 3 states: `state1` , `state2` , `state3`

you can go see each state to tests it;

choose state1 and state2;

or

choose [state1,state2,state3];

### undo instructions

you can reverse flow for n instructions , and also force value.

undo <INT>;
or
undo <INT> [<VAR>,..];

### retro to a state

you can come back to a state with:

retro <VAR>;

## code exemple:

```
create a = 1;
create b = 1;

save state1 [create d = a ; a+= b;b = c ];

create c = a + b;
print(c)

retro state1;

create c = a + b;
print(c)

```
