# numworks-nofrendo

A NES emulator for the NumWorks calculator, for v12 firmware

## Easy Installation

See here : https://zardam.github.io/webnofrendo/

## How to build

Connect the calculator to the computer, then

### For N100

```bash
git clone https://github.com/numworks/epsilon.git
cd epsilon
git clone -b v12-n110 https://github.com/zardam/numworks-nofrendo.git apps/nes
make MODEL=n0100 EPSILON_APPS='calculation graph code statistics probability solver sequence regression settings nes' epsilon.bin
cat your_nes_rom.nes >> output/release/device/n0100/epsilon.bin
dfu-util -i 0 -a 0 -s 0x08000000:leave -D output/release/device/n0100/epsilon.bin
```

### For N110

```bash
git clone https://github.com/numworks/epsilon.git
cd epsilon
git clone -b v12-n110 https://github.com/zardam/numworks-nofrendo.git apps/nes
make MODEL=n0110 EPSILON_APPS='calculation graph code statistics probability solver sequence regression settings nes' epsilon_flash
dfu-util -i 0 -a 0 -s 0x90400000:leave -D your_nes_rom.nes
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
