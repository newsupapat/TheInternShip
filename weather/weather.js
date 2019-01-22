
var convert = require('xml-js');
//       if (process.argv.length < 3) {
//   console.log('node ' + process.argv[1] + ' FILE PLEASE');
//   process.exit(1);
// }
if(process.argv[2]=="weather.xml"){
var fs = require('fs')
  , filename = process.argv[2];
fs.readFile(filename, 'utf8', function(err, data) {
  if (err) throw err;
  console.log(data);
});
}
else if(process.argv[2]=="weather.json"){
  var fs = require('fs')
    , filename = weather.xml;
  fs.readFile(filename, 'utf8', function(err, data) {
    if (err) throw err;
  var options = {compact: true,ignoreComment: true, spaces: 4,ignoreDeclaration:true,instructionHasAttributes:true,indentAttributes:true,attributesKey:'value'};
  var result1 = convert.xml2json(data, options);
  console.log(result1);
  });
}
