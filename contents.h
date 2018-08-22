//NÃO ALTERE ESSE ARQUIVO!!!!!

const char *data_update_js_str=" var x = setInterval(function() {\n\
        loadData(\"data.txt\",updateData)\n\
    }, 1000);\n\
\n\
function loadData(url, callback){\n\
    var xhttp = new XMLHttpRequest();\n\
\n\
    xhttp.onreadystatechange = function(){\n\
        if(this.readyState == 4 && this.status == 200){\n\
            callback.apply(xhttp);\n\
        }\n\
    };\n\
\n\
    xhttp.open(\"GET\", url, true);\n\
    xhttp.send();\n\
}\n\
\n\
function updateData(){\n\
    document.getElementById(\"data\").innerHTML = this.responseText;\n\
}\n\
\n\
function req(){\n\
    var xhttp = new XMLHttpRequest();\n\
    xhttp.open(\"GET\", \"Abre\", true);\n\
    xhttp.send();\n\
}\n\
\n\
function req2(){\n\
    var xhttp = new XMLHttpRequest();\n\
    xhttp.open(\"GET\", \"Fecha\", true);\n\
    xhttp.send();\n\
}\n\
\n\
function req3(){\n\
    var xhttp = new XMLHttpRequest();\n\
    xhttp.open(\"GET\", \"Metade\", true);\n\
    xhttp.send();\n\
}\n\
\n\
function abre(){\n\
    document.getElementById(\"Abre\").onclick = req;\n\
}\n\
\n\
document.addEventListener(\"DOMContentLoaded\", abre)\n\
\n\
function fecha(){\n\
    document.getElementById(\"Fecha\").onclick = req2;\n\
}\n\
\n\
document.addEventListener(\"DOMContentLoaded\", fecha)\n\
\n\
function metade(){\n\
    document.getElementById(\"Metade\").onclick = req3;\n\
}\n\
\n\
document.addEventListener(\"DOMContentLoaded\", metade)\n\
";
const char *index_html_str="<head>\n\
<script type=\"text/javascript\" src=\"data_update.js\" charset=\"utf-8\"></script>\n\
</head>\n\
<h1>Site de Testes NodeMCU</h1><h1>Servo:</h1> <h1 id=\"data\">\"\"</h1>\n\
<p><button id=\"Abre\">Abre</button></p>\n\
<p><button id=\"Fecha\">Fecha</button></p></p>\n\
<p><button id=\"Metade\">Metade</button></p>\n\
";
