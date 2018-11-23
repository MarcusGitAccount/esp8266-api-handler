'use strict';

const express = require('express');
const ip = require('ip');
const bodyParser = require('body-parser');

const app = express();

app.set('case sensitive routing', false);
app.use(bodyParser.urlencoded({extended: true}));
app.use(bodyParser.json());

app.get('/', (req, res) => {
  res.send('Root page');
})

app.post('/data', (req, res) => {
  const distance = req.body.distance;

  console.log('Data received: ', distance);
  res.send("The End.");
});

app.get('*', (req, res) => {
  res.status(404).send('Wrong way buddy');
})

const listener = app.listen(process.env.PORT || 5000, () => {
  const {address, port} = listener.address();

  console.log(`Server started on http://${address}:${port}`)
});