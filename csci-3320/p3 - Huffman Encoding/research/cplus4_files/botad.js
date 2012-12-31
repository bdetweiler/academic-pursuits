if(document.layers)  oldopera = true;
if (!oldopera)
 {
document.writeln('<div class="noprint1">');

if (showgoogle && !window.opera) {
 // google adsense
google_ad_client = "pub-4537544073997079";
google_alternate_color = "d7f7ff";
google_ad_width = 336;
google_ad_height = 280;
google_ad_format = "336x280_as";
google_ad_channel ="5428712153";
google_color_link = ["0000ff"];
google_color_url = ["777777"];
google_color_text = ["000000"];
google_color_bg = ["d7f7ff"];
google_color_border = ["d7f7ff"];
document.writeln('<script type="text\/javascript" src="http:\/\/pagead2.googlesyndication.com\/pagead/show_ads.js"><\/script>');
} else {
google_ad_client = "pub-4537544073997079";
google_ad_width = 125;
google_ad_height = 125;
google_ad_format = "125x125_as_rimg";
google_cpa_choice = "CAAQueabzgEaCMowawMgvVU8KInC93M";
document.write(adverts[1]);
}
document.writeln('<\/div>');
}
