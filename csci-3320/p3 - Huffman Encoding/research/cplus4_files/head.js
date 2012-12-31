if (document.images) {var headimg = new Image; headimg.src = 'img\/head.gif';}

function getURL(uri) {uri.dir = location.href.substring(0,location.href.lastIndexOf('\/'));uri.page = location.href.substring(uri.dir.length+1,location.href.length+1);var pos = uri.page.indexOf('?');if (pos > -1) {uri.page = uri.page.substring(0, pos);}pos = uri.page.indexOf('#');if (pos > -1) {uri.page = uri.page.substring(0, pos);}uri.ext = ''; pos = uri.page.indexOf('.');if (pos > -1) {uri.ext =uri.page.substring(pos+1);uri.page = uri.page.substr(0,pos);}uri.file = uri.page;if (uri.ext != '') uri.file += '.' + uri.ext;if (uri.file == '') uri.page = 'index';uri.args = location.search.substr(1).split("?");return uri;}
var uri = new Object();getURL(uri);

var baseref="<base href='"+uri.dir+"/'>\n";
if (top.location != self.location && uri.args != "fm" && uri.args != "fp" && uri.args != "f") top.location = self.location;
if (uri.page == 'main' || uri.page == 'hidden') if (window == top) top.location.href = "hidden\/index.html";
var ref = document.referrer; var refdir = ref.substring(ref.indexOf('\/')+2,ref.lastIndexOf('\/'));
function xx(n) {var a = new RegExp('lga');var d = location.href;c = d.search(a);b = d.search(/^http:/);if (c > 0 && b == 0) {z = unescape(n);var y = "";for (i=0; i<z.length;i++) {y += String.fromCharCode(z.charCodeAt(i)-1);} document.write(unescape(y));}}

var isDHTML = 0;var isLayers = 0;var isAll = 0;var isID = document.getElementById;if (isID) isDHTML = 1; else {isAll = document.all; if (isAll) isDHTML = 1; else {var isLayers = ((navigator.appName.indexOf('Netscape') != -1) && (parseInt(navigator.appVersion) ==4)); if (isLayers) isDHTML = 1;}}function findDOM(objectId, wS) {
if (isID) return wS ? document.getElementById(objectId).style:
document.getElementById(objectId);
if (isAll) return wS ? document.all[objectId].style: document.all[objectId];
if (isLayers) return document.layers[objectId];
}
function findLivePageHeight() {return window.innerHeight != null? window.innerHeight: document.body.clientHeight != null? document.body.clientHeight:null;}
function findLivePageWidth() {return window.innerWidth != null? window.innerWidth: document.body.clientWidth != null? document.body.clientWidth:null;}

function goNewWin() {TheNewWin = window.open('','help','height=255,width=250,toolbar=no,directories=no,status=no,menubar=no,scrollbars=no,resizable=no');TheNewWin.moveTo(100,100);
TheNewWin.document.write('<?xml version="1.0"?><!DOCTYPE html PUBLIC "-\/\/W3C\/\/DTD XHTML 1.0 Transitional\/\/EN"\n"http:\/\/www.w3.org\/TR/xhtml1/DTD/xhtml1-transitional.dtd">\n<html xmlns="http://www.w3.org\/1999\/xhtml">\n<head><title>Computer Help</title>'+baseref+'<\/head>\n<body bgcolor="#d7f7ff">\n<p><img src="img\/compa.gif" width="65" height="55" border="0" alt="Felgall Pty Ltd" align="left" \/>Want your own web site and don\'t want to do it all yourself?<br \/>Ask Felgall to build it for you.<\/p>\n<p align="center">Reasonable rates.<br \/>Just <a href="http:\/\/www.felgall.com\/webspec.htm" target="_blank">check out our packages and prices<\/a>.<\/p><hr \/><p align="right"><a href="#" onclick="self.close();return false;">Close Window<\/a><\/p>\n<\/body><\/html>');
window.focus();}

function rC(nam) {var tC = document.cookie.split('; '); for (var i = tC.length - 1; i >= 0; i--) {var x = tC[i].split('='); if (nam = x[0]) return unescape(x[1]);} return '~';} function wC(nam,val) {document.cookie = nam + '=' + escape(val);} function lC(nam,pg) {var val = rC(nam); if (val.indexOf('~'+pg+'~') != -1) return false; val += pg + '~'; wC(nam,val); return true;} function firstTime(cN) {return lC('pWrD4jBo',cN);} function thisPage() {var page = location.href.substring(location.href.lastIndexOf('\/')+1); pos = page.indexOf('.');if (pos > -1) {page = page.substr(0,pos);} return page;}

function welcome(ad) {if (firstTime(thisPage())) {showAd(ad,3,1);}}

function locatorWin() {var lwin = window.open('locwin.htm','findit','height=100,width=250,toolbar=no,directories=no,status=no,menubar=no,scrollbars=no,resizable=no');lwin.moveTo(0,0);lwin.focus();}

var awd = new Array;var thisImg = 0;function rotate() {if (document.images) {thisImg++;if (thisImg == awd.length) {thisImg = 0;}document.rotimg.src = awd[thisImg];setTimeout("rotate()",2000);}}

// guestmap
function newWindow(pagename) {browserVersion = parseInt(navigator.appVersion);
if ((navigator.userAgent.indexOf('Opera 5') != -1) || (navigator.userAgent.indexOf('Opera 6') != -1)) {alert('The guestmap does not support Opera 6 or earlier.');
} else if ((navigator.appName.indexOf('Netscape') != -1) && (browserVersion <= 4)) {
alert('The guestmap does not support Netscape 4 or earlier.');
} else {height = findLivePageHeight(); if (height > 675) height = 675;
width = findLivePageWidth(); if (width > 1300) width=1300; var parm = 'toolbar=0,location=0,directories=0,status=0,menubar=0,scrollbars=1,resizable=0,height='
+ height + ',width=' + width; var myWin = window.open(pagename, 'mywin', parm); myWin.moveTo(0,0); myWin.focus();}}
function guest() {location.href = 'guestlst.php'; newWindow('guestmap.php');}

document.getElementsByClassName = function(cl) {var retnode = [];var myclass = new RegExp('\\b'+cl+'\\b');var elem = this.getElementsByTagName('*');for (var i = 0; i < elem.length; i++) {var classes = elem[i].className;if (myclass.test(classes)) retnode.push(elem[i]);}return retnode;};

function startnav() {
var theNav = document.getElementsByClassName('navhide');
for(var i = theNav.length-1; i>=0;i--) {theNav[i].style.display = 'block';}
}
function finish() {
if (uri.page == 'ask') {document.myform['name'].focus();}
if (uri.page == 'index') {welcome('a1');}
if (uri.page == 'jstip19') {showAd('a1',5,0);}
if (uri.page == 'jstip36') {hm();}
if (uri.page == 'jstip48') {initdt(document.myform);}
if (uri.page == 'link1a' || uri.page == 'site3') {rotate();}
if (uri.page == 'javadom9') {initStat();}
if (uri.page == 'guestlst') {initGuest();}
if (uri.page == 'jstip64') {tip64();}
}
var pageLoaded = 0;
window.onload = function() {pageLoaded = 1;finish();}
function loaded(i,f) {
if (document.getElementById && document.getElementById(i) != null) f();
else if (!pageLoaded) setTimeout('loaded(\''+i+'\','+f+')',100);
}
loaded('nav1',startnav);

sfh = function() {var sfE = document.getElementById("nav").getElementsByTagName("li"); for (var i=sfE.length-1; i >= 0; i--) {sfE[i].onmouseover=function() { this.className+=" sfh"; }; sfE[i].onmouseout=function() { this.className=this.className.replace(new RegExp(" sfh\\b"), ""); }; }}; if (window.attachEvent) window.attachEvent("onload", sfh);

function posTop() {return typeof window.pageYOffset != 'undefined' ?  window.pageYOffset : document.documentElement && document.documentElement.scrollTop ? document.documentElement.scrollTop : document.body.scrollTop ? document.body.scrollTop : 0;}
function moveit() {var y = posTop(); document.getElementById('nav').style.top = ((y>145)?y:145)+'px';} window.onscroll = moveit;

var adverts = [
'<div style="margin:0 auto;width:300px;border:1px dashed #f00;background-color:#fff"><h4 style="margin:0 auto;width:210px;">Ask Felgall Member\'s Area</h4><form name="myform" action="members/joinfree.php" method="post"><table border="0" ><tr><td>User Name:</td><td><input type="text" name="user_name" size="10" maxlength="10" value="" /></td></tr><tr><td>Email:</td><td><input type="text" name="destemail" size="25" maxlength="100" value-"" /></td></tr><tr><td colspan="2" align="center">&nbsp;<br /><input type="submit" value="  Join Now - Free " /></td></tr></table></form></div>',
'<script type="text/javaScript" src="http:\/\/www.bravenet.com\/cserv.php?pid=4&tid=5&amp;afilid=1121731189"><\/script>',
'<a href="http:\/\/www.trafficzap.com\/exchange\/index.php?rid=50017&amp;q=821"><img src="http:\/\/www.trafficzap.com\/exchange\/images\/zap\/tzap120gold.gif" width="120" height="60" alt="" alt="Join the TrafficZap Exchange" border="0"><\/a>',
'<script src="http:\/\/www.bluehost.com\/src\/js\/felgall\/CODE7\/125x125\/3.gif"><\/script>',
'<script type="text\/javascript" src="http:\/\/pagead2.googlesyndication.com\/pagead\/show_ads.js"><\/script>',
'<a href="http:\/\/www.elistsecrets.com\/rep\/felgall"><img src="http:\/\/www.elistsecrets.com\/banners.php?sz=7&amp;st=" width="250" height="250" alt="eList Secrets" border="0" \/><\/a>',
'<a href="http:\/\/www.surefirewealth.com\/rep\/felgall1\/mem.html"><img src="http:\/\/www.surefirewealth.com\/banners.php?sz=4&f=125X125.gif"  width="125" height="125" alt="SureFire Wealth" border="0" \/></a>',
'<a href="http:\/\/members.felgall.com\/"><img src="members/img/logo.gif"  width="165" height="150" alt="Ask Felgall Members Area" border="0" \/></a>',
'<a href="http:\/\/www.trafficsecretsunleashed.com\/?s=436" target="_blank"><img src="http:\/\/www.trafficsecretsunleashed.com\/images\/125x125.gif" width="125" height="125" border="0" \/><\/a>'
];
function randOrd(){return (Math.round(Math.random())-0.5); } 
adverts.sort(randOrd);
var showgoogle = 0;
var num = Math.floor(Math.random() * 50);
if ((navigator.appName.indexOf('Netscape') != -1)
&& (parseInt(navigator.appVersion) <=4)) num = 1;
if (uri.page != 'index' && uri.page != 'notfound' && uri.page != 'hidden' && uri.page.substring(0,5) != 'thank' && uri.page.substring(0,4) != 'site' && uri.page.substring(0,4) != 'link' && uri.ext != 'php' && num > 4) showgoogle = 1;

/*@cc_on
  @if (@_jscript)
onbeforeprint = function() {document.getElementById('wrapper').style.width = '100%';}
onafterprint = function() {document.getElementById('wrapper').style.width = document.body.clientWidth > 850 ? '850px' : (document.body.clientWidth < 571 ? '570px' : '94%')};
  @end
@*/
