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
              align-items: center;
            }
            p {
              color: black;
              font-family: verdana;
              font-size: 80%;
              align-items: center;
            }
            button {
                align-items: center;
                font-size: 160%;
                margin-right: 20px;
                margin-bottom: 20px;
            }
            input{
                align-items: center;
                width: 40%;
            }
            </style>
    </head>
    <body>
        <h1>DMX-512 Controller</h1>

        <div id="chose_type" style="margin: 20px; font-size: 160%; ">
            <select name="Led type" id="led_type" style="margin-bottom: 40px; font-size: 100%" onchange="sendType(led_type.value)">
                <option value="RGB">RGB</option>
                <option value="RGBW" >RGBW</option>
            </select>
            LED type :<span id="LEDType">RGB</span>
        </div>

        <div id="colors" style="margin: 20px;" >
            <button type="button" onclick="sendData(1)" style="background-color:red;">RED</button>
            <button type="button" onclick="sendData(2)" style="background-color:green;">GREEN</button>
            <button type="button" onclick="sendData(3)" style="background-color:blue;">BLUE</button>
            <button type="button" onclick="sendData(4)" >WHITE</button>
            <br>
            <button type="button" onclick="sendData(5)">LED ON</button>
            <button type="button" onclick="sendData(0)">LED OFF</button><BR>
        </div>

        <div style="margin: 20px; color:red; font-size: 160%">
            LED status : <span id="LEDState">OFF</span>
        </div>

        <div id="ch_slider" style="margin: 20px; font-size: 160%">
            <p>Nomer kanala:</p>
            <input type = "number" id = "ch_number" value = "1" min = "1" max = "512" style="background-color:lightgrey; color:black; margin-bottom: 20px; width: 10%; font-size:150% ;"><br>
            <input type="range" id = "ch_value" name = "ch_range" min = "0" max = "255" value = "0"  onchange="sendvalue(ch_value.value,ch_number.value)"><br>
            Znachenie : <span id="channel_value">0</span>
        </div>

        <div style="margin: 20px; ">
            <button type="button" onclick="changeslider('minus')">MINUS</button>
            <button type="button" onclick="changeslider('plus')">PLUS</button><BR>
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

        function sendvalue(chvalue,chnumber) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) 
            {
            document.getElementById("channel_value").innerHTML =
            this.responseText; 
            }
        };
        var info
        if (chnumber.length == 1)
         { 
            info = "00" + chnumber;
         };
         if (chnumber.length == 2)
         { 
            info = "0" + chnumber;
         };
         if (chnumber.length == 3)
         { 
            info = chnumber;
         };
         info = info +  chvalue; 

        xhttp.open("GET", "setvalue?LEDnumber="+info, true);
        xhttp.send();
        }

        function changeslider(op){
            if (op== "plus"){
            var x = parseInt(document.getElementById("ch_value").value);
            x = x+1 ;
            document.getElementById("ch_value").value = x;
            sendvalue(ch_value.value,ch_number.value);
            };
            if (op== "minus"){
            var x = parseInt(document.getElementById("ch_value").value);
            x = x-1 ;
            document.getElementById("ch_value").value = x;
            sendvalue(ch_value.value,ch_number.value);
            };
        };

        </script>
    </body>
</html>


)=====";