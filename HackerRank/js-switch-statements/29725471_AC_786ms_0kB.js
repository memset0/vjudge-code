const out = ['ONE', 'TWO', 'THREE', 'FOUR', 'FIVE', 'SIX', 'SEVEN', 'EIGHT', 'NINE'];
// console.log(!isNaN(num), !isNaN(parseInt(num)), String(num).length == 1, 1 <= parseInt(num), parseInt(num) <= 9);
if (!isNaN(num) && !isNaN(parseInt(num)) && String(num).length == 1 && 1 <= parseInt(num) && parseInt(num) <= 9) {
  console.log(out[parseInt(num) - 1]);
} else {
  console.log('PLEASE TRY AGAIN');
}