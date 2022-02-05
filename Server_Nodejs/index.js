const { connect, wait } = require("./utils");
const WebSocket = require('ws')
const wss = new WebSocket.Server({ port: 8080 },()=>{
    console.log('Neurosity server started')
})

const spinner = require("ora")().start();
spinner.info("Navigate to https://console.neurosity.co/ to access training data.");

wss.on('connection', function connection(ws) {
  var nb = 0;
(async () => {
  console.log('client connected')
  const mind = await connect();
  spinner.start(`Hand open`);
  
  mind.kinesis("rightIndexFinger").subscribe(async (intent) => {
    //console.log(intent);
    if (intent.confidence >= 0.7&&intent.confidence < 0.99) {
      ws.send("close");
      //console.log("\nHand closed")
      await wait(2000);
      ws.send("open");
    
      //spinner.text = `Command detected. Awaiting confirmation=(conf=${intent.confidence})`;
      
    }
    
  });
})();
})
wss.on('listening',()=>{
  console.log('Port : 8080')
  console.log('Waiting any client')
})


