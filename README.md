
Simple application that uses an ultrasonic sensor connected to an ESP8266 board
to read and process the distance to the nearest object.

The ESP8266 is responsible to make an api call to the server and post the results it obtained.

Next the server, implemented in NodeJS, has to send the update to all the connected peers. SocketIO
library is used for this.

The application is hosted on heroku.