const { connect, wait } = require("./utils");
const WebSocket = require('ws')
const wss = new WebSocket.Server({ port: 8080 },()=>{
    console.log('Neurosity server started')
})
let i = 0;
const spinner = require("ora")().start();
spinner.info("Navigate to https://console.neurosity.co/ to access training data.");

wss.on('connection', function connection(ws) {
  var nb = 0;
(async () => {
  console.log('client connected')
  const mind = await connect();
  ws.send("open");
  isOpen = true;
  
  spinner.start(`Think about your right index finger`);
  function waiting(){
    console.log("\nopening...")
    ws.send("open");
    isOpen = true;
  }
  /*setTimeout(test, 2000);
  
  function test(){
    console.log("\n...Test..." + i);
    ws.send(i);
    i++;
    setTimeout(test, 2000);
  }
  ws.send("TEST");*/
  let intervalId = undefined;
  mind.kinesis("rightIndexFinger").subscribe(async (intent) => {
    //console.log(intent);
    if (intent.confidence >= 0.7&&intent.confidence < 0.99) {
      console.log("\nintent");
      if(isOpen){
        ws.send("close");
        console.log("\nclosing...")
      }

      isOpen = false;
      if(intervalId) {
        try {
          clearInterval(intervalId);
        } catch {}
      }
      intervalId = setTimeout(waiting,3000);
      
      
      
      
      
      
    
      //spinner.text = `Command detected. Awaiting confirmation=(conf=${intent.confidence})`;
      
    }
    
  });
})();
})
wss.on('listening',()=>{
  console.log('Port : 8080')
  console.log('Waiting any client')
})


