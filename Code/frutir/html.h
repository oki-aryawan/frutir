const char html_page[] PROGMEM = R"RawString(
<!DOCTYPE html>
<html>
<head>
  <title>FRUIT SORTIR</title>
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/bootstrap/5.3.0/css/bootstrap.min.css">
  <style>
    body {
      font-family: sans-serif;
    }
    
    h1 {
      text-align: center;
      font-size: 30px;
      margin: 20px 0;
    }
    
    p.a, p.b, p.c, p.e, p.f {
      text-align: center;
      font-size: 40px;
      margin-bottom: 10px;
    }
    
    p.a {
      color: #FF0000;
    }
    
    p.b {
      color: #00FF00;
    }
    
    p.c {
      color: #0000FF;
    }
    
    p.e {
      color: #0000FF;
    }
    
    p.f {
      color: #0000FF;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>FRUIT SORTIR</h1>
    <p class="a">Red = <span id="_R">0</span></p>
    <p class="b">Green = <span id="_G">0</span></p>
    <p class="c">Blue = <span id="_B">0</span></p>
    <p class="e">Jumlah Sesuai Grade = <span id="grade">0</span></p>
    <p class="f">Jumlah Tidak Sesuai Grade = <span id="no_grade">0</span></p>
  </div>

  <script src="https://cdnjs.cloudflare.com/ajax/libs/bootstrap/5.3.0/js/bootstrap.bundle.min.js"></script>
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
          document.getElementById("grade").innerHTML = myArr[3];
          document.getElementById("no_grade").innerHTML = myArr[4];
        }
      };
      xhttp.open("GET", "readColors", true);
      xhttp.send();
    }, 100);
  </script>
</body>
</html>
)RawString";

/*
  ESP32 HTML WebServer Page Code
  http:://www.electronicwings.com


const char html_page[] PROGMEM = R"RawString(
<!DOCTYPE html>
<html>
  <style>
    body {font-family: sans-serif;}
    h1 {text-align: center; font-size: 30px;}
    p.a {text-align: center; color: #FF0000; font-size: 40px;}
    p.b {text-align: center; color: #00FF00; font-size: 40px;}
    p.c {text-align: center; color: #0000FF; font-size: 40px;}
    p.e {text-align: center; color: #0000FF; font-size: 40px;}
    p.f {text-align: center; color: #0000FF; font-size: 40px;}
  </style>

<body>
  <h1>FRUIT SORTIR</h1><br>
  <p class="a">Red = <span id="_R">0</span></p>
  <p class="b">Green = <span id="_G">0</span></p>
  <p class="c">Blue = <span id="_B">0</span></p>
  <p class="e">Jumlah Sesuai Grade = <span id="grade">0</span></p>
  <p class="f">Jumlah Tidak Sesuai Grade = <span id="no_grade">0</span></p>

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
       document.getElementById("grade").innerHTML = myArr[3];
       document.getElementById("no_grade").innerHTML = myArr[4];

      }
    };
    xhttp.open("GET", "readColors", true);
    xhttp.send();
  },100);
</script>
</body>
</html>
)RawString";

*/