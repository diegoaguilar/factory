var net = require('net');
var fs = require('fs');
var path = '/tmp/echo.sock';
fs.unlink(path, function () {
  var server = net.createServer(function(c) {
    console.log('server connected');

  });


    server.on('end', function() {
      console.log('server disconnected');
    });

    server.on('data', function (data) {
        console.log(data);
    });

    server.on('error', function (err) {
        console.log(err);
    });
    server.write('hello\r\n');
    server.pipe(c);
});
