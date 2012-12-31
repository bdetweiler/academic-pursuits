

var gBVType='firefox',gBVVersion='20',gOSType='windows nt 5';

/* This source code is Copyright (c) Vibrant Media 2001-2007 and forms part of the
patent-pending Vibrant Media product "IntelliTXT" (sm). */
function lES(url){
var e = document.createElement("script");
e.src = url;
e.type="text/javascript";
document.getElementsByTagName("body")[0].appendChild(e);
}

function iG(){
gHN=new Array('!ad_txt');
gAN=new Array();
gSN=new Array('<b>','<h1>','<h2>','<h3>','<h4>','<h5>','<strong>','<em>','<i>','box_tr','!smallfont','!ad_notxt');
gUPN=new Array('<b>','<i>','<u>');
gBPN=new Array();
}

function kwM(){
var ad=fABDID(aAD,gDI);
if(null==ad)return;
window.status=ad.t.replace(/\&pound\;/, '?');
}

var gCLM=1,
gK=new Array(),
gKL=new Array();

gITXTNIdx=0;
function cpl(s){
var p=s.indexOf(' '),
c=1;
while(p>=0){
p=s.indexOf(' ',p+1);
c++;
}
return c;
}
for(var i=0;i<gK.length;i++)gKL[i]=cpl(gK[i]);

document.getElementsByClassName = function(cl) {
var retnode = [];
var myclass = new RegExp('\\b'+cl+'\\b');
var elem = this.getElementsByTagName('*');
for (var i = 0; i < elem.length; i++) {
var classes = elem[i].className;
if (myclass.test(classes)) retnode.push(elem[i]);
}
return retnode;
};

function trimWS(t){
 return t.replace(/^\s+|\s+$/g,"").replace(/\n/g," ");
}
function stripTags(t){
 while (t.match(/<.*>/)) t = t.replace(/<[^>]*>/, "");
 return t;
}
function doIt(){

ipartid=881;
ibid=1593;
ipid=3052;
t_s='20070712082027';
mk=10;
server='daniweb.us.intellitxt.com';
cc='us';
rcc='us';
itxtreg='ky';
itxtdma='632';
ulS='font-weight:normal;font-size:100%;text-decoration:underline;border-bottom:darkgreen 0.075em solid;padding-bottom: 1px;color:darkgreen;background-color:transparent;padding-bottom:1px';
hS='font-weight:normal;font-size:100%;text-decoration:underline;border-bottom:darkgreen 0.2em solid;padding-bottom: 1px;color:darkgreen;background-color:transparent;padding-bottom:1px';
iEulS='font-weight:bold;text-decoration:none;border-bottom:none;padding-bottom:0px;color:#003399;background-color:transparent;cursor:pointer;cursor:hand;';
iEhS='font-weight:bold;text-decoration:none;border-bottom:#0033ac 1px dashed;padding-bottom:0px;color:#003399;background-color:transparent;cursor:pointer;cursor:hand;';
sWTU='http://www.daniweb.com/intellitxt.php';
iCF=3;
gDBL=0;
kwpn=1;
kwpp=-1;
gSkp=0;
ppp=false;
gTI='';
gATIg='';
gATIr='http://images.intellitxt.com/ast/adTypes/';
gATIs='height:10px;width:10px;position:relative;top:1px;left:1px;padding:0px;padding-right:0px;margin:0px;border:none;';
gFTTm='||||||||||||||||preloader.swf$$320$$200$$8|||||||||||||||preloader.swf$$320$$200$$8||preloader.swf$$320$$200$$8||||||||||||preloader.swf$$320$$200$$8||preloader.swf$$300$$250$$8';
gFTTr='http://images.intellitxt.com/ast/allflash_adunit/prod/';
gFOJBG='#FFFFFF';
gFFMF='0';
gSVURL='';
gSVIMG='';
gFdBck='';
gSI=1;
gSID='ea8cfbe964629a9036ec031c16e0a06b';
mTL=50;
gDrag=1;
gOFlt=0;
gIRB=0;
gTTt=1500;
gDASB=3;
gAUAT=0;
gDAT='6,12,18,25';
gEAT='';
gHLN=1;
gKWPF=0;
gPVU='4150eba9791b4c438d9f89b73f03f1b3';
gPVM='b1645ef7e2bd633b76d22d14a816d854';
gIPL=0;
iTTC=0;

gLCL=0;
if('v1'==gCM)mTL=0;
ndbST=new Date().getTime();
iDW();
if(gCM=='v1')
gITXTN=gIA2();
else
gITXTN=gIA(gdB, gCM, 0);
skippinder();
var bCF=1;

var aCs=new Array();
gCntIP(aCs);

if( (true) && (true && ((bCF==1 && gCL) || (gIRB==1 && bCF==0 && gCL>=(gLCL * 1.1)) || (gDTo==false && gIRB==1 && bCF==0 && Math.abs(gCL-gLCL)>=(gLCL * 10) / 100)))) {

// this only needs to be done if we're SPITing and we're running IntelliEdit
var tTXT='',aIEE,dDate='';

if(tTXT.length==0)tTXT=document.title;

gINt=' zxz ';
for(var i=0;i<aCs.length;i++)
gINt+=aCs[i];
var pTx=gINt,
nC=0,cn=0,sTx='',sSptTs=(new Date()).getTime(),chnkSz=(iNBc?250:500);
if (pEsc(pTx).length>chnkSz) {
   
sTx=pTx.substring(0,chnkSz);
while (sTx.length==chnkSz) {
    
lES('http://'+server+'/v3/chunks.jsp?ipid='+ipid+'&sid='+gSID+'&ts='+sSptTs+'&enc='+gENC+'&cn='+cn+'&tx='+pEsc(sTx));

nC+=chnkSz;cn++;
sTx=pTx.substring(nC, nC+chnkSz);
}
   
lES('http://'+server+'/v3/chunks.jsp?ipid='+ipid+'&sid='+gSID+'&nbc='+iNBc+'&ts='+sSptTs+'&enc='+gENC+'&cn='+cn+'&tx='+pEsc(sTx));
var sSpt = 'http://'+server+'/v3/spit.jsp?ipid='+ipid+'&ts='+sSptTs+'&pagecl=15000&cc='+cc+'&rcc='+rcc+'&reg='+itxtreg+'&dma='+itxtdma+'&dfr=false&fdt=0&ign86=false&cn='+cn+'&cf='+iCF+'&mk='+mk+'&kwpn='+kwpn+'&ppp='+ppp+'&kwpp='+kwpp+'&sid='+gSID+'&si='+gSI+'&rdtm='+iRDTM+'&rrm='+iRRM+'&rcpcm='+iRCPCM+'&ripsm='+iRIPSM+'&rorm='+iRORM+'&walg='+iWAlg+'&wpsm='+iWPSM+'&wpim='+iWPIM+'&wsmth='+iWSMTH+'&wcrv='+iWCRV+'&dfc='+iDFC+'&rp='+bYCR+'&so='+iSo+'&nbc='+iNBc+'&adi='+iADi+'&ac=0&dat='+gDAT+'&eat='+gEAT+'&irb='+gIRB+'&enc='+gENC+'&ims=2&iek=0&iel=4&ieak=0&ieix=true&iedm=0&ttxt='+escape(tTXT)+'&auat=0&lpgv=0&ddate='+dDate+'&pvu='+gPVU+'&pvm='+gPVM+'&ias='+itxtIas+'&ru='+pEsc(sRU);

window.setTimeout('lES(\''+sSpt+'\');', 250);
} else

lES('http://'+server+'/v3/spit.jsp?ipid='+ipid+'&ts='+sSptTs+'&pagecl=15000&cc='+cc+'&rcc='+rcc+'&reg='+itxtreg+'&dma='+itxtdma+'&dfr=false&fdt=0&ign86=false&cf='+iCF+'&mk='+mk+'&kwpn='+kwpn+'&ppp='+ppp+'&kwpp='+kwpp+'&sid='+gSID+'&si='+gSI+'&rdtm='+iRDTM+'&rrm='+iRRM+'&rcpcm='+iRCPCM+'&ripsm='+iRIPSM+'&rorm='+iRORM+'&walg='+iWAlg+'&wpsm='+iWPSM+'&wpim='+iWPIM+'&wsmth='+iWSMTH+'&wcrv='+iWCRV+'&dfc='+iDFC+'&rp='+bYCR+'&so='+iSo+'&nbc='+iNBc+'&adi='+iADi+'&ac=0&dat='+gDAT+'&eat='+gEAT+'&irb='+gIRB+'&enc='+gENC+'&ims=2&iek=0&iel=4&ieak=0&ieix=true&iedm=0&ttxt='+pEsc(tTXT)+'&auat=0&lpgv=0&ddate='+dDate+'&pvu='+gPVU+'&pvm='+gPVM+'&ias='+itxtIas+'&ru='+pEsc(sRU)+'&tx='+pEsc(pTx));

gSpitTimer = window.setInterval('checkSpit();', 5000);
} else if (gCL)

 {

if ((gITXTN == null) || (gITXTN != null && gITXTN.length==0))
gITXTN=gIA(gdB, gCM, 0);
if (gITXTN != null && gITXTN.length)
if (gCL>0) rKWL(250);

}
}
var ndbST,
iRDTM=100000000,
iRRM=100000,
iRCPCM=10000,
iRIPSM=1000,
iRCLM=1,
iRORM=10000,
iWAlg=0,
iWPSM=75,
iWPIM=50,
iWSMTH=1.0,
iWCRV=1.0,
iDFC=0,
iTTl=1,
iTTp=0,
iSo=0,
iNBc=0,
iADi=0,
sKPs='~',
sKFs='|',
sRU='http://www.daniweb.com/forums/thread67272.html',
gMR=1000,
bWAC=0,
bYCR=0,
gMNC=255,
gTTD=50,
iIEK=0,
sIEFH='',
ieslu='',
iessu='',
iesbu='',
iewtu='',
iett='',
iDAH=0,
gFES=0,
gSDCv=0,
gFAo=1,
gPmoe=0,
gTlpC=new Object();
gTlpC.tttc='#000099';gTlpC.ttht='#0000DE';
gTlpC.ttdc='#000000';gTlpC.tthdc='#000000';
gTlpC.ttac='#008000';gTlpC.ttha='#008000';
gTlpC.ttbg='#F0F0F0';gTlpC.tthv='#FFFFFF';
var sspl='Advertisement',
swti='What\'s this?',
slm='LEARN MORE',
ssch='Searching...',
sbn='Buy now',
scls='Close',
sCC='$',
sEet='End time',
sEcb='Place bid',
sEsn='Seller',
iert='Related Articles';
var gNeedProtos=1;

var prevOnload=(window.onload?window.onload:new Function()),
itxtInited=0,
itxtPrevOnloadCalled=0;
function itxtOnloader() {
 
startIntelliTXT(0);
}
function itxtStateChange() {
 
startIntelliTXT(1);
}
function startIntelliTXT(v) {
 
if (!v) {
if( itxtPrevOnloadCalled )
return;
itxtPrevOnloadCalled=1;
prevOnload();
}
if (itxtInited) return;
 
itxtInited=1;
lES('http://images.intellitxt.com/ast/js/vm/func_200706222110.js');
}
window.onload=itxtOnloader;
window.setTimeout('startIntelliTXT(1);',3000);

