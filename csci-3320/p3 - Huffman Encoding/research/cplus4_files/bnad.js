var oldopera = false;
var agt=navigator.userAgent.toLowerCase();
if(agt.substr(agt.indexOf('opera')+6,1) < 9) oldopera = true;
if(document.layers)  oldopera = true;
if (!oldopera)
 {
 // google adsense
google_ad_client = "pub-4537544073997079";
google_alternate_color = "d7f7ff";
if (findLivePageWidth() > 790) {
google_ad_width = 728;
google_ad_height = 90;
google_ad_format = "728x90_as";
} else {
google_ad_width = 468;
google_ad_height = 60;
google_ad_format = "468x60_as";
}
google_ad_type = "text_image";
google_ad_channel ="4526289903";
google_color_link = ["0000ff"];
google_color_url = ["777777"];
google_color_text = ["000000"];
google_color_bg = ["d7f7ff"];
google_color_border = ["d7f7ff"];
document.writeln('<script type="text\/javascript" src="http:\/\/pagead2.googlesyndication.com\/pagead\/show_ads.js"><\/script>');
}

