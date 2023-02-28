#ifndef WEB_HTML_ROOT_H
#define WEB_HTML_ROOT_H

const char g_Web_Htlm_Root[] PROGMEM = R"=====(
<!DOCTYPE html>
<html><head>
<meta http-equiv="content-type" content="text/html; charset=UTF-8"> 
 <meta name="viewport" content="width=device-width, initial-scale=1">
 <title>Alexa eight relays belen</title>
<link rel="shortcut icon" href="favicon.ico" type="image/x-icon">
<link rel="icon" href="favicon.ico">
<link rel="icon" href="favicon.svg" type="image/svg+xml">
<link rel="apple-touch-icon" href="apple-touch-icon.png">
<link rel="stylesheet" type="text/css" href="css.css">
<meta http-equiv='cache-control' content='no-cache'>
<meta http-equiv='expires' content='0'>
<meta http-equiv='pragma' content='no-cache'>
<style>
	.dot {
		margin-left:1rem;
  height: 0.7em;
  width: 0.7em;
  border-radius: 50%;
  border: 2px solid #fff;
  display: inline-block;
}
.right{text-align:right;}
.red{background-color: #e00;}
.gray{background-color: #444;}
.yellow{background-color:#ffffcc;}
.button{ border-color:#eee; margin-left:0.25em; border-radius: 8px;}
	</style>
<script src="js.js"></script>  
</head>
<body>
<div id="divbody">
<div class="row">
	<div class="column">
		<img style=" width:120px; " src="svg.svg" alt="Logo">
	</div>
	<div class="column">
			<spam class="title">Alexa eight relays
			<br><spam class="titlesub">Alexa and web managging  eight relays. (ESP32 and 8 relays module)</spam></spam>
	 </div>
  
</div> 
<div class="row right"> 
<input type="button" Class="button yellow" onClick="fncRelayAjaxJson('refresh');" value ="Refresh" title="Restore before saved values"/>
<input type="button" Class="button yellow" onClick="fncRelayAjaxJson('apply');" value ="Apply" title ="Apply but not save"/>
<input type="button" Class="button yellow" onClick="fncRelayAjaxJson('save');" value ="Apply & Save" title="Aply and save values"/>
<input type="button" Class="button yellow" onclick="location.href='/config'" value="Config Network" title="Config network">
        

   <div id="scnNtpSunrise" style="border: 1px solid gray; background-color:#eeeeee;  margin:2px; height:1rem;">
   	Now: <span id="scnDateTime">.</span>
   	Sunrise: <span id="scnSunrise">.</span>
   	Sunset: <span id="scnSunset">.</span>
   	Is Daylight:<span id="scnIsDay">.</span>
   	
   	
   	</div>
   <div id="scnMessages" style="border: 1px solid gray; background-color:#eeeeee;  margin:2px; height:1rem;"><span id="scnMessage"></span><span id="scnMessageDate"></span></div>
</div>
<div class="row">

 <fieldset>
 <legend><span id="scnName0" >Name</span> <span id="scnStatus0">status</span></legend>
 <br/>
 
 <p><b>Mode:</b>
 <input type="radio" id="scnMode00" name="scnMode0" value="0" checked><label for="scnMode01">Fixed</label>
 <input type="radio" id="scnMode01" name="scnMode0" value="1"><label for="scnMode02">Flashing</label>
 <input type="radio" id="scnMode02" name="scnMode0" value="2"><label for="scnMode03">Randon Flash</label>
 <p> <b>Time use:</b>
 <input type="radio" id="scnTime00" name="scnTime0" value="0" checked><label for="scnTime0D">ON Day</label>
 <input type="radio" id="scnTime01" name="scnTime0" value="1"><label for="scnTime0N">ON Night</label>
 <input type="radio" id="scnTime02" name="scnTime0" value="2"><label for="scnTime0ON">ON Always </label>
 <input type="radio" id="scnTime03" name="scnTime0" value="3"><label for="scnTime0OFF">OFF Always</label>
 </p>
 Comand: Alexa!  <span id="scnName0b" >Name</Span> (on or off)
 <br><span id="idMsg0">.</span>
</fieldset>
<fieldset>
<legend><span id="scnName1" >Name</span> <span id="scnStatus1">status</span></legend>
 <p><b>Mode:</b>
 <input type="radio" id="scnMode10" name="scnMode1" value="0" checked><label for="scnMode10">Fixed</label>
 <input type="radio" id="scnMode11" name="scnMode1" value="1"><label for="scnMode11">Flashing</label>
 <input type="radio" id="scnMode12" name="scnMode1" value="2"><label for="scnMode12">Randon Flash</label>
 <p> <b>Time use:</b>
 <input type="radio" id="scnTime10" name="scnTime1" value="0" checked><label for="scnTime10">ON Day</label>
 <input type="radio" id="scnTime11" name="scnTime1" value="1"><label for="scnTime11">ON Night</label>
 <input type="radio" id="scnTime12" name="scnTime1" value="2"><label for="scnTime12">ON Always</label>
 <input type="radio" id="scnTime13" name="scnTime1" value="3"><label for="scnTime13">OFF Always</label>
 </p>
 Comand: Alexa!  <span id="scnName1b" >Name</Span> (on or off)
 <br><span id="idMsg0">.</span>
</fieldset>
<fieldset>
<legend><span id="scnName2" >Name</span> <span id="scnStatus2">status</span></legend>
 <p><b>Mode:</b>
 <input type="radio" id="scnMode20" name="scnMode2" value="0" checked><label for="scnMode20">Fixed</label>
 <input type="radio" id="scnMode21" name="scnMode2" value="1"><label for="scnMode21">Flashing</label>
 <input type="radio" id="scnMode22" name="scnMode2" value="2"><label for="scnMode22">Randon Flash</label>
 <p> <b>Time use:</b>
 <input type="radio" id="scnTime20" name="scnTime2" value="0" checked><label for="scnTime20">ON Day</label>
 <input type="radio" id="scnTime21" name="scnTime2" value="1"><label for="scnTime21">ON Night</label>
 <input type="radio" id="scnTime22" name="scnTime2" value="2"><label for="scnTime22">ON Always</label>
 <input type="radio" id="scnTime23" name="scnTime2" value="3"><label for="scnTime23">OFF Always</label>
 </p>
 Comand: Alexa!  <span id="scnName2b" >Name</Span> (on or off)
 <br><span id="idMsg0">.</span>
</fieldset>
<fieldset>
<legend><span id="scnName3" >Name</span> <span id="scnStatus3">status</span></legend>
 <br/> <p><b>Mode:</b>
 <input type="radio" id="scnMode40" name="scnMode3" value="0" checked><label for="scnMode40">Fixed</label>
 <input type="radio" id="scnMode41" name="scnMode3" value="1"><label for="scnMode41">Flashing</label>
 <input type="radio" id="scnMode42" name="scnMode3" value="2"><label for="scnMode42">Randon Flash</label>
 <p> <b>Time use:</b>
 <input type="radio" id="scnTime30" name="scnTime3" value="0" checked><label for="scnTime30">ON Day</label>
 <input type="radio" id="scnTime31" name="scnTime3" value="1"><label for="scnTime31">ON Night</label>
 <input type="radio" id="scnTime32" name="scnTime3" value="2"><label for="scnTime32">ON Always</label>
 <input type="radio" id="scnTime33" name="scnTime3" value="3"><label for="scnTime33">OFF Always</label>
 </p>
 Comand: Alexa!  <span id="scnName3b" >Name</Span> (on or off)
 <br><span id="idMsg0">.</span>
</fieldset>
<fieldset>
<legend><span id="scnName4" >Name</span> <span id="scnStatus4">status</span></legend>
 
 <p><b>Mode:</b>
 <input type="radio" id="scnMode40" name="scnMode4" value="0" checked><label for="scnMode40">Fixed</label>
 <input type="radio" id="scnMode41" name="scnMode4" value="1"><label for="scnMode41">Flashing</label>
 <input type="radio" id="scnMode42" name="scnMode4" value="2"><label for="scnMode42">Randon Flash</label>
 <p> <b>Time use:</b>
 <input type="radio" id="scnTime0D" name="scnTime4" value="0" checked><label for="scnTime40">ON Day</label>
 <input type="radio" id="scnTime41" name="scnTime4" value="1"><label for="scnTime41">ON Night</label>
 <input type="radio" id="scnTime42" name="scnTime4" value="2"><label for="scnTime42">ON Always</label>
 <input type="radio" id="scnTime43" name="scnTime4" value="3"><label for="scnTime43">OFF Always</label>
 </p>
 Comand: Alexa!  <span id="scnName4b" >Name</Span> (on or off)
 <br><span id="idMsg0">.</span>
</fieldset>
<fieldset>
<legend><span id="scnName5" >Name</span> <span id="scnStatus5">status</span></legend>
 <p><b>Mode:</b>
 <input type="radio" id="scnMode50" name="scnMode5" value="0" checked><label for="scnMode50">Fixed</label>
 <input type="radio" id="scnMode51" name="scnMode5" value="1"><label for="scnMode51">Flashing</label>
 <input type="radio" id="scnMode52" name="scnMode5" value="2"><label for="scnMode52">Randon Flash</label>
 <p> <b>Time use:</b>
 <input type="radio" id="scnTime50" name="scnTime5" value="0" checked><label for="scnTime50">ON Day</label>
 <input type="radio" id="scnTime51" name="scnTime5" value="1"><label for="scnTime51">ON Night</label>
 <input type="radio" id="scnTime52" name="scnTime5" value="2"><label for="scnTime52">ON Always</label>
 <input type="radio" id="scnTime53" name="scnTime5" value="3"><label for="scnTime53">OFF Always</label>
 </p>
 Comand: Alexa!  <span id="scnName5b" >Name</Span> (on or off)
 <br><span id="idMsg0">.</span>
</fieldset>
<fieldset>
<legend><span id="scnName6" >Name</span> <span id="scnStatus6">status</span></legend>
 <p><b>Mode:</b>
 <input type="radio" id="scnMode60" name="scnMode6" value="0" checked><label for="scnMode60">Fixed</label>
 <input type="radio" id="scnMode61" name="scnMode6" value="1"><label for="scnMode61">Flashing</label>
 <input type="radio" id="scnMode62" name="scnMode6" value="2"><label for="scnMode62">Randon Flash</label>
 <p> <b>Time use:</b>
 <input type="radio" id="scnTime60" name="scnTime6" value="0" checked><label for="scnTime60">ON Day</label>
 <input type="radio" id="scnTime61" name="scnTime6" value="1"><label for="scnTime61">ON Night</label>
 <input type="radio" id="scnTime62" name="scnTime6" value="2"><label for="scnTime62">ON Always</label>
 <input type="radio" id="scnTime63" name="scnTime6" value="3"><label for="scnTime63">OFF Always</label>
 </p>
 Comand: Alexa!  <span id="scnName6b" >Name</Span> (on or off)
 <br><span id="idMsg0">.</span>
</fieldset>
<fieldset>
<legend><span id="scnName7" >Name</span> <span id="scnStatus7">status</span></legend>
 <br/>
 <p><b>Mode:</b>
 <input type="radio" id="scnMode70" name="scnMode7" value="0" checked><label for="scnMode70">Fixed</label>
 <input type="radio" id="scnMode71" name="scnMode7" value="1"><label for="scnMode71">Flashing</label>
 <input type="radio" id="scnMode72" name="scnMode7" value="2"><label for="scnMode72">Randon Flash</label>
 <p> <b>Time use:</b>
 <input type="radio" id="scnTime70" name="scnTime7" value="0" checked><label for="scnTime70">ON Day</label>
 <input type="radio" id="scnTime71" name="scnTime7" value="1"><label for="scnTime71">ON Night</label>
 <input type="radio" id="scnTime72" name="scnTime7" value="2"><label for="scnTime72">ON Always</label>
 <input type="radio" id="scnTime73" name="scnTime7" value="3"><label for="scnTime73">OFF Always</label>
 </p>
 Comand: Alexa!  <span id="scnName7b" >Name</Span> (on or off)
 <br><span id="idMsg0">.</span>
</fieldset>
</div>

<script>
//===============================================
//===============================================
//===============================================
function fncRelayAjaxJson(option)
{
 var pURL="/getsetrelaysConfig?option="+option+"&json=";
 pURL=pURL+ fncReadScreenToJson();
 console.log("Enviado");
 console.log("fncRelayAjaxJson(option) pURL= " + pURL);
 var xhttp;
 var reply = "";
 xhttp = new XMLHttpRequest();
 xhttp.onreadystatechange = function() 
 {
  if (xhttp.readyState == 4 && xhttp.status == 200) 
  {
   message="";
   arrJson = xhttp.responseText;
   console.log("recibido");
   console.log(arrJson);
   fillJsonScreen(arrJson);
   if(option=="refresh"){message="refresed at";}
   if(option=="apply"){message="refresed at ";}
   if(option=="save"){message="saved at ";}
   let elem = document.getElementsByName("scnMessage");
   if(elem !== null && elem !== 'undefined' )
   {
	 elem.innerHTML=message;
	}
   var now = new Date();
   now.setMinutes(now.getMinutes() - now.getTimezoneOffset());
   elem = document.getElementsByName("scnMessageDateTime");
   if(elem !== null && elem !== 'undefined' )
   {
	 elem.innerHTML=now.toISOString().slice(0,16); 
	}
}
 };
 
 console.log("xhttp.open(GET, pURL, true)");
 xhttp.open("GET", pURL, true);
 xhttp.send();

}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------

function fncReadScreenToJson()
{
	let jsonValues="[";
	let isFirst=true;
	for (idRelay=0;idRelay<8;idRelay++)
	{
    	if(isFirst==false){
		    jsonValues=jsonValues+", ";
		}
		isFirst=false;
	    jsonValues=jsonValues+ fncReadScreenToJsonRelay(idRelay);
	}
	jsonValues=jsonValues+"]";
	return jsonValues;
}
function fncReadScreenToJsonRelay(idRelay)
{
let fldRelay="Relay";
let fldName="Name";
let fldMode="Mode";
let fldTime="Time";

let scnRelay ="scn"+fldRelay+idRelay;
let scnName  ="scn"+fldName+idRelay;
let scnMode  ="scn"+fldMode+idRelay;
let scnTime  ="scn"+fldTime+idRelay;

let result='{"idRelay":"'+idRelay+'"';

var elem =document.getElementById(scnName);
if(elem !== null && elem !== 'undefined' )
{
	
	result=result + ', "'+ fldName +'": "'+ elem.innerText+'"'; 
	
	}
let val=fncGetRadioSelected(scnMode);
result =result +', "'+ fldMode + '": "'+val+'"';
val=fncGetRadioSelected(scnTime);
result =result +', "'+ fldTime + '":"'+val+'"';
result =result +"}";
return result;
}
	
function fncGetRadioSelected(pNameRadio) 
{
let result='';
let ele = document.getElementsByName(pNameRadio);
for(i = 0; i < ele.length; i++) 
{
	if(ele[i].checked)
	{
		result = ele[i].value;
	}
}
return result;
}
function jsCmd(pIdRelay,pCmd)
{
	
	let radioNameMode='scnMode'+pIdRelay;
	let radioNameTime='scnTime'+pIdRelay;
	let idMsg='idMsg'+pIdRelay;
	let vMode=fncGetRadioSelected(radioNameMode);
	let vTime=fncGetRadioSelected(radioNameTime);
  let url='/cmd?id=' + pIdRelay + "&cmd=" + pCmd + '&mode=' + vMode+'&time='+vTime;
  document.getElementById(idMsg).innerHTML = url;
  fncGetHtml(idMsg, url) ;
	}
 function fncCapitalize(str)
{
	return str.charAt(0).toUpperCase() + str.slice(1);
	}


//===============================================
//===============================================
//===============================================
function  fillJsonScreen(arrJson)
{
	 console.log("fillJsonScreen arrJson= " + arrJson);

let idRelay=-1;
let  isFirst=0;
let oJson=JSON.parse(arrJson);
for (var i = 0; i < oJson.length; i++)
{
	var oRow = oJson[i];
   	if (oRow.hasOwnProperty('idRelay'))
    {
		idRelay=oRow['idRelay'];}
   	else
	{
		idRelay='-1';
   	}
   fillJsonScreenRow(idRelay, oRow);
}
}

//===============================================
//===============================================
//===============================================
function fillJsonScreenRow(idRelay,oRow)
{
  var idRelay=-1;
	for (var key in oRow)
	{
		var colValue = oRow[key];
   		var colName= key;
   		var colNameb= key;
   		var scnName="scn"+colName;
		scnName=scnName.trim();
		//console.log("1 For key ColName=" + colName + " scnName=" + scnName + " colValue= "+ colValue);
    	if (oRow.hasOwnProperty('DateTime'))
		{
		
 			var elem = document.getElementById(scnName);
    		if(elem !== null && elem !== 'undefined' ){ elem.innerHTML=colValue;}
   		}
   		//--------------------------------------------------
   		if (oRow.hasOwnProperty('idRelay'))
		{
		
			idRelay=oRow['idRelay'];
			scnName=scnName+idRelay;
		//	console.log("2 For hasOwnProperty IdRelay"+ idRelay+ " ColName=" + colName + " scnName=" + scnName + " colValue= "+ colValue );
			if (colName=='Mode'|| colName=='Time')
   			{
				scnName=scnName+colValue;
				console.log("2 For hasOwnProperty IdRelay= "+ idRelay+ " ColName=" + colName + " scnName=" + scnName + " colValue= "+ colValue );
				let elem = document.getElementById(scnName);
       			if(elem !== null && elem !== 'undefined' ){ elem.checked=true;}
      		}
				//scnStatus0
   	  		if (colName=='Status')
	  		{
				console.log("Status="+colValue);
				let elem = document.getElementById(scnName);
        		if(elem !== null && elem !== 'undefined' )
				{
					colValue=colValue.trim().toUpperCase();
        			if(colValue=="0") 
					{
					colValue="<span class='dot red'></span>"; 
					}
					else
        			{
					colValue="<span class='dot gray'></span>"; 
					}
        			elem.innerHTML=colValue;
					console.log("Status="+colValue);
	   			} 
	  		}	
      		if (colName.includes("Name"))
      		{
				let elem = document.getElementById(scnName);
        		if(elem !== null && elem !== 'undefined' )
	   			{
					colValue=fncCapitalize(colValue);
					elem.innerHTML=colValue;
        			scmNameb=scnName+'b'
        			elem=document.getElementById(scmNameb);
        			if(elem !== null && elem !== 'undefined' ){elem.innerHTML=colValue;}
       			}
    		}
    	} //end relays
 }  // end key
   
} // end function


//===============================================
//===============================================
//===============================================

document.addEventListener("DOMContentLoaded", () => {fncRelayAjaxJson('refresh');});
</script>


</div></body></html>
)=====";
#endif