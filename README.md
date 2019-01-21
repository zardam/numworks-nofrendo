# numworks-nofrendo

A NES emulator for the NumWorks calculator

## Easy Installation

See here : https://zardam.github.io/webnofrendo/

## How to build

```bash
git clone https://github.com/numworks/epsilon.git
cd epsilon
git clone https://github.com/zardam/numworks-nofrendo.git apps/nes
make EPSILON_APPS='calculation graph code statistics probability solver sequence regression settings nes' epsilon.bin
cat your_nes_rom.nes >> epsilon.bin
make EPSILON_APPS='calculation graph code statistics probability solver sequence regression settings nes' epsilon_flash
```

## Controls

| Calculator | NES    |
|------------|--------|
| Up         | Up     |
| Down       | Down   |
| Left       | Left   |
| Right      | Right  |
| Back       | A      |
| OK         | B      |
| Up         | Start  |
| OnOff      | Select |
| BackSpace  | Reset  |
| Any other  | Exit   |
