
"use strict";

let Gprmc = require('./Gprmc.js');
let Gpgsa = require('./Gpgsa.js');
let Gpgga = require('./Gpgga.js');
let Gpgsv = require('./Gpgsv.js');
let GpgsvSatellite = require('./GpgsvSatellite.js');
let Gpgst = require('./Gpgst.js');
let Sentence = require('./Sentence.js');

module.exports = {
  Gprmc: Gprmc,
  Gpgsa: Gpgsa,
  Gpgga: Gpgga,
  Gpgsv: Gpgsv,
  GpgsvSatellite: GpgsvSatellite,
  Gpgst: Gpgst,
  Sentence: Sentence,
};
