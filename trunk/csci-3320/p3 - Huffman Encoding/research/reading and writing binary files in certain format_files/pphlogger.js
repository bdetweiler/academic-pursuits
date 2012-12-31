/* -----------------------------------------------
   POWER PHLOGGER - v.2.2.5
   (c) 2000-2003 www.phpee.com
   contact: webmaster@phpee.com
  ------------------------------------------------ */
  
id = "forums";

// define some defaults -------------------------------------
if(showme==null) var showme='n';
if(st==null)     var st='js';    // st means show-type


// get the user agent name ----------------------------------
v = navigator.appName;

// get the screen resolution --------------------------------
c=0;
if (v != "Netscape") c = screen.colorDepth;
else c = screen.pixelDepth;

// get the screen size --------------------------------------
s = screen.width+"x"+screen.height;

// get the document's title ---------------------------------
t = escape(document.title);

// get the document's referrer -------------------------------
var f = "";

// if pp_frames is true then try getting the framed referral (without error checking)
if (typeof(pp_frames) != "undefined")
	if (pp_frames)
		f = top.document.referrer;

// get the referral for non-multi-domained-framed sites using a Netscape browser
if ((f == "") || (f == "[unknown origin]") || (f == "unknown") || (f == "undefined"))
	if (document["parent"] != null) 
		if (parent["document"] != null) // ACCESS ERROR HERE!
			if (parent.document["referrer"] != null) 
				if (typeof(parent.document) == "object")
					f = parent.document.referrer; 

// get the referral for the current document if a framed referral wasn't found
if ((f == "") || (f == "[unknown origin]") || (f == "unknown") || (f == "undefined"))
	if (document["referrer"] != null) 
		f = document.referrer;

// convert all the unknown's into blank
if ((f == "") || (f == "[unknown origin]") || (f == "unknown") || (f == "undefined"))
	f = "";

// escape the referral
f = escape(f);

// getting data ready to send -------------------------------
r="?id="+id+"&referer="+f+"&r="+s+"&c="+c+"&showme="+showme+"&st="+st+"&title="+t;

// adding logid if called by st='phpjs'
if(jslogid==null) var jslogid = 0;
else r = r + "&jslogid="+jslogid;


if (st=='js') { // calling PowerPhlogger by JavaScript-tag
	if (v != "Microsoft Internet Explorer") {
		r = r+"&url="+document.URL; // $HTTP_REFERER problem with NS,...
	}
	document.open();
	document.write("<script type=\"text/javascript\" src=\"http://www.desilva.biz/logger/pphlogger.php"+r+"\"></script>");
	document.close();
} else { // calling PowerPhlogger by IMG-tag
	rand = Math.round(1000*Math.random());
	r = r+"&b="+rand;  //force the page to load the IMG
	document.open();
	document.write("<img src=\"http://www.desilva.biz/logger/pphlogger.php"+r+"\" alt=\"\" border=\"0\">");
	document.close();
}

// stuff
function _gidrd( id )
{
	var _gidauf = document.frmGIDAAT;
	_gidauf.action	= "http://www.gidnetwork.com/gidrd.php";
	_gidauf.i.value	= id;
	_gidauf.target	= "_blank";
	_gidauf.submit();
}
function _gidhs()
{
	window.status = '';
}
function _gidss( url )
{
	window.status = 'http://' + url;
	return( true );
}

function gtcb( url )
{
	var gf = document.gidadcbform;
	gf.action = "http://www.gidnetwork.com/gidcontext-r.php?p=cb";
	gf.iRD.value = url;
	gf.iB.value = 0;
	gf.iL.value = "";
	gf.target = "_blank";
	gf.submit();
}