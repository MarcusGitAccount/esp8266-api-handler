
### Description

Simple application that uses an ultrasonic sensor connected to an ESP8266 board
to read and process the distance to the nearest object and send it to web clients.

### Installation

- download the repository
- open the board_logic project inside an IDE that supports Arduino development
- flash the code onto an ESP8266 WesMos board that has an HC-SR04 Ultrasonic sensor
connected to it(trigger on D1 and echo on D2, otherwise you will have to change the defines  from the beginning of the .ino file)
- go to https://distance-sensor.herokuapp.com to check the processed distance

### License

MIT
