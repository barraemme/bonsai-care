//include the dicionary of kanjis
Qt.include("dictionary.js")

// Switches to the application given by appName.
// The application is loaded by setting the source
// property, which makes the application code to
// be loaded. The application handle
// is obtained from the children property
function switchApp(appName) {
   loader.source = appName+".qml";
}

//include the dicionary of kanjis
Qt.include("dictionary.js")

// With this I can take any element and reduce my array in order not significant//
Array.prototype.popElement = function(element){

                var aux = this[element];
                if (element + 1 == this.length){
                        this.pop();
                }
                else if (element == 0){
                        this.shift();
                }
                else {
                        this[element] = this.pop();

                }
                return aux;
}

//this make a copy no reference to another array, copy the elements in real//
Array.prototype.copyNoref = function(){

                var copyArray = new Array(this.length);
                for (var i = 0; i < this.length; i++)
                        copyArray[i] = this[i];
                return copyArray;

}

var kanjiDic;
var hiraganaDic;
var katakanaDic;
var ideogram;
var maxColumn = 5;
var maxRow = 4;
var maxIndex = maxColumn * maxRow;
var componentOk = Qt.createComponent("Ok.qml");
var kanjis = new Array(10);
var refKanjis = new Array(10);
var board = new Array(maxIndex);
var okboard = new Array(maxIndex);
var guide;
var positions =  new Array();
var clicks = 0;
var posclick = null;
var positionClicks;
var hits = 0;
var index = 0;
var currentScore=0;
var correctScore=0;
var wrongScore=0;

function newHiragana(){
        //load or reload all the game needs
        hiraganaDic = hiragana.copyNoref();
        ideogram = hiraganaDic[index];
        //balloon_.opacity = 1;
        //balloon_.text = "Find the same kanji and discover\n how to read and pronunce it.";
        kanjiText.text = ideogram["hiragana"];
        romanjiText.text = ideogram["romanji"];
}

function nextHiragana(){
        //load or reload all the game needs
        if(index<hiraganaDic.length-1)
            index++;
        ideogram = hiraganaDic[index];
        //balloon_.opacity = 1;
        //balloon_.text = "Find the same kanji and discover\n how to read and pronunce it.";
        kanjiText.text = ideogram["hiragana"];
        romanjiText.text = ideogram["romanji"];
}


function prevHiragana(){
        if(index>0)
            index--;
        //load or reload all the game needs
        ideogram = hiraganaDic[index];
        //balloon_.opacity = 1;
        //balloon_.text = "Find the same kanji and discover\n how to read and pronunce it.";
        kanjiText.text = ideogram["hiragana"];
        romanjiText.text = ideogram["romanji"];
}

function verifyHiraganaQuiz(){

   if(romanjiTextInput.text == ideogram["romanji"]){
       updateScore(true);
       correctValue.text = correctScore;
       scoreValue.text = currentScore+"%";
       return true;
   }
   updateScore(flase);
   wrongValue.text = wrongScore;
   scoreValue.text = currentScore+"%";
   return false;
}

function updateScore(correct){
    if(correct)
        correctScore++;
    else
        wrongScore++;
    currentScore = (correctScore*100)/(correctScore+wrongScore);
}

function clean(){
    romanjiTextInput.text=""
    romanjiTextInput.color="#1027d5"
}
