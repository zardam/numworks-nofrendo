# numworks-nofrendo

A NES emulator for the NumWorks calculator.

## How to build

Connect the calculator to the computer, then

### For N100

```bash
git clone https://github.com/numworks/epsilon.git
cd epsilon
git clone https://github.com/zardam/numworks-nofrendo.git apps/nes
make NES_ROM='<path_to_ROM>' MODEL=n0100 EPSILON_APPS='calculation graph code statistics probability solver sequence regression settings nes' epsilon_flash
```

### For N110

```bash
git clone https://github.com/numworks/epsilon.git
cd epsilon
git clone https://github.com/zardam/numworks-nofrendo.git apps/nes
make NES_ROM='<path_to_ROM>' MODEL=n0110 EPSILON_APPS='calculation graph code statistics probability solver sequence regression settings nes' epsilon_flash
```

## Controls

| Calculator | NES           |
|------------|---------------|
| Up         | Up            |
| Down       | Down          |
| Left       | Left          |
| Right      | Right         |
| Back       | A             |
| OK         | B             |
| Up         | Start         |
| OnOff      | Select        |
| BackSpace  | Reset         |
| Copy       | Save state    |
| Paste      | Restore state |
| Any other  | Exit          |
