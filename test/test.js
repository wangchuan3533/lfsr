var lfsr = require('../build/Release/lfsr');
var chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';

function num2str(n) {
  var str = '';
  for (var i = 0; i < 8; i++) {
    var rem = n % 16;
    str += chars[rem + 5];
    n = parseInt(n / 16);
  }
  return str;
}

var current = 1;
for (var i = 0; i < 65536; i++) {
  console.log(num2str(current));
  //console.log(current);
  current = lfsr.next(current);
}
