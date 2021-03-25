const express = require('express');
const router = express.Router();
const example_sql = require('../models/example_model');

router.get('/allpeople',
    function(request,response){
        example_sql.getAllPeople(function(err, dbResult){
            if(err){
                response.json(err);
            }
            else {
                response.json(dbResult);
            }
        }
        )
    }
);

module.exports = router;