var fs = require('fs');
var data = fs.readFileSync('/dev/stdin');
var inputString = data.toString();
var input = inputString.trim().split('\n').slice(1);
for (var n of input) {
	var res = 1;
	for (var i = 0; i < n; i++) {
		if (i & 1) {
			res += 1;
		} else {
			res <<= 1;
		}
	}
	console.log(res);
}
process.exit();