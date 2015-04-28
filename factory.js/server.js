var net = require('net');
var fs = require('fs');
var path = '/tmp/echo.sock';
fs.unlink(path, function () {
  var server = net.createServer(function(c) {
    console.log('server connected');
    c.on('end', function() {
      console.log('server disconnected');
    });

    c.on('data', function (data) {
        console.log(data);
    });

    c.on('error', function (err) {
        console.log(err);
    });
    c.write('hello\r\n');
    c.pipe(c);
  });
  server.listen(path, function() {
    console.log('server bound on %s', path);
  });
});
