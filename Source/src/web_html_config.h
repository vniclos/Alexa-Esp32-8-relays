#ifndef WEB_HTML_CONFIG_H
#define WEB_HTML_CONFIG_H

const char g_Web_Html_Config[] PROGMEM = R"=====(
    <!DOCTYPE html><html><head> 
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
	<meta name=viewport content="width=device-width, initial-scale=1">
  <link rel="icon" href="favicon.svg" type=”image/svg+xml”>
  <link rel=”mask-icon” href=”mask-icon.svg” color=”#000000">
  <link rel="manifest" href="manifest.json">
<link rel="stylesheet" type="text/css" href="css.css">
<title>Config wifi</title> 
<style>
label {display: block; width: 130px; font-weight:bold; }
input[type=text] { padding: 12px 20px;  min-width: :20em;   box-sizing: border-box;   paddin:3px;   font-size:1rem; }
input[type=password] { padding: 12px 20px;  min-width: :20em;   box-sizing: border-box;   paddin:3px;   font-size:1rem; }
.slidecontainer {   width: 100%; } 
.slider {   -webkit-appearance: none;   width: 100%;   height: 25px;   background: #d3d3d3;   outline: none;   opacity: 0.7;  -webkit-transition: .2s;   transition: opacity .2s; }
.slider:hover {   opacity: 1; }
.slider::-webkit-slider-thumb { -webkit-appearance: none;  appearance: none;   width: 25px;   height: 25px;   background: #04AA6D;   cursor: pointer; }
.slider::-moz-range-thumb {   width: 25px;   height: 25px;   background: #04AA6D;   cursor: pointer; }
.divbuttons{
 border: 3px solid #666666;
  padding: 5px;
  text-align:right;
}
</style>
</head>
<body>
<div id="divbody">
<div class="row">
<spam class="title">Wifi configuration
<br/><spam class="titlesub">Be careful</spam></spam>
<div class="divbuttons">
<input type="button" Class="button" onClick="fncGetAjaxConfig('/getconfig')" value ="get config"/>
<input type="button" Class="button" onClick="fncGetAjaxConfig('/getConfigdefault')" value ="get default"/>
<input type="button" Class="button" onClick="jsCfgSave()" value ="Save"/>
<input type="button" Class="button" onClick="fncSendGetHtml('scnMsgSend','/reset')" value ="Apply changes and reset"/>
<div id="scnMsgSend" style=" border: 1px solid gray;; background-color:#eeeeee;" margin:2px;"></div>
<div id="scnMsgReply" style="border: 1px solid gray; background-color:#eeeeee;" margin:2px;"></div>
</div>
</div>
<div class="row">
<fieldset>
  <legend>For join to your net as ws:</legend>
  <br/>
  <label for="scnSsid">SSID</label>
  <input type="text" id ="scnSsid" name="scnSsid"><br>
  <label for="scnPwd">Password</label>
  <input  type="password" id ="scnPwd" name="scnPwd">
  <input type="checkbox" onclick="togglePwd('scnPwd')"><strong>Show Password</strong>
  <br>
  <label for="scnIp">IP Address</label>
  <input type="text" id ="scnIp" name="scnIp" value="192.168.2.47"><br>
  <label for="scnMask">IP Mask</label>
  <input type="text" id ="scnMask" name="scnMask" value="255.255.255.0"><br>
  <label for="scnGat">Gateway Address</label>
  <input type="text" id ="scnGat" name="scnGat" value="192.168.2.1"><br>
  <br/>
</fieldset>
<fieldset>
   <legend>For get local time from NTP server</legend>
   <div class="slidecontainer">
   <b>"Time zone in hours"</b>
   <input type="range" min="-11" max="12" value="1" class="slider" id="scnTimeZone" name="scnTimeZone"  oninput="fncShowValue('scnTimeZone','scnTimeZoneValue')" >
   <p>Time zone:<span id="scnTimeZoneValue"></span></p>
   </div>
   <div class="slidecontainer">
   <input type="range" min="-2" max="+2" value="1" class="slider" id="scnTimeZoneDay" name="scnTimeZoneDay" oninput="fncShowValue('scnTimeZoneDay','scnTimeZoneDayValue')" >
   <p>Time zone Day Light (summer): <span id="scnTimeZoneDayValue"></span></p>
   </div>
</fieldset>
<fieldset>
  <legend>GPS decimal cordinates</legend>
  <label for="scnGpsLat">Latitude:</label>
  <input type="number" id ="scnGpsLat" name="scnGpsLat" value="0" step="any" placeholder="40.4165000"><span>40.4167  (Madrid)</span><br>
  <label for="scnGpsLon">Longitude:</label>
  <input type="number" id ="scnGpsLon" name="scnGpsLon" value="0" step="any"  placeholder="-3.703228"><span id="scnGpsLongNote">-3.703228 (Madrid)</span><br>
</fieldset>




</div>
</body>

<script>

function fncSendGetHtml(pDivTarget, pURL) {
 console.log("pDivTarget=" + pDivTarget + "\n pURL= " + pURL);
   document.getElementById("scnMsgSend").innerHTML = pURL;
 var xhttp;
 xhttp = new XMLHttpRequest();
 xhttp.onreadystatechange = function() {
  if (xhttp.readyState == 4 && xhttp.status == 200) {
  
     document.getElementById(pDivTarget).innerHTML = xhttp.responseText ;
  }
 };
 xhttp.open("GET", pURL, true);
 xhttp.send();
}
function ValidateIPaddress(ipaddress) 
{
 if (/^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/.test(myForm.emailAddr.value))
  {
    return (true)
  }
alert("You have entered an invalid IP address!")
return (false)
}

function jsCfgSave()
{
  let url="/cfgsave?";
  url=url+"ssid="+document.getElementById('scnSsid').value.trim();
  url=url+"&pwd="+document.getElementById('scnPwd').value.trim();
  url=url+"&ip="+document.getElementById('scnIp').value.trim();
  url=url+"&mask="+document.getElementById('scnMask').value.trim();
  url=url+"&gat="+document.getElementById('scnGat').value.trim();
  url=url+"&TimeZone="+document.getElementById('scnTimeZone').value.trim();
  url=url+"&TimeDayLight="+document.getElementById('scnTimeZoneDay').value.trim();
  url=url+"&lat="+document.getElementById('scnGpsLat').value.trim();
  url=url+"&long="+document.getElementById('scnGpsLon').value.trim();
  fncSendGetHtml('scnMsgReply', url) ;
}
function togglePwd(id) {
var temp = document.getElementById(id);
if (temp.type === "password") {temp.type = "text";}
else {temp.type = "password";}
}
function jsReset()
{
fncGetHtml('scnMsgReply', "/reset") ;
}
function fncShowValue(idRange, idRangeValue)
{
var slider = document.getElementById(idRange);
var output = document.getElementById(idRangeValue);
console.log(idRange); 
console.log(idRangeValue);
console.log(slider.value) ;
output.innerHTML = slider.value;
}
//---------------------------------------
document.addEventListener("DOMContentLoaded", () => {
  console.log("Hello World!");
  //fncSendGetHtml('scnDebug', '/geconfig');
 
fncGetAjaxConfig('/getconfig');



});
//---------------------------------------
function fncGetAjaxConfig(pURL) {
  // https://www.w3schools.com/js/js_ajax_http_send.asp
 console.log("fncGetAjax pURL= " + pURL);
 var xhttp;
 var reply = "";
 xhttp = new XMLHttpRequest();
 xhttp.onreadystatechange = function() {
  if (xhttp.readyState == 4 && xhttp.status == 200) 
  {
   reply = xhttp.responseText;
   document.getElementById("scnMsgReply").innerHTML = reply;
 fillFields(reply)
 }

 };
 xhttp.open("GET", pURL, true);
 xhttp.send();
}
function fillFields(stringValues)
{
   var aValues = stringValues.split("#");
 for (var i=0; i< aValues.length;i++) {console.log( i+" = "+ aValues[i]); }
 document.getElementById("scnSsid").value = aValues[0];
 document.getElementById("scnPwd").value = aValues[1];
 document.getElementById("scnIp").value = aValues[2];
 document.getElementById("scnMask").value = aValues[3];
 document.getElementById("scnGat").value = aValues[4];
 
 document.getElementById("scnTimeZone").value = aValues[5];
 document.getElementById("scnTimeZoneValue").value = aValues[5];

 document.getElementById("scnTimeZoneDay").value = aValues[6];
 document.getElementById("scnTimeZoneDayValue").value = aValues[6];
 
 aValues[7]=aValues[7].replace('.', ',').trim();;
 document.getElementById("scnGpsLat").value = aValues[7].trim();
 console.log(aValues[7]);

 aValues[8]=aValues[8].replace('.', ',').trim();;
 document.getElementById("scnGpsLon").value = aValues[8].trim();
 console.log(aValues[8]);

}
</script>
</html>
)=====";
#endif