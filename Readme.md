# GBKD Flashcart Experiment

How to Run:

(If Larold did everything correctly! :D )

> NodeJS is required for this program.

Set your favorite emulator's executable in an environment variable named `EMULATOR_PATH`
or just change this line at the start of index.js:

`const EMULATOR_PATH = process.env.EMULATOR_PATH || "C:\\Emulicious\\Emulicious.exe"`

Run the index.js file using nodejs

`node index`

From there, an (infinite until the main process ends) loop will start:

An example.gb will run that prompts to use left/right ot select a file.
The files listed will be from the "roms" folder

Press A to select a ROM, then you can close the emulator. When it closes, the given ROM file will run. After you close that emulator instance, the original will run again.

You can add up to 100 ROM files in the "roms" folder (although i've only tested 3)