var SerialPort = require("serialport").SerialPort;
var port=  new SerialPort("/dev/tty.usbmodem1421", {
	baudRate: 9600
});

var stdin = process.openStdin();
process.stdin.setRawMode(true);
stdin.setEncoding('utf8');


port.on("open", function () {
	var num = 0;
	stdin.on('data', function (key) {
		if (key ===  "\u0003") {
			console.log("exiting");
			process.exit();
		}
		// process.stdout.write('received: ' + key);
		if (key === 'k') {
			num = (num + 1) % 768;
		} else if (key === 'j') {
			num = (num - 1) % 768;
		} else if (key === '0') {
			num = 0;
		}
		port.write(num, function (err, result) {
			if (err) {
				console.log("error");
			}
			console.log("result: " + result + " actual: " + num);
		});
	});
});
