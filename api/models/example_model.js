const database=require('../database');

const example_sql={

    getAllPeople: function(callback){
        return database.query('select * from person', 
        callback);
    },

    getOnePerson: function(id, callback){
        return database.query('select * from person where id_person=?',[id],
        callback);
    }
};

module.exports = example_sql;