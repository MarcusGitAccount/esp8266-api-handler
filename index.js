'use strict';

const path = require('path');

const express = require('express');
const ip = require('ip');
const bodyParser = require('body-parser');
const http = require('http');
const socket = require('socket.io');

const app = express();
const server = http.Server(app);
const io = socket(server);

app.set('case sensitive routing', false);
app.use(bodyParser.urlencoded({extended: true}));
app.use(bodyParser.json());

app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'index.html'));
})

app.post('/data', (req, res) => {
  const distance = req.body.distance;

  console.log('Data received: ', distance);

  io.emit('distance', {distance});
  res.send("The End.");
});

app.get('*', (req, res) => {
  res.status(404).send('Wrong way buddy');
})

const listener = server.listen(process.env.PORT || 5000, () => {
  const {address, port} = listener.address();

  console.log(`Server started on http://${address}:${port}`)
});