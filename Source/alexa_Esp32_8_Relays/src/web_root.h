#ifndef _WEB_ROOT_H
#define _WEB_ROOT_H

const char g_HTML_Web_root[] PROGMEM = R"=====(
    <!DOCTYPE html><html><head> 
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
	<meta name=viewport content="width=device-width, initial-scale=1">
  <link rel="shortcut icon" href="/favicon.ico" type="image/x-icon">
  <link rel="icon" href="/favicon.ico" type="image/x-icon">

<link rel="stylesheet" type="text/css" href="css.css"><script src="/js.js"></script> <title>relay participativo v8 </title> 
</head>
<body>
<div id="divbody">
<div class="row">
	<div class="column">
		<img  style=" width:120px; "src='/svg.svg' alt="Logo">
	</div>
	<div class="column" >
			<spam class="title">Alexa eight relays
			<br/><spam class="titlesub">Alexa and web managging  eight relays. (ESP32 and 8 relays module)</spam></spam>
	</div>
  <div class="clear"></div>
</div>

 <fieldset>
   <legend>Relay 1:</legend>
  <br/>
  <input type="button" Class="button" onClick="jsCmd(0,0,'idMsg0')" value ="Off"/>
  <input type="button" Class="button" onClick="jsCmd(0,1,'idMsg0')" value ="ON"/>
  <input type="button" Class="button" onClick="jsCmd(0,2,'idMsg0')" value ="Flash"/>
  <input type="button" Class="button" onClick="jsCmd(0,3,'idMsg0')" value ="Flash randon"/>
  <br/>Alexa! relay 1 <alexa command>
  <br/><span id="idMsg0">.</span>
</fieldset>

 <fieldset>
<legend>Relay 2</legend>
  <br/>
  <input type="button" Class="button" onClick="jsCmd(1,0,'idMsg1')" value ="Off"/>
  <input type="button" Class="button" onClick="jsCmd(1,1,'idMsg1')" value ="ON"/>
  <input type="button" Class="button" onClick="jsCmd(1,2,'idMsg1')" value ="Flash"/>
  <input type="button" Class="button" onClick="jsCmd(1,3,'idMsg1')" value ="Flash randon"/>
<br/>Alexa! relay 2 <alexa command>
  <br/><span id="idMsg1">.</span>
  </fieldset>
 <fieldset>
<legend>Relay 3</legend>
  <br/>
  <input type="button" Class="button" onClick="jsCmd(2,0,'idMsg2')" value ="Off"/>
  <input type="button" Class="button" onClick="jsCmd(2,1,'idMsg2')" value ="ON"/>
  <input type="button" Class="button" onClick="jsCmd(2,2,'idMsg2')" value ="Flash"/>
  <input type="button" Class="button" onClick="jsCmd(2,3,'idMsg2')" value ="Flash randon"/>
  <br/>Alexa! relay 3 <alexa command>
  <br/><span id="idMsg2">.</span>
</fieldset>
 <fieldset>

<legend>Relay 4</legend>
  <br/>
  <input type="button" Class="button" onClick="jsCmd(3,0,'idMsg3')" value ="Off"/>
  <input type="button" Class="button" onClick="jsCmd(3,1,'idMsg3')" value ="ON"/>
  <input type="button" Class="button" onClick="jsCmd(3,2,'idMsg3')" value ="Flash"/>
  <input type="button" Class="button" onClick="jsCmd(3,3,'idMsg3')" value ="Flash randon"/>
 <br/>Alexa! relay 4 <alexa command>
  <br/><span id="idMsg3">.</span>
</fieldset>
 <fieldset>
<legend>Relay 5</legend>
  <br/>
  <input type="button" Class="button" onClick="jsCmd(4,0,'idMsg4')" value ="Off"/>
  <input type="button" Class="button" onClick="jsCmd(4,1,'idMsg4')" value ="ON"/>
  <input type="button" Class="button" onClick="jsCmd(4,2,'idMsg4')" value ="Flash"/>
  <input type="button" Class="button" onClick="jsCmd(4,3,'idMsg4')" value ="Flash randon"/>
<br/>Alexa! relay 5 <alexa command>
  <br/><span id="idMsg4">.</span>
</fieldset>
 <fieldset>
<legend>relay 6</legend>
  <br/>
  <input type="button" Class="button" onClick="jsCmd(5,0,'idMsg5')" value ="Off"/>
  <input type="button" Class="button" onClick="jsCmd(5,1,'idMsg5')" value ="ON"/>
  <input type="button" Class="button" onClick="jsCmd(5,2,'idMsg5')" value ="Flash"/>
  <input type="button" Class="button" onClick="jsCmd(5,3,'idMsg5')" value ="Flash randon"/>
  <br/>Alexa! relay 6 <alexa command>
  <br/><span id="idMsg5">.</span>
</fieldset>
 <fieldset>
<legend>Relay 7</legend>
  <br/>
  <input type="button" Class="button" onClick="jsCmd(6,0,'idMsg6')" value ="Off"/>
  <input type="button" Class="button" onClick="jsCmd(6,1,'idMsg6')" value ="ON"/>
  <input type="button" Class="button" onClick="jsCmd(6,2,'idMsg6')" value ="Flash"/>
  <input type="button" Class="button" onClick="jsCmd(6,3,'idMsg6')" value ="Flash randon"/>
  <br/>Alexa! relay 7 <alexa command>
  <br/><span id="idMsg6">.</span>
</fieldset>
 <fieldset>
<legend>Relay 8</legend>
  <br/>
  <input type="button" Class="button" onClick="jsCmd(7,0,'idMsg7')" value ="Off"/>
  <input type="button" Class="button" onClick="jsCmd(7,1,'idMsg7')" value ="ON"/>
  <input type="button" Class="button" onClick="jsCmd(7,2,'idMsg7')" value ="Flash"/>
  <input type="button" Class="button" onClick="jsCmd(7,3,'idMsg7')" value ="Flash randon"/>
  <br/>Alexa! relay 8 <alexa command>
  <br/><span id="idMsg7">.</span>
</fieldset>

<script>
function jsCmd(idRelay,value,idMsg)
{
  let url="/cmd?id="+idRelay+"&value="+value;
  document.getElementById(idMsg).innerHTML = url;
  fncGetHtml(idMsg, url) ;
	}
</script>
<br/>
<div id="scnMsg">.</div>
<div id="scnBody">.</div>
<div id="scnDebug"></div>
</div>
</body>
</html>
)=====";
#endif