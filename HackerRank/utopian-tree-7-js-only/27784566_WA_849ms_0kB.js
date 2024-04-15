function solve(limit) {
	let res = 1
	for (let i = 0; i < limit; i++) {
		if (i & 1) {
			res += 1;
		} else {
			res <<= 1;
		}
	}
	return res;
}

function processData(inputString) {
	let input = inputString.split('\n').map(parseInt).slice(1);
	input.forEach(number => {
		console.log(solve(number));
	});
} 

process.stdin.resume();
process.stdin.setEncoding("ascii");
_input = "";
process.stdin.on("data", function (input) {
	_input += input;
});

process.stdin.on("end", function () {
 processData(_input);
});