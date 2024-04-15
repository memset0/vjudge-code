var _input = "";
var _output = "";
process.stdin.resume();
process.stdin.setEncoding("ascii");
process.stdin.on("data", function (input) {
  _input += input;
});
process.stdin.on("end", function () {
  var stdin = {
    source: _input,
    splited: _input.split(/\s+/),
    pointer: 0,
    readStr() {
      if (stdin.pointer == stdin.splited.length) {
        return null;
      }
      return stdin.splited[stdin.pointer++]
    },
    readInt() {
      if (stdin.pointer == stdin.splited.length) {
        return null;
      }
      return parseInt(stdin.splited[stdin.pointer++]);
    },
  };
  var stdout = {
    print(str) { _output += String(str); },
    println(str) { _output += String(str) + '\n'; },
  };
  main(stdin, stdout);
  if (_output && _output.length) {
    if (_output.endsWith('\n')) {
      _output = _output.slice(0, _output.length - 1);
    }
    console.log(_output);
  }
});

const utils = {
  assign1D(n) {
    let res = [];
    for (let i = 0; i < n; i++) {
      res.push(null);
    }
    return res;
  },
  assign2D(n, m) {
    let res = [];
    for (let i = 0; i < n; i++) {
      res.push([]);
      for (let j = 0; j < m; j++) {
        res[i].push(null);
      }
    }
    return res;
  },
};

function main(stdin, stdout) {
  let n = stdin.readInt(), S = stdin.readInt();
  let a = utils.assign1D(n);
  for (let i = 0; i < n; i++) {
    a[i] = stdin.readInt();
  }
  a.sort((x, y) => {
    return parseInt(x) - parseInt(y);
  });

  let ans = 0;
  for (let i = 0; i < n; i++)
    if (a[i] <= S) {
      S -= a[i];
      ++ans;
    }
  stdout.println(ans);
}