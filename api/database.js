const mysql = require('mysql');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'root',
  password: 'WILMA2',
  database: 'qt_example'
});
module.exports = connection;