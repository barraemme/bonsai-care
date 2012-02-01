import QtQuick 1.0

XmlListModel {
    id: db

    source: 'resources/db.xml'
    query: "/items/item"

    XmlRole { name: "name"; query: "name/string()" }
    XmlRole { name: "sid"; query: "@id/number()" }
    XmlRole { name: "operations"; query: "operation" }

    function getDate(date) {

        var nowDate = new Date();
        var nyDate = new Date(date);

        var diffBetween = Math.abs(nowDate - nyDate);

        var num_years = Math.round(diffBetween/31536000000);
        var num_months = Math.round((diffBetween % 31536000000)/2628000000);
        var num_days = Math.round(((diffBetween % 31536000000) % 2628000000)/86400000);


        var dateString = "";

        if(num_days>0)
            dateString += num_days+" days, ";
        if(num_months>0)
            dateString += num_months+" months, ";
        if(num_years>0)
            dateString += num_years+" years ";

        return dateString;
    }

    function getName(id){
        db.query = "/items/item[@id="+id+"]";
        if(db.count>0)
            return db.get(0).name;
        return "";
    }
}
