




var ledOnePath = 'led/one';
var ledTwoPath = 'led/two';
var ledThreePath = 'led/three';

var dataLedPath = 'led';
const ledRef = database.ref(dataLedPath);
const databaseLedOne = database.ref(ledOnePath);
const databaseLedTwo = database.ref(ledTwoPath);
const databaseLedThree = database.ref(ledThreePath);

 
databaseLedOne.on('value', (snapshot) => {
    ledOneState = snapshot.val();
    console.log(ledOneState);
    document.getElementById("reading-led-one").innerHTML = ledOneState;
},(errorObject) => {
    console.log('The read failed: ' + errorObject.name);
});

databaseLedTwo.on('value', (snapshot) => {
  ledTwoState = snapshot.val();
  console.log(ledTwoState);
  document.getElementById("reading-led-two").innerHTML = ledTwoState;
},(errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

databaseLedThree.on('value', (snapshot) => {
  ledThreeState = snapshot.val();
  console.log(ledThreeState);
  document.getElementById("reading-led-three").innerHTML = ledThreeState;
},(errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

// LED ONE Control
const ledOneOnButton = document.getElementById("led-one-OnState"); 
ledOneOnButton.addEventListener("click", ledOneOnBtnClicked);

function ledOneOnBtnClicked(e)  {
    ledRef.update({"one":1})
}

const ledOneOffButton = document.getElementById("led-one-OffState"); 
ledOneOffButton.addEventListener("click", ledOneOffBtnClicked);

function ledOneOffBtnClicked(e)  {
    ledRef.update({"one":0})
}



// LED TWO Control
const ledTwoOnButton = document.getElementById("led-two-OnState"); 
ledTwoOnButton.addEventListener("click", ledTwoOnBtnClicked);

function ledTwoOnBtnClicked(e)  {
    ledRef.update({"two":1})
}

const ledTwoOffButton = document.getElementById("led-two-OffState"); 
ledTwoOffButton.addEventListener("click", ledTwoOffBtnClicked);

function ledTwoOffBtnClicked(e)  {
    ledRef.update({"two":0})
}



// LED THREE Control
const ledThreeOnButton = document.getElementById("led-three-OnState"); 
ledThreeOnButton.addEventListener("click", ledThreeOnBtnClicked);

function ledThreeOnBtnClicked(e)  {
    ledRef.update({"three":1})
}

const ledThreeOffButton = document.getElementById("led-three-OffState"); 
ledThreeOffButton.addEventListener("click", ledThreeOffBtnClicked);

function ledThreeOffBtnClicked(e)  {
    ledRef.update({"three":0})
}



