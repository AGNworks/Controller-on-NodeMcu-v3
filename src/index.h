const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
    <head>
        <title>Index</title>
        <style>
            h1 {
              color: black;
              font-family: verdana;
              font-size: 300%;
              margin: 20px;
            }
            p {
              color: red;
              font-family: verdana;
              font-size: 160%;
            }
            button {
                font-size: 160%;
                margin-right: 20px;
                margin-bottom: 20px;
            }
            input{
                width: 40%;
            }
            </style>
    </head>
    <body>
        <h1>DMX-512 Controller</h1>

        <div style="margin: 20px; font-size: 160%;">
            <select name="Led type" id="led_type" style="margin-bottom: 40px;" onchange="sendType(led_type.value)">
                <option value="RGB">RGB</option>
                <option value="RGBW" >RGBW</option>
            </select>
            LED type :<span id="LEDType">NA</span>
        </div>

        <div id="demo" style="margin: 20px;" >
            <button type="button" onclick="sendData(1)" style="background-color:red;">RED</button>
            <button type="button" onclick="sendData(2)" style="background-color:green;">GREEN</button>
            <button type="button" onclick="sendData(3)" style="background-color:blue;">BLUE</button>
            <button type="button" onclick="sendData(4)" >WHITE</button>
            <br>
            <button type="button" onclick="sendData(5)">LED ON</button>
            <button type="button" onclick="sendData(0)">LED OFF</button><BR>
        </div>

        <div style="margin: 20px; color:red; font-size: 160%">
            LED State is : <span id="LEDState">NA</span>
        </div>

        <div style="margin: 20px; font-size: 160%">
            <input type="range" name = "ch_range" min = "0" max = "255" value = "0" id = "ch_value" onchange="sendvalue(ch_value.value)"><br>
            Value : <span id="channel_value">NA</span>
        </div>

        <script>
            
        function sendData(led) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) 
            {
            document.getElementById("LEDState").innerHTML =
            this.responseText;   //LEDState will be what we get from the server as response (ledState varuable in c++ file)
            }
        };
        xhttp.open("GET", "setLED?LEDstate="+led, true);
        xhttp.send();
        }

        function sendType(type) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) 
            {
            document.getElementById("LEDType").innerHTML =
            this.responseText; 
            }
        };
        xhttp.open("GET", "settype?LEDtype="+type, true);
        xhttp.send();
        }

        function sendvalue(chvalue) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) 
            {
            document.getElementById("channel_value").innerHTML =
            this.responseText; 
            }
        };
        xhttp.open("GET", "setvalue?LEDvalue="+chvalue, true);
        xhttp.send();
        }

        </script>
    </body>
</html>


)=====";