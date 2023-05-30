const {exec, execSync} = require("child_process")
const {readFileSync,writeFileSync} = require("fs")

while(true){

    const bytes = readFileSync("Example.sav")

    const checkSumHex = bytes[2].toString(16)+""+bytes[1].toString(16)
    const checkSum = parseInt(checkSumHex,16)
    const file = parseInt(bytes[0].toString(16),16)

    if(checkSum==12345){

        

    console.log("Check sum: "+checkSum);
    console.log("Check sum: "+file);

    bytes[1]=0;
    bytes[2]=0;

    writeFileSync("Example.sav",bytes)

    try {
        if(file==0)execSync("C:\\Emulicious\\Emulicious.exe 1942.gb")
        else execSync("C:\\Emulicious\\Emulicious.exe tetris.gb")
    }catch(e){
        console.log(e)
    }

    }else{

        try {
            execSync("C:\\Emulicious\\Emulicious.exe Example.gb");
        }catch(e){
            console.log(e)
        }
    }

}