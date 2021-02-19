process.stdin.resume();
process.stdin.setEncoding("ascii");
_input = "";
process.stdin.on("data", function (input) {
  _input += input;
});
process.stdin.on("end", function () {
  main(_input);
});

function main(input) {
  function assign1D(n) {
    let res = [];
    for (let i = 0; i < n; i++) {
      res.push(null);
    }
    return res;
  }
  function assign2D(n, m) {
    let res = [];
    for (let i = 0; i < n; i++) {
      res.push([]);
      for (let j = 0; j < m; j++) {
        res[i].push(null);
      }
    }
    return res;
  }

  const n = input.split('\n')[0];
  const m = input.split('\n')[1];
  let arr = assign2D(n, m);
  for (let i = 0; i < n; i++)
    for (let j = 0; j < m; j++) {
      arr[i][j] = parseInt(input.split('\n')[i + 2].split(' ')[j]);
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

  console.log(ans);
}