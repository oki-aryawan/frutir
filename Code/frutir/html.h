/*
  ESP32 HTML WebServer Page Code
  http:://www.electronicwings.com
*/

const char html_page[] PROGMEM = R"RawString(
<!DOCTYPE html>
<html>
  <style>
    body {font-family: sans-serif;}
    h1 {text-align: center; font-size: 30px;}
    p.a {text-align: center; color: #FF0000; font-size: 40px;}
    p.b {text-align: center; color: #00FF00; font-size: 40px;}
    p.c {text-align: center; color: #0000FF; font-size: 40px;}
  </style>

<body>
  <h1>TCS3200 Color Sensor with ESP32 </h1><br>
  <p class="a">Red = <span id="_R">0</span></p>
  <p class="b">Green = <span id="_G">0</span></p>
  <p class="c">Blue = <span id="_B">0</span></p>

<script>
  setInterval(function() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        const text = this.responseText;
        const myArr = JSON.parse(text);
       document.getElementById("_R").innerHTML = myArr[0];
       document.getElementById("_G").innerHTML = myArr[1];
       document.getElementById("_B").innerHTML = myArr[2];

      }
    };
    xhttp.open("GET", "readColors", true);
    xhttp.send();
  },100);
</script>
</body>
</html>
)RawString";