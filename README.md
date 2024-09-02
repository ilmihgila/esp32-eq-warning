# esp32 Earthquake Warning
## Preview & schematic
<div style="display: flex;">
  <img src="https://github.com/user-attachments/assets/b1457896-1189-4bb4-b5ef-d626a371a4e0" alt="full image" width="50%">
  <img src="https://github.com/user-attachments/assets/bfb2ec00-e055-4c95-961e-87a22a2a8128" alt="LED" width="35%">
</div>
<img src="https://github.com/user-attachments/assets/6769e262-8ef3-479b-a241-9025d38b095b" alt="LED" width="45%">

## Intro
Example usage of esp32 http request on BMKG API (no key requiered as of August 2024)

This example use builtin led and (optional) speaker for earthquake warning

An (optional) led is used for the recording date, place and other usefull information of the earthquake


## What you need
1. Esp32 (i use esp-wroom-32 devkit on this project). Any board with wifi module should also work
2. (optional) Led display (i use 124 * 64 OLED display). Consider using bigger display than mine
3. (optional) speaker (i use buzzer). Consider using 3.3-5v speaker with mp3 player module

## What to improve?
- [X] idk :(

## Thanks!
1. Arduino community and everyone who work on those library that i used
2. BMKG
