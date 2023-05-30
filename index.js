const { exec, execSync } = require("child_process");
const { readFileSync, writeFileSync, readdir, existsSync} = require("fs");


const EMULATOR_PATH = process.env.EMULATOR_PATH || "C:\\Emulicious\\Emulicious.exe"

if(!existsSync("Example.gb")){
    execSync("make")
}

function runProgram(romFileNames){

while (true) {
  var bytes = null;
  
  if(!existsSync("Example.sav")){

    bytes = Buffer.alloc(32768)
    bytes.fill(255)
    
  }else{
    bytes= readFileSync("Example.sav");
  }

  const checkSumHex = bytes[2].toString(16) + "" + bytes[1].toString(16);
  const checkSum = parseInt(checkSumHex, 16);
  const file = parseInt(bytes[0].toString(16), 16);



  if (checkSum == 12345) {
    console.log(bytes)
    console.log("Check sum: " + checkSum);
    console.log("Check sum: " + file);

    bytes[1] = 0;
    bytes[2] = 0;

    writeFileSync("Example.sav", bytes);

    try {
        console.log("running: "+romFileNames[file])
        execSync(EMULATOR_PATH+" roms\\"+romFileNames[file]);
    } catch (e) {
      console.log(e);
    }
  } else {

    
    console.log("Got "+romFileNames.length+" roms");
    
    bytes[3] = romFileNames.length;

    for(var i=0;i<romFileNames.length;i++){

        var filename = romFileNames[i].toLowerCase()

        const len = Math.min(filename.length,20)

        bytes[4+i*21] = len

        for(var j=0;j<len;j++){

            const charCode = filename.charCodeAt(j)

            const index = 4+i*21+j+1

            if(charCode>='0'.charCodeAt(0)&&charCode<='9'.charCodeAt(0))bytes[index] = 48 + (charCode-'0'.charCodeAt(0))
            else if(charCode>='a'.charCodeAt(0)&&charCode<='z'.charCodeAt(0))bytes[index] = 97 + (charCode-'a'.charCodeAt(0))
            else bytes[index]  =0;


        }
        
    }

    console.log(bytes)
    writeFileSync("Example.sav", bytes);


    try {
      execSync(EMULATOR_PATH+" Example.gb");
    } catch (e) {
      console.log(e);
      return;
    }
  }
}

  }

  
const romFileNames = []

    readdir("roms", (err, files) => {
    files.forEach(file => {
        console.log(file)
        romFileNames.push(file);
    });
    runProgram(romFileNames);
  });
