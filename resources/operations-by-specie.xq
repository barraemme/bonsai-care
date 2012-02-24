doc(inputDocument)//sun,
for $time in doc("forecast.xml")//tabular/time
    order by $time/@from
    return <time>
        { $time/@from }
        <symbol>
            { $time/symbol/@name, $time/symbol/@number }
        </symbol>
        <temperature>
            { $time/temperature/@value, $time/temperature/@unit }
        </temperature>
        </time>
