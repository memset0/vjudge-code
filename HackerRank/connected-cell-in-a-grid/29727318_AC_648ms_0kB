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
  process.exit(0);
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
  const { assign1D, assign2D } = utils;

  const n = stdin.readInt();
  const m = stdin.readInt();
  let arr = assign2D(n, m);
  for (let i = 0; i < n; i++)
    for (let j = 0; j < m; j++) {
      arr[i][j] = stdin.readInt();
    }

  let anc = assign1D(n * m);
  for (let i = 0; i < n * m; i++) {
    anc[i] = i;
  }
  function findAnc(u) {
    if (anc[u] == u) {
      return u;
    } else {
      return anc[u] = findAnc(anc[u]);
    }
  }

  for (let i = 0; i < n; i++)
    for (let j = 0; j < m; j++)
      if (arr[i][j] == 1) {
        for (const [deltaX, deltaY] of [[0, 1], [1, 0], [0, -1], [-1, 0], [1, 1], [1, -1], [-1, 1], [-1, -1]]) {
          x = i + deltaX, y = j + deltaY;
          if (x < 0 || y < 0 || x >= n || y >= m) continue;
          if (arr[x][y] != 1) continue;
          anc[findAnc(i * m + j)] = findAnc(x * m + y);
        }
      }
  
  let siz = assign1D(n * m);
  for (let i = 0; i < n; i++)
    for (let j = 0; j < m; j++)
      if (arr[i][j] == 1) {
        if (!siz[findAnc(i * m + j)]) {
          siz[findAnc(i * m + j)] = 0;
        }
        siz[findAnc(i * m + j)] += 1;
      }
  
  let ans = 0;
  for (let i = 0; i < n * m; i++)
    if (siz[i] && siz[i] > ans) {
      ans = siz[i];
    }

  stdout.println(ans);
}